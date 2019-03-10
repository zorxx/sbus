/*! \copyright 2019 Zorxx Software. All rights reserved.
 *  \file sbus.c
 *  \brief SBUS parser
 */
#include <stdint.h>
#include "sbus.h"

#define SBUS_HEADER 0x0F
#define SBUS_FOOTER 0x00

typedef void (*pfnHandleChar)(const uint8_t c);

static void handle_char_idle(const uint8_t c);
static void handle_char_data(const uint8_t c);

static sbus_message_t message; 
static uint8_t message_offset;
static pfnHandleChar pCharHandler; 
static pfnHandleMessage pMessageHandler; 
static sbus_stats_t stats;

/* ----------------------------------------------------------------------------------- 
 * Exported Functions
 */

void sbus_parse_init(pfnHandleMessage messageHandler)
{
   pMessageHandler = messageHandler;
	sbus_parse_reset();
}

void sbus_parse_char(uint8_t c)
{
   pCharHandler(c);
}

void sbus_get_stats(sbus_stats_t *pStats)
{
   pStats->invalid_message = stats.invalid_message;
   pStats->valid_message = stats.valid_message;
   pStats->discard_idle = stats.discard_idle;
}

void sbus_parse_reset(void)
{
   pCharHandler = handle_char_idle;
   stats.invalid_message = 0;
   stats.valid_message = 0;
   stats.discard_idle = 0;
}

/* ----------------------------------------------------------------------------------- 
 * Implementation 
 */

static void handle_char_idle(const uint8_t c)
{
   if(SBUS_HEADER == c)
   {
      pCharHandler = handle_char_data;
      message_offset = 0;
   }
   else
      ++stats.discard_idle;
}

static void handle_char_data(const uint8_t c)
{
   if(message_offset >= SBUS_MESSAGE_DATA_LENGTH)
   {
      if(SBUS_FOOTER == c)
      {
         pMessageHandler(message);
			++stats.valid_message;
      }
      else
         ++stats.invalid_message;
      pCharHandler = handle_char_idle;
   }
   else
   {
      message.bytes[message_offset] = c;
      ++message_offset;
   }
}
