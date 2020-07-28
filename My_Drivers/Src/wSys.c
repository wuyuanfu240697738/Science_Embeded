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

/* Filename    : wSys.c*/

    #include "wSys.h"  
    #include "os.h"
    #include "wSerial.h"

#if WS_CFG_SPI_EN == WS_DEF_ENABLED
    #include "wSpi.h"
#endif 

OS_TMR      Tmr_Sys; 

void wSys_DisAll(void)
{
    
#if WS_CFG_SPI_EN == WS_DEF_ENABLED
    wSpi_DisAll();
#endif 
    
#if WS_CFG_UART_EN == WS_DEF_ENABLED
    wUart_DisAll();
#endif       
    
}

 uint8_t wSys_ResetCheck(void)
 {
    uint8_t RCC_FLAG =0;

#if  defined(STM32F4) 
    /* 检查欠电压复位 */
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_BORRST) != RESET)
    {
        RCC_FLAG |= 0x01;
        wDebug("BOR RST\n");
    }
#endif 
     
    /* 检查 NRST 引脚复位 */
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST) != RESET)
    {
        RCC_FLAG |= 0x02;
        wDebug("NRST RST\n");
    }
    
    /* 检查上电/掉电复位*/
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST) != RESET)
    {
        RCC_FLAG |= 0x04;
        wDebug("POR RST\n");
    }
    
    /* 检查软件复位*/
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST) != RESET)
    {
        RCC_FLAG |= 0x08;
        wDebug("SFT RST\n");
    }
    /* 检测独立看门狗复位*/
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST) != RESET)
    {
        RCC_FLAG |= 0x10;
        wDebug("IWDG RST\n");
    }
    
    /* 检测独立看门狗复位*/
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST) != RESET)
    {
        RCC_FLAG |= 0x20;
        wDebug("WWDG RST\n");
    }
    
    /* 检测低功耗复位*/
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_LPWRRST) != RESET)
    {
        RCC_FLAG |= 0x40;
        wDebug("LPWR RST\n");
    }    
    
    /* 清楚复位源标志位 */
    __HAL_RCC_CLEAR_RESET_FLAGS();     
    
    return RCC_FLAG;
 }     
 
static void wSys_TmrReset(void *p_tmr, void *p_arg)
{
    __disable_irq();
    HAL_RCC_DeInit();
    HAL_NVIC_SystemReset();
}    
 
void HAL_MspInit(void)
{
    OS_ERR  oserr;
    
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();

    #if  defined(STM32F1)   
        __HAL_RCC_AFIO_CLK_ENABLE();    
        __HAL_AFIO_REMAP_SWJ_NOJTAG();//如果需使用pb3/4/5口，必须加上
    #endif    

	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	
    /* MemoryManagement_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
    /* BusFault_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
    /* UsageFault_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
    /* SVCall_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
    /* DebugMonitor_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
    
    //PendSV中断的优先级最低
    /* PendSV_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);
    /* SysTick_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SysTick_IRQn, 8, 0);
    
    OSTmrCreate (&Tmr_Sys,"Tmr_Sys",0,0,OS_OPT_TMR_ONE_SHOT,wSys_TmrReset,0,&oserr);//创建定时器  
}
 
void wSys_Reset(uint32_t timeout)
{
    OS_ERR  oserr;
    if(timeout > 0)
    {
        timeout = timeout * OS_CFG_TMR_TASK_RATE_HZ / 1000;
        OSTmrSet(&Tmr_Sys,timeout,timeout,wSys_TmrReset,0,&oserr);
        OSTmrStart(&Tmr_Sys,&oserr); 
    }
    else
    {
        wSys_TmrReset(0,0);//立即复位
    }
}

uint32_t  wSys_GetClkFreq (void)
{//获取CPU运行时钟
    return (uint32_t) HAL_RCC_GetHCLKFreq();
}

uint8_t wSys_ClockConfig(uint32_t Clock,uint32_t Ticks)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    HAL_Init();   /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

    __HAL_RCC_PWR_CLK_ENABLE();
    
#if  defined(STM32F4) 
    __HAL_RCC_GPIOH_CLK_ENABLE();
    //时使性能与功耗实现平衡，此功能只有STM32F42xx和STM32F43xx器件有
    //设置调压器输出电压级别1
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1); 
    
#endif 
    
    /** Initializes the CPU, AHB and APB busses clocks */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    //RCC_OscInitStruct.LSEState = RCC_LSE_ON;  
    RCC_OscInitStruct.HSIState = RCC_HSI_ON; 
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE; 
    
#if defined(STM32F1)  
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;//F1 
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;//F1

#if defined (STM32F107xC)
    RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_HSE;//8M
    RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL_NONE;//8M
    if(Clock == CLOCK_25M)
    {
        RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV5;
        RCC_OscInitStruct.PLL2.PLL2MUL = RCC_PLL2_MUL8;
        RCC_OscInitStruct.PLL2.HSEPrediv2Value = RCC_HSE_PREDIV2_DIV5;
        RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_PLL2;//25M
        RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL2_ON;//25M    
    } 
#endif
    
#elif defined(STM32F4)
    
    RCC_OscInitStruct.PLL.PLLM = Clock;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;
  
#endif    
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        return 1;
    }
    
    /**Initializes the CPU, AHB and APB busses clocks */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
#if  defined(STM32F1)     
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        return 1;
    }  
#elif  defined(STM32F4)     
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)    
//    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
        return 1;
    }  
#endif 

    HAL_RCC_EnableCSS();        // 使能CSS功能，优先使用外部晶振，内部时钟源为备用

#if defined (STM32F107xC)
    __HAL_RCC_PLLI2S_ENABLE();
#endif  
    
#if  defined(STM32F4) 
    /* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported  */
    if (HAL_GetREVID() == 0x1001)
    {
        /* Enable the Flash prefetch */
        __HAL_FLASH_PREFETCH_BUFFER_ENABLE();//使能flash预取
    }
#endif

#if  defined(STM32F1) 

  RCC_PeriphCLKInitTypeDef PeriphClkInit;
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBPLLCLK_DIV1;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
  
#endif

    /* 配置MCO输出引脚 : PA8 */
//    wGpio_Init(wPIN_A8,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_VERY_HIGH,GPIO_AF0_MCO);//PA8  MCO
    //使能MCO输出，输出为外部高速时钟:8MHz
//    HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_PLLCLK, RCC_MCODIV_3);   
  
    /**Configure the Systick interrupt time */
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/Ticks);
    /**Configure the Systick */
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    
    __enable_irq(); //使能中断

    return 0;    
}   
