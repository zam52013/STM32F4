#ifndef __CZT_H_
#define __CZT_H_
#include "fft.h"

#ifndef TWO_PI
#define TWO_PI 3.141592*2
#endif

void chirpzfft(COMPLEX *out, COMPLEX *in, int size,float fre1,float fre2 ) ;

#endif

