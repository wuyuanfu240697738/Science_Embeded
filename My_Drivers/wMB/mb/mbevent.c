/*
********************************************************************************************************
*                                                wModbus
*                                 The Embedded Modbus Stack Software
*
*               Copyright: Wu YuanFu. All rights reserved.Protected by international copyright laws.
*
* Programmer  : Wu YuanFu
* Version     : V2.50
* LICENSING TERMS:
* ---------------
*           wModbus is provided in source form for FREE short-term evaluation, for educational use or
*           for peaceful research.  If you plan or intend to use wModbus in a commercial application/
*           product then, you need to contact Wu YuanFu<240697738@qq.com> to properly license wModbus
*           for its use in your application/product.  The fact that the source is provided does NOT 
*           mean that you can use it commercially without paying a licensing fee.
*
*           Knowledge of the source code may NOT be used to develop a similar product.
*               
********************************************************************************************************
*/

/* Filename    : mbevent.c*/

#include "mb.h"
  
#define MB_linux                              ( 0 )
#define MB_ucos                               ( 1 )
#define MB_rtthread                           ( 2 )

#define MB_EventMutex  MB_ucos

#if (MB_EventMutex ==  MB_linux)
	#include<pthread.h>
#elif (MB_EventMutex ==  MB_ucos)
	#include "oS.h" 
#endif
 
/*
********************************************************************************************************
*                                                Init A Mutex RunRes 
*
* Description: �˺������ڳ�ʹ��RunRes������Դ
* Arguments  : p_mb           ָ��1��wModbus��ָ��
* Returns    : UCHAR          ���ش�����
*                   MBTRUE              ����
*                   MBFALSE             ���� 
* Note(s)    : 1 MB_MutexInit() ��MASTER Modbus��ʹ��
********************************************************************************************************
*/
UCHAR MB_MutexInit( wMB *p_mb , void* mutex)
{
    p_mb->Mutex = mutex;
    
    if( p_mb->Mutex == 0 )
    {
         return MBTRUE; 
    }
	
	#if (MB_EventMutex ==  MB_linux)
		int error;
		error = pthread_mutex_init(p_mb->Mutex, NULL);
		if( error == 0) return MBTRUE; else return MBFALSE;
	#elif (MB_EventMutex ==  MB_ucos)
		OS_ERR       OsErr;
		OSMutexCreate(p_mb->Mutex, "Master Run Res Sem",&OsErr );
		if( OsErr == OS_ERR_NONE) return MBTRUE; else return MBFALSE;
	#endif
}

/*
********************************************************************************************************
*                                                Close A Mutex RunRes
*
* Description: �˺�������ɾ��RunRes������Դ
* Arguments  : p_mb           ָ��1��wModbus��ָ��
* Returns    : UCHAR          ���ش�����
*                   MBTRUE              ����
*                   MBFALSE             ���� 
* Note(s)    : 1) MB_MutexClose()
********************************************************************************************************
*/
UCHAR MB_MutexClose( wMB *p_mb )
{
    if( p_mb->Mutex == 0 )
    {
         return MBTRUE; 
    }  
	
	#if (MB_EventMutex ==  MB_linux)
		int error;
		error = pthread_mutex_destroy(p_mb->Mutex);
		if( error == 0) return MBTRUE; else return MBFALSE;
	#elif (MB_EventMutex ==  MB_ucos)
		OS_ERR       OsErr;
		OSMutexDel(p_mb->Mutex,OS_OPT_DEL_ALWAYS,&OsErr );
		if( OsErr == OS_ERR_NONE) return MBTRUE; else return MBFALSE;
	#endif
} 

/*
********************************************************************************************************
*                                                Post A Mutex RunRes
*
* Description: �˺������ڷ���RunRes������Դ
* Arguments  : p_mb           ָ��1��wModbus��ָ��
* Returns    : UCHAR          ���ش�����
*                   MBTRUE              ����
*                   MBFALSE             ���� 
* Note(s)    : 1) MB_MutexPost() ��MASTER Modbus��ʹ��
********************************************************************************************************
*/
UCHAR MB_MutexPost( wMB *p_mb )
{
    if( p_mb->Mutex == 0 )
    {
         return MBTRUE; 
    } 

	#if (MB_EventMutex ==  MB_linux)
		int error;
		error = pthread_mutex_unlock(p_mb->Mutex);
		if( error == 0) return MBTRUE; else return MBFALSE;
	#elif (MB_EventMutex ==  MB_ucos)
		OS_ERR       OsErr;
		OSMutexPost(p_mb->Mutex,OS_OPT_POST_NONE, &OsErr);
		if( OsErr == OS_ERR_NONE) return MBTRUE; else return MBFALSE;
	#endif	
}

/*
********************************************************************************************************
*                                                Pend A Mutex RunRes
*
* Description: �˺�����������RunRes������Դ
* Arguments  : p_mb           ָ��1��wModbus��ָ��
* Returns    : UCHAR          ���ش�����
*                   MBTRUE              ����
*                   MBFALSE             ���� 
* Note(s)    : 1) MB_MutexPend() ��MASTER Modbus��ʹ��
********************************************************************************************************
*/
UCHAR MB_MutexPend( wMB *p_mb)
{
    if( p_mb->Mutex == 0 )
    {
         return MBTRUE; 
    }
	
	#if (MB_EventMutex ==  MB_linux)
		int error;
		error = pthread_mutex_lock(p_mb->Mutex);
		if( error == 0) return MBTRUE; else return MBFALSE;
	#elif (MB_EventMutex ==  MB_ucos)
		OS_ERR       OsErr;
		OSMutexPend(p_mb->Mutex, 0, OS_OPT_PEND_BLOCKING, 0, &OsErr);
		if( OsErr == OS_ERR_NONE) return MBTRUE; else return MBFALSE;
	#endif	
}
