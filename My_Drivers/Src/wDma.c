
#include "Cpucfg.h"
#include "wIt.h" 
#include "wDma.h" 
#include "os.h" 

    DMA_HandleTypeDef*      Int_hdma1[8];
    DMA_HandleTypeDef*      Int_hdma2[8]; 
    
HAL_StatusTypeDef wDma_Init(DMA_HandleTypeDef* hdma, 
                            DMA_Stream_TypeDef* Instance,
                            uint32_t Channel,
                            uint32_t Direction,
                            uint32_t DataAlignment,
                            uint32_t Mode,
                            uint32_t Priority)
{
    __HAL_RCC_DMA1_CLK_ENABLE();
    __HAL_RCC_DMA2_CLK_ENABLE();        
  
    uint32_t   Preempt = NoUse_Pri;
    IRQn_Type  IRQn;
    
    if(Instance == DMA1_Stream0)
    {
        Preempt = DMA1_CS0_Pri;
        IRQn = DMA1_Stream0_IRQn;
        Int_hdma1[0] = hdma;        
    }
    else if(Instance == DMA1_Stream1)
    {
        Preempt = DMA1_CS1_Pri;
        IRQn = DMA1_Stream1_IRQn; 
        Int_hdma1[1] = hdma;        
    }
    else if(Instance == DMA1_Stream2)
    {
        Preempt = DMA1_CS2_Pri;
        IRQn = DMA1_Stream2_IRQn; 
        Int_hdma1[2] = hdma;         
    }    
    else if(Instance == DMA1_Stream3)
    {
        Preempt = DMA1_CS3_Pri;
        IRQn = DMA1_Stream3_IRQn; 
        Int_hdma1[3] = hdma;         
    }    
    else if(Instance == DMA1_Stream4)
    {
        Preempt = DMA1_CS4_Pri;
        IRQn = DMA1_Stream4_IRQn; 
        Int_hdma1[4] = hdma;         
    }    
    else if(Instance == DMA1_Stream5)
    {
        Preempt = DMA1_CS5_Pri;
        IRQn = DMA1_Stream5_IRQn; 
        Int_hdma1[5] = hdma;         
    }    
    else if(Instance == DMA1_Stream6)
    {
        Preempt = DMA1_CS6_Pri;
        IRQn = DMA1_Stream6_IRQn;
        Int_hdma1[6] = hdma;         
    }    
    else if(Instance == DMA1_Stream7)
    {
        Preempt = DMA1_CS7_Pri;
        IRQn = DMA1_Stream7_IRQn;
        Int_hdma1[7] = hdma;         
    }    
    else if(Instance == DMA2_Stream0)
    {
        Preempt = DMA2_CS0_Pri;
        IRQn = DMA2_Stream0_IRQn; 
        Int_hdma2[0] = hdma;         
    }    
    else if(Instance == DMA2_Stream1)
    {
        Preempt = DMA2_CS1_Pri;
        IRQn = DMA2_Stream1_IRQn; 	 
        Int_hdma2[1] = hdma;         
    } 
    else if(Instance == DMA2_Stream2)
    {
        Preempt = DMA2_CS2_Pri;
        IRQn = DMA2_Stream2_IRQn; 	
        Int_hdma2[2] = hdma;         
    } 
    else if(Instance == DMA2_Stream3)
    {
        Preempt = DMA2_CS3_Pri;
        IRQn = DMA2_Stream3_IRQn; 
        Int_hdma2[3] = hdma;         
    } 
    else if(Instance == DMA2_Stream4)
    {
        Preempt = DMA2_CS4_Pri;
        IRQn = DMA2_Stream4_IRQn; 
        Int_hdma2[4] = hdma;         
    } 
    else if(Instance == DMA2_Stream5)
    {
        Preempt = DMA2_CS5_Pri;
        IRQn = DMA2_Stream5_IRQn; 	
        Int_hdma2[5] = hdma;         
    } 
    else if(Instance == DMA2_Stream6)
    {
        Preempt = DMA2_CS6_Pri;
        IRQn = DMA2_Stream6_IRQn; 	
        Int_hdma2[6] = hdma;         
    } 
    else if(Instance == DMA2_Stream7)
    {
        Preempt = DMA2_CS7_Pri;
        IRQn = DMA2_Stream7_IRQn;
        Int_hdma2[7] = hdma;         
    }     
    else{}

        
//#if defined (STM32F105xC) 					
//                IRQn = DMA2_Channel4_IRQn;
//#else				
//                IRQn = DMA2_Channel4_5_IRQn;
//#endif					

//#if defined (STM32F105xC) 					
//                IRQn = DMA2_Channel5_IRQn;
//#else					
//                IRQn = DMA2_Channel4_5_IRQn;
//#endif		          
        
    if(Preempt != NoUse_Pri)
    {
        HAL_NVIC_SetPriority(IRQn, Preempt, 0);
        HAL_NVIC_EnableIRQ(IRQn); 
    }
    
    hdma->Instance = Instance;   
    hdma->Init.Channel = Channel; 
    hdma->Init.Direction = Direction;
    hdma->Init.PeriphInc = DMA_PINC_DISABLE;
    hdma->Init.MemInc = DMA_MINC_ENABLE;
    hdma->Init.PeriphDataAlignment = DataAlignment;
    hdma->Init.MemDataAlignment = DataAlignment;
    hdma->Init.Mode = Mode;
    hdma->Init.Priority = Priority;  

#if  defined(STM32F4)
    hdma->Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
    hdma->Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;  //DMA_FIFO_THRESHOLD_HALFFULL adc
    hdma->Init.MemBurst            = DMA_MBURST_INC4;
    hdma->Init.PeriphBurst         = DMA_PBURST_INC4;
	
    //hdma->Init.MemBurst            = DMA_MBURST_SINGLE;//spi adc
	//hdma->Init.PeriphBurst         = DMA_MBURST_SINGLE;//spi adc
#endif
    
    return HAL_DMA_Init(hdma); 
}

#if  defined(STM32F1)
void DMA1_Channel1_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma1[1] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma1[1]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA1_Channel1_IRQn);       
    } 	
    OSIntExit(); 
}

void DMA1_Channel2_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma1[2] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma1[2]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA1_Channel2_IRQn);       
    }  
    OSIntExit(); 
}

void DMA1_Channel3_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma1[3] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma1[3]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA1_Channel3_IRQn);       
    }
    OSIntExit(); 
}
void DMA1_Channel4_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma1[4] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma1[4]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA1_Channel4_IRQn);       
    }
    OSIntExit(); 
}
void DMA1_Channel5_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma1[5] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma1[5]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA1_Channel5_IRQn);       
    }
    OSIntExit(); 
}

void DMA1_Channel6_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma1[6] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma1[6]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA1_Channel6_IRQn);       
    }
    OSIntExit(); 
}
void DMA1_Channel7_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma1[7] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma1[7]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA1_Channel7_IRQn);       
    }
    OSIntExit(); 
}

void DMA2_Channel1_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma2[1] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma2[1]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA2_Channel1_IRQn);       
    }
    OSIntExit(); 
}
void DMA2_Channel2_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma2[2] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma2[2]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA2_Channel2_IRQn);       
    }
    OSIntExit(); 
}

void DMA2_Channel3_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma2[3] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma2[3]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA2_Channel3_IRQn);       
    }
    OSIntExit(); 
}

void DMA2_Channel4_5_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma2[4] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma2[4]);
    }
	
    if(Int_hdma2[5] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma2[5]);
    }

    if((Int_hdma2[4] == NULL) && (Int_hdma2[5] != NULL))
    {
        HAL_NVIC_ClearPendingIRQ(DMA2_Channel4_5_IRQn);       
    }
	
    OSIntExit(); 
}

#elif  defined(STM32F4)

void DMA1_Stream0_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma1[0] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma1[0]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA1_Stream0_IRQn);       
    }
    OSIntExit(); 
}

void DMA1_Stream1_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma1[1] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma1[1]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA1_Stream1_IRQn);       
    }
    OSIntExit(); 
}

void DMA1_Stream2_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma1[2] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma1[2]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA1_Stream2_IRQn);       
    }
    OSIntExit(); 
}

void DMA1_Stream3_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma1[3] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma1[3]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA1_Stream3_IRQn);       
    }  
    OSIntExit(); 
}

void DMA1_Stream4_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma1[4] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma1[4]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA1_Stream4_IRQn);       
    }
    OSIntExit(); 
} 

void DMA1_Stream5_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma1[5] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma1[5]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA1_Stream5_IRQn);       
    }
    OSIntExit(); 
}

void DMA1_Stream6_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma1[6] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma1[6]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA1_Stream6_IRQn);       
    }
    OSIntExit(); 
} 

void DMA1_Stream7_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma1[7] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma1[7]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA1_Stream7_IRQn);       
    }
    OSIntExit(); 
} 

void DMA2_Stream0_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma2[0] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma2[0]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA2_Stream0_IRQn);       
    }     
    OSIntExit(); 
}

void DMA2_Stream1_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma2[1] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma2[1]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA2_Stream1_IRQn);       
    }
    OSIntExit(); 
}

void DMA2_Stream2_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma2[2] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma2[2]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA2_Stream2_IRQn);       
    }
    OSIntExit(); 
}

void DMA2_Stream3_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma2[3] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma2[3]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA2_Stream3_IRQn);       
    }
    OSIntExit(); 
}

void DMA2_Stream4_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma2[4] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma2[4]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA2_Stream4_IRQn);       
    }
    OSIntExit(); 
}

void DMA2_Stream5_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma2[5] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma2[5]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA2_Stream5_IRQn);       
    }
    OSIntExit(); 
}

void DMA2_Stream6_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma2[6] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma2[6]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA2_Stream6_IRQn);       
    }
    OSIntExit(); 
}

void DMA2_Stream7_IRQHandler(void)
{
    OSIntEnter();
    if(Int_hdma2[7] != NULL)  
    {     
        HAL_DMA_IRQHandler(Int_hdma2[7]);
    }
    else
    {
        HAL_NVIC_ClearPendingIRQ(DMA2_Stream7_IRQn);       
    }
    OSIntExit(); 
}

#endif
