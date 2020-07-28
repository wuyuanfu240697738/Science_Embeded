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

/* Filename    : wGpio.h*/

#ifndef __WY_GPIO_H
#define __WY_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

    #include "wS.h"  

#define  wExti_Num     16u      /*Exti数量*/

#ifndef GPIO_MODE_IT
    #define GPIO_MODE_IT          0x00010000U
#endif

typedef  enum {
    wLow=0,         //低电平有效     
    wHigh=1,        //高电平有效         
}wGpio_Level;                          
 
typedef  enum {
    wINACTIVE=0,    //无效电平      
    wACTIVE=1,      //有效电平  
    wERRACTIVE=0xff //错误电平
}wGpio_State; 

typedef  enum {
    Set_INACTIVE=0,    //无效电平      
    Set_ACTIVE=1,      //有效电平  
    Set_CHANGE=2       //切换电平
}wGpio_Set; 

typedef  struct {
    GPIO_TypeDef*           GPIOx;           //引脚
    uint16_t                GPIO_Pin;        //引脚
    wFun                    EN;              //使能开关 
    wGpio_Level             Level;           //有效电平
}wGpio_Def;    


typedef  void (*ExtiCpltFnct)(uint16_t GPIO_Pin);//回调函数
typedef  struct    wExti_def       wExti_Def;
struct  wExti_def{
    ExtiCpltFnct            CpltPtr;         //中断输入回调
};
void wExti_SetCallback(uint16_t GPIO_Pin,ExtiCpltFnct CpltPtr);

 uint16_t wGpio_Init(wPin pin,uint32_t Mode,uint32_t Pull,uint32_t Speed,uint32_t Alternate);
 void wGpio_putInit(wGpio_Def* wGPIO,wPin pin,uint32_t Mode,uint32_t Pull,uint32_t Speed,wGpio_Level level); 
 void wGpio_putWrite(wGpio_Def* wGPIO,wGpio_Set CurState);  
 wGpio_State wGpio_putRead(wGpio_Def* wGPIO);  
     
#ifdef __cplusplus
}
#endif

#endif 
