#include<stdio.h>
#include<stdlib.h>
#include<opencv2\core\fast_math.hpp>
#include<cv.h>
#include<highgui.h>
#include<imgcodecs\imgcodecs_c.h>
void get_img_data(char* img_name,double *f) {
	/*FILE *fp;
	fopen_s(&fp, img_name, "rb");
	if (fp==NULL)
	{
	fprintf(stderr,"open the file faultly\n");
	system("pause");
	exit(1);
	}
	fclose(fp);*/
	double Gray;
	IplImage* img = cvLoadImage(img_name, 1);
	if (img == NULL)
	{
		fprintf(stderr, "open the file %s faultly\n",img_name);
		system("pause");
		exit(1);
	}
	for (int i = 0; i < 28; i++)
	{
		for (int j = 0; j < 28; j++)
		{
			//����һ��ʹ��cvGet2D()������ӷ���
			CvScalar s = cvGet2D(img, i, j); //����i����y�ᣨ��i�У�����height��j����x�ᣨ��j�У�����width��
			Gray = (s.val[2] * 0.299 + s.val[1] * 0.587 + s.val[0] * 0.114)/255;
			*f++ = Gray;
			//printf("%3.f %3.f %3.f\n", s.val[2], s.val[1], s.val[0]);
		}
	}
	//free(img);
}