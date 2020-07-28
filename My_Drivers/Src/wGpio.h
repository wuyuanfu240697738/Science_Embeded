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

#define  wExti_Num     16u      /*Exti����*/

#ifndef GPIO_MODE_IT
    #define GPIO_MODE_IT          0x00010000U
#endif

typedef  enum {
    wLow=0,         //�͵�ƽ��Ч     
    wHigh=1,        //�ߵ�ƽ��Ч         
}wGpio_Level;                          
 
typedef  enum {
    wINACTIVE=0,    //��Ч��ƽ      
    wACTIVE=1,      //��Ч��ƽ  
    wERRACTIVE=0xff //�����ƽ
}wGpio_State; 

typedef  enum {
    Set_INACTIVE=0,    //��Ч��ƽ      
    Set_ACTIVE=1,      //��Ч��ƽ  
    Set_CHANGE=2       //�л���ƽ
}wGpio_Set; 

typedef  struct {
    GPIO_TypeDef*           GPIOx;           //����
    uint16_t                GPIO_Pin;        //����
    wFun                    EN;              //ʹ�ܿ��� 
    wGpio_Level             Level;           //��Ч��ƽ
}wGpio_Def;    


typedef  void (*ExtiCpltFnct)(uint16_t GPIO_Pin);//�ص�����
typedef  struct    wExti_def       wExti_Def;
struct  wExti_def{
    ExtiCpltFnct            CpltPtr;         //�ж�����ص�
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
