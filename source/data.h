typedef struct {
	double w_1_2[30][784];//1_2��ĳ�ʼȨ��
	double w_2_3[10][30];//2_3��ĳ�ʼȨ��
}weight;
typedef struct {
	double b2[30];//2��ĳ�ʼƫ��
	double b3[10];//3��ĳ�ʼƫ��
}biase;
typedef struct {
	double Grayscale[784];//ͼƬ�ĻҶ�ֵ
	int real_value[10];//ͼƬ����ʵֵ
}train_data;
extern weight weights;
extern biase biases;