#include "protocol.h"

/*
 * Auto-generate mock: include/crc.h
 * Also compile: build/tests/mocks/Mockcrc.c
 */
#include "mocks/Mockcrc.h"

void suiteSetUp(void)
{
}

int suiteTearDown(int num_failures)
{
    return num_failures;
}

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Protocol_Precondition_ExpectedCRCSizeIs_2Bytes_16Bits(void)
{
    /* In these tests the only assumption about the CRC is the size. */
    crc_t crc;
    TEST_ASSERT_EQUAL(2, sizeof(crc.crc));
}

void test_Protocol_MessageAndCRCFitOnBuff_ReturnsOK(void)
{
    uint8_t buff[3] = {0x5A, 0x5A, 0x5A};
    uint8_t msg = '\0';
    crc_t crc = {0xFFFF};

    CRCCalcBuff_ExpectAndReturn(&msg, 1, crc);

    TEST_ASSERT_EQUAL(PROTOCOL_OK, ProtocolAppendCRC(&buff[0], 3, &msg, 1));
}

void test_Protocol_MessageAndCRCFitOnBuff_ReturnsOK_2(void)
{
    uint8_t buff[4] = {0x5A, 0x5A, 0x5A, 0x5A};
    uint8_t msg = '\0';
    crc_t crc = {0xFFFF};

    CRCCalcBuff_ExpectAndReturn(&msg, 1, crc);

    TEST_ASSERT_EQUAL(PROTOCOL_OK, ProtocolAppendCRC(&buff[0], 4, &msg, 1));
}

void test_Protocol_MessageAndCRCFitOnBuff_ReturnsOK_3(void)
{
    uint8_t buff[2] = {0x5A, 0x5A};
    crc_t crc = {0xFFFF};
    uint8_t msg = '\0';

    CRCCalcBuff_ExpectAndReturn(&msg, 0, crc);

    TEST_ASSERT_EQUAL(PROTOCOL_OK, ProtocolAppendCRC(&buff[0], 2, &msg, 0));
}

void test_Protocol_MessageAndCRCDontFitOnBuff_ReturnsERR(void)
{
    uint8_t buff[2] = {0x5A, 0x5A};
    uint8_t msg = '\0';

    TEST_ASSERT_EQUAL(PROTOCOL_ERR, ProtocolAppendCRC(&buff[0], 2, &msg, 1));
}

void test_Protocol_MessageAndCRCDontFitOnBuff_ReturnsERR_2(void)
{
    uint8_t buff[1] = {0x5A};
    uint8_t msg = '\0';

    TEST_ASSERT_EQUAL(PROTOCOL_ERR, ProtocolAppendCRC(&buff[0], 1, &msg, 0));
}

void test_Protocol_MessageAndCRCAreCopiedToBuff(void)
{
    uint8_t buff[3] = {0x5A, 0x5A, 0x5A};
    uint8_t msg = '\0';
    crc_t crc = {0xAA55};

    CRCCalcBuff_ExpectAndReturn(&msg, 1, crc);

    ProtocolAppendCRC(&buff[0], 3, &msg, 1);

    TEST_ASSERT_EQUAL(0, buff[0]);
    TEST_ASSERT_EQUAL(0x55, buff[1]);
    TEST_ASSERT_EQUAL(0xAA, buff[2]);
}

void test_Protocol_MessageAndCRCAreCopiedToBuff_2(void)
{
    uint8_t buff[4] = {0x5A, 0x5A, 0x5A, 0x5A};
    uint8_t msg[2] = {'A', 'B'};
    crc_t crc = {0xBB66};

    CRCCalcBuff_ExpectAndReturn(&msg[0], 2, crc);

    ProtocolAppendCRC(&buff[0], 4, &msg[0], 2);

    TEST_ASSERT_EQUAL('A', buff[0]);
    TEST_ASSERT_EQUAL('B', buff[1]);
    TEST_ASSERT_EQUAL(0x66, buff[2]);
    TEST_ASSERT_EQUAL(0xBB, buff[3]);
}

void test_Protocol_MessageAndCRCAreCopiedToBuff_3(void)
{
    uint8_t buff[2] = {0x5A, 0x5A};
    crc_t crc = {0xCC77};
    uint8_t msg = '\0';

    CRCCalcBuff_ExpectAndReturn(&msg, 0, crc);

    ProtocolAppendCRC(&buff[0], 2, &msg, 0);

    TEST_ASSERT_EQUAL(0x77, buff[0]);
    TEST_ASSERT_EQUAL(0xCC, buff[1]);
}
