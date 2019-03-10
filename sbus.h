/*! \copyright 2019 Zorxx Software. All rights reserved.
 *  \file sbus.h
 *  \brief SBUS parser
 */
#ifndef SBUS_H
#define SBUS_H

#include <stdint.h>

#define SBUS_MESSAGE_DATA_LENGTH 23
#define SBUS_BAUD_RATE           100000
#define SBUS_DATA_BITS           8
#define SBUS_STOP_BITS           2
#define SBUS_PARITY              /*EVEN*/

typedef union
{
   struct
   {
      unsigned channel1: 11;
      unsigned channel2: 11;
      unsigned channel3: 11;
      unsigned channel4: 11;
      unsigned channel5: 11;
      unsigned channel6: 11;
      unsigned channel7: 11;
      unsigned channel8: 11;
      unsigned channel9: 11;
      unsigned channel10: 11;
      unsigned channel11: 11;
      unsigned channel12: 11;
      unsigned channel13: 11;
      unsigned channel14: 11;
      unsigned channel15: 11;
      unsigned channel16: 11;
      unsigned channel17: 1;
      unsigned channel18: 1;
      unsigned frame_lost: 1;
      unsigned failsafe: 1;
      unsigned reserved: 4;
   } bits;
   uint8_t bytes[SBUS_MESSAGE_DATA_LENGTH];
} __attribute__((packed)) sbus_message_t;

typedef struct
{
   uint32_t invalid_message;
   uint32_t valid_message;
   uint32_t discard_idle;
} sbus_stats_t;

typedef void (*pfnHandleMessage)(const sbus_message_t message); 

void sbus_parse_init(pfnHandleMessage messageHandler);
void sbus_parse_reset(void);
void sbus_get_stats(sbus_stats_t *pStats);
void sbus_parse_char(uint8_t c);

#endif /* SBUS_H */
