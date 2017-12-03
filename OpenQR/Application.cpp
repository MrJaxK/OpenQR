#include<iostream>
#include<vector>
#include <complex>
#include <cmath>
#include"core.h"
#include "SupFunction.h"
#include"BMPImageIO.hpp"
#include"bmp.h"
using namespace std;
using namespace openqr;

int main()
{
    //region  BMPImageIO test
//	BMPImageIO<int> t;
//	Matrix<int> temp =t.ImageRead("no.bmp");
//	cout << temp << endl;

//	BMP t("no.bmp");
//	unsigned char R, G, B;
//	unsigned char gray;
//	BYTE* ImgValue_s = t.pixels;
//	cout << t.rows << " " << t.cols << endl;
//	for (int y = 0; y < t.rows; y++) {
//		for (int x = 0; x < t.cols; x++) {
//
//			R = ImgValue_s[3 * (t.cols*y + x) + 2];
//			G = ImgValue_s[3 * (t.cols*y + x) + 1];
//			B = ImgValue_s[3 * (t.cols *y + x) + 0];
//
//			//cout << (int)R << " " << (int)G << " " << (int)B << endl;
//			gray = (R * 11 + G * 16 + B * 5) / 32; // define gray color
//			ImgValue_s[3 * (t.cols*y + x) + 2] = gray;
//			ImgValue_s[3 * (t.cols*y + x) + 1] = gray;
//			ImgValue_s[3 * (t.cols*y + x) + 0] = gray;
//		}
//	}
//	t.save("another.bmp");
//endregion
    //    region ImageIO test
	//ImageIO imageIO;
 //   Matrix<int> mat = imageIO.ImageRead<int>("no.bmp");
	//for (int x = 0; x < 1000; ++x)
	//	for (int j = 0; j < 100; ++j)
	//		mat(x, j) = 0;
 //   if (imageIO.ImageSave("another1.bmp", mat))
 //       cout << "Done" << endl;
	//else
	//	cout << "Save fail" << endl;
    //Matrix<int> mat2(500,300,130);
    //if (imageIO.ImageSave("pure.bmp", mat2))
    //    cout << "Done" << endl;
    //else
    //    cout << "Save fail" << endl;
//        endregion

   //complex<double>a[5],b[5],c[5];
   // for(int i=0;i<5;++i)
   //     a[i]=i+1;
   // FastFourierTransform(a,5,b,fourier_transform_direction::ftdSpectrumToFunction);
   // for(int i=0;i<5;++i)
   //     cout<<b[i]<<endl;
   // cout<<endl;
   // FastFourierTransform(b,5,c,fourier_transform_direction::ftdFunctionToSpectrum);
   // for(int i=0;i<5;++i)
   //     cout<<c[i]<<endl;

	QRCode qr;
	Matrix<int>mat(400, 400, 255);
	ImageIO io;
	io.ImageSave("func.bmp", qr.BitConvertToGray());
	return 0;
}