#include "protocol.h"

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "cmocka.h"

#include "mocks/crc_mock.c"

int suiteSetUp(void **state)
{
    (void)state;
    return 0;
}

int suiteTearDown(void **state)
{
    (void)state;
    return 0;
}

int setUp(void **state)
{
    (void)state;
    return 0;
}

int tearDown(void **state)
{
    (void)state;
    return 0;
}

void test_Protocol_Precondition_ExpectedCRCSizeIs_2Bytes_16Bits(void **state)
{
    /* In these tests the only assumption about the CRC is the size. */
    (void)state;
    crc_t crc;

    assert_int_equal(2, sizeof(crc.crc));
}

void test_Protocol_MessageAndCRCFitOnBuff_ReturnsOK(void **state)
{
    (void)state;
    uint8_t buff[3] = {0x5A, 0x5A, 0x5A};
    uint8_t msg = '\0';

    ignore_function_calls(CRCCalcBuff);
    expect_any(CRCCalcBuff, buff_ptr);
    expect_any(CRCCalcBuff, size);
    will_return(CRCCalcBuff, 0xFFFF);

    assert_int_equal(PROTOCOL_OK, ProtocolAppendCRC(&buff[0], 3, &msg, 1));
}

void test_Protocol_MessageAndCRCFitOnBuff_ReturnsOK_2(void **state)
{
    (void)state;
    uint8_t buff[4] = {0x5A, 0x5A, 0x5A, 0x5A};
    uint8_t msg = '\0';

    ignore_function_calls(CRCCalcBuff);
    expect_any(CRCCalcBuff, buff_ptr);
    expect_any(CRCCalcBuff, size);
    will_return(CRCCalcBuff, 0xFFFF);

    assert_int_equal(PROTOCOL_OK, ProtocolAppendCRC(&buff[0], 4, &msg, 1));
}

void test_Protocol_MessageAndCRCFitOnBuff_ReturnsOK_3(void **state)
{
    (void)state;
    uint8_t buff[2] = {0x5A, 0x5A};

    ignore_function_calls(CRCCalcBuff);
    expect_any(CRCCalcBuff, buff_ptr);
    expect_any(CRCCalcBuff, size);
    will_return(CRCCalcBuff, 0xFFFF);

    assert_int_equal(PROTOCOL_OK, ProtocolAppendCRC(&buff[0], 2, NULL, 0));
}

void test_Protocol_MessageAndCRCDontFitOnBuff_ReturnsERR(void **state)
{
    (void)state;
    uint8_t buff[2] = {0x5A, 0x5A};
    uint8_t msg = '\0';

    assert_int_equal(PROTOCOL_ERR, ProtocolAppendCRC(&buff[0], 2, &msg, 1));
}

void test_Protocol_MessageAndCRCDontFitOnBuff_ReturnsERR_2(void **state)
{
    (void)state;
    uint8_t buff[1] = {0x5A};

    assert_int_equal(PROTOCOL_ERR, ProtocolAppendCRC(&buff[0], 1, NULL, 0));
}

void test_Protocol_MessageAndCRCAreCopiedToBuff(void **state)
{
    (void)state;
    uint8_t buff[3] = {0x5A, 0x5A, 0x5A};
    uint8_t msg = '\0';

    expect_value(CRCCalcBuff, buff_ptr, &msg);
    expect_value(CRCCalcBuff, size, 1);
    will_return(CRCCalcBuff, 0xAA55);

    ProtocolAppendCRC(&buff[0], 3, &msg, 1);

    assert_int_equal(0, buff[0]);
    assert_int_equal(0x55, buff[1]);
    assert_int_equal(0xAA, buff[2]);
}

void test_Protocol_MessageAndCRCAreCopiedToBuff_2(void **state)
{
    (void)state;
    uint8_t buff[4] = {0x5A, 0x5A, 0x5A, 0x5A};
    uint8_t msg[2] = {'A', 'B'};

    expect_value(CRCCalcBuff, buff_ptr, &msg);
    expect_value(CRCCalcBuff, size, 2);
    will_return(CRCCalcBuff, 0xBB66);

    ProtocolAppendCRC(&buff[0], 4, &msg[0], 2);

    assert_int_equal('A', buff[0]);
    assert_int_equal('B', buff[1]);
    assert_int_equal(0x66, buff[2]);
    assert_int_equal(0xBB, buff[3]);
}

void test_Protocol_MessageAndCRCAreCopiedToBuff_3(void **state)
{
    (void)state;
    uint8_t buff[2] = {0x5A, 0x5A};

    expect_value(CRCCalcBuff, buff_ptr, NULL);
    expect_value(CRCCalcBuff, size, 0);
    will_return(CRCCalcBuff, 0xCC77);

    ProtocolAppendCRC(&buff[0], 2, NULL, 0);

    assert_int_equal(0x77, buff[0]);
    assert_int_equal(0xCC, buff[1]);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(
            test_Protocol_Precondition_ExpectedCRCSizeIs_2Bytes_16Bits,
            setUp,
            tearDown),
        cmocka_unit_test_setup_teardown(
            test_Protocol_MessageAndCRCFitOnBuff_ReturnsOK, setUp, tearDown),
        cmocka_unit_test_setup_teardown(
            test_Protocol_MessageAndCRCFitOnBuff_ReturnsOK_2, setUp, tearDown),
        cmocka_unit_test_setup_teardown(
            test_Protocol_MessageAndCRCFitOnBuff_ReturnsOK_3, setUp, tearDown),
        cmocka_unit_test_setup_teardown(
            test_Protocol_MessageAndCRCDontFitOnBuff_ReturnsERR,
            setUp,
            tearDown),
        cmocka_unit_test_setup_teardown(
            test_Protocol_MessageAndCRCDontFitOnBuff_ReturnsERR_2,
            setUp,
            tearDown),
        cmocka_unit_test_setup_teardown(
            test_Protocol_MessageAndCRCAreCopiedToBuff, setUp, tearDown),
        cmocka_unit_test_setup_teardown(
            test_Protocol_MessageAndCRCAreCopiedToBuff_2, setUp, tearDown),
        cmocka_unit_test_setup_teardown(
            test_Protocol_MessageAndCRCAreCopiedToBuff_3, setUp, tearDown),
    };

    return cmocka_run_group_tests(tests, suiteSetUp, suiteTearDown);
}
