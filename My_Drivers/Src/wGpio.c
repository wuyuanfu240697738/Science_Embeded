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

/* Filename    : wGpio.c*/

#include "wGpio.h"
#include "wIt.h" 
#include "os.h" 

static wExti_Def wExti[16];

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint8_t n;
    switch(GPIO_Pin)
    {
        case GPIO_PIN_0:    {n = 0 ;}break;
        case GPIO_PIN_1:    {n = 1 ;}break;	
        case GPIO_PIN_2:    {n = 2 ;}break;
        case GPIO_PIN_3:    {n = 3 ;}break;	
        case GPIO_PIN_4:    {n = 4 ;}break; 
        case GPIO_PIN_5:    {n = 5 ;}break;
        case GPIO_PIN_6:    {n = 6 ;}break;     
        case GPIO_PIN_7:    {n = 7 ;}break;
        case GPIO_PIN_8:    {n = 8 ;}break;     
        case GPIO_PIN_9:    {n = 9 ;}break;
        case GPIO_PIN_10:   {n = 10;}break;
        case GPIO_PIN_11:   {n = 11;}break;    
        case GPIO_PIN_12:   {n = 12;}break;
        case GPIO_PIN_13:   {n = 13;}break;     
        case GPIO_PIN_14:   {n = 14;}break; 
        case GPIO_PIN_15:   {n = 15;}break;     
        default:            {n = 16;}break;   
    }
    if(n < 16 )
    {
        wExti[n].CpltPtr(GPIO_Pin);
    }         
}

void wExti_SetCallback(uint16_t GPIO_Pin,ExtiCpltFnct CpltPtr)
{
    if(CpltPtr != (ExtiCpltFnct)0)
    {
        switch(GPIO_Pin)
        {
            case GPIO_PIN_0:
            {
                wExti[0].CpltPtr = CpltPtr;              
            }break;
            case GPIO_PIN_1:
            {
                wExti[1].CpltPtr = CpltPtr;                 
            }break;	
            case GPIO_PIN_2:
            {
                wExti[2].CpltPtr = CpltPtr;                
            }break;
            case GPIO_PIN_3:
            {
                wExti[3].CpltPtr = CpltPtr;                  
            }break;	
            case GPIO_PIN_4:
            {
                wExti[4].CpltPtr = CpltPtr;               
            }break;            
            case GPIO_PIN_5:
            {
                wExti[5].CpltPtr = CpltPtr;               
            }break;
            case GPIO_PIN_6:
            {
                wExti[6].CpltPtr = CpltPtr;               
            }break;                
            case GPIO_PIN_7:
            {
                wExti[7].CpltPtr = CpltPtr;               
            }break;
            case GPIO_PIN_8:
            {
                wExti[8].CpltPtr = CpltPtr;               
            }break;                
            case GPIO_PIN_9:                
            {
                wExti[9].CpltPtr = CpltPtr;                 
            }break;
            case GPIO_PIN_10:                
            {
                wExti[10].CpltPtr = CpltPtr;                  
            }break;
            case GPIO_PIN_11:                 
            {
                wExti[11].CpltPtr = CpltPtr;                  
            }break;               
            case GPIO_PIN_12:                
            {
                wExti[12].CpltPtr = CpltPtr;                  
            }break;
            case GPIO_PIN_13:                
            {
                wExti[13].CpltPtr = CpltPtr;                  
            }break;                
            case GPIO_PIN_14:                 
            {
                wExti[14].CpltPtr = CpltPtr;                  
            }break; 
            case GPIO_PIN_15:                
            {
                wExti[15].CpltPtr = CpltPtr;                  
            }break;                
            default:break;   
        }
    }
}

void EXTI0_IRQHandler(void)
{
    OSIntEnter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
    HAL_NVIC_ClearPendingIRQ(EXTI0_IRQn);
    OSIntExit(); 
}

void EXTI1_IRQHandler(void)
{
    OSIntEnter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);		
    HAL_NVIC_ClearPendingIRQ(EXTI1_IRQn);       
    OSIntExit(); 
}

void EXTI2_IRQHandler(void)
{
    OSIntEnter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);		
    HAL_NVIC_ClearPendingIRQ(EXTI2_IRQn);       
    OSIntExit(); 
}	

void EXTI3_IRQHandler(void)
{
    OSIntEnter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);		
    HAL_NVIC_ClearPendingIRQ(EXTI3_IRQn);       
    OSIntExit(); 
}

void EXTI4_IRQHandler(void)
{
    OSIntEnter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);		
    HAL_NVIC_ClearPendingIRQ(EXTI4_IRQn);       
    OSIntExit(); 
}

void EXTI9_5_IRQHandler(void)
{
    OSIntEnter();

    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);		
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);		
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);		
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);		
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);		
    HAL_NVIC_ClearPendingIRQ(EXTI9_5_IRQn); 
    
    OSIntExit(); 
}	

void EXTI15_10_IRQHandler(void)
{
    OSIntEnter();

    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);		
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);		
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);		
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);		
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);		
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);		
    HAL_NVIC_ClearPendingIRQ(EXTI15_10_IRQn);     
    OSIntExit(); 
}	



uint16_t wGpio_Init(wPin pin,uint32_t Mode,uint32_t Pull,uint32_t Speed,uint32_t Alternate)      
{/*>>直接初使化GPIO引脚*/
    
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_TypeDef *GPIO;
    
	switch(wPIN_GPIO_MASK & pin)
    {
        case wPIN_A0:{GPIO=GPIOA;__HAL_RCC_GPIOA_CLK_ENABLE();}break;
        case wPIN_B0:{GPIO=GPIOB;__HAL_RCC_GPIOB_CLK_ENABLE();}break;	
        case wPIN_C0:{GPIO=GPIOC;__HAL_RCC_GPIOC_CLK_ENABLE();}break;
        case wPIN_D0:{GPIO=GPIOD;__HAL_RCC_GPIOD_CLK_ENABLE();}break;							
        case wPIN_E0:{GPIO=GPIOE;__HAL_RCC_GPIOE_CLK_ENABLE();}break;
    #ifdef GPIOF
        case wPIN_F0:{GPIO=GPIOF;__HAL_RCC_GPIOF_CLK_ENABLE();}break;	
    #endif  

    #ifdef GPIOG
        case wPIN_G0:{GPIO=GPIOG;__HAL_RCC_GPIOG_CLK_ENABLE();}break; 
    #endif
        
    #ifdef GPIOH
        case wPIN_H0:{GPIO=GPIOH;__HAL_RCC_GPIOH_CLK_ENABLE();}break;
    #endif

    #ifdef GPIOI
        case wPIN_I0:{GPIO=GPIOI;__HAL_RCC_GPIOI_CLK_ENABLE();}break;
    #endif        
        default:return NULL ;
    }
 
	switch(wPIN_PIN_MASK & pin)
    {
        case wPIN_0:{GPIO_InitStruct.Pin = GPIO_PIN_0;}break;
        case wPIN_1:{GPIO_InitStruct.Pin = GPIO_PIN_1;}break;	
        case wPIN_2:{GPIO_InitStruct.Pin = GPIO_PIN_2;}break;
        case wPIN_3:{GPIO_InitStruct.Pin = GPIO_PIN_3;}break;							
        case wPIN_4:{GPIO_InitStruct.Pin = GPIO_PIN_4;}break;
        case wPIN_5:{GPIO_InitStruct.Pin = GPIO_PIN_5;}break;							
        case wPIN_6:{GPIO_InitStruct.Pin = GPIO_PIN_6;}break;        
        case wPIN_7:{GPIO_InitStruct.Pin = GPIO_PIN_7;}break;
        case wPIN_8:{GPIO_InitStruct.Pin = GPIO_PIN_8;}break;
        case wPIN_9:{GPIO_InitStruct.Pin = GPIO_PIN_9;}break;	
        case wPIN_10:{GPIO_InitStruct.Pin = GPIO_PIN_10;}break;
        case wPIN_11:{GPIO_InitStruct.Pin = GPIO_PIN_11;}break;							
        case wPIN_12:{GPIO_InitStruct.Pin = GPIO_PIN_12;}break;
        case wPIN_13:{GPIO_InitStruct.Pin = GPIO_PIN_13;}break;							
        case wPIN_14:{GPIO_InitStruct.Pin = GPIO_PIN_14;}break;        
        case wPIN_15:{GPIO_InitStruct.Pin = GPIO_PIN_15;}break;
        default: return NULL;
    }
    
    GPIO_InitStruct.Mode = Mode;
    
    if(IS_GPIO_PULL(Pull))   { GPIO_InitStruct.Pull = Pull;}
    else               {GPIO_InitStruct.Pull = GPIO_NOPULL;}
    
    if(IS_GPIO_SPEED(Speed)){GPIO_InitStruct.Speed = Speed;}
    else    { GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;} 
    
#if  defined(STM32F4)
    GPIO_InitStruct.Alternate = Alternate;
#endif      
    
    HAL_GPIO_Init(GPIO, &GPIO_InitStruct); 
    
    if((Mode & GPIO_MODE_IT) == GPIO_MODE_IT)
    {
        uint32_t   Preempt = NoUse_Pri;
        IRQn_Type  IRQn;
        
        switch(GPIO_InitStruct.Pin)
        {
            case GPIO_PIN_0:
            {
                Preempt = EXTI0_Pri;
                IRQn = EXTI0_IRQn;              
            }break;
            case GPIO_PIN_1:
            {
                Preempt = EXTI1_Pri;
                IRQn = EXTI1_IRQn;                     
            }break;	
            case GPIO_PIN_2:
            {
                Preempt = EXTI2_Pri;
                IRQn = EXTI2_IRQn;                 
            }break;
            case GPIO_PIN_3:
            {
                Preempt = EXTI3_Pri;
                IRQn = EXTI3_IRQn;                   
            }break;	
            case GPIO_PIN_4:
            {
                Preempt = EXTI4_Pri;
                IRQn = EXTI4_IRQn;              
            }break;            
            case GPIO_PIN_5:
            case GPIO_PIN_6:
            case GPIO_PIN_7:
            case GPIO_PIN_8:
            case GPIO_PIN_9:                
            {
                Preempt = EXTI9_5_Pri;
                IRQn = EXTI9_5_IRQn;                
            }break;
            case GPIO_PIN_10:                
            case GPIO_PIN_11:                               
            case GPIO_PIN_12:                
            case GPIO_PIN_13:                              
            case GPIO_PIN_14:                 
            case GPIO_PIN_15:                
            {
                Preempt = EXTI15_10_Pri;
                IRQn = EXTI15_10_IRQn;                    
            }break;                
            default:break;   
        }
        
        if(Preempt != NoUse_Pri)
        {
            HAL_NVIC_SetPriority(IRQn, Preempt, 0);
            HAL_NVIC_EnableIRQ(IRQn); 
        }
    }
    return GPIO_InitStruct.Pin ;
}

void wGpio_putInit(wGpio_Def* wGPIO,wPin pin,uint32_t Mode,uint32_t Pull,uint32_t Speed,wGpio_Level level)
{/*>>带句柄方式初使化GPIO引脚，并增加了有效电平位*/
    
	switch(wPIN_GPIO_MASK & pin)
    {
        case wPIN_A0:{wGPIO->GPIOx=GPIOA;}break;
        case wPIN_B0:{wGPIO->GPIOx=GPIOB;}break;	
        case wPIN_C0:{wGPIO->GPIOx=GPIOC;}break;
        case wPIN_D0:{wGPIO->GPIOx=GPIOD;}break;							
        case wPIN_E0:{wGPIO->GPIOx=GPIOE;}break;
    #ifdef GPIOF
        case wPIN_F0:{wGPIO->GPIOx=GPIOF;}break;	
    #endif  

    #ifdef GPIOG
        case wPIN_G0:{wGPIO->GPIOx=GPIOG;}break; 
    #endif
        
    #ifdef GPIOH
        case wPIN_H0:{wGPIO->GPIOx=GPIOH;}break;
    #endif

    #ifdef GPIOI
        case wPIN_I0:{wGPIO->GPIOx=GPIOI;}break;
    #endif              
        default:return ;
    }    
    wGPIO->GPIO_Pin = wGpio_Init(pin,Mode,Pull,Speed,NULL);
    wGPIO->Level = level ;
    wGPIO->EN = wENABLE ;  
}

wGpio_State wGpio_putRead(wGpio_Def* wGPIO)
{/*>>读取电平的有效性*/
    wGpio_State             State;           //当前状态 
    if(wGPIO->EN)
    {
        if(HAL_GPIO_ReadPin(wGPIO->GPIOx, wGPIO->GPIO_Pin))
        {//读取到正限位引脚为高电平
            if(wGPIO->Level==wHigh) // 如果定义高电平有效
            {
                State = wACTIVE;
            }
            else                    // 如果定义低电平有效
            {
                State = wINACTIVE;
            }
        }
        else// 读取到正限位引脚为低电平
        {
            if(wGPIO->Level==wHigh)
            {
                State = wINACTIVE;
            }
            else
            {
                State = wACTIVE;
            }
        }
    }
    return State;
}

void wGpio_putWrite(wGpio_Def* wGPIO,wGpio_Set CurState)
{/*>>设置电平的有效性*/
    if(wGPIO->EN == ENABLE)
    {
        if(CurState == Set_ACTIVE)
        {//设定为有效电平
            if(wGPIO->Level==wHigh) 
            {// 如果定义高电平有效
                HAL_GPIO_WritePin(wGPIO->GPIOx, wGPIO->GPIO_Pin,GPIO_PIN_SET);
            }
            else 
            {
                HAL_GPIO_WritePin(wGPIO->GPIOx, wGPIO->GPIO_Pin,GPIO_PIN_RESET);
            }
        }
        else if(CurState == Set_INACTIVE)
        {//设定为无效电平
            if(wGPIO->Level==wHigh)
            {
                HAL_GPIO_WritePin(wGPIO->GPIOx, wGPIO->GPIO_Pin,GPIO_PIN_RESET);
            }
            else
            {
                HAL_GPIO_WritePin(wGPIO->GPIOx, wGPIO->GPIO_Pin,GPIO_PIN_SET);
            }
        }
		else
		{//切换电平
			HAL_GPIO_TogglePin(wGPIO->GPIOx, wGPIO->GPIO_Pin);
		}
    } 
}
