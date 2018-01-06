#include<iostream>
#include<vector>
#include <complex>
#include <cmath>
#include"core.h"
#include "SupFunction.h"
using namespace std;
using namespace openqr;

int main()
{

	//QRCode qrGen;
	//ImageIO io;
	//qrGen.GenerateQRCode("WJH ZZH");
	//io.ImageSave("scanQR.bmp", qrGen.BitConvertToGray());
	/*
	Matrix<int> qrPic = io.ImageRead<int>("scanQR.bmp");
	QRCode qrScan;
	for(int i=0;i<16;++i)
		for (int j = 0; j < 16; ++j)
		{
			qrPic(12 * 16 + i, 12 * 16 + j) = ~qrPic(12 * 16 + i, 12 * 16 + j);
			qrPic(13 * 16 + i, 12 * 16 + j) = ~qrPic(13 * 16 + i, 12 * 16 + j);
			qrPic(15 * 16 + i, 18 * 16 + j) = ~qrPic(15 * 16 + i, 18 * 16 + j);
			qrPic(14 * 16 + i, 13 * 16 + j) = ~qrPic(14 * 16 + i, 13 * 16 + j);
		}
	io.ImageSave("scanQRchanged.bmp", qrPic);
	cout<<qrScan.DecodeQRCode(qrPic);*/
	ImageIO io;
	Matrix<int> changedQRPic = io.ImageRead<int>("scanQR.bmp");
	QRCode qrScan;
	cout << qrScan.DecodeQRCode(changedQRPic);
	return 0;
}