/*
 * SPI.c
 *
 *  Created on: Aug 13, 2014
 *      Author: Nate
 */

#include "SPI.h"
#include "MKL25Z4.h"
#include "SPI_PDD.h"
#include "SPI0.h"

void spi_init(void)  
{  
 SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;      //Turn on clock to D module  
 SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;       //Enable SPI0 clock  
  
  //PORTD_PCR0 = PORT_PCR_MUX(0x2);    //Set PTD0 to mux 2 [SPI0_PCS0]  
  PORTD_PCR1 = PORT_PCR_MUX(0x2);    //Set PTD1 to mux 2 [SPI0_SCK]  
  PORTD_PCR2 = PORT_PCR_MUX(0x2);    //Set PTD2 to mux 2 [SPI0_MOSI]  
  PORTD_PCR3 = PORT_PCR_MUX(0x2);    //Set PTD3 to mux 2 [SPIO_MISO]  
  
  SPI0_C1 = SPI_C1_MSTR_MASK; //| SPI_C1_SSOE_MASK;   //Set SPI0 to Master & SS pin to auto SS  
    
  //SPI0_C2 = SPI_C2_MODFEN_MASK;   //Master SS pin acts as slave select output   
    
  SPI0_BR = (SPI_BR_SPPR(0x01) | SPI_BR_SPR(0x02));     //Set baud rate prescale divisor to 3 & set baud rate divisor to 64 for baud rate of 15625 hz  
    
  SPI0_C1 |= SPI_C1_SPE_MASK;    //Enable SPI0  
  
}  
  
uint8_t spi_send_recv(uint8_t Input_Data)  
{  
  uint8_t  Recieved_Data = 0;
  while(!(SPI_S_SPTEF_MASK & SPI0_S))  
  {      
    __asm("nop");  //While buffer is not empty do nothing
  }  
//      SPI_PDD_WriteData8Bit(SPI0_DEVICE, Input_Data);

  SPI0_D = Input_Data;    //Write char to SPI
  while(!(SPI0_S & SPI_S_SPRF_MASK))
  {
      __asm("NOP");
  } // Wait for receive flag to set
//     Recieved_Data = SPI_PDD_ReadData8bit(SPI0_DEVICE);
  Recieved_Data = SPI0_D;
  return Recieved_Data;
}  
