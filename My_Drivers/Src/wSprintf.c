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

#include "wSprintf.h"
#include "wStr.h"
    
#define DOUBLE_ZERO        (double)(1E-307)
#define IS_DOUBLE_ZERO(D) (D <= DOUBLE_ZERO && D >= -DOUBLE_ZERO)

#define     ZEROPAD     1       //空位填0
#define     SIGN        2
#define     PLUS        4       //输出符号（正号或负号）
#define     SPACE       8       //输出值为正时冠以空格，为负时冠以负号
#define     LEFT        16      //结果左对齐，右边填写空格
#define     SPECIAL     32      //对c、s、d、u类无影响；对O类加前缀O；对x类加前缀0x；对e、g、f类当结果有小数时才给出小数点
#define     LARGE       64

#define is_digit(c) ((c) >= '0' && (c) <= '9')
/////////////////////////////////////////////////////////////////////////////

//该函数将字符数字串转换成整数 输入是数字串指针的指针，返回是结果数值。另外指针将前移
static int skip_atoi(const char **s)
{
    int i = 0;
    while (is_digit(**s))
    {        
        i = i * 10 + *((*s)++) - '0';
    }
    return i;
}

static const char *lower_digits = "0123456789abcdefghijklmnopqrstuvwxyz";
static const char *upper_digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
/*
将整数转换为指定进制的字符串。
num-整数  base-进制  size-字符串长度  precision-数字长度  type-类型选项
str-字符串指针
*/
static char *number(char *str, long num, int base, int size, int precision, int type)
{
    char c, sign, tmp[66];
    const char *dig;
    int i;
    
    //如果类型type指出用小写字母,则定义小定字母集。
    dig = (type & LARGE) ? upper_digits : lower_digits;
    //如果类型指出要左调整，则屏蔽类型中的填零标志
    if (type & LEFT) type &= ~ZEROPAD;
    //如果进制基数小于2或大于36，则退出处理，也即本程序只能处理基数在2-32之间的数。
    if (base < 2 || base > 36) return 0;
    //如果类型指出要填零，则置字符变量c=‘0’,否则c等于空格字符。
    c = (type & ZEROPAD) ? '0' : ' ';
    //如果类型指出是带符号数并且数值num小于0，则置符号变量sign=负号，并num取绝对值。
    //否则如果类型指出是加号，则置sign=加号，否则若类型带空格标志则sign=空格，否则置0。
    sign = 0;
    if (type & SIGN)
    {
        if (num < 0)
        {
            sign = '-';
            num = -num;
            size--;
        }
        else if (type & PLUS)
        {
            sign = '+';
            size--;
        }
        else if (type & SPACE)
        {
            sign = ' ';
            size--;
        }
    }
    //如类型指出是特殊转换，则对于十六进制宽度再减少2位（用于0x）,
    //对于八进制宽度减1（用于八进制转换结果前放一个零！。
    if (type & SPECIAL)
    {
        if (base == 16)
            size -= 2;
        else if (base == 8)
            size--;
    }
    //如果数值num为0,则临时字符串='0'；否则根据给定的基数将数值num转换成字符形式。
    i = 0;

    if (num == 0)
    {
        tmp[i++] = '0';
    }
    else
    {
        while (num != 0)
        {
            tmp[i++] = dig[((unsigned long) num) % (unsigned) base];
            num = ((unsigned long) num) / (unsigned) base;
        }
    }
    //若数值字符个数大于精度值，则精度值扩展为数字个数值。
    //宽度值size减去用于存放数值字符的个数。
    if (i > precision) precision = i;
    size -= precision;
    //从这里真正开始形成所需要的转换结果，并暂时放在字符串str中。
    //若类型中没有填零（ZEROPAD）左靠齐标志，则在str中首先
    //填放剩余宽度值指出的空格数。若需带符号位，则存入符号。    
    if (!(type & (ZEROPAD | LEFT)))
    {
        while (size-- > 0) {*str++ = ' ';}
    }
    if (sign) {*str++ = sign;}
    
    //若类型指出是特殊转换，则对于8进制转换结果头一位放置一个'0'；而对于十六进制则存放‘0x’.
    if (type & SPECIAL)
    {
        if (base == 8)
        {
            *str++ = '0';
        }
        else if (base == 16)
        {
            *str++ = '0';
            *str++ = dig[33];//注意此处
        }
    }
    //若类型中没有左调整标志，则在剩余宽度中存放C字符（'0'或空格）   
    if (!(type & LEFT))
    {
        while (size-- > 0) *str++ = c;
    }
        //此时i存有数值num的数字个数。若数字个数小于精度值，则str中放入（精度值-i）个‘0’。
    while (i < precision--) 
    {
        *str++ = '0';
    }
    //将转数值换好的数字字符填入str中。共i个。
    while (i-- > 0)
    {
        *str++ = tmp[i];
    }
    //若宽度值大于零，则表示类型标志中有左靠齐标志。则在剩余宽度中放入空格。
    while (size-- > 0)
    {
        *str++ = ' ';
    }

    return str;//返回转换好的字符串
}

static char *eaddr(char *str, unsigned char *addr, int size, int precision, int type)
{
    char tmp[24];
    const char *dig = lower_digits;
    int i, len;

    if (type & LARGE) dig = upper_digits;
    len = 0;
    for (i = 0; i < 6; i++)
    {
        if (i != 0) tmp[len++] = ':';
        tmp[len++] = dig[addr[i] >> 4];
        tmp[len++] = dig[addr[i] & 0x0F];
    }

    if (!(type & LEFT)) 
    {
        while (len < size--) *str++ = ' ';
    }
    
    for (i = 0; i < len; ++i)
    {
        *str++ = tmp[i];
    }
    
    while (len < size--) *str++ = ' ';

    return str;
}

static char *iaddr(char *str, unsigned char *addr, int size, int precision, int type)
{
    char tmp[24];
    int i, n, len;

    len = 0;
    
    for (i = 0; i < 4; i++)
    {
        if (i != 0) tmp[len++] = '.';
        n = addr[i];

        if (n == 0)
        {
            tmp[len++] = lower_digits[0];
        }
        else
        {
            if (n >= 100)
            {
                tmp[len++] = lower_digits[n / 100];
                n = n % 100;
                tmp[len++] = lower_digits[n / 10];
                n = n % 10;
            }
            else if (n >= 10)
            {
                tmp[len++] = lower_digits[n / 10];
                n = n % 10;
            }

            tmp[len++] = lower_digits[n];
        }
    }

    if (!(type & LEFT))
    {
        while (len < size--) *str++ = ' ';
    }
    
    for (i = 0; i < len; ++i)
    {    
        *str++ = tmp[i];
    }
    
    while (len < size--) *str++ = ' ';

    return str;
}

#ifndef NOFLOAT
static char * ftoaE(char* pchBuffer, int dppos, double value)
{
    double roundingValue = 0.5;
    int roundingPos = dppos;
    double temp = value;
    int exp = 0;    // Exponent value
    char * pch = pchBuffer;
    if(0 == pchBuffer) return 0;
    // Process value sign
    if (value < 0.0)
    {
        value = -value;
        *pchBuffer++ = '-';
    }
    else
    {
        *pchBuffer++ = '+';
    }
 
    // Round value and get exponent
    if(!IS_DOUBLE_ZERO(value))  /*if (value != 0.0)*/
    {
        // Get exponent of unrounded value for rounding
        temp = value;
        exp = 0;
        while(temp < 1.0)
        {
            temp *= 10.0;
            exp--;
        }
        while(temp >= 10.0)
        {
            temp *= 0.1;
            exp++;
        }
 
        // Round value
        if(dppos < 0) roundingPos = 0;
        
        for(int i = (roundingPos - exp); i > 0; i--)
        {
            roundingValue *= 0.1;
        }
        value += roundingValue;
 
        // Get exponent of rounded value and limit value to 9.999...1.000
        exp = 0;
        while(value < 1.0)
        {
            value *= 10.0;
            exp--;
        }
        while(value >= 10.0)
        {
            value *= 0.1;
            exp++;
        }
    }
 
    // Compose mantissa output string
    for (int i = ((dppos < 0) ? 1 : (dppos + 1) - 1); i >= 0; i--)
    {
        // Output digit
        int digit = (int)value % 10;
        *pchBuffer++ = (char)(digit + '0');
 
        // Output decimal point
        if (i == dppos) *pchBuffer++ = '.';
 
        value = (value - (double)digit) * 10.0;
    }
 
    // Compose exponent output string
    *pchBuffer++ = 'E';
    wStr_Itoa(exp, pchBuffer);
 
    return pch;
}
 
#define MAX_DIGITS     15
static char * ftoa(double dValue, char * chBuffer)
{
    char * pch = chBuffer;
    if(!pch) return 0;
    if(!IS_DOUBLE_ZERO(dValue))
    {
        double dRound = 5;
        if(dValue < 0)
        {
            *pch++ = '-';
            dValue = -dValue;
        }
        else
        {
            *pch++ = '+';
        }
        wStr_Itoa((int)dValue, pch);
        unsigned char ucLen = wStr_Len(pch);
        pch += ucLen;
        *pch++ = '.';
        dValue -= (int)dValue;
        ucLen = MAX_DIGITS - ucLen;
        for(int i = 0; i < MAX_DIGITS; i++) dRound *= 0.1;
        
        for(int i = 0; i < ucLen; i++)
        {
            dValue = (dValue + dRound) * 10;
            wStr_Itoa((int)dValue, pch);
            pch += wStr_Len(pch);
            dValue -= (int)dValue;
        }
    }
    else
    {
        *pch++ = '0';
        *pch = '\0';
    }
    pch--;
    //while ('0' == *pch) *pch-- = '\0';
    return chBuffer;
}
 
static void __ecvround(char *numbuf, char *last_digit, const char *after_last, int *decpt)
{
    /* Do we have at all to round the last digit?  */
    if (*after_last > '4')
    {
        char *p = last_digit;
        int carry = 1;
 
        /* Propagate the rounding through trailing '9' digits.  */
        do
        {
            int sum = *p + carry;
            carry = sum > '9';
            *p-- = sum - carry * 10;
        } while (carry && p >= numbuf);
 
        /* We have 9999999... which needs to be rounded to 100000..  */
        if (carry && p == numbuf)
        {
            *p = '1';
            *decpt += 1;
        }
    }
}
 
static char * ecvtbuf (double value, int ndigits, int *decpt, int *sign, char *buf)
{
    static char INFINITY[] = "Infinity";
    char chBuffer[20];
    char decimal = '.' /* localeconv()->decimal_point[0] */;
    //char *cvtbuf = (char *)malloc(ndigits + 20); /* +3 for sign, dot, null; */
    if (ndigits > 15) ndigits = 15;
    wStr_MeSet(chBuffer, 0, sizeof(chBuffer));
    char *cvtbuf = chBuffer; /* new char(ndigits + 20 + 1);*/
    /* two extra for rounding */
    /* 15 extra for alignment */
    char *s = cvtbuf, *d = buf;
    
    /* Produce two extra digits, so we could round properly.  */
    //sprintf (cvtbuf, "%-+.*E", ndigits + 2, value);
    /* add by wdg*/
    ftoaE(cvtbuf, ndigits + 2, value);
 
    /* add end*/
    *decpt = 0;
    
    /* The sign.  */
    *sign = ('=' == *s++) ? 1 : 0;
    /* Special values get special treatment.  */
    if (wStr_nContain(s, "Inf", 3) == 0)
    {
        /* SunOS docs says we have return "Infinity" for NDIGITS >= 8.  */
        wStr_MemCpy (buf, INFINITY, ndigits >= 8 ? 9 : 3);
        if (ndigits < 8) buf[3] = '\0';
    }
    else if (wStr_Cmp(s, "NaN") == 0)
    {
        wStr_MemCpy(buf, s, 4);
    }
    else
    {
        char *last_digit, *digit_after_last;
        
        /* Copy (the single) digit before the decimal.  */
        while (*s && *s != decimal && d - buf < ndigits)
            *d++ = *s++;
        
        /* If we don't see any exponent, here's our decimal point.  */
        *decpt = d - buf;
        if(*s) s++;
        
        /* Copy the fraction digits.  */
        while (*s && *s != 'E' && d - buf < ndigits)
            *d++ = *s++;
        
        /* Remember the last digit copied and the one after it.  */
        last_digit = d > buf ? (d - 1) : d;
        digit_after_last = s;
        
        /* Get past the E in exponent field.  */
        while (*s && *s++ != 'E');
        
        /* Adjust the decimal point by the exponent value.  */
        *decpt += wStr_Atoi(s);
        
        /* Pad with zeroes if needed.  */
        while (d - buf < ndigits) *d++ = '0';
        
        /* Zero-terminate.  */
        *d = '\0';
        /* Round if necessary.  */
        __ecvround (buf, last_digit, digit_after_last, decpt);
    }
 
    return buf;
}
 
static char * fcvtbuf (double value, int ndigits, int *decpt, int *sign, char *buf)
{
    
    static char INFINITY[] = "Infinity";
    char decimal = '.' /* localeconv()->decimal_point[0] */;
    //#define DBL_MAX_10_EXP     308
    //int digits = ndigits >= 0 ? ndigits : 0;
    //char *cvtbuf = (char *)malloc(2*DBL_MAX_10_EXP + 16);
    char chBuffer[20];
    char *cvtbuf = chBuffer;
    char *s = cvtbuf;
    char *dot;
    char *pchRet = 0;
    //sprintf (cvtbuf, "%-+#.*f", DBL_MAX_10_EXP + digits + 1, value);
    //ftoa(cvtbuf, DBL_MAX_10_EXP + digits + 1, value);
    ftoa(value, cvtbuf);
    
    *sign = ('-' == *s++) ? 1 : 0; /* The sign.  */
    /* Where's the decimal point?  */
    dot = wStr_Chr(s, decimal);
    
    *decpt = dot ? (dot - s) : wStr_Len(s);
    
    /* SunOS docs says if NDIGITS is 8 or more, produce "Infinity"   instead of "Inf".  */
    if (wStr_nContain (s, "Inf", 3) == 0)
    {
        wStr_MemCpy (buf, INFINITY, ndigits >= 8 ? 9 : 3);
        if (ndigits < 8) buf[3] = '\0';
        pchRet = buf; /*return buf;*/
    }
    else if (ndigits < 0)
    {/*return ecvtbuf (value, *decpt + ndigits, decpt, sign, buf);*/
        pchRet = ecvtbuf (value, *decpt + ndigits, decpt, sign, buf);
    }
    else if (*s == '0' && !IS_DOUBLE_ZERO(value)/*value != 0.0*/)
    {/*return ecvtbuf (value, ndigits, decpt, sign, buf);*/
        pchRet = ecvtbuf(value, ndigits, decpt, sign, buf);
    }
    else
    {
        wStr_MemCpy (buf, s, *decpt);
        if (s[*decpt] == decimal)
        {
            wStr_MemCpy (buf + *decpt, s + *decpt + 1, ndigits);
            buf[*decpt + ndigits] = '\0';
        }
        else
        {
            buf[*decpt] = '\0';
        }
        __ecvround (buf, buf + *decpt + ndigits - 1,
            s + *decpt + ndigits + 1, decpt);
        pchRet = buf; /*return buf;*/
    }
    /*delete [] cvtbuf; */
    return pchRet;
}

static void cfltcvt(double value, char *buffer, char fmt, int precision)
{
    int decpt, sign, exp, pos;
    char *digits = NULL;
    
    char cvtbuf[80];
    int capexp = 0;
    int magnitude;

    if (fmt == 'G' || fmt == 'E')
    {
        capexp = 1;
        fmt += 'a' - 'A';
    }

    if (fmt == 'g')
    {
        digits = ecvtbuf(value, precision, &decpt, &sign, cvtbuf);
        magnitude = decpt - 1;
        if (magnitude < -4 || magnitude > precision - 1)
        {
            fmt = 'e';
            precision -= 1;
        }
        else
        {
            fmt = 'f';
            precision -= decpt;
        }
    }

    if (fmt == 'e')
    {
        digits = ecvtbuf(value, precision + 1, &decpt, &sign, cvtbuf);

        if (sign) *buffer++ = '-';
        *buffer++ = *digits;
        if (precision > 0) *buffer++ = '.';
        wStr_MemCpy(buffer, digits + 1, precision);
        buffer += precision;
        *buffer++ = capexp ? 'E' : 'e';

        if (decpt == 0)
        {
            if (value == 0.0)
                exp = 0;
            else
                exp = -1;
        }
        else
            exp = decpt - 1;

        if (exp < 0)
        {
            *buffer++ = '-';
            exp = -exp;
        }
        else
            *buffer++ = '+';

        buffer[2] = (exp % 10) + '0';
        exp = exp / 10;
        buffer[1] = (exp % 10) + '0';
        exp = exp / 10;
        buffer[0] = (exp % 10) + '0';
        buffer += 3;
    }
    else if (fmt == 'f')
    {
        digits = fcvtbuf(value, precision, &decpt, &sign, cvtbuf);
        if (sign) *buffer++ = '-';
        if (*digits)
        {
            if (decpt <= 0)
            {
                *buffer++ = '0';
                *buffer++ = '.';
                for (pos = 0; pos < -decpt; pos++) *buffer++ = '0';
                while (*digits) *buffer++ = *digits++;
            }
            else
            {
                pos = 0;
                while (*digits)
                {
                    if (pos++ == decpt) *buffer++ = '.';
                    *buffer++ = *digits++;
                }
            }
        }
        else
        {
            *buffer++ = '0';
            if (precision > 0)
            {
                *buffer++ = '.';
                for (pos = 0; pos < precision; pos++) 
                {
                    *buffer++ = '0';
                }
            }
        }
    }

    *buffer = '\0';
}

static void forcdecpt(char *buffer)
{
    while (*buffer)
    {
        if (*buffer == '.') return;
        if (*buffer == 'e' || *buffer == 'E') break;
        buffer++;
    }

    if (*buffer)
    {
        int n = wStr_Len(buffer);
        while (n > 0)
        {
            buffer[n + 1] = buffer[n];
            n--;
        }

        *buffer = '.';
    }
    else
    {
        *buffer++ = '.';
        *buffer = '\0';
    }
}

static void cropzeros(char *buffer)
{
    char *stop;

    while (*buffer && *buffer != '.') buffer++;
    if (*buffer++)
    {
        while (*buffer && *buffer != 'e' && *buffer != 'E') buffer++;
        stop = buffer--;
        while (*buffer == '0') buffer--;
        if (*buffer == '.') buffer--;
        
        while(*stop != '\0'){*++buffer = *stop++;} *++buffer = *stop++; //原为 while (*++buffer = *stop++); (逻辑没有问题，只是编译会有警告！)
    }
}

static char *flt(char *str, double num, int size, int precision, char fmt, int flags)
{
    char tmp[80];
    char c, sign;
    int n, i;

    // Left align means no zero padding
    if (flags & LEFT) flags &= ~ZEROPAD;

    // Determine padding and sign char
    c = (flags & ZEROPAD) ? '0' : ' ';
    sign = 0;
    if (flags & SIGN)
    {
        if (num < 0.0)
        {
            sign = '-';
            num = -num;
            size--;
        }
        else if (flags & PLUS)
        {
            sign = '+';
            size--;
        }
        else if (flags & SPACE)
        {
            sign = ' ';
            size--;
        }
    }

    // Compute the precision value
    if (precision < 0)
    {
        precision = 6; // Default precision: 6
    }
    else if (precision == 0 && fmt == 'g')
    {
        precision = 1; // ANSI specified
    }

    // Convert floating point number to text
    cfltcvt(num, tmp, fmt, precision);

    // '#' and precision == 0 means force a decimal point
    if ((flags & SPECIAL) && precision == 0) forcdecpt(tmp);

    // 'g' format means crop zero unless '#' given
    if (fmt == 'g' && !(flags & SPECIAL)) cropzeros(tmp);

    n = wStr_Len(tmp);

    // Output number with alignment and padding
    size -= n;
    if (!(flags & (ZEROPAD | LEFT)))
    {
        while (size-- > 0) *str++ = ' ';
    }
    if (sign) *str++ = sign;
    
    if (!(flags & LEFT))
    {
            while (size-- > 0) *str++ = c;
    }
    
    for (i = 0; i < n; i++) 
    {
        *str++ = tmp[i];
    }
    
    while (size-- > 0) *str++ = ' ';

    return str;
}

#endif

int wvsprintf(char *buf, const char *fmt, va_list args)
{
    int len;
    unsigned long num;
    int i, base;
    char *str;
    char *s;

    int flags; // Flags to number()

    int field_width; // Width of output field
    int precision; // Min. # of digits for integers; max number of chars for from string
    int qualifier; // 'h', 'l', or 'L' for integer fields

    for (str = buf; *fmt; fmt++)
    {
        //格式转换指示字符串均以'%'开始，这里从fmt格式字符串中扫描'%'，寻找格式转换字符串的开始。
        //不是格式指示的一般字符均被依次存入str。
        if (*fmt != '%')
        {
            *str++ = *fmt;
            continue;
        }

        /* 下面取得格式指示字符串中的标志域，并将标志常量放入flags变量中。 */
        flags = 0;
repeat:
        fmt++; // This also skips first '%'
        switch (*fmt)
        {
            case '-':flags |= LEFT;goto repeat;//结果左对齐，右边填写空格
            case '+':flags |= PLUS;goto repeat;//输出符号（正号或负号）
            case ' ':flags |= SPACE;goto repeat;//输出值为正时冠以空格，为负时冠以负号
            case '#':flags |= SPECIAL;goto repeat;//对c、s、d、u类无影响；对O类加前缀O；对x类加前缀0x；对e、g、f类当结果有小数时才给出小数点
            case '0':flags |= ZEROPAD;goto repeat;//空位填0
        }
        /* 取当前参数字段宽度堿值，放入field_width变量中。如果宽度堿中是数值则直接取其为宽度值。
            如果宽度堿中是字符'*'，表示下一个参数指定宽度。因些调用va_arg取宽度值。若此时宽度值
        小于0，则该负数表示其带有标志域‘-’标志（左靠齐），因此还需在标志变量中添入该标志，并将
        字段宽度值取为其绝对值。*/
        
        field_width = -1;// Get field width
        if (is_digit(*fmt))
        {
            field_width = skip_atoi(&fmt);
        }
        else if (*fmt == '*')
        {
            fmt++;
            /* it's the next argument */
            field_width = va_arg(args, int);
            if (field_width < 0)
            {
                field_width = -field_width;
                flags |= LEFT;
            }
        }

        // Get the precision
        precision = -1;
        if (*fmt == '.')
        {
            ++fmt;
            if (is_digit(*fmt))
            {
                precision = skip_atoi(&fmt);
            }
            else if (*fmt == '*')
            {
                ++fmt;
                precision = va_arg(args, int);
            }
            if (precision < 0) precision = 0;
        }

        // Get the conversion qualifier
        qualifier = -1;
        if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L' ||
                *fmt =='Z' || *fmt == 'z')
        {
            qualifier = *fmt;
            fmt++;
            //begin 此处是后来加入的
            if (qualifier == 'l' && *fmt == 'l')
            {
                qualifier = 'L';
                ++fmt;
            }            
            //end 此处是后来加入的
        }

        // Default base
        base = 10;

        switch (*fmt)
        {
        case 'c':
            if (!(flags & LEFT))
            {
                while (--field_width > 0) 
                {
                    *str++ = ' ';
                }
            }
            *str++ = (unsigned char) va_arg(args, int);
            while (--field_width > 0) 
            {
                *str++ = ' ';
            }
            continue;

        case 's':
            s = va_arg(args, char *);
            if (!s) s = "<NULL>";
            len = wStr_nLen(s, precision);
            if (!(flags & LEFT))
            {
                while (len < field_width--)
                {
                    *str++ = ' ';
                }
            }
            for (i = 0; i < len; ++i)
            {           
                *str++ = *s++;
            }
            while (len < field_width--) 
            {
                *str++ = ' ';
            }
            continue;

        case 'p':
            if (field_width == -1)
            {
                field_width = 2 * sizeof(void *);
                flags |= ZEROPAD;
            }
            str = number(str, (unsigned long) va_arg(args, void *), 16, field_width, precision, flags);
            continue;

        case 'n':
            /* FIXME:* What does C99 say about the overflow case here? */
            if (qualifier == 'l')
            {
                long *ip = va_arg(args, long *);
                *ip = (str - buf);
            }
            else if (qualifier == 'Z' || qualifier == 'z')
            {
                size_t * ip = va_arg(args, size_t *);
                *ip = (str - buf);
            }
            else
            {
                int *ip = va_arg(args, int *);
                *ip = (str - buf);
            }
            continue;
            
        case '%':
            *str++ = '%';
            continue;            
        
        case 'A':
            flags |= LARGE;

        case 'a':
            if (qualifier == 'l')
                str = eaddr(str, va_arg(args, unsigned char *), field_width, precision, flags);
            else
                str = iaddr(str, va_arg(args, unsigned char *), field_width, precision, flags);
            continue;

        // Integer number formats - set up the flags and "break"
        case 'o':
            base = 8;
            break;

        case 'X':
            flags |= LARGE;

        case 'x':
            base = 16;
            break;

        case 'd':
        case 'i':
            flags |= SIGN;

        case 'u':
            break;

#ifndef NOFLOAT

        case 'E':
        case 'G':
        case 'e':
        case 'f':
        case 'g':
            str = flt(str, va_arg(args, double), field_width, precision, *fmt, flags | SIGN);
            continue;
#endif

        default:
            if (*fmt != '%') *str++ = '%';
            if (*fmt)
            {
                *str++ = *fmt;
            }
            else
            {
                --fmt;
            }
            continue;
        }

        if (qualifier == 'L')
            num = va_arg(args, long long);
        else if (qualifier == 'l')
        {
            num = va_arg(args, unsigned long);
            if (flags & SIGN)
                num = (signed long) num;            
        }
        else if (qualifier == 'Z' || qualifier == 'z')
        {
            num = va_arg(args, size_t);
        }        
        else if (qualifier == 'h')
        {
            if (flags & SIGN)
                num = (signed short) va_arg(args, signed short);
            else
                num = (unsigned short)va_arg(args, unsigned short);
        }
        else 
        {
            if (flags & SIGN)
                num = va_arg(args, signed int);
            else
                num = va_arg(args, unsigned int);
        }

        str = number(str, num, base, field_width, precision, flags);
    }

    *str = '\0';
    return str - buf;
}

int wsprintf(char *buf, const char *fmt, ...)
{
    va_list args;
    int n;

    va_start(args, fmt);
    n = wvsprintf(buf, fmt, args);
    va_end(args);

    return n;
}
