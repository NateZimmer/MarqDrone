/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : FTM1.h
**     Project     : MarqDroneMK22FN
**     Processor   : MK22FN512VLH12
**     Component   : Init_FTM
**     Version     : Component 01.010, Driver 01.10, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-01-16, 17:34, # CodeGen: 3
**     Abstract    :
**          This file implements the FTM (FTM1) module initialization
**          according to the Peripheral Initialization settings, and
**          defines interrupt service routines prototypes.
**     Settings    :
**          Component name                                 : FTM1
**          Device                                         : FTM1
**          Settings                                       : 
**            Clock gate                                   : Enabled
**            Clock settings                               : 
**              Clock source                               : System clock
**              Prescaler                                  : divide by 2
**              Counter frequency                          : 30 MHz
**              Counter init                               : 0
**              Modulo counter                             : 1005
**              Period                                     : 33.533 us
**              Deadtime                                   : 
**                Deadtime prescaler                       : divide by 1
**                Deadtime value                           : 0
**                Deadtime delay                           : DISABLED
**              Num of timer overflows                     : 0
**            FTM mode                                     : Disabled
**            BDM mode                                     : FTM counter stopped; channels outputs functional
**            Global time base                             : Disabled
**            Global time base output                      : Disabled
**            Write protection                             : Disabled
**            Quadrature decoder                           : 
**              Quadrature decoder                         : Disabled
**              Quadrature decoder mode                    : Phase A / Phase B
**              Phase A input polarity                     : Normal
**              Phase B input polarity                     : Normal
**              Phase A input filter                       : Disabled
**              Phase B input filter                       : Disabled
**            Combined channels                            : 
**              Channels 0 and 1                           : 
**                Complementary mode                       : Disabled
**                Fault control                            : Disabled
**                Synchronization                          : Disabled
**                Deadtime                                 : Disabled
**                Inverting                                : Disabled
**            Synchronization                              : 
**              Synchronization mode                       : Disabled
**                Counter reinitialization                 : Disabled
**              HW trigger mode                            : Enabled
**              CNTIN synchronization                      : Disabled
**              INVCTRL synchronization                    : Disabled
**              SWOCTRL synchronization                    : Disabled
**              Software Trigger                           : Disabled
**              OUTMASK synchronization                    : Disabled
**              Minimum loading point                      : Disabled
**              Maximum loading point                      : Disabled
**            External triggers                            : 
**              Counter init trigger                       : Disabled
**              Channel 0 trigger                          : Disabled
**              Channel 1 trigger                          : Disabled
**            Fault control settings                       : 
**              Fault control mode                         : Disabled
**              Fault input filter value                   : Disabled
**              Fault input 0 filter                       : Disabled
**              Fault input 0 polarity                     : High
**              Fault input 1 filter                       : Disabled
**              Fault input 1 polarity                     : High
**          Channels                                       : 
**            Channel 0                                    : Enabled
**              Channel mode                               : Edge-aligned PWM
**                PWM polarity                             : High-true
**                Channel value register                   : 0
**              Input capture filter                       : Disabled
**              Software output control                    : Disabled
**              Pin                                        : Enabled
**                Pin                                      : PTA12/FTM1_CH0/I2S0_TXD0/FTM1_QD_PHA
**              Interrupt/DMA                              : 
**                Interrupt                                : INT_FTM1
**                Channel interrupt                        : Disabled
**                DMA request                              : Disabled
**            Channel 1                                    : Enabled
**              Channel mode                               : Edge-aligned PWM
**                PWM polarity                             : High-true
**                Channel value register                   : 0
**              Input capture filter                       : Disabled
**              Software output control                    : Disabled
**              Pin                                        : Enabled
**                Pin                                      : PTA13/LLWU_P4/FTM1_CH1/I2S0_TX_FS/FTM1_QD_PHB
**              Interrupt/DMA                              : 
**                Interrupt                                : INT_FTM1
**                Channel interrupt                        : Disabled
**                DMA request                              : Disabled
**          Pins                                           : 
**            Fault pins                                   : 
**              Fault pin 0                                : Disabled
**              Fault pin 1                                : Disabled
**            External clock pin                           : Disabled
**            Phase A Input pin                            : Disabled
**            Phase B Input pin                            : Disabled
**            HW Synchronization triggers                  : 
**              Hardware Trigger 0                         : Disabled
**              Hardware Trigger 1                         : Disabled
**              Hardware Trigger 2                         : Disabled
**          Interrupts                                     : 
**            Channels / Timer overflow / Fault            : 
**              Interrupt                                  : INT_FTM1
**              Interrupt request                          : Enabled
**              Interrupt priority                         : 16
**              ISR Name                                   : FT1
**              Channels interrupt/DMA                     : See the respective Channel settings
**              Timer overflow interrupt                   : Enabled
**              Fault interrupt                            : Disabled
**          Initialization                                 : 
**            Initialize the Channels Output               : yes
**            Load enable                                  : yes
**            Channel 0 load select                        : yes
**            Channel 1 load select                        : yes
**            Call Init method                             : yes
**            Utilize after reset values                   : default
**     Contents    :
**         Init - void FTM1_Init(void);
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file FTM1.h
** @version 01.10
** @brief
**          This file implements the FTM (FTM1) module initialization
**          according to the Peripheral Initialization settings, and
**          defines interrupt service routines prototypes.
*/         
/*!
**  @addtogroup FTM1_module FTM1 module documentation
**  @{
*/         

#ifndef FTM1_H_
#define FTM1_H_

/* MODULE FTM1. */

#include "FTM1_Init.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Initialization method user name */
#define FTM1_Init FTM1_Init
/* PDD macros peripheral base address parameter */
#define FTM1_DEVICE FTM1_BASE_PTR
/*
** ===================================================================
** The interrupt service routine must be implemented by user in one
** of the user modules (see FTM1.c file for more information).
** ===================================================================
*/
PE_ISR(FT1);

#ifdef __cplusplus
}
#endif

/* END FTM1. */
#endif /* #ifndef __FTM1_H_ */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

