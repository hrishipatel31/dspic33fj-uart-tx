#include "my_defines.h"

volatile mPORTD * const myPORTD = (volatile mPORTD *) PORTD_ADDR;
volatile mTRISD * const myTRISD = (volatile mTRISD *) TRISD_ADDR;
volatile mLATD * const myLATD   = (volatile mLATD *) LATD_ADDR;

volatile mU1MODE * const myU1MODE = (volatile mU1MODE *) U1MODE_ADDR;
volatile mU1STA * const myU1STA = (volatile mU1STA *) U1STA_ADDR;
volatile mU1BRG * const myU1BRG = (volatile mU1BRG *) U1BRG_ADDR;
volatile mU1TXREG * const myU1TXREG = (volatile mU1TXREG *) U1TXREG_ADDR;
volatile mU1RXREG * const myU1RXREG = (volatile mU1RXREG *) U1RXREG_ADDR;
volatile mIEC0 * const myIEC0 = (volatile mIEC0 *) IEC0_ADDR;
volatile mIFS0 * const myIFS0 = (volatile mIFS0 *) IFS0_ADDR;

volatile mDMA0CON * const myDMA0CON = (volatile mDMA0CON *) DMA0CON_ADDR;
volatile mDMA0REQ * const myDMA0REQ = (volatile mDMA0REQ *) DMA0REQ_ADDR;
volatile mDMA0STA * const myDMA0STA = (volatile mDMA0STA *) DMA0STA_ADDR;
volatile mDMA0STB * const myDMA0STB = (volatile mDMA0STB *) DMA0STB_ADDR;
volatile mDMA0PAD * const myDMA0PAD = (volatile mDMA0PAD *) DMA0PAD_ADDR;
volatile mDMA0CNT * const myDMA0CNT = (volatile mDMA0CNT *) DMA0CNT_ADDR;

volatile mDMA1CON * const myDMA1CON = (volatile mDMA1CON *) DMA1CON_ADDR;
volatile mDMA1REQ * const myDMA1REQ = (volatile mDMA1REQ *) DMA1REQ_ADDR;
volatile mDMA1STA * const myDMA1STA = (volatile mDMA1STA *) DMA1STA_ADDR;
volatile mDMA1STB * const myDMA1STB = (volatile mDMA1STB *) DMA1STB_ADDR;
volatile mDMA1PAD * const myDMA1PAD = (volatile mDMA1PAD *) DMA1PAD_ADDR;
volatile mDMA1CNT * const myDMA1CNT = (volatile mDMA1CNT *) DMA1CNT_ADDR;
