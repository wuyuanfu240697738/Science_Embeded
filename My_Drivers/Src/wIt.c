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
{//-3 ���������жϣ������ⲿNMI�����	
    
}

void HardFault_Handler(void)
{//-2 ���б����ܵ�fault,�����Ϸó�Ӳfault
    //Ӳ���� -- ���ܼ�ʱ��Ӧ�Ĺ���ͳһ���ΪӲ����
  while (1){}
}

void MemManage_Handler(void)
{//-1 �洢������� ��fault MPU���ʷ����Լ����ʷǷ�λ�ã��ڷ�ִ����ȡָ��������
  while (1){}
}

void BusFault_Handler(void)
{//����ϵͳ�յ�������Ӧ
  while (1){}
}

void UsageFault_Handler(void)
{//����������쳣��ʹ����һ����Чָ����߷Ƿ���״̬ת��
  while (1){}
}

void SVC_Handler(void)
{//ִ��ϵͳ�������ָ��svc�������쳣

}

void DebugMon_Handler(void)
{//�߶ȼ��������ϵ㣬���ݹ۲�㣬�������ⲿ��������

}

void SysTick_Handler(void)
{//ϵͳ�δ�ʱ��
    HAL_IncTick();
    //HAL_SYSTICK_IRQHandler();
    OS_CPU_SysTickHandler();    
}
