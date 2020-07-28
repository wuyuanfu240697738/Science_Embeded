
#ifndef __WY_S_H
#define __WY_S_H

/*
********************************************************************************************************
*                                                 STM
********************************************************************************************************
*/

#if defined (STM32F103xB) || defined (STM32F103xE) || defined (STM32F103xG) || defined (STM32F105xC) || defined (STM32F107xC)

    #include "stm32f1xx_hal.h"    
    #define BIT_ADDR_num  0
    
#elif defined (STM32F405xx) || defined (STM32F415xx) || defined (STM32F407xx) || defined (STM32F417xx) || \
      defined (STM32F427xx) || defined (STM32F437xx) || defined (STM32F429xx) || defined (STM32F439xx) || \
      defined (STM32F401xC) || defined (STM32F401xE) || defined (STM32F410Tx) || defined (STM32F410Cx) || \
      defined (STM32F410Rx) || defined (STM32F411xE) || defined (STM32F446xx) || defined (STM32F469xx) || \
      defined (STM32F479xx) || defined (STM32F412Cx) || defined (STM32F412Rx) || defined (STM32F412Vx) || \
      defined (STM32F412Zx) || defined (STM32F413xx) || defined (STM32F423xx)

    #include "stm32f4xx_hal.h"      
    #define BIT_ADDR_num  8 
    
#endif

#ifndef GPIO_SPEED_FREQ_VERY_HIGH
    #define  GPIO_SPEED_FREQ_VERY_HIGH   GPIO_SPEED_FREQ_HIGH //兼容F1
#endif

#include "wType.h"	

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x02000000+((addr & 0x00FFFFFF)<<5)+(bitnum<<2))   
#define BIT_ADDR(addr, bitnum)   *((volatile unsigned long *)(BITBAND(addr, bitnum)))             


// 单独操作 GPIO的某一个IO口，n(0,1,2...16),n表示具体是哪一个IO口
#define PAout(n)   BIT_ADDR((GPIOA_BASE+12+BIT_ADDR_num),n)  //输出   
#define PAin(n)    BIT_ADDR((GPIOA_BASE+8+ BIT_ADDR_num),n)  //输入   
#define PBout(n)   BIT_ADDR((GPIOB_BASE+12+BIT_ADDR_num),n)  //输出   
#define PBin(n)    BIT_ADDR((GPIOB_BASE+8+ BIT_ADDR_num),n)  //输入   
#define PCout(n)   BIT_ADDR((GPIOC_BASE+12+BIT_ADDR_num),n)  //输出   
#define PCin(n)    BIT_ADDR((GPIOC_BASE+8+ BIT_ADDR_num),n)  //输入   
#define PDout(n)   BIT_ADDR((GPIOD_BASE+12+BIT_ADDR_num),n)  //输出   
#define PDin(n)    BIT_ADDR((GPIOD_BASE+8+ BIT_ADDR_num),n)  //输入   
#define PEout(n)   BIT_ADDR((GPIOE_BASE+12+BIT_ADDR_num),n)  //输出   
#define PEin(n)    BIT_ADDR((GPIOE_BASE+8+ BIT_ADDR_num),n)  //输入  
#define PFout(n)   BIT_ADDR((GPIOF_BASE+12+BIT_ADDR_num),n)  //输出   
#define PFin(n)    BIT_ADDR((GPIOF_BASE+8+ BIT_ADDR_num),n)  //输入  
#define PGout(n)   BIT_ADDR((GPIOG_BASE+12+BIT_ADDR_num),n)  //输出   
#define PGin(n)    BIT_ADDR((GPIOG_BASE+8+ BIT_ADDR_num),n)  //输入 

#define  wNULL 		                                    0u

#define  wNO                                            0u
#define  wYES                                           1u

#define  wINVALID                                       0u
#define  wVALID                                         1u

#define  wOFF                                           0u
#define  wON                                            1u

#define  wCLR                                           0u
#define  wSET                                           1u

typedef enum {wFALSE = 0, wTRUE = !wFALSE} wBOOL;      //真假
typedef enum {wDISABLE = 0,wENABLE = !wDISABLE} wFun;  //功能开关

typedef enum
{
  wOK       = 0x00U,
  wERROR    = 0x01U,
  wBUSY     = 0x02U,
  wTIMEOUT  = 0x03U,
}wStatus;


#define      wPIN_0                              (wuint)0x0u 
#define      wPIN_1                              (wuint)0x1u 
#define      wPIN_2                              (wuint)0x2u
#define      wPIN_3                              (wuint)0x3u
#define      wPIN_4                              (wuint)0x4u
#define      wPIN_5                              (wuint)0x5u
#define      wPIN_6                              (wuint)0x6u
#define      wPIN_7                              (wuint)0x7u
#define      wPIN_8                              (wuint)0x8u
#define      wPIN_9                              (wuint)0x9u
#define      wPIN_10                             (wuint)0xAu
#define      wPIN_11                             (wuint)0xBu
#define      wPIN_12                             (wuint)0xCu
#define      wPIN_13                             (wuint)0xDu
#define      wPIN_14                             (wuint)0xEu
#define      wPIN_15                             (wuint)0xFu
    
typedef  enum {
    wPIN_NO                             =     (wuint)0u,  
    wPIN_Iwdg                           =     (wuint)1u, 
    
//////////////////////////////////////////////////////////////////////////////////////
    #define  wPIN_PIN_MASK                    (wuint)0x000fu
    #define  wPIN_GPIO_MASK                   (wuint)0x00f0u
    
    wPIN_A0                             =     (wuint)0x0010u + wPIN_0, 
    wPIN_A1                             =     (wuint)0x0010u + wPIN_1, 
    wPIN_A2                             =     (wuint)0x0010u + wPIN_2, 
    wPIN_A3                             =     (wuint)0x0010u + wPIN_3, 
    wPIN_A4                             =     (wuint)0x0010u + wPIN_4, 
    wPIN_A5                             =     (wuint)0x0010u + wPIN_5, 
    wPIN_A6                             =     (wuint)0x0010u + wPIN_6, 
    wPIN_A7                             =     (wuint)0x0010u + wPIN_7, 
    wPIN_A8                             =     (wuint)0x0010u + wPIN_8, 
    wPIN_A9                             =     (wuint)0x0010u + wPIN_9, 
    wPIN_A10                            =     (wuint)0x0010u + wPIN_10, 
    wPIN_A11                            =     (wuint)0x0010u + wPIN_11, 
    wPIN_A12                            =     (wuint)0x0010u + wPIN_12, 
    wPIN_A13                            =     (wuint)0x0010u + wPIN_13, 
    wPIN_A14                            =     (wuint)0x0010u + wPIN_14, 
    wPIN_A15                            =     (wuint)0x0010u + wPIN_15, 

    wPIN_B0                             =     (wuint)0x0020u + wPIN_0, 
    wPIN_B1                             =     (wuint)0x0020u + wPIN_1, 
    wPIN_B2                             =     (wuint)0x0020u + wPIN_2, 
    wPIN_B3                             =     (wuint)0x0020u + wPIN_3, 
    wPIN_B4                             =     (wuint)0x0020u + wPIN_4, 
    wPIN_B5                             =     (wuint)0x0020u + wPIN_5, 
    wPIN_B6                             =     (wuint)0x0020u + wPIN_6, 
    wPIN_B7                             =     (wuint)0x0020u + wPIN_7, 
    wPIN_B8                             =     (wuint)0x0020u + wPIN_8, 
    wPIN_B9                             =     (wuint)0x0020u + wPIN_9, 
    wPIN_B10                            =     (wuint)0x0020u + wPIN_10, 
    wPIN_B11                            =     (wuint)0x0020u + wPIN_11, 
    wPIN_B12                            =     (wuint)0x0020u + wPIN_12, 
    wPIN_B13                            =     (wuint)0x0020u + wPIN_13, 
    wPIN_B14                            =     (wuint)0x0020u + wPIN_14, 
    wPIN_B15                            =     (wuint)0x0020u + wPIN_15, 
    
    wPIN_C0                             =     (wuint)0x0030u + wPIN_0, 
    wPIN_C1                             =     (wuint)0x0030u + wPIN_1, 
    wPIN_C2                             =     (wuint)0x0030u + wPIN_2, 
    wPIN_C3                             =     (wuint)0x0030u + wPIN_3, 
    wPIN_C4                             =     (wuint)0x0030u + wPIN_4, 
    wPIN_C5                             =     (wuint)0x0030u + wPIN_5, 
    wPIN_C6                             =     (wuint)0x0030u + wPIN_6, 
    wPIN_C7                             =     (wuint)0x0030u + wPIN_7, 
    wPIN_C8                             =     (wuint)0x0030u + wPIN_8, 
    wPIN_C9                             =     (wuint)0x0030u + wPIN_9, 
    wPIN_C10                            =     (wuint)0x0030u + wPIN_10, 
    wPIN_C11                            =     (wuint)0x0030u + wPIN_11, 
    wPIN_C12                            =     (wuint)0x0030u + wPIN_12, 
    wPIN_C13                            =     (wuint)0x0030u + wPIN_13, 
    wPIN_C14                            =     (wuint)0x0030u + wPIN_14, 
    wPIN_C15                            =     (wuint)0x0030u + wPIN_15, 
    
    wPIN_D0                             =     (wuint)0x0040u + wPIN_0, 
    wPIN_D1                             =     (wuint)0x0040u + wPIN_1, 
    wPIN_D2                             =     (wuint)0x0040u + wPIN_2, 
    wPIN_D3                             =     (wuint)0x0040u + wPIN_3, 
    wPIN_D4                             =     (wuint)0x0040u + wPIN_4, 
    wPIN_D5                             =     (wuint)0x0040u + wPIN_5, 
    wPIN_D6                             =     (wuint)0x0040u + wPIN_6, 
    wPIN_D7                             =     (wuint)0x0040u + wPIN_7, 
    wPIN_D8                             =     (wuint)0x0040u + wPIN_8, 
    wPIN_D9                             =     (wuint)0x0040u + wPIN_9, 
    wPIN_D10                            =     (wuint)0x0040u + wPIN_10, 
    wPIN_D11                            =     (wuint)0x0040u + wPIN_11, 
    wPIN_D12                            =     (wuint)0x0040u + wPIN_12, 
    wPIN_D13                            =     (wuint)0x0040u + wPIN_13, 
    wPIN_D14                            =     (wuint)0x0040u + wPIN_14, 
    wPIN_D15                            =     (wuint)0x0040u + wPIN_15,
    
    wPIN_E0                             =     (wuint)0x0050u + wPIN_0, 
    wPIN_E1                             =     (wuint)0x0050u + wPIN_1, 
    wPIN_E2                             =     (wuint)0x0050u + wPIN_2, 
    wPIN_E3                             =     (wuint)0x0050u + wPIN_3, 
    wPIN_E4                             =     (wuint)0x0050u + wPIN_4, 
    wPIN_E5                             =     (wuint)0x0050u + wPIN_5, 
    wPIN_E6                             =     (wuint)0x0050u + wPIN_6, 
    wPIN_E7                             =     (wuint)0x0050u + wPIN_7, 
    wPIN_E8                             =     (wuint)0x0050u + wPIN_8, 
    wPIN_E9                             =     (wuint)0x0050u + wPIN_9, 
    wPIN_E10                            =     (wuint)0x0050u + wPIN_10, 
    wPIN_E11                            =     (wuint)0x0050u + wPIN_11, 
    wPIN_E12                            =     (wuint)0x0050u + wPIN_12, 
    wPIN_E13                            =     (wuint)0x0050u + wPIN_13, 
    wPIN_E14                            =     (wuint)0x0050u + wPIN_14, 
    wPIN_E15                            =     (wuint)0x0050u + wPIN_15, 

    wPIN_F0                             =     (wuint)0x0060u + wPIN_0, 
    wPIN_F1                             =     (wuint)0x0060u + wPIN_1, 
    wPIN_F2                             =     (wuint)0x0060u + wPIN_2, 
    wPIN_F3                             =     (wuint)0x0060u + wPIN_3, 
    wPIN_F4                             =     (wuint)0x0060u + wPIN_4, 
    wPIN_F5                             =     (wuint)0x0060u + wPIN_5, 
    wPIN_F6                             =     (wuint)0x0060u + wPIN_6, 
    wPIN_F7                             =     (wuint)0x0060u + wPIN_7, 
    wPIN_F8                             =     (wuint)0x0060u + wPIN_8, 
    wPIN_F9                             =     (wuint)0x0060u + wPIN_9, 
    wPIN_F10                            =     (wuint)0x0060u + wPIN_10, 
    wPIN_F11                            =     (wuint)0x0060u + wPIN_11, 
    wPIN_F12                            =     (wuint)0x0060u + wPIN_12, 
    wPIN_F13                            =     (wuint)0x0060u + wPIN_13, 
    wPIN_F14                            =     (wuint)0x0060u + wPIN_14, 
    wPIN_F15                            =     (wuint)0x0060u + wPIN_15, 

    wPIN_G0                             =     (wuint)0x0070u + wPIN_0, 
    wPIN_G1                             =     (wuint)0x0070u + wPIN_1, 
    wPIN_G2                             =     (wuint)0x0070u + wPIN_2, 
    wPIN_G3                             =     (wuint)0x0070u + wPIN_3, 
    wPIN_G4                             =     (wuint)0x0070u + wPIN_4, 
    wPIN_G5                             =     (wuint)0x0070u + wPIN_5, 
    wPIN_G6                             =     (wuint)0x0070u + wPIN_6, 
    wPIN_G7                             =     (wuint)0x0070u + wPIN_7, 
    wPIN_G8                             =     (wuint)0x0070u + wPIN_8, 
    wPIN_G9                             =     (wuint)0x0070u + wPIN_9, 
    wPIN_G10                            =     (wuint)0x0070u + wPIN_10, 
    wPIN_G11                            =     (wuint)0x0070u + wPIN_11, 
    wPIN_G12                            =     (wuint)0x0070u + wPIN_12, 
    wPIN_G13                            =     (wuint)0x0070u + wPIN_13, 
    wPIN_G14                            =     (wuint)0x0070u + wPIN_14, 
    wPIN_G15                            =     (wuint)0x0070u + wPIN_15, 
    
    wPIN_H0                             =     (wuint)0x0080u + wPIN_0, 
    wPIN_H1                             =     (wuint)0x0080u + wPIN_1, 
    wPIN_H2                             =     (wuint)0x0080u + wPIN_2, 
    wPIN_H3                             =     (wuint)0x0080u + wPIN_3, 
    wPIN_H4                             =     (wuint)0x0080u + wPIN_4, 
    wPIN_H5                             =     (wuint)0x0080u + wPIN_5, 
    wPIN_H6                             =     (wuint)0x0080u + wPIN_6, 
    wPIN_H7                             =     (wuint)0x0080u + wPIN_7, 
    wPIN_H8                             =     (wuint)0x0080u + wPIN_8, 
    wPIN_H9                             =     (wuint)0x0080u + wPIN_9, 
    wPIN_H10                            =     (wuint)0x0080u + wPIN_10, 
    wPIN_H11                            =     (wuint)0x0080u + wPIN_11, 
    wPIN_H12                            =     (wuint)0x0080u + wPIN_12, 
    wPIN_H13                            =     (wuint)0x0080u + wPIN_13, 
    wPIN_H14                            =     (wuint)0x0080u + wPIN_14, 
    wPIN_H15                            =     (wuint)0x0080u + wPIN_15, 
    
    wPIN_I0                             =     (wuint)0x0090u + wPIN_0, 
    wPIN_I1                             =     (wuint)0x0090u + wPIN_1, 
    wPIN_I2                             =     (wuint)0x0090u + wPIN_2, 
    wPIN_I3                             =     (wuint)0x0090u + wPIN_3, 
    wPIN_I4                             =     (wuint)0x0090u + wPIN_4, 
    wPIN_I5                             =     (wuint)0x0090u + wPIN_5, 
    wPIN_I6                             =     (wuint)0x0090u + wPIN_6, 
    wPIN_I7                             =     (wuint)0x0090u + wPIN_7, 
    wPIN_I8                             =     (wuint)0x0090u + wPIN_8, 
    wPIN_I9                             =     (wuint)0x0090u + wPIN_9, 
    wPIN_I10                            =     (wuint)0x0090u + wPIN_10, 
    wPIN_I11                            =     (wuint)0x0090u + wPIN_11, 
    wPIN_I12                            =     (wuint)0x0090u + wPIN_12, 
    wPIN_I13                            =     (wuint)0x0090u + wPIN_13, 
    wPIN_I14                            =     (wuint)0x0090u + wPIN_14, 
    wPIN_I15                            =     (wuint)0x0090u + wPIN_15, 

//////////////////////////////////////////////////////////////////////////////////////
    #define  wPIN_TIM_OC_MASK                     (wuint)0xf000u
    #define  wPIN_TIM_CHANNEL_MASK                (wuint)0x0f00u
    #define  wPIN_TIM_CHANNEL1                    (wuint)0x0100u
    #define  wPIN_TIM_CHANNEL2                    (wuint)0x0200u
    #define  wPIN_TIM_CHANNEL3                    (wuint)0x0300u
    #define  wPIN_TIM_CHANNEL4                    (wuint)0x0400u

    wPIN_TIM1                               =     (wuint)0x1000u,
    wPIN_TIM1_PWM_CH1_PA8                   =     (wuint)0x1100u + wPIN_A8,        
    wPIN_TIM1_PWM_CH1_PE9                   =     (wuint)0x1100u + wPIN_E9,          
    wPIN_TIM1_PWM_CH2_PA9                   =     (wuint)0x1200u + wPIN_A9,     
    wPIN_TIM1_PWM_CH2_PE11                  =     (wuint)0x1200u + wPIN_E11,     
    wPIN_TIM1_PWM_CH3_PA10                  =     (wuint)0x1300u + wPIN_A10,      
    wPIN_TIM1_PWM_CH3_PE13                  =     (wuint)0x1300u + wPIN_E13, 
    wPIN_TIM1_PWM_CH4_PA11                  =     (wuint)0x1400u + wPIN_A11,     
    wPIN_TIM1_PWM_CH4_PE14                  =     (wuint)0x1400u + wPIN_E14, 
    wPIN_TIM1_Encoder                       =     (wuint)0x1900u,
    wPIN_TIM1_Encoder_A8A9                  =     (wuint)0x1901u, 
    wPIN_TIM1_Encoder_E9E11                 =     (wuint)0x1902u, 

    wPIN_TIM2                               =     (wuint)0x2000u,
    wPIN_TIM2_PWM_CH1_PA0                   =     (wuint)0x2100u + wPIN_A0,          
    wPIN_TIM2_PWM_CH1_PA15                  =     (wuint)0x2100u + wPIN_A15,     
    wPIN_TIM2_PWM_CH2_PA1                   =     (wuint)0x2200u + wPIN_A1,      
    wPIN_TIM2_PWM_CH2_PB3                   =     (wuint)0x2200u + wPIN_B3,      
    wPIN_TIM2_PWM_CH3_PA2                   =     (wuint)0x2300u + wPIN_A2,     
    wPIN_TIM2_PWM_CH3_PB10                  =     (wuint)0x2300u + wPIN_B10, 
    wPIN_TIM2_PWM_CH4_PA3                   =     (wuint)0x2400u + wPIN_A3,     
    wPIN_TIM2_PWM_CH4_PB11                  =     (wuint)0x2400u + wPIN_B11, 
    wPIN_TIM2_Encoder                       =     (wuint)0x2900u,    
    wPIN_TIM2_Encoder_A0A1                  =     (wuint)0x2901u, 
    wPIN_TIM2_Encoder_A15B3                 =     (wuint)0x2902u,

    wPIN_TIM3                               =     (wuint)0x3000u,
    wPIN_TIM3_PWM_CH1_PA6                   =     (wuint)0x3100u + wPIN_A6,         
    wPIN_TIM3_PWM_CH1_PB4                   =     (wuint)0x3100u + wPIN_B4, 
    wPIN_TIM3_PWM_CH1_PC6                   =     (wuint)0x3100u + wPIN_C6,    
    wPIN_TIM3_PWM_CH2_PA7                   =     (wuint)0x3200u + wPIN_A7,    
    wPIN_TIM3_PWM_CH2_PB5                   =     (wuint)0x3200u + wPIN_B5, 
    wPIN_TIM3_PWM_CH2_PC7                   =     (wuint)0x3200u + wPIN_C7,    
    wPIN_TIM3_PWM_CH3_PB0                   =     (wuint)0x3300u + wPIN_B0,  
    wPIN_TIM3_PWM_CH3_PC8                   =     (wuint)0x3300u + wPIN_C8, 
    wPIN_TIM3_PWM_CH4_PB1                   =     (wuint)0x3400u + wPIN_B1,  
    wPIN_TIM3_PWM_CH4_PC9                   =     (wuint)0x3400u + wPIN_C9, 
    wPIN_TIM3_Encoder                       =     (wuint)0x3900u,     
    wPIN_TIM3_Encoder_A6A7                  =     (wuint)0x3901u, 
    wPIN_TIM3_Encoder_B4B5                  =     (wuint)0x3902u, 
    wPIN_TIM3_Encoder_C6C7                  =     (wuint)0x3903u, 
    
    wPIN_TIM4                               =     (wuint)0x4000u, 
    wPIN_TIM4_PWM_CH1_PB6                   =     (wuint)0x4100u + wPIN_B6,         
    wPIN_TIM4_PWM_CH1_PD12                  =     (wuint)0x4100u + wPIN_D12,     
    wPIN_TIM4_PWM_CH2_PB7                   =     (wuint)0x4200u + wPIN_B7,      
    wPIN_TIM4_PWM_CH2_PD13                  =     (wuint)0x4200u + wPIN_D13,     
    wPIN_TIM4_PWM_CH3_PB8                   =     (wuint)0x4300u + wPIN_B8,     
    wPIN_TIM4_PWM_CH3_PD14                  =     (wuint)0x4300u + wPIN_D14, 
    wPIN_TIM4_PWM_CH4_PB9                   =     (wuint)0x4400u + wPIN_B9,    
    wPIN_TIM4_PWM_CH4_PD15                  =     (wuint)0x4400u + wPIN_D15, 
    wPIN_TIM4_Encoder                       =     (wuint)0x4900u,     
    wPIN_TIM4_Encoder_B6B7                  =     (wuint)0x4901u, 
    wPIN_TIM4_Encoder_D12D13                =     (wuint)0x4902u, 
    
    wPIN_TIM5                               =     (wuint)0x5000u, 
    wPIN_TIM5_PWM_CH1_PA0                   =     (wuint)0x5100u + wPIN_A0,         
    wPIN_TIM5_PWM_CH2_PA1                   =     (wuint)0x5200u + wPIN_A1,    
    wPIN_TIM5_PWM_CH3_PA2                   =     (wuint)0x5300u + wPIN_A2,     
    wPIN_TIM5_PWM_CH4_PA3                   =     (wuint)0x5400u + wPIN_A3,
    wPIN_TIM5_Encoder                       =     (wuint)0x5900u,    
    wPIN_TIM5_Encoder_A0A1                  =     (wuint)0x59001u,

    wPIN_TIM8                               =     (wuint)0x6000u,
    wPIN_TIM8_Encoder                       =     (wuint)0x6900u,    
    wPIN_TIM8_Encoder_C6C7                  =     (wuint)0x6901u,

    #define  wPIN_TIM_BASE_MASK                   (wuint)0xff00u
    wPIN_TIM6                               =     (wuint)0x8600u,
    wPIN_TIM7                               =     (wuint)0x8700u, 
    wPIN_TIM9                               =     (wuint)0x8900u,
    wPIN_TIM10                              =     (wuint)0x8a00u,
    wPIN_TIM11                              =     (wuint)0x8b00u,
    wPIN_TIM12                              =     (wuint)0x8c00u,
    wPIN_TIM13                              =     (wuint)0x8d00u,
    wPIN_TIM14                              =     (wuint)0x8e00u,
//////////////////////////////////////////////////////////////////////////////////////

    wPIN_U1_A9A10                           =     (wuint)0xf011u,
    wPIN_U1_B6B7                            =     (wuint)0xf012u,
    wPIN_U2_A2A3                            =     (wuint)0xf021u,
    wPIN_U2_D5D6                            =     (wuint)0xf022u,
    wPIN_U3_B10B11                          =     (wuint)0xf031u,
    wPIN_U3_C10C11                          =     (wuint)0xf032u,
    wPIN_U3_D8D9                            =     (wuint)0xf033u,
    wPIN_U4_C10C11                          =     (wuint)0xf041u,
    wPIN_U5_C12D2                           =     (wuint)0xf042u,  

    wPIN_I2C1_B6B7                          =     (wuint)0xf111u,
    wPIN_I2C1_B8B9                          =     (wuint)0xf112u,
    wPIN_I2C2_B10B11                        =     (wuint)0xf121u, 

    wPIN_SPI1_A4A5A6A7                      =     (wuint)0xf211u,
    wPIN_SPI1_A15B3B4B5                     =     (wuint)0xf212u,
    wPIN_SPI2_B12B13B14B15                  =     (wuint)0xf221u,    
    wPIN_SPI3_A15B3B4B5                     =     (wuint)0xf231u,
    wPIN_SPI3_A4C10C11C12                   =     (wuint)0xf232u,
  
    wPIN_CAN1_A11A12                        =     (wuint)0xf311u,
    wPIN_CAN1_B8B9                          =     (wuint)0xf312u,    
    wPIN_CAN1_D0D1                          =     (wuint)0xf313u, 
    wPIN_CAN1_B12B13                        =     (wuint)0xf314u,  
    wPIN_CAN1_B5B6                          =     (wuint)0xf315u, 
    
//////////////////////////////////////////////////////////////////////////////////////
    #define  wPIN_ADC_MASK                    (wuint)0xFF00u

    wPIN_ADC1IN0_A0                     =     (wuint)0xf400u, 
    wPIN_ADC1IN1_A1                     =     (wuint)0xf401u,  
    wPIN_ADC1IN2_A2                     =     (wuint)0xf402u, 
    wPIN_ADC1IN3_A3                     =     (wuint)0xf403u, 
    wPIN_ADC1IN4_A4                     =     (wuint)0xf404u, 
    wPIN_ADC1IN5_A5                     =     (wuint)0xf405u, 
    wPIN_ADC1IN6_A6                     =     (wuint)0xf406u, 
    wPIN_ADC1IN7_A7                     =     (wuint)0xf407u, 
    wPIN_ADC1IN8_B0                     =     (wuint)0xf408u, 
    wPIN_ADC1IN9_B1                     =     (wuint)0xf409u, 
    wPIN_ADC1IN10_C0                    =     (wuint)0xf40au, 
    wPIN_ADC1IN11_C1                    =     (wuint)0xf40bu, 
    wPIN_ADC1IN12_C2                    =     (wuint)0xf40cu, 
    wPIN_ADC1IN13_C3                    =     (wuint)0xf40du, 
    wPIN_ADC1IN14_C4                    =     (wuint)0xf40eu,  
    wPIN_ADC1IN15_C5                    =     (wuint)0xf40fu, 
    wPIN_ADC1IN16_TEMP                  =     (wuint)0xf410u, 
    wPIN_ADC1IN17_VREF                  =     (wuint)0xf411u, 
    wPIN_ADC1IN18_VBAT                  =     (wuint)0xf412u, 
    
    wPIN_ADC2IN0_A0                     =     (wuint)0xf500u, 
    wPIN_ADC2IN1_A1                     =     (wuint)0xf501u, 
    wPIN_ADC2IN2_A2                     =     (wuint)0xf502u, 
    wPIN_ADC2IN3_A3                     =     (wuint)0xf503u, 
    wPIN_ADC2IN4_A4                     =     (wuint)0xf504u, 
    wPIN_ADC2IN5_A5                     =     (wuint)0xf505u, 
    wPIN_ADC2IN6_A6                     =     (wuint)0xf506u, 
    wPIN_ADC2IN7_A7                     =     (wuint)0xf507u, 
    wPIN_ADC2IN8_B0                     =     (wuint)0xf508u, 
    wPIN_ADC2IN9_B1                     =     (wuint)0xf509u, 
    wPIN_ADC2IN10_C0                    =     (wuint)0xf50Au, 
    wPIN_ADC2IN11_C1                    =     (wuint)0xf50Bu, 
    wPIN_ADC2IN12_C2                    =     (wuint)0xf50Cu, 
    wPIN_ADC2IN13_C3                    =     (wuint)0xf50Du, 
    wPIN_ADC2IN14_C4                    =     (wuint)0xf50Eu, 
    wPIN_ADC2IN15_C5                    =     (wuint)0xf50Fu, 

    wPIN_ADC3IN0_A0                     =     (wuint)0xf600u, 
    wPIN_ADC3IN1_A1                     =     (wuint)0xf601u, 
    wPIN_ADC3IN2_A2                     =     (wuint)0xf602u, 
    wPIN_ADC3IN3_A3                     =     (wuint)0xf603u, 
    wPIN_ADC3IN4_F6                     =     (wuint)0xf604u, 
    wPIN_ADC3IN5_F7                     =     (wuint)0xf605u, 
    wPIN_ADC3IN6_F8                     =     (wuint)0xf606u, 
    wPIN_ADC3IN7_F9                     =     (wuint)0xf607u, 
    wPIN_ADC3IN8_F10                    =     (wuint)0xf608u, 
    wPIN_ADC3IN9_F3                     =     (wuint)0xf609u, 
    wPIN_ADC3IN10_C0                    =     (wuint)0xf60Au, 
    wPIN_ADC3IN11_C1                    =     (wuint)0xf60Bu, 
    wPIN_ADC3IN12_C2                    =     (wuint)0xf60Cu, 
    wPIN_ADC3IN13_C3                    =     (wuint)0xf60Du, 
    wPIN_ADC3IN14_F4                    =     (wuint)0xf60Eu, 
    wPIN_ADC3IN15_F5                    =     (wuint)0xf60Fu, 
 

    #define  wPIN_ETH_MASK_D8                 (wuint)0x01u
    #define  wPIN_ETH_MASK_C4                 (wuint)0x02u
    #define  wPIN_ETH_MASK_B11                (wuint)0x10u
    #define  wPIN_ETH_MASK_G11                (wuint)0x20u
    
    wPIN_ETH_ModeD8B11                  =     (wuint)0xf711u,     
    wPIN_ETH_ModeC4B11                  =     (wuint)0xf712u,        
    wPIN_ETH_ModeD8G11                  =     (wuint)0xf721u,     
    wPIN_ETH_ModeC4G11                  =     (wuint)0xf722u,   


}wPin; 
	
#endif
