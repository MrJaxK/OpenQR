#include"Examples.h"
#include"core.h"
#include"SupFunction.h"

//If u want to use the samples,
//Please copy the functions inside the main function
//cause some header files are not included in this file
namespace openqr
{
	void BMPIOTest()
	{
		//region  BMPImageIO test
		//BMPImageIO<int> t;
		//Matrix<int> temp = t.ImageRead("no.bmp");
		//cout << temp << endl;

		//BMP t("no.bmp");
		//unsigned char R, G, B;
		//unsigned char gray;
		//BYTE* ImgValue_s = t.pixels;
		//cout << t.rows << " " << t.cols << endl;
		//for (int y = 0; y < t.rows; y++) {
		//	for (int x = 0; x < t.cols; x++) {

		//		R = ImgValue_s[3 * (t.cols*y + x) + 2];
		//		G = ImgValue_s[3 * (t.cols*y + x) + 1];
		//		B = ImgValue_s[3 * (t.cols *y + x) + 0];

		//		//cout << (int)R << " " << (int)G << " " << (int)B << endl;
		//		gray = (R * 11 + G * 16 + B * 5) / 32; // define gray color
		//		ImgValue_s[3 * (t.cols*y + x) + 2] = gray;
		//		ImgValue_s[3 * (t.cols*y + x) + 1] = gray;
		//		ImgValue_s[3 * (t.cols*y + x) + 0] = gray;
		//	}
		//}
		//t.save("another.bmp");
		//endregion
	}

	void ImageIOTest()
	{
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
	}

	void FastFourierTransTest()
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
	}
	
	void GenerateRSCodeword()
	{
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
	}

	void Generate2_QStandardQRCode()
	{
		//QRCode qr;
		////qr.GenerateQRCode("OpEnQR");
		//ImageIO io;
		//io.ImageSave("ModulePlaced.bmp", qr.BitConvertToGray());
		//qr.GenerateQRCode("OPENQR MRK HELLOWORLD");
		//io.ImageSave("bestMasked.bmp", qr.BitConvertToGray());
	}
}


