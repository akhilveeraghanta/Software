#include "firmware_new/boards/frankie_v1/io/ublox_odinw262_communicator_buffer_handlers.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

inline UbloxResponseStatus_t
io_ublox_odinw262_communicator_getUbloxResponseStatusFromCircularBuffer(
    size_t current_byte_position, size_t buffer_length, uint8_t* circular_buffer)
{
    // This function is desgined to run inside an interrupt routine, triggered when there
    // is an idle line on the g_ublox_uart_handle peripheral. The DMA receive buffer is
    // configured in circular mode with the IDLE_LINE interrupt enabled.
    //
    // To learn more about UART + DMA + Idle Line Detection, visit this link:
    // https://stm32f4-discovery.net/2017/07/stm32-tutorial-efficiently-receive-uart-data-using-dma/
    //
    // This function is supposed to be _fast_ and its only purpose is to figure out if the
    // u-blox finished transmission (it checks for either an ERROR\r\n or an OK\r\n when
    // the IDLE_LINE interrupt is triggered) and returns.
    //
    //          circular_buffer              start_pos_response_ok
    //                                                             circular_buffer +
    //                                                             buffer_length
    //               │                                   │
    //               │                                   │                        │
    //            ┌──▼───────────────────────────────────▼────────────────────────▼──┐
    //            │ ┌─┐┌─┐┌─┐┌─┐┌─┐┌─┐┌─┐┌─┐┌─┐┌─┐┌─┐┌─┐┌─┐┌─┐┌─┐┌─┐             ┌─┐ │
    //            │ │A││T││R││N││O││K││R││N││A││T││R││N││O││K││R││N│ ──────────▶ │?│ │
    //            │ └─┘└─┘└─┘└─┘└─┘└─┘└─┘└─┘└─┘└─┘└─┘└─┘└─┘└─┘└─┘└─┘             └─┘ │
    //            └─────────────────────────────▲─────────────────▲──────────────────┘
    //                                          │                 │
    //                                          │                 │
    //                                                            │
    //                              start_pos_response_error      │
    //
    //                                                   current_byte_position
    //
    //  We can assume that we will be sending valid AT commands, so we can compute the
    //  position of where the UBLOX_RESPONSE_OK would start first, and store it in
    //  start_pos_response_ok. We then compare the characters starting from
    //  start_pos_response_ok in the circular_buffer and check if they match
    //  UBLOX_RESPONSE_OK. If they match we return UBLOX_RESPONSE_OK.
    //
    //  If UBLOX_RESPONSE_OK does not match, it's likely we received an error, so we
    //  repeat the same steps with g_ublox_error_response.
    //
    //  If g_ublox_error_response does not match, the UART_IT_IDLE must have triggered
    //  prematurely. We return UBLOX_RESPONSE_INCOMPLETE in this case.
    //
    UbloxResponseStatus_t ublox_response_status = UBLOX_RESPONSE_UNDETERMINED;

    size_t start_pos_response_ok =
        (buffer_length + current_byte_position - UBLOX_OK_RESPONSE_LENGTH_BYTES) %
        buffer_length;

    for (size_t k = 0; k < UBLOX_OK_RESPONSE_LENGTH_BYTES; k++)
    {
        if (UBLOX_OK_RESPONSE_STRING[k] !=
            circular_buffer[(start_pos_response_ok + k) % buffer_length])
        {
            ublox_response_status = UBLOX_RESPONSE_INCOMPLETE;
            break;
        }
    }

    if (ublox_response_status == UBLOX_RESPONSE_UNDETERMINED)
    {
        return UBLOX_RESPONSE_OK;
    }

    ublox_response_status = UBLOX_RESPONSE_UNDETERMINED;

    size_t start_pos_response_error =
        (buffer_length + current_byte_position - UBLOX_ERROR_RESPONSE_LENGTH_BYTES) %
        buffer_length;
    for (size_t k = 0; k < UBLOX_ERROR_RESPONSE_LENGTH_BYTES; k++)
    {
        if (UBLOX_ERROR_RESPONSE_STRING[k] !=
            circular_buffer[(start_pos_response_error + k) % buffer_length])
        {
            ublox_response_status = UBLOX_RESPONSE_INCOMPLETE;
            break;
        }
    }

    if (ublox_response_status == UBLOX_RESPONSE_UNDETERMINED)
    {
        return UBLOX_RESPONSE_ERROR;
    }

    return ublox_response_status;
}

void io_ublox_odinw262_communicator_extractResponseFromCircularBuffer(
    size_t last_parsed_byte_position, size_t current_byte_position, size_t buffer_length,
    uint8_t* circular_buffer, uint8_t* linear_buffer)
{
    if (last_parsed_byte_position < current_byte_position)
    {
        memcpy(linear_buffer, circular_buffer + last_parsed_byte_position,
               current_byte_position - last_parsed_byte_position);
    }
    else
    {
        memcpy(linear_buffer, circular_buffer + last_parsed_byte_position,
               buffer_length - last_parsed_byte_position);

        memcpy(linear_buffer + (buffer_length - last_parsed_byte_position),
               circular_buffer, current_byte_position);
    }
}
