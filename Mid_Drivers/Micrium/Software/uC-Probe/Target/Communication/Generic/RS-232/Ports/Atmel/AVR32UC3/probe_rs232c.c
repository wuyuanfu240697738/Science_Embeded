/*
*********************************************************************************************************
*                                       uC/Probe Communication
*
*                         (c) Copyright 2007-2008; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                        COMMUNICATION: RS-232
*
*                                    PORT FOR THE ATMEL AVR32 UC3
*
* Filename      : probe_rs232c.c
* Version       : V2.20
* Programmer(s) : FGK
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include <includes.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       ProbeRS232_InitTarget()
*
* Description : Initialize the UART for Probe communication.
*
* Argument(s) : baud_rate   Intended baud rate of the RS-232.
*
* Return(s)   : none.
*
* Caller(s)   : ProbeRS232_Init().
*
* Note(s)     : (1) Though the baud rate used may vary from application to application or target to
*                   target, other communication settings are constamt.  The hardware must always be
*                   configured for the following :
*
*                   (a) No parity
*                   (b) One stop bit
*                   (c) Eight data bits.
*
*               (2) Neither receive nor transmit interrupts should be enabled by this function.
*********************************************************************************************************
*/

void  ProbeRS232_InitTarget (CPU_INT32U baud_rate)
{
#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_0)
    BSP_USART_Init(0, baud_rate);
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_1)
    BSP_USART_Init(1, baud_rate);
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_2)
    BSP_USART_Init(2, baud_rate);
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_3)
    BSP_USART_Init(3, baud_rate);
#endif

}


/*
*********************************************************************************************************
*                                     ProbeRS232_RxTxISRHandler()
*
* Description : Handle receive and transmit interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : (1) This function is empty because receive and transmit interrupts are handled in the
*                   separate interrupt handlers, ProbeRS232_RxISRHandler() and ProbeRS232_TxISRHandler().
*********************************************************************************************************
*/

void  ProbeRS232_RxTxISRHandler (void)
{
}


/*
*********************************************************************************************************
*                                      ProbeRS232_RxISRHandler()
*
* Description : Handle receive interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  ProbeRS232_RxISRHandler (void)
{
    CPU_INT08U  c;


#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_0)
    c = BSP_USART_ByteRd(0);
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_1)
    c = BSP_USART_ByteRd(1);
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_2)
    c = BSP_USART_ByteRd(2);
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_3)
    c = BSP_USART_ByteRd(3);
#endif


#if (PROBE_COM_CFG_RS232_EN == DEF_ENABLED)
    ProbeRS232_RxHandler(c);
#else
    (void)c;
#endif
}


/*
*********************************************************************************************************
*                                        ProbeRS232_RxIntDis()
*
* Description : Disable receive interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) The application should call this function to stop communication.
*********************************************************************************************************
*/

void  ProbeRS232_RxIntDis (void)
{
#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_0)
    BSP_USART_IntDis(0, AVR32_USART_RXRDY_MASK);
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_1)
    BSP_USART_IntDis(1, AVR32_USART_RXRDY_MASK);
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_2)
    BSP_USART_IntDis(2, AVR32_USART_RXRDY_MASK);
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_3)
    BSP_USART_IntDis(3, AVR32_USART_RXRDY_MASK);
#endif
}


/*
*********************************************************************************************************
*                                        ProbeRS232_RxIntEn()
*
* Description : Enable receive interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) The application should call this function to start communication.
*********************************************************************************************************
*/

void  ProbeRS232_RxIntEn (void)
{
#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_0)
    BSP_USART_IntEn(0, AVR32_USART_RXRDY_MASK);
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_1)
    BSP_USART_IntEn(1, AVR32_USART_RXRDY_MASK);
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_2)
    BSP_USART_IntEn(2, AVR32_USART_RXRDY_MASK);
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_3)
    BSP_USART_IntEn(3, AVR32_USART_RXRDY_MASK);
#endif
}


/*
*********************************************************************************************************
*                                      ProbeRS232_TxISRHandler()
*
* Description : Handle transmit interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  ProbeRS232_TxISRHandler (void)
{
#if (PROBE_COM_CFG_RS232_EN == DEF_ENABLED)
    ProbeRS232_TxHandler();
#endif
}


/*
*********************************************************************************************************
*                                          ProbeRS232_Tx1()
*
* Description : Transmit one byte.
*
* Argument(s) : c           The byte to transmit.
*
* Return(s)   : none.
*
* Caller(s)   : ProbeRS232_TxHandler().
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  ProbeRS232_Tx1 (INT8U c)
{
#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_0)
    BSP_USART_ByteWr(0, c);
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_1)
    BSP_USART_ByteWr(1, c);
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_2)
    BSP_USART_ByteWr(2, c);
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_3)
    BSP_USART_ByteWr(3, c);
#endif
}


/*
*********************************************************************************************************
*                                        ProbeRS232_TxIntDis()
*
* Description : Disable transmit interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : ProbeRS232_TxHandler().
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  ProbeRS232_TxIntDis (void)
{
#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_0)
    BSP_USART_IntDis(0, AVR32_USART_TXRDY_MASK);
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_1)
    BSP_USART_IntDis(1, AVR32_USART_TXRDY_MASK);
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_2)
    BSP_USART_IntDis(2, AVR32_USART_TXRDY_MASK);
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_3)
    BSP_USART_IntDis(3, AVR32_USART_TXRDY_MASK);
#endif
}


/*
*********************************************************************************************************
*                                        ProbeRS232_TxIntEn()
*
* Description : Enable transmit interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : ProbeRS232_TxStart().
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  ProbeRS232_TxIntEn (void)
{
#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_0)
    BSP_USART_IntEn(0, AVR32_USART_TXRDY_MASK);
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_1)
    BSP_USART_IntEn(1, AVR32_USART_TXRDY_MASK);
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_2)
    BSP_USART_IntEn(2, AVR32_USART_TXRDY_MASK);
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_3)
    BSP_USART_IntEn(3, AVR32_USART_TXRDY_MASK);
#endif
}
