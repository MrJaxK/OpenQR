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

	

	QRCode qr;
	ImageIO io;
	//io.ImageSave("qr1.bmp", qr.BitConvertToGray());
	qr.GenerateQRCode("JACK THE RIPPER");
	io.ImageSave("myQRCode.bmp", qr.BitConvertToGray());
	qr.GenerateQRCode("JACK THE RIPPERsad");
	io.ImageSave("myQRCode2.bmp", qr.BitConvertToGray());
	return 0;
}