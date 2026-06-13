/* 
 * File:   my_defines.h
 * Author: hpatel
 *
 * Created on February 27, 2026, 9:54 AM
 */

#include <stdint.h>
#define U1MODE_ADDR   0x0220
#define U1STA_ADDR    0x0222
#define U1TXREG_ADDR  0x0224
#define U1RXREG_ADDR  0x0226
#define U1BRG_ADDR    0x0228

#define IEC0_ADDR     0x0094
#define IFS0_ADDR     0x0084

#define TRISD_ADDR    0x02D2
#define PORTD_ADDR    0x02D4
#define LATD_ADDR     0x02D6

#define DMA0CON_ADDR  0x0380
#define DMA0REQ_ADDR  0x0382
#define DMA0STA_ADDR  0x0384
#define DMA0STB_ADDR  0x0386
#define DMA0PAD_ADDR  0x0388
#define DMA0CNT_ADDR  0x038A

#define DMA1CON_ADDR  0x038C
#define DMA1REQ_ADDR  0x038E
#define DMA1STA_ADDR  0x0390
#define DMA1STB_ADDR  0x0392
#define DMA1PAD_ADDR  0x0394
#define DMA1CNT_ADDR  0x0396


typedef union
{
    struct
    {
        uint16_t TRISD0  : 1;
        uint16_t TRISD1  : 1;
        uint16_t TRISD2  : 1;
        uint16_t TRISD3  : 1;
        uint16_t TRISD4  : 1;
        uint16_t TRISD5  : 1;
        uint16_t TRISD6  : 1;
        uint16_t TRISD7  : 1;
        uint16_t TRISD8  : 1;
        uint16_t TRISD9  : 1;
        uint16_t TRISD10 : 1;
        uint16_t TRISD11 : 1;
        uint16_t TRISD12 : 1;
        uint16_t TRISD13 : 1;
        uint16_t TRISD14 : 1;
        uint16_t TRISD15 : 1;
    }bits;
    uint16_t value;
}mTRISD;

typedef union
{
    struct
    {
        uint16_t RD0  : 1;
        uint16_t RD1  : 1;
        uint16_t RD2  : 1;
        uint16_t RD3  : 1;
        uint16_t RD4  : 1;
        uint16_t RD5  : 1;
        uint16_t RD6  : 1;
        uint16_t RD7  : 1;
        uint16_t RD8  : 1;
        uint16_t RD9  : 1;
        uint16_t RD10 : 1;
        uint16_t RD11 : 1;
        uint16_t RD12 : 1;
        uint16_t RD13 : 1;
        uint16_t RD14 : 1;
        uint16_t RD15 : 1;
    }bits;
    uint16_t value;
}mPORTD;

typedef union
{
    struct
    {
        uint16_t LATD0  : 1;
        uint16_t LATD1  : 1;
        uint16_t LATD2  : 1;
        uint16_t LATD3  : 1;
        uint16_t LATD4  : 1;
        uint16_t LATD5  : 1;
        uint16_t LATD6  : 1;
        uint16_t LATD7  : 1;
        uint16_t LATD8  : 1;
        uint16_t LATD9  : 1;
        uint16_t LATD10 : 1;
        uint16_t LATD11 : 1;
        uint16_t LATD12 : 1;
        uint16_t LATD13 : 1;
        uint16_t LATD14 : 1;
        uint16_t LATD15 : 1;
    }bits;
    uint16_t value;
}mLATD;

typedef union
{
    struct
    {
        uint16_t STSEL     : 1;
        uint16_t PDSEL     : 2;
        uint16_t BRGH      : 1;
        uint16_t UR1INV    : 1;
        uint16_t ABAUD     : 1;
        uint16_t LPBACK    : 1;
        uint16_t WAKE      : 1;
        uint16_t UEN       : 2;
        uint16_t RESERVED1 : 1;
        uint16_t RTSMD     : 1;
        uint16_t IREN      : 1;
        uint16_t USID      : 1;
        uint16_t RESERVED2 : 1;
        uint16_t UARTEN    : 1;
    }bits;
    uint16_t value;
}mU1MODE;

typedef union
{
    struct
    {
        uint16_t URXDA     : 1;
        uint16_t OERR      : 1;
        uint16_t FERR      : 1;
        uint16_t PERR      : 1;
        uint16_t RIDLE     : 1;
        uint16_t ADDEN     : 1;
        uint16_t URXISEL   : 2;
        uint16_t TRMT      : 1;
        uint16_t UTXBF     : 1;
        uint16_t UTXEN     : 1;
        uint16_t UTXBRK    : 1;
        uint16_t RESERVED1 : 1;
        uint16_t UTXISEL0  : 1;
        uint16_t UTXINV    : 1;
        uint16_t UTXISEL1  : 1;
    }bits;
    uint16_t value;
}mU1STA;

typedef union
{
    uint16_t value;
    
}mU1BRG;

typedef union
{
    uint8_t value;
    
}mU1TXREG;

typedef union
{
    uint8_t value;
    
}mU1RXREG;

typedef union
{
    struct
    {
        uint16_t INT0IE     : 1;
        uint16_t IC1IE      : 1;
        uint16_t OC1IE      : 1;
        uint16_t T1IE       : 1;
        uint16_t DMA0IE     : 1;
        uint16_t IC2IE      : 1;
        uint16_t OC2IE      : 1;
        uint16_t T2IE       : 1;
        uint16_t T3IE       : 1;
        uint16_t SPI1EIE    : 1;
        uint16_t SPI1IE     : 1;
        uint16_t U1RXIE     : 1;
        uint16_t U1TXIE     : 1;
        uint16_t AD1IE      : 1;
        uint16_t DMA1IE     : 1;
        uint16_t RESERVED   : 1;
    }bits;
    uint16_t value;
}mIEC0;

typedef union
{
    struct
    {
        uint16_t INT0IF     : 1;
        uint16_t IC1IF      : 1;
        uint16_t OC1IF      : 1;
        uint16_t T1IF       : 1;
        uint16_t DMA0IF     : 1;
        uint16_t IC2IF      : 1;
        uint16_t OC2IF      : 1;
        uint16_t T2IF       : 1;
        uint16_t T3IF       : 1;
        uint16_t SPI1EIF    : 1;
        uint16_t SPI1IF     : 1;
        uint16_t U1RXIF     : 1;
        uint16_t U1TXIF     : 1;
        uint16_t AD1IF      : 1;
        uint16_t DMA1IF     : 1;
        uint16_t RESERVED   : 1;
    }bits;
    uint16_t value;
}mIFS0;

typedef union {
    struct 
    {
        uint16_t MODE       : 2;
        uint16_t RESERVED1  : 2;
        uint16_t AMODE      : 2;
        uint16_t RESERVED2  : 5;
        uint16_t NULLW      : 1;
        uint16_t HALF       : 1;
        uint16_t DIR        : 1;
        uint16_t SIZE       : 1;
        uint16_t CHEN       : 1;    
    }bits;
    uint16_t value;  
}mDMA0CON;

typedef union {
    struct 
    {
        uint16_t IRQSEL     : 7;
        uint16_t RESERVED1  : 8;
        uint16_t FORCE      : 1;   
    }bits;
    uint16_t value;  
}mDMA0REQ;

typedef union {
    struct 
    {
        uint16_t STA  : 16;
    }bits;
    uint16_t value;  
}mDMA0STA;

typedef union {
    struct 
    {
        uint16_t STB  : 16;
    }bits;
    uint16_t value;  
}mDMA0STB;

typedef union {
    struct 
    {
        uint16_t PAD  : 16;
    }bits;
    uint16_t value;  
}mDMA0PAD;

typedef union {
    struct 
    {
        uint16_t CNT       : 10;
        uint16_t RESERVED1 : 6;
    }bits;
    uint16_t value;  
}mDMA0CNT;

typedef union {
    struct 
    {
        uint16_t MODE       : 2;
        uint16_t RESERVED1  : 2;
        uint16_t AMODE      : 2;
        uint16_t RESERVED2  : 5;
        uint16_t NULLW      : 1;
        uint16_t HALF       : 1;
        uint16_t DIR        : 1;
        uint16_t SIZE       : 1;
        uint16_t CHEN       : 1;    
    }bits;
    uint16_t value;  
}mDMA1CON;

typedef union {
    struct 
    {
        uint16_t IRQSEL     : 7;
        uint16_t RESERVED1  : 8;
        uint16_t FORCE      : 1;   
    }bits;
    uint16_t value;  
}mDMA1REQ;

typedef union {
    struct 
    {
        uint16_t STA  : 16;
    }bits;
    uint16_t value;  
}mDMA1STA;

typedef union {
    struct 
    {
        uint16_t STB  : 16;
    }bits;
    uint16_t value;  
}mDMA1STB;

typedef union {
    struct 
    {
        uint16_t PAD  : 16;
    }bits;
    uint16_t value;  
}mDMA1PAD;

typedef union {
    struct 
    {
        uint16_t CNT       : 10;
        uint16_t RESERVED1 : 6;
    }bits;
    uint16_t value;  
}mDMA1CNT;

extern volatile mTRISD * const myTRISD;
extern volatile mPORTD * const myPORTD;
extern volatile mLATD * const myLATD;

extern volatile mU1MODE * const myU1MODE;
extern volatile mU1STA * const myU1STA;
extern volatile mU1BRG * const myU1BRG;
extern volatile mU1TXREG * const myU1TXREG;
extern volatile mU1RXREG * const myU1RXREG;
extern volatile mIEC0 * const myIEC0;
extern volatile mIFS0 * const myIFS0;

extern volatile mDMA0CON * const myDMA0CON;
extern volatile mDMA0REQ * const myDMA0REQ;
extern volatile mDMA0STA * const myDMA0STA;
extern volatile mDMA0STB * const myDMA0STB;
extern volatile mDMA0PAD * const myDMA0PAD;
extern volatile mDMA0CNT * const myDMA0CNT;

extern volatile mDMA1CON * const myDMA1CON;
extern volatile mDMA1REQ * const myDMA1REQ;
extern volatile mDMA1STA * const myDMA1STA;
extern volatile mDMA1STB * const myDMA1STB;
extern volatile mDMA1PAD * const myDMA1PAD;
extern volatile mDMA1CNT * const myDMA1CNT;