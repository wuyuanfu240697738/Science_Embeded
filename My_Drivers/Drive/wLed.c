#define WS_INC_wLED
#include "Cpucfg.h"

#include "wLed.h" 
#if (WS_CFG_SHELL_EN == WS_DEF_ENABLED) 
#include "wShell.h" 
#endif

#include "wStr.h"

static wLedDef led[Led_Num];

static void wLed_TmrOff(void *p_tmr, void *p_arg);
static void wLed_TmrOn(void *p_tmr, void *p_arg);

#if (WS_CFG_SHELL_EN == WS_DEF_ENABLED) 
static wShell_Def ShellCmd_led;
static void wCmd_led(uint8_t Id,uint8_t argc,char *argv[])
{
    //led 1 on/off/flast/flash1-6
   
    if(argc == 3)
    {    
        //此次可以加入权限判断
        if(p_User != 0)
        {//只有有效的用户才有此命令权限
            unsigned int n = wStr_Atoi(argv[1]);
            if(n< Led_Num)
            {
                wLedStatus status;
                if(wStr_nContain(argv[2],"on",2) == 0)
                {
                    status = Led_On;
                }
                else if(wStr_nContain(argv[2],"off",3) == 0)
                {
                    status = Led_Off;
                }
                else if(wStr_nContain(argv[2],"flast",5) == 0)
                {
                    status = Led_Flast;
                }
                else if(wStr_nContain(argv[2],"flash1",6) == 0)
                {
                    status = Led_Flash1;
                }
                else if(wStr_nContain(argv[2],"flash2",6) == 0)
                {
                    status = Led_Flash2;
                }
                else if(wStr_nContain(argv[2],"flash3",6) == 0)
                {
                    status = Led_Flash3;
                }
                else if(wStr_nContain(argv[2],"flash4",6) == 0)
                {
                    status = Led_Flash4;
                }
                else if(wStr_nContain(argv[2],"flash5",6) == 0)
                {
                    status = Led_Flash5;
                }
                else if(wStr_nContain(argv[2],"flash6",6) == 0)
                {
                    status = Led_Flash6;
                }
                else
                {
                    status = Led_No;
                }
                
                if(status != Led_No)
                {
                    wLed_SetIdStatus(n,status,0);
                    wShell_Printf(Id,"OK: The control of Led is OK \n");
                }
                else
                {
                    wShell_Printf(Id,"Error: The control of Led is ERR \n");
                }
                
            }
            else
            {
                wShell_Printf(Id,"Error: The number of Led is ERR \n");
            }
        }
        else
        {
            wShell_Printf(Id,"Error: Not user, please su user!\n");//当前没有用户登录
        }
    }
    else
    {
        wShell_Printf(Id,"Error: Usage: led [argument1-num] [argument2-on/off/flast/flash1-6]\n");
    } 
}

void wLed_CmdInit(void)
{
    wShell_Add(&ShellCmd_led,"led",115,wCmd_led,"led Usage: led [argument1-num] [argument2-on/off/flast/flash1-6] \n");//添加add命令 
}
#endif

wStatus wLed_IdInit(uint16_t id,wPin pin,wGpio_Level level,wLedStatus LedStatus,uint8_t LoopCnt)
{
    wStatus Status = wOK;
    OS_ERR               oserr;
    
    if( id < Led_Num)
    {
        wLedDef* pLed = &led[id];

        OSTmrCreate (&pLed->Tmr_On,"Led Tmr_On",0,0,OS_OPT_TMR_ONE_SHOT,wLed_TmrOn,pLed,&oserr);//创建定时器    
        OSTmrCreate (&pLed->Tmr_Off,"Led Tmr_Off",0,0,OS_OPT_TMR_ONE_SHOT,wLed_TmrOff,pLed,&oserr);//创建定时器 
        
        pLed->Flag = Led_Stop;  
        
        wGpio_putInit(&pLed->CSS,pin,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_MEDIUM,level);
        wLed_SetIdStatus(id,LedStatus,LoopCnt);
    } 
    else
    {
        Status = wERROR;
    }
    
    return Status;    
}

//配置灯的显示状态
wStatus wLed_SetIdStatus(uint16_t id,wLedStatus LedStatus,uint8_t LoopCnt)
{
    wStatus Status = wOK;
    
    if( id < Led_Num)
    {
        wLedDef* pLed = &led[id];
        
        if(LedStatus != Led_No)
        {
            pLed->LedStatus = LedStatus;
            pLed->Num = 1;
            pLed->LoopCnt = LoopCnt;
            
            if(pLed->Flag == Led_Stop)
            {
                wLed_TmrOn(0, pLed);
            }
        } 
    } 
    else
    {
        Status = wERROR;
    }
    
    return Status;      
}

//配置灯的显示状态
wStatus wLed_SetStatus(wLedDef* pLed,wLedStatus LedStatus,uint8_t LoopCnt)
{
    wStatus Status = wOK;    
    if(pLed != 0)
    {
        if(LedStatus != Led_No)
        {
            pLed->LedStatus = LedStatus;
            pLed->Num = 1;
            pLed->LoopCnt = LoopCnt;
            
            if(pLed->Flag == Led_Stop)
            {
                wLed_TmrOn(0, pLed);
            }
        }
    }
    else
    {
        Status = wERROR;
    }
    
    return Status;      
}

//初使化灯的参数
wStatus wLed_Init(wLedDef* pLed,wPin pin,wGpio_Level level,wLedStatus LedStatus,uint8_t LoopCnt)
{
    wStatus Status = wOK; 
    OS_ERR               oserr;
    
    if(pLed != 0)
    {    
        OSTmrCreate (&pLed->Tmr_On,"Led Tmr_On",0,0,OS_OPT_TMR_ONE_SHOT,wLed_TmrOn,pLed,&oserr);//创建定时器    
        OSTmrCreate (&pLed->Tmr_Off,"Led Tmr_Off",0,0,OS_OPT_TMR_ONE_SHOT,wLed_TmrOff,pLed,&oserr);//创建定时器 
        
        pLed->Flag = Led_Stop;  
        
        wGpio_putInit(&pLed->CSS,pin,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_MEDIUM,level);
        wLed_SetStatus(pLed,LedStatus,LoopCnt);
    }
    else
    {
        Status = wERROR;
    }
    
    return Status;          
}

static void wLed_TmrOn(void *p_tmr, void *p_arg)
{//定时器亮灯回调函数
    OS_ERR  oserr;
    wLedDef * pLed = p_arg;
    uint16_t timeout = 0;
    
    wGpio_putWrite(&pLed->CSS,Set_ACTIVE);//亮灯

    switch(pLed->LedStatus)
    {
        case Led_No:{pLed->Flag = Led_Stop;}break;
        case Led_Off:
        {
            wGpio_putWrite(&pLed->CSS,Set_INACTIVE);//灭灯
            pLed->Flag = Led_Stop;
        }break;
        case Led_On:
        {
            pLed->Flag = Led_Stop;
            //不处理
        }break;
        case Led_Flash1:
        {
            timeout = 500;
        }break;
        case Led_Flast:
        case Led_Flash2:
        case Led_Flash3:
        case Led_Flash4:
        case Led_Flash5:
        case Led_Flash6:
        {
            timeout = 100;
        }break;
     
    }
    if(timeout > 0)
    {
        timeout = timeout * OS_CFG_TMR_TASK_RATE_HZ / 1000;
        OSTmrSet(&pLed->Tmr_Off,timeout,timeout,wLed_TmrOff,pLed,&oserr);
        OSTmrStart(&pLed->Tmr_Off,&oserr);
    }
 
}

static void wLed_TmrOff(void *p_tmr, void *p_arg)
{//定时器灭灯回调函数
    OS_ERR  oserr;
    wLedDef * pLed = p_arg;
    uint16_t timeout = 0;
    
    wGpio_putWrite(&pLed->CSS,Set_INACTIVE);//灭灯   
    switch(pLed->LedStatus)
    {
        case Led_No:{pLed->Flag = Led_Stop;}break;
        case Led_Off:
        {
            pLed->Flag = Led_Stop;
            //不处理
        }break;
        case Led_On:
        {
            pLed->Flag = Led_Stop;
            wGpio_putWrite(&pLed->CSS,Set_ACTIVE);//亮灯
        }break;
        case Led_Flast:
        {
            timeout = 200;
            if(pLed->LoopCnt > 0)
            {
                pLed->LoopCnt--;
                if(pLed->LoopCnt == 0)
                {
                    pLed->Flag = Led_Stop;
                    timeout = 0;
                }
            }
        }break;
        case Led_Flash1:
        {
            timeout = 500;
            if(pLed->LoopCnt > 0)
            {
                pLed->LoopCnt--;
                if(pLed->LoopCnt == 0)
                {
                    pLed->Flag = Led_Stop;
                    timeout = 0;
                }
            }            
        }break;
        case Led_Flash2:
        case Led_Flash3:
        case Led_Flash4:
        case Led_Flash5:
        case Led_Flash6:
        {
            if(pLed->Num < pLed->LedStatus)
            {
                pLed->Num++;
                timeout = 400;
            }
            else
            {
                pLed->Num=1;
                timeout = 1600;
                if(pLed->LoopCnt > 0)
                {
                    pLed->LoopCnt--;
                    if(pLed->LoopCnt == 0)
                    {
                        pLed->Flag = Led_Stop;
                        timeout = 0;
                    }
                }                
            }
        }break;
    }

    if(timeout > 0)
    {
        timeout = timeout * OS_CFG_TMR_TASK_RATE_HZ / 1000;
        OSTmrSet(&pLed->Tmr_On,timeout,timeout,wLed_TmrOn,pLed,&oserr);
        OSTmrStart(&pLed->Tmr_On,&oserr);
    }    
}
