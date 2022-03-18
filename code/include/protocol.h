#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <crc.h>

typedef enum
{
    PROTOCOL_OK,
    PROTOCOL_ERR
} protocol_result_t;

protocol_result_t ProtocolAppendCRC(
    uint8_t *buff_ptr,
    uint16_t buff_size,
    const uint8_t *msg_ptr,
    uint16_t msg_size);

#ifdef __cplusplus
}
#endif

#endif /* PROTOCOL_H_ */
