#include<stdlib.h>
#include"data.h"
double make_rand();
void initialize() {
	double *p;
	p = (double*)weights.w_1_2;
	for (int i = 0; i < 30*784; i++)
	{
		*p++ = make_rand();
	}
	p = (double*)weights.w_2_3;
	for (int i = 0; i < 300; i++)
	{
		*p++ = make_rand();
	}
	p = biases.b2;
	for (int i = 0; i < 30; i++)
	{
		*p++ = make_rand();
	}
	p = biases.b3;
	for (int i = 0; i < 10; i++)
	{
		*p++ = make_rand();
	}
}
double make_rand() {
	int a = rand();
	int b = rand();
	return a < b ? (double)a / (double)b : -(double)b / (double)a;
}