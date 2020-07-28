/*
********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                       Keil Development Kits
*                                              on the
*                                      东莞嵌远电子技术有限公司
*
* Filename      : main.c
* Version       : V1.0
* Programmer(s) : Wu Yuanfu
* Email         : 240697738@qq.com （支付宝同号，欢迎打赏） 
* Time          : 2020/02/06 16:01:01
* 个人博客      ：https://blog.csdn.net/abc240697738
********************************************************************************************************
*/

#define WS_INC_wHARDWARE
#include "Cpucfg.h"
#include "wS.h" 
#include "os_cfg_app.h"
#include "wLed.h" 
#include "wSys.h"
#include "wSerial.h"

extern uint32_t __Vectors;

            #define wMain_STKSIZE       256
            static  OS_TCB	            Main_TaskTCB;		   			
__align(8)  static  CPU_STK	            Main_TaskStk[wMain_STKSIZE];	


uint8_t data[500];

static  void  MainTask(void *p_arg)
{
	OS_ERR  oserr;
    
    CPU_Init();                                                 /* Initialize the uC/CPU Services                       */
#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&oserr);                             /* Compute CPU capacity with no task running            */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    //初使化led灯 永久无限循环
    wLed_IdInit(0,GPIO_Pin_RUN,wLow,Led_Flash1,0);
    
    //初使化串口
    uint8_t sock = 0;
    wSerial_Init(sock,wSerial_Pin_1,wSerial_BaudRate,wSerial_StopBits,wSerial_Parity);
    
    //485方式相对于232方式仅仅增加了1个控制引脚，只需要初使这个控制引脚就可以，其它用法与232方式完全一致。
    wSerial_CSSInit(sock,wSerial_Pin_1CN,wLow);
    
	while (1)
    {  
        //阻塞接收数据
        int Rlen = wSerial_Receive(sock,data,500,0);
        
        if(Rlen > 0)
        {//接收到数据
            //把接收到的数据发出去
            wSerial_Transmit(sock,data,Rlen,2000);
        } 
    }	
}

/*
********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
********************************************************************************************************
*/

int main(void)
{
	OS_ERR  oserr;
    
    SCB->VTOR = (uint32_t)(&__Vectors);
    
    wSys_ClockConfig(CLOCK_8M,OS_CFG_TICK_RATE_HZ);       /* Configure the system clock */
    
#if (WS_CFG_PROBE_SCOPE_EN == WS_DEF_ENABLED)
    ProbeScope_Init(1000);
#endif

    OS_CPU_SysTickInit (wSys_GetClkFreq()/(CPU_INT32U)OS_CFG_TICK_RATE_HZ);  	
	
    OSInit(&oserr);                                       /* Init uC/OS-III.                                      */
    OSTaskCreate((OS_TCB       *)&Main_TaskTCB,           /* Create the start task                                */
                 (CPU_CHAR     *)"Main Task",
                 (OS_TASK_PTR   )MainTask,
                 (void         *)0,
                 (OS_PRIO       )2,                       //启动优先级
                 (CPU_STK      *)&Main_TaskStk[0u],
                 (CPU_STK_SIZE  )wMain_STKSIZE / 10u,
                 (CPU_STK_SIZE  )wMain_STKSIZE,
                 (OS_MSG_QTY    )0u,
                 (OS_TICK       )0u,
                 (void         *)0u,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&oserr);
    OSStart(&oserr);                                      /* Start multitasking (i.e. give control to uC/OS-III). */
}
/* End Main */
