/*
 * Timer.h
 *
 *  Created on: Oct 26, 2015
 *      Author: Z
 */

#ifndef SOURCES_DRIVERS_TIMER_H_
#define SOURCES_DRIVERS_TIMER_H_

#include <stdint.h>

uint8_t Get_System_Tick();

extern uint32_t CPU_Tick;
extern uint32_t CPU_USAGE;

#endif /* SOURCES_DRIVERS_TIMER_H_ */
