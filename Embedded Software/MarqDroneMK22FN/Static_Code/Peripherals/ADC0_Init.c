/** ###################################################################
 **     Filename    : ADC0_Init.c
 **     Processor   : MK22FN512LH12
 **     Abstract    :
 **          This file implements the ADC0 module initialization
 **          according to the Peripheral Initialization settings, and
 **          defines interrupt service routines prototypes.
 **
 **     Contents    :
 **         Int   - void ADC0_Init(void);
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
 * @file ADC0_Init.c
 * @brief This file implements the ADC0 module initialization according to the
 *        Peripheral Initialization settings, and defines interrupt service
 *        routines prototypes.
 */


/* MODULE ADC0_Init. */

#include "ADC0_Init.h"
#include "MK22F51212.h"
#include "Init_Config.h"

#ifdef __cplusplus
extern "C" {
#endif

void ADC0_Init(void) {

  /* Register 'ADC0_CFG1' initialization */
  #ifdef ADC0_CFG1_VALUE
  ADC0_CFG1 = ADC0_CFG1_VALUE;
  #endif

  /* Register 'ADC0_CFG2' initialization */
  #ifdef ADC0_CFG2_VALUE
  ADC0_CFG2 = ADC0_CFG2_VALUE;
  #endif

  /* Register 'ADC0_CV1' initialization */
  #ifdef ADC0_CV1_VALUE
  ADC0_CV1 = ADC0_CV1_VALUE;
  #endif

  /* Register 'ADC0_CV2' initialization */
  #ifdef ADC0_CV2_VALUE
  ADC0_CV2 = ADC0_CV2_VALUE;
  #endif

  /* Register 'ADC0_OFS' initialization */
  #ifdef ADC0_OFS_VALUE
  ADC0_OFS = ADC0_OFS_VALUE;
  #endif

  /* Register 'ADC0_SC2' initialization */
  #if ADC0_SC2_MASK
    #if ADC0_SC2_MASK == 0xFFFFFFFF
  ADC0_SC2 = ADC0_SC2_VALUE;
    #elif ADC0_SC2_MASK == ADC0_SC2_VALUE
  ADC0_SC2 |= ADC0_SC2_VALUE;
    #elif ADC0_SC2_VALUE == 0
  ADC0_SC2 &= ~ADC0_SC2_MASK;
    #else
  ADC0_SC2 = (ADC0_SC2 & (~ADC0_SC2_MASK)) | ADC0_SC2_VALUE;
    #endif
  #elif defined(ADC0_SC2_VALUE)
  ADC0_SC2 = ADC0_SC2_VALUE;
  #endif

  /* Register 'ADC0_SC3' initialization */
  #ifdef ADC0_SC3_VALUE
  ADC0_SC3 = ADC0_SC3_VALUE;
  #endif

  /* Register 'ADC0_SC1A' initialization */
  #ifdef ADC0_SC1A_VALUE
  ADC0_SC1A = ADC0_SC1A_VALUE;
  #endif

  /* Register 'ADC0_SC1B' initialization */
  #ifdef ADC0_SC1B_VALUE
  ADC0_SC1B = ADC0_SC1B_VALUE;
  #endif
}

#ifdef __cplusplus
}
#endif

/* END ADC0_Init. */

/** ###################################################################
 **
 **     This file is a part of Processor Expert static initialization
 **     library for Freescale microcontrollers.
 **
 ** ################################################################### */
