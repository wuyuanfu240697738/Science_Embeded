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

/* Filename    : wStr.c*/


#ifndef __WY_STR_H
#define __WY_STR_H

#ifdef __cplusplus
 extern "C" {
#endif
 
char* wStr_Chr(const char *p_str, char ch);

char* wStr_Itoa(int num, char * str);

void* wStr_MeSet(void* p_str,char ch,unsigned long count);//设置字符串的值全为ch

unsigned int wStr_Len(const char *p_str);//取字符串中的长度
unsigned int wStr_nLen(const char *p_str, unsigned int count);

char *wStr_Copy (char  *pstr_dest,const char *pstr_src);//复制字符串
void* wStr_MemCpy(void *dst, const void *src, unsigned long count);

char* wStr_Cntrl(char* p_str,unsigned int count);//清除不可见字符

int wStr_Cmp(const char *p1_str,const char *p2_str);//比较两字符串是否相等，相等返回0，不等返回其它值

int wStr_nCmp(const void *p1_str,const void *p2_str,int count);

char wStr_Tolower(char chr);//将单个大写字母转换为小写字母

char* wStr_lwr(char* p_str);//将大写字母转换为小写字母

char wStr_Upper(char chr);//将单个小写字母转换为大写字母

char* wStr_Upr(char* p_str);//将小写字母转换为大写字母

int wStr_Atoi(const char *p_str);//把一个十进制数字的字符串转换为相应的整数 举例：将“1234”转换成整数1234.

int wStr_Htoi(const char *p_str);//将十六进制的字符串转换成整数

double wStr_Atof(const char *p_str);//把一个浮点数的字符串转换为相应的浮点数 举例：将“12.34”转换成浮点数12.34.

int wStr_nContain(const char *p1_str,const char *p2_str,int count);
#ifdef __cplusplus
}
#endif

#endif
