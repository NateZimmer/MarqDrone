/** @file uscib0.c
*
* @brief SPI and CCxxxx radio communication functions
*         This file uses the USCIB0 SPI peripheral
*
* @author Alvaro Prieto
*/
#include "cc.h"
#include "../Drivers/SPI.h"
#include "../Drivers/Remote.h"
#include "../Drivers/GPIO.h"
#include "WAIT1.h"
//#include "g2553.h"

#define SPI_INTERFACE_USCIB0
#if !defined(SPI_INTERFACE_USCIB0)
#error This SPI library was written for device with USCI B0
#endif

void wait_cycles(uint16_t cycles)
{
  while(cycles>15)                          // 15 cycles consumed by overhead
    cycles = cycles - 6;                    // 6 cycles consumed each iteration
}

/*******************************************************************************
 * @fn void spi_setup(void)
 * @brief Setup SPI with the appropriate settings for CCxxxx communication
 * ****************************************************************************/
void spi_setup(void)
{
	spi_init();
//  CSn_PxOUT |= CSn_PIN;
//  CSn_PxDIR |= CSn_PIN;         // /CS disable
//
//  UCB0CTL1 |= UCSWRST;                      // **Disable USCI state machine**
//  UCB0CTL0 |= UCMST+UCCKPL+UCMSB+UCSYNC;    // 3-pin, 8-bit SPI master
//  UCB0CTL1 |= UCSSEL_2;                     // SMCLK
//  UCB0BR0 = 0x10;                           // UCLK/2
//  UCB0BR1 = 0;
//  SPI_USCIB0_PxSEL  |= SPI_USCIB0_SIMO
//                          | SPI_USCIB0_SOMI
//                          | SPI_USCIB0_UCLK;
//#ifndef __MSP430F2274__
//  SPI_USCIB0_PxSEL2 |= SPI_USCIB0_SIMO
//                          | SPI_USCIB0_SOMI
//                          | SPI_USCIB0_UCLK;
//#else
//  // SPI option select
//  SPI_USCIB0_PxDIR |= (SPI_USCIB0_SIMO | SPI_USCIB0_UCLK);
//#endif
//                                            // SPI option select
//  //SPI_USCIB0_PxDIR |= SPI_USCIB0_SIMO | SPI_USCIB0_UCLK;
//                                            // SPI TXD out direction
//  UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

/*******************************************************************************
 * @fn void cc_write_reg(uint8_t addr, uint8_t value)
 * @brief Write single register value to CCxxxx
 * ****************************************************************************/
void cc_write_reg(uint8_t addr, uint8_t value)
{
	// CS Enable
	Set_Pin(&(CC_CS_PIN), 0);

	// Send address
	spi_send_recv(addr);

	// Send value
	spi_send_recv(value);

	// CS Disable
	Set_Pin(&(CC_CS_PIN), 1);

//  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
//		  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
//		  UCB0TXBUF = addr;                         // Send address
//		  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
//		  UCB0TXBUF = value;                        // Send data
//		  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
//  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

/*******************************************************************************
 * @fn cc_write_burst_reg(uint8_t addr, uint8_t *buffer, uint8_t count)
 * @brief Write multiple values to CCxxxx
 * ****************************************************************************/
void cc_write_burst_reg(uint8_t addr, uint8_t *buffer, uint8_t count)
{
  uint16_t i;

  // CS Enable
  Set_Pin(&(CC_CS_PIN), 0);

  // Send address
  spi_send_recv(addr | TI_CCxxx0_WRITE_BURST);

  // Send burst data
  for (i = 0; i < count; i++) {
	  // Send the data
	  spi_send_recv(buffer[i]);
  }

  // CS Disable
  Set_Pin(&(CC_CS_PIN), 1);
//  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
//  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
//  UCB0TXBUF = addr | TI_CCxxx0_WRITE_BURST; // Send address
//  for (i = 0; i < count; i++)
//  {
//    while (!(IFG2&UCB0TXIFG));              // Wait for TXBUF ready
//    UCB0TXBUF = buffer[i];                  // Send data
//  }
//  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
//  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

/*******************************************************************************
 * @fn uint8_t cc_read_reg(uint8_t addr)
 * @brief read single register from CCxxxx
 * ****************************************************************************/
uint8_t cc_read_reg(uint8_t addr)
{
  uint8_t x;

  // CS Enable
  Set_Pin(&(CC_CS_PIN), 0);

  // Write the address
  spi_send_recv(addr | TI_CCxxx0_READ_SINGLE);

  // Dummy write in order to receive data
  x = spi_send_recv((uint8_t)0);

  // CS Disable
  Set_Pin(&(CC_CS_PIN), 1);

  // Return read value
  return (x);

//  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
//  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
//  UCB0TXBUF = (addr | TI_CCxxx0_READ_SINGLE);// Send address
//  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
//  UCB0TXBUF = 0;                            // Dummy write so we can read data
//  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
//  CSn_PxOUT |= CSn_PIN;         // /CS disable
//  x = UCB0RXBUF;                            // Read data
//
//  return x;
}

/*******************************************************************************
 * @fn cc_read_burst_reg(uint8_t addr, uint8_t *buffer, uint8_t count)
 * @brief read multiple registers from CCxxxx
 * ****************************************************************************/
void cc_read_burst_reg(uint8_t addr, uint8_t *buffer, uint8_t count)
{
  uint8_t i;

  // CS Enable
  Set_Pin(&(CC_CS_PIN), 0);

  // Send address
  spi_send_recv(addr | TI_CCxxx0_READ_BURST);

  // Receive burst data
  for (i = 0; i < count; i++) {
	  //Dummy write in order to receive incoming data
	  buffer[i] = spi_send_recv((uint8_t)0);
  }

  // CS Disable
  Set_Pin(&(CC_CS_PIN), 1);

//  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
//  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
//  UCB0TXBUF = (addr | TI_CCxxx0_READ_BURST);// Send address
//  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
//  UCB0TXBUF = 0;                            // Dummy write to read 1st data byte
//  // Addr byte is now being TX'ed, with dummy byte to follow immediately after
  //IFG2 &= ~UCB0RXIFG;                       // Clear flag
//  while (!(IFG2&UCB0RXIFG));                // Wait for end of 1st data byte TX
//  // First data byte now in RXBUF
//  for (i = 0; i < (count-1); i++)
//  {
//    UCB0TXBUF = 0;                          //Initiate next data RX, meanwhile..
//    buffer[i] = UCB0RXBUF;                  // Store data from last data RX
//    while (!(IFG2&UCB0RXIFG));              // Wait for RX to finish
//  }
//  buffer[count-1] = UCB0RXBUF;              // Store last RX byte in buffer
//  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

/*******************************************************************************
 * @fn uint8_t cc_read_status(uint8_t addr)
 * @brief send status command and read returned status byte
 * ****************************************************************************/

/*
uint8_t cc_read_status(uint8_t addr)
{
  uint8_t status;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = (addr | TI_CCxxx0_READ_BURST);// Send address
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = 0;                            // Dummy write so we can read data
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  status = UCB0RXBUF;                       // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return status;
}
*/

uint8_t cc_read_status(uint8_t addr)
{
  uint8_t status;
//  volatile Chip_Status = 0;

  // CS Enable
  Set_Pin(&(CC_CS_PIN), 0);
  // Send address
  status = spi_send_recv(addr | TI_CCxxx0_READ_BURST);

  // Dummy write in order to read status
  status = spi_send_recv((uint8_t)0);

  // CS Disable
  Set_Pin(&(CC_CS_PIN), 1);
  // Return the read status
  return (status);

//  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
//  while (!(IFG2 & UCB0TXIFG));                // Wait for TXBUF ready
//  UCB0TXBUF = (addr | TI_CCxxx0_READ_BURST);// Send address
//  while (!(IFG2 & UCB0TXIFG));                // Wait for TXBUF ready
//  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
//  Chip_Status = UCB0RXBUF;
//  UCB0TXBUF = 0;                            // Dummy write so we can read data
//  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
//  status = UCB0RXBUF;                       // Read data
//  CSn_PxOUT |= CSn_PIN;         // /CS disable
//
//  return status;
}

uint8_t cc_read_status_byte()
{
  uint8_t status = 0;
  volatile uint8_t dummy = 0;

  // CS Enable
  Set_Pin(&(CC_CS_PIN), 0);

  // Send the address
  // TODO Check this with NATE
  status = spi_send_recv(TI_CCxxx0_RSSI | TI_CCxxx0_READ_BURST);

  // Dummy write to read the data
  // TODO Check this with NATE
  dummy = spi_send_recv((uint8_t)0);
  if (dummy) {
	  dummy++;
  }

  // CS Disable
  Set_Pin(&(CC_CS_PIN), 1);

  // Return the status
  return (status);

//  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
//  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
//  UCB0TXBUF = (TI_CCxxx0_RSSI | TI_CCxxx0_READ_BURST);// Send address
//  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
//  status = UCB0RXBUF;                       // Read data
//  UCB0TXBUF = 0;                            // Dummy write so we can read data
//  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
//  dummy = UCB0RXBUF;                       // Read data
//  if(dummy)
//  {
//	  dummy++;
//  }
//
//  CSn_PxOUT |= CSn_PIN;         // /CS disable
//
//  return status;
}





/*******************************************************************************
 * @fn void cc_strobe (uint8_t strobe)
 * @brief send strobe command
 * ****************************************************************************/
void cc_strobe(uint8_t strobe)
{
	// CS Enable
	Set_Pin(&(CC_CS_PIN), 0);

	// Send strobe
	spi_send_recv(strobe);

	// CS Disable
	Set_Pin(&(CC_CS_PIN), 1);

//  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
//  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
//  UCB0TXBUF = strobe;                       // Send strobe
//  // Strobe addr is now being TX'ed
//  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
//  CSn_PxOUT |= CSn_PIN;         // /CS disable
}
/*******************************************************************************
 * @fn void cc_powerup_reset()
 * @brief reset radio
 * ****************************************************************************/
void cc_powerup_reset(void)
{
	// CS Disable
	Set_Pin(&(CC_CS_PIN), 1);
//  CSn_PxOUT |= CSn_PIN;
	wait_cycles(3000);
	// CS Enable
	Set_Pin(&(CC_CS_PIN), 0);
//	CSn_PxOUT &= ~CSn_PIN;
	wait_cycles(3000);
	// CS Disable
	Set_Pin(&(CC_CS_PIN), 1);
//	CSn_PxOUT |= CSn_PIN;
	wait_cycles(4500);

	// CS Enable
	Set_Pin(&(CC_CS_PIN), 0);

	// Send stobe
	spi_send_recv(TI_CCxxx0_SRES);

	// Small delay to wait for device to reset
	wait_cycles(4500);

	// CS Disable
	Set_Pin(&(CC_CS_PIN), 1);

//  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
//  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
//  UCB0TXBUF = TI_CCxxx0_SRES;               // Send strobe
//  // Strobe addr is now being TX'ed
//  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
//  while(SPI_USCIB0_PxIN & SPI_USCIB0_SOMI); // Wait until the device has reset
//  CSn_PxOUT |= CSn_PIN;         // /CS disable
}
