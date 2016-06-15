/*
 * SPI.c
 *
 *  Created on: Nov 14, 2015
 *      Author: Z
 */

#include "SPI.h"
#include "../../Static_Code/PDD/SPI_PDD.h"
#include "GPIO.h"

void spi_init(void)
{

}


////////////////////////////////////////////////////////
// spi_send_recv_CC Writes/Recieves from the MPU9250
////////////////////////////////////////////////////////

uint8_t spi_send_recv(uint8_t Input_Data)
{
	uint8_t spiRecvData = 0;

#ifdef MK22FN
    SPI_PDD_WriteData8Bits(SPI0_BASE_PTR,Input_Data);
    while( (SPI0_SR & SPI_SR_RXCTR_MASK)==0);
    spiRecvData = SPI_PDD_ReadData8bits(SPI0_BASE_PTR);
#endif

#ifdef KL25Z

    while(!(SPI_S_SPTEF_MASK & SPI0_S))
    {
      __asm("nop");  //While buffer is not empty do nothing
    }

    SPI0_D = Input_Data;    //Write char to SPI
     while(!(SPI0_S & SPI_S_SPRF_MASK))
     {
         __asm("NOP");
     } // Wait for receive flag to set
   //     Recieved_Data = SPI_PDD_ReadData8bit(SPI0_DEVICE);
     spiRecvData = SPI0_D;
#endif

    return spiRecvData;
}
///////////////////END OF FUNCTION//////////////////////

////////////////////////////////////////////////////////
// spi_send_recv_CC Writes/Recieves from the CC2500
////////////////////////////////////////////////////////
uint8_t spi_send_recv_CC(uint8_t Input_Data)
{
	uint8_t returnValue = 0;

#ifdef MK22FN
    SPI_PDD_WriteData8Bits(SPI1_BASE_PTR,Input_Data);
    while( (SPI1_SR & SPI_SR_RXCTR_MASK)==0);
    returnValue = SPI_PDD_ReadData8bits(SPI1_BASE_PTR);
#endif
#ifdef KL25Z
    while(!(SPI_S_SPTEF_MASK & SPI1_S))
    {
      __asm("nop");  //While buffer is not empty do nothing
    }

    SPI1_D = Input_Data;    //Write char to SPI
     while(!(SPI1_S & SPI_S_SPRF_MASK))
     {
         __asm("NOP");
     } // Wait for receive flag to set
     returnValue = SPI1_D;
#endif

    return returnValue;
}
///////////////////END OF FUNCTION//////////////////////
