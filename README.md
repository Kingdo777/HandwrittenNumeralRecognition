# HandwrittenNumeralRecognition
###文档  目录结构：  
<p>HandwrittenNumeralRecognition/</P>  
├──Data/
│   ├────mnlist.zip			  压缩文件中包含所有的图片文件  
│   └────train_data.zip		已经通过程序处理过的数据文件，是对mnlist.zip中图片经过归类，像素灰度计算之后二进制文件，由于原来的二进制文件太大，因此进行了压缩，解压时请选择加压到当前文件夹，已确保.bin文件在Data根目录中    
│  
├──source/  
│   ├────data.h				    定义了所需的数据结构  
│   ├────discipline.h  
│   ├────discipline.c		  训练函数,负责迭代计算权值w和b  
│   ├────img_process.h		
│   ├────get_img_data.c		处理图片并获得灰度值  
│   ├────initialize.h		
│   ├────initialize.c		  初始化矩阵  
│   ├────identifier.h  
│   ├────identifier.c		  测试识别图片  
│   └────main.c				    你懂的=.=#  
│  
├──TestDate/				      测试用的标准图片，程序目前只能识别28*28的图片，格式：view.exe test/1.jpg  
│  
├──View.exe/				      可执行文件（win10 pro 64bit）  
│  
└────README.md				    the file which you are reading...  
