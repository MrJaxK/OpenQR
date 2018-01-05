#include "QRCode.h"


openqr::QRCode::QRCode()
{
	MatrixDataInitlize();
}

openqr::QRCode::QRCode(const std::string & message)
{
	GenerateQRCode(message);
}


openqr::QRCode::~QRCode()
{
}
//Origin: 25x25 matrix
//Convert to 400x400 matrix
openqr::Matrix<int> openqr::QRCode::BitConvertToGray()
{
	return BitConvertToGray(functionPatterns);
}
openqr::Matrix<int> openqr::QRCode::BitConvertToGray(Matrix<int> mat)
{
	
	Matrix<int>temp(mat);
	//Matrix<int>temp(dataAreaMask);
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
bool openqr::QRCode::GenerateQRCode(const std::string & message)
{
	MatrixDataInitlize();
	PlaceMessage(message);
	return true;
}
void openqr::QRCode::GenerateDataMaskTest()
{
	for (int i = 0; i < 8; ++i)
	{
		Matrix<int> temp = DataMasking(i);
		ImageIO io;
		std::string fileName = std::to_string(i);
		fileName += ".bmp";
		io.ImageSave(fileName, BitConvertToGray(temp));
	}
}
void openqr::QRCode::GenerateQRCodeTest()
{
	GenerateQRCode("https://github.com/MrDxxK");
	std::string LvQ_formatInfoString[8] = { "011010101011111","011000001101000",
		"011111100110001","011101000000110","010010010110100","010000110000011",
		"010111011011010","010101111101101" };
	std::vector<Matrix<int>> maskedData(8);
	int bestMaskNumber = 0;
	for (int i = 0; i < 8; ++i)
	{
		maskedData[i].Resize(25, 25, 0);
		Matrix<int> dataMaskingPatterns = DataMasking(i);
		for (int x = 0; x < 25; ++x)
		{
			for (int y = 0; y < 25; ++y)
			{
				maskedData[i](x, y) = functionPatterns(x, y) ^ dataMaskingPatterns(x, y);
			}
		}

		int pos = 0;
		
		for (int y = 0; y <=6 ; ++y)
		{
			maskedData[i](8, y) = LvQ_formatInfoString[i][pos++]-'0';
		}
		for (int x = 17; x <25; ++x)
			maskedData[i](x, 16) = LvQ_formatInfoString[i][pos++] - '0';
		pos = 0;
		
		for (int x = 0; x <=8; ++x)
		{
			if (x != 6)
				maskedData[i](x, 16) = LvQ_formatInfoString[i][pos++]-'0';
		}
		for (int y = 17; y <25; ++y)
		{
			if (y != 18)
				maskedData[i](8, y) = LvQ_formatInfoString[i][pos++] - '0';
		}
		ImageIO io;
		std::string fileName = std::to_string(i);
		fileName = "data"+fileName+".bmp";
		io.ImageSave(fileName, BitConvertToGray(maskedData[i]));

		//Evalute all 8 penalties and confirm best MaskID
		//maskMode=bestMaskNumber;
		//functionPattrens=maskedData[bestMaskNumber];
	}
}
void openqr::QRCode::MatrixDataInitlize()
{
	GenerateFunctionPatterns();
	GenerateDataAreaMask();
}
//Use 2-Q specification
void openqr::QRCode::GenerateFunctionPatterns()
{
	functionPatterns.Resize(25, 25, 100);//Default 100 to test
	AddFinderPatterns(0,24);
	AddFinderPatterns(0,6);
	AddFinderPatterns(25-7,24);
	AddSeparators();
	AddAlignmentPatterns(18,6);
	ReserveFormatArea();
	AddTimingPatterns();
	//Add dark module
	functionPatterns(8, 7) = 1;
	//ReserveVersionArea();
}

void openqr::QRCode::AddFinderPatterns(int x, int y)
{
	for (int i = 0; i < 7; ++i)
		for (int j = 0; j < 7; ++j)
			functionPatterns(x + i, y - j) = 0;
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
	for (int i = -2; i <= 2; ++i)
		for (int j = -2; j <= 2; ++j)
			functionPatterns(centerx + i, centery + j) = 0;
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
		functionPatterns(7 + i, 18) = i % 2;
}
//Only For Version2
std::string openqr::QRCode::GenerateFinalBits(const std::string & message)
{
	DataEncoder dataEncoder;
	std::string encodeWith2_QStandard = dataEncoder.Encode2_Q(message);
	const int MessageLength = 22;
	uint8_t EncodeCoeff[22];
	for (int i = 0; i < 22; ++i)
	{
		std::string temp = encodeWith2_QStandard.substr(8 * i, 8);
		std::bitset<8>tempBit(temp);
		//std::cout << temp << "  " << tempBit.to_ulong() << std::endl;
		EncodeCoeff[i] = tempBit.to_ulong();
	}
	const int EccLength = 22;
	uint8_t* encoded = new uint8_t[EccLength + MessageLength];
	RS::ReedSolomon<MessageLength, EccLength> rsencoder;
	rsencoder.Encode(EncodeCoeff, encoded);

	int standardEncoded[44];
	std::string finalBits;
	for (int i = 0; i < 44; ++i)
	{
		standardEncoded[i] = encoded[i];
		std::bitset<8>tempBit(standardEncoded[i]);
		finalBits += tempBit.to_string();
	}
	//for (int i = 0; i < 44; ++i)
	//{
	//	std::string temp = finalBits.substr(8 * i, 8);
	//	std::bitset<8>tempBit(temp);
	//	std::cout << temp << "  " << tempBit.to_ulong() << std::endl;
	//}
	//Add remainder bits
	finalBits += "0000000";
	delete[] encoded;
	encoded = nullptr;
	return finalBits;
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

void openqr::QRCode::GenerateDataAreaMask()
{
	dataAreaMask.Resize(25, 25, 0);
	for(int i=0;i<25;++i)
		for (int j = 0; j < 25; ++j)
		{
			if (functionPatterns(i, j) == 100)
				dataAreaMask(i, j) = 1;
		}
}

void openqr::QRCode::PlaceMessage(const std::string & message)
{
	std::string finalBits = GenerateFinalBits(message);
	int nowPos = 0;
	for (int x = 24; x >= 7; x -= 2)
	{
		if (x % 4 == 0)//upwards
		{
			for (int y = 0; y < 25; ++y)
			{
				if (functionPatterns(x, y) == 100)
					functionPatterns(x, y) = finalBits[nowPos++] - '0';
				if (functionPatterns(x - 1, y) == 100)
					functionPatterns(x - 1, y) = finalBits[nowPos++] - '0';
			}
		}
		else//downwards
		{
			for (int y = 24; y >= 0; --y)
			{
				if (functionPatterns(x, y) == 100)
					functionPatterns(x, y) = finalBits[nowPos++] - '0';
				if (functionPatterns(x - 1, y) == 100)
					functionPatterns(x - 1, y) = finalBits[nowPos++] - '0';
			}
		}
	}
	//After the Vertical Timing Pattern
	for (int x = 5; x >= 0; x -= 2)
	{
		if (x % 4 == 1)//upwards
		{
			for (int y = 0; y < 25; ++y)
			{
				if (functionPatterns(x, y) == 100)
					functionPatterns(x, y) = finalBits[nowPos++] - '0';
				if (functionPatterns(x - 1, y) == 100)
					functionPatterns(x - 1, y) = finalBits[nowPos++] - '0';
			}
		}
		else//downwards
		{
			for (int y = 24; y >= 0; --y)
			{
				if (functionPatterns(x, y) == 100)
					functionPatterns(x, y) = finalBits[nowPos++] - '0';
				if (functionPatterns(x - 1, y) == 100)
					functionPatterns(x - 1, y) = finalBits[nowPos++] - '0';
			}
		}
	}
}

void openqr::QRCode::MaskingEvalute()
{
	std::vector<Matrix<int>> maskedData(8);
	int bestMaskNumber = 0;
	for (int i = 0; i < 8; ++i)
	{
		maskedData[i].Resize(25, 25, 0);
		Matrix<int> dataMaskingPatterns = DataMasking(i);
		for (int x = 0; x < 25; ++x)
		{
			for (int y = 0; y < 25; ++y)
			{
				maskedData[i](x, y) = functionPatterns(x, y) ^ dataMaskingPatterns(x, y);
			}
		}
		//ImageIO io;
		//std::string fileName = std::to_string(i);
		//fileName += "data.bmp";
		//io.ImageSave(fileName, BitConvertToGray(maskedData[i]));
		
		//Evalute all 8 penalties and confirm best MaskID
		//maskMode=bestMaskNumber;
		//functionPattrens=maskedData[bestMaskNumber];
	}

}
void openqr::QRCode::AddFormatInformation()
{
	AddFormatInformation(maskMode);
}
void openqr::QRCode::AddFormatInformation(int bestMaskID)
{
	std::string LvQ_formatInfoString[8] = { "011010101011111","011000001101000",
		"011111100110001","011101000000110","010010010110100","010000110000011",
	"010111011011010","010101111101101" };
	int pos = 0;
	for (int y = 0; y < 7; ++y)
	{
		functionPatterns(8, y) = LvQ_formatInfoString[bestMaskID][pos++];
	}
	for (int x = 17; x < 25; ++x)
		functionPatterns(x, 16) = LvQ_formatInfoString[bestMaskID][pos++];

	pos = 0;
	for (int x = 0; x <= 8; ++x)
	{
		if (x != 6)
			functionPatterns(x, 16) = LvQ_formatInfoString[bestMaskID][pos++];	
	}
	for (int y = 17; y < 25; ++y)
	{
		if(y!=18)
			functionPatterns(8, y) = LvQ_formatInfoString[bestMaskID][pos++];
	}
}

openqr::Matrix<int> openqr::QRCode::DataMasking(int maskNumber)
{
	int row = 24;
	int column = 24;
	Matrix<int> mask(25, 25, 0);
	switch (maskNumber)
	{
	case 0:
		for (int x = 0; x < 25; ++x)
			for (int y = 0; y < 25; ++y)
			{
				int col = x;
				int row = 24 - y;
				if ((row + col) % 2 == 0)
					mask(x, y) = 1;
			}
		break;
	case 1:
		for (int x = 0; x < 25; ++x)
			for (int y = 0; y < 25; ++y)
			{
				int col = x;
				int row = 24 - y;
				if (row % 2 == 0)
					mask(x, y) = 1;
			}
		break;
	case 2:
		for (int x = 0; x < 25; ++x)
			for (int y = 0; y < 25; ++y)
			{
				int col = x;
				int row = 24 - y;
				if (col % 3 == 0)
					mask(x, y) = 1;
			}
		break;
	case 3:
		for (int x = 0; x < 25; ++x)
			for (int y = 0; y < 25; ++y)
			{
				int col = x;
				int row = 24 - y;
				if ((row+col) % 3 == 0)
					mask(x, y) = 1;
			}
		break;
	case 4:
		for (int x = 0; x < 25; ++x)
			for (int y = 0; y < 25; ++y)
			{
				int col = x;
				int row = 24 - y;
				if ((row/2 + col/3) % 2 == 0)
					mask(x, y) = 1;
			}
		break;
	case 5:
		for (int x = 0; x < 25; ++x)
			for (int y = 0; y < 25; ++y)
			{
				int col = x;
				int row = 24 - y;
				if (((row*col)%2)+((row*col)%3) == 0)
					mask(x, y) = 1;
			}
		break;
	case 6:
		for (int x = 0; x < 25; ++x)
			for (int y = 0; y < 25; ++y)
			{
				int col = x;
				int row = 24 - y;
				if (((row*col) % 2) + ((row*col) % 3)%2 == 0)
					mask(x, y) = 1;
			}
		break;
	case 7:
		for (int x = 0; x < 25; ++x)
			for (int y = 0; y < 25; ++y)
			{
				int col = x;
				int row = 24 - y;
				if (((row+col) % 2) + ((row*col) % 3)%2 == 0)
					mask(x, y) = 1;
			}
		break;
	}
	for(int i=0;i<25;++i)
		for (int j = 0; j < 25; ++j)
		{
			mask(i, j) = mask(i, j)&dataAreaMask(i, j);
		}
	return mask;
}
