/*
 * MKL25Z.c
 *
 *  Created on: Oct 27, 2015
 *      Author: Alvaro Prieto
 *   Ported By: Kellen Carey
 */

#include "cc2500.h"
#include "cc.h"
#include "string.h"
#include "../Drivers/SPI.h"
#include "PTD.h"
#include "PORT_PDD.h"
#include "WAIT1.h"
#include "../Drivers/USB_Echo.h"
#include <stdio.h>
#include <stdint.h>

// Define positions in buffer for various fields
#define LENGTH_FIELD  (0)
#define ADDRESS_FIELD (1)
#define DATA_FIELD    (2)


static uint8_t dummy_callback( uint8_t*, uint8_t );


// Receive buffer
static uint8_t p_rx_buffer[CC2500_BUFFER_LENGTH];
static uint8_t p_tx_buffer[CC2500_BUFFER_LENGTH];

bool RF_Keep_Alive=false;


uint8_t writeRFSettings(void);

uint8_t setup_cc2500(void) {

	uint8_t returnValue=0;
	uint8_t initial_power = 0xFB;				// 0 dBm
	// Set-up rx_callback function

	do
	{
		// Changed
		//spi_init();                         // Initialize SPI port

		// FIXME Add uscib0 files
		cc_powerup_reset();               // Reset CCxxxx

		// TODO implement this
		wait_cycles(500);  // Wait for device to reset (Not sure why this is needed)

		if(writeRFSettings())                        // Write RF settings to config reg
		{
			returnValue = 1; // Failed
			break;
		}

		// FIXME Add uscib0 files
		cc_write_burst_reg( TI_CCxxx0_PATABLE, &initial_power, 1);//Write PATABLE

		// FIXME Add uscib0 files
		WAIT1_Waitms(10);
		cc_strobe(TI_CCxxx0_SFRX);      // Flush RXFIFO
		WAIT1_Waitms(10);
		cc_strobe(TI_CCxxx0_SFTX);      // Flush RXFIFO
		WAIT1_Waitms(10);
		cc_strobe(TI_CCxxx0_SRX);           // Initialize CCxxxx in RX mode.
		WAIT1_Waitms(10);


		returnValue = cc_read_status(TI_CCxxx0_MARCSTATE);
		returnValue =0;



		// When a pkt is received, it will
		// signal on GDO0 and wake CPU

		// FIXME
		// Configure GDO0 port
	//	GDO0_PxIES |= GDO0_PIN;       // Int on falling edge (end of pkt)
	//	GDO0_PxIFG &= ~GDO0_PIN;      // Clear flag
	//	GDO0_PxIE |= GDO0_PIN;        // Enable int on end of packet

	}while(0);

	return returnValue;
}

/*******************************************************************************
 * @fn     cc2500_tx( uint8_t* p_buffer, uint8_t length )
 * @brief  Send raw message through radio
 * ****************************************************************************/
void cc2500_tx( uint8_t* p_buffer, uint8_t length )
{
  volatile int i;
  //  GDO0_PxIE &= ~GDO0_PIN;
  // Disable interrupt

  if(OK_TO_TRANSMIT2)
  {
	 // PORT_PDD_SetPinInterruptConfiguration(PTD_PORT_DEVICE, GDO0_PIN, PORT_PDD_INTERRUPT_DMA_DISABLED);
	  cc_write_burst_reg(TI_CCxxx0_TXFIFO, p_buffer, length); // Write TX data
	  cc_strobe(TI_CCxxx0_STX);           // Change state to TX, initiating
	                                            // data transfer

	// sometimes the chip hangs on while(!(GDO0_PxIN&GDO0_PIN)); line, see http://alvarop.com/2011/12/cc2500-project-part-1/#comment-467755523
	  //for (i=0;i<100000 && !(GDO0_PxIN & GDO0_PIN);i++); // Wait GDO0 to go hi or timeout -> sync TX'ed
	  //for (i=0;i<100000 && (GDO0_PxIN & GDO0_PIN);i++);  // Wait GDO0 to clear or timeout -> end of pkt
	//no used anymore
	//  while (!(GDO0_PxIN&GDO0_PIN));
	                                            // Wait GDO0 to go hi -> sync TX'ed
	//  while (GDO0_PxIN & GDO0_PIN);
	                                            // Wait GDO0 to clear -> end of pkt
	//  GDO0_PxIFG &= ~GDO0_PIN;      // After pkt TX, this flag is set.
	//                                            // Has to be cleared before existing
	//
	//  GDO0_PxIFG &= ~GDO0_PIN;

	  // Clear flag
	//PORT_PDD_ClearInterruptFlags(PTD_PORT_DEVICE, GDO0_PIN);
	//PORT_PDD_SetPinInterruptConfiguration(PTD_PORT_DEVICE, GDO0_PIN, PORT_PDD_INTERRUPT_ON_FALLING);
  }

//  GDO0_PxIE |= GDO0_PIN;            // Enable interrupt
}

/*******************************************************************************
 * @fn     void cc2500_tx_packet( uint8_t* p_buffer, uint8_t length,
 *                                                        uint8_t destination )
 * @brief  Send packet through radio. Takes care of adding length and
 *         destination to packet.
 * ****************************************************************************/
void cc2500_tx_packet( uint8_t* p_buffer, uint8_t length, uint8_t destination )
{
  // Add one to packet length account for address byte
  p_tx_buffer[LENGTH_FIELD] = length + 1;

  // Insert destination address to buffer
  p_tx_buffer[ADDRESS_FIELD] = destination;

  // Copy message buffer into tx buffer. Add one to account for length byte
  memcpy( &p_tx_buffer[DATA_FIELD], p_buffer, length );

  // Add DATA_FIELD to account for packet length and address bytes
  cc2500_tx( p_tx_buffer, (length + DATA_FIELD) );
}

/*******************************************************************************
 * @fn     cc2500_set_address( uint8_t );
 * @brief  Set device address
 * ****************************************************************************/
void cc2500_set_address( uint8_t address )
{
  cc_write_reg( TI_CCxxx0_ADDR, address );
}

/*******************************************************************************
 * @fn     cc2500_set_channel( uint8_t );
 * @brief  Set device channel
 * ****************************************************************************/
void cc2500_set_channel( uint8_t channel )
{
  cc_write_reg( TI_CCxxx0_CHANNR, channel );
}

/*******************************************************************************
 * @fn     cc2500_set_power( uint8_t );
 * @brief  Set device transmit power
 * ****************************************************************************/
void cc2500_set_power( uint8_t power )
{
  // Set TX power
  cc_write_burst_reg(TI_CCxxx0_PATABLE, &power, 1 );
}

/*******************************************************************************
 * @fn     cc2500_enable_addressing( );
 * @brief  Enable address checking with 0x00 as a broadcast address
 * ****************************************************************************/
void cc2500_enable_addressing()
{
  uint8_t tmp_reg;

  tmp_reg = ( cc_read_reg( TI_CCxxx0_PKTCTRL1  ) & ~0x03 ) | 0x02;

  cc_write_reg( TI_CCxxx0_PKTCTRL1, tmp_reg );
}

/*******************************************************************************
 * @fn     cc2500_disable_addressing( );
 * @brief  Disable address checking
 * ****************************************************************************/
void cc2500_disable_addressing()
{
  uint8_t tmp_reg;

  tmp_reg = ( cc_read_reg( TI_CCxxx0_PKTCTRL1  ) & ~0x03 );

  cc_write_reg( TI_CCxxx0_PKTCTRL1, tmp_reg );
}

/*******************************************************************************
 * @fn     cc2500_sleep( );
 * @brief  Set device to low power sleep mode
 * ****************************************************************************/
void cc2500_sleep( )
{
  // Set device to idle
  cc_strobe(TI_CCxxx0_SIDLE);

  // Set device to power-down (sleep) mode
  cc_strobe(TI_CCxxx0_SPWD);
}

/*******************************************************************************
 * @fn     void dummy_callback( void )
 * @brief  empty function works as default callback
 * ****************************************************************************/
static uint8_t dummy_callback( uint8_t* buffer, uint8_t length )
{
//  __no_operation();

  return 0;
}

/*******************************************************************************
 * @fn     uint8_t receive_packet( uint8_t* p_buffer, uint8_t* length )
 * @brief  Receive packet from the radio using CC2500
 * ****************************************************************************/
uint8_t receive_packet( uint8_t* p_buffer, uint8_t* length )
{
  uint8_t status[2];
  uint8_t packet_length;
  volatile uint8_t Testo = 0;

  uint8_t ReadStatusValue =0;
  ReadStatusValue = cc_read_status( TI_CCxxx0_RXBYTES );

  // Make sure there are bytes to be read in the FIFO buffer
  if (ReadStatusValue  )
  {
    // Read the first byte which contains the packet length
    packet_length = cc_read_reg( TI_CCxxx0_RXFIFO );

    // Make sure the packet length is smaller than our buffer
    if ( packet_length <= *length )
    {
      // Read the rest of the packet
      cc_read_burst_reg( TI_CCxxx0_RXFIFO, p_buffer, packet_length );

      // Return packet size in length variable
      *length = packet_length;

      // Read two byte status
      cc_read_burst_reg( TI_CCxxx0_RXFIFO, status, 2 );

      // Append status bytes to buffer
      memcpy( &p_buffer[packet_length], status, 2 );

      // Return 1 when CRC matches, 0 otherwise
      return ( status[TI_CCxxx0_LQI_RX] & TI_CCxxx0_CRC_OK );
    }
    else
    {
      // If the packet is larger than the buffer, flush the RX FIFO
      *length = packet_length;

      // Flush RX FIFO
      cc_strobe(TI_CCxxx0_SFRX);      // Flush RXFIFO

      return 0;
    }

  }

  return 0;
}

uint8_t receive_packet_fixed_length( uint8_t* p_buffer, uint8_t length,bool Append_CRC)
{
  uint8_t status[2];
  uint8_t packet_length=0;
  volatile uint8_t ReadStatusValue =0;
  cc_read_burst_reg( TI_CCxxx0_RXFIFO, p_buffer, length );
  if(Append_CRC)
  {
  // Read two byte status
	  cc_read_burst_reg( TI_CCxxx0_RXFIFO, status, 2 );
	  memcpy( &p_buffer[packet_length], status, 2 );
	  return ( status[TI_CCxxx0_LQI_RX] & TI_CCxxx0_CRC_OK );
  }
  return 0;
}


typedef enum
{
	RX_FIFO_THR_TRIGGER=0,
	RX_FIFIO_THR_TRIGGERED_OR_END_OF_PACKET=1,
	TX_FIFO_THR_TRIGGERED=2,
	TX_FIFIO_THR_TRIGGERED_OR_END_OF_PACKET=3,
	RX_FIFO_OVERFLOW=4,
	TX_FIFIO_UNDERFLOW=5,
}GDO_VALUES;


#define WRITE_GDO2_SETTING 0x6

uint8_t writeRFSettings(void)
{
	uint8_t temp = 0;
	uint8_t returnValue = 0;
	// FIXME Add uscib0 files
	// Write register settings
	do{
		  //cc_write_reg(TI_CCxxx0_IOCFG2,  0x30);  // GDO2 output pin config.
		cc_write_reg(TI_CCxxx0_IOCFG2,WRITE_GDO2_SETTING);  // GDO2 output pin config.

		  temp = cc_read_reg(TI_CCxxx0_IOCFG2);

		  if(temp != WRITE_GDO2_SETTING)
		  {
			  while(1);
			  returnValue = 1;
			  break;
		  }

		  //cc_write_reg(TI_CCxxx0_IOCFG0,   0x06);  // GDO0 output pin config.
		  cc_write_reg(TI_CCxxx0_IOCFG0,   0x01);  // GDO0 output pin config.
		  //cc_write_reg(TI_CCxxx0_IOCFG0,   0x01);  // GDO0 output pin config.
		  //cc_write_reg(TI_CCxxx0_PKTLEN,   0x3D);  // Packet length.
		  cc_write_reg(TI_CCxxx0_PKTLEN,   0x7);  // Packet length.

		  //cc_write_reg(TI_CCxxx0_PKTCTRL1, 0x4);  // Packet automation control. // Was 0xE
		  cc_write_reg(TI_CCxxx0_PKTCTRL1, CRC_AUTO_FLUSH);  // Packet automation control. // Was 0xE
		  temp = cc_read_reg(TI_CCxxx0_PKTCTRL1);
		  //cc_write_reg(TI_CCxxx0_PKTCTRL0, 0x05);  // Packet automation control.
		  cc_write_reg(TI_CCxxx0_PKTCTRL0, CRC_EN);  // Packet automation control.
		  temp = cc_read_reg(TI_CCxxx0_PKTCTRL0);

		  cc_write_reg(TI_CCxxx0_ADDR,     0x00);  // Device address.
		  cc_write_reg(TI_CCxxx0_CHANNR,   0x00); // Channel number.
		  cc_write_reg(TI_CCxxx0_FSCTRL1,  0x07); // Freq synthesizer control.
		  temp = cc_read_reg(TI_CCxxx0_FSCTRL1);

		  if(temp != 0x7)
		  {
			  while(1);
			  returnValue = 1;
			  break;
		  }

		  cc_write_reg(TI_CCxxx0_FSCTRL0,  0x00); // Freq synthesizer control.
		  cc_write_reg(TI_CCxxx0_FREQ2,    0x5D); // Freq control word, high byte
		  cc_write_reg(TI_CCxxx0_FREQ1,    0x93); // Freq control word, mid byte.
		  cc_write_reg(TI_CCxxx0_FREQ0,    0xB1); // Freq control word, low byte.
		  cc_write_reg(TI_CCxxx0_MDMCFG4,  0x2D); // Modem configuration. ////WAS 2D, determines data rate
		  cc_write_reg(TI_CCxxx0_MDMCFG3,  0x3B); // Modem configuration.
		  cc_write_reg(TI_CCxxx0_MDMCFG2,  0x73); // Modem configuration. // MSK(0x7), 32 bytes of SYNC (0x3) :0x73
		  cc_write_reg(TI_CCxxx0_MDMCFG1,  0x22); // Modem configuration. //
		  cc_write_reg(TI_CCxxx0_MDMCFG0,  0xF8); // Modem configuration.
		  cc_write_reg(TI_CCxxx0_DEVIATN,  0x00); // Modem dev (when FSK mod en)
		  cc_write_reg(TI_CCxxx0_MCSM1 ,   0x2F); //MainRadio Cntrl State Machine
		  cc_write_reg(TI_CCxxx0_MCSM0 ,   0x18); //MainRadio Cntrl State Machine
		  cc_write_reg(TI_CCxxx0_FOCCFG,   0x1D); // Freq Offset Compens. Config
		  cc_write_reg(TI_CCxxx0_BSCFG,    0x1C); //  Bit synchronization config.
		  cc_write_reg(TI_CCxxx0_AGCCTRL2, 0xC7); // AGC control.
		  cc_write_reg(TI_CCxxx0_AGCCTRL1, 0x00); // AGC control.
		  cc_write_reg(TI_CCxxx0_AGCCTRL0, 0xB2); // AGC control.
		  cc_write_reg(TI_CCxxx0_FREND1,   0xB6); // Front end RX configuration.
		  cc_write_reg(TI_CCxxx0_FREND0,   0x10); // Front end RX configuration.
		  cc_write_reg(TI_CCxxx0_FSCAL3,   0xEA); // Frequency synthesizer cal.
		  cc_write_reg(TI_CCxxx0_FSCAL2,   0x0A); // Frequency synthesizer cal.
		  cc_write_reg(TI_CCxxx0_FSCAL1,   0x00); // Frequency synthesizer cal.
		  cc_write_reg(TI_CCxxx0_FSCAL0,   0x11); // Frequency synthesizer cal. //// NOTE UPDATE FOR updated bit rate
		  cc_write_reg(TI_CCxxx0_FSTEST,   0x59); // Frequency synthesizer cal.
		  cc_write_reg(TI_CCxxx0_TEST2,    0x88); // Various test settings.
		  cc_write_reg(TI_CCxxx0_TEST1,    0x31); // Various test settings.
		  cc_write_reg(TI_CCxxx0_TEST0,    0x0B);  // Various test settings.
	}while(0);

	return returnValue;
}

char buff[20];

void handleRadioCore()
{
	 CC2500_STATES CC2500_State=0;
	 uint16_t numBytes = 0;
	 CC2500_State = cc_read_status(TI_CCxxx0_MARCSTATE);

	 //numBytes =cc_read_status(TI_CCxxx0_NUM_RXBYTES);

	 //if(RF_Keep_Alive)
	 if(1)
	 {
		 switch(CC2500_State)
		  {
			case TXFIFIO_UNDERFLOW:
			  cc_strobe(TI_CCxxx0_SFTX);      // Flush TXFIFO
			  debug_console("!!!TX Buffer Overflow!!!\r\n");
			  break;
			case RXFIFIO_OVERFLOW:
				//cc_strobe(TI_CCxxx0_SFRX);      // Flush RXFIFO
				cc_strobe(TI_CCxxx0_SIDLE);
				WAIT1_WaitCycles(100);
				cc_strobe(TI_CCxxx0_SFRX);      // Flush RXFIFO
				WAIT1_WaitCycles(100);
				cc_strobe(TI_CCxxx0_SFTX);      // Flush RXFIFO
				WAIT1_WaitCycles(100);
				cc_strobe(TI_CCxxx0_SRX);           // Initialize CCxxxx in RX mode.
				WAIT1_WaitCycles(100);
				debug_console("RF Core failure, restarting\r\n");
				debug_console("!!!RX Buffer Overflow!!!\r\n");
				break;

			default:
				break;
		  }
	 }
	 if(0)
	 {
			cc_strobe(TI_CCxxx0_SIDLE);
			WAIT1_WaitCycles(100);
			cc_strobe(TI_CCxxx0_SFRX);      // Flush RXFIFO
			WAIT1_WaitCycles(100);
			cc_strobe(TI_CCxxx0_SFTX);      // Flush RXFIFO
			WAIT1_WaitCycles(100);
			cc_strobe(TI_CCxxx0_SRX);           // Initialize CCxxxx in RX mode.
			WAIT1_WaitCycles(100);
			debug_console("RF Core failure, restarting\r\n");
	 }
}

void Quick_Reset_Core()
{
	cc_strobe(TI_CCxxx0_SIDLE);
	WAIT1_WaitCycles(100);
	cc_strobe(TI_CCxxx0_SFRX);      // Flush RXFIFO
	WAIT1_WaitCycles(100);
	cc_strobe(TI_CCxxx0_SFTX);      // Flush RXFIFO
	WAIT1_WaitCycles(100);
	cc_strobe(TI_CCxxx0_SRX);           // Initialize CCxxxx in RX mode.
}

