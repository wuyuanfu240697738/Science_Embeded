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

/* Filename    : wSerial.c*/

#define     WS_INC_wSERIAL
#include "Cpucfg.h"

#if (WS_CFG_UART_EN == WS_DEF_ENABLED) 

#include "wSerial.h" 
#include "wSprintf.h"

#include <stdlib.h>

void wSerial_RxIdleIRQHandler(UART_HandleTypeDef *huart,uint32_t length); 
void wSerial_TxIRQHandler(UART_HandleTypeDef *huart);

static wSerial_Def Serial[Serial_Num];

wStatus wSerial_Init(uint8_t Id,wPin PortPin,uint32_t BaudRate ,uint32_t StopBits,uint32_t Parity)
{//���ڳ�ʹ������  ������˿ڡ������ʡ��ֳ���ֹͣλ��У��λ
    wStatus Status = wOK; 
    OS_ERR oserr;

    if(Id < Serial_Num)
    {
        wSerial_Def *pto = &Serial[Id];  
        
        OSSemCreate(&pto->TxSemflg, "wSerial Tx Tfg",0,&oserr ); //���������ź���
        OSSemCreate(&pto->RxSemflg, "wSerial Rx Rfg",0,&oserr ); //���������ź���
        wUart_DMAInit(&pto->Uart,PortPin,BaudRate,StopBits,Parity,UART_MODE_TX_RX );//ʵ�����ײ�uart�˿ڴ�dma��ʽ�ĳ�ʹ��
        wUart_SetCallback(&pto->Uart,wSerial_TxIRQHandler,wSerial_RxIdleIRQHandler);//�趨�ص�����
    }
    else
    {
        Status = wERROR;
    } 
        
    return Status;       
}

wStatus wSerial_CSSInit(uint8_t Id,wPin CnPin,wGpio_Level level)
{
    wStatus Status = wOK; 
    if(Id < Serial_Num)
    {
        wSerial_Def *p_Serial = &Serial[Id];  
        wUart_CSSInit(&p_Serial->Uart,CnPin,level);
    } 
    else
    {
        Status = wERROR;
    } 
        
    return Status;       
}

wStatus wSerial_Transmit(uint8_t Id, uint8_t *pData, uint16_t Size,uint32_t Timeout)
{//��������+���������ʱ��  ֱ�ӷ�������
    wStatus Status = wOK; 
    OS_ERR oserr;

    if(Id < Serial_Num)
    {
        wSerial_Def *p_Serial = &Serial[Id];  
        OSSemSet(&p_Serial->TxSemflg,0, &oserr); //���ź����� 
        wUart_DMATransmit(&p_Serial->Uart.huart,pData,Size); //�������� 
        OSSemPend(&p_Serial->TxSemflg, Timeout, OS_OPT_PEND_BLOCKING, NULL, &oserr);//�����������ȴ��������
    }
    else
    {
        Status = wERROR;
    } 
        
    return Status;      
}

wStatus wSerial_PrintfHex(uint8_t Id,void* buf,uint16_t len)
{//������ӡ����---������printf���� �������ɴ�ӡ5���ֽ�
    wStatus Status = wOK; 

    char* pbuf = buf;
    if(Id < Serial_Num)
    {
        uint16_t Size = 0;
        char *p = (char *)malloc( len * 3 * sizeof(char) + 20 );
        if(p != wNULL)
        {
            for(uint16_t i=0;i<len;i++)
            {
                Size += wsprintf(&p[3*i],"%02x ",pbuf[i]);//���ݴ���
            }
            
            Size += wsprintf(&p[3*len],"\r\n");//���ݴ���
            wSerial_Transmit(Id,(uint8_t *)p, Size, 2000);//ֱ�ӷ�������
            free(p);
            p = wNULL;
        } 
    }
    else
    {
        Status = wERROR;
    } 
    return Status;      
}


wStatus wSerial_Printf(uint8_t Id,char* fmt,...)
{//������ӡ����---������printf���� �������ɴ�ӡ256���ֽ�
    wStatus Status = wOK; 
    
    if(Id < Serial_Num)
    {
        uint16_t Size = 0;
        va_list args;
        va_start(args, fmt);
        char *p = (char *)malloc( 256 * sizeof(char) );
        if(p != wNULL)
        {
            Size = wvsprintf(p,fmt,args);//���ݴ���
            wSerial_Transmit(Id,(uint8_t *)p, Size, 0);//ֱ�ӷ�������
            free(p);
            p = wNULL;
        }
        va_end(args);  
    }
    else
    {
        Status = wERROR;
    } 
        
    return Status;      
}

uint16_t wSerial_Receive(uint8_t Id, uint8_t *pData, uint16_t Size,uint32_t Timeout)
{//��������+����������ʱ��
    OS_ERR oserr;
    uint16_t Revlen = 0;
    
    if(Id < Serial_Num)
    {
        wSerial_Def *p_Serial = &Serial[Id];  
            
        OSSemSet(&p_Serial->RxSemflg,0, &oserr);//������  
        
        wUart_DMAReceive(&p_Serial->Uart.huart,pData,Size);//��ʼ��������
        
        OSSemPend(&p_Serial->RxSemflg, Timeout, OS_OPT_PEND_BLOCKING, NULL, &oserr);//�ȴ�����  Timeoutһ����0
        if((Timeout != 0)&&(oserr == OS_ERR_TIMEOUT))
        {//���ճ�ʱ          
            wUart_AbortReceive(&p_Serial->Uart.huart); //ֹͣuart���չ���
            Revlen = 0;//���ճ�����0
        }
        else
        {
            if(p_Serial->length < Size)
            {
                pData[p_Serial->length] = 0;//β����0
            }
            Revlen = p_Serial->length;
        }
    }
    return Revlen;//���س���ֵ
}


uint16_t wSerial_TransmitReceive(uint8_t Id, uint8_t *pData, uint16_t TSize, uint16_t RSize,uint32_t Timeout)
{// ֱ�ӷ������� + ��������
    OS_ERR oserr;
    uint16_t Revlen = 0;
    
    if(Id < Serial_Num)
    {
        wSerial_Def *p_Serial = &Serial[Id];  
        OSSemSet(&p_Serial->TxSemflg,0, &oserr);    //���ź����� 
        OSSemSet(&p_Serial->RxSemflg,0, &oserr);    //������  
        
        wUart_DMATransmit(&p_Serial->Uart.huart,pData,TSize); //�������� 
        
        OSSemPend(&p_Serial->TxSemflg, Timeout, OS_OPT_PEND_BLOCKING, NULL, &oserr);//�����������ȴ��������
        
        wUart_DMAReceive(&p_Serial->Uart.huart,pData,RSize);//��ʼ��������
        
        OSSemPend(&p_Serial->RxSemflg, Timeout, OS_OPT_PEND_BLOCKING, NULL, &oserr);//�ȴ�����  Timeoutһ����0
        if((Timeout != 0)&&(oserr == OS_ERR_TIMEOUT))
        {//���ճ�ʱ          
            wUart_AbortReceive(&p_Serial->Uart.huart); //ֹͣuart���չ���
            Revlen = 0;//���ճ�����0
        }
        else
        {
            if(p_Serial->length < RSize)
            {
                pData[p_Serial->length] = 0;//β����0
            }
            Revlen = p_Serial->length;
        }        
    }
    
    return Revlen;//���س���ֵ   
}


void wSerial_RxIdleIRQHandler(UART_HandleTypeDef *huart,uint32_t length)  
{//���ڽ�������ж�   //��Ҫ��HAL_UART_IRQHandlerHead��������
    OS_ERR oserr;
    wSerial_Def *p_Serial;

    for(uint8_t Id =0;Id < Serial_Num;Id++)
    {
        p_Serial = &Serial[Id];
        
		if(huart == &p_Serial->Uart.huart)
		{
            p_Serial->length = length;
			OSSemPost(&p_Serial->RxSemflg,OS_OPT_POST_ALL, &oserr); 
			break;
		}        
    }	
} 

void wSerial_TxIRQHandler(UART_HandleTypeDef *huart)
{//���ڷ�������ж�
 //��Ҫ��HAL_UART_TxCpltCallback��������
    OS_ERR oserr; 
    wSerial_Def *p_Serial;

    for(uint8_t Id =0;Id < Serial_Num;Id++)
    {
        p_Serial = &Serial[Id];
        
		if(huart == &p_Serial->Uart.huart)
		{
            OSSemPost(&p_Serial->TxSemflg,OS_OPT_POST_ALL, &oserr);
			break;
		}        
    }				
}

#endif
