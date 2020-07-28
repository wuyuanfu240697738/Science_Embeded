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

void* wStr_MeSet(void* p_str,char ch,unsigned long count);//�����ַ�����ֵȫΪch

unsigned int wStr_Len(const char *p_str);//ȡ�ַ����еĳ���
unsigned int wStr_nLen(const char *p_str, unsigned int count);

char *wStr_Copy (char  *pstr_dest,const char *pstr_src);//�����ַ���
void* wStr_MemCpy(void *dst, const void *src, unsigned long count);

char* wStr_Cntrl(char* p_str,unsigned int count);//������ɼ��ַ�

int wStr_Cmp(const char *p1_str,const char *p2_str);//�Ƚ����ַ����Ƿ���ȣ���ȷ���0�����ȷ�������ֵ

int wStr_nCmp(const void *p1_str,const void *p2_str,int count);

char wStr_Tolower(char chr);//��������д��ĸת��ΪСд��ĸ

char* wStr_lwr(char* p_str);//����д��ĸת��ΪСд��ĸ

char wStr_Upper(char chr);//������Сд��ĸת��Ϊ��д��ĸ

char* wStr_Upr(char* p_str);//��Сд��ĸת��Ϊ��д��ĸ

int wStr_Atoi(const char *p_str);//��һ��ʮ�������ֵ��ַ���ת��Ϊ��Ӧ������ ����������1234��ת��������1234.

int wStr_Htoi(const char *p_str);//��ʮ�����Ƶ��ַ���ת��������

double wStr_Atof(const char *p_str);//��һ�����������ַ���ת��Ϊ��Ӧ�ĸ����� ����������12.34��ת���ɸ�����12.34.

int wStr_nContain(const char *p1_str,const char *p2_str,int count);
#ifdef __cplusplus
}
#endif

#endif
