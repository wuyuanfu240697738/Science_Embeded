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

#define     ZEROPAD     1       //��λ��0
#define     SIGN        2
#define     PLUS        4       //������ţ����Ż򸺺ţ�
#define     SPACE       8       //���ֵΪ��ʱ���Կո�Ϊ��ʱ���Ը���
#define     LEFT        16      //�������룬�ұ���д�ո�
#define     SPECIAL     32      //��c��s��d��u����Ӱ�죻��O���ǰ׺O����x���ǰ׺0x����e��g��f�൱�����С��ʱ�Ÿ���С����
#define     LARGE       64

#define is_digit(c) ((c) >= '0' && (c) <= '9')
/////////////////////////////////////////////////////////////////////////////

//�ú������ַ����ִ�ת�������� ���������ִ�ָ���ָ�룬�����ǽ����ֵ������ָ�뽫ǰ��
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
������ת��Ϊָ�����Ƶ��ַ�����
num-����  base-����  size-�ַ�������  precision-���ֳ���  type-����ѡ��
str-�ַ���ָ��
*/
static char *number(char *str, long num, int base, int size, int precision, int type)
{
    char c, sign, tmp[66];
    const char *dig;
    int i;
    
    //�������typeָ����Сд��ĸ,����С����ĸ����
    dig = (type & LARGE) ? upper_digits : lower_digits;
    //�������ָ��Ҫ������������������е������־
    if (type & LEFT) type &= ~ZEROPAD;
    //������ƻ���С��2�����36�����˳�����Ҳ��������ֻ�ܴ��������2-32֮�������
    if (base < 2 || base > 36) return 0;
    //�������ָ��Ҫ���㣬�����ַ�����c=��0��,����c���ڿո��ַ���
    c = (type & ZEROPAD) ? '0' : ' ';
    //�������ָ���Ǵ�������������ֵnumС��0�����÷��ű���sign=���ţ���numȡ����ֵ��
    //�����������ָ���ǼӺţ�����sign=�Ӻţ����������ʹ��ո��־��sign=�ո񣬷�����0��
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
    //������ָ��������ת���������ʮ�����ƿ���ټ���2λ������0x��,
    //���ڰ˽��ƿ�ȼ�1�����ڰ˽���ת�����ǰ��һ���㣡��
    if (type & SPECIAL)
    {
        if (base == 16)
            size -= 2;
        else if (base == 8)
            size--;
    }
    //�����ֵnumΪ0,����ʱ�ַ���='0'��������ݸ����Ļ�������ֵnumת�����ַ���ʽ��
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
    //����ֵ�ַ��������ھ���ֵ���򾫶�ֵ��չΪ���ָ���ֵ��
    //���ֵsize��ȥ���ڴ����ֵ�ַ��ĸ�����
    if (i > precision) precision = i;
    size -= precision;
    //������������ʼ�γ�����Ҫ��ת�����������ʱ�����ַ���str�С�
    //��������û�����㣨ZEROPAD�������־������str������
    //���ʣ����ֵָ���Ŀո��������������λ���������š�    
    if (!(type & (ZEROPAD | LEFT)))
    {
        while (size-- > 0) {*str++ = ' ';}
    }
    if (sign) {*str++ = sign;}
    
    //������ָ��������ת���������8����ת�����ͷһλ����һ��'0'��������ʮ���������š�0x��.
    if (type & SPECIAL)
    {
        if (base == 8)
        {
            *str++ = '0';
        }
        else if (base == 16)
        {
            *str++ = '0';
            *str++ = dig[33];//ע��˴�
        }
    }
    //��������û���������־������ʣ�����д��C�ַ���'0'��ո�   
    if (!(type & LEFT))
    {
        while (size-- > 0) *str++ = c;
    }
        //��ʱi������ֵnum�����ָ����������ָ���С�ھ���ֵ����str�з��루����ֵ-i������0����
    while (i < precision--) 
    {
        *str++ = '0';
    }
    //��ת��ֵ���õ������ַ�����str�С���i����
    while (i-- > 0)
    {
        *str++ = tmp[i];
    }
    //�����ֵ�����㣬���ʾ���ͱ�־���������־������ʣ�����з���ո�
    while (size-- > 0)
    {
        *str++ = ' ';
    }

    return str;//����ת���õ��ַ���
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
        
        while(*stop != '\0'){*++buffer = *stop++;} *++buffer = *stop++; //ԭΪ while (*++buffer = *stop++); (�߼�û�����⣬ֻ�Ǳ�����о��棡)
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
        //��ʽת��ָʾ�ַ�������'%'��ʼ�������fmt��ʽ�ַ�����ɨ��'%'��Ѱ�Ҹ�ʽת���ַ����Ŀ�ʼ��
        //���Ǹ�ʽָʾ��һ���ַ��������δ���str��
        if (*fmt != '%')
        {
            *str++ = *fmt;
            continue;
        }

        /* ����ȡ�ø�ʽָʾ�ַ����еı�־�򣬲�����־��������flags�����С� */
        flags = 0;
repeat:
        fmt++; // This also skips first '%'
        switch (*fmt)
        {
            case '-':flags |= LEFT;goto repeat;//�������룬�ұ���д�ո�
            case '+':flags |= PLUS;goto repeat;//������ţ����Ż򸺺ţ�
            case ' ':flags |= SPACE;goto repeat;//���ֵΪ��ʱ���Կո�Ϊ��ʱ���Ը���
            case '#':flags |= SPECIAL;goto repeat;//��c��s��d��u����Ӱ�죻��O���ǰ׺O����x���ǰ׺0x����e��g��f�൱�����С��ʱ�Ÿ���С����
            case '0':flags |= ZEROPAD;goto repeat;//��λ��0
        }
        /* ȡ��ǰ�����ֶο�ȉAֵ������field_width�����С������ȉA������ֵ��ֱ��ȡ��Ϊ���ֵ��
            �����ȉA�����ַ�'*'����ʾ��һ������ָ����ȡ���Щ����va_argȡ���ֵ������ʱ���ֵ
        С��0����ø�����ʾ����б�־��-����־�����룩����˻����ڱ�־����������ñ�־������
        �ֶο��ֵȡΪ�����ֵ��*/
        
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
            //begin �˴��Ǻ��������
            if (qualifier == 'l' && *fmt == 'l')
            {
                qualifier = 'L';
                ++fmt;
            }            
            //end �˴��Ǻ��������
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
