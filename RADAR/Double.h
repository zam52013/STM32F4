/*
The MIT License (MIT)

Copyright (c) 2015-? suhetao

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _DOUBLE_H
#define _DOUBLE_H

//////////////////////////////////////////////////////////////////////////
//algorithm from the book
//<<Fast and Accurate Finite-Element Multigrid Solvers for PDE Simulations on GPU Clusters>>
//References:
//Emulated double precision Double single routine from nvidia developer zone
//////////////////////////////////////////////////////////////////////////
//define my own double struct
typedef struct
{
	float hi;
	float lo;
} Double;
 Double intToDouble(int A);
 Double floatToDouble(float A);
 Double doubleToDouble(double A);
 double DoubleTodouble(Double B);
 Double DoubleAdd(Double A, Double B);
 Double DoubleSub(Double A, Double B);
 Double DoubleMul(Double A, Double B);
 Double DoubleDiv(Double A, Double B);
#endif
