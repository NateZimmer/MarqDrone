/** ###################################################################
 **     Filename    : FTM2_Init.c
 **     Processor   : MK22FN512LH12
 **     Abstract    :
 **          This file implements the FTM2 module initialization
 **          according to the Peripheral Initialization settings, and
 **          defines interrupt service routines prototypes.
 **
 **     Contents    :
 **         Int   - void FTM2_Init(void);
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
 * @file FTM2_Init.c
 * @brief This file implements the FTM2 module initialization according to the
 *        Peripheral Initialization settings, and defines interrupt service
 *        routines prototypes.
 */


/* MODULE FTM2_Init. */

#include "FTM2_Init.h"
#include "MK22F51212.h"
#include "Init_Config.h"

#ifdef __cplusplus
extern "C" {
#endif

void FTM2_Init(void) {
  (void)FTM2_SC;  /* Dummy read of the Control Status register to clear the interrupt flag */
  FTM2_SC = 0;  /* Stop the counter */
  #ifdef FTM2_C0SC
  (void)FTM2_C0SC; /* Dummy read of the Channel Status and Control 0 register to clear the interrupt flag */
  #endif
  #ifdef FTM2_C1SC
  (void)FTM2_C1SC; /* Dummy read of the Channel Status and Control 1 register to clear the interrupt flag */
  #endif
  #ifdef FTM2_C2SC
  (void)FTM2_C2SC; /* Dummy read of the Channel Status and Control 2 register to clear the interrupt flag */
  #endif
  #ifdef FTM2_C3SC
  (void)FTM2_C3SC; /* Dummy read of the Channel Status and Control 3 register to clear the interrupt flag */
  #endif
  #ifdef FTM2_C4SC
  (void)FTM2_C4SC; /* Dummy read of the Channel Status and Control 4 register to clear the interrupt flag */
  #endif
  #ifdef FTM2_C5SC
  (void)FTM2_C5SC; /* Dummy read of the Channel Status and Control 5 register to clear the interrupt flag */
  #endif
  #ifdef FTM2_C6SC
  (void)FTM2_C6SC; /* Dummy read of the Channel Status and Control 6 register to clear the interrupt flag */
  #endif
  #ifdef FTM2_C7SC
  (void)FTM2_C7SC; /* Dummy read of the Channel Status and Control 7 register to clear the interrupt flag */
  #endif
  #ifdef FTM2_MODE_VALUE_1
  FTM2_MODE |= FTM2_MODE_VALUE_1; /* Disable write protection */
  #endif

  FTM2_C0SC = 0;

  FTM2_C1SC = 0;

  /* Register 'FTM2_SC' initialization */
  #if FTM2_SC_MASK_2
    #if FTM2_SC_MASK_2 == 0xFFFFFFFF
  FTM2_SC = FTM2_SC_VALUE_2;
    #elif FTM2_SC_MASK_2 == FTM2_SC_VALUE_2
  FTM2_SC |= FTM2_SC_VALUE_2;
    #elif FTM2_SC_VALUE_2 == 0
  FTM2_SC &= ~FTM2_SC_MASK_2;
    #else
  FTM2_SC = (FTM2_SC & (~FTM2_SC_MASK_2)) | FTM2_SC_VALUE_2;
    #endif
  #elif defined(FTM2_SC_VALUE_2)
  FTM2_SC = FTM2_SC_VALUE_2;
  #endif

  /* Register 'FTM2_MODE' initialization */
  #if FTM2_MODE_MASK_2
    #if FTM2_MODE_MASK_2 == 0xFFFFFFFF
  FTM2_MODE = FTM2_MODE_VALUE_2;
    #elif FTM2_MODE_MASK_2 == FTM2_MODE_VALUE_2
  FTM2_MODE |= FTM2_MODE_VALUE_2;
    #elif FTM2_MODE_VALUE_2 == 0
  FTM2_MODE &= ~FTM2_MODE_MASK_2;
    #else
  FTM2_MODE = (FTM2_MODE & (~FTM2_MODE_MASK_2)) | FTM2_MODE_VALUE_2;
    #endif
  #elif defined(FTM2_MODE_VALUE_2)
  FTM2_MODE = FTM2_MODE_VALUE_2;
  #endif

  /* Register 'FTM2_COMBINE' initialization */
  #if FTM2_COMBINE_MASK
    #if FTM2_COMBINE_MASK == 0xFFFFFFFF
  FTM2_COMBINE = FTM2_COMBINE_VALUE;
    #elif FTM2_COMBINE_MASK == FTM2_COMBINE_VALUE
  FTM2_COMBINE |= FTM2_COMBINE_VALUE;
    #elif FTM2_COMBINE_VALUE == 0
  FTM2_COMBINE &= ~FTM2_COMBINE_MASK;
    #else
  FTM2_COMBINE = (FTM2_COMBINE & (~FTM2_COMBINE_MASK)) | FTM2_COMBINE_VALUE;
    #endif
  #elif defined(FTM2_COMBINE_VALUE)
  FTM2_COMBINE = FTM2_COMBINE_VALUE;
  #endif

  /* Register 'FTM2_INVCTRL' initialization */
  #if FTM2_INVCTRL_MASK
    #if FTM2_INVCTRL_MASK == 0xFFFFFFFF
  FTM2_INVCTRL = FTM2_INVCTRL_VALUE;
    #elif FTM2_INVCTRL_MASK == FTM2_INVCTRL_VALUE
  FTM2_INVCTRL |= FTM2_INVCTRL_VALUE;
    #elif FTM2_INVCTRL_VALUE == 0
  FTM2_INVCTRL &= ~FTM2_INVCTRL_MASK;
    #else
  FTM2_INVCTRL = (FTM2_INVCTRL & (~FTM2_INVCTRL_MASK)) | FTM2_INVCTRL_VALUE;
    #endif
  #elif defined(FTM2_INVCTRL_VALUE)
  FTM2_INVCTRL = FTM2_INVCTRL_VALUE;
  #endif

  /* Register 'FTM2_C0SC' initialization */
  #if FTM2_C0SC_MASK
    #if FTM2_C0SC_MASK == 0xFFFFFFFF
  FTM2_C0SC = FTM2_C0SC_VALUE;
    #elif FTM2_C0SC_MASK == FTM2_C0SC_VALUE
  FTM2_C0SC |= FTM2_C0SC_VALUE;
    #elif FTM2_C0SC_VALUE == 0
  FTM2_C0SC &= ~FTM2_C0SC_MASK;
    #else
  FTM2_C0SC = (FTM2_C0SC & (~FTM2_C0SC_MASK)) | FTM2_C0SC_VALUE;
    #endif
  #elif defined(FTM2_C0SC_VALUE)
  FTM2_C0SC = FTM2_C0SC_VALUE;
  #endif

  /* Register 'FTM2_C1SC' initialization */
  #if FTM2_C1SC_MASK
    #if FTM2_C1SC_MASK == 0xFFFFFFFF
  FTM2_C1SC = FTM2_C1SC_VALUE;
    #elif FTM2_C1SC_MASK == FTM2_C1SC_VALUE
  FTM2_C1SC |= FTM2_C1SC_VALUE;
    #elif FTM2_C1SC_VALUE == 0
  FTM2_C1SC &= ~FTM2_C1SC_MASK;
    #else
  FTM2_C1SC = (FTM2_C1SC & (~FTM2_C1SC_MASK)) | FTM2_C1SC_VALUE;
    #endif
  #elif defined(FTM2_C1SC_VALUE)
  FTM2_C1SC = FTM2_C1SC_VALUE;
  #endif

  /* Register 'FTM2_C0V' initialization */
  #if FTM2_C0V_MASK
    #if FTM2_C0V_MASK == 0xFFFFFFFF
  FTM2_C0V = FTM2_C0V_VALUE;
    #elif FTM2_C0V_MASK == FTM2_C0V_VALUE
  FTM2_C0V |= FTM2_C0V_VALUE;
    #elif FTM2_C0V_VALUE == 0
  FTM2_C0V &= ~FTM2_C0V_MASK;
    #else
  FTM2_C0V = (FTM2_C0V & (~FTM2_C0V_MASK)) | FTM2_C0V_VALUE;
    #endif
  #elif defined(FTM2_C0V_VALUE)
  FTM2_C0V = FTM2_C0V_VALUE;
  #endif

  /* Register 'FTM2_C1V' initialization */
  #if FTM2_C1V_MASK
    #if FTM2_C1V_MASK == 0xFFFFFFFF
  FTM2_C1V = FTM2_C1V_VALUE;
    #elif FTM2_C1V_MASK == FTM2_C1V_VALUE
  FTM2_C1V |= FTM2_C1V_VALUE;
    #elif FTM2_C1V_VALUE == 0
  FTM2_C1V &= ~FTM2_C1V_MASK;
    #else
  FTM2_C1V = (FTM2_C1V & (~FTM2_C1V_MASK)) | FTM2_C1V_VALUE;
    #endif
  #elif defined(FTM2_C1V_VALUE)
  FTM2_C1V = FTM2_C1V_VALUE;
  #endif

  /* Register 'FTM2_POL' initialization */
  #if FTM2_POL_MASK
    #if FTM2_POL_MASK == 0xFFFFFFFF
  FTM2_POL = FTM2_POL_VALUE;
    #elif FTM2_POL_MASK == FTM2_POL_VALUE
  FTM2_POL |= FTM2_POL_VALUE;
    #elif FTM2_POL_VALUE == 0
  FTM2_POL &= ~FTM2_POL_MASK;
    #else
  FTM2_POL = (FTM2_POL & (~FTM2_POL_MASK)) | FTM2_POL_VALUE;
    #endif
  #elif defined(FTM2_POL_VALUE)
  FTM2_POL = FTM2_POL_VALUE;
  #endif

  /* Register 'FTM2_FILTER' initialization */
  #if FTM2_FILTER_MASK
    #if FTM2_FILTER_MASK == 0xFFFFFFFF
  FTM2_FILTER = FTM2_FILTER_VALUE;
    #elif FTM2_FILTER_MASK == FTM2_FILTER_VALUE
  FTM2_FILTER |= FTM2_FILTER_VALUE;
    #elif FTM2_FILTER_VALUE == 0
  FTM2_FILTER &= ~FTM2_FILTER_MASK;
    #else
  FTM2_FILTER = (FTM2_FILTER & (~FTM2_FILTER_MASK)) | FTM2_FILTER_VALUE;
    #endif
  #elif defined(FTM2_FILTER_VALUE)
  FTM2_FILTER = FTM2_FILTER_VALUE;
  #endif

  /* Register 'FTM2_OUTINIT' initialization */
  #if FTM2_OUTINIT_MASK
    #if FTM2_OUTINIT_MASK == 0xFFFFFFFF
  FTM2_OUTINIT = FTM2_OUTINIT_VALUE;
    #elif FTM2_OUTINIT_MASK == FTM2_OUTINIT_VALUE
  FTM2_OUTINIT |= FTM2_OUTINIT_VALUE;
    #elif FTM2_OUTINIT_VALUE == 0
  FTM2_OUTINIT &= ~FTM2_OUTINIT_MASK;
    #else
  FTM2_OUTINIT = (FTM2_OUTINIT & (~FTM2_OUTINIT_MASK)) | FTM2_OUTINIT_VALUE;
    #endif
  #elif defined(FTM2_OUTINIT_VALUE)
  FTM2_OUTINIT = FTM2_OUTINIT_VALUE;
  #endif

  /* Register 'FTM2_OUTMASK' initialization */
  #if FTM2_OUTMASK_MASK
    #if FTM2_OUTMASK_MASK == 0xFFFFFFFF
  FTM2_OUTMASK = FTM2_OUTMASK_VALUE;
    #elif FTM2_OUTMASK_MASK == FTM2_OUTMASK_VALUE
  FTM2_OUTMASK |= FTM2_OUTMASK_VALUE;
    #elif FTM2_OUTMASK_VALUE == 0
  FTM2_OUTMASK &= ~FTM2_OUTMASK_MASK;
    #else
  FTM2_OUTMASK = (FTM2_OUTMASK & (~FTM2_OUTMASK_MASK)) | FTM2_OUTMASK_VALUE;
    #endif
  #elif defined(FTM2_OUTMASK_VALUE)
  FTM2_OUTMASK = FTM2_OUTMASK_VALUE;
  #endif

  /* Register 'FTM2_FLTCTRL' initialization */
  #if FTM2_FLTCTRL_MASK_1
    #if FTM2_FLTCTRL_MASK_1 == 0xFFFFFFFF
  FTM2_FLTCTRL = FTM2_FLTCTRL_VALUE_1;
    #elif FTM2_FLTCTRL_MASK_1 == FTM2_FLTCTRL_VALUE_1
  FTM2_FLTCTRL |= FTM2_FLTCTRL_VALUE_1;
    #elif FTM2_FLTCTRL_VALUE_1 == 0
  FTM2_FLTCTRL &= ~FTM2_FLTCTRL_MASK_1;
    #else
  FTM2_FLTCTRL = (FTM2_FLTCTRL & (~FTM2_FLTCTRL_MASK_1)) | FTM2_FLTCTRL_VALUE_1;
    #endif
  #elif defined(FTM2_FLTCTRL_VALUE_1)
  FTM2_FLTCTRL = FTM2_FLTCTRL_VALUE_1;
  #endif

  /* Register 'FTM2_FLTPOL' initialization */
  #if FTM2_FLTPOL_MASK
    #if FTM2_FLTPOL_MASK == 0xFFFFFFFF
  FTM2_FLTPOL = FTM2_FLTPOL_VALUE;
    #elif FTM2_FLTPOL_MASK == FTM2_FLTPOL_VALUE
  FTM2_FLTPOL |= FTM2_FLTPOL_VALUE;
    #elif FTM2_FLTPOL_VALUE == 0
  FTM2_FLTPOL &= ~FTM2_FLTPOL_MASK;
    #else
  FTM2_FLTPOL = (FTM2_FLTPOL & (~FTM2_FLTPOL_MASK)) | FTM2_FLTPOL_VALUE;
    #endif
  #elif defined(FTM2_FLTPOL_VALUE)
  FTM2_FLTPOL = FTM2_FLTPOL_VALUE;
  #endif

  /* Register 'FTM2_FLTCTRL' initialization */
  #if FTM2_FLTCTRL_MASK_2
    #if FTM2_FLTCTRL_MASK_2 == 0xFFFFFFFF
  FTM2_FLTCTRL = FTM2_FLTCTRL_VALUE_2;
    #elif FTM2_FLTCTRL_MASK_2 == FTM2_FLTCTRL_VALUE_2
  FTM2_FLTCTRL |= FTM2_FLTCTRL_VALUE_2;
    #elif FTM2_FLTCTRL_VALUE_2 == 0
  FTM2_FLTCTRL &= ~FTM2_FLTCTRL_MASK_2;
    #else
  FTM2_FLTCTRL = (FTM2_FLTCTRL & (~FTM2_FLTCTRL_MASK_2)) | FTM2_FLTCTRL_VALUE_2;
    #endif
  #elif defined(FTM2_FLTCTRL_VALUE_2)
  FTM2_FLTCTRL = FTM2_FLTCTRL_VALUE_2;
  #endif

  /* Register 'FTM2_SYNC' initialization */
  #if FTM2_SYNC_MASK
    #if FTM2_SYNC_MASK == 0xFFFFFFFF
  FTM2_SYNC = FTM2_SYNC_VALUE;
    #elif FTM2_SYNC_MASK == FTM2_SYNC_VALUE
  FTM2_SYNC |= FTM2_SYNC_VALUE;
    #elif FTM2_SYNC_VALUE == 0
  FTM2_SYNC &= ~FTM2_SYNC_MASK;
    #else
  FTM2_SYNC = (FTM2_SYNC & (~FTM2_SYNC_MASK)) | FTM2_SYNC_VALUE;
    #endif
  #elif defined(FTM2_SYNC_VALUE)
  FTM2_SYNC = FTM2_SYNC_VALUE;
  #endif

  /* Register 'FTM2_EXTTRIG' initialization */
  #if FTM2_EXTTRIG_MASK
    #if FTM2_EXTTRIG_MASK == 0xFFFFFFFF
  FTM2_EXTTRIG = FTM2_EXTTRIG_VALUE;
    #elif FTM2_EXTTRIG_MASK == FTM2_EXTTRIG_VALUE
  FTM2_EXTTRIG |= FTM2_EXTTRIG_VALUE;
    #elif FTM2_EXTTRIG_VALUE == 0
  FTM2_EXTTRIG &= ~FTM2_EXTTRIG_MASK;
    #else
  FTM2_EXTTRIG = (FTM2_EXTTRIG & (~FTM2_EXTTRIG_MASK)) | FTM2_EXTTRIG_VALUE;
    #endif
  #elif defined(FTM2_EXTTRIG_VALUE)
  FTM2_EXTTRIG = FTM2_EXTTRIG_VALUE;
  #endif

  /* Register 'FTM2_MOD' initialization */
  #if FTM2_MOD_MASK
    #if FTM2_MOD_MASK == 0xFFFFFFFF
  FTM2_MOD = FTM2_MOD_VALUE;
    #elif FTM2_MOD_MASK == FTM2_MOD_VALUE
  FTM2_MOD |= FTM2_MOD_VALUE;
    #elif FTM2_MOD_VALUE == 0
  FTM2_MOD &= ~FTM2_MOD_MASK;
    #else
  FTM2_MOD = (FTM2_MOD & (~FTM2_MOD_MASK)) | FTM2_MOD_VALUE;
    #endif
  #elif defined(FTM2_MOD_VALUE)
  FTM2_MOD = FTM2_MOD_VALUE;
  #endif

  /* Register 'FTM2_CNTIN' initialization */
  #if FTM2_CNTIN_MASK
    #if FTM2_CNTIN_MASK == 0xFFFFFFFF
  FTM2_CNTIN = FTM2_CNTIN_VALUE;
    #elif FTM2_CNTIN_MASK == FTM2_CNTIN_VALUE
  FTM2_CNTIN |= FTM2_CNTIN_VALUE;
    #elif FTM2_CNTIN_VALUE == 0
  FTM2_CNTIN &= ~FTM2_CNTIN_MASK;
    #else
  FTM2_CNTIN = (FTM2_CNTIN & (~FTM2_CNTIN_MASK)) | FTM2_CNTIN_VALUE;
    #endif
  #elif defined(FTM2_CNTIN_VALUE)
  FTM2_CNTIN = FTM2_CNTIN_VALUE;
  #endif

  /* Register 'FTM2_DEADTIME' initialization */
  #if FTM2_DEADTIME_MASK
    #if FTM2_DEADTIME_MASK == 0xFFFFFFFF
  FTM2_DEADTIME = FTM2_DEADTIME_VALUE;
    #elif FTM2_DEADTIME_MASK == FTM2_DEADTIME_VALUE
  FTM2_DEADTIME |= FTM2_DEADTIME_VALUE;
    #elif FTM2_DEADTIME_VALUE == 0
  FTM2_DEADTIME &= ~FTM2_DEADTIME_MASK;
    #else
  FTM2_DEADTIME = (FTM2_DEADTIME & (~FTM2_DEADTIME_MASK)) | FTM2_DEADTIME_VALUE;
    #endif
  #elif defined(FTM2_DEADTIME_VALUE)
  FTM2_DEADTIME = FTM2_DEADTIME_VALUE;
  #endif

  FTM2_CNT &= ~0xFFFF;

  /* Register 'FTM2_MODE' initialization */
  #if FTM2_MODE_MASK_3
    #if FTM2_MODE_MASK_3 == 0xFFFFFFFF
  FTM2_MODE = FTM2_MODE_VALUE_3;
    #elif FTM2_MODE_MASK_3 == FTM2_MODE_VALUE_3
  FTM2_MODE |= FTM2_MODE_VALUE_3;
    #elif FTM2_MODE_VALUE_3 == 0
  FTM2_MODE &= ~FTM2_MODE_MASK_3;
    #else
  FTM2_MODE = (FTM2_MODE & (~FTM2_MODE_MASK_3)) | FTM2_MODE_VALUE_3;
    #endif
  #elif defined(FTM2_MODE_VALUE_3)
  FTM2_MODE = FTM2_MODE_VALUE_3;
  #endif

  /* Register 'FTM2_SYNCONF' initialization */
  #if FTM2_SYNCONF_MASK
    #if FTM2_SYNCONF_MASK == 0xFFFFFFFF
  FTM2_SYNCONF = FTM2_SYNCONF_VALUE;
    #elif FTM2_SYNCONF_MASK == FTM2_SYNCONF_VALUE
  FTM2_SYNCONF |= FTM2_SYNCONF_VALUE;
    #elif FTM2_SYNCONF_VALUE == 0
  FTM2_SYNCONF &= ~FTM2_SYNCONF_MASK;
    #else
  FTM2_SYNCONF = (FTM2_SYNCONF & (~FTM2_SYNCONF_MASK)) | FTM2_SYNCONF_VALUE;
    #endif
  #elif defined(FTM2_SYNCONF_VALUE)
  FTM2_SYNCONF = FTM2_SYNCONF_VALUE;
  #endif

  /* Register 'FTM2_SC' initialization */
  #if FTM2_SC_MASK_3
    #if FTM2_SC_MASK_3 == 0xFFFFFFFF
  FTM2_SC = FTM2_SC_VALUE_3;
    #elif FTM2_SC_MASK_3 == FTM2_SC_VALUE_3
  FTM2_SC |= FTM2_SC_VALUE_3;
    #elif FTM2_SC_VALUE_3 == 0
  FTM2_SC &= ~FTM2_SC_MASK_3;
    #else
  FTM2_SC = (FTM2_SC & (~FTM2_SC_MASK_3)) | FTM2_SC_VALUE_3;
    #endif
  #elif defined(FTM2_SC_VALUE_3)
  FTM2_SC = FTM2_SC_VALUE_3;
  #endif

  /* Register 'FTM2_FMS' initialization */
  #if FTM2_FMS_MASK
    #if FTM2_FMS_MASK == 0xFFFFFFFF
  FTM2_FMS = FTM2_FMS_VALUE;
    #elif FTM2_FMS_MASK == FTM2_FMS_VALUE
  FTM2_FMS |= FTM2_FMS_VALUE;
    #elif FTM2_FMS_VALUE == 0
  FTM2_FMS &= ~FTM2_FMS_MASK;
    #else
  FTM2_FMS = (FTM2_FMS & (~FTM2_FMS_MASK)) | FTM2_FMS_VALUE;
    #endif
  #elif defined(FTM2_FMS_VALUE)
  FTM2_FMS = FTM2_FMS_VALUE;
  #endif

  /* Register 'FTM2_QDCTRL' initialization */
  #ifdef FTM2_QDCTRL_VALUE
  FTM2_QDCTRL = FTM2_QDCTRL_VALUE;
  #endif

  /* Register 'FTM2_SWOCTRL' initialization */
  #if FTM2_SWOCTRL_MASK
    #if FTM2_SWOCTRL_MASK == 0xFFFFFFFF
  FTM2_SWOCTRL = FTM2_SWOCTRL_VALUE;
    #elif FTM2_SWOCTRL_MASK == FTM2_SWOCTRL_VALUE
  FTM2_SWOCTRL |= FTM2_SWOCTRL_VALUE;
    #elif FTM2_SWOCTRL_VALUE == 0
  FTM2_SWOCTRL &= ~FTM2_SWOCTRL_MASK;
    #else
  FTM2_SWOCTRL = (FTM2_SWOCTRL & (~FTM2_SWOCTRL_MASK)) | FTM2_SWOCTRL_VALUE;
    #endif
  #elif defined(FTM2_SWOCTRL_VALUE)
  FTM2_SWOCTRL = FTM2_SWOCTRL_VALUE;
  #endif

  /* Register 'FTM2_CONF' initialization */
  #if FTM2_CONF_MASK
    #if FTM2_CONF_MASK == 0xFFFFFFFF
  FTM2_CONF = FTM2_CONF_VALUE;
    #elif FTM2_CONF_MASK == FTM2_CONF_VALUE
  FTM2_CONF |= FTM2_CONF_VALUE;
    #elif FTM2_CONF_VALUE == 0
  FTM2_CONF &= ~FTM2_CONF_MASK;
    #else
  FTM2_CONF = (FTM2_CONF & (~FTM2_CONF_MASK)) | FTM2_CONF_VALUE;
    #endif
  #elif defined(FTM2_CONF_VALUE)
  FTM2_CONF = FTM2_CONF_VALUE;
  #endif

  /* Register 'FTM2_PWMLOAD' initialization */
  #if FTM2_PWMLOAD_MASK
    #if FTM2_PWMLOAD_MASK == 0xFFFFFFFF
  FTM2_PWMLOAD = FTM2_PWMLOAD_VALUE;
    #elif FTM2_PWMLOAD_MASK == FTM2_PWMLOAD_VALUE
  FTM2_PWMLOAD |= FTM2_PWMLOAD_VALUE;
    #elif FTM2_PWMLOAD_VALUE == 0
  FTM2_PWMLOAD &= ~FTM2_PWMLOAD_MASK;
    #else
  FTM2_PWMLOAD = (FTM2_PWMLOAD & (~FTM2_PWMLOAD_MASK)) | FTM2_PWMLOAD_VALUE;
    #endif
  #elif defined(FTM2_PWMLOAD_VALUE)
  FTM2_PWMLOAD = FTM2_PWMLOAD_VALUE;
  #endif
}

#ifdef __cplusplus
}
#endif

/* END FTM2_Init. */

/** ###################################################################
 **
 **     This file is a part of Processor Expert static initialization
 **     library for Freescale microcontrollers.
 **
 ** ################################################################### */
