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

/* Filename    : wSprintf.c*/

#ifndef __WY_SPRINTF_H
#define __WY_SPRINTF_H

#ifdef __cplusplus
 extern "C" {
#endif
     

typedef char*  va_list;

#ifndef __va_rounded_size
#define __va_rounded_size(TYPE) (((sizeof(TYPE)+sizeof(int)-1)/sizeof(int))*sizeof(int))
#endif

#ifndef va_start
#define va_start(AP, LASTARG)   (AP = ((char *)& (LASTARG) + __va_rounded_size(LASTARG)))
#endif

#ifndef va_arg
#define va_arg(AP, TYPE)        (AP += __va_rounded_size(TYPE), *((TYPE *)(AP - __va_rounded_size(TYPE))))
#endif

#ifndef va_end
#define va_end(AP)              (AP = (va_list)0 )
#endif

#ifndef size_t
    //#define size_t              unsigned int
    typedef unsigned int size_t;
#endif

#ifndef NULL
    #define NULL 0 
#endif
    

//#define     _INTSIZEOF(n)   ((sizeof(n)+sizeof(int)-1)&~(sizeof(int) - 1) )
//#define     wva_start(ap,v)  ( ap = (char*)&v + _INTSIZEOF(v) )
//#define     wva_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )


int wvsprintf(char *buf, const char *fmt, va_list args);
int wsprintf(char *buf, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
