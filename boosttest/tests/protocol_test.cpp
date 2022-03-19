#include "protocol.h"

#define BOOST_TEST_DYN_LINK
#include "boost/test/unit_test.hpp"

/*
 * Also compile: fakes/crc_fake.cpp
 */
#include "fakes/crc_fake.h"

struct TestSuiteFixture
{
    /* Set-up. */
    TestSuiteFixture() { Fake_CRCCalcBuff_Reset(); }

    /* Tear-down. */
    ~TestSuiteFixture() {}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteName, TestSuiteFixture)

BOOST_AUTO_TEST_CASE(Precondition_ExpectedCRCSizeIs_2Bytes_16Bits)
{
    /* In these tests the only assumption about the CRC is the size. */
    crc_t crc;
    BOOST_TEST(2U == sizeof(crc.crc));
}

BOOST_AUTO_TEST_CASE(MessageAndCRCFitOnBuff_ReturnsOK)
{
    uint8_t buff[3] = {0x5A, 0x5A, 0x5A};
    uint8_t msg = '\0';

    BOOST_TEST(PROTOCOL_OK == ProtocolAppendCRC(&buff[0], 3, &msg, 1));
}

BOOST_AUTO_TEST_CASE(MessageAndCRCFitOnBuff_ReturnsOK_2)
{
    uint8_t buff[4] = {0x5A, 0x5A, 0x5A, 0x5A};
    uint8_t msg = '\0';

    BOOST_TEST(PROTOCOL_OK == ProtocolAppendCRC(&buff[0], 4, &msg, 1));
}

BOOST_AUTO_TEST_CASE(MessageAndCRCFitOnBuff_ReturnsOK_3)
{
    uint8_t buff[2] = {0x5A, 0x5A};
    uint8_t msg = '\0';

    BOOST_TEST(PROTOCOL_OK == ProtocolAppendCRC(&buff[0], 2, &msg, 0));
}

BOOST_AUTO_TEST_CASE(MessageAndCRCDontFitOnBuff_ReturnsERR)
{
    uint8_t buff[2] = {0x5A, 0x5A};
    uint8_t msg = '\0';

    BOOST_TEST(PROTOCOL_ERR == ProtocolAppendCRC(&buff[0], 2, &msg, 1));
}

BOOST_AUTO_TEST_CASE(MessageAndCRCDontFitOnBuff_ReturnsERR_2)
{
    uint8_t buff[1] = {0x5A};
    uint8_t msg = '\0';

    BOOST_TEST(PROTOCOL_ERR == ProtocolAppendCRC(&buff[0], 1, &msg, 0));
}

BOOST_AUTO_TEST_CASE(MessageAndCRCAreCopiedToBuff)
{
    uint8_t buff[3] = {0x5A, 0x5A, 0x5A};
    uint8_t msg = '\0';

    Fake_CRCCalcBuff_SetReturnValue(crc_t{0xAA55});

    ProtocolAppendCRC(&buff[0], 3, &msg, 1);

    BOOST_TEST(0 == buff[0]);
    BOOST_TEST(0x55 == buff[1]);
    BOOST_TEST(0xAA == buff[2]);
}

BOOST_AUTO_TEST_CASE(MessageAndCRCAreCopiedToBuff_2)
{
    uint8_t buff[4] = {0x5A, 0x5A, 0x5A, 0x5A};
    uint8_t msg[2] = {'A', 'B'};

    Fake_CRCCalcBuff_SetReturnValue(crc_t{0xBB66});

    ProtocolAppendCRC(&buff[0], 4, &msg[0], 2);

    BOOST_TEST('A' == buff[0]);
    BOOST_TEST('B' == buff[1]);
    BOOST_TEST(0x66 == buff[2]);
    BOOST_TEST(0xBB == buff[3]);
}

BOOST_AUTO_TEST_CASE(MessageAndCRCAreCopiedToBuff_3)
{
    uint8_t buff[2] = {0x5A, 0x5A};
    uint8_t msg = '\0';

    Fake_CRCCalcBuff_SetReturnValue(crc_t{0xCC77});

    ProtocolAppendCRC(&buff[0], 2, &msg, 0);

    BOOST_TEST(0x77 == buff[0]);
    BOOST_TEST(0xCC == buff[1]);
}

BOOST_AUTO_TEST_SUITE_END()
