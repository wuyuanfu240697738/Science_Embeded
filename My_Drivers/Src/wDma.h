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

/* Filename    : wDma.c*/

#ifndef __WY_DMA_H
#define __WY_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif
     
 /* Includes ------------------------------------------------------------------*/
  #include "wS.h"   
  #include "wgpio.h"     
 
HAL_StatusTypeDef wDma_Init(DMA_HandleTypeDef* hdma, 
                            DMA_Stream_TypeDef* Instance,
                            uint32_t Channel,
                            uint32_t Direction,
                            uint32_t DataAlignment,
                            uint32_t Mode,
                            uint32_t Priority);

#ifdef __cplusplus
}
#endif

#endif
