#include "protocol.h"

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

/*
 * Also compile: mocks/crc_mock.cpp
 */

TEST_GROUP (Protocol)
{
    void setup() {}
    void teardown() {}
};

TEST(Protocol, Precondition_ExpectedCRCSizeIs_2Bytes_16Bits)
{
    /* In these tests the only assumption about the CRC is the size. */
    crc_t crc;
    LONGS_EQUAL(2, sizeof(crc.crc));
}

TEST(Protocol, MessageAndCRCFitOnBuff_ReturnsOK)
{
    uint8_t buff[3] = {0x5A, 0x5A, 0x5A};
    uint8_t msg = '\0';

    mock().ignoreOtherCalls();

    LONGS_EQUAL(PROTOCOL_OK, ProtocolAppendCRC(&buff[0], 3, &msg, 1));
}

TEST(Protocol, MessageAndCRCFitOnBuff_ReturnsOK_2)
{
    uint8_t buff[4] = {0x5A, 0x5A, 0x5A, 0x5A};
    uint8_t msg = '\0';

    mock().ignoreOtherCalls();

    LONGS_EQUAL(PROTOCOL_OK, ProtocolAppendCRC(&buff[0], 4, &msg, 1));
}

TEST(Protocol, MessageAndCRCFitOnBuff_ReturnsOK_3)
{
    uint8_t buff[2] = {0x5A, 0x5A};
    uint8_t msg = '\0';

    mock().ignoreOtherCalls();

    LONGS_EQUAL(PROTOCOL_OK, ProtocolAppendCRC(&buff[0], 2, &msg, 0));
}

TEST(Protocol, MessageAndCRCDontFitOnBuff_ReturnsERR)
{
    uint8_t buff[2] = {0x5A, 0x5A};
    uint8_t msg = '\0';

    LONGS_EQUAL(PROTOCOL_ERR, ProtocolAppendCRC(&buff[0], 2, &msg, 1));
}

TEST(Protocol, MessageAndCRCDontFitOnBuff_ReturnsERR_2)
{
    uint8_t buff[1] = {0x5A};
    uint8_t msg = '\0';

    LONGS_EQUAL(PROTOCOL_ERR, ProtocolAppendCRC(&buff[0], 1, &msg, 0));
}

TEST(Protocol, MessageAndCRCAreCopiedToBuff)
{
    uint8_t buff[3] = {0x5A, 0x5A, 0x5A};
    uint8_t msg = '\0';

    mock()
        .expectOneCall("CRCCalcBuff")
        .withParameter("buff_ptr", (const uint8_t *)&msg)
        .withParameter("size", 1)
        .andReturnValue(0xAA55);

    ProtocolAppendCRC(&buff[0], 3, &msg, 1);

    LONGS_EQUAL(0, buff[0]);
    LONGS_EQUAL(0x55, buff[1]);
    LONGS_EQUAL(0xAA, buff[2]);
}

TEST(Protocol, MessageAndCRCAreCopiedToBuff_2)
{
    uint8_t buff[4] = {0x5A, 0x5A, 0x5A, 0x5A};
    uint8_t msg[2] = {'A', 'B'};

    mock()
        .expectOneCall("CRCCalcBuff")
        .withParameter("buff_ptr", (const uint8_t *)&msg)
        .withParameter("size", 2)
        .andReturnValue(0xBB66);

    ProtocolAppendCRC(&buff[0], 4, &msg[0], 2);

    LONGS_EQUAL('A', buff[0]);
    LONGS_EQUAL('B', buff[1]);
    LONGS_EQUAL(0x66, buff[2]);
    LONGS_EQUAL(0xBB, buff[3]);
}

TEST(Protocol, MessageAndCRCAreCopiedToBuff_3)
{
    uint8_t buff[2] = {0x5A, 0x5A};
    uint8_t msg = '\0';

    mock()
        .expectOneCall("CRCCalcBuff")
        .withParameter("buff_ptr", (const uint8_t *)&msg)
        .withParameter("size", 0)
        .andReturnValue(0xCC77);

    ProtocolAppendCRC(&buff[0], 2, &msg, 0);

    LONGS_EQUAL(0x77, buff[0]);
    LONGS_EQUAL(0xCC, buff[1]);
}
