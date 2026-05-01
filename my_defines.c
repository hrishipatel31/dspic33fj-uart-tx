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
