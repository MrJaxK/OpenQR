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

	//QRCode qr;
	//ImageIO io;
	//io.ImageSave("func.bmp", qr.BitConvertToGray());

	//DataEncoder da;
	//string encodeWith2_QStandard = da.Encode2_Q("openqr");
	//const int MessageLength = 22;
	//uint8_t EncodeCoeff[22];
	//for (int i = 0; i < 22; ++i)
	//{
	//	string temp = encodeWith2_QStandard.substr(8 * i, 8);
	//	bitset<8>tempBit(temp);
	//	//cout << temp << "  " << tempBit.to_ulong() << endl;
	//	cout << tempBit.to_ulong() << ",";
	//	EncodeCoeff[i] = tempBit.to_ulong();
	//}
	//cout << endl;
	//const int EccLength = 22;
	////char* encoded = new char[EccLength + MessageLength];
	//uint8_t* encoded = new uint8_t[EccLength + MessageLength];
	//RS::ReedSolomon<MessageLength, EccLength> rsencoder;
	//rsencoder.Encode(EncodeCoeff, encoded);
	//int standardEncoded[44];
	//for (int i = 0; i < 44; ++i)
	//{
	//	standardEncoded[i] = encoded[i];//(encoded[i] + 256) % 256;
	//}
	//for (int i = 22; i < 44; ++i)
	//{
	//	cout << standardEncoded[i] << "  ";
	//}
	//delete[] encoded;

	QRCode qr;
	//qr.GenerateQRCode("OpEnQR");
	ImageIO io;
	io.ImageSave("ModulePlaced.bmp", qr.BitConvertToGray());
	qr.GenerateQRCode("OPENQR MRK HELLOWORLD");
	io.ImageSave("bestMasked.bmp", qr.BitConvertToGray());
	return 0;
}