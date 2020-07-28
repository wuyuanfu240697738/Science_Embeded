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

/* Filename    : wUart.c*/

#ifndef __WY_UART_H
#define __WY_UART_H

#ifdef __cplusplus
 extern "C" {
#endif
     
 /* Includes ------------------------------------------------------------------*/
  #include "wS.h"   
  #include "wgpio.h"     
 
#define  wUart_Num     7u      /*Uart数量*/

#ifndef GPIO_AF7_USART1
    #define GPIO_AF7_USART1        ((uint8_t)0x07)  /* USART1 Alternate Function mapping  	*/
#endif

#ifndef GPIO_AF7_USART2
    #define GPIO_AF7_USART2        ((uint8_t)0x07)  /* USART2 Alternate Function mapping   	*/
#endif

#ifndef GPIO_AF7_USART3
    #define GPIO_AF7_USART3        ((uint8_t)0x07)  /* USART3 Alternate Function mapping   	*/
#endif

#ifndef GPIO_AF8_UART4
    #define GPIO_AF8_UART4         ((uint8_t)0x08)  /* UART4 Alternate Function mapping  	*/
#endif

#ifndef GPIO_AF8_UART5
    #define GPIO_AF8_UART5         ((uint8_t)0x08)  /* UART5 Alternate Function mapping  	*/
#endif

#ifndef GPIO_AF8_USART6
    #define GPIO_AF8_USART6        ((uint8_t)0x08)  /* USART6 Alternate Function mapping 	*/
#endif

#if  defined(STM32F1)  

    #define  wUart1_TXDMA       DMA1_
    #define  wUart1_TXChannel   Channel4
    
    #define  wUart2_TXDMA       DMA1_
    #define  wUart2_TXChannel   Channel7 

    #define  wUart3_TXDMA       DMA1_
    #define  wUart3_TXChannel   Channel2 
    
    #define  wUart4_TXDMA       DMA2_
    #define  wUart4_TXChannel   Channel5  
    
    #define  wUart1_RXDMA       DMA1_
    #define  wUart1_RXChannel   Channel5
    
    #define  wUart2_RXDMA       DMA1_
    #define  wUart2_RXChannel   Channel6 

    #define  wUart3_RXDMA       DMA1_
    #define  wUart3_RXChannel   Channel3 
    
    #define  wUart4_RXDMA       DMA2_
    #define  wUart4_RXChannel   Channel3  
      
#elif  defined(STM32F4)

    #define  wUart1_TXDMA       DMA2_
    #define  wUart1_TXChannel   Stream7
    
    #define  wUart2_TXDMA       DMA1_
    #define  wUart2_TXChannel   Stream6 

    #define  wUart3_TXDMA       DMA1_
    #define  wUart3_TXChannel   Stream3 
//    #define  wUart3_TXChannel   Stream4 //通道7
    
    #define  wUart4_TXDMA       DMA1_
    #define  wUart4_TXChannel   Stream4 

    #define  wUart1_RXDMA       DMA2_
    #define  wUart1_RXChannel   Stream2
//    #define  wUart1_RXChannel   Stream5   
    
    #define  wUart2_RXDMA       DMA1_
    #define  wUart2_RXChannel   Stream5 

    #define  wUart3_RXDMA       DMA1_
    #define  wUart3_RXChannel   Stream1 
    
    #define  wUart4_RXDMA       DMA1_
    #define  wUart4_RXChannel   Stream2      
    
#endif  
  
    #define  DMA_USART1_RX_Instance     Conn2(wUart1_RXDMA,wUart1_RXChannel) 
    #define  DMA_USART2_RX_Instance     Conn2(wUart2_RXDMA,wUart2_RXChannel) 
    #define  DMA_USART3_RX_Instance     Conn2(wUart3_RXDMA,wUart3_RXChannel)  
    #define  DMA_USART4_RX_Instance     Conn2(wUart4_RXDMA,wUart4_RXChannel)
      
    #define  DMA_USART1_TX_Instance     Conn2(wUart1_TXDMA,wUart1_TXChannel) 
    #define  DMA_USART2_TX_Instance     Conn2(wUart2_TXDMA,wUart2_TXChannel) 
    #define  DMA_USART3_TX_Instance     Conn2(wUart3_TXDMA,wUart3_TXChannel)  
    #define  DMA_USART4_TX_Instance     Conn2(wUart4_TXDMA,wUart4_TXChannel) 
	
#define  wRxEnable                                      1u      /*接收使能*/
#define  wTxEnable                                      2u      /*发送使能*/

typedef  void (*UartRxCpltFnct_Idle)(UART_HandleTypeDef *huart,uint32_t length);//接收空闲回调函数
typedef  void (*UartTxCpltFnct     )(UART_HandleTypeDef *huart);//发送完成回调函数

typedef  struct    wUart_def       wUart_Def;
struct  wUart_def{
    UART_HandleTypeDef    huart;   
    DMA_HandleTypeDef     hdma_tx;
    DMA_HandleTypeDef     hdma_rx;   	 
    wGpio_Def             CSS;
	wUart_Def*			  NextPtr;
    UartRxCpltFnct_Idle   RxCplt_IdlePtr;   
    UartTxCpltFnct        TxCpltPtr;        
};    

void HAL_UART_RxCpltCallback_Idle(UART_HandleTypeDef *huart);
void wUart_SetCallback(wUart_Def *p_Uart,UartTxCpltFnct TxCpltPtr,UartRxCpltFnct_Idle RxCplt_IdlePtr);

HAL_StatusTypeDef wUart_DMAReceive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef wUart_DMATransmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
void wUart_AbortReceive(UART_HandleTypeDef *huart);
UART_HandleTypeDef* wUart_Init(wUart_Def* p_Uart,wPin Pin,uint32_t BaudRate,uint32_t StopBits,uint32_t Parity,uint32_t Trans);
UART_HandleTypeDef* wUart_DMAInit(wUart_Def* p_Uart,wPin Pin,uint32_t BaudRate,uint32_t StopBits,uint32_t Parity,uint32_t Trans);
void wUart_CSSInit(wUart_Def* p_Uart,wPin pin,wGpio_Level level);
void wUart_DisAll(void);

#ifdef __cplusplus
}
#endif

#endif
