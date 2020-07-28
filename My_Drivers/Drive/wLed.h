
#ifndef __WY_LED_H
#define __WY_LED_H

	#include "wS.h"
	#include "os.h"  
	#include "wGpio.h" 

typedef enum
{
    Led_No=0,       //����
    Led_Flash1=1,   //Flash 1
    Led_Flash2=2,   //Flash 2
    Led_Flash3=3,   //Flash 3
    Led_Flash4=4,   //Flash 4
    Led_Flash5=5,   //Flash 5
    Led_Flash6=6,   //Flash 6  
    Led_Flast=7,    //Flast    
    Led_Off=8,      //����
    Led_On=9,       //����
}wLedStatus;

typedef enum
{
    Led_Stop=0,   //ֹͣ    
    Led_Start=1,   //������
}wLedFalg;

typedef  struct{
    wLedStatus  LedStatus;
    uint8_t     Num;
    uint8_t     LoopCnt; //ѭ������   
    wLedFalg    Flag;//���б�־   
    OS_TMR      Tmr_On;    
    OS_TMR      Tmr_Off; 
    wGpio_Def   CSS;//Led����    
}wLedDef;

void wLed_CmdInit(void);

wStatus wLed_SetIdStatus(uint16_t id,wLedStatus LedStatus,uint8_t LoopCnt);
wStatus wLed_IdInit(uint16_t id,wPin pin,wGpio_Level level,wLedStatus LedStatus,uint8_t LoopCnt);

wStatus wLed_SetStatus(wLedDef* pLed,wLedStatus LedStatus,uint8_t LoopCnt);
wStatus wLed_Init(wLedDef* pLed,wPin pin,wGpio_Level level,wLedStatus LedStatus,uint8_t LoopCnt);

#endif
