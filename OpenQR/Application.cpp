#include<iostream>
#include"core.h"
#include"BMPImageIO.hpp"
using namespace std;
using namespace openqr;
template<typename T>
bool test(IImageIO<T>& imageIO)
{
	imageIO.ImageRead("123");
	return true;
}
int main()
{
	Matrix<int> mat;
	//BMPImageIO<int> a;
	//test<int>(a);
	// cout << a.data << endl;
	return 0;
}