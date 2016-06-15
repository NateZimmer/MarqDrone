/*
 * Compare.h
 *
 *  Created on: Feb 4, 2015
 *      Author: 5016zimmern
 */

#ifndef COMPARE_H_
#define COMPARE_H_

#include "../Drivers/ESC.h"

void CMP_Enable_Phase_A(bool ER);
void CMP_Enable_Phase_B(bool ER);
void CMP_Enable_Phase_C(bool ER);

typedef enum
{
	CMP_INPUT0=0,
	CMP_INPUT1=1,
	CMP_INPUT2=2,
	CMP_INPUT3=3,
	CMP_INPUT4=4,
	CMP_INPUT5=5,
	CMP_INPUT6=6,
	CMP_INPUT7=7
}CMP_INPUTS;



#endif /* COMPARE_H_ */
