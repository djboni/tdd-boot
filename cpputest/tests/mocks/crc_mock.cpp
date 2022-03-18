#include "crc.h"

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

crc_t CRCCalcBuff(const uint8_t *buff_ptr, uint16_t size)
{
    crc_t crc;

    crc.crc = mock()
                  .actualCall("CRCCalcBuff")
                  .withParameter("buff_ptr", buff_ptr)
                  .withParameter("size", size)
                  .returnIntValueOrDefault(0xFFFF);

    return crc;
}
