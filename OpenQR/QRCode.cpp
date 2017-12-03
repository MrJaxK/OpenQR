#include "QRCode.h"



openqr::QRCode::QRCode()
{
	GenerateFunctionPatterns();
}


openqr::QRCode::~QRCode()
{
}
openqr::Matrix<int> openqr::QRCode::BitConvertToGray()
{
	Matrix<int>temp(functionPatterns);
	for(int i=0;i<temp.getColNumber();++i)
		for (int j = 0; j < temp.getRowNumber(); ++j)
		{
			if (temp(i, j))//1 is black
				temp(i, j) = 0;//Gray
			else
				temp(i, j) = 255;
		}
	return temp;
}
//Use 2-Q specification
void openqr::QRCode::GenerateFunctionPatterns()
{
	functionPatterns.Resize(25, 25, 0);
	AddFinderPatterns(0, 0);
	AddFinderPatterns(25 - 7, 0);
	AddFinderPatterns(0, 25 - 7);
	
}

void openqr::QRCode::AddFinderPatterns(int x, int y)
{
	for (int i = 0; i < 7; ++i)
	{
		functionPatterns(x + i, y) = 1;
		functionPatterns(x + i, y + 6) = 1;
	}
	for (int j = 1; j < 6; ++j)
	{
		functionPatterns(x, y + j) = 1;
		functionPatterns(x + 6, y + j) = 1;
	}
	for (int i = 2; i <= 4; ++i)
		for (int j = 2; j <= 4; ++j)
			functionPatterns(x + i, y + j) = 1;
}
