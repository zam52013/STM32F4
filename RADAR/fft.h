#ifndef __FFT_H_
#define __FFT_H_


#define FFT_N 1024      //512
#define log2N 10   //log2N=9
#define FS (21000000/33)
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

extern FA_OUT Q_out_x[FFT_N/2]; //
extern FA_OUT I_out_x[FFT_N/2]; //
extern FA_OUT IQ_out_x[FFT_N/2]; //

extern FA_OUT Q_out_MAX; //
extern FA_OUT I_out_MAX; //
extern FA_OUT IQ_out_MAX; //

float FFT(float I_data[],float Q_data[]);

#endif
