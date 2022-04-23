#include "protocol.h"

#include <string.h>

protocol_result_t ProtocolAppendCRC(
    uint8_t *buff_ptr,
    uint16_t buff_size,
    const uint8_t *msg_ptr,
    uint16_t msg_size)
{
    crc_t crc;
    uint8_t i;

    if (buff_size < msg_size + sizeof(crc.crc))
        return PROTOCOL_ERR;

    memcpy(buff_ptr, msg_ptr, msg_size);
    buff_ptr += msg_size;

    crc = CRCCalcBuff(msg_ptr, msg_size);

    for (i = 0; i < sizeof(crc.crc); i++)
    {
        buff_ptr[i] = crc.crc & 0xFF;
        crc.crc >>= 8;
    }

    return PROTOCOL_OK;
}
