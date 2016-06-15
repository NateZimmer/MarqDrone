/*
 * USB_Echo.h
 *
 *  Created on: Oct 26, 2015
 *      Author: Z
 */

#ifndef SOURCES_DRIVERS_USB_ECHO_H_
#define SOURCES_DRIVERS_USB_ECHO_H_

#include <stdbool.h>

extern bool USB_INIT;
extern bool USB_RDY;

void Handle_USB_Read(void);
void debug_console(char * textBuffer);

#endif /* SOURCES_DRIVERS_USB_ECHO_H_ */
