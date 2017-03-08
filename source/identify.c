#include "data.h"
#include <stdio.h>
#include "discipline.h"
int identifier(train_data test_data,int if_put) {
	int i, j;
	double z2[30] = { 0.0 }, z3[10] = { 0.0 };//z2ºÍz3
	double a2[30] = { 0.0 }, a3[10] = { 0.0 };//¦Ò(z2)ºÍ¦Ò(z3)

	for (i = 0; i < 30; i++)
	{
		for (j = 0; j < 784; j++)
		{
			z2[i] += weights.w_1_2[i][j] * test_data.Grayscale[j];
		}
		z2[i] += biases.b2[i];
	}
	sigmoid(z2, a2, 30);

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 30; j++)
		{
			z3[i] += weights.w_2_3[i][j] * a2[j];
		}
		z3[i] += biases.b3[i];
	}
	sigmoid(z3, a3, 10);

	int max=0;
	double Probability=0.0;
	for ( i = 0; i < 10; i++)
	{
		if (a3[i]>Probability)
		{
			Probability = a3[i];
			max = i;
		}
		if (if_put)
		{
			printf("%d:%f\n", i, a3[i]);
		}
	}
	return max;
}