#ifndef __WY_TYPE_H
#define __WY_TYPE_H

#define _Conn2(x,y) x##y
#define Conn2(x,y) _Conn2(x,y)

#define _Conn3(x,y,z) x##y##z
#define Conn3(x,y,z) _Conn3(x,y,z)

#define _ToString(x) #x 
#define ToString(x) _ToString(x) 

#ifndef __at
#define __at(_addr) __attribute__ ((at(_addr)))
#endif

#ifndef __section
#define __section(_name) __attribute__ ((section(_name)))
#endif

#define     w_noinit     __attribute__((zero_init))         //不初使化变量

/* This type MUST be 8-bit */
typedef 			 	unsigned  	char        	wu8;        /*  8-bit unsigned integer */
typedef  			  	signed   	char        	ws8;        /*  8-bit   signed integer */
/* These types MUST be 16-bit */
typedef  			 	unsigned  	short  int      wu16;       /* 16-bit unsigned integer */
typedef  			  	signed  	short  int      ws16;       /* 16-bit   signed integer */
/* These types MUST be 16-bit or 32-bit */
typedef 			 	unsigned  	int         	wuint;      /* 32-bit unsigned integer */
typedef 			   	signed  	int         	wsint;      /* 32-bit   signed integer */
/* These types MUST be 32-bit */
typedef 			 	unsigned  	long    		wu32;       /* 64-bit unsigned integer */
typedef  			  	signed  	long    		ws32;       /* 64-bit   signed integer */
/* This type MUST be 64-bit */
typedef					unsigned  	long  long  	wu64;       /* 64-bit unsigned integer */
typedef  			  	signed  	long  long  	ws64;       /* 64-bit   signed integer */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* This type MUST be 8-bit */
typedef 	const	 	unsigned  	char        	wcu8;       /*  8-bit unsigned integer */
typedef  	const	  	signed  	char        	wcs8;       /*  8-bit   signed integer */
/* These types MUST be 16-bit */
typedef  	const	 	unsigned  	short  int      wcu16;      /* 16-bit unsigned integer */
typedef  	const	  	signed  	short  int      wcs16;      /* 16-bit   signed integer */
/* These types MUST be 16-bit or 32-bit */
typedef 	const	 	unsigned  	int         	wcuint;     /* 32-bit unsigned integer */
typedef 	const	   	signed  	int         	wcsint;     /* 32-bit   signed integer */
/* These types MUST be 32-bit */
typedef 	const	 	unsigned  	long    		wcu32;      /* 64-bit unsigned integer */
typedef  	const	  	signed  	long    		wcs32;      /* 64-bit   signed integer */
/* This type MUST be 64-bit */
typedef		const		unsigned  	long  long  	wcu64;      /* 64-bit unsigned integer */
typedef  	const	  	signed  	long  long  	wcs64;      /* 64-bit   signed integer */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* This type MUST be 8-bit */
typedef 	volatile 	unsigned  	char        	wvu8;        /*  8-bit unsigned integer */
typedef  	volatile  	signed	    char        	wvs8;        /*  8-bit   signed integer */
/* These types MUST be 16-bit */
typedef  	volatile	unsigned  	short  int      wvu16;       /* 16-bit unsigned integer */
typedef  	volatile	signed  	short  int      wvs16;       /* 16-bit   signed integer */
/* These types MUST be 16-bit or 32-bit */
typedef 	volatile 	unsigned  	int         	wvuint;      /* 32-bit unsigned integer */
typedef 	volatile   	signed  	int         	wvsint;      /* 32-bit   signed integer */
/* These types MUST be 32-bit */
typedef 	volatile 	unsigned  	long    		wvu32;       /* 64-bit unsigned integer */
typedef  	volatile  	signed  	long    		wvs32;       /* 64-bit   signed integer */
/* This type MUST be 64-bit */
typedef		volatile	unsigned  	long  long  	wvu64;       /* 64-bit unsigned integer */
typedef  	volatile  	signed  	long  long  	wvs64;       /* 64-bit   signed integer */

typedef     union {
    struct 
    {
        unsigned b0:1;
        unsigned b1:1;
        unsigned b2:1;
        unsigned b3:1;
        unsigned b4:1;
        unsigned b5:1;
        unsigned b6:1;
        unsigned b7:1;
        unsigned b8:1;
        unsigned b9:1;
        unsigned b10:1;
        unsigned b11:1;
        unsigned b12:1;
        unsigned b13:1;
        unsigned b14:1;
        unsigned b15:1;          
    }Bit;
    struct
    {
        wu8     c0;
        wu8     c1;
    }uchar;
    wu16        uint;
} wUnion_uInt;//uint联合体

typedef     union {
    struct 
    {
        unsigned b0:1;
        unsigned b1:1;
        unsigned b2:1;
        unsigned b3:1;
        unsigned b4:1;
        unsigned b5:1;
        unsigned b6:1;
        unsigned b7:1;         
    }Bit;
    wu8         uchar;
} wUnion_uChar;//uint联合体
  
#endif



