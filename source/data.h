typedef struct {
	double w_1_2[30][784];//1_2层的初始权重
	double w_2_3[10][30];//2_3层的初始权重
}weight;
typedef struct {
	double b2[30];//2层的初始偏移
	double b3[10];//3层的初始偏移
}biase;
typedef struct {
	double Grayscale[784];//图片的灰度值
	int real_value[10];//图片的真实值
}train_data;
extern weight weights;
extern biase biases;