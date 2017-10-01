#include<iostream>
#include"BMPImageIO.h"
using namespace std;
using namespace openqr;
bool test(IImageIO& imageIO)
{
	imageIO.ImageRead("123");
	return true;
}
int main()
{
	BMPImageIO a;
	test(a);
	cout << a.data << endl;
	return 0;
}