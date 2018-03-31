#ifndef __FFT_H_
#define __FFT_H_


#define FFT_N 1024      //512
#define FFT_N1 256      //512

#define log2N 10   //log2N=9
#define log2N1 8   //log2N=9

#define FS (21000000/33)
#ifndef PI
#define PI 3.141592
#endif
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

extern FA_OUT IQ_out_x[FFT_N/2]; //
extern FA_OUT Z_out_x[FFT_N]; //

extern FA_OUT IQ_out_MAX; //
extern FA_OUT Z_out_MAX; //

extern double db_amp;  
COMPLEX add(COMPLEX a,COMPLEX b);
COMPLEX sub(COMPLEX a,COMPLEX b);
COMPLEX mul(COMPLEX a,COMPLEX b);

float FFT(float I_data[],float Q_data[]);
float fft2(COMPLEX * out, COMPLEX *in, int size,int log2n);

#endif
