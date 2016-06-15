/*
 * SPI.h
 *
 *  Created on: Aug 13, 2014
 *      Author: Nate
 */

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

void spi_init(void);  
uint8_t spi_send_recv(uint8_t Input_Data) ;  

#endif /* SPI_H_ */
