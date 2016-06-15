/** ###################################################################
 **     Filename    : UART0_Init.c
 **     Processor   : MK22FN512LH12
 **     Abstract    :
 **          This file implements the UART0 module initialization
 **          according to the Peripheral Initialization settings, and
 **          defines interrupt service routines prototypes.
 **
 **     Contents    :
 **         Int   - void UART0_Init(void);
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
 * @file UART0_Init.c
 * @brief This file implements the UART0 module initialization according to the
 *        Peripheral Initialization settings, and defines interrupt service
 *        routines prototypes.
 */


/* MODULE UART0_Init. */

#include "UART0_Init.h"
#include "MK22F51212.h"
#include "Init_Config.h"

#ifdef __cplusplus
extern "C" {
#endif

void UART0_Init(void) {

  /* Register 'UART0_C2' initialization */
  #if UART0_C2_MASK_1
    #if UART0_C2_MASK_1 == 0xFF
  UART0_C2 = UART0_C2_VALUE_1;
    #elif UART0_C2_MASK_1 == UART0_C2_VALUE_1
  UART0_C2 |= UART0_C2_VALUE_1;
    #elif UART0_C2_VALUE_1 == 0
  UART0_C2 &= ~UART0_C2_MASK_1;
    #else
  UART0_C2 = (UART0_C2 & (~UART0_C2_MASK_1)) | UART0_C2_VALUE_1;
    #endif
  #elif defined(UART0_C2_VALUE_1)
  UART0_C2 = UART0_C2_VALUE_1;
  #endif

  /* Register 'UART0_BDH' initialization */
  #ifdef UART0_BDH_VALUE
  UART0_BDH = UART0_BDH_VALUE;
  #endif

  /* Register 'UART0_BDL' initialization */
  #ifdef UART0_BDL_VALUE
  UART0_BDL = UART0_BDL_VALUE;
  #endif

  /* Register 'UART0_C4' initialization */
  #ifdef UART0_C4_VALUE
  UART0_C4 = UART0_C4_VALUE;
  #endif

  /* Register 'UART0_MA1' initialization */
  #ifdef UART0_MA1_VALUE
  UART0_MA1 = UART0_MA1_VALUE;
  #endif

  /* Register 'UART0_MA2' initialization */
  #ifdef UART0_MA2_VALUE
  UART0_MA2 = UART0_MA2_VALUE;
  #endif

  /* Register 'UART0_C1' initialization */
  #ifdef UART0_C1_VALUE
  UART0_C1 = UART0_C1_VALUE;
  #endif

  /* Register 'UART0_S2' initialization */
  #ifdef UART0_S2_VALUE
  UART0_S2 = UART0_S2_VALUE;
  #endif

  /* Register 'UART0_MODEM' initialization */
  #ifdef UART0_MODEM_VALUE
  UART0_MODEM = UART0_MODEM_VALUE;
  #endif

  /* Register 'UART0_IR' initialization */
  #ifdef UART0_IR_VALUE
  UART0_IR = UART0_IR_VALUE;
  #endif

  /* Register 'UART0_TWFIFO' initialization */
  #ifdef UART0_TWFIFO_VALUE
  UART0_TWFIFO = UART0_TWFIFO_VALUE;
  #endif

  /* Register 'UART0_RWFIFO' initialization */
  #ifdef UART0_RWFIFO_VALUE
  UART0_RWFIFO = UART0_RWFIFO_VALUE;
  #endif

  /* Register 'UART0_SFIFO' initialization */
  #ifdef UART0_SFIFO_VALUE
  UART0_SFIFO = UART0_SFIFO_VALUE;
  #endif

  /* Register 'UART0_CFIFO' initialization */
  #if UART0_CFIFO_MASK
    #if UART0_CFIFO_MASK == 0xFF
  UART0_CFIFO = UART0_CFIFO_VALUE;
    #elif UART0_CFIFO_MASK == UART0_CFIFO_VALUE
  UART0_CFIFO |= UART0_CFIFO_VALUE;
    #elif UART0_CFIFO_VALUE == 0
  UART0_CFIFO &= ~UART0_CFIFO_MASK;
    #else
  UART0_CFIFO = (UART0_CFIFO & (~UART0_CFIFO_MASK)) | UART0_CFIFO_VALUE;
    #endif
  #elif defined(UART0_CFIFO_VALUE)
  UART0_CFIFO = UART0_CFIFO_VALUE;
  #endif

  /* Register 'UART0_PFIFO' initialization */
  #if UART0_PFIFO_MASK
    #if UART0_PFIFO_MASK == 0xFF
  UART0_PFIFO = UART0_PFIFO_VALUE;
    #elif UART0_PFIFO_MASK == UART0_PFIFO_VALUE
  UART0_PFIFO |= UART0_PFIFO_VALUE;
    #elif UART0_PFIFO_VALUE == 0
  UART0_PFIFO &= ~UART0_PFIFO_MASK;
    #else
  UART0_PFIFO = (UART0_PFIFO & (~UART0_PFIFO_MASK)) | UART0_PFIFO_VALUE;
    #endif
  #elif defined(UART0_PFIFO_VALUE)
  UART0_PFIFO = UART0_PFIFO_VALUE;
  #endif

  /* Register 'UART0_TL7816' initialization */
  #ifdef UART0_TL7816_VALUE
  UART0_TL7816 = UART0_TL7816_VALUE;
  #endif

  /* Register 'UART0_ET7816' initialization */
  #ifdef UART0_ET7816_VALUE
  UART0_ET7816 = UART0_ET7816_VALUE;
  #endif

  /* Register 'UART0_WF7816' initialization */
  #ifdef UART0_WF7816_VALUE
  UART0_WF7816 = UART0_WF7816_VALUE;
  #endif

  /* Register 'UART0_WN7816' initialization */
  #ifdef UART0_WN7816_VALUE
  UART0_WN7816 = UART0_WN7816_VALUE;
  #endif

  /* Register 'UART0_AP7816B_T0' initialization */
  #ifdef UART0_AP7816B_T0_VALUE
  UART0_AP7816B_T0 = UART0_AP7816B_T0_VALUE;
  #endif

  /* Register 'UART0_AP7816A_T0' initialization */
  #ifdef UART0_AP7816A_T0_VALUE
  UART0_AP7816A_T0 = UART0_AP7816A_T0_VALUE;
  #endif

  /* Register 'UART0_WP7816' initialization */
  #ifdef UART0_WP7816_VALUE
  UART0_WP7816 = UART0_WP7816_VALUE;
  #endif

  /* Register 'UART0_WP7816B_T0' initialization */
  #ifdef UART0_WP7816B_T0_VALUE
  UART0_WP7816B_T0 = UART0_WP7816B_T0_VALUE;
  #endif

  /* Register 'UART0_WP7816A_T0' initialization */
  #ifdef UART0_WP7816A_T0_VALUE
  UART0_WP7816A_T0 = UART0_WP7816A_T0_VALUE;
  #endif

  /* Register 'UART0_WGP7816_T1' initialization */
  #ifdef UART0_WGP7816_T1_VALUE
  UART0_WGP7816_T1 = UART0_WGP7816_T1_VALUE;
  #endif

  /* Register 'UART0_WP7816C_T1' initialization */
  #if UART0_WP7816C_T1_MASK
    #if UART0_WP7816C_T1_MASK == 0xFF
  UART0_WP7816C_T1 = UART0_WP7816C_T1_VALUE;
    #elif UART0_WP7816C_T1_MASK == UART0_WP7816C_T1_VALUE
  UART0_WP7816C_T1 |= UART0_WP7816C_T1_VALUE;
    #elif UART0_WP7816C_T1_VALUE == 0
  UART0_WP7816C_T1 &= ~UART0_WP7816C_T1_MASK;
    #else
  UART0_WP7816C_T1 = (UART0_WP7816C_T1 & (~UART0_WP7816C_T1_MASK)) | UART0_WP7816C_T1_VALUE;
    #endif
  #elif defined(UART0_WP7816C_T1_VALUE)
  UART0_WP7816C_T1 = UART0_WP7816C_T1_VALUE;
  #endif

  /* Register 'UART0_WP7816B_T1' initialization */
  #ifdef UART0_WP7816B_T1_VALUE
  UART0_WP7816B_T1 = UART0_WP7816B_T1_VALUE;
  #endif

  /* Register 'UART0_WP7816A_T1' initialization */
  #ifdef UART0_WP7816A_T1_VALUE
  UART0_WP7816A_T1 = UART0_WP7816A_T1_VALUE;
  #endif

  /* Register 'UART0_IS7816' initialization */
  #ifdef UART0_IS7816_VALUE
  UART0_IS7816 = UART0_IS7816_VALUE;
  #endif

  /* Register 'UART0_IE7816' initialization */
  #ifdef UART0_IE7816_VALUE
  UART0_IE7816 = UART0_IE7816_VALUE;
  #endif

  /* Register 'UART0_C7816' initialization */
  #if UART0_C7816_MASK
    #if UART0_C7816_MASK == 0xFF
  UART0_C7816 = UART0_C7816_VALUE;
    #elif UART0_C7816_MASK == UART0_C7816_VALUE
  UART0_C7816 |= UART0_C7816_VALUE;
    #elif UART0_C7816_VALUE == 0
  UART0_C7816 &= ~UART0_C7816_MASK;
    #else
  UART0_C7816 = (UART0_C7816 & (~UART0_C7816_MASK)) | UART0_C7816_VALUE;
    #endif
  #elif defined(UART0_C7816_VALUE)
  UART0_C7816 = UART0_C7816_VALUE;
  #endif

  /* Clear flags */
  #ifdef UART0_CLEAR_FLAGS
  (void)UART0_S1;
  (void)UART0_D;
  #endif

  /* Register 'UART0_C5' initialization */
  #if UART0_C5_MASK
    #if UART0_C5_MASK == 0xFF
  UART0_C5 = UART0_C5_VALUE;
    #elif UART0_C5_MASK == UART0_C5_VALUE
  UART0_C5 |= UART0_C5_VALUE;
    #elif UART0_C5_VALUE == 0
  UART0_C5 &= ~UART0_C5_MASK;
    #else
  UART0_C5 = (UART0_C5 & (~UART0_C5_MASK)) | UART0_C5_VALUE;
    #endif
  #elif defined(UART0_C5_VALUE)
  UART0_C5 = UART0_C5_VALUE;
  #endif

  /* Register 'UART0_C3' initialization */
  #ifdef UART0_C3_VALUE
  UART0_C3 = UART0_C3_VALUE;
  #endif

  /* Register 'UART0_C2' initialization */
  #ifdef UART0_C2_VALUE_2
  UART0_C2 = UART0_C2_VALUE_2;
  #endif
}

#ifdef __cplusplus
}
#endif

/* END UART0_Init. */

/** ###################################################################
 **
 **     This file is a part of Processor Expert static initialization
 **     library for Freescale microcontrollers.
 **
 ** ################################################################### */
