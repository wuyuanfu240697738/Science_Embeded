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

/* Filename    : wIt.h*/

#ifndef __WY_IT_H
#define __WY_IT_H

#ifdef __cplusplus
 extern "C" {
#endif
     
    #include "wS.h"   
    #include "Cpucfg.h"    

#define NoUse_Pri                       0xff

#ifndef PendSV_Pri
	#define  PendSV_Pri                  8     /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
#endif
#ifndef SysTick_Pri
	#define  SysTick_Pri                 8     /*!< 15 Cortex-M4 System Tick Interrupt                                */
#endif

#ifndef EXTI0_Pri
	#define  EXTI0_Pri                   2     /*!< EXTI Line0 Interrupt                                              */
#endif
#ifndef EXTI1_Pri
	#define  EXTI1_Pri                   2     /*!< EXTI Line1 Interrupt                                              */
#endif
#ifndef EXTI2_Pri
	#define  EXTI2_Pri                   2     /*!< EXTI Line2 Interrupt                                              */
#endif
#ifndef EXTI3_Pri
	#define  EXTI3_Pri                   2     /*!< EXTI Line3 Interrupt                                              */
#endif
#ifndef EXTI4_Pri
	#define  EXTI4_Pri                   2     /*!< EXTI Line3 Interrupt                                              */
#endif
#ifndef EXTI9_5_Pri
	#define  EXTI9_5_Pri                 2     /*!< External Line[9:5] Interrupts                                     */
#endif
#ifndef EXTI15_10_Pri
	#define  EXTI15_10_Pri               2     /*!< External Line[15:10] Interrupts                                   */
#endif

#ifndef USART1_Pri
	#define  USART1_Pri                  3     /*!< USART1 global Interrupt                                           */
#endif
#ifndef USART2_Pri
	#define  USART2_Pri                  3     /*!< USART2 global Interrupt                                           */
#endif
#ifndef USART3_Pri
	#define  USART3_Pri                  3     /*!< USART3 global Interrupt                                           */
#endif
#ifndef UART4_Pri
	#define  UART4_Pri                   3     /*!< UART4 global Interrupt                                            */
#endif
#ifndef UART5_Pri
	#define  UART5_Pri                   3     /*!< UART5 global Interrupt                                            */
#endif
#ifndef USART6_Pri
	#define  USART6_Pri                  3     /*!< USART6 global interrupt                                           */
#endif
#ifndef UART7_Pri
	#define  UART7_Pri                   3     /*!< USART6 global interrupt                                           */
#endif

#ifndef DMA1_CS0_Pri
	#define  DMA1_CS0_Pri            	 9     /*!< DMA1 CS 0 global Interrupt                                    */
#endif
#ifndef DMA1_CS1_Pri
	#define  DMA1_CS1_Pri            	 9     /*!< DMA1 CS 1 global Interrupt                                    */
#endif
#ifndef DMA1_CS2_Pri
	#define  DMA1_CS2_Pri            	 9     /*!< DMA1 CS 2 global Interrupt                                    */
#endif
#ifndef DMA1_CS3_Pri
	#define  DMA1_CS3_Pri            	 9     /*!< DMA1 CS 3 global Interrupt                                    */
#endif
#ifndef DMA1_CS4_Pri
	#define  DMA1_CS4_Pri            	 9     /*!< DMA1 CS 4 global Interrupt                                    */
#endif
#ifndef DMA1_CS5_Pri
	#define  DMA1_CS5_Pri            	 9     /*!< DMA1 CS 5 global Interrupt                                    */
#endif
#ifndef DMA1_CS6_Pri
	#define  DMA1_CS6_Pri            	 9     /*!< DMA1 CS 6 global Interrupt                                    */
#endif
#ifndef DMA1_CS7_Pri
	#define  DMA1_CS7_Pri            	 9     /*!< DMA1 CS7 Interrupt                                            */
#endif
#ifndef DMA2_CS0_Pri
	#define  DMA2_CS0_Pri            	 9     /*!< DMA2 CS 0 global Interrupt                                    */
#endif
#ifndef DMA2_CS1_Pri
	#define  DMA2_CS1_Pri            	 9     /*!< DMA2 CS 1 global Interrupt                                    */
#endif
#ifndef DMA2_CS2_Pri
	#define  DMA2_CS2_Pri            	 9     /*!< DMA2 CS 2 global Interrupt                                    */
#endif
#ifndef DMA2_CS3_Pri
	#define  DMA2_CS3_Pri            	 9     /*!< DMA2 CS 3 global Interrupt                                    */
#endif
#ifndef DMA2_CS4_Pri
	#define  DMA2_CS4_Pri            	 9     /*!< DMA2 CS 4 global Interrupt                                    */
#endif
#ifndef DMA2_CS5_Pri
	#define  DMA2_CS5_Pri            	 9     /*!< DMA2 CS 5 global interrupt                                    */
#endif
#ifndef DMA2_CS6_Pri
	#define  DMA2_CS6_Pri            	 9     /*!< DMA2 CS 6 global interrupt                                    */
#endif
#ifndef DMA2_CS7_Pri
	#define  DMA2_CS7_Pri            	 9     /*!< DMA2 CS 7 global interrupt                                    */
#endif

#ifndef ADC_Pri
	#define  ADC_Pri                     15     /*!< ADC1 ADC2 and ADC3 global Interrupts                             */
#endif

#ifndef SPI1_Pri
	#define  SPI1_Pri                    4     /*!< SPI1 global Interrupt                                             */
#endif
#ifndef SPI2_Pri
	#define  SPI2_Pri                    4     /*!< SPI2 global Interrupt                                             */
#endif
#ifndef SPI3_Pri
	#define  SPI3_Pri                    4     /*!< SPI3 global Interrupt                                             */
#endif

#ifndef TIM1_BRK_TIM9_Pri
	#define  TIM1_BRK_TIM9_Pri           5     /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
#endif
#ifndef TIM1_UP_TIM10_Pri
	#define  TIM1_UP_TIM10_Pri           5     /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
#endif
#ifndef TIM1_TRG_COM_TIM11_Pri
	#define  TIM1_TRG_COM_TIM11_Pri      5     /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
#endif
#ifndef TIM1_CC_Pri
	#define  TIM1_CC_Pri                 5     /*!< TIM1 Capture Compare Interrupt                                    */
#endif
#ifndef TIM2_Pri
	#define  TIM2_Pri                    5     /*!< TIM2 global Interrupt                                             */
#endif
#ifndef TIM3_Pri
	#define  TIM3_Pri                    5     /*!< TIM3 global Interrupt                                             */
#endif
#ifndef TIM4_Pri
	#define  TIM4_Pri                    5     /*!< TIM4 global Interrupt                                             */
#endif
#ifndef TIM5_Pri
	#define  TIM5_Pri                    5     /*!< TIM5 global Interrupt                                             */
#endif
#ifndef TIM6_Pri
	#define  TIM6_Pri                    5     /*!< TIM6 global and DAC1&2 underrun error  interrupts                 */
#endif
#ifndef TIM7_Pri
	#define  TIM7_Pri                    1     /*!< TIM7 global interrupt                                             */
#endif
#ifndef TIM8_BRK_TIM12_Pri
	#define  TIM8_BRK_TIM12_Pri          5     /*!< TIM8 Break Interrupt and TIM12 global interrupt                   */
#endif
#ifndef TIM8_UP_TIM13_Pri
	#define  TIM8_UP_TIM13_Pri           5     /*!< TIM8 Update Interrupt and TIM13 global interrupt                  */
#endif
#ifndef TIM8_TRG_COM_TIM14_Pri
	#define  TIM8_TRG_COM_TIM14_Pri      5     /*!< TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt */
#endif
#ifndef TIM8_CC_Pri
	#define  TIM8_CC_Pri                 5     /*!< TIM8 Capture Compare global interrupt                             */
#endif

#ifndef I2C1_EV_Pri
	#define  I2C1_EV_Pri                 6     /*!< I2C1 Event Interrupt                                              */
#endif
#ifndef I2C1_ER_Pri
	#define  I2C1_ER_Pri                 6     /*!< I2C1 Error Interrupt                                              */
#endif
#ifndef I2C2_EV_Pri
	#define  I2C2_EV_Pri                 6     /*!< I2C2 Event Interrupt                                              */
#endif
#ifndef I2C2_ER_Pri
	#define  I2C2_ER_Pri                 6     /*!< I2C2 Error Interrupt                                              */
#endif
#ifndef I2C3_EV_Pri
	#define  I2C3_EV_Pri                 6     /*!< I2C3 event interrupt                                              */
#endif
#ifndef I2C3_ER_Pri
	#define  I2C3_ER_Pri                 6     /*!< I2C3 error interrupt                                              */
#endif

#ifndef ETH_Pri
	#define  ETH_Pri                     10     /*!< Ethernet global Interrupt                                         */
#endif
#ifndef ETH_WKUP_Pri
	#define  ETH_WKUP_Pri                10     /*!< Ethernet Wakeup through EXTI line Interrupt                       */
#endif

#ifndef OTG_FS_Rri
	#define  OTG_FS_Rri                  7     /*!< Ethernet global Interrupt                                         */
#endif

#ifndef OTG_HS_Rri
	#define  OTG_HS_Rri                  7     /*!< Ethernet global Interrupt                                         */
#endif

#ifdef __cplusplus
}
#endif

#endif /* __STM32F1xx_IT_H */


