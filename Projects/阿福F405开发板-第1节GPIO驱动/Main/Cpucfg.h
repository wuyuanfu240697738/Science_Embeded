

#ifdef __cplusplus
 extern "C" {
#endif

#define  WS_DEF_DISABLED                        0u
#define  WS_DEF_ENABLED                         1u

#define  WS_CFG_DEBUG_EN                        WS_DEF_DISABLED          /* Enable (DEF_ENABLED)   */
#define  WS_CFG_MODBUS_EN						WS_DEF_DISABLED
#define  WS_CFG_ETH_EN                          WS_DEF_DISABLED         /* Enable (DEF_ENABLED)   */
#define  WS_CFG_TIM_EN                          WS_DEF_DISABLED         /* Enable (DEF_ENABLED)   */
#define  WS_CFG_ADC_EN                          WS_DEF_DISABLED         /* Enable (DEF_ENABLED)   */
#define  WS_CFG_SPI_EN                          WS_DEF_DISABLED          /* Enable (DEF_ENABLED)   */
#define  WS_CFG_UART_EN                         WS_DEF_DISABLED          /* Enable (DEF_ENABLED)   */
#define  WS_CFG_I2C_EN                          WS_DEF_DISABLED          /* Enable (DEF_ENABLED)   */
#define  WS_CFG_SHELL_EN                        WS_DEF_DISABLED          /* Enable (DEF_ENABLED)   */
#define  WS_CFG_CRC_EN                          WS_DEF_DISABLED          /* Enable (DEF_ENABLED)   */
#define  WS_CFG_USB_EN                          WS_DEF_DISABLED          /* Enable (DEF_ENABLED)   */

/*
********************************************************************************************************
*                                                 wShell.c
********************************************************************************************************
*/
#ifdef WS_INC_wSHELL
#define User_Num                10      //用户数量
#define Pwd_MAXLEN              12      //用户密码最大长度
#define Name_MAXLEN             12      //用户名最大长度
#endif

/*
********************************************************************************************************
*                                                 wLed.c
********************************************************************************************************
*/
#ifdef WS_INC_wLED
#define Led_Num                 1       //led 指示灯数量
#endif

/*
********************************************************************************************************
*                                                 wRealy.c
********************************************************************************************************
*/
#define Relay_Num               6       //Realy 继电器数量

/*
********************************************************************************************************
*                                                 wInput.c
********************************************************************************************************
*/
#define Input_Num               8       //Input 继电器数量


/*
********************************************************************************************************
*                                                 w24cxx.c
********************************************************************************************************
*/
#ifdef WS_INC_wAT24CXX
#define At24Cxx_Num             1       //At24cxx 数量
#endif

/*
********************************************************************************************************
*                                                 wSerial.c
********************************************************************************************************
*/
#ifdef WS_INC_wSERIAL
#define Serial_Num              3       //Serial 数量
#endif


/*
********************************************************************************************************
*                                                 w5500.c
********************************************************************************************************
*/
#ifdef WS_INC_w5500
#define W5500_Num              1        //w5500 数量
#endif



/*
********************************************************************************************************
*                                                 硬件相关
********************************************************************************************************
*/
#ifdef WS_INC_wHARDWARE

	#define 	GPIO_Pin_X00  	   	wPIN_B1
	#define 	GPIO_Pin_X01  	    wPIN_A7   	
	#define 	GPIO_Pin_X02  	    wPIN_A6
	#define 	GPIO_Pin_X03  	    wPIN_A5
	#define 	GPIO_Pin_X04  	    wPIN_B6        
	#define 	GPIO_Pin_X05  	    wPIN_B7
	#define 	GPIO_Pin_X06  	    wPIN_A1 
	#define 	GPIO_Pin_X07  	    wPIN_A0  
     
	#define 	GPIO_Pin_Y01  	    wPIN_B13  
	#define 	GPIO_Pin_Y02  	    wPIN_C6 
	#define 	GPIO_Pin_Y03  	    wPIN_C7  
	#define 	GPIO_Pin_Y04  	    wPIN_A8 
	
	#define 	GPIO_Pin_Y10  	    wPIN_C13     
	#define 	GPIO_Pin_Y11  	    wPIN_C0    
	#define 	GPIO_Pin_Y12  	    wPIN_C8   
	#define 	GPIO_Pin_Y13  	    wPIN_C4 
	#define 	GPIO_Pin_Y14  	    wPIN_B14   
	#define 	GPIO_Pin_Y15  	    wPIN_B12 
    
    #define     GPIO_Pin_RF         wPIN_B0     
	#define 	GPIO_Pin_RUN  	    wPIN_A4   
	
	#define 	GPIO_Pin_USBPM  	wPIN_C5

	#define     T1					wPIN_C9
	#define     T2					wPIN_C1
    
	#define     wSerial_Pin_2	    wPIN_U2_A2A3     //TTL
    #define     wSerial_Pin_0       wPIN_U3_C10C11   //232
    #define     wSerial_Pin_1       wPIN_U1_A9A10    //485
	#define 	wSerial_Pin_1CN     wPIN_B15         //485控制引脚

    #define     wSerial_BaudRate    115200         
    #define     wSerial_WordLength  0x08    
    #define     wSerial_StopBits    0x01
    #define     wSerial_Parity      UART_PARITY_NONE
    #define     wSerial_Mode        UART_MODE_TX_RX

    #define     w24Cxx_Pin          wPIN_I2C2_B10B11  
    #define     w24Cxx_Speed        30000 
#endif

#ifdef __cplusplus
}
#endif
