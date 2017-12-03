#include "QRCode.h"



openqr::QRCode::QRCode()
{
	GenerateFunctionPatterns();
}


openqr::QRCode::~QRCode()
{
}
//Origin: 25x25 matrix
//Convert to 400x400 matrix
openqr::Matrix<int> openqr::QRCode::BitConvertToGray()
{
	Matrix<int>temp(functionPatterns);
	for(int i=0;i<temp.getColNumber();++i)
		for (int j = 0; j < temp.getRowNumber(); ++j)
		{
			if (temp(i, j)==1)//1 is black
				temp(i, j) = 0;//Gray: Black:0 White:255
			else
				if(temp(i,j)==0)
					temp(i, j) = 255;
		}
	Matrix<int>tempBig(400, 400);
	for(int x=0;x<temp.getColNumber();++x)
		for (int y = 0; y < temp.getRowNumber(); ++y)
		{
			for (int i = 16 * x; i < 16 * x + 16; ++i)
				for (int j = 16 * y; j < 16 * y + 16; ++j)
					tempBig(i, j) = temp(x, y);
		}
	return tempBig;
}
//Use 2-Q specification
void openqr::QRCode::GenerateFunctionPatterns()
{
	functionPatterns.Resize(25, 25, 100);//Default 50 to test
	AddFinderPatterns(0,24);
	AddFinderPatterns(0,6);
	AddFinderPatterns(25-7,24);
	AddSeparators();
	AddAlignmentPatterns(18,6);
	ReserveFormatArea();
	AddTimingPatterns();
	//Add dark module
	functionPatterns(8, 7) = 1;
	ReserveVersionArea();
}

void openqr::QRCode::AddFinderPatterns(int x, int y)
{
	for (int i = 0; i < 7; ++i)
	{
		functionPatterns(x + i, y) = 1;
		functionPatterns(x + i, y - 6) = 1;
	}
	for (int j = 1; j < 6; ++j)
	{
		functionPatterns(x, y - j) = 1;
		functionPatterns(x + 6, y - j) = 1;
	}
	for (int i = 2; i <= 4; ++i)
		for (int j = 2; j <= 4; ++j)
			functionPatterns(x + i, y - j) = 1;
}

void openqr::QRCode::AddSeparators()
{
	for (int x = 0; x <= 7; ++x)
	{
		functionPatterns(x, 7) = 0;
		functionPatterns(x, 17) = 0;
	}
	for (int yCount = 0; yCount < 7; ++yCount)
	{
		functionPatterns(7, yCount) = 0;
		functionPatterns(7, 18 + yCount) = 0;
	}
	for (int x = 17; x < 25; ++x)
		functionPatterns(x, 17) = 0;
	for (int y = 17; y < 25; ++y)
		functionPatterns(17, y) = 0;
}

void openqr::QRCode::AddAlignmentPatterns(int centerx,int centery)
{
	functionPatterns(centerx, centery) = 1;
	for (int i = -2; i <= 2; ++i)
	{
		functionPatterns(centerx + i, centery + 2) = 1;
		functionPatterns(centerx + i, centery - 2) = 1;
	}
	for (int i = -1; i <= 1; ++i)
	{
		functionPatterns(centerx - 2, centery + i) = 1;
		functionPatterns(centerx + 2, centery + i) = 1;
	}
}

void openqr::QRCode::AddTimingPatterns()
{
	for (int i = 1; i <= 9; ++i)
		functionPatterns(6, 7 + i) = i % 2;
	for (int i = 1; i <= 9; ++i)
		functionPatterns(7 + i, 17) = i % 2;
}
//Use gray 180 stand for reservation
void openqr::QRCode::ReserveFormatArea()
{
	for (int y = 0; y <= 6; ++y)
		functionPatterns(8, y) = 180;
	for (int x = 17; x < 25; ++x)
		functionPatterns(x, 16) = 180;
	for (int x = 0; x <= 8; ++x)
		functionPatterns(x, 16) = 180;
	for (int y = 17; y < 25; ++y)
		functionPatterns(8, y)=180;
}

void openqr::QRCode::ReserveVersionArea()
{
	for (int x = 0; x < 6; ++x)
		for (int y = 8; y <= 10; ++y)
			functionPatterns(x, y) = 50;
	for (int x = 14; x <= 16; ++x)
		for (int y = 19; y < 25; ++y)
			functionPatterns(x, y) = 50;
}
