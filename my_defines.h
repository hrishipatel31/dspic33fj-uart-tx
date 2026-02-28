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
#define U1RXREG_ADDR  0x0224
#define U1BRG_ADDR    0x0228

#define IEC0_ADDR     0x0094
#define IFS0_ADDR     0x0084

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
        uint16_t UR1DA     : 1;
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

volatile mU1MODE * const myU1MODE = (volatile mU1MODE *) U1MODE_ADDR;
volatile mU1STA * const myU1STA = (volatile mU1STA *) U1STA_ADDR;
volatile mU1BRG * const myU1BRG = (volatile mU1BRG *) U1BRG_ADDR;
volatile mU1TXREG * const myU1TXREG = (volatile mU1TXREG *) U1TXREG_ADDR;
volatile mIEC0 * const myIEC0 = (volatile mIEC0 *) IEC0_ADDR;
volatile mIFS0 * const myIFS0 = (volatile mIFS0 *) IFS0_ADDR;
