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

/* Filename    : wSerial.h*/

#ifndef __WY_Serial_H
#define __WY_Serial_H

	#include "wS.h"
	#include "os.h"  
    #include "wUart.h"
    #include "Cpucfg.h"
    
typedef  struct    wSerial_def       wSerial_Def;
struct  wSerial_def{
    OS_SEM		         TxSemflg;      //发送信号量
    OS_SEM		         RxSemflg;      //接收信号量
	wUart_Def            Uart;          //uart端口句柄
    uint32_t             length;        //未接收长度
};  

wStatus wSerial_Init(uint8_t Id,wPin Pin,uint32_t BaudRate,uint32_t StopBits,uint32_t Parity);
wStatus wSerial_CSSInit(uint8_t Id,wPin CnPin,wGpio_Level level);

wStatus wSerial_PrintfHex(uint8_t Id,void* buf,uint16_t len);
wStatus wSerial_Printf(uint8_t Id,char* fmt,...);
wStatus wSerial_Transmit(uint8_t Id,uint8_t *pData, uint16_t Size,uint32_t Timeout);
uint16_t wSerial_Receive(uint8_t Id,uint8_t *pData, uint16_t Size,uint32_t Timeout);
uint16_t wSerial_TransmitReceive(uint8_t Id, uint8_t *pData, uint16_t TSize, uint16_t RSize,uint32_t Timeout);

#if (WS_CFG_DEBUG_EN == WS_DEF_ENABLED)   
    #define     wDebug(fmt,arg...)     wSerial_Printf(0,fmt,##arg)
#else
    #define     wDebug(fmt,arg...) 
#endif


#endif
