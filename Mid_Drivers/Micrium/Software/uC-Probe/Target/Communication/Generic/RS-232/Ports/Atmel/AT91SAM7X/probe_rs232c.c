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
*                                    PORT FOR THE ATMEL AT91SAM7X
*
* Filename      : probe_rs232c.c
* Version       : V2.20
* Programmer(s) : BAN
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <probe_com.h>
#include  <probe_rs232.h>


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

                                                                /* ------------- Register Base Specifications ------------- */
#define  US0_BASE               ((CPU_INT32U)0xFFFC0000)
#define  US1_BASE               ((CPU_INT32U)0xFFFC4000)
#define  DBGU_BASE              ((CPU_INT32U)0xFFFFF200)
#define  AIC_BASE               ((CPU_INT32U)0xFFFFF000)
#define  PIOA_BASE              ((CPU_INT32U)0xFFFFF400)
#define  PMC_BASE               ((CPU_INT32U)0xFFFFFC00)

                                                                /* -------------------- Peripheral IDs -------------------- */
#define  AT91C_ID_SYS                   1
#define  AT91C_ID_US0                   6
#define  AT91C_ID_US1                   7

                                                                /* ----------------- US0 Register Defines ----------------- */
#define  US0_CR             (*(volatile CPU_INT32U *)(US0_BASE  + 0x0000))
#define  US0_MR             (*(volatile CPU_INT32U *)(US0_BASE  + 0x0004))
#define  US0_IER            (*(volatile CPU_INT32U *)(US0_BASE  + 0x0008))
#define  US0_IDR            (*(volatile CPU_INT32U *)(US0_BASE  + 0x000C))
#define  US0_CSR            (*(volatile CPU_INT32U *)(US0_BASE  + 0x0014))
#define  US0_RHR            (*(volatile CPU_INT32U *)(US0_BASE  + 0x0018))
#define  US0_THR            (*(volatile CPU_INT32U *)(US0_BASE  + 0x001C))
#define  US0_BRGR           (*(volatile CPU_INT32U *)(US0_BASE  + 0x0020))

                                                                /* ----------------- US1 Register Defines ----------------- */
#define  US1_CR             (*(volatile CPU_INT32U *)(US1_BASE  + 0x0000))
#define  US1_MR             (*(volatile CPU_INT32U *)(US1_BASE  + 0x0004))
#define  US1_IER            (*(volatile CPU_INT32U *)(US1_BASE  + 0x0008))
#define  US1_IDR            (*(volatile CPU_INT32U *)(US1_BASE  + 0x000C))
#define  US1_CSR            (*(volatile CPU_INT32U *)(US1_BASE  + 0x0014))
#define  US1_RHR            (*(volatile CPU_INT32U *)(US1_BASE  + 0x0018))
#define  US1_THR            (*(volatile CPU_INT32U *)(US1_BASE  + 0x001C))
#define  US1_BRGR           (*(volatile CPU_INT32U *)(US1_BASE  + 0x0020))

                                                                /* ----------------- DBGU Register Defines ---------------- */
#define  DBGU_CR            (*(volatile CPU_INT32U *)(DBGU_BASE + 0x0000))
#define  DBGU_MR            (*(volatile CPU_INT32U *)(DBGU_BASE + 0x0004))
#define  DBGU_IER           (*(volatile CPU_INT32U *)(DBGU_BASE + 0x0008))
#define  DBGU_IDR           (*(volatile CPU_INT32U *)(DBGU_BASE + 0x000C))
#define  DBGU_CSR           (*(volatile CPU_INT32U *)(DBGU_BASE + 0x0014))
#define  DBGU_RHR           (*(volatile CPU_INT32U *)(DBGU_BASE + 0x0018))
#define  DBGU_THR           (*(volatile CPU_INT32U *)(DBGU_BASE + 0x001C))
#define  DBGU_BRGR          (*(volatile CPU_INT32U *)(DBGU_BASE + 0x0020))

                                                                /* ----------------- AIC Register Defines ----------------- */
#define  AIC_SMR(n)         (*(volatile CPU_INT32U *)(AIC_BASE  + 0x0000 + 4 * (n)))
#define  AIC_SVR(n)         (*(volatile CPU_INT32U *)(AIC_BASE  + 0x0080 + 4 * (n)))
#define  AIC_IVR            (*(volatile CPU_INT32U *)(AIC_BASE  + 0x0100))
#define  AIC_IECR           (*(volatile CPU_INT32U *)(AIC_BASE  + 0x0120))
#define  AIC_ICCR           (*(volatile CPU_INT32U *)(AIC_BASE  + 0x0128))
#define  AIC_EOICR          (*(volatile CPU_INT32U *)(AIC_BASE  + 0x0130))

                                                                /* ----------------- PMC Register Defines ----------------- */
#define  PMC_PCER           (*(volatile CPU_INT32U *)(PMC_BASE  + 0x0010))

                                                                /* ---------------- PIOA Register Defines ----------------- */
#define  PIOA_PDR           (*(volatile CPU_INT32U *)(PIOA_BASE + 0x0004))
#define  PIOA_ASR           (*(volatile CPU_INT32U *)(PIOA_BASE + 0x0070))
#define  PIOA_BSR           (*(volatile CPU_INT32U *)(PIOA_BASE + 0x0074))

                                                                /* -------------- US_IER Register Bit Defines ------------- */
#define  AT91C_US_RXRDY                     DEF_BIT_00
#define  AT91C_US_TXRDY                     DEF_BIT_01
#define  AT91C_US_ENDRX                     DEF_BIT_03
#define  AT91C_US_ENDTX                     DEF_BIT_04
#define  AT91C_US_OVRE                      DEF_BIT_05
#define  AT91C_US_FRAME                     DEF_BIT_06
#define  AT91C_US_PARE                      DEF_BIT_07
#define  AT91C_US_TXEMPTY                   DEF_BIT_09
#define  AT91C_US_TXBUFE                    DEF_BIT_11
#define  AT91C_US_RXBUFF                    DEF_BIT_12
#define  AT91C_US_COMM_TX                   DEF_BIT_30
#define  AT91C_US_COMM_RX                   DEF_BIT_31

                                                                /* --------------- US_CR Register Bit Defines ------------- */
#define  AT91C_US_RSTRX                     DEF_BIT_02
#define  AT91C_US_RSTTX                     DEF_BIT_03
#define  AT91C_US_RXEN                      DEF_BIT_04
#define  AT91C_US_RXDIS                     DEF_BIT_05
#define  AT91C_US_TXEN                      DEF_BIT_06
#define  AT91C_US_TXDIS                     DEF_BIT_07
#define  AT91C_US_RSTSTA                    DEF_BIT_08

                                                                /* -------------- US_MR Register Bit Defines -------------- */
#define  AT91C_US_USMODE_NORMAL             (0x00 <<  0)
#define  AT91C_US_CLKS_CLOCK                (0x00 <<  4)
#define  AT91C_US_CHRL_8_BITS               (0x03 <<  6)
#define  AT91C_US_PAR_NONE                  (0x04 <<  9)
#define  AT91C_US_NBSTOP_1_BIT              (0x00 << 12)

                                                                /* ------------- AIC_SMR Register Bit Defines ------------- */
#define  AT91C_AIC_SRCTYPE_EXT_HIGH_LEVEL   (0x02 <<  5)
#define  AT91C_AIC_PRIOR_LOWEST             (0x00 <<  0)


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                    EXTERNAL FUNCTION PROTOTYPES
*
* Note(s)     : (1) 'BSP_CPU_ClkFreq()' should return the Master Clock (MCK) frequency in Hz.
*********************************************************************************************************
*/

extern  CPU_INT32U  BSP_CPU_ClkFreq    (void);


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef    PROBE_RS232_CFG_COMM_SEL

  #error  "PROBE_RS232_CFG_COMM_SEL          not #define'd in 'probe_com_cfg.h'"
  #error  "                                  [MUST be PROBE_RS232_UART_0   ]   "
  #error  "                                  [     || PROBE_RS232_UART_1   ]   "
  #error  "                                  [     || PROBE_RS232_UART_DBG ]   "

#elif     (PROBE_RS232_CFG_COMM_SEL != PROBE_RS232_UART_0  ) && \
          (PROBE_RS232_CFG_COMM_SEL != PROBE_RS232_UART_1  ) && \
          (PROBE_RS232_CFG_COMM_SEL != PROBE_RS232_UART_DBG)

  #error  "PROBE_RS232_CFG_COMM_SEL    illegally #define'd in 'probe_com_cfg.h'"
  #error  "                                  [MUST be PROBE_RS232_UART_0   ]   "
  #error  "                                  [     || PROBE_RS232_UART_1   ]   "
  #error  "                                  [     || PROBE_RS232_UART_DBG ]   "
#endif


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
* Note(s)     : (1) The DBGU shares the system interrupt with several other peripherals (including the
*                   Periodic Interval Timer (PIT)).  Consequently, the interrupt for the DBGU is not
*                   initialized here; rather, it is assumed to be initialized in user code.  Note also
*                   that the interrupt is not cleared for the DBGU in OSView_RxTxISRHandler().  This should
*                   be done in user code as well.
*********************************************************************************************************
*/

void  ProbeRS232_InitTarget (CPU_INT32U baud_rate)
{
    CPU_INT32U     pclk_freq;


    pclk_freq             = BSP_CPU_ClkFreq();                  /* Calculate PCLK frequency                                 */

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_0)
                                                                /* ------------------ CONFIGURE US0 I/Os ------------------ */
                                                                /* Set GPIOA pins 0 & 1 as US0 pins                         */
    PIOA_PDR              = DEF_BIT_00 | DEF_BIT_01;
    PIOA_ASR              = DEF_BIT_00 | DEF_BIT_01;

                                                                /* ---------------------- SETUP US0 ----------------------- */
    US0_IDR               = AT91C_US_RXRDY | AT91C_US_TXRDY;    /* Disable Rx & Tx interrupts                               */
    US0_CR                = AT91C_US_RXEN  | AT91C_US_TXEN;     /* Enable the receiver & transmitter                        */

    US0_MR                = AT91C_US_USMODE_NORMAL              /* RS232C mode selected                                     */
                          | AT91C_US_CLKS_CLOCK                 /* USART input CLK is MCK                                   */
                          | AT91C_US_CHRL_8_BITS                /* 8 bit data to be sent                                    */
                          | AT91C_US_PAR_NONE                   /* No parity bit selected                                   */
                          | AT91C_US_NBSTOP_1_BIT;              /* 1 stop bit selected                                      */

                                                                /* Set the USART baud rate                                  */
    US0_BRGR              = (CPU_INT16U)((pclk_freq) / baud_rate / 16);

                                                                /* ---------------- INITIALIZE AIC FOR US0 ---------------- */
    AIC_SVR(AT91C_ID_US0) = (CPU_INT32U)ProbeRS232_RxTxISRHandler;
    AIC_SMR(AT91C_ID_US0) = AT91C_AIC_SRCTYPE_EXT_HIGH_LEVEL | AT91C_AIC_PRIOR_LOWEST;
    AIC_ICCR              = (1 << AT91C_ID_US0);
    AIC_IECR              = (1 << AT91C_ID_US0);

    PMC_PCER              = (1 << AT91C_ID_US0);              /* Enable the US0 peripheral clock                            */
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_1)
                                                                /* ------------------ CONFIGURE US1 I/Os ------------------ */
                                                                /* Set GPIOA pins 5 & 6 as US1 pins                         */
    PIOA_PDR              = DEF_BIT_05 | DEF_BIT_06;
    PIOA_ASR              = DEF_BIT_05 | DEF_BIT_06;

                                                                /* ---------------------- SETUP US1 ----------------------- */
    US1_IDR               = AT91C_US_RXRDY | AT91C_US_TXRDY;    /* Disable Rx & Tx interrupts                               */
    US1_CR                = AT91C_US_RXEN  | AT91C_US_TXEN;     /* Enable the receiver & transmitter                        */

    US1_MR                = AT91C_US_USMODE_NORMAL              /* RS232C mode selected                                     */
                          | AT91C_US_CLKS_CLOCK                 /* USART input CLK is MCK                                   */
                          | AT91C_US_CHRL_8_BITS                /* 8 bit data to be sent                                    */
                          | AT91C_US_PAR_NONE                   /* No parity bit selected                                   */
                          | AT91C_US_NBSTOP_1_BIT;              /* 1 stop bit selected                                      */

                                                                /* Set the USART baud rate                                  */
    US1_BRGR              = (CPU_INT16U)((pclk_freq) / baud_rate / 16);

                                                                /* ---------------- INITIALIZE AIC FOR US1 ---------------- */
    AIC_SVR(AT91C_ID_US1) = (CPU_INT32U)ProbeRS232_RxTxISRHandler;
    AIC_SMR(AT91C_ID_US1) = AT91C_AIC_SRCTYPE_EXT_HIGH_LEVEL | AT91C_AIC_PRIOR_LOWEST;
    AIC_ICCR              = (1 << AT91C_ID_US1);
    AIC_IECR              = (1 << AT91C_ID_US1);

    PMC_PCER              = (1 << AT91C_ID_US1);              /* Enable the US1 peripheral clock                            */
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_DBG)
                                                                /* ----------------- CONFIGURE DBGU I/Os ------------------ */
                                                                /* Set GPIOA pins 27 & 28 as DBGU pins                      */
    PIOA_PDR  = DEF_BIT_27 | DEF_BIT_28;
    PIOA_ASR  = DEF_BIT_27 | DEF_BIT_28;

                                                                /* --------------------- SETUP DBGU ----------------------- */
    DBGU_IDR  = AT91C_US_RXRDY | AT91C_US_TXRDY;                /* Disable Rx & Tx interrupts                               */
    DBGU_CR   = AT91C_US_RXEN  | AT91C_US_TXEN;                 /* Enable the receiver & transmitter                        */

    DBGU_MR   = AT91C_US_USMODE_NORMAL                          /* RS232C mode selected                                     */
              | AT91C_US_CLKS_CLOCK                             /* USART input CLK is MCK                                   */
              | AT91C_US_CHRL_8_BITS                            /* 8 bit data to be sent                                    */
              | AT91C_US_PAR_NONE                               /* No parity bit selected                                   */
              | AT91C_US_NBSTOP_1_BIT;                          /* 1 stop bit selected                                      */

                                                                /* Set the USART baud rate                                  */
    DBGU_BRGR = (CPU_INT16U)((pclk_freq) / baud_rate / 16);

                                                                /* --------------- INITIALIZE AIC FOR DBGU ---------------- */
                                                                /* See Note (1)                                             */
    PMC_PCER  = (1 << AT91C_ID_SYS);                            /* Enable the DBGU peripheral clock                         */
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
* Note(s)     : (1) If DBGU is used, then this function is expected to be called by an external
*                   function which handles interrupts on the system (SYS) vector.  It is expected as well
*                   that that function will clear the SYS interrupt.
*
*               (2) The AIC End Of Interrupt Command Register (AIC_EOICR) will need to be written by the
*                   generic interrupt handler which vectored to this specific IRQ handler after this
*                   function returns.
*********************************************************************************************************
*/

void  ProbeRS232_RxTxISRHandler (void)
{
    CPU_INT08U  rx_data;


#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_0)
    AIC_IVR   = 0;                                              /* Debug variant of IVR (protect mode is used)              */
                                                                /* If we received a byte                                    */
    if ((US0_CSR & AT91C_US_RXRDY) == AT91C_US_RXRDY) {
        rx_data = (CPU_INT08U)(US0_RHR & 0x00FF);               /* Remove the data from the holding register                */
        ProbeRS232_RxHandler(rx_data);                          /* Call the generic Rx handler                              */
    }

                                                                /* If we completed transmitting a byte                      */
    if ((US0_CSR & AT91C_US_TXRDY) == AT91C_US_TXRDY) {
        ProbeRS232_TxHandler();                                 /* Call the generic Tx handler                              */
    }

    if ((US0_CSR  & AT91C_US_OVRE) == AT91C_US_OVRE) {
        US0_CR = AT91C_US_RSTSTA;                               /* If an overrun occurs, reset the OR flag                  */
    }

    AIC_ICCR  = AT91C_ID_US0;                                   /* Clear  US0 interrupt                                     */
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_1)
    AIC_IVR   = 0;                                              /* Debug variant of IVR (protect mode is used)              */
                                                                /* If we received a byte                                    */
    if ((US1_CSR & AT91C_US_RXRDY) == AT91C_US_RXRDY) {
        rx_data = (CPU_INT08U)(US1_RHR & 0x00FF);               /* Remove the data from the holding register                */
        ProbeRS232_RxHandler(rx_data);                          /* Call the generic Rx handler                              */
    }

                                                                /* If we completed transmitting a byte                      */
    if ((US1_CSR & AT91C_US_TXRDY) == AT91C_US_TXRDY) {
        ProbeRS232_TxHandler();                                 /* Call the generic Tx handler                              */
    }

    if ((US0_CSR  & AT91C_US_OVRE) == AT91C_US_OVRE) {
        US1_CR = AT91C_US_RSTSTA;                               /* If an overrun occurs, reset the OR flag                  */
    }

    AIC_ICCR  = AT91C_ID_US1;                                   /* Clear  US0 interrupt                                     */
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_DBG)
                                                                /* If we received a byte                                    */
    if ((DBGU_CSR & AT91C_US_RXRDY) == AT91C_US_RXRDY) {
        rx_data = (CPU_INT08U)(DBGU_RHR & 0x00FF);              /* Remove the data from the holding register                */
        ProbeRS232_RxHandler(rx_data);                          /* Call the generic Rx handler                              */
    }

                                                                /* If we completed transmitting a byte                      */
    if ((DBGU_CSR & AT91C_US_TXRDY) == AT91C_US_TXRDY) {
        ProbeRS232_TxHandler();                                 /* Call the generic Tx handler                              */
    }

    if ((DBGU_CSR  & AT91C_US_OVRE) == AT91C_US_OVRE) {
        DBGU_CR = AT91C_US_RSTSTA;                              /* If an overrun occurs, reset the OR flag                  */
    }
#endif
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
* Note(s)     : (1) This function is empty because receive interrupts are handled by the combined receive/
*                   transmit interrupt handler, 'ProbeRS232_RxTxISRHandler()'.
*********************************************************************************************************
*/

void  ProbeRS232_RxISRHandler (void)
{
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
    US0_IDR  = AT91C_US_RXRDY;
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_1)
    US1_IDR  = AT91C_US_RXRDY;
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_DBG)
    DBGU_IDR = AT91C_US_RXRDY;
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
    US0_IER  = AT91C_US_RXRDY;
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_1)
    US1_IER  = AT91C_US_RXRDY;
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_DBG)
    DBGU_IER = AT91C_US_RXRDY;
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
* Note(s)     : (1) This function is empty because transmit interrupts are handled by the combined receive/
*                   transmit interrupt handler, 'ProbeRS232_RxTxISRHandler()'.
*********************************************************************************************************
*/

void  ProbeRS232_TxISRHandler (void)
{
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

void  ProbeRS232_Tx1 (CPU_INT08U c)
{
#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_0)
    US0_THR  = c;
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_1)
    US1_THR  = c;
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_DBG)
    DBGU_THR = c;
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
    US0_IDR  = AT91C_US_TXRDY;
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_1)
    US1_IDR  = AT91C_US_TXRDY;
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_DBG)
    DBGU_IDR = AT91C_US_TXRDY;
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
    US0_IER  = AT91C_US_TXRDY;
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_1)
    US1_IER  = AT91C_US_TXRDY;
#endif

#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_DBG)
    DBGU_IER = AT91C_US_TXRDY;
#endif
}


/*
*********************************************************************************************************
*                                              ENABLE END
*
* Note(s) : See 'ENABLE  Note #1'.
*********************************************************************************************************
*/

#endif
