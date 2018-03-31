#include "main.h"
#include "fft.h"
#include "czt.h"
#include "FastMath.h"
#include <math.h>
COMPLEX wn[FFT_N]; //
COMPLEX xdata_x[FFT_N]; //
COMPLEX xdata_x0[FFT_N]; //
COMPLEX Z_data_x[FFT_N]; //

FA_OUT IQ_out_x[FFT_N/2]; //
FA_OUT Z_out_x[FFT_N]; //

FA_OUT IQ_out_MAX; //
FA_OUT Z_out_MAX; //

double db_amp;  

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
 float IQmaxfre=0.001,IQmaxamp=0;
 float Zmaxfre=0.001,Zmaxamp=0;
 float fre1,fre2;
 for(i=0;i<FFT_N;i++)
 {
	 xdata_x[i].real=I_data[i];
	 xdata_x[i].img=Q_data[i];	 
	 xdata_x0[i].real=I_data[i];
	 xdata_x0[i].img=Q_data[i];
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
 db_amp=0;
 for(i=1;i<=(FFT_N/2);i++)
 {
		 
	 IQ_out_x[i].fre=((float)i)*FS/(FFT_N*1.0);
	 IQ_out_x[i].amp=FastSqrt(xdata_x[i].real*xdata_x[i].real+xdata_x[i].img*xdata_x[i].img);
	 db_amp+=IQ_out_x[i].amp*2;
     if(i<50&&flag==1&&IQ_out_x[i].amp>250)
     	{
     		 // printf("IQ_out_MAX.amp=%f,",IQ_out_x[i].amp);
			 // printf("IQ_out_MAX.fre=%f,",IQ_out_x[i].fre/1000);
			 // printf("db_amp=%f,",db_amp);
			//  printf("dis=%f\r\n",IQ_out_x[i].fre*0.001423825344/2);
     	}
	 //send(IQ_out_x[i].amp,IQ_out_x[i].fre);
	 if(IQ_out_x[i].amp>IQmaxamp && i<50)
	 {
	  IQmaxfre=IQ_out_x[i].fre;
	  IQmaxamp=IQ_out_x[i].amp;
	 }	 
 }
 flag=0;
 
 IQ_out_MAX.amp=IQmaxamp;
 IQ_out_MAX.fre=IQmaxfre; 
 fre1=IQ_out_MAX.fre-2*FS/(FFT_N*1.0);
 if(fre1<=0) fre1=0;
 fre2=IQ_out_MAX.fre+2*FS/(FFT_N*1.0);
 chirpzfft(Z_data_x, xdata_x0, FFT_N1,fre1,fre2 ) ;
 for(i=1;i<FFT_N1;i++)
 {
 	 Z_out_x[i].fre=fre1+((float)i)*(fre2-fre1)/(FFT_N1*1.0);
	 Z_out_x[i].amp=FastSqrt(Z_data_x[i].real*Z_data_x[i].real+Z_data_x[i].img*Z_data_x[i].img); 

	 if(Z_out_x[i].amp>Zmaxamp)
	 {
	  Zmaxfre=Z_out_x[i].fre;
	  Zmaxamp=Z_out_x[i].amp;
	 }
 }

 Z_out_MAX.amp=Zmaxamp;
 Z_out_MAX.fre=Zmaxfre; 

 return 1;
}
/***码位倒序函数***/
COMPLEX xdata[FFT_N1*2];
void Reverse2(void)
{
 unsigned int i,j,k;
 unsigned int t;
 COMPLEX temp;
 for(i=0;i<FFT_N1;i++)
 {
  k=i;
  j=0;
  for(t=0;t<log2N1;t++)
  {
   j<<=1;
   j|=(k&1);
   k>>=1;
  }
  if(j>i)
  {
   temp=xdata[i];
   xdata[i]=xdata[j];
   xdata[j]=temp;
  }
 }
}

float fft2(COMPLEX * out, COMPLEX *in, int size,int log2n)
{
 unsigned int i,j,k,l;
 COMPLEX top,bottom,xW;
 COMPLEX wn_1[FFT_N1*2];
 for(i=0;i<size;i++)
 {
	 xdata[i].real=in[i].real;
	 xdata[i].img=in[i].img;
	 wn_1[i].real=FastCos(2.0*PI/size*i);
     wn_1[i].img=-FastSin(2.0*PI/size*i);
 }	
   
 Reverse2(); 

 for(i=0;i<log2n;i++)
 {   
	l=1<<i;
	for(j=0;j<size;j+=2*l)  
	{   
	 for(k=0;k<l;k++) 
	 { 

		 xW=mul(xdata[j+k+l],wn_1[size/(2*l)*k]); 
		 top=add(xdata[j+k],xW); 
		 bottom=sub(xdata[j+k],xW);
		 xdata[j+k]=top;
		 xdata[j+k+l]=bottom;
	 }
	}
 }
 out=xdata;
 return 1;
}

