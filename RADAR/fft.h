#ifndef __FFT_H_
#define __FFT_H_


#define FFT_N 256      //512
#define log2N 8   //log2N=9
#define FS 100
#define PI 3.141592
typedef struct
{
 float real;
 float img;
}COMPLEX;
typedef struct
{
 float fre;
 float amp;
}FA_OUT;

extern FA_OUT out_x[FFT_N/2]; //

float FFT(float I_data[],float Q_data[]);

#endif
