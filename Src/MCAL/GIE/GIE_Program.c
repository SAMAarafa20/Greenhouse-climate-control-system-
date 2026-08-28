#include "GIE_Interface.h"

void GIE_Enable(void)
{
    SetBit(SREG_REG, GIE_BIT);
}

void GIE_Disable(void)
{
    ClearBit(SREG_REG, GIE_BIT);
}