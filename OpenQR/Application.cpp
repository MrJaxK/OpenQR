#include<iostream>
#include"core.h"
#include"BMPImageIO.hpp"
#include"bmp.h"
using namespace std;
using namespace openqr;
int main()
{
	/*BMPImageIO<int> t;
	Matrix<int> temp =t.ImageRead("no.bmp");
	cout << temp << endl;*/
	string a;
	cin >> a;
	
	std::string fileSuffix = a.substr(a.find_last_of(".") + 1);
	transform(fileSuffix.begin(), fileSuffix.end(), fileSuffix.begin(), ::tolower);
	cout << fileSuffix;
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
	//		
	//		cout << (int)R << " " << (int)G << " " << (int)B << endl;
	//		gray = (R * 11 + G * 16 + B * 5) / 32; // define gray color
	//		if (x == t.cols / 2 - 1)
	//			cout << "             jojifjoasjdoa" << endl;
	//	}
	//}
	//


	return 0;
}