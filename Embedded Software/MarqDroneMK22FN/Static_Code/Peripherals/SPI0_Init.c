/** ###################################################################
 **     Filename    : SPI0_Init.c
 **     Processor   : MK22FN512LH12
 **     Abstract    :
 **          This file implements the SPI0 module initialization
 **          according to the Peripheral Initialization settings, and
 **          defines interrupt service routines prototypes.
 **
 **     Contents    :
 **         Int   - void SPI0_Init(void);
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
 * @file SPI0_Init.c
 * @brief This file implements the SPI0 module initialization according to the
 *        Peripheral Initialization settings, and defines interrupt service
 *        routines prototypes.
 */


/* MODULE SPI0_Init. */

#include "SPI0_Init.h"
#include "MK22F51212.h"
#include "Init_Config.h"

#ifdef __cplusplus
extern "C" {
#endif

void SPI0_Init(void) {

  SPI0_MCR = 0x1;

  /* Register 'SPI0_MCR' initialization */
  #if SPI0_MCR_MASK_1
    #if SPI0_MCR_MASK_1 == 0xFFFFFFFF
  SPI0_MCR = SPI0_MCR_VALUE_1;
    #elif SPI0_MCR_MASK_1 == SPI0_MCR_VALUE_1
  SPI0_MCR |= SPI0_MCR_VALUE_1;
    #elif SPI0_MCR_VALUE_1 == 0
  SPI0_MCR &= ~SPI0_MCR_MASK_1;
    #else
  SPI0_MCR = (SPI0_MCR & (~SPI0_MCR_MASK_1)) | SPI0_MCR_VALUE_1;
    #endif
  #elif defined(SPI0_MCR_VALUE_1)
  SPI0_MCR = SPI0_MCR_VALUE_1;
  #endif

  /* Register 'SPI0_TCR' initialization */
  #ifdef SPI0_TCR_VALUE
  SPI0_TCR = SPI0_TCR_VALUE;
  #endif

  /* Register 'SPI0_CTAR0' initialization */
  #ifdef SPI0_CTAR0_VALUE
  SPI0_CTAR0 = SPI0_CTAR0_VALUE;
  #endif

  /* Register 'SPI0_CTAR1' initialization */
  #ifdef SPI0_CTAR1_VALUE
  SPI0_CTAR1 = SPI0_CTAR1_VALUE;
  #endif

  /* Register 'SPI0_CTAR0_SLAVE' initialization */
  #if SPI0_CTAR0_SLAVE_MASK
    #if SPI0_CTAR0_SLAVE_MASK == 0xFFFFFFFF
  SPI0_CTAR0_SLAVE = SPI0_CTAR0_SLAVE_VALUE;
    #elif SPI0_CTAR0_SLAVE_MASK == SPI0_CTAR0_SLAVE_VALUE
  SPI0_CTAR0_SLAVE |= SPI0_CTAR0_SLAVE_VALUE;
    #elif SPI0_CTAR0_SLAVE_VALUE == 0
  SPI0_CTAR0_SLAVE &= ~SPI0_CTAR0_SLAVE_MASK;
    #else
  SPI0_CTAR0_SLAVE = (SPI0_CTAR0_SLAVE & (~SPI0_CTAR0_SLAVE_MASK)) | SPI0_CTAR0_SLAVE_VALUE;
    #endif
  #elif defined(SPI0_CTAR0_SLAVE_VALUE)
  SPI0_CTAR0_SLAVE = SPI0_CTAR0_SLAVE_VALUE;
  #endif

  /* Register 'SPI0_SR' initialization */
  #ifdef SPI0_SR_VALUE
  SPI0_SR = SPI0_SR_VALUE;
  #endif

  /* Register 'SPI0_RSER' initialization */
  #ifdef SPI0_RSER_VALUE
  SPI0_RSER = SPI0_RSER_VALUE;
  #endif

  /* Register 'SPI0_MCR' initialization */
  #if SPI0_MCR_MASK_2
    #if SPI0_MCR_MASK_2 == 0xFFFFFFFF
  SPI0_MCR = SPI0_MCR_VALUE_2;
    #elif SPI0_MCR_MASK_2 == SPI0_MCR_VALUE_2
  SPI0_MCR |= SPI0_MCR_VALUE_2;
    #elif SPI0_MCR_VALUE_2 == 0
  SPI0_MCR &= ~SPI0_MCR_MASK_2;
    #else
  SPI0_MCR = (SPI0_MCR & (~SPI0_MCR_MASK_2)) | SPI0_MCR_VALUE_2;
    #endif
  #elif defined(SPI0_MCR_VALUE_2)
  SPI0_MCR = SPI0_MCR_VALUE_2;
  #endif
}

#ifdef __cplusplus
}
#endif

/* END SPI0_Init. */

/** ###################################################################
 **
 **     This file is a part of Processor Expert static initialization
 **     library for Freescale microcontrollers.
 **
 ** ################################################################### */
