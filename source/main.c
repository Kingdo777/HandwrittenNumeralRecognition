#include<stdio.h>
#include<stdlib.h>
#include<cv.h>
#include<highgui.h>
#include"initialize.h"
#include"img_process.h"
#include"data.h"
#include"discipline.h"
#include"identifier.h"
#define TRAIN_DATA_COUNT 37950
void eatline(void);
void make_train_data();
const int num_layers = 3;//层数
const int neuron_num_p_layer[3] = { 784, 30, 10 };//每层的神经元个数
weight weights;
biase biases;
int main() {
	//make_train_data();
	initialize();
	FILE *fp;
	fopen_s(&fp, "Data\\train_data.bin", "rb");
	train_data*data = (train_data*)malloc(TRAIN_DATA_COUNT * sizeof(train_data));
	fread(data, sizeof(train_data), TRAIN_DATA_COUNT, fp);
	fclose(fp);
	int m;
	printf("输入迭代次数：");
	while (scanf_s("%d", &m)!=1)
	{
		eatline();
	}
	eatline();
	SGD(m, 3.0, 10, data, TRAIN_DATA_COUNT);
	printf("迭代全部完成，可以进行数据测试\n");
	train_data test_data;//用于存放测试图片的灰度值
	int value;
	char img_name[101] = "";
	char file[31];
	printf("Input the img_name like 1.jpg\n");
	while (scanf_s("%s", file, 101) != EOF) {
		eatline();
		strcat_s(img_name, 101, file);
		get_img_data(img_name, test_data.Grayscale);
		value = identifier(test_data, 1);
		printf("%d\n", value);
		strcpy_s(img_name, 101, "");
	}
	system("pause");
	return 0;
}

void eatline(void)
{
	while (getchar() != '\n')
	{
		continue;
	}
	return;
}
void make_train_data() {
	int i, j, k;
	FILE *fp;
	char img_name[101];
	train_data data;
	fopen_s(&fp, "Data\\train_data.bin", "a+b");
	if (fp == NULL)
	{
		fprintf(stderr, "open the file faultly\n");
		system("pause");
		exit(1);
	}
	int item_count[10] = { 4132,4684,4177,4351,4072,3795,4137,4401,4063,4188 };
	for (i = 0; i < 3795; i++)
	{
		for (j = 0; j < 10; j++) {
			sprintf_s(img_name, 101, "Data\\%d\\%d.%d.jpg", j, j, i);
			for (k = 0; k < 10; k++)
			{
				data.real_value[k] = k == j ? 1 : 0;
			}
			get_img_data(img_name, data.Grayscale);
			fwrite(&data, sizeof(train_data), 1, fp);
		}
	}
	fclose(fp);
}