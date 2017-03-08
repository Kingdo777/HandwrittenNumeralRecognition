#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"data.h"
#include"identifier.h"
static weight nw;//用于描述w的变化值(变化值是一组数据变化的平均值)
static biase nb;//用于描述b的变化值(变化值是一组数据变化的平均值)
void zeros_data();
void TestSuccessrate();
void sigmoid_prime(const double s[], double o[], int count);
void sigmoid(const double in[], double out[], int count);
void backprop(train_data *data);
void SGD(int epochs, double eta, int mini_batch_size, train_data train_datas[], int train_data_count);
void update_mini_batch(train_data * ptr_train_data, double eta, int mini_batch_size);
void SGD(int epochs, double eta, int mini_batch_size, train_data train_datas[], int train_data_count) {//epochs：迭代次数 eta学习参数mini_batch_size：最小分支数train_datas：训练数据train_data_count：训练数据的个数
	int i;//用于控制迭代循环
	int j;//j用于控制选取的样本循环
	train_data *ptr_train_data = train_datas;
	for (i = 0; i < epochs; i++) {
		printf("正在进行第%d次迭代计算\n", i+1);
		ptr_train_data = train_datas;
		for (j = 0; j < train_data_count; j += mini_batch_size, ptr_train_data += mini_batch_size)
		{
			update_mini_batch(ptr_train_data, eta, mini_batch_size);
		}
		TestSuccessrate();
	}
}

void update_mini_batch(train_data * ptr_train_data, double eta, int mini_batch_size)
{
	
	zeros_data();
	for (int i = 0; i < mini_batch_size; i++) {
		backprop(ptr_train_data++);
	}
	double *p, *q;//p指向原数据，q指向变化量
	p = (double*)weights.w_1_2;
	q = (double*)nw.w_1_2;
	for (int i = 0; i < 30 * 784; i++)
	{
		*p = *p++ - (eta / mini_batch_size) * *q++;
	}
	p = (double*)weights.w_2_3;
	q = (double*)nw.w_2_3;
	for (int i = 0; i < 300; i++)
	{
		*p = *p++ - (eta / mini_batch_size) * *q++;
	}
	p = biases.b2;
	q = nb.b2;
	for (int i = 0; i < 30; i++)
	{
		*p = *p++ - (eta / mini_batch_size) * *q++;
	}
	p = biases.b3;
	q = nb.b3;
	for (int i = 0; i < 10; i++)
	{
		*p = *p++ - (eta / mini_batch_size) * *q++;
	}
}

void backprop(train_data*data) {
	/*
	输入 x:计算输入层相应的激活函数值 a1。
	正向传播：对每个 l=2,3,…,Ll=2,3,…,L ，计算 zl=wlal−1+blzl=wlal−1+bl 和 al=σ(zl)al=σ(zl) 。
	输出误差  δLδL ：计算向量 δL=∇aC⊙σ′(zL)δL=∇aC⊙σ′(zL) 。
	将误差反向传播：对每个 l=L−1,L−2,…,2l=L−1,L−2,…,2 计算 δl=((wl+1)Tδl+1)⊙σ′(zl)δl=((wl+1)Tδl+1)⊙σ′(zl)
	输出：代价函数的梯度为 ∂C∂wljk=al−1kδlj∂C∂wjkl=akl−1δjl 和 ∂C∂blj=δlj∂C∂bjl=δjl
	*/
	int i,j;
	double z2[30] = {0.0}, z3[10] = { 0.0 };//z2和z3
	double a2[30] = { 0.0 }, a3[10] = { 0.0 };//σ(z2)和σ(z3)
	double z3_dao[10] = { 0.0 }, z2_dao[30] = { 0.0 };//σ′(z3)

	double error_3[10], error_2[30];//δ3和δ2

	//计算z2和z3 、σ(z2)和σ(z3)
	

	for ( i = 0; i < 30; i++)
	{
		for ( j = 0; j < 784; j++)
		{
			z2[i] += weights.w_1_2[i][j] * data->Grayscale[j];
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

	//计算σ′(z3)
	sigmoid_prime(a3, z3_dao, 10);
	sigmoid_prime(a2, z2_dao, 30);

	//计算δ3和δ2

	for (int i = 0; i < 10; i++) {
		error_3[i] = (a3[i] - data->real_value[i])*z3_dao[i];
		for (int j = 0; j < 30; j++)
		{
			nw.w_2_3[i][j] += a2[j] * error_3[i];
		}
		nb.b3[i] += error_3[i];
	}


	double tem = 0.0;
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 10; j++) {
			tem += (weights.w_2_3[j][i] * error_3[j]);
		}
		error_2[i] = (tem)*z2_dao[i];
		
		for (int j = 0; j < 784; j++)
		{
			nw.w_1_2[i][j] += data->Grayscale[j] * error_2[i];
		}
		nb.b2[i] += error_2[i];
	}

}
void sigmoid(const double in[],double out[],int count) {
	for (int i = 0; i < count; i++)
	{
		out[i] = 1.0 / (1.0 + exp(-in[i]));
	}
}

void sigmoid_prime(const double s[], double o[], int count) {
	for (int i = 0; i < count; i++)
	{
		o[i] = s[i] * (1.0 - s[i]);
	}
}
void zeros_data() {
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 784; j++) {
			nw.w_1_2[i][j] = 0.0;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 30; j++) {
			nw.w_2_3[i][j] = 0.0;
		}
	}
	for (int i = 0; i < 30; i++)
	{
			nb.b2[i] = 0.0;
	}
	for (int i = 0; i < 10; i++)
	{
		nb.b3[i] = 0.0;
	}
}
void TestSuccessrate() {
	FILE *fp;
	fopen_s(&fp, "Data\\train_data.bin", "rb");
	train_data*data = (train_data*)malloc(37950 * sizeof(train_data));
	fread(data, sizeof(train_data), 37950, fp);
	fclose(fp);
	int count=0;
	fputs("正在测试识别率。。。\n",stdout);
	for (int i = 0; i < 37950; i++)
	{
		if (data->real_value[identifier(*data, 0)])
		{
			count++;
		}
		data++;
	}
	printf("测试结束成功率为%%%.2f\n",((double)count/37950.0)*100);
}

