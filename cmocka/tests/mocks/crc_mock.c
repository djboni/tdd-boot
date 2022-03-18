#include "crc.h"

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "cmocka.h"

crc_t CRCCalcBuff(const uint8_t *buff_ptr, uint16_t size)
{
    crc_t crc;

    check_expected(buff_ptr);
    check_expected(size);
    crc.crc = mock();

    return crc;
}
