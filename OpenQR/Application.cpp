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
	//BMPImageIO<int> a;
	//test<int>(a);
	//cout << a.data << endl;
    Matrix<double> mat(1,13,21.9f);
    cout<<mat;
	return 0;
}