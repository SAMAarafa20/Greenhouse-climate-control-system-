#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SetBit(Reg,BitNo)     (Reg |= (1 << BitNo))
#define ClearBit(Reg,BitNo)   (Reg &= ~(1 << BitNo))
#define ToggleBit(Reg,BitNo)  (Reg ^= (1 << BitNo))
#define ReadBit(Reg,BitNo)    ((Reg >> BitNo) & 0x01)

#endif /* BIT_MATH_H_ */