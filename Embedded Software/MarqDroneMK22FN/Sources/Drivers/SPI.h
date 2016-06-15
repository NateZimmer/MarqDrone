/*
 * SPI.h
 *
 *  Created on: Nov 14, 2015
 *      Author: Z
 */

#ifndef SOURCES_DRIVERS_SPI_H_
#define SOURCES_DRIVERS_SPI_H_

#include "FC.h"

uint8_t spi_send_recv(uint8_t Input_Data);
uint8_t spi_send_recv_CC(uint8_t Input_Data);

#endif /* SOURCES_DRIVERS_SPI_H_ */
