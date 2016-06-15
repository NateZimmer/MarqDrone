/** ###################################################################
 **     Filename    : FTM3_Init.c
 **     Processor   : MK22FN512LH12
 **     Abstract    :
 **          This file implements the FTM3 module initialization
 **          according to the Peripheral Initialization settings, and
 **          defines interrupt service routines prototypes.
 **
 **     Contents    :
 **         Int   - void FTM3_Init(void);
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
 * @file FTM3_Init.c
 * @brief This file implements the FTM3 module initialization according to the
 *        Peripheral Initialization settings, and defines interrupt service
 *        routines prototypes.
 */


/* MODULE FTM3_Init. */

#include "FTM3_Init.h"
#include "MK22F51212.h"
#include "Init_Config.h"

#ifdef __cplusplus
extern "C" {
#endif

void FTM3_Init(void) {
  (void)FTM3_SC;  /* Dummy read of the Control Status register to clear the interrupt flag */
  FTM3_SC = 0;  /* Stop the counter */
  #ifdef FTM3_C0SC
  (void)FTM3_C0SC; /* Dummy read of the Channel Status and Control 0 register to clear the interrupt flag */
  #endif
  #ifdef FTM3_C1SC
  (void)FTM3_C1SC; /* Dummy read of the Channel Status and Control 1 register to clear the interrupt flag */
  #endif
  #ifdef FTM3_C2SC
  (void)FTM3_C2SC; /* Dummy read of the Channel Status and Control 2 register to clear the interrupt flag */
  #endif
  #ifdef FTM3_C3SC
  (void)FTM3_C3SC; /* Dummy read of the Channel Status and Control 3 register to clear the interrupt flag */
  #endif
  #ifdef FTM3_C4SC
  (void)FTM3_C4SC; /* Dummy read of the Channel Status and Control 4 register to clear the interrupt flag */
  #endif
  #ifdef FTM3_C5SC
  (void)FTM3_C5SC; /* Dummy read of the Channel Status and Control 5 register to clear the interrupt flag */
  #endif
  #ifdef FTM3_C6SC
  (void)FTM3_C6SC; /* Dummy read of the Channel Status and Control 6 register to clear the interrupt flag */
  #endif
  #ifdef FTM3_C7SC
  (void)FTM3_C7SC; /* Dummy read of the Channel Status and Control 7 register to clear the interrupt flag */
  #endif
  #ifdef FTM3_MODE_VALUE_1
  FTM3_MODE |= FTM3_MODE_VALUE_1; /* Disable write protection */
  #endif

  FTM3_C0SC = 0;

  FTM3_C1SC = 0;

  FTM3_C2SC = 0;

  FTM3_C3SC = 0;

  FTM3_C4SC = 0;

  FTM3_C5SC = 0;

  FTM3_C6SC = 0;

  FTM3_C7SC = 0;

  /* Register 'FTM3_SC' initialization */
  #if FTM3_SC_MASK_2
    #if FTM3_SC_MASK_2 == 0xFFFFFFFF
  FTM3_SC = FTM3_SC_VALUE_2;
    #elif FTM3_SC_MASK_2 == FTM3_SC_VALUE_2
  FTM3_SC |= FTM3_SC_VALUE_2;
    #elif FTM3_SC_VALUE_2 == 0
  FTM3_SC &= ~FTM3_SC_MASK_2;
    #else
  FTM3_SC = (FTM3_SC & (~FTM3_SC_MASK_2)) | FTM3_SC_VALUE_2;
    #endif
  #elif defined(FTM3_SC_VALUE_2)
  FTM3_SC = FTM3_SC_VALUE_2;
  #endif

  /* Register 'FTM3_MODE' initialization */
  #if FTM3_MODE_MASK_2
    #if FTM3_MODE_MASK_2 == 0xFFFFFFFF
  FTM3_MODE = FTM3_MODE_VALUE_2;
    #elif FTM3_MODE_MASK_2 == FTM3_MODE_VALUE_2
  FTM3_MODE |= FTM3_MODE_VALUE_2;
    #elif FTM3_MODE_VALUE_2 == 0
  FTM3_MODE &= ~FTM3_MODE_MASK_2;
    #else
  FTM3_MODE = (FTM3_MODE & (~FTM3_MODE_MASK_2)) | FTM3_MODE_VALUE_2;
    #endif
  #elif defined(FTM3_MODE_VALUE_2)
  FTM3_MODE = FTM3_MODE_VALUE_2;
  #endif

  /* Register 'FTM3_COMBINE' initialization */
  #if FTM3_COMBINE_MASK
    #if FTM3_COMBINE_MASK == 0xFFFFFFFF
  FTM3_COMBINE = FTM3_COMBINE_VALUE;
    #elif FTM3_COMBINE_MASK == FTM3_COMBINE_VALUE
  FTM3_COMBINE |= FTM3_COMBINE_VALUE;
    #elif FTM3_COMBINE_VALUE == 0
  FTM3_COMBINE &= ~FTM3_COMBINE_MASK;
    #else
  FTM3_COMBINE = (FTM3_COMBINE & (~FTM3_COMBINE_MASK)) | FTM3_COMBINE_VALUE;
    #endif
  #elif defined(FTM3_COMBINE_VALUE)
  FTM3_COMBINE = FTM3_COMBINE_VALUE;
  #endif

  /* Register 'FTM3_INVCTRL' initialization */
  #if FTM3_INVCTRL_MASK
    #if FTM3_INVCTRL_MASK == 0xFFFFFFFF
  FTM3_INVCTRL = FTM3_INVCTRL_VALUE;
    #elif FTM3_INVCTRL_MASK == FTM3_INVCTRL_VALUE
  FTM3_INVCTRL |= FTM3_INVCTRL_VALUE;
    #elif FTM3_INVCTRL_VALUE == 0
  FTM3_INVCTRL &= ~FTM3_INVCTRL_MASK;
    #else
  FTM3_INVCTRL = (FTM3_INVCTRL & (~FTM3_INVCTRL_MASK)) | FTM3_INVCTRL_VALUE;
    #endif
  #elif defined(FTM3_INVCTRL_VALUE)
  FTM3_INVCTRL = FTM3_INVCTRL_VALUE;
  #endif

  /* Register 'FTM3_C0SC' initialization */
  #if FTM3_C0SC_MASK
    #if FTM3_C0SC_MASK == 0xFFFFFFFF
  FTM3_C0SC = FTM3_C0SC_VALUE;
    #elif FTM3_C0SC_MASK == FTM3_C0SC_VALUE
  FTM3_C0SC |= FTM3_C0SC_VALUE;
    #elif FTM3_C0SC_VALUE == 0
  FTM3_C0SC &= ~FTM3_C0SC_MASK;
    #else
  FTM3_C0SC = (FTM3_C0SC & (~FTM3_C0SC_MASK)) | FTM3_C0SC_VALUE;
    #endif
  #elif defined(FTM3_C0SC_VALUE)
  FTM3_C0SC = FTM3_C0SC_VALUE;
  #endif

  /* Register 'FTM3_C1SC' initialization */
  #if FTM3_C1SC_MASK
    #if FTM3_C1SC_MASK == 0xFFFFFFFF
  FTM3_C1SC = FTM3_C1SC_VALUE;
    #elif FTM3_C1SC_MASK == FTM3_C1SC_VALUE
  FTM3_C1SC |= FTM3_C1SC_VALUE;
    #elif FTM3_C1SC_VALUE == 0
  FTM3_C1SC &= ~FTM3_C1SC_MASK;
    #else
  FTM3_C1SC = (FTM3_C1SC & (~FTM3_C1SC_MASK)) | FTM3_C1SC_VALUE;
    #endif
  #elif defined(FTM3_C1SC_VALUE)
  FTM3_C1SC = FTM3_C1SC_VALUE;
  #endif

  /* Register 'FTM3_C2SC' initialization */
  #if FTM3_C2SC_MASK
    #if FTM3_C2SC_MASK == 0xFFFFFFFF
  FTM3_C2SC = FTM3_C2SC_VALUE;
    #elif FTM3_C2SC_MASK == FTM3_C2SC_VALUE
  FTM3_C2SC |= FTM3_C2SC_VALUE;
    #elif FTM3_C2SC_VALUE == 0
  FTM3_C2SC &= ~FTM3_C2SC_MASK;
    #else
  FTM3_C2SC = (FTM3_C2SC & (~FTM3_C2SC_MASK)) | FTM3_C2SC_VALUE;
    #endif
  #elif defined(FTM3_C2SC_VALUE)
  FTM3_C2SC = FTM3_C2SC_VALUE;
  #endif

  /* Register 'FTM3_C3SC' initialization */
  #if FTM3_C3SC_MASK
    #if FTM3_C3SC_MASK == 0xFFFFFFFF
  FTM3_C3SC = FTM3_C3SC_VALUE;
    #elif FTM3_C3SC_MASK == FTM3_C3SC_VALUE
  FTM3_C3SC |= FTM3_C3SC_VALUE;
    #elif FTM3_C3SC_VALUE == 0
  FTM3_C3SC &= ~FTM3_C3SC_MASK;
    #else
  FTM3_C3SC = (FTM3_C3SC & (~FTM3_C3SC_MASK)) | FTM3_C3SC_VALUE;
    #endif
  #elif defined(FTM3_C3SC_VALUE)
  FTM3_C3SC = FTM3_C3SC_VALUE;
  #endif

  /* Register 'FTM3_C4SC' initialization */
  #if FTM3_C4SC_MASK
    #if FTM3_C4SC_MASK == 0xFFFFFFFF
  FTM3_C4SC = FTM3_C4SC_VALUE;
    #elif FTM3_C4SC_MASK == FTM3_C4SC_VALUE
  FTM3_C4SC |= FTM3_C4SC_VALUE;
    #elif FTM3_C4SC_VALUE == 0
  FTM3_C4SC &= ~FTM3_C4SC_MASK;
    #else
  FTM3_C4SC = (FTM3_C4SC & (~FTM3_C4SC_MASK)) | FTM3_C4SC_VALUE;
    #endif
  #elif defined(FTM3_C4SC_VALUE)
  FTM3_C4SC = FTM3_C4SC_VALUE;
  #endif

  /* Register 'FTM3_C5SC' initialization */
  #if FTM3_C5SC_MASK
    #if FTM3_C5SC_MASK == 0xFFFFFFFF
  FTM3_C5SC = FTM3_C5SC_VALUE;
    #elif FTM3_C5SC_MASK == FTM3_C5SC_VALUE
  FTM3_C5SC |= FTM3_C5SC_VALUE;
    #elif FTM3_C5SC_VALUE == 0
  FTM3_C5SC &= ~FTM3_C5SC_MASK;
    #else
  FTM3_C5SC = (FTM3_C5SC & (~FTM3_C5SC_MASK)) | FTM3_C5SC_VALUE;
    #endif
  #elif defined(FTM3_C5SC_VALUE)
  FTM3_C5SC = FTM3_C5SC_VALUE;
  #endif

  /* Register 'FTM3_C6SC' initialization */
  #if FTM3_C6SC_MASK
    #if FTM3_C6SC_MASK == 0xFFFFFFFF
  FTM3_C6SC = FTM3_C6SC_VALUE;
    #elif FTM3_C6SC_MASK == FTM3_C6SC_VALUE
  FTM3_C6SC |= FTM3_C6SC_VALUE;
    #elif FTM3_C6SC_VALUE == 0
  FTM3_C6SC &= ~FTM3_C6SC_MASK;
    #else
  FTM3_C6SC = (FTM3_C6SC & (~FTM3_C6SC_MASK)) | FTM3_C6SC_VALUE;
    #endif
  #elif defined(FTM3_C6SC_VALUE)
  FTM3_C6SC = FTM3_C6SC_VALUE;
  #endif

  /* Register 'FTM3_C7SC' initialization */
  #if FTM3_C7SC_MASK
    #if FTM3_C7SC_MASK == 0xFFFFFFFF
  FTM3_C7SC = FTM3_C7SC_VALUE;
    #elif FTM3_C7SC_MASK == FTM3_C7SC_VALUE
  FTM3_C7SC |= FTM3_C7SC_VALUE;
    #elif FTM3_C7SC_VALUE == 0
  FTM3_C7SC &= ~FTM3_C7SC_MASK;
    #else
  FTM3_C7SC = (FTM3_C7SC & (~FTM3_C7SC_MASK)) | FTM3_C7SC_VALUE;
    #endif
  #elif defined(FTM3_C7SC_VALUE)
  FTM3_C7SC = FTM3_C7SC_VALUE;
  #endif

  /* Register 'FTM3_C0V' initialization */
  #if FTM3_C0V_MASK
    #if FTM3_C0V_MASK == 0xFFFFFFFF
  FTM3_C0V = FTM3_C0V_VALUE;
    #elif FTM3_C0V_MASK == FTM3_C0V_VALUE
  FTM3_C0V |= FTM3_C0V_VALUE;
    #elif FTM3_C0V_VALUE == 0
  FTM3_C0V &= ~FTM3_C0V_MASK;
    #else
  FTM3_C0V = (FTM3_C0V & (~FTM3_C0V_MASK)) | FTM3_C0V_VALUE;
    #endif
  #elif defined(FTM3_C0V_VALUE)
  FTM3_C0V = FTM3_C0V_VALUE;
  #endif

  /* Register 'FTM3_C1V' initialization */
  #if FTM3_C1V_MASK
    #if FTM3_C1V_MASK == 0xFFFFFFFF
  FTM3_C1V = FTM3_C1V_VALUE;
    #elif FTM3_C1V_MASK == FTM3_C1V_VALUE
  FTM3_C1V |= FTM3_C1V_VALUE;
    #elif FTM3_C1V_VALUE == 0
  FTM3_C1V &= ~FTM3_C1V_MASK;
    #else
  FTM3_C1V = (FTM3_C1V & (~FTM3_C1V_MASK)) | FTM3_C1V_VALUE;
    #endif
  #elif defined(FTM3_C1V_VALUE)
  FTM3_C1V = FTM3_C1V_VALUE;
  #endif

  /* Register 'FTM3_C2V' initialization */
  #if FTM3_C2V_MASK
    #if FTM3_C2V_MASK == 0xFFFFFFFF
  FTM3_C2V = FTM3_C2V_VALUE;
    #elif FTM3_C2V_MASK == FTM3_C2V_VALUE
  FTM3_C2V |= FTM3_C2V_VALUE;
    #elif FTM3_C2V_VALUE == 0
  FTM3_C2V &= ~FTM3_C2V_MASK;
    #else
  FTM3_C2V = (FTM3_C2V & (~FTM3_C2V_MASK)) | FTM3_C2V_VALUE;
    #endif
  #elif defined(FTM3_C2V_VALUE)
  FTM3_C2V = FTM3_C2V_VALUE;
  #endif

  /* Register 'FTM3_C3V' initialization */
  #if FTM3_C3V_MASK
    #if FTM3_C3V_MASK == 0xFFFFFFFF
  FTM3_C3V = FTM3_C3V_VALUE;
    #elif FTM3_C3V_MASK == FTM3_C3V_VALUE
  FTM3_C3V |= FTM3_C3V_VALUE;
    #elif FTM3_C3V_VALUE == 0
  FTM3_C3V &= ~FTM3_C3V_MASK;
    #else
  FTM3_C3V = (FTM3_C3V & (~FTM3_C3V_MASK)) | FTM3_C3V_VALUE;
    #endif
  #elif defined(FTM3_C3V_VALUE)
  FTM3_C3V = FTM3_C3V_VALUE;
  #endif

  /* Register 'FTM3_C4V' initialization */
  #if FTM3_C4V_MASK
    #if FTM3_C4V_MASK == 0xFFFFFFFF
  FTM3_C4V = FTM3_C4V_VALUE;
    #elif FTM3_C4V_MASK == FTM3_C4V_VALUE
  FTM3_C4V |= FTM3_C4V_VALUE;
    #elif FTM3_C4V_VALUE == 0
  FTM3_C4V &= ~FTM3_C4V_MASK;
    #else
  FTM3_C4V = (FTM3_C4V & (~FTM3_C4V_MASK)) | FTM3_C4V_VALUE;
    #endif
  #elif defined(FTM3_C4V_VALUE)
  FTM3_C4V = FTM3_C4V_VALUE;
  #endif

  /* Register 'FTM3_C5V' initialization */
  #if FTM3_C5V_MASK
    #if FTM3_C5V_MASK == 0xFFFFFFFF
  FTM3_C5V = FTM3_C5V_VALUE;
    #elif FTM3_C5V_MASK == FTM3_C5V_VALUE
  FTM3_C5V |= FTM3_C5V_VALUE;
    #elif FTM3_C5V_VALUE == 0
  FTM3_C5V &= ~FTM3_C5V_MASK;
    #else
  FTM3_C5V = (FTM3_C5V & (~FTM3_C5V_MASK)) | FTM3_C5V_VALUE;
    #endif
  #elif defined(FTM3_C5V_VALUE)
  FTM3_C5V = FTM3_C5V_VALUE;
  #endif

  /* Register 'FTM3_C6V' initialization */
  #if FTM3_C6V_MASK
    #if FTM3_C6V_MASK == 0xFFFFFFFF
  FTM3_C6V = FTM3_C6V_VALUE;
    #elif FTM3_C6V_MASK == FTM3_C6V_VALUE
  FTM3_C6V |= FTM3_C6V_VALUE;
    #elif FTM3_C6V_VALUE == 0
  FTM3_C6V &= ~FTM3_C6V_MASK;
    #else
  FTM3_C6V = (FTM3_C6V & (~FTM3_C6V_MASK)) | FTM3_C6V_VALUE;
    #endif
  #elif defined(FTM3_C6V_VALUE)
  FTM3_C6V = FTM3_C6V_VALUE;
  #endif

  /* Register 'FTM3_C7V' initialization */
  #if FTM3_C7V_MASK
    #if FTM3_C7V_MASK == 0xFFFFFFFF
  FTM3_C7V = FTM3_C7V_VALUE;
    #elif FTM3_C7V_MASK == FTM3_C7V_VALUE
  FTM3_C7V |= FTM3_C7V_VALUE;
    #elif FTM3_C7V_VALUE == 0
  FTM3_C7V &= ~FTM3_C7V_MASK;
    #else
  FTM3_C7V = (FTM3_C7V & (~FTM3_C7V_MASK)) | FTM3_C7V_VALUE;
    #endif
  #elif defined(FTM3_C7V_VALUE)
  FTM3_C7V = FTM3_C7V_VALUE;
  #endif

  /* Register 'FTM3_POL' initialization */
  #if FTM3_POL_MASK
    #if FTM3_POL_MASK == 0xFFFFFFFF
  FTM3_POL = FTM3_POL_VALUE;
    #elif FTM3_POL_MASK == FTM3_POL_VALUE
  FTM3_POL |= FTM3_POL_VALUE;
    #elif FTM3_POL_VALUE == 0
  FTM3_POL &= ~FTM3_POL_MASK;
    #else
  FTM3_POL = (FTM3_POL & (~FTM3_POL_MASK)) | FTM3_POL_VALUE;
    #endif
  #elif defined(FTM3_POL_VALUE)
  FTM3_POL = FTM3_POL_VALUE;
  #endif

  /* Register 'FTM3_FILTER' initialization */
  #if FTM3_FILTER_MASK
    #if FTM3_FILTER_MASK == 0xFFFFFFFF
  FTM3_FILTER = FTM3_FILTER_VALUE;
    #elif FTM3_FILTER_MASK == FTM3_FILTER_VALUE
  FTM3_FILTER |= FTM3_FILTER_VALUE;
    #elif FTM3_FILTER_VALUE == 0
  FTM3_FILTER &= ~FTM3_FILTER_MASK;
    #else
  FTM3_FILTER = (FTM3_FILTER & (~FTM3_FILTER_MASK)) | FTM3_FILTER_VALUE;
    #endif
  #elif defined(FTM3_FILTER_VALUE)
  FTM3_FILTER = FTM3_FILTER_VALUE;
  #endif

  /* Register 'FTM3_OUTINIT' initialization */
  #if FTM3_OUTINIT_MASK
    #if FTM3_OUTINIT_MASK == 0xFFFFFFFF
  FTM3_OUTINIT = FTM3_OUTINIT_VALUE;
    #elif FTM3_OUTINIT_MASK == FTM3_OUTINIT_VALUE
  FTM3_OUTINIT |= FTM3_OUTINIT_VALUE;
    #elif FTM3_OUTINIT_VALUE == 0
  FTM3_OUTINIT &= ~FTM3_OUTINIT_MASK;
    #else
  FTM3_OUTINIT = (FTM3_OUTINIT & (~FTM3_OUTINIT_MASK)) | FTM3_OUTINIT_VALUE;
    #endif
  #elif defined(FTM3_OUTINIT_VALUE)
  FTM3_OUTINIT = FTM3_OUTINIT_VALUE;
  #endif

  /* Register 'FTM3_OUTMASK' initialization */
  #if FTM3_OUTMASK_MASK
    #if FTM3_OUTMASK_MASK == 0xFFFFFFFF
  FTM3_OUTMASK = FTM3_OUTMASK_VALUE;
    #elif FTM3_OUTMASK_MASK == FTM3_OUTMASK_VALUE
  FTM3_OUTMASK |= FTM3_OUTMASK_VALUE;
    #elif FTM3_OUTMASK_VALUE == 0
  FTM3_OUTMASK &= ~FTM3_OUTMASK_MASK;
    #else
  FTM3_OUTMASK = (FTM3_OUTMASK & (~FTM3_OUTMASK_MASK)) | FTM3_OUTMASK_VALUE;
    #endif
  #elif defined(FTM3_OUTMASK_VALUE)
  FTM3_OUTMASK = FTM3_OUTMASK_VALUE;
  #endif

  /* Register 'FTM3_FLTCTRL' initialization */
  #if FTM3_FLTCTRL_MASK_1
    #if FTM3_FLTCTRL_MASK_1 == 0xFFFFFFFF
  FTM3_FLTCTRL = FTM3_FLTCTRL_VALUE_1;
    #elif FTM3_FLTCTRL_MASK_1 == FTM3_FLTCTRL_VALUE_1
  FTM3_FLTCTRL |= FTM3_FLTCTRL_VALUE_1;
    #elif FTM3_FLTCTRL_VALUE_1 == 0
  FTM3_FLTCTRL &= ~FTM3_FLTCTRL_MASK_1;
    #else
  FTM3_FLTCTRL = (FTM3_FLTCTRL & (~FTM3_FLTCTRL_MASK_1)) | FTM3_FLTCTRL_VALUE_1;
    #endif
  #elif defined(FTM3_FLTCTRL_VALUE_1)
  FTM3_FLTCTRL = FTM3_FLTCTRL_VALUE_1;
  #endif

  /* Register 'FTM3_FLTPOL' initialization */
  #if FTM3_FLTPOL_MASK
    #if FTM3_FLTPOL_MASK == 0xFFFFFFFF
  FTM3_FLTPOL = FTM3_FLTPOL_VALUE;
    #elif FTM3_FLTPOL_MASK == FTM3_FLTPOL_VALUE
  FTM3_FLTPOL |= FTM3_FLTPOL_VALUE;
    #elif FTM3_FLTPOL_VALUE == 0
  FTM3_FLTPOL &= ~FTM3_FLTPOL_MASK;
    #else
  FTM3_FLTPOL = (FTM3_FLTPOL & (~FTM3_FLTPOL_MASK)) | FTM3_FLTPOL_VALUE;
    #endif
  #elif defined(FTM3_FLTPOL_VALUE)
  FTM3_FLTPOL = FTM3_FLTPOL_VALUE;
  #endif

  /* Register 'FTM3_FLTCTRL' initialization */
  #if FTM3_FLTCTRL_MASK_2
    #if FTM3_FLTCTRL_MASK_2 == 0xFFFFFFFF
  FTM3_FLTCTRL = FTM3_FLTCTRL_VALUE_2;
    #elif FTM3_FLTCTRL_MASK_2 == FTM3_FLTCTRL_VALUE_2
  FTM3_FLTCTRL |= FTM3_FLTCTRL_VALUE_2;
    #elif FTM3_FLTCTRL_VALUE_2 == 0
  FTM3_FLTCTRL &= ~FTM3_FLTCTRL_MASK_2;
    #else
  FTM3_FLTCTRL = (FTM3_FLTCTRL & (~FTM3_FLTCTRL_MASK_2)) | FTM3_FLTCTRL_VALUE_2;
    #endif
  #elif defined(FTM3_FLTCTRL_VALUE_2)
  FTM3_FLTCTRL = FTM3_FLTCTRL_VALUE_2;
  #endif

  /* Register 'FTM3_SYNC' initialization */
  #if FTM3_SYNC_MASK
    #if FTM3_SYNC_MASK == 0xFFFFFFFF
  FTM3_SYNC = FTM3_SYNC_VALUE;
    #elif FTM3_SYNC_MASK == FTM3_SYNC_VALUE
  FTM3_SYNC |= FTM3_SYNC_VALUE;
    #elif FTM3_SYNC_VALUE == 0
  FTM3_SYNC &= ~FTM3_SYNC_MASK;
    #else
  FTM3_SYNC = (FTM3_SYNC & (~FTM3_SYNC_MASK)) | FTM3_SYNC_VALUE;
    #endif
  #elif defined(FTM3_SYNC_VALUE)
  FTM3_SYNC = FTM3_SYNC_VALUE;
  #endif

  /* Register 'FTM3_EXTTRIG' initialization */
  #if FTM3_EXTTRIG_MASK
    #if FTM3_EXTTRIG_MASK == 0xFFFFFFFF
  FTM3_EXTTRIG = FTM3_EXTTRIG_VALUE;
    #elif FTM3_EXTTRIG_MASK == FTM3_EXTTRIG_VALUE
  FTM3_EXTTRIG |= FTM3_EXTTRIG_VALUE;
    #elif FTM3_EXTTRIG_VALUE == 0
  FTM3_EXTTRIG &= ~FTM3_EXTTRIG_MASK;
    #else
  FTM3_EXTTRIG = (FTM3_EXTTRIG & (~FTM3_EXTTRIG_MASK)) | FTM3_EXTTRIG_VALUE;
    #endif
  #elif defined(FTM3_EXTTRIG_VALUE)
  FTM3_EXTTRIG = FTM3_EXTTRIG_VALUE;
  #endif

  /* Register 'FTM3_MOD' initialization */
  #if FTM3_MOD_MASK
    #if FTM3_MOD_MASK == 0xFFFFFFFF
  FTM3_MOD = FTM3_MOD_VALUE;
    #elif FTM3_MOD_MASK == FTM3_MOD_VALUE
  FTM3_MOD |= FTM3_MOD_VALUE;
    #elif FTM3_MOD_VALUE == 0
  FTM3_MOD &= ~FTM3_MOD_MASK;
    #else
  FTM3_MOD = (FTM3_MOD & (~FTM3_MOD_MASK)) | FTM3_MOD_VALUE;
    #endif
  #elif defined(FTM3_MOD_VALUE)
  FTM3_MOD = FTM3_MOD_VALUE;
  #endif

  /* Register 'FTM3_CNTIN' initialization */
  #if FTM3_CNTIN_MASK
    #if FTM3_CNTIN_MASK == 0xFFFFFFFF
  FTM3_CNTIN = FTM3_CNTIN_VALUE;
    #elif FTM3_CNTIN_MASK == FTM3_CNTIN_VALUE
  FTM3_CNTIN |= FTM3_CNTIN_VALUE;
    #elif FTM3_CNTIN_VALUE == 0
  FTM3_CNTIN &= ~FTM3_CNTIN_MASK;
    #else
  FTM3_CNTIN = (FTM3_CNTIN & (~FTM3_CNTIN_MASK)) | FTM3_CNTIN_VALUE;
    #endif
  #elif defined(FTM3_CNTIN_VALUE)
  FTM3_CNTIN = FTM3_CNTIN_VALUE;
  #endif

  /* Register 'FTM3_DEADTIME' initialization */
  #if FTM3_DEADTIME_MASK
    #if FTM3_DEADTIME_MASK == 0xFFFFFFFF
  FTM3_DEADTIME = FTM3_DEADTIME_VALUE;
    #elif FTM3_DEADTIME_MASK == FTM3_DEADTIME_VALUE
  FTM3_DEADTIME |= FTM3_DEADTIME_VALUE;
    #elif FTM3_DEADTIME_VALUE == 0
  FTM3_DEADTIME &= ~FTM3_DEADTIME_MASK;
    #else
  FTM3_DEADTIME = (FTM3_DEADTIME & (~FTM3_DEADTIME_MASK)) | FTM3_DEADTIME_VALUE;
    #endif
  #elif defined(FTM3_DEADTIME_VALUE)
  FTM3_DEADTIME = FTM3_DEADTIME_VALUE;
  #endif

  FTM3_CNT &= ~0xFFFF;

  /* Register 'FTM3_MODE' initialization */
  #if FTM3_MODE_MASK_3
    #if FTM3_MODE_MASK_3 == 0xFFFFFFFF
  FTM3_MODE = FTM3_MODE_VALUE_3;
    #elif FTM3_MODE_MASK_3 == FTM3_MODE_VALUE_3
  FTM3_MODE |= FTM3_MODE_VALUE_3;
    #elif FTM3_MODE_VALUE_3 == 0
  FTM3_MODE &= ~FTM3_MODE_MASK_3;
    #else
  FTM3_MODE = (FTM3_MODE & (~FTM3_MODE_MASK_3)) | FTM3_MODE_VALUE_3;
    #endif
  #elif defined(FTM3_MODE_VALUE_3)
  FTM3_MODE = FTM3_MODE_VALUE_3;
  #endif

  /* Register 'FTM3_SYNCONF' initialization */
  #if FTM3_SYNCONF_MASK
    #if FTM3_SYNCONF_MASK == 0xFFFFFFFF
  FTM3_SYNCONF = FTM3_SYNCONF_VALUE;
    #elif FTM3_SYNCONF_MASK == FTM3_SYNCONF_VALUE
  FTM3_SYNCONF |= FTM3_SYNCONF_VALUE;
    #elif FTM3_SYNCONF_VALUE == 0
  FTM3_SYNCONF &= ~FTM3_SYNCONF_MASK;
    #else
  FTM3_SYNCONF = (FTM3_SYNCONF & (~FTM3_SYNCONF_MASK)) | FTM3_SYNCONF_VALUE;
    #endif
  #elif defined(FTM3_SYNCONF_VALUE)
  FTM3_SYNCONF = FTM3_SYNCONF_VALUE;
  #endif

  /* Register 'FTM3_SC' initialization */
  #if FTM3_SC_MASK_3
    #if FTM3_SC_MASK_3 == 0xFFFFFFFF
  FTM3_SC = FTM3_SC_VALUE_3;
    #elif FTM3_SC_MASK_3 == FTM3_SC_VALUE_3
  FTM3_SC |= FTM3_SC_VALUE_3;
    #elif FTM3_SC_VALUE_3 == 0
  FTM3_SC &= ~FTM3_SC_MASK_3;
    #else
  FTM3_SC = (FTM3_SC & (~FTM3_SC_MASK_3)) | FTM3_SC_VALUE_3;
    #endif
  #elif defined(FTM3_SC_VALUE_3)
  FTM3_SC = FTM3_SC_VALUE_3;
  #endif

  /* Register 'FTM3_FMS' initialization */
  #if FTM3_FMS_MASK
    #if FTM3_FMS_MASK == 0xFFFFFFFF
  FTM3_FMS = FTM3_FMS_VALUE;
    #elif FTM3_FMS_MASK == FTM3_FMS_VALUE
  FTM3_FMS |= FTM3_FMS_VALUE;
    #elif FTM3_FMS_VALUE == 0
  FTM3_FMS &= ~FTM3_FMS_MASK;
    #else
  FTM3_FMS = (FTM3_FMS & (~FTM3_FMS_MASK)) | FTM3_FMS_VALUE;
    #endif
  #elif defined(FTM3_FMS_VALUE)
  FTM3_FMS = FTM3_FMS_VALUE;
  #endif

  /* Register 'FTM3_SWOCTRL' initialization */
  #if FTM3_SWOCTRL_MASK
    #if FTM3_SWOCTRL_MASK == 0xFFFFFFFF
  FTM3_SWOCTRL = FTM3_SWOCTRL_VALUE;
    #elif FTM3_SWOCTRL_MASK == FTM3_SWOCTRL_VALUE
  FTM3_SWOCTRL |= FTM3_SWOCTRL_VALUE;
    #elif FTM3_SWOCTRL_VALUE == 0
  FTM3_SWOCTRL &= ~FTM3_SWOCTRL_MASK;
    #else
  FTM3_SWOCTRL = (FTM3_SWOCTRL & (~FTM3_SWOCTRL_MASK)) | FTM3_SWOCTRL_VALUE;
    #endif
  #elif defined(FTM3_SWOCTRL_VALUE)
  FTM3_SWOCTRL = FTM3_SWOCTRL_VALUE;
  #endif

  /* Register 'FTM3_CONF' initialization */
  #if FTM3_CONF_MASK
    #if FTM3_CONF_MASK == 0xFFFFFFFF
  FTM3_CONF = FTM3_CONF_VALUE;
    #elif FTM3_CONF_MASK == FTM3_CONF_VALUE
  FTM3_CONF |= FTM3_CONF_VALUE;
    #elif FTM3_CONF_VALUE == 0
  FTM3_CONF &= ~FTM3_CONF_MASK;
    #else
  FTM3_CONF = (FTM3_CONF & (~FTM3_CONF_MASK)) | FTM3_CONF_VALUE;
    #endif
  #elif defined(FTM3_CONF_VALUE)
  FTM3_CONF = FTM3_CONF_VALUE;
  #endif

  /* Register 'FTM3_PWMLOAD' initialization */
  #if FTM3_PWMLOAD_MASK
    #if FTM3_PWMLOAD_MASK == 0xFFFFFFFF
  FTM3_PWMLOAD = FTM3_PWMLOAD_VALUE;
    #elif FTM3_PWMLOAD_MASK == FTM3_PWMLOAD_VALUE
  FTM3_PWMLOAD |= FTM3_PWMLOAD_VALUE;
    #elif FTM3_PWMLOAD_VALUE == 0
  FTM3_PWMLOAD &= ~FTM3_PWMLOAD_MASK;
    #else
  FTM3_PWMLOAD = (FTM3_PWMLOAD & (~FTM3_PWMLOAD_MASK)) | FTM3_PWMLOAD_VALUE;
    #endif
  #elif defined(FTM3_PWMLOAD_VALUE)
  FTM3_PWMLOAD = FTM3_PWMLOAD_VALUE;
  #endif
}

#ifdef __cplusplus
}
#endif

/* END FTM3_Init. */

/** ###################################################################
 **
 **     This file is a part of Processor Expert static initialization
 **     library for Freescale microcontrollers.
 **
 ** ################################################################### */
