/*
********************************************************************************************************
*                                                wDrive-STM32
*                                       The Embedded STM32 Stack
*
*               Copyright: Wu HaiMeng. All rights reserved.Protected by international copyright laws.
*

* Programmer  : Wu YuanFu
* Version     : V2.10
* LICENSING TERMS:
* ---------------
*           wDrive-STM32 is provided in source form for FREE short-term evaluation, for educational use or
*           for peaceful research.  If you plan or intend to use wDrive-STM32 in a commercial application/
*           product then, you need to contact Wu YuanFu<240697738@qq.com> to properly license wDrive-STM32
*           for its use in your application/product.  The fact that the source is provided does NOT 
*           mean that you can use it commercially without paying a licensing fee.
*
*           Knowledge of the source code may NOT be used to develop a similar product.
*               
********************************************************************************************************
*/

/* Filename    : wSys.h*/

#ifndef __WY_SYS_H
#define __WY_SYS_H

#ifdef __cplusplus
 extern "C" {
#endif
     
    #include "wS.h"   
    #include "Cpucfg.h"    

#define CLOCK_8M    8
#define CLOCK_25M   25

uint8_t wSys_ClockConfig(uint32_t Clock,uint32_t Ticks);

uint32_t  wSys_GetClkFreq (void);

void wSys_Reset(uint32_t timeout);
uint8_t wSys_ResetCheck(void);

void wSys_DisAll(void);

#ifdef __cplusplus
}
#endif

#endif
