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


#include "Cpucfg.h"

/*
    F1最高频率为2.25Mb/s 或4.5Mb/s  F4最高频率为10.5Mb/s
*/

#if (WS_CFG_UART_EN == WS_DEF_ENABLED) 

#include "wUart.h"   
#include "wIt.h"  
#include "wDma.h" 
#include "os.h" 

wUart_Def* wUart_ListPtr;//起始链表指针

UART_HandleTypeDef*     Int_huart[wUart_Num];

static void wUart_List(wUart_Def *p_Uart)
{
    //需要查询原有的链表中是否已经注册，如已经注册过，则无需再次注册
    wUart_Def* p_list = wUart_ListPtr; 
    
    while(p_list != (wUart_Def *)NULL)
    {
        if(p_list == p_Uart){break;}
        else{p_list = p_list->NextPtr;}
    }
    if(p_list != p_Uart)
    {
        //如还未注册过，则需注册
        if( wUart_ListPtr == (wUart_Def *)NULL )
        {
            p_Uart->NextPtr = (wUart_Def *)NULL;
            wUart_ListPtr = p_Uart;
        }
        else
        {
            p_Uart->NextPtr = wUart_ListPtr;
            wUart_ListPtr = p_Uart;
        }
    } 
}

static void wUart_CSSEnable( UART_HandleTypeDef *huart,uint8_t xEnable )
{
	wUart_Def  *p_Uart = wUart_ListPtr;
	
	while (p_Uart != (wUart_Def *)NULL)
    {
        if(huart == &p_Uart->huart)
        {
             if (p_Uart->CSS.EN==ENABLE)
            {    
                if(xEnable == wTxEnable)
                {
                    wGpio_putWrite(&p_Uart->CSS,Set_INACTIVE);
                }
                else
                {
                    wGpio_putWrite(&p_Uart->CSS,Set_ACTIVE);
                }       
            }         
            break;
        }
        p_Uart = p_Uart->NextPtr;
    } 
}

void HAL_UART_RxCpltCallback_Idle(UART_HandleTypeDef *huart)
{ 
    wUart_Def  *p_Uart = wUart_ListPtr;
    
    if(__HAL_UART_GET_FLAG(huart,UART_FLAG_IDLE) != RESET)  
    { 
        
#if  defined(STM32F1)    
    uint32_t length = huart->RxXferSize - huart->hdmarx->Instance->CNDTR;   
#elif  defined(STM32F4)
    uint32_t length = huart->RxXferSize - huart->hdmarx->Instance->NDTR;      
#endif 
        wUart_AbortReceive(huart); 
        
        while (p_Uart != (wUart_Def *)NULL)
        {
            if(huart == &p_Uart->huart)
            {
                if( p_Uart->RxCplt_IdlePtr != (UartRxCpltFnct_Idle )NULL)
                {
                    p_Uart->RxCplt_IdlePtr(huart,length);
                }                
                break;           
            }
            p_Uart = p_Uart->NextPtr;
        }        
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    wUart_Def  *p_Uart = wUart_ListPtr;
    
    wUart_CSSEnable( huart,wRxEnable );
    __HAL_UART_CLEAR_FLAG(huart, UART_IT_TC | UART_IT_TXE);//清中断

    while (p_Uart != (wUart_Def *)NULL)
    {
        if(huart == &p_Uart->huart)
        {
            if( p_Uart->TxCpltPtr != (UartTxCpltFnct )NULL)
            {
                p_Uart->TxCpltPtr(huart);
            }               
            break;           
        }
        p_Uart = p_Uart->NextPtr;
    }
}

void wUart_SetCallback(wUart_Def *p_Uart,UartTxCpltFnct TxCpltPtr,UartRxCpltFnct_Idle RxCplt_IdlePtr)
{
    if(p_Uart != (wUart_Def *)NULL)
    {
        p_Uart->TxCpltPtr = TxCpltPtr;
        p_Uart->RxCplt_IdlePtr = RxCplt_IdlePtr;
    }
}

void wUart_CSSInit(wUart_Def *p_Uart,wPin pin,wGpio_Level level)
{
    wGpio_putInit(&p_Uart->CSS,pin,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,level); 
    wGpio_putWrite(&p_Uart->CSS,Set_INACTIVE);
}

UART_HandleTypeDef* wUart_Init(wUart_Def *p_Uart,wPin Pin,uint32_t BaudRate,uint32_t StopBits,uint32_t Parity,uint32_t Trans)
{	
	UART_HandleTypeDef* huart = &p_Uart->huart;
	
    uint32_t   Preempt = NoUse_Pri;
    IRQn_Type  IRQn;
    
    if((Pin==wPIN_U1_A9A10) || (Pin==wPIN_U1_B6B7))
    {
        huart->Instance=USART1;
        __HAL_RCC_USART1_CLK_ENABLE();
		
        if(Pin==wPIN_U1_A9A10)
        {       
#if  defined(STM32F1)
            __HAL_AFIO_REMAP_USART1_DISABLE();
#endif             
            wGpio_Init(wPIN_A9,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_AF7_USART1);
            wGpio_Init(wPIN_A10,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_AF7_USART1);  
        }else
        {
#if  defined(STM32F1)            
            __HAL_AFIO_REMAP_USART1_ENABLE();   
#endif    			
            wGpio_Init(wPIN_B6,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_AF7_USART1);
            wGpio_Init(wPIN_B7,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_AF7_USART1); 
        }
        
        Preempt = USART1_Pri;
        IRQn = USART1_IRQn;   
        Int_huart[0] = huart;
    }
    else if((Pin==wPIN_U2_A2A3) || (Pin==wPIN_U2_D5D6))
    {
        huart->Instance=USART2;
        __HAL_RCC_USART2_CLK_ENABLE();
        if(Pin==wPIN_U2_A2A3)
        {
#if  defined(STM32F1)               
            __HAL_AFIO_REMAP_USART2_DISABLE();   
#endif  			
            wGpio_Init(wPIN_A2,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_AF7_USART2);
            wGpio_Init(wPIN_A3,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_AF7_USART2); 
          
        }else
        { 
#if  defined(STM32F1)               
            __HAL_AFIO_REMAP_USART2_ENABLE();     
#endif  
            wGpio_Init(wPIN_D5,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_AF7_USART2);
            wGpio_Init(wPIN_D6,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_AF7_USART2);  
        }
        Preempt = USART2_Pri;
        IRQn = USART2_IRQn; 
        Int_huart[1] = huart;        
    }
    else if((Pin==wPIN_U3_B10B11) || (Pin==wPIN_U3_C10C11) || (Pin==wPIN_U3_D8D9))
    {
        huart->Instance=USART3;
        __HAL_RCC_USART3_CLK_ENABLE();
        if(Pin==wPIN_U3_B10B11)
        {          
#if  defined(STM32F1)               
            __HAL_AFIO_REMAP_USART3_DISABLE();  
#endif  			
            wGpio_Init(wPIN_B10,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_AF7_USART3);
            wGpio_Init(wPIN_B11,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_AF7_USART3);  
        }else if(Pin==wPIN_U3_C10C11)
        {          
#if  defined(STM32F1)               
            __HAL_AFIO_REMAP_USART3_PARTIAL();  
#endif			
            wGpio_Init(wPIN_C10,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_AF7_USART3);
            wGpio_Init(wPIN_C11,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_AF7_USART3);             
        }else
        {
#if  defined(STM32F1)               
            __HAL_AFIO_REMAP_USART3_ENABLE();     
#endif 
            wGpio_Init(wPIN_D8,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_AF7_USART3);
            wGpio_Init(wPIN_D9,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_AF7_USART3);
        } 
        Preempt = USART3_Pri;
        IRQn = USART3_IRQn; 
        Int_huart[2] = huart;         
    }
    else if(Pin==wPIN_U4_C10C11)
    {
        huart->Instance=UART4;
        __HAL_RCC_UART4_CLK_ENABLE();
        wGpio_Init(wPIN_C10,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_AF8_UART4);
        wGpio_Init(wPIN_C11,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_AF8_UART4);  
        Preempt = UART4_Pri;
        IRQn = UART4_IRQn;  
        Int_huart[3] = huart; 		
	}
    else if(Pin==wPIN_U5_C12D2)
    {
        huart->Instance=UART5;
        __HAL_RCC_UART5_CLK_ENABLE();
        wGpio_Init(wPIN_C12,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_AF8_UART5);
        wGpio_Init(wPIN_D2,GPIO_MODE_AF_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_AF8_UART5);  
        Preempt = UART5_Pri;
        IRQn = UART5_IRQn; 
        Int_huart[4] = huart;         
    }
    else
        {return NULL;}  

        
#if defined (STM32F405xx) || defined (STM32F415xx) || defined (STM32F407xx) || defined (STM32F417xx) || \
defined (STM32F427xx) || defined (STM32F437xx) || defined (STM32F429xx) || defined (STM32F439xx) || \
defined (STM32F401xC) || defined (STM32F401xE) || defined (STM32F410Tx) || defined (STM32F410Cx) || \
defined (STM32F410Rx) || defined (STM32F411xE) || defined (STM32F446xx) || defined (STM32F469xx) || \
defined (STM32F479xx) || defined (STM32F412Cx) || defined (STM32F412Rx) || defined (STM32F412Vx) || \
defined (STM32F412Zx) || defined (STM32F413xx) || defined (STM32F423xx)
        //case wIRQ_USART6        	:

#endif

#if defined (STM32F415xx) || defined (STM32F417xx) || \
defined (STM32F427xx) || defined (STM32F437xx) || defined (STM32F429xx) || defined (STM32F439xx) || \
defined (STM32F401xC) || defined (STM32F401xE) || defined (STM32F410Tx) || defined (STM32F410Cx) || \
defined (STM32F410Rx) || defined (STM32F411xE) || defined (STM32F446xx) || defined (STM32F469xx) || \
defined (STM32F479xx) || defined (STM32F412Cx) || defined (STM32F412Rx) || defined (STM32F412Vx) || \
defined (STM32F412Zx) || defined (STM32F413xx) || defined (STM32F423xx)
        //case wIRQ_UART7        	:

#endif        

    if(Preempt != NoUse_Pri)
    {
        HAL_NVIC_SetPriority(IRQn, Preempt, 0);
        HAL_NVIC_EnableIRQ(IRQn); 
    }
        
    wUart_List(p_Uart);   
    huart->Init.BaudRate = BaudRate;
        
    if(StopBits==2)
    {
        huart->Init.StopBits = UART_STOPBITS_2;
    }
    else
    {
       huart->Init.StopBits = UART_STOPBITS_1;
    }
    
    if(IS_UART_PARITY(Parity))
    {
        huart->Init.Parity = Parity;
    }
    else
    {
        huart->Init.Parity = UART_PARITY_NONE;
    }
    
    if(huart->Init.Parity == UART_PARITY_NONE)
    {
        huart->Init.WordLength = UART_WORDLENGTH_8B;
    }
    else
    {
        huart->Init.WordLength = UART_WORDLENGTH_9B;
    }
    
    huart->Init.HwFlowCtl = UART_HWCONTROL_NONE; 
    huart->Init.OverSampling = UART_OVERSAMPLING_16; //在波特率较大切换UART_OVERSAMPLING_8
    huart->Init.Mode = Trans & 0x00ff;
    if (HAL_UART_Init(huart) != HAL_OK)
    {
        return NULL;
    }
	
    return huart;
}

UART_HandleTypeDef* wUart_DMAInit(wUart_Def *p_Uart,wPin Pin,uint32_t BaudRate,uint32_t StopBits,uint32_t Parity,uint32_t Trans)
{
    
	UART_HandleTypeDef* huart = wUart_Init(p_Uart,Pin,BaudRate,StopBits,Parity,Trans); 
    
	if(huart== NULL) {return NULL;}

    if((Trans & UART_MODE_TX) == UART_MODE_TX)
	{//发送
        __HAL_LINKDMA(huart,hdmatx,p_Uart->hdma_tx);         
        if(huart->Instance==USART1)
        {
            huart->hdmatx->Instance = DMA_USART1_TX_Instance;
            wDma_Init(huart->hdmatx,DMA_USART1_TX_Instance,DMA_CHANNEL_4,DMA_MEMORY_TO_PERIPH,DMA_PDATAALIGN_BYTE,DMA_NORMAL,DMA_PRIORITY_HIGH);
        }else if(huart->Instance==USART2)
        {          
            huart->hdmatx->Instance = DMA_USART2_TX_Instance;  
            wDma_Init(huart->hdmatx,DMA_USART2_TX_Instance,DMA_CHANNEL_4,DMA_MEMORY_TO_PERIPH,DMA_PDATAALIGN_BYTE,DMA_NORMAL,DMA_PRIORITY_HIGH);
        }else if(huart->Instance==USART3)
        {
           huart->hdmatx->Instance = DMA_USART3_TX_Instance;    
           wDma_Init(huart->hdmatx,DMA_USART3_TX_Instance,DMA_CHANNEL_4,DMA_MEMORY_TO_PERIPH,DMA_PDATAALIGN_BYTE,DMA_NORMAL,DMA_PRIORITY_HIGH);
        }else if(huart->Instance==UART4)
        {            
            huart->hdmatx->Instance = DMA_USART4_TX_Instance;
            wDma_Init(huart->hdmatx,DMA_USART4_TX_Instance,DMA_CHANNEL_4,DMA_MEMORY_TO_PERIPH,DMA_PDATAALIGN_BYTE,DMA_NORMAL,DMA_PRIORITY_HIGH);
        }
    }
    
    if((Trans & UART_MODE_RX) == UART_MODE_RX)
    {
        __HAL_LINKDMA(huart,hdmarx,p_Uart->hdma_rx);  

        if(huart->Instance==USART1)
        {
            huart->hdmarx->Instance = DMA_USART1_RX_Instance;  
            wDma_Init(huart->hdmarx,DMA_USART1_RX_Instance,DMA_CHANNEL_4,DMA_PERIPH_TO_MEMORY,DMA_PDATAALIGN_BYTE,DMA_CIRCULAR,DMA_PRIORITY_LOW);
        }else if(huart->Instance==USART2)
        {       
            huart->hdmarx->Instance = DMA_USART2_RX_Instance;    
            wDma_Init(huart->hdmarx,DMA_USART2_RX_Instance,DMA_CHANNEL_4,DMA_PERIPH_TO_MEMORY,DMA_PDATAALIGN_BYTE,DMA_CIRCULAR,DMA_PRIORITY_LOW);   
        }else if(huart->Instance==USART3)
        {
            huart->hdmarx->Instance = DMA_USART3_RX_Instance;
            uint32_t Channel = DMA_CHANNEL_4;
            if(DMA1_Stream4 == DMA_USART3_RX_Instance)
            {
                Channel = DMA_CHANNEL_7;
            }
            wDma_Init(huart->hdmarx,DMA_USART3_RX_Instance,Channel,DMA_PERIPH_TO_MEMORY,DMA_PDATAALIGN_BYTE,DMA_CIRCULAR,DMA_PRIORITY_LOW);       
        }else if(huart->Instance==UART4)
        {       
            huart->hdmarx->Instance = DMA_USART4_RX_Instance;
            wDma_Init(huart->hdmarx,DMA_USART4_RX_Instance,DMA_CHANNEL_4,DMA_PERIPH_TO_MEMORY,DMA_PDATAALIGN_BYTE,DMA_CIRCULAR,DMA_PRIORITY_LOW);       
        }
    }
    /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
    //__HAL_UART_ENABLE_IT(huart, UART_IT_ERR); 
    return huart ;
}

HAL_StatusTypeDef wUart_DMAReceive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
    /* Clean the input path */
    //__HAL_UART_FLUSH_DRREGISTER(huart);
    
    __HAL_UART_CLEAR_FLAG(huart, UART_IT_RXNE);
    __HAL_UART_CLEAR_IDLEFLAG(huart);
    
    __HAL_UART_ENABLE_IT(huart,UART_IT_RXNE); //使能空闲中断    
    __HAL_UART_ENABLE_IT(huart,UART_IT_IDLE); //使能空闲中断

    wUart_CSSEnable( huart,wRxEnable ); 
    return HAL_UART_Receive_DMA(huart,pData,Size);//开始接收数据    
}

HAL_StatusTypeDef wUart_DMATransmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
    wUart_CSSEnable( huart,wTxEnable ); 
    return HAL_UART_Transmit_DMA(huart,pData,Size);//开始接收数据    
}

void wUart_AbortReceive(UART_HandleTypeDef *huart)
{
    //__HAL_UART_DISABLE_IT(huart,UART_IT_RXNE); //关闭空闲中断     
    __HAL_UART_DISABLE_IT(huart,UART_IT_IDLE); //关闭空闲中断      
    
    __HAL_UART_CLEAR_FLAG(huart, UART_IT_RXNE);
    __HAL_UART_CLEAR_IDLEFLAG(huart); //清空闲中断    
    
    HAL_UART_AbortReceive_IT(huart); //停止uart接收功能
}

void wUart_ErrFlagCheck(UART_HandleTypeDef *huart)
{
    if(((__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE))!=RESET) 
     ||((__HAL_UART_GET_FLAG(huart, UART_FLAG_PE)) !=RESET) 
     ||((__HAL_UART_GET_FLAG(huart, UART_FLAG_FE)) !=RESET) 
     ||((__HAL_UART_GET_FLAG(huart, UART_FLAG_NE)) !=RESET))
    {
        READ_REG(huart->Instance->DR);
        __HAL_UART_CLEAR_PEFLAG(huart);
    }       
}

void wUart_DisAll(void)
{
    //关闭spi服务 
    for(int i=0;i<wUart_Num;i++)
    {
        if(Int_huart[i] != NULL)
        {
            HAL_UART_DeInit(Int_huart[i]);
        }
    }  
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
    if(huart->hdmatx != NULL)
    {/* */
        HAL_DMA_DeInit(huart->hdmatx);          
    }
    
    if(huart->hdmarx != NULL)
    {/* */
        HAL_DMA_DeInit(huart->hdmarx);            
    }
 
    if(huart->Instance == USART1)
    {
        __HAL_RCC_USART1_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(USART1_IRQn);                
    }
    else if(huart->Instance == USART2)
    {
        __HAL_RCC_USART2_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(USART2_IRQn);             
    }
    else if(huart->Instance == USART3)
    {
        __HAL_RCC_USART3_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(USART3_IRQn);          
    }
    else if(huart->Instance == UART4)
    {
        __HAL_RCC_UART4_CLK_DISABLE();         
        HAL_NVIC_DisableIRQ(UART4_IRQn);     
    }
    else if(huart->Instance == UART5)
    {
        __HAL_RCC_UART5_CLK_DISABLE();          
        HAL_NVIC_DisableIRQ(UART5_IRQn);   
    }
    else
    {
        /*表明出错*/
    }    
}


void USART1_IRQHandler(void)
{
    OSIntEnter();
    
    if(Int_huart[0] != NULL)  
    {
		HAL_UART_RxCpltCallback_Idle(Int_huart[0]);		
        HAL_UART_IRQHandler(Int_huart[0]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(USART1_IRQn);       
    }	   
    OSIntExit(); 
}

void USART2_IRQHandler(void)
{
    OSIntEnter();
    if(Int_huart[1] != NULL)  
    {
		HAL_UART_RxCpltCallback_Idle(Int_huart[1]);		
        HAL_UART_IRQHandler(Int_huart[1]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(USART2_IRQn);       
    }     
    OSIntExit(); 
}

void USART3_IRQHandler(void)
{
    OSIntEnter();    
    if(Int_huart[2] != NULL)  
    {
		HAL_UART_RxCpltCallback_Idle(Int_huart[2]);		
        HAL_UART_IRQHandler(Int_huart[2]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(USART3_IRQn);       
    }  
    OSIntExit(); 
}

void UART4_IRQHandler(void)
{
    OSIntEnter();
    if(Int_huart[3] != NULL)  
    {
		HAL_UART_RxCpltCallback_Idle(Int_huart[3]);		
        HAL_UART_IRQHandler(Int_huart[3]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(UART4_IRQn);       
    }    
    OSIntExit(); 
}


void UART5_IRQHandler(void)
{
    OSIntEnter();
    if(Int_huart[4] != NULL)  
    {
		HAL_UART_RxCpltCallback_Idle(Int_huart[4]);		
        HAL_UART_IRQHandler(Int_huart[4]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(UART5_IRQn);       
    }     
    OSIntExit(); 
}


#if defined (STM32F405xx) || defined (STM32F415xx) || defined (STM32F407xx) || defined (STM32F417xx) || \
    defined (STM32F427xx) || defined (STM32F437xx) || defined (STM32F429xx) || defined (STM32F439xx) || \
    defined (STM32F401xC) || defined (STM32F401xE) || defined (STM32F410Tx) || defined (STM32F410Cx) || \
    defined (STM32F410Rx) || defined (STM32F411xE) || defined (STM32F446xx) || defined (STM32F469xx) || \
    defined (STM32F479xx) || defined (STM32F412Cx) || defined (STM32F412Rx) || defined (STM32F412Vx) || \
    defined (STM32F412Zx) || defined (STM32F413xx) || defined (STM32F423xx)
void USART6_IRQHandler(void)
{
    OSIntEnter();
    if(Int_huart[5] != NULL)  
    {
		HAL_UART_RxCpltCallback_Idle(Int_huart[5]);		
        HAL_UART_IRQHandler(Int_huart[5]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(USART6_IRQn);       
    }     
    OSIntExit(); 
}
#endif

#if defined (STM32F415xx) || defined (STM32F417xx) || \
    defined (STM32F427xx) || defined (STM32F437xx) || defined (STM32F429xx) || defined (STM32F439xx) || \
    defined (STM32F401xC) || defined (STM32F401xE) || defined (STM32F410Tx) || defined (STM32F410Cx) || \
    defined (STM32F410Rx) || defined (STM32F411xE) || defined (STM32F446xx) || defined (STM32F469xx) || \
    defined (STM32F479xx) || defined (STM32F412Cx) || defined (STM32F412Rx) || defined (STM32F412Vx) || \
    defined (STM32F412Zx) || defined (STM32F413xx) || defined (STM32F423xx)

void UART7_IRQHandler(void)
{
    OSIntEnter();
    if(Int_huart[6] != NULL)  
    {
		HAL_UART_RxCpltCallback_Idle(Int_huart[6]);		
        HAL_UART_IRQHandler(Int_huart[6]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(UART7_IRQn);       
    }     
    OSIntExit(); 
}
#endif

#endif
