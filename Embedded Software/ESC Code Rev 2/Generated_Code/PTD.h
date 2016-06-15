/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : PTD.h
**     Project     : ProcessorExpert
**     Processor   : MKL25Z64VLK4
**     Component   : Init_GPIO
**     Version     : Component 01.004, Driver 01.04, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-09-24, 20:29, # CodeGen: 8
**     Abstract    :
**          This file implements the GPIO (PTD) module initialization
**          according to the Peripheral Initialization settings, and
**          defines interrupt service routines prototypes.
**     Settings    :
**          Component name                                 : PTD
**          Device                                         : PTD
**          Settings                                       : 
**            Pin 0                                        : Do not initialize
**            Pin 1                                        : Do not initialize
**            Pin 2                                        : Do not initialize
**            Pin 3                                        : Do not initialize
**            Pin 4                                        : Do not initialize
**            Pin 5                                        : Do not initialize
**            Pin 6                                        : Do not initialize
**            Pin 7                                        : Do not initialize
**          Pins                                           : 
**            Pin 0                                        : Disabled
**            Pin 1                                        : Disabled
**            Pin 2                                        : Disabled
**            Pin 3                                        : Disabled
**            Pin 4                                        : Disabled
**            Pin 5                                        : Disabled
**            Pin 6                                        : Disabled
**            Pin 7                                        : Disabled
**          Interrupts                                     : 
**            Port interrupt                               : Disabled
**          Initialization                                 : 
**            Call Init method                             : yes
**     Contents    :
**         Init - void PTD_Init(void);
**
**     Copyright : 1997 - 2013 Freescale Semiconductor, Inc. All Rights Reserved.
**     SOURCE DISTRIBUTION PERMISSIBLE as directed in End User License Agreement.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
/*!
** @file PTD.h
** @version 01.04
** @brief
**          This file implements the GPIO (PTD) module initialization
**          according to the Peripheral Initialization settings, and
**          defines interrupt service routines prototypes.
*/         
/*!
**  @addtogroup PTD_module PTD module documentation
**  @{
*/         

#ifndef PTD_H_
#define PTD_H_

/* MODULE PTD. */

/* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"

/* Peripheral base address parameter */
#define PTD_DEVICE PTD_BASE_PTR

/* Peripheral port base address parameter */
#define PTD_PORT_DEVICE PORTD_BASE_PTR



/*
** ===================================================================
**     Method      :  PTD_Init (component Init_GPIO)
**     Description :
**         This method initializes registers of the GPIO module
**         according to the Peripheral Initialization settings.
**         Call this method in user code to initialize the module. By
**         default, the method is called by PE automatically; see "Call
**         Init method" property of the component for more details.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void PTD_Init(void);


/* END PTD. */
#endif /* #ifndef __PTD_H_ */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.08]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/