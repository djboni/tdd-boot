#ifndef CRC_H_
#define CRC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct
{
    uint16_t crc;
} crc_t;

crc_t CRCCalcBuff(const uint8_t *buff_ptr, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif /* CRC_H_ */
