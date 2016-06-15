/** ###################################################################
 **     Filename    : FTM1_Init.c
 **     Processor   : MK22FN512LH12
 **     Abstract    :
 **          This file implements the FTM1 module initialization
 **          according to the Peripheral Initialization settings, and
 **          defines interrupt service routines prototypes.
 **
 **     Contents    :
 **         Int   - void FTM1_Init(void);
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
 * @file FTM1_Init.c
 * @brief This file implements the FTM1 module initialization according to the
 *        Peripheral Initialization settings, and defines interrupt service
 *        routines prototypes.
 */


/* MODULE FTM1_Init. */

#include "FTM1_Init.h"
#include "MK22F51212.h"
#include "Init_Config.h"

#ifdef __cplusplus
extern "C" {
#endif

void FTM1_Init(void) {
  (void)FTM1_SC;  /* Dummy read of the Control Status register to clear the interrupt flag */
  FTM1_SC = 0;  /* Stop the counter */
  #ifdef FTM1_C0SC
  (void)FTM1_C0SC; /* Dummy read of the Channel Status and Control 0 register to clear the interrupt flag */
  #endif
  #ifdef FTM1_C1SC
  (void)FTM1_C1SC; /* Dummy read of the Channel Status and Control 1 register to clear the interrupt flag */
  #endif
  #ifdef FTM1_C2SC
  (void)FTM1_C2SC; /* Dummy read of the Channel Status and Control 2 register to clear the interrupt flag */
  #endif
  #ifdef FTM1_C3SC
  (void)FTM1_C3SC; /* Dummy read of the Channel Status and Control 3 register to clear the interrupt flag */
  #endif
  #ifdef FTM1_C4SC
  (void)FTM1_C4SC; /* Dummy read of the Channel Status and Control 4 register to clear the interrupt flag */
  #endif
  #ifdef FTM1_C5SC
  (void)FTM1_C5SC; /* Dummy read of the Channel Status and Control 5 register to clear the interrupt flag */
  #endif
  #ifdef FTM1_C6SC
  (void)FTM1_C6SC; /* Dummy read of the Channel Status and Control 6 register to clear the interrupt flag */
  #endif
  #ifdef FTM1_C7SC
  (void)FTM1_C7SC; /* Dummy read of the Channel Status and Control 7 register to clear the interrupt flag */
  #endif
  #ifdef FTM1_MODE_VALUE_1
  FTM1_MODE |= FTM1_MODE_VALUE_1; /* Disable write protection */
  #endif

  FTM1_C0SC = 0;

  FTM1_C1SC = 0;

  /* Register 'FTM1_SC' initialization */
  #if FTM1_SC_MASK_2
    #if FTM1_SC_MASK_2 == 0xFFFFFFFF
  FTM1_SC = FTM1_SC_VALUE_2;
    #elif FTM1_SC_MASK_2 == FTM1_SC_VALUE_2
  FTM1_SC |= FTM1_SC_VALUE_2;
    #elif FTM1_SC_VALUE_2 == 0
  FTM1_SC &= ~FTM1_SC_MASK_2;
    #else
  FTM1_SC = (FTM1_SC & (~FTM1_SC_MASK_2)) | FTM1_SC_VALUE_2;
    #endif
  #elif defined(FTM1_SC_VALUE_2)
  FTM1_SC = FTM1_SC_VALUE_2;
  #endif

  /* Register 'FTM1_MODE' initialization */
  #if FTM1_MODE_MASK_2
    #if FTM1_MODE_MASK_2 == 0xFFFFFFFF
  FTM1_MODE = FTM1_MODE_VALUE_2;
    #elif FTM1_MODE_MASK_2 == FTM1_MODE_VALUE_2
  FTM1_MODE |= FTM1_MODE_VALUE_2;
    #elif FTM1_MODE_VALUE_2 == 0
  FTM1_MODE &= ~FTM1_MODE_MASK_2;
    #else
  FTM1_MODE = (FTM1_MODE & (~FTM1_MODE_MASK_2)) | FTM1_MODE_VALUE_2;
    #endif
  #elif defined(FTM1_MODE_VALUE_2)
  FTM1_MODE = FTM1_MODE_VALUE_2;
  #endif

  /* Register 'FTM1_COMBINE' initialization */
  #if FTM1_COMBINE_MASK
    #if FTM1_COMBINE_MASK == 0xFFFFFFFF
  FTM1_COMBINE = FTM1_COMBINE_VALUE;
    #elif FTM1_COMBINE_MASK == FTM1_COMBINE_VALUE
  FTM1_COMBINE |= FTM1_COMBINE_VALUE;
    #elif FTM1_COMBINE_VALUE == 0
  FTM1_COMBINE &= ~FTM1_COMBINE_MASK;
    #else
  FTM1_COMBINE = (FTM1_COMBINE & (~FTM1_COMBINE_MASK)) | FTM1_COMBINE_VALUE;
    #endif
  #elif defined(FTM1_COMBINE_VALUE)
  FTM1_COMBINE = FTM1_COMBINE_VALUE;
  #endif

  /* Register 'FTM1_INVCTRL' initialization */
  #if FTM1_INVCTRL_MASK
    #if FTM1_INVCTRL_MASK == 0xFFFFFFFF
  FTM1_INVCTRL = FTM1_INVCTRL_VALUE;
    #elif FTM1_INVCTRL_MASK == FTM1_INVCTRL_VALUE
  FTM1_INVCTRL |= FTM1_INVCTRL_VALUE;
    #elif FTM1_INVCTRL_VALUE == 0
  FTM1_INVCTRL &= ~FTM1_INVCTRL_MASK;
    #else
  FTM1_INVCTRL = (FTM1_INVCTRL & (~FTM1_INVCTRL_MASK)) | FTM1_INVCTRL_VALUE;
    #endif
  #elif defined(FTM1_INVCTRL_VALUE)
  FTM1_INVCTRL = FTM1_INVCTRL_VALUE;
  #endif

  /* Register 'FTM1_C0SC' initialization */
  #if FTM1_C0SC_MASK
    #if FTM1_C0SC_MASK == 0xFFFFFFFF
  FTM1_C0SC = FTM1_C0SC_VALUE;
    #elif FTM1_C0SC_MASK == FTM1_C0SC_VALUE
  FTM1_C0SC |= FTM1_C0SC_VALUE;
    #elif FTM1_C0SC_VALUE == 0
  FTM1_C0SC &= ~FTM1_C0SC_MASK;
    #else
  FTM1_C0SC = (FTM1_C0SC & (~FTM1_C0SC_MASK)) | FTM1_C0SC_VALUE;
    #endif
  #elif defined(FTM1_C0SC_VALUE)
  FTM1_C0SC = FTM1_C0SC_VALUE;
  #endif

  /* Register 'FTM1_C1SC' initialization */
  #if FTM1_C1SC_MASK
    #if FTM1_C1SC_MASK == 0xFFFFFFFF
  FTM1_C1SC = FTM1_C1SC_VALUE;
    #elif FTM1_C1SC_MASK == FTM1_C1SC_VALUE
  FTM1_C1SC |= FTM1_C1SC_VALUE;
    #elif FTM1_C1SC_VALUE == 0
  FTM1_C1SC &= ~FTM1_C1SC_MASK;
    #else
  FTM1_C1SC = (FTM1_C1SC & (~FTM1_C1SC_MASK)) | FTM1_C1SC_VALUE;
    #endif
  #elif defined(FTM1_C1SC_VALUE)
  FTM1_C1SC = FTM1_C1SC_VALUE;
  #endif

  /* Register 'FTM1_C0V' initialization */
  #if FTM1_C0V_MASK
    #if FTM1_C0V_MASK == 0xFFFFFFFF
  FTM1_C0V = FTM1_C0V_VALUE;
    #elif FTM1_C0V_MASK == FTM1_C0V_VALUE
  FTM1_C0V |= FTM1_C0V_VALUE;
    #elif FTM1_C0V_VALUE == 0
  FTM1_C0V &= ~FTM1_C0V_MASK;
    #else
  FTM1_C0V = (FTM1_C0V & (~FTM1_C0V_MASK)) | FTM1_C0V_VALUE;
    #endif
  #elif defined(FTM1_C0V_VALUE)
  FTM1_C0V = FTM1_C0V_VALUE;
  #endif

  /* Register 'FTM1_C1V' initialization */
  #if FTM1_C1V_MASK
    #if FTM1_C1V_MASK == 0xFFFFFFFF
  FTM1_C1V = FTM1_C1V_VALUE;
    #elif FTM1_C1V_MASK == FTM1_C1V_VALUE
  FTM1_C1V |= FTM1_C1V_VALUE;
    #elif FTM1_C1V_VALUE == 0
  FTM1_C1V &= ~FTM1_C1V_MASK;
    #else
  FTM1_C1V = (FTM1_C1V & (~FTM1_C1V_MASK)) | FTM1_C1V_VALUE;
    #endif
  #elif defined(FTM1_C1V_VALUE)
  FTM1_C1V = FTM1_C1V_VALUE;
  #endif

  /* Register 'FTM1_POL' initialization */
  #if FTM1_POL_MASK
    #if FTM1_POL_MASK == 0xFFFFFFFF
  FTM1_POL = FTM1_POL_VALUE;
    #elif FTM1_POL_MASK == FTM1_POL_VALUE
  FTM1_POL |= FTM1_POL_VALUE;
    #elif FTM1_POL_VALUE == 0
  FTM1_POL &= ~FTM1_POL_MASK;
    #else
  FTM1_POL = (FTM1_POL & (~FTM1_POL_MASK)) | FTM1_POL_VALUE;
    #endif
  #elif defined(FTM1_POL_VALUE)
  FTM1_POL = FTM1_POL_VALUE;
  #endif

  /* Register 'FTM1_FILTER' initialization */
  #if FTM1_FILTER_MASK
    #if FTM1_FILTER_MASK == 0xFFFFFFFF
  FTM1_FILTER = FTM1_FILTER_VALUE;
    #elif FTM1_FILTER_MASK == FTM1_FILTER_VALUE
  FTM1_FILTER |= FTM1_FILTER_VALUE;
    #elif FTM1_FILTER_VALUE == 0
  FTM1_FILTER &= ~FTM1_FILTER_MASK;
    #else
  FTM1_FILTER = (FTM1_FILTER & (~FTM1_FILTER_MASK)) | FTM1_FILTER_VALUE;
    #endif
  #elif defined(FTM1_FILTER_VALUE)
  FTM1_FILTER = FTM1_FILTER_VALUE;
  #endif

  /* Register 'FTM1_OUTINIT' initialization */
  #if FTM1_OUTINIT_MASK
    #if FTM1_OUTINIT_MASK == 0xFFFFFFFF
  FTM1_OUTINIT = FTM1_OUTINIT_VALUE;
    #elif FTM1_OUTINIT_MASK == FTM1_OUTINIT_VALUE
  FTM1_OUTINIT |= FTM1_OUTINIT_VALUE;
    #elif FTM1_OUTINIT_VALUE == 0
  FTM1_OUTINIT &= ~FTM1_OUTINIT_MASK;
    #else
  FTM1_OUTINIT = (FTM1_OUTINIT & (~FTM1_OUTINIT_MASK)) | FTM1_OUTINIT_VALUE;
    #endif
  #elif defined(FTM1_OUTINIT_VALUE)
  FTM1_OUTINIT = FTM1_OUTINIT_VALUE;
  #endif

  /* Register 'FTM1_OUTMASK' initialization */
  #if FTM1_OUTMASK_MASK
    #if FTM1_OUTMASK_MASK == 0xFFFFFFFF
  FTM1_OUTMASK = FTM1_OUTMASK_VALUE;
    #elif FTM1_OUTMASK_MASK == FTM1_OUTMASK_VALUE
  FTM1_OUTMASK |= FTM1_OUTMASK_VALUE;
    #elif FTM1_OUTMASK_VALUE == 0
  FTM1_OUTMASK &= ~FTM1_OUTMASK_MASK;
    #else
  FTM1_OUTMASK = (FTM1_OUTMASK & (~FTM1_OUTMASK_MASK)) | FTM1_OUTMASK_VALUE;
    #endif
  #elif defined(FTM1_OUTMASK_VALUE)
  FTM1_OUTMASK = FTM1_OUTMASK_VALUE;
  #endif

  /* Register 'FTM1_FLTCTRL' initialization */
  #if FTM1_FLTCTRL_MASK_1
    #if FTM1_FLTCTRL_MASK_1 == 0xFFFFFFFF
  FTM1_FLTCTRL = FTM1_FLTCTRL_VALUE_1;
    #elif FTM1_FLTCTRL_MASK_1 == FTM1_FLTCTRL_VALUE_1
  FTM1_FLTCTRL |= FTM1_FLTCTRL_VALUE_1;
    #elif FTM1_FLTCTRL_VALUE_1 == 0
  FTM1_FLTCTRL &= ~FTM1_FLTCTRL_MASK_1;
    #else
  FTM1_FLTCTRL = (FTM1_FLTCTRL & (~FTM1_FLTCTRL_MASK_1)) | FTM1_FLTCTRL_VALUE_1;
    #endif
  #elif defined(FTM1_FLTCTRL_VALUE_1)
  FTM1_FLTCTRL = FTM1_FLTCTRL_VALUE_1;
  #endif

  /* Register 'FTM1_FLTPOL' initialization */
  #if FTM1_FLTPOL_MASK
    #if FTM1_FLTPOL_MASK == 0xFFFFFFFF
  FTM1_FLTPOL = FTM1_FLTPOL_VALUE;
    #elif FTM1_FLTPOL_MASK == FTM1_FLTPOL_VALUE
  FTM1_FLTPOL |= FTM1_FLTPOL_VALUE;
    #elif FTM1_FLTPOL_VALUE == 0
  FTM1_FLTPOL &= ~FTM1_FLTPOL_MASK;
    #else
  FTM1_FLTPOL = (FTM1_FLTPOL & (~FTM1_FLTPOL_MASK)) | FTM1_FLTPOL_VALUE;
    #endif
  #elif defined(FTM1_FLTPOL_VALUE)
  FTM1_FLTPOL = FTM1_FLTPOL_VALUE;
  #endif

  /* Register 'FTM1_FLTCTRL' initialization */
  #if FTM1_FLTCTRL_MASK_2
    #if FTM1_FLTCTRL_MASK_2 == 0xFFFFFFFF
  FTM1_FLTCTRL = FTM1_FLTCTRL_VALUE_2;
    #elif FTM1_FLTCTRL_MASK_2 == FTM1_FLTCTRL_VALUE_2
  FTM1_FLTCTRL |= FTM1_FLTCTRL_VALUE_2;
    #elif FTM1_FLTCTRL_VALUE_2 == 0
  FTM1_FLTCTRL &= ~FTM1_FLTCTRL_MASK_2;
    #else
  FTM1_FLTCTRL = (FTM1_FLTCTRL & (~FTM1_FLTCTRL_MASK_2)) | FTM1_FLTCTRL_VALUE_2;
    #endif
  #elif defined(FTM1_FLTCTRL_VALUE_2)
  FTM1_FLTCTRL = FTM1_FLTCTRL_VALUE_2;
  #endif

  /* Register 'FTM1_SYNC' initialization */
  #if FTM1_SYNC_MASK
    #if FTM1_SYNC_MASK == 0xFFFFFFFF
  FTM1_SYNC = FTM1_SYNC_VALUE;
    #elif FTM1_SYNC_MASK == FTM1_SYNC_VALUE
  FTM1_SYNC |= FTM1_SYNC_VALUE;
    #elif FTM1_SYNC_VALUE == 0
  FTM1_SYNC &= ~FTM1_SYNC_MASK;
    #else
  FTM1_SYNC = (FTM1_SYNC & (~FTM1_SYNC_MASK)) | FTM1_SYNC_VALUE;
    #endif
  #elif defined(FTM1_SYNC_VALUE)
  FTM1_SYNC = FTM1_SYNC_VALUE;
  #endif

  /* Register 'FTM1_EXTTRIG' initialization */
  #if FTM1_EXTTRIG_MASK
    #if FTM1_EXTTRIG_MASK == 0xFFFFFFFF
  FTM1_EXTTRIG = FTM1_EXTTRIG_VALUE;
    #elif FTM1_EXTTRIG_MASK == FTM1_EXTTRIG_VALUE
  FTM1_EXTTRIG |= FTM1_EXTTRIG_VALUE;
    #elif FTM1_EXTTRIG_VALUE == 0
  FTM1_EXTTRIG &= ~FTM1_EXTTRIG_MASK;
    #else
  FTM1_EXTTRIG = (FTM1_EXTTRIG & (~FTM1_EXTTRIG_MASK)) | FTM1_EXTTRIG_VALUE;
    #endif
  #elif defined(FTM1_EXTTRIG_VALUE)
  FTM1_EXTTRIG = FTM1_EXTTRIG_VALUE;
  #endif

  /* Register 'FTM1_MOD' initialization */
  #if FTM1_MOD_MASK
    #if FTM1_MOD_MASK == 0xFFFFFFFF
  FTM1_MOD = FTM1_MOD_VALUE;
    #elif FTM1_MOD_MASK == FTM1_MOD_VALUE
  FTM1_MOD |= FTM1_MOD_VALUE;
    #elif FTM1_MOD_VALUE == 0
  FTM1_MOD &= ~FTM1_MOD_MASK;
    #else
  FTM1_MOD = (FTM1_MOD & (~FTM1_MOD_MASK)) | FTM1_MOD_VALUE;
    #endif
  #elif defined(FTM1_MOD_VALUE)
  FTM1_MOD = FTM1_MOD_VALUE;
  #endif

  /* Register 'FTM1_CNTIN' initialization */
  #if FTM1_CNTIN_MASK
    #if FTM1_CNTIN_MASK == 0xFFFFFFFF
  FTM1_CNTIN = FTM1_CNTIN_VALUE;
    #elif FTM1_CNTIN_MASK == FTM1_CNTIN_VALUE
  FTM1_CNTIN |= FTM1_CNTIN_VALUE;
    #elif FTM1_CNTIN_VALUE == 0
  FTM1_CNTIN &= ~FTM1_CNTIN_MASK;
    #else
  FTM1_CNTIN = (FTM1_CNTIN & (~FTM1_CNTIN_MASK)) | FTM1_CNTIN_VALUE;
    #endif
  #elif defined(FTM1_CNTIN_VALUE)
  FTM1_CNTIN = FTM1_CNTIN_VALUE;
  #endif

  /* Register 'FTM1_DEADTIME' initialization */
  #if FTM1_DEADTIME_MASK
    #if FTM1_DEADTIME_MASK == 0xFFFFFFFF
  FTM1_DEADTIME = FTM1_DEADTIME_VALUE;
    #elif FTM1_DEADTIME_MASK == FTM1_DEADTIME_VALUE
  FTM1_DEADTIME |= FTM1_DEADTIME_VALUE;
    #elif FTM1_DEADTIME_VALUE == 0
  FTM1_DEADTIME &= ~FTM1_DEADTIME_MASK;
    #else
  FTM1_DEADTIME = (FTM1_DEADTIME & (~FTM1_DEADTIME_MASK)) | FTM1_DEADTIME_VALUE;
    #endif
  #elif defined(FTM1_DEADTIME_VALUE)
  FTM1_DEADTIME = FTM1_DEADTIME_VALUE;
  #endif

  FTM1_CNT &= ~0xFFFF;

  /* Register 'FTM1_MODE' initialization */
  #if FTM1_MODE_MASK_3
    #if FTM1_MODE_MASK_3 == 0xFFFFFFFF
  FTM1_MODE = FTM1_MODE_VALUE_3;
    #elif FTM1_MODE_MASK_3 == FTM1_MODE_VALUE_3
  FTM1_MODE |= FTM1_MODE_VALUE_3;
    #elif FTM1_MODE_VALUE_3 == 0
  FTM1_MODE &= ~FTM1_MODE_MASK_3;
    #else
  FTM1_MODE = (FTM1_MODE & (~FTM1_MODE_MASK_3)) | FTM1_MODE_VALUE_3;
    #endif
  #elif defined(FTM1_MODE_VALUE_3)
  FTM1_MODE = FTM1_MODE_VALUE_3;
  #endif

  /* Register 'FTM1_SYNCONF' initialization */
  #if FTM1_SYNCONF_MASK
    #if FTM1_SYNCONF_MASK == 0xFFFFFFFF
  FTM1_SYNCONF = FTM1_SYNCONF_VALUE;
    #elif FTM1_SYNCONF_MASK == FTM1_SYNCONF_VALUE
  FTM1_SYNCONF |= FTM1_SYNCONF_VALUE;
    #elif FTM1_SYNCONF_VALUE == 0
  FTM1_SYNCONF &= ~FTM1_SYNCONF_MASK;
    #else
  FTM1_SYNCONF = (FTM1_SYNCONF & (~FTM1_SYNCONF_MASK)) | FTM1_SYNCONF_VALUE;
    #endif
  #elif defined(FTM1_SYNCONF_VALUE)
  FTM1_SYNCONF = FTM1_SYNCONF_VALUE;
  #endif

  /* Register 'FTM1_SC' initialization */
  #if FTM1_SC_MASK_3
    #if FTM1_SC_MASK_3 == 0xFFFFFFFF
  FTM1_SC = FTM1_SC_VALUE_3;
    #elif FTM1_SC_MASK_3 == FTM1_SC_VALUE_3
  FTM1_SC |= FTM1_SC_VALUE_3;
    #elif FTM1_SC_VALUE_3 == 0
  FTM1_SC &= ~FTM1_SC_MASK_3;
    #else
  FTM1_SC = (FTM1_SC & (~FTM1_SC_MASK_3)) | FTM1_SC_VALUE_3;
    #endif
  #elif defined(FTM1_SC_VALUE_3)
  FTM1_SC = FTM1_SC_VALUE_3;
  #endif

  /* Register 'FTM1_FMS' initialization */
  #if FTM1_FMS_MASK
    #if FTM1_FMS_MASK == 0xFFFFFFFF
  FTM1_FMS = FTM1_FMS_VALUE;
    #elif FTM1_FMS_MASK == FTM1_FMS_VALUE
  FTM1_FMS |= FTM1_FMS_VALUE;
    #elif FTM1_FMS_VALUE == 0
  FTM1_FMS &= ~FTM1_FMS_MASK;
    #else
  FTM1_FMS = (FTM1_FMS & (~FTM1_FMS_MASK)) | FTM1_FMS_VALUE;
    #endif
  #elif defined(FTM1_FMS_VALUE)
  FTM1_FMS = FTM1_FMS_VALUE;
  #endif

  /* Register 'FTM1_QDCTRL' initialization */
  #ifdef FTM1_QDCTRL_VALUE
  FTM1_QDCTRL = FTM1_QDCTRL_VALUE;
  #endif

  /* Register 'FTM1_SWOCTRL' initialization */
  #if FTM1_SWOCTRL_MASK
    #if FTM1_SWOCTRL_MASK == 0xFFFFFFFF
  FTM1_SWOCTRL = FTM1_SWOCTRL_VALUE;
    #elif FTM1_SWOCTRL_MASK == FTM1_SWOCTRL_VALUE
  FTM1_SWOCTRL |= FTM1_SWOCTRL_VALUE;
    #elif FTM1_SWOCTRL_VALUE == 0
  FTM1_SWOCTRL &= ~FTM1_SWOCTRL_MASK;
    #else
  FTM1_SWOCTRL = (FTM1_SWOCTRL & (~FTM1_SWOCTRL_MASK)) | FTM1_SWOCTRL_VALUE;
    #endif
  #elif defined(FTM1_SWOCTRL_VALUE)
  FTM1_SWOCTRL = FTM1_SWOCTRL_VALUE;
  #endif

  /* Register 'FTM1_CONF' initialization */
  #if FTM1_CONF_MASK
    #if FTM1_CONF_MASK == 0xFFFFFFFF
  FTM1_CONF = FTM1_CONF_VALUE;
    #elif FTM1_CONF_MASK == FTM1_CONF_VALUE
  FTM1_CONF |= FTM1_CONF_VALUE;
    #elif FTM1_CONF_VALUE == 0
  FTM1_CONF &= ~FTM1_CONF_MASK;
    #else
  FTM1_CONF = (FTM1_CONF & (~FTM1_CONF_MASK)) | FTM1_CONF_VALUE;
    #endif
  #elif defined(FTM1_CONF_VALUE)
  FTM1_CONF = FTM1_CONF_VALUE;
  #endif

  /* Register 'FTM1_PWMLOAD' initialization */
  #if FTM1_PWMLOAD_MASK
    #if FTM1_PWMLOAD_MASK == 0xFFFFFFFF
  FTM1_PWMLOAD = FTM1_PWMLOAD_VALUE;
    #elif FTM1_PWMLOAD_MASK == FTM1_PWMLOAD_VALUE
  FTM1_PWMLOAD |= FTM1_PWMLOAD_VALUE;
    #elif FTM1_PWMLOAD_VALUE == 0
  FTM1_PWMLOAD &= ~FTM1_PWMLOAD_MASK;
    #else
  FTM1_PWMLOAD = (FTM1_PWMLOAD & (~FTM1_PWMLOAD_MASK)) | FTM1_PWMLOAD_VALUE;
    #endif
  #elif defined(FTM1_PWMLOAD_VALUE)
  FTM1_PWMLOAD = FTM1_PWMLOAD_VALUE;
  #endif
}

#ifdef __cplusplus
}
#endif

/* END FTM1_Init. */

/** ###################################################################
 **
 **     This file is a part of Processor Expert static initialization
 **     library for Freescale microcontrollers.
 **
 ** ################################################################### */
