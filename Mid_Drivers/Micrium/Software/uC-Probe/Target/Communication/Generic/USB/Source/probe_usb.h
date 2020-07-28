/*
*********************************************************************************************************
*                                       uC/Probe Communication
*
*                         (c) Copyright 2007-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                         COMMUNICATION: USB
*
* Filename      : probe_usb.h
* Version       : V1.01
* Programmer(s) : JPB
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               PROBE_USB present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  PROBE_USB_PRESENT                                      /* See Note #1.                                         */
#define  PROBE_USB_PRESENT


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef    PROBE_USB_MODULE
#define   PROBE_USB_EXT
#else
#define   PROBE_USB_EXT  extern
#endif


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <probe_com.h>
#include  <probe_com_cfg.h>


/*
*********************************************************************************************************
*                                               ENABLE
*
* Note(s) : (1) USB communication is enabled/disabled via the PROBE_COM_CFG_USB_EN configuration define
*               (see 'probe_com_cfg.h  COMMUNICATION MODULE CONFIGURATION').
*********************************************************************************************************
*/

#if (PROBE_COM_CFG_USB_EN == DEF_ENABLED)                       /* See Note #1.                                         */


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

CPU_BOOLEAN  ProbeUSB_Init   (CPU_INT08U  dev_nbr,
                              CPU_INT08U  cfg_hs,
                              CPU_INT08U  cfg_fs);
void         ProbeUSB_Task   (CPU_INT08U  class_nbr);

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*                                   DEFINED IN OS's probe_usb_os.c
*********************************************************************************************************
*/

void         ProbeUSB_OS_Init(CPU_INT08U  class_nbr);


/*
*********************************************************************************************************
*                                          CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  PROBE_USB_CFG_TASK_PRIO
#error  "PROBE_USB_CFG_TASK_PRIO               not #define'd in 'probe_com_cfg.h'  "
#endif

#ifndef  PROBE_USB_CFG_TASK_STK_SIZE
#error  "PROBE_USB_CFG_TASK_STK_SIZE           not #define'd in 'probe_com_cfg.h'  "
#endif


#ifndef  PROBE_USB_CFG_RX_BUF_SIZE
#error  "PROBE_USB_CFG_RX_BUF_SIZE             not #define'd in 'probe_com_cfg.h'  "
#error  "                                [MUST be  >= 32   ]                       "
#error  "                                [     &&  <= 65535]                       "

#elif  ((PROBE_USB_CFG_RX_BUF_SIZE > 65535) || \
        (PROBE_USB_CFG_RX_BUF_SIZE < 32   ))
#error  "PROBE_USB_CFG_RX_BUF_SIZE       illegally #define'd in 'probe_com_cfg.h'  "
#error  "                                [MUST be  >= 32   ]                       "
#error  "                                [     &&  <= 65535]                       "
#endif


#ifndef  PROBE_USB_CFG_TX_BUF_SIZE
#error  "PROBE_USB_CFG_TX_BUF_SIZE             not #define'd in 'probe_com_cfg.h'  "
#error  "                                [MUST be  >= 32   ]                       "
#error  "                                [     &&  <= 65535]                       "

#elif  ((PROBE_USB_CFG_TX_BUF_SIZE > 65535) || \
        (PROBE_USB_CFG_TX_BUF_SIZE < 32   ))
#error  "PROBE_USB_CFG_TX_BUF_SIZE       illegally #define'd in 'probe_com_cfg.h'  "
#error  "                                [MUST be  >= 32   ]                       "
#error  "                                [     &&  <= 65535]                       "
#endif


/*
*********************************************************************************************************
*                                              ENABLE END
*
* Note(s) : See 'ENABLE  Note #1'.
*********************************************************************************************************
*/

#endif


/*
*********************************************************************************************************
*                                             MODULE END
*
* Note(s) : See 'MODULE  Note #1'.
*********************************************************************************************************
*/

#endif                                                          /* End of PROBE_USB module include (see Note #1).     */
