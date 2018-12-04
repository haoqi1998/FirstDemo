// FirstDemo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")
int main()

{

	GDALDataset* poSrcDS;           //����ͼ��

	GDALDataset* poDstDS;			//���ͼ��

	int imgXlen, imgYlen;			//ͼ��Ŀ�Ⱥ͸߶�

	char* srcPath = "trees.jpg";	//����ͼ��·��

	char* dstPath = "res.tif";		//���ͼ��·��

	GByte* buffTmp;					//ͼ���ڴ�洢

	int i, bandNum;					//ͼ�񲨶���

									//ע������

	GDALAllRegister();



	//��ͼ��

	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);



	//��ȡͼ���ߺͲ�������

	imgXlen = poSrcDS->GetRasterXSize();

	imgYlen = poSrcDS->GetRasterYSize();

	bandNum = poSrcDS->GetRasterCount();



	//�����ȡ���

	cout << "Image X Length: " << imgXlen << endl;

	cout << "Image Y Length: " << imgYlen << endl;

	cout << "Band Number: " << bandNum << endl;



	//����ͼ��Ŀ�߷����ڴ�

	buffTmp = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));

	//�������ͼ��

	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);

	//���ε����������

	for (i = 0; i < bandNum; i++)

	{

		poSrcDS->GetRasterBand(i + 1)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmp, imgXlen, imgYlen, GDT_Byte, 0, 0);

		poDstDS->GetRasterBand(i + 1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmp, imgXlen, imgYlen, GDT_Byte, 0, 0);

		printf("...... band %d processing ......\n", i);

	}



	//����ڴ�

	CPLFree(buffTmp);

	//�ر�dataset���ȴ򿪵ĺ��

	GDALClose(poDstDS);

	GDALClose(poSrcDS);



	system("PAUSE");

	return 0;

}
