#include "fft.h"
#include "FastMath.h"
#include <math.h>
COMPLEX wn[FFT_N]; //
COMPLEX xdata_x[FFT_N]; //
COMPLEX Qdata_x[FFT_N]; //
COMPLEX Idata_x[FFT_N]; //


FA_OUT Q_out_x[FFT_N/2]; //
FA_OUT I_out_x[FFT_N/2]; //
FA_OUT IQ_out_x[FFT_N/2]; //

FA_OUT Q_out_MAX; //
FA_OUT I_out_MAX; //
FA_OUT IQ_out_MAX; //


/*复数加法*/
COMPLEX add(COMPLEX a,COMPLEX b)
{
 COMPLEX c;
 c.real=a.real+b.real;
 c.img=a.img+b.img;
 return c;
}

/*复数减法*/
COMPLEX sub(COMPLEX a,COMPLEX b)
{
 COMPLEX c;
 c.real=a.real-b.real;
 c.img=a.img-b.img;
 return c;
}

/*复数乘法*/
COMPLEX mul(COMPLEX a,COMPLEX b)
{
 COMPLEX c;
 c.real=a.real*b.real - a.img*b.img;
 c.img=a.real*b.img + a.img*b.real;
 return c;
}

/***码位倒序函数***/
void Reverse(void)
{
 unsigned int i,j,k;
 unsigned int t;
 COMPLEX temp;
 for(i=0;i<FFT_N;i++)
 {
  k=i;
  j=0;
  for(t=0;t<log2N;t++)
  {
   j<<=1;
   j|=(k&1);
   k>>=1;
  }
  if(j>i)
  {
   temp=xdata_x[i];
   xdata_x[i]=xdata_x[j];
   xdata_x[j]=temp;
  }
 }
}

float FFT(float I_data[],float Q_data[])
{
 unsigned int i,j,k,l;
 COMPLEX top,bottom,xW;
 float Qmaxfre=0.001,Qmaxamp=0;
 float Imaxfre=0.001,Imaxamp=0;
 float IQmaxfre=0.001,IQmaxamp=0;
 for(i=0;i<FFT_N;i++)
 {
	 xdata_x[i].real=I_data[i];
	 xdata_x[i].img=Q_data[i];
	 wn[i].real=FastCos(2.0*PI/FFT_N*i);
   wn[i].img=-FastSin(2.0*PI/FFT_N*i);
 }	
   
 Reverse(); 

 for(i=0;i<log2N;i++)
 {   
	l=1<<i;
	for(j=0;j<FFT_N;j+=2*l)  
	{   
	 for(k=0;k<l;k++) 
	 { 

		 xW=mul(xdata_x[j+k+l],wn[FFT_N/(2*l)*k]); 
		 top=add(xdata_x[j+k],xW); 
		 bottom=sub(xdata_x[j+k],xW);
		 xdata_x[j+k]=top;
		 xdata_x[j+k+l]=bottom;
	 }
	}
 }
 for(i=1;i<=(FFT_N/2);i++)
 {
	 Idata_x[i].real=0.5*(xdata_x[i].real+xdata_x[FFT_N-i].real);
	 Idata_x[i].img=0.5*(xdata_x[i].img-xdata_x[FFT_N-i].img);

	 Qdata_x[i].real=0.5*(xdata_x[i].real-xdata_x[FFT_N-i].real);
     Qdata_x[i].img=0.5*(xdata_x[i].img+xdata_x[FFT_N-i].img);

 }

 for(i=1;i<=(FFT_N/2);i++)
 {
	 I_out_x[i].fre=((float)i)*FS/(FFT_N*1.0);
	 I_out_x[i].amp=FastSqrt(Idata_x[i].real*Idata_x[i].real+Idata_x[i].img*Idata_x[i].img);
	 if(I_out_x[i].amp>Imaxamp)
	 {
	  Imaxfre=I_out_x[i].fre;
	  Imaxamp=I_out_x[i].amp;
	 }	
	 
	 Q_out_x[i].fre=((float)i)*FS/(FFT_N*1.0);
	 Q_out_x[i].amp=FastSqrt(Qdata_x[i].real*Qdata_x[i].real+Qdata_x[i].img*Qdata_x[i].img);
	 if(Q_out_x[i].amp>Qmaxamp)
	 {
	  Qmaxfre=Q_out_x[i].fre;
	  Qmaxamp=Q_out_x[i].amp;
	 }	 
	 IQ_out_x[i].fre=((float)i)*FS/(FFT_N*1.0);
	 IQ_out_x[i].amp=FastSqrt(xdata_x[i].real*xdata_x[i].real+xdata_x[i].img*xdata_x[i].img);
	 if(IQ_out_x[i].amp>Imaxamp)
	 {
	  IQmaxfre=IQ_out_x[i].fre;
	  IQmaxamp=IQ_out_x[i].amp;
	 }	 
 }
 
 I_out_MAX.amp=Imaxamp;
 I_out_MAX.fre=Imaxfre; 

 Q_out_MAX.amp=Qmaxamp;
 Q_out_MAX.fre=Qmaxfre;	
 
 IQ_out_MAX.amp=IQmaxamp;
 IQ_out_MAX.fre=IQmaxfre; 

 return 1;
}

