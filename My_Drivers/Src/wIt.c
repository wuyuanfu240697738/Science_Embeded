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

/* Filename    : wIt.c*/

#include "wIt.h"
#include "wUart.h"
#include "os.h"

void NMI_Handler(void)
{//-3 不可屏蔽中断，来自外部NMI输入脚	
    
}

void HardFault_Handler(void)
{//-2 所有被除能的fault,都将上访成硬fault
    //硬故障 -- 不能及时响应的故障统一归结为硬故障
  while (1){}
}

void MemManage_Handler(void)
{//-1 存储管理故障 ：fault MPU访问犯规以及访问非法位置，在非执行区取指均可引发
  while (1){}
}

void BusFault_Handler(void)
{//总线系统收到错误响应
  while (1){}
}

void UsageFault_Handler(void)
{//程序错误导致异常，使用了一条无效指令，或者非法的状态转换
  while (1){}
}

void SVC_Handler(void)
{//执行系统服务调用指令svc引发的异常

}

void DebugMon_Handler(void)
{//高度监视器（断点，数据观察点，或者是外部调试请求）

}

void SysTick_Handler(void)
{//系统滴答时钟
    HAL_IncTick();
    //HAL_SYSTICK_IRQHandler();
    OS_CPU_SysTickHandler();    
}
