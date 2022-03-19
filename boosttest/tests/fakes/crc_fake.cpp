#include "crc.h"

void Fake_CRCCalcBuff_Reset(void);
void Fake_CRCCalcBuff_SetReturnValue(crc_t crc);

static crc_t CRCCalcBuff_ReturnValue{0x0000};

void Fake_CRCCalcBuff_Reset(void)
{
    Fake_CRCCalcBuff_SetReturnValue(crc_t{0x0000});
}

void Fake_CRCCalcBuff_SetReturnValue(crc_t crc)
{
    CRCCalcBuff_ReturnValue = crc;
}

crc_t CRCCalcBuff(const uint8_t *buff_ptr, uint16_t size)
{
    (void)buff_ptr;
    (void)size;
    return CRCCalcBuff_ReturnValue;
}
