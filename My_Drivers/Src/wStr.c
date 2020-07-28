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

#include "wStr.h"
#include "wS.h"

#define is_digit(c) ((c) >= '0' && (c) <= '9')

void* wStr_MeSet(void* p_str,char ch,unsigned long count)
{//�����ַ�����ֵȫΪch
    
    if(!p_str) return 0;
    
    char *pstr = p_str;
    
    while(count--)
    {
        *pstr++ = ch;
    }
    
    return p_str;
}

void* wStr_MemCpy(void *dst, const void *src, unsigned long count)
{
   if(!(dst && src)) return 0;
    
   char * pchdst = (char*)dst;
   char * pchsrc = (char*)src;
    
   while((count--) && (*pchsrc != '\0'))
   {
       *pchdst++ = *pchsrc++;
   }
   
   *pchdst = '\0';
   
   return dst;
}

//�ڲ��� str ��ָ����ַ�����������һ�γ����ַ� c��һ���޷����ַ�����λ�� 
char* wStr_Chr(const char *p_str, char ch)
{
    while(*p_str && *p_str != ch) {p_str++;}
 
    if (*p_str == (char)ch)
    {
        return((char *)p_str);
    }
 
    return 0;
}

char* wStr_Itoa(int num, char * str)
{
    int i = 1;
    
    char * pch = str;
    if(!pch) return 0;
    
    while(num / i) i *= 10;
    
    if(num < 0)
    {
        num = -num;
        *pch++ = '-';
    }
    
    if (0 == num) i = 10;
    
    while(i /= 10)
    {
        *pch++ = num / i + '0';
        num %= i;
    }
    
    *pch = '\0';
    
    return str;
}

unsigned int wStr_nLen(const char *p_str, unsigned int count)
{
    const char *sc;
    for (sc = p_str; *sc != '\0' && count--; ++sc)
    /* nothing */;
    return sc - p_str;
}

unsigned int wStr_Len(const char *p_str)
{//ȡ�ַ����еĳ���
    const  char  *pstr = p_str;
    unsigned int len = 0;
    
    while((pstr != (const char *)  0 ) && (*pstr != (char)'\0'))
    {
        pstr++;len++;
    }
    return len;
    
/*  
    ��һ��ʵ�ַ���
    const char *p = str;
    while(*p++);
    return (int)(p - str - 1);
*/       
}

int wStr_Cmp(const char *p1_str,const char *p2_str)
{//�Ƚ����ַ����Ƿ���ȣ���ȷ���0�����ȷ�������ֵ
    while (( p1_str != (const char*) 0) && ( p2_str != (const char*) 0)) 
    {
        if(*p1_str == *p2_str)
        {
            if(*p1_str == (char)'\0')
            {
                //�����Ƚ���ȣ���������
                return 0;
            }
            else
            {
                //�����Ƚ���ȣ�������һλ�Ƚ�
                p1_str++;
                p2_str++;
            }
        }
        else
        {
            //��������ȣ���ǰ����
            return (*p1_str - *p2_str);
        }
    } 
    return -1;//��ַΪ��
}

int wStr_nCmp(const void *p1_str,const void *p2_str,int count)
{//�Ƚ����ַ����Ƿ���ȣ���ȷ���0�����ȷ�������ֵ
   
    const char *p1str = p1_str;
    const char *p2str = p2_str;
    
    if(count <= 0) return 0;
    while(--count && *p1str == *p2str)
    {        
        p1str++;
        p2str++;
    }
    return (*p1str - *p2str);
}

int wStr_nContain(const char *p1_str,const char *p2_str,int count)
{//�Ƚ����ַ����Ƿ���ȣ���ȷ���0�����ȷ�������ֵ
    
    if(count <= 0) return 0;
    while(--count && *p1_str && *p1_str == *p2_str)
    {        
        p1_str++;
        p2_str++;
    }
    return (*p1_str - *p2_str);
}

char *wStr_Copy (char  *pstr_dest,const char *pstr_src)
{//�����ַ���
    char  *pstr = pstr_dest;
    
    if((pstr == 0) || (pstr_src == 0))
    {
        return 0;
    }
    
    while((pstr != 0) && (pstr_src != 0)&&(*pstr_src != '\0'))
    {
        *pstr++ = *pstr_src++;
    }

    *pstr = '\0';//��β����������
  
    return pstr_dest;
}

char wStr_Tolower(char chr)
{//��������д��ĸת��ΪСд��ĸ
    if (chr >= 'A' && chr <= 'Z')  
    {  
        return chr + 0x20;  
    }  
    else  
    {  
        return chr;  
    } 
}
char* wStr_lwr(char* p_str)
{//����д��ĸת��ΪСд��ĸ
    char *pstr = p_str;
    
    while(*pstr != '\0')
    {
        
        if (*pstr >= 'A' && *pstr <= 'Z')  
        {  
            *pstr += 0x20;  pstr++;
        }  
    }

    return p_str;  
}

char wStr_Upper(char chr)
{//������Сд��ĸת��Ϊ��д��ĸ
    if (chr >= 'a' && chr <= 'z')  
    {  
        return chr - 0x20;  
    }  
    else  
    {  
        return chr;  
    } 
}

char* wStr_Upr(char* p_str)
{//��Сд��ĸת��Ϊ��д��ĸ
    char *pstr = p_str;
    
    while(*pstr != '\0')
    {
        
        if (*pstr >= 'a' && *pstr <= 'z')  
        {  
            *pstr -= 0x20;  pstr++;
        }  
    }

    return p_str; 
}

char* wStr_Cntrl(char* p_str,unsigned int count)
{//������ɼ��ַ�
    char *pstr = p_str;
    
    while((*pstr != '\0') && (count--))
    {
        if (*pstr <= 0x1F)  
        {  
            *pstr = '\0';
        } 
        pstr++;
    }

    return p_str;     
}

int wStr_Atoi(const char *p_str)
{//��һ��ʮ�������ֵ��ַ���ת��Ϊ��Ӧ������ ����������1234��ת��������1234.
    const  char  *pstr = p_str;
    int n = 0;
    int sign = 1;

    while(pstr != 0)
    {
        if(*pstr == '\0')
        {
            return 0;
        }
        else if( (*pstr == '-') || (*pstr == '+') || is_digit(*pstr) )
        {
            break;//��⵽��Чֵ���˳�
        }
        else
        {
            pstr++;//������Ч�ֽ�
        }
    }
    
    if(*pstr == '-')
    {
        sign = -1; pstr++;//�и���
    }
    else if(*pstr == '+') 
    {
        sign = 1; pstr++;//������
    }
    else{sign = 1;}//��������

    if(!is_digit(*pstr))
    {
        return 0;//�������־��˳�
    }
    
    while(is_digit(*pstr))
    {
        n = 10*n+(*pstr++ - '0');//��������
    }
    
    return (sign*n);  
}


int wStr_Htoi(const char *p_str)
{//��ʮ�����Ƶ��ַ���ת��������
 
    const  char  *pstr = p_str;
    int n = 0;
    int sign = 1;

    while(pstr != 0)
    {
        if(*pstr == '\0')
        {
            return 0;
        }
        else if( (*pstr == '-') || (*pstr == '+') || is_digit(*pstr) || \
                ((*pstr >= 'a') && (*pstr <= 'f')) || ((*pstr >='A') && (*pstr <= 'F')) )
        {
            break;//��⵽��Чֵ���˳�
        }
        else
        {
            pstr++;//������Ч�ֽ�
        }
    }
    
    if(*pstr == '-')
    {
        sign = -1; pstr++;//�и���
    }
    else if(*pstr == '+') 
    {
        sign = 1; pstr++;//������
    }
    else{sign = 1;}//��������

    
    if(*pstr != '0') return 0;//��1����ĸΪ0
    
    pstr++;
    
    if(!((*pstr == 'x') || (*pstr == 'X'))) return 0;//��2����ĸΪx��X
    
    pstr++;
    
    while(is_digit(*pstr) || ((*pstr >= 'a') && (*pstr <= 'f')) || ((*pstr >='A') && (*pstr <= 'F')))
    {
        if(is_digit(*pstr))
        {
            n = 16 * n + ( *pstr++ - '0');  //����
        }
        else if((*pstr >= 'a') && (*pstr <= 'f'))
        {
            n = 16 * n + ( 10 + *pstr++ - 'a');  //���� abcdef
        }
        else
        {
            n = 16 * n + ( 10 + *pstr++ - 'A');  //���� ABCDEF
        }
        
    }
    
    return (sign*n);           
}

double wStr_Atof(const char *p_str)
{//��һ�����������ַ���ת��Ϊ��Ӧ�ĸ����� ����������12.34��ת���ɸ�����12.34.
    
    const  char  *pstr = p_str;
    double n = 0,div=10.0;
    int sign = 1;
    
    int jishu = 0,jishu_sign;
    
    while(pstr != 0)
    {
        if(*pstr == '\0')
        {
            return 0;
        }
        else if( (*pstr == '-') || (*pstr == '+') || is_digit(*pstr) )
        {
            break;//��⵽��Чֵ���˳�
        }
        else
        {
            pstr++;//������Ч�ֽ�
        }
    }
    
    if(*pstr == '-')
    {
        sign = -1; pstr++;//�и���
    }
    else if(*pstr == '+') 
    {
        sign = 1; pstr++;//������
    }
    else{sign = 1;}//��������
    
    if(!is_digit(*pstr))
    {
        return 0;//�������־��˳�
    }

    while((*pstr >= '0') && (*pstr <= '9') && (*pstr != '.') )
    {
        n = 10.0*n+(*pstr++ - '0');//��������
    }
    
    if(*pstr == '.')
    {//��С����
        pstr++;
 
        if(!is_digit(*pstr))
        {
            return (sign*n);//����
        }
    
        while(is_digit(*pstr))
        {
            n = n + (*pstr++ - '0')/div;//С������
            div*=10.0;
        }
    }
    
    if((*pstr == 'e') || (*pstr == 'E'))
    {//��ѧ������
        pstr++;
        if(*pstr == '-')
        {
            jishu_sign = -1;pstr++;
        }
        else if(*pstr == '+')
        {
            jishu_sign = 1;pstr++;
        }
        else
        {
            jishu_sign = 1;
        }

        if(!is_digit(*pstr))
        {
            return (sign*n);//����
        }
    
        while(is_digit(*pstr))
        {
            jishu = jishu * 10 + (*pstr++ - '0');//ָ������
        }
        
        jishu = jishu_sign*jishu;
        
        if(jishu > 0)
        {
            while(jishu-- > 0 )
            {
                n = n * 10;
            }
        }
        else if(jishu == 0)
        {
            n = 1;
        }
        else
        {
            while(jishu ++<0)
            {
                n = n / 10;
            }            
        }  
    }

    return (sign*n);  
}













/* Exported macro ------------------------------------------------------------*/
#define IS_CAP_LETTER(c)    (((c) >= 'A') && ((c) <= 'F'))
#define IS_LC_LETTER(c)     (((c) >= 'a') && ((c) <= 'f'))
#define IS_09(c)            (((c) >= '0') && ((c) <= '9'))
#define ISVALIDHEX(c)       (IS_CAP_LETTER(c) || IS_LC_LETTER(c) || IS_09(c))
#define ISVALIDDEC(c)       IS_09(c)
#define CONVERTDEC(c)       (c - '0')

#define CONVERTHEX_ALPHA(c) (IS_CAP_LETTER(c) ? ((c) - 'A'+10) : ((c) - 'a'+10))
#define CONVERTHEX(c)       (IS_09(c) ? ((c) - '0') : CONVERTHEX_ALPHA(c))

/**
  * @brief  Convert an Integer to a string
  * @param  p_str: The string output pointer
  * @param  intnum: The integer to be converted
  * @retval None
  */
void Int2Str(uint8_t *p_str, uint32_t intnum)
{
    uint32_t i, divider = 1000000000, pos = 0, status = 0;

    for (i = 0; i < 10; i++)
    {
        p_str[pos++] = (intnum / divider) + '0' ;

        intnum = intnum % divider;
        divider /= 10;
        if ((p_str[pos-1] == '0') & (status == 0))
        {
            pos = 0;
        }
        else
        {
            status++;
        }
    }
}

/**
  * @brief  Convert a string to an integer
  * @param  p_inputstr: The string to be converted
  * @param  p_intnum: The integer value
  * @retval 1: Correct
  *         0: Error
  */
uint32_t Str2Int(uint8_t *p_inputstr, uint32_t *p_intnum)
{
    uint32_t i = 0, res = 0;
    uint32_t val = 0;

    if ((p_inputstr[0] == '0') && ((p_inputstr[1] == 'x') || (p_inputstr[1] == 'X')))
    {
        i = 2;
        while ( ( i < 11 ) && ( p_inputstr[i] != '\0' ) )
        {
            if (ISVALIDHEX(p_inputstr[i]))
            {
                val = (val << 4) + CONVERTHEX(p_inputstr[i]);
            }
            else
            {
                /* Return 0, Invalid input */
                res = 0;
                break;
            }
            i++;
        }

        /* valid result */
        if (p_inputstr[i] == '\0')
        {
            *p_intnum = val;
            res = 1;
        }
    }
    else /* max 10-digit decimal input */
    {
        while ( ( i < 11 ) && ( res != 1 ) )
        {
            if (p_inputstr[i] == '\0')
            {
                *p_intnum = val;
                /* return 1 */
                res = 1;
            }
            else if (((p_inputstr[i] == 'k') || (p_inputstr[i] == 'K')) && (i > 0))
            {
                val = val << 10;
                *p_intnum = val;
                res = 1;
            }
            else if (((p_inputstr[i] == 'm') || (p_inputstr[i] == 'M')) && (i > 0))
            {
                val = val << 20;
                *p_intnum = val;
                res = 1;
            }
            else if (ISVALIDDEC(p_inputstr[i]))
            {
                val = val * 10 + CONVERTDEC(p_inputstr[i]);
            }
            else
            {
                /* return 0, Invalid input */
                res = 0;
                break;
            }
            i++;
        }
    }

    return res;
}
