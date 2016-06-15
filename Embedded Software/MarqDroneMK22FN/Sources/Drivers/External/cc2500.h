/** @file cc2500.h
*
* @brief cc2500 radio functions
*
* @author Alvaro Prieto
*     derived from SLAA465 examples
*/
#ifndef _CC2500_H
#define _CC2500_H

#include <stdint.h>
#include <stdbool.h>

#define CC2500_BUFFER_LENGTH 64

//#ifndef DEVICE_ADDRESS
//#define DEVICE_ADDRESS 0x00
//#error Device address not set!
//#endif


extern bool CC_2500_SETUP_DONE;


uint8_t setup_cc2500();
void cc2500_tx( uint8_t*, uint8_t );

void cc2500_tx_packet( uint8_t*, uint8_t, uint8_t );

void cc2500_set_address( uint8_t );
void cc2500_set_channel( uint8_t );
void cc2500_set_power( uint8_t );

void cc2500_sleep( );

void cc2500_enable_addressing();
void cc2500_disable_addressing();

void Quick_Reset_Core();

uint8_t writeRFSettings(void);

uint8_t receive_packet( uint8_t* p_buffer, uint8_t* length );
uint8_t receive_packet_fixed_length( uint8_t* p_buffer, uint8_t length,bool Append_CRC);

/**
 * Packet header structure. The packet length byte is omitted, since the receive
 * function strips it away. Also, the cc2500_tx_packet function inserts it
 * automatically.
 */
typedef struct
{
  uint8_t destination;  // Packet destination
  uint8_t source;       // Packet source
  uint8_t type;         // Packet Type
  uint8_t flags;        // Misc flags
} packet_header_t;

//CC2500 PKTCTRL0 Defines
#define	FIXED_PACKET_LENGTH		0x0
#define VARIABLE_PACKET_LENGTH	0x1
#define CRC_EN					(0x1<<2)

//CC2500 PKTCTRL1 Defines
#define ADR_CHECK_DISABLED		0x0
#define ADR_CHECK_ENABLED		0x1
#define APPEND_STATUS			(0x1<<2)
#define CRC_AUTO_FLUSH			(0x1<<3)



//
// Packet Type Definitions (todo)
//
#define IO_CHANGE (0x01)


#endif /* _CC2500_H */
