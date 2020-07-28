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
{//设置字符串的值全为ch
    
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

//在参数 str 所指向的字符串中搜索第一次出现字符 c（一个无符号字符）的位置 
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
{//取字符串中的长度
    const  char  *pstr = p_str;
    unsigned int len = 0;
    
    while((pstr != (const char *)  0 ) && (*pstr != (char)'\0'))
    {
        pstr++;len++;
    }
    return len;
    
/*  
    另一种实现方法
    const char *p = str;
    while(*p++);
    return (int)(p - str - 1);
*/       
}

int wStr_Cmp(const char *p1_str,const char *p2_str)
{//比较两字符串是否相等，相等返回0，不等返回其它值
    while (( p1_str != (const char*) 0) && ( p2_str != (const char*) 0)) 
    {
        if(*p1_str == *p2_str)
        {
            if(*p1_str == (char)'\0')
            {
                //表明比较相等，正常结束
                return 0;
            }
            else
            {
                //表明比较相等，继续下一位比较
                p1_str++;
                p2_str++;
            }
        }
        else
        {
            //表明不相等，提前结束
            return (*p1_str - *p2_str);
        }
    } 
    return -1;//地址为空
}

int wStr_nCmp(const void *p1_str,const void *p2_str,int count)
{//比较两字符串是否相等，相等返回0，不等返回其它值
   
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
{//比较两字符串是否相等，相等返回0，不等返回其它值
    
    if(count <= 0) return 0;
    while(--count && *p1_str && *p1_str == *p2_str)
    {        
        p1_str++;
        p2_str++;
    }
    return (*p1_str - *p2_str);
}

char *wStr_Copy (char  *pstr_dest,const char *pstr_src)
{//复制字符串
    char  *pstr = pstr_dest;
    
    if((pstr == 0) || (pstr_src == 0))
    {
        return 0;
    }
    
    while((pstr != 0) && (pstr_src != 0)&&(*pstr_src != '\0'))
    {
        *pstr++ = *pstr_src++;
    }

    *pstr = '\0';//在尾部补结束符
  
    return pstr_dest;
}

char wStr_Tolower(char chr)
{//将单个大写字母转换为小写字母
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
{//将大写字母转换为小写字母
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
{//将单个小写字母转换为大写字母
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
{//将小写字母转换为大写字母
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
{//清除不可见字符
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
{//把一个十进制数字的字符串转换为相应的整数 举例：将“1234”转换成整数1234.
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
            break;//检测到有效值后退出
        }
        else
        {
            pstr++;//过滤无效字节
        }
    }
    
    if(*pstr == '-')
    {
        sign = -1; pstr++;//有负号
    }
    else if(*pstr == '+') 
    {
        sign = 1; pstr++;//有正号
    }
    else{sign = 1;}//无正负号

    if(!is_digit(*pstr))
    {
        return 0;//不是数字就退出
    }
    
    while(is_digit(*pstr))
    {
        n = 10*n+(*pstr++ - '0');//整数部分
    }
    
    return (sign*n);  
}


int wStr_Htoi(const char *p_str)
{//将十六进制的字符串转换成整数
 
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
            break;//检测到有效值后退出
        }
        else
        {
            pstr++;//过滤无效字节
        }
    }
    
    if(*pstr == '-')
    {
        sign = -1; pstr++;//有负号
    }
    else if(*pstr == '+') 
    {
        sign = 1; pstr++;//有正号
    }
    else{sign = 1;}//无正负号

    
    if(*pstr != '0') return 0;//第1个字母为0
    
    pstr++;
    
    if(!((*pstr == 'x') || (*pstr == 'X'))) return 0;//第2个字母为x或X
    
    pstr++;
    
    while(is_digit(*pstr) || ((*pstr >= 'a') && (*pstr <= 'f')) || ((*pstr >='A') && (*pstr <= 'F')))
    {
        if(is_digit(*pstr))
        {
            n = 16 * n + ( *pstr++ - '0');  //数字
        }
        else if((*pstr >= 'a') && (*pstr <= 'f'))
        {
            n = 16 * n + ( 10 + *pstr++ - 'a');  //数字 abcdef
        }
        else
        {
            n = 16 * n + ( 10 + *pstr++ - 'A');  //数字 ABCDEF
        }
        
    }
    
    return (sign*n);           
}

double wStr_Atof(const char *p_str)
{//把一个浮点数的字符串转换为相应的浮点数 举例：将“12.34”转换成浮点数12.34.
    
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
            break;//检测到有效值后退出
        }
        else
        {
            pstr++;//过滤无效字节
        }
    }
    
    if(*pstr == '-')
    {
        sign = -1; pstr++;//有负号
    }
    else if(*pstr == '+') 
    {
        sign = 1; pstr++;//有正号
    }
    else{sign = 1;}//无正负号
    
    if(!is_digit(*pstr))
    {
        return 0;//不是数字就退出
    }

    while((*pstr >= '0') && (*pstr <= '9') && (*pstr != '.') )
    {
        n = 10.0*n+(*pstr++ - '0');//整数部分
    }
    
    if(*pstr == '.')
    {//有小数点
        pstr++;
 
        if(!is_digit(*pstr))
        {
            return (sign*n);//结束
        }
    
        while(is_digit(*pstr))
        {
            n = n + (*pstr++ - '0')/div;//小数部分
            div*=10.0;
        }
    }
    
    if((*pstr == 'e') || (*pstr == 'E'))
    {//科学计数法
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
            return (sign*n);//结束
        }
    
        while(is_digit(*pstr))
        {
            jishu = jishu * 10 + (*pstr++ - '0');//指数部分
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
