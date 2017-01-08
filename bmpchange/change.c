#include <stdio.h> 
#include <stdlib.h>

/*位图文件头*/
typedef  struct  tagBITMAPFILEHEADER
{ 
	unsigned short int  bfType;       //位图文件的类型，必须为BM 
	unsigned long       bfSize;       //文件大小，以字节为单位
	unsigned short int  bfReserverd1; //位图文件保留字，必须为0 
	unsigned short int  bfReserverd2; //位图文件保留字，必须为0 
	unsigned long       bfbfOffBits;  //位图文件头到数据的偏移量，以字节为单位
}BITMAPFILEHEADER; 

/*位图信息头*/
typedef  struct  tagBITMAPINFOHEADER 
{ 
	long biSize;                        //该结构大小，字节为单位
	long  biWidth;                     //图形宽度以象素为单位
	long  biHeight;                     //图形高度以象素为单位
	short int  biPlanes;               //目标设备的级别，必须为1 
	short int  biBitcount;             //颜色深度，每个象素所需要的位数
	short int  biCompression;        //位图的压缩类型
	long  biSizeImage;              //位图的大小，以字节为单位
	long  biXPelsPermeter;       //位图水平分辨率，每米像素数
	long  biYPelsPermeter;       //位图垂直分辨率，每米像素数
	long  biClrUsed;            //位图实际使用的颜色表中的颜色数
	long  biClrImportant;       //位图显示过程中重要的颜色数
}BITMAPINFOHEADER; 

/*彩色表*/
typedef struct RGB_QUAD 
{
	unsigned short rgbBlue; /* 蓝色强度 */
	unsigned short rgbGreen; /* 绿色强度 */
	unsigned short rgbRed; /* 红色强度 */
	unsigned short rgbReversed; /* 保留值 */
}RGBQUAD;

//定义一个位图结构，此结构对本例仅起测试作用 
typedef  struct 
{ 
	BITMAPFILEHEADER  file; //文件信息区
	BITMAPINFOHEADER  info; //图象信息区
}bmp;


int main(){
 	bmp  m;        //定义一个位图结构，此结构对本例仅起测试作用 
  	FILE *fp; 
	if((fp=fopen( "test.bmp", "rb+"))==NULL){ 
		printf( "can't open the bmp imgae.\n "); 
   		exit(0); 
 	}


	fread(&m.file.bfType,sizeof(char),1,fp); 
	printf("类型为%c",m.file.bfType); 
	fread(&m.file.bfType,sizeof(char),1,fp); 
	printf("%c\n",m.file.bfType);        
	fread(&m.file.bfSize,sizeof(long),1,fp); 
	printf("文件长度为%ld\n",m.file.bfSize);  
	fread(&m.file.bfReserverd1,sizeof(short int),1,fp); 
	printf("保留字1为%d\n",m.file.bfReserverd1); 
	fread(&m.file.bfReserverd2,sizeof(short int),1,fp); 
	printf("保留字2为%d\n",m.file.bfReserverd2); 
	fread(&m.file.bfbfOffBits,sizeof(long),1,fp); 
	printf("偏移量为%ld\n",m.file.bfbfOffBits);
	fread(&m.info.biSize,sizeof(long),1,fp); 
	printf("此结构大小为%ld\n",m.info.biSize); 
	fread(&m.info.biWidth,sizeof(long),1,fp); 
	printf("位图的宽度为%ld\n",m.info.biWidth);
	fread(&m.info.biHeight,sizeof(long),1,fp); 
	printf("位图的高度为%ld\n",m.info.biHeight);
	fread(&m.info.biPlanes,sizeof(short),1,fp); 
	printf("目标设备位图数%d\n",m.info.biPlanes);
	fread(&m.info.biBitcount,sizeof(short),1,fp); 
	printf("颜色深度为%d\n",m.info.biBitcount);
	fread(&m.info.biCompression,sizeof(long),1,fp); 
	printf("位图压缩类型%d\n",m.info.biCompression); 
	fread(&m.info.biSizeImage,sizeof(long),1,fp); 
	printf("位图大小%ld\n",m.info.biSizeImage); 
	fread(&m.info.biXPelsPermeter,sizeof(long),1,fp); 
	printf("位图水平分辨率为%ld\n",m.info.biXPelsPermeter); 
	fread(&m.info.biYPelsPermeter,sizeof(long),1,fp); 
	printf("位图垂直分辨率为%ld\n",m.info.biYPelsPermeter); 
	fread(&m.info.biClrUsed,sizeof(long),1,fp); 
	printf("位图实际使用颜色数%ld\n",m.info.biClrUsed);
	fread(&m.info.biClrImportant,sizeof(long),1,fp); 
	printf("位图显示中比较重要颜色数%ld\n",m.info.biClrImportant); 
	
	
	char a[m.info.biSizeImage], b[m.info.biSizeImage];
	
	fseek(fp, m.file.bfbfOffBits, 0);
	fread(&a, sizeof(char), m.info.biSizeImage, fp);
//***************************************************************************************************
//	int  i = 0;
//	char *p;
//	for(p = a + m.info.biSizeImage-1;; p >= a; p--,i++);
//		b[i] = *p;
//***************************************************************************************************
//	char *p , *i ,*j;
//	i = a;
//	j = a + m.info.biSizeImage-1;
//	p = a + (m.info.biSizeImage-1)/2; 
//	for(; i <= p; ++i, --j);
//		*i ^= *j;
//		*j ^= *i;
//		*i ^= *j;
//  以上两段代码没发现错误 调试功能没法正常进行 
//  用指针操作内存中存储的信息不能输出正确的结果？ 
//***************************************************************************************************
	
	for(int i = 0,j = m.info.biSizeImage-1; i < m.info.biSizeImage; i++,j--)
		b[i] = a[j];

//*************************************************************************************************** 
	fseek(fp, m.file.bfbfOffBits, 0);
	fwrite(&b, sizeof(char), m.info.biSizeImage, fp);

	fclose(fp);

	printf("\nsucceed\n");

	getchar();

	return 0; 
}
