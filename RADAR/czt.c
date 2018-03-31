//Using gauss multiplication a single multiplication can be ommitted, however the performance increase is hardware dependent.
#include "fft.h"
#include "czt.h"
#include "FastMath.h"
#include <math.h>
COMPLEX fcreciproc(COMPLEX a) 
{
    COMPLEX ainv;
    float normsq = a.real*a.real + a.img * a.img;
    ainv.real = a.real / normsq;
    ainv.img = -a.img / normsq;
    return ainv;
}
//This methods computes the ifft of in and stores it into out. If size is a power of 2 it will directly call fft2, elsewise it will compute the fft using chirpzfft.
void ifft(COMPLEX *out, COMPLEX *in, int size) 
{  // Perform out = FFT(in)
    COMPLEX in2 [FFT_N1*2];
    
    //store the conjugate in in2
    for(int i = 0; i < size; ++i) {
        in2[i].real = in[i].real;
        in2[i].img = -in[i].img;
    }
    fft2(out, in2, size, log2N1+1);
    
    //back conjugate the result and multiply it with 1./size
    for(int i = 0; i < size; ++i) {
        out[i].real = 1./size * out[i].real;
        out[i].img = - 1./size * out[i].img;
    }
}
 COMPLEX chirp_w [FFT_N1];
 void chirpzfft(COMPLEX * out, COMPLEX *in, int size,float fre1,float fre2 ) 
{
    int npow2 =size*2;
    float exponent;
    COMPLEX val;  

    COMPLEX xp [FFT_N1*2];	
    COMPLEX recipchirp_h[FFT_N1*2]; //holds reciprocal of chirpz	
    //COMPLEX arr1 [FFT_N*2];
    //COMPLEX arr2 [FFT_N*2];	
	
    for(int i =0; i < size; i++) 
		{
		exponent = ((float)i*i)/2.0;
        val.real = FastCos(TWO_PI*(fre2-fre1)/(size*FS*1.0) * exponent);
        val.img = -FastSin(TWO_PI*(fre2-fre1)/(size*FS*1.0) * exponent);
        chirp_w[i] = val;
		exponent = -i;
        val.real = FastCos(TWO_PI*fre1/FS * exponent);
        val.img = FastSin(TWO_PI*fre1/FS * exponent);
        xp[i] = val;		
    }
    
    for(int i = 0; i < size; i++) 
		{
		 xp[i] = mul(xp[i], chirp_w[i]);
		 xp[i] = mul(xp[i], in[i]);
    	}
    for(int i = size; i < npow2; i++) 
		{
		  xp[i].real = 0; 
		  xp[i].img = 0;
	    } //make sure xp is zero padded after size
      
    for(int i = 0; i <size; ++i) 
		{
		  exponent = -i*i/2.0;
          val.real = FastCos(TWO_PI*(fre2-fre1)/(size*FS) * exponent);
          val.img = -FastSin(TWO_PI*(fre2-fre1)/(size*FS) * exponent);
          recipchirp_h[i]= val;		
    	}
    for(int i = size; i < npow2; ++i) 
		{
		  exponent = -(npow2-i)*(npow2-i)/2.0;
          val.real = FastCos(TWO_PI*(fre2-fre1)/(size*FS) * exponent);
          val.img = -FastSin(TWO_PI*(fre2-fre1)/(size*FS) * exponent);		
		  recipchirp_h[i]=val;
	    } //make sure the rest is zero padded
    

    
    //init_twiddles(npow2);
    
    fft2(xp, xp, npow2, log2N1+1);
    fft2(recipchirp_h, recipchirp_h, npow2, log2N1+1);
    
    for(int i = 0; i < npow2; ++i) xp[i] = mul(xp[i],recipchirp_h[i]); //make arr1 the element-wise product.
    ifft(recipchirp_h,xp,npow2); //store ifft(fft(xp)*fft(recichirp)) into arr2
    
    for(int i = 0; i < size; ++i) out[i] = mul(chirp_w[i], recipchirp_h[i]);
}

