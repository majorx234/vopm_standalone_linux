#ifndef _GLOBAL_STUFF_HPP_
#define _GLOBAL_STUFF_HPP_

#include <stdio.h>
#include <math.h>

#define N_CH 8

#define PRECISION_BITS (10)
#define PRECISION (1<<PRECISION_BITS)
#define SIZEALPHATBL_BITS (10)
#define SIZEALPHATBL (1<<SIZEALPHATBL_BITS)

#define SIZESINTBL_BITS (10)
#define SIZESINTBL (1<<SIZESINTBL_BITS)
#define MAXSINVAL (1<<(SIZESINTBL_BITS+2))

#define PI 3.1415926535897932
#define MAXELVAL_BITS (30)
#define MAXELVAL (1<<MAXELVAL_BITS)
#define MAXARTIME_BITS (20)
#define SIZEARTBL (100)
#define MAXARTIME (SIZEARTBL*(1<<MAXARTIME_BITS))
#define ALPHAZERO (SIZEALPHATBL*3)

struct GlobalStuff{
  int STEPTBL[11*12*64];
  int STEPTBL3[11*12*64];

  unsigned short ALPHATBL[ALPHAZERO+SIZEALPHATBL+1];
  short SINTBL[SIZESINTBL];

  int STEPTBL_O2[12*64];
  int D1LTBL[16];
  int DT1TBL[128+4];
  int DT1TBL_org[128+4];

  struct XR_ELE {
    int val_and;
    int add;
  };

  XR_ELE XRTBL[64+32];

  int DT2TBL[4];
  unsigned short NOISEALPHATBL[ALPHAZERO+SIZEALPHATBL+1];
};

#endif // _GLOBAL_STUFF_HPP_
