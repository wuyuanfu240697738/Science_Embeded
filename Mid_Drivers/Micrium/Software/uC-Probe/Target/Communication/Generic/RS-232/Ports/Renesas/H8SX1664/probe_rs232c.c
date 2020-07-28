/*
*********************************************************************************************************
*                                      uC/Probe Communication
*
*                           (c) Copyright 2007; Micrium, Inc.; Weston, FL
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
*                                              uC/Probe
*
*                                      Communication: RS-232
*                                    H8SX/1664  Specific code
*
*
* Filename      : probe_rs232c.c
* Version       : V1.00
* Programmer(s) : Hong Soong
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  "includes.h"


/*
*********************************************************************************************************
*                                               ENABLE
*
* Note(s) : (1) See 'probe_rs232.h  ENABLE'.
*********************************************************************************************************
*/

#if (PROBE_COM_CFG_RS232_EN == DEF_ENABLED)                     /* See Note #1.                                         */


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#if      PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_0
#define  PROBE_RS232                 SCI0

#elif    PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_1
#define  PROBE_RS232                 SCI1

#elif    PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_2
#define  PROBE_RS232                 SCI2

#elif    PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_4
#define  PROBE_RS232                 SCI4

#endif


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

void  ProbeRS232_Config     (void);
void  ProbeRS232_EnSCIF     (void);

/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                         GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

extern void ProbeRS232_EriISRHandler (void);
extern void ProbeRS232_RxISRHandler  (void);
extern void ProbeRS232_TxISRHandler  (void);

/*
*********************************************************************************************************
*                                      ProbeRS232_InitTarget()
*
* Description : Initialize the UART for uC/Probe communication.
*
* Argument(s) : baud_rate   Intended baud rate of the RS-232.
*
* Return(s)   : none.
*********************************************************************************************************
*/

void  ProbeRS232_InitTarget (CPU_INT32U baud_rate)
{
    CPU_INT08U baud_clk;
    CPU_INT16U brr;


    ProbeRS232_EnSCIF();

    PROBE_RS232.SCR.BIT.TIE   =  0;                                     /* Disable transmit interrupts                      */
    PROBE_RS232.SCR.BIT.TE    =  0;                                     /* Disable transmitting                             */
    PROBE_RS232.SCR.BIT.RIE   =  0;                                     /* Disable receive interrupts                       */
    PROBE_RS232.SCR.BIT.RE    =  0;                                     /* Disable receiving                                */
    PROBE_RS232.TDR = 0;                                                                    /* Clear error flags                                */
    PROBE_RS232.SSR.BIT.FER   =  0;
    PROBE_RS232.SSR.BIT.PER   =  0;
    PROBE_RS232.SSR.BIT.ORER  =  0;
    PROBE_RS232.SCR.BIT.CKE   =  0;                                     /* Use internal clock, set SCK pin as input pin     */
    PROBE_RS232.SMR.BIT.CA    =  0;                                     /* Set for asynchronous mode                        */
    PROBE_RS232.SMR.BIT.CHR   =  0;                                     /* 8-bit data                                       */
    PROBE_RS232.SMR.BIT._PE   =  0;                                     /* Parity mode disabled                             */
    PROBE_RS232.SMR.BIT.OE    =  0;                                     /* No parity                                        */
    PROBE_RS232.SMR.BIT.STOP  =  0;                                     /* 1 stop bit                                       */
    baud_clk                  =  0;                                     /* Algorithm for finding SCBRR value                */

    do {                                                                /* N = BRR (0-255), B = bit rate, n = baud clock    */
        brr = SP_Brr(baud_rate, baud_clk);                              /* N = Pclk / (64 * 2^(2 * n - 1) * B) - 1          */

        if (brr > 255) {
             baud_clk++;
        }
    } while (brr > 255);

    PROBE_RS232.SMR.BIT.CKS   =  baud_clk;
    PROBE_RS232.BRR           =  brr;
    ProbeRS232_Config();
    BSP_Dly(1);
    PROBE_RS232.SCR.BIT.TE    =  1;                                     /* Enable transmitting                              */
    PROBE_RS232.SCR.BIT.TIE   =  0;                                     /* Enable Transmit Interrupts                       */
    PROBE_RS232.SCR.BIT.RE    =  1;                                     /* Enable receiving                                 */
    PROBE_RS232.SCR.BIT.RIE   =  0;                                     /* Enable Receive Interrupts                        */
}

void  ProbeRS232_EnSCIF (void)
{
#if   PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_0
    MSTP.CRB.BIT._SCI0    =  0;                                         /* Enable SCIF0 module                              */

#elif PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_1
    MSTP.CRB.BIT._SCI1    =  0;                                         /* Enable SCIF1 module                              */

#elif PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_4
    MSTP.CRB.BIT._SCI4    =  0;                                         /* Enable SCIF4 module                              */

#endif
}

void  ProbeRS232_Config (void)
{
#if   PROBE_RS232_CFG_COMM_SEL  ==  PROBE_RS232_UART_0
    P2.DDR              = 0x04;                                         /* Set the data direction register                  */
    P2.ICR.BYTE         = 0x02;                                         /* Set the input buffer control register            */
    INTC.IPRK.BIT._SCI0 =   11;                                         /* Set the interrupt priority                       */

#elif PROBE_RS232_CFG_COMM_SEL  ==  PROBE_RS232_UART_1
    P2.DDR              = 0x40;                                         /* Set the data direction register                  */
    P2.ICR.BYTE         = 0x20;                                         /* Set the input buffer control register            */
    INTC.IPRK.BIT._SCI1 =   11;                                         /* Set the interrupt priority                       */

#elif PROBE_RS232_CFG_COMM_SEL  ==  PROBE_RS232_UART_4
    P6.DDR              = 0x01;                                         /* Set the data direction register                  */
    P6.ICR.BYTE         = 0x02;                                         /* Set the input buffer control register            */
    INTC.IPRL.BIT._SCI4 =   11;                                         /* Set the interrupt priority                       */

#endif
}

/*
*********************************************************************************************************
*                                     ProbeRS232_RxTxISRHandler()
*
* Description : Handle Rx and Tx interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : (1) This function may be empty if Rx and Tx interrupts are handled in the separate
*                   interrupt handlers, ProbeRS232_RxISRHandler() and ProbeRS232_TxISRHandler().
*********************************************************************************************************
*/

void  ProbeRS232_RxTxISRHandler (void)
{

}


/*
*********************************************************************************************************
*                                    ProbeRS232_RxISRHandler()
*
* Description : Handle Rx interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : (1) This function may empty if Rx interrupts are handled by the combined Rx/Tx interrupt
*                   handler, ProbeRS232_RxTxISRHandler()
*********************************************************************************************************
*/

#if   PROBE_RS232_CFG_COMM_SEL  ==  PROBE_RS232_UART_0
__interrupt(vect=145)

#elif PROBE_RS232_CFG_COMM_SEL  ==  PROBE_RS232_UART_1
__interrupt(vect=149)

#elif PROBE_RS232_CFG_COMM_SEL  ==  PROBE_RS232_UART_4
__interrupt(vect=161)

#endif
void  ProbeRS232_RxISRHandler (void)
{
    CPU_CHAR rx_data;


    while (PROBE_RS232.SSR.BIT.RDRF == 0) ;                             /* Wait until a read is requested                   */

    rx_data  = PROBE_RS232.RDR;
    PROBE_RS232.SSR.BIT.RDRF = 0;                                       /* Read then clear the read flag                    */
    PROBE_RS232.SSR.BIT.RDRF;

    ProbeRS232_RxHandler(rx_data);
}


/*
*********************************************************************************************************
*                                      ProbeRS232_RxIntDis()
*
* Description : Disable Rx interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

void  ProbeRS232_RxIntDis (void)
{
    PROBE_RS232.SCR.BIT.RIE = 0;                                        /* Enable receiving                                 */
}


/*
*********************************************************************************************************
*                                      ProbeRS232_RxIntEn()
*
* Description : Enable Rx interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

void  ProbeRS232_RxIntEn (void)
{
    PROBE_RS232.SCR.BIT.RIE = 1;                                        /* Enable Transmit Interrupts                       */
}


/*
*********************************************************************************************************
*                                    ProbeRS232_TxISRHandler()
*
* Description : Handle Tx interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : (1) This function may empty if Tx interrupts are handled by the combined Rx/Tx interrupt
*                   handler, ProbeRS232_RxTxISRHandler()
*********************************************************************************************************
*/

#if   PROBE_RS232_CFG_COMM_SEL  ==  PROBE_RS232_UART_0
__interrupt(vect=146)

#elif PROBE_RS232_CFG_COMM_SEL  ==  PROBE_RS232_UART_1
__interrupt(vect=150)

#elif PROBE_RS232_CFG_COMM_SEL  ==  PROBE_RS232_UART_4
__interrupt(vect=162)

#endif
void  ProbeRS232_TxISRHandler (void)
{
    ProbeRS232_TxHandler();
}


/*
*********************************************************************************************************
*                                      ProbeRS232_Tx1()
*
* Description : Transmit one byte.
*
* Argument(s) : c           The byte to transmit.
*
* Return(s)   : none.
*********************************************************************************************************
*/

void  ProbeRS232_Tx1 (CPU_INT08U c)
{
    while (PROBE_RS232.SSR.BIT.TDRE == 0) ;

    PROBE_RS232.TDR          = c;                                       /* Place character to be transmitted into register  */
    PROBE_RS232.SSR.BIT.TDRE = 0;                                       /* Clear register empty flag                        */
    PROBE_RS232.SSR.BIT.TDRE;
    PROBE_RS232.SSR.BIT.TEND = 0;                                       /* Clear transmission end flag                      */
}

/*
*********************************************************************************************************
*                                      ProbeRS232_TxIntDis()
*
* Description : Disable Tx interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

void  ProbeRS232_TxIntDis (void)
{
    PROBE_RS232.SCR.BIT.TIE = 0;                                        /* Disable Transmit Interrupts                      */
}


/*
*********************************************************************************************************
*                                      ProbeRS232_TxIntEn()
*
* Description : Enable Tx interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

void  ProbeRS232_TxIntEn (void)
{
    PROBE_RS232.SCR.BIT.TIE = 1;                                        /* Enable Transmit Interrupts                       */
}

#if   PROBE_RS232_CFG_COMM_SEL  ==  PROBE_RS232_UART_0
__interrupt(vect=144)

#elif PROBE_RS232_CFG_COMM_SEL  ==  PROBE_RS232_UART_1
__interrupt(vect=148)

#elif PROBE_RS232_CFG_COMM_SEL  ==  PROBE_RS232_UART_4
__interrupt(vect=160)

#endif
void ProbeRS232_EriISRHandler (void)
{
    if (PROBE_RS232.SSR.BIT.FER  == 1) {
        PROBE_RS232.SSR.BIT.FER   = 0;
        PROBE_RS232.SSR.BIT.FER;
    }
    if (PROBE_RS232.SSR.BIT.ORER == 1) {
        PROBE_RS232.SSR.BIT.ORER  = 0;
        PROBE_RS232.SSR.BIT.ORER;
    }
    if (PROBE_RS232.SSR.BIT.PER  == 1) {
        PROBE_RS232.SSR.BIT.PER   = 0;
        PROBE_RS232.SSR.BIT.PER;
    }
}
#endif
