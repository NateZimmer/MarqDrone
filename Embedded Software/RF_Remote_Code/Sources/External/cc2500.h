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

uint8_t setup_cc2500();
void cc2500_tx( uint8_t*, uint8_t );

void cc2500_tx_packet( uint8_t*, uint8_t, uint8_t );


void cc2500_set_address( uint8_t );
void cc2500_set_channel( uint8_t );
void cc2500_set_power( uint8_t );

void cc2500_sleep( );

void cc2500_enable_addressing();
void cc2500_disable_addressing();

uint8_t writeRFSettings(void);
uint8_t receive_packet( uint8_t* p_buffer, uint8_t* length );
uint8_t receive_packet_fixed_length( uint8_t* p_buffer, uint8_t length,bool Append_CRC);
extern bool RF_Keep_Alive;
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

typedef enum
{
	SLEEP=0,
	IDLE=1,
	XOFF=2,
	VCOON_MC=3,
	REGON_MC=4,
	MANCAL=5,
	VCOON=6,
	REGON=7,
	STARTCAL=8,
	BWBOOST=9,
	FS_LOCK=10,
	IFADCON=11,
	ENDCAL=12,
	RX=13,
	RX_END=14,
	RX_RST=15,
	TXRX_SWITCH=16,
	RXFIFIO_OVERFLOW=17,
	FSTXON=18,
	TX=19,
	TX_END=20,
	RXTX_SWITCH=21,
	TXFIFIO_UNDERFLOW=22
}CC2500_STATES;


//CC2500 PKTCTRL0 Defines
#define	FIXED_PACKET_LENGTH		0x0
#define VARIABLE_PACKET_LENGTH	0x1
#define CRC_EN					(0x1<<2)

//CC2500 PKTCTRL1 Defines
#define ADR_CHECK_DISABLED		0x0
#define ADR_CHECK_ENABLED		0x1
#define APPEND_STATUS			(0x1<<2)
#define CRC_AUTO_FLUSH			(0x1<<3)

#define OK_TO_TRANSMIT ((GPIOD_PDIR & GDO0_PIN)) // Ensure that we are not currently recieving a packet
#define OK_TO_TRANSMIT2 ((GPIOD_PDIR & GDO2_PIN)==0) // Ensure that we are not currently recieving a packet

void handleRadioCore();

void Quick_Reset_Core();
//
// Packet Type Definitions (todo)
//
#define IO_CHANGE (0x01)


#endif /* _CC2500_H */
