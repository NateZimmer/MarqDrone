/* ###################################################################
**     Filename    : Events.h
**     Project     : ESC_Code
**     Processor   : MKL25Z64VLH4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-10-28, 20:20, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "TPM1.h"
#include "CMP0.h"
#include "TPM2.h"
#include "CS1.h"
#include "TPM0.h"
#include "WAIT1.h"
#include "PIT.h"
#include "PTB.h"
#include "PTD.h"

#ifdef __cplusplus
extern "C" {
#endif 

void AD1_OnEnd(void);
/*
** ===================================================================
**     Event       :  AD1_OnEnd (module Events)
**
**     Component   :  AD1 [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  Cpu_OnLowVoltageINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when Low Voltage interrupt had occured.
**         This event is automatically enabled when either [LVD
**         interrupt] is set to 'Enabled' and [LVD reset] is set to
**         'Disabled' or [LVW interrupt] is set to 'Enabled'.
**     @param
**         Reason          - The parameter defines the reason of
**                           the low voltage interrupt. You can use
**                           predefined constants LVDSRC_* defined in
**                           generated PE_Const.h file to determine a
**                           reason of the last reset. See definition of
**                           these constants in this file for details.
*/
/* ===================================================================*/
void Cpu_OnLowVoltageINT(uint8_t Reason);

/*
** ===================================================================
**     Event       :  Cpu_OnHardFault (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Hard Fault exception had
**         occurred. This event is automatically enabled when the [Hard
**         Fault] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnHardFault(void);

/*
** ===================================================================
**     Event       :  Cpu_OnSupervisorCall (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Supervisor Call exception had
**         occurred. This event is automatically enabled when the
**         [Supervisor Call] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnSupervisorCall(void);

/*
** ===================================================================
**     Event       :  Cpu_OnPendableService (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Pendable Service exception had
**         occurred. This event is automatically enabled when the
**         [Pendable Service] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnPendableService(void);

/*
** ===================================================================
**     Event       :  Cpu_OnLossOfLockINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when Loss of Lock interrupt had occured.
**         This event is automatically enabled when either [Loss of
**         lock interrupt] is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnLossOfLockINT(void);

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void);

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
