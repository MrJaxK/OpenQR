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
	std::string LvQ_formatInfoString[8] = { "011010101011111","011000001101000",
		"011111100110001","011101000000110","010010010110100","010000110000011",
		"010111011011010","010101111101101" };
	std::vector<Matrix<int>> maskedData(8);
	int evaluteCount[8] = { 0 };
	int bestMaskNumber = 0;
	int minCount = 9999999;
	//Data masking
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

		for (int y = 0; y <= 6; ++y)
			maskedData[i](8, y) = LvQ_formatInfoString[i][pos++] - '0';
		for (int x = 17; x <25; ++x)
			maskedData[i](x, 16) = LvQ_formatInfoString[i][pos++] - '0';
		pos = 0;

		for (int x = 0; x <= 8; ++x)
		{
			if (x != 6)
				maskedData[i](x, 16) = LvQ_formatInfoString[i][pos++] - '0';
		}
		for (int y = 17; y <25; ++y)
		{
			if (y != 18)
				maskedData[i](8, y) = LvQ_formatInfoString[i][pos++] - '0';
		}
		
		//Evalute all 8 penalties and confirm best MaskID
		evaluteCount[i] = EvaluteMaskQuality(maskedData[i]);

		if (evaluteCount[i] < minCount)
		{
			minCount = evaluteCount[i];
			bestMaskNumber = i;
		}

	}
	maskMode = bestMaskNumber;
	functionPatterns = maskedData[bestMaskNumber];
	return true;
}
std::string openqr::QRCode::DecodeQRCode(Matrix<int> mat)
{
	if (mat.getColNumber() != 400 || mat.getRowNumber() != 400)
		throw("Matrix size unfit");
	BinaryzationBigMat(mat);
	Demasking();
	return DecodeCore();
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
	std::string message = "MrK";
	MatrixDataInitlize();
	PlaceMessage(message);
	std::string LvQ_formatInfoString[8] = { "011010101011111","011000001101000",
		"011111100110001","011101000000110","010010010110100","010000110000011",
		"010111011011010","010101111101101" };
	std::vector<Matrix<int>> maskedData(8);
	int evaluteCount[8] = { 0 };
	int bestMaskNumber = 0;
	int minCount = 9999999;
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
		//io.ImageSave("mask"+std::to_string(i)+".bmp", BitConvertToGray(dataMaskingPatterns));
		//Evalute all 8 penalties and confirm best MaskID
		evaluteCount[i] = EvaluteMaskQuality(maskedData[i]);
		
		if (evaluteCount[i] < minCount)
		{
			minCount = evaluteCount[i];
			bestMaskNumber = i;
		}
		
	}
	maskMode=bestMaskNumber;
	std::cout << "Mask Mode is: "<<maskMode << std::endl;
	functionPatterns=maskedData[bestMaskNumber];
}
std::string openqr::QRCode::DecodeQRCodeTest(Matrix<int> mat)
{
	
	//binaryzation
	MatrixDataInitlize();
	functionPatterns.Resize(25, 25);
	maskMode = -1;
	const int threshold = 16 * 16 * 255 / 2;
	for (int x = 0; x < 400; x += 16)
	{
		for (int y = 0; y < 400; y += 16)
		{
			int totalGray = 0;
			for(int i=0;i<16;++i)
				for (int j = 0; j < 16; ++j)
				{
					totalGray += mat(x + i, y + j);
				}
			if (totalGray > threshold)
			{
				functionPatterns(x / 16, y / 16) = 0;
			}
			else
			{
				functionPatterns(x / 16, y / 16) = 1;
			}
		}
	}
	//Find mask mode
	//Asuming both of the mask mode codeword is correct
	std::string LvQ_formatInfoString[8] = { "011010101011111","011000001101000",
		"011111100110001","011101000000110","010010010110100","010000110000011",
		"010111011011010","010101111101101" };
	std::string maskCodeword;
	for (int y = 0; y <= 6; ++y)
		maskCodeword+=functionPatterns(8, y)+'0';
	for (int x = 17; x <25; ++x)
		maskCodeword+=functionPatterns(x, 16)+'0';
	for(int i=0;i<8;++i)
		if (maskCodeword == LvQ_formatInfoString[i])
		{
			maskMode = i;
			break;
		}
	//Demasking
	Matrix<int> mask = DataMasking(maskMode);
	for (int x = 0; x < 25; ++x)
	{
		for (int y = 0; y < 25; ++y)
		{
			functionPatterns(x, y) ^= mask(x, y);
		}
	}
	//Read message+Ecc
	std::string finalBits;
	for (int x = 24; x >= 7; x -= 2)
	{
		if (x % 4 == 0)//upwards
		{
			for (int y = 0; y < 25; ++y)
			{
				if (dataAreaMask(x, y) == 1)
					finalBits+=functionPatterns(x, y) + '0';
				if (dataAreaMask(x - 1, y) == 1)
					finalBits+=functionPatterns(x - 1, y)+ '0';
			}
		}
		else//downwards
		{
			for (int y = 24; y >= 0; --y)
			{
				if (dataAreaMask(x, y) == 1)
					finalBits+=functionPatterns(x, y) + '0';
				if (dataAreaMask(x - 1, y) == 1)
					finalBits+=functionPatterns(x - 1, y) + '0';
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
				if (dataAreaMask(x, y) == 1)
					finalBits+=functionPatterns(x, y) + '0';
				if (dataAreaMask(x - 1, y) == 1)
					finalBits+=functionPatterns(x - 1, y) + '0';
			}
		}
		else//downwards
		{
			for (int y = 24; y >= 0; --y)
			{
				if (dataAreaMask(x, y) == 1)
					finalBits+=functionPatterns(x, y) + '0';
				if (dataAreaMask(x - 1, y) == 1)
					finalBits += functionPatterns(x - 1, y) + '0';
			}
		}
	}
	//Correcting the message
	const int MessageLength = 22;
	const int EccLength = 22;
	uint8_t encoded[44];
	for (int i = 0; i < 44; ++i)
	{
		std::string temp = finalBits.substr(8 * i, 8);
		std::bitset<8>tempBit(temp);
		encoded[i] = tempBit.to_ulong();
	}
	RS::ReedSolomon<MessageLength, EccLength> rsDecoder;
	uint8_t repaired[22];
	rsDecoder.Decode(encoded, repaired);
	std::string repairedMessage;
	for (int i = 0; i < 22; ++i)
	{
		std::bitset<8>tempBit(repaired[i]);
		repairedMessage += tempBit.to_string();
	}
	//Decode Alphanumeric Mode codeword
	if (repairedMessage.substr(0, 4) != "0010")
		throw("Not supported encoded mode.\nOnly support Alphanumeric Mode");
	std::bitset<9> characterCount(repairedMessage.substr(4, 9));
	int messageSize = characterCount.to_ulong();
	std::string finalMessage;
	//Starts form repairedMessage[13]
	DataDecoder decoder;
	int i = 0;
	for (; i < messageSize - 1; i+=2)
	{
		//All the letters are combined two by two. Each of the combination cost 11 bits
		std::bitset<11>tempBits(repairedMessage.substr(13 + 11 * (i / 2), 11));
		int temp = tempBits.to_ulong();
		finalMessage += decoder.ReverseMap(temp / 45) + decoder.ReverseMap(temp % 45);
	}
	//One letter in the end, 6 bits
	//last one letter	
	if (i == messageSize - 1)
	{
		std::bitset<6>tempBits(repairedMessage.substr(13 + 11 * (i / 2), 6));
		int temp = tempBits.to_ulong();
		finalMessage += decoder.ReverseMap(temp);
	}
	
	std::cout << finalMessage;
	return finalMessage;
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
int openqr::QRCode::EvaluteMaskQuality(Matrix<int> masked)
{
	int total = 0;

	//Penalty Rule 1
	int penalty1 = 0;
	//Check rows
	for (int y = 0; y < 25; ++y)
	{
		int first = 0, last = 0;
		for (int x = 1; x < 25; ++x)
		{
			if (masked(x, y) == masked(x - 1, y))
				last = x;
			else
			{
				if (last - first >= 4)
					penalty1 += last - first - 1;
				else
				{
					first = x;
					last = x;
				}
			}
		}
		//x==24. Boundary conditions
		if (last - first >= 4)
			penalty1 += last - first - 1;
	}
	//Check column
	for (int x = 0; x < 25; ++x)
	{
		int first = 0, last = 0;
		for (int y = 1; y < 25; ++y)
		{
			if (masked(x, y) == masked(x , y - 1))
				last = y;
			else
			{
				if (last - first >= 4)
					penalty1 += last - first - 1;
				else
				{
					first = y;
					last = y;
				}
			}
		}
		//y==24
		if (last - first >= 4)
			penalty1 += last - first - 1;
	}

	//Penalty Rule 2
	int penalty2 = 0;
	for (int x = 0; x < 24; ++x)
	{
		for (int y = 0; y < 24; ++y)
		{
			if (masked(x, y) == masked(x, y + 1) &&
				masked(x + 1, y) == masked(x, y) &&
				masked(x, y) == masked(x + 1, y + 1))
				penalty2 += 3;
		}
	}

	//Penalty Rule 3
	int penalty3 = 0;
	const int rulePattern[2][11] = { {1,0,1,1,1,0,1,0,0,0,0},{0,0,0,0,1,0,1,1,1,0,1} };
	//Check row
	for (int y = 0; y < 25; ++y)
	{
		for (int x = 0; x <= 14; ++x)
		{

			for (int index = 0; index < 2; ++index)
			{
				bool flag = true;
				for (int i = 0; i < 11; ++i)
				{
					if (masked(x + i, y) != rulePattern[index][i])
					{
						flag = false;
						break;
					}
				}
				if (flag)
					penalty3 += 40;
			}

		}
	}
	//Check column
	for (int x = 0; x < 25; ++x)
	{
		for (int y = 0; y <= 14; ++y)
		{

			for (int index = 0; index < 2; ++index)
			{
				bool flag = true;
				for (int i = 0; i < 11; ++i)
				{
					if (masked(x , y + i) != rulePattern[index][i])
					{
						flag = false;
						break;
					}
				}
				if (flag)
					penalty3 += 40;
			}

		}
	}

	//Penalty Rule 4
	int penalty4 = 0;
	const int totalMods = 25 * 25;
	int darkMods = 0;
	for (int x = 0; x < 25; ++x)
		for (int y = 0; y < 25; ++y)
			darkMods += masked(x, y);
	double darkRatio = 100 * darkMods / totalMods;//   darkRatio%
	int darkRatioInt = static_cast<int>(darkRatio);
	int d5 = darkRatioInt / 5;
	int prev = d5 * 5; int next = d5 * 5 + 5;
	prev = abs(prev - 50) / 5;
	next = abs(next - 50) / 5;
	penalty4 = (prev > next ? next : prev) * 10;
	
	total = penalty1 + penalty2 + penalty3 + penalty4;
	return total;
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
				int column = x;
				int row = 24 - y;
				if ((((row * column) % 2) + ((row * column) % 3))% 2 == 0)
					mask(x, y) = 1;
			}
		break;
	case 7:
		for (int x = 0; x < 25; ++x)
			for (int y = 0; y < 25; ++y)
			{
				int column = x;
				int row = 24 - y;
				if ((((row + column) % 2) + ((row * column) % 3)) % 2 == 0)
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

inline std::string openqr::QRCode::DecodeCore()
{
	//Read message+Ecc
	std::string finalBits;
	for (int x = 24; x >= 7; x -= 2)
	{
		if (x % 4 == 0)//upwards
		{
			for (int y = 0; y < 25; ++y)
			{
				if (dataAreaMask(x, y) == 1)
					finalBits += functionPatterns(x, y) + '0';
				if (dataAreaMask(x - 1, y) == 1)
					finalBits += functionPatterns(x - 1, y) + '0';
			}
		}
		else//downwards
		{
			for (int y = 24; y >= 0; --y)
			{
				if (dataAreaMask(x, y) == 1)
					finalBits += functionPatterns(x, y) + '0';
				if (dataAreaMask(x - 1, y) == 1)
					finalBits += functionPatterns(x - 1, y) + '0';
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
				if (dataAreaMask(x, y) == 1)
					finalBits += functionPatterns(x, y) + '0';
				if (dataAreaMask(x - 1, y) == 1)
					finalBits += functionPatterns(x - 1, y) + '0';
			}
		}
		else//downwards
		{
			for (int y = 24; y >= 0; --y)
			{
				if (dataAreaMask(x, y) == 1)
					finalBits += functionPatterns(x, y) + '0';
				if (dataAreaMask(x - 1, y) == 1)
					finalBits += functionPatterns(x - 1, y) + '0';
			}
		}
	}
	//Correcting the message
	const int MessageLength = 22;
	const int EccLength = 22;
	uint8_t encoded[44];
	for (int i = 0; i < 44; ++i)
	{
		std::string temp = finalBits.substr(8 * i, 8);
		std::bitset<8>tempBit(temp);
		encoded[i] = tempBit.to_ulong();
	}
	RS::ReedSolomon<MessageLength, EccLength> rsDecoder;
	uint8_t repaired[22];
	rsDecoder.Decode(encoded, repaired);
	std::string repairedMessage;
	for (int i = 0; i < 22; ++i)
	{
		std::bitset<8>tempBit(repaired[i]);
		repairedMessage += tempBit.to_string();
	}
	//Decode Alphanumeric Mode codeword
	if (repairedMessage.substr(0, 4) != "0010")
		throw("Not supported encoded mode.\nOnly support Alphanumeric Mode");
	std::bitset<9> characterCount(repairedMessage.substr(4, 9));
	int messageSize = characterCount.to_ulong();
	std::string finalMessage;
	//Starts form repairedMessage[13]
	DataDecoder decoder;
	int i = 0;
	for (; i < messageSize - 1; i += 2)
	{
		//All the letters are combined two by two. Each of the combination cost 11 bits
		std::bitset<11>tempBits(repairedMessage.substr(13 + 11 * (i / 2), 11));
		int temp = tempBits.to_ulong();
		finalMessage += decoder.ReverseMap(temp / 45) + decoder.ReverseMap(temp % 45);
	}
	//One letter in the end, 6 bits
	//last one letter	
	if (i == messageSize - 1)
	{
		std::bitset<6>tempBits(repairedMessage.substr(13 + 11 * (i / 2), 6));
		int temp = tempBits.to_ulong();
		finalMessage += decoder.ReverseMap(temp);
	}
	return finalMessage;
}

//std::string openqr::QRCode::DecodeCore(Matrix<int> mat)
//{
//	if (mat.getRowNumber() != 25 || mat.getColNumber() != 25)
//		throw("Mat size unfit");
//	//Read message+Ecc
//	std::string finalBits;
//	for (int x = 24; x >= 7; x -= 2)
//	{
//		if (x % 4 == 0)//upwards
//		{
//			for (int y = 0; y < 25; ++y)
//			{
//				if (dataAreaMask(x, y) == 1)
//					finalBits += mat(x, y) + '0';
//				if (dataAreaMask(x - 1, y) == 1)
//					finalBits += mat(x - 1, y) + '0';
//			}
//		}
//		else//downwards
//		{
//			for (int y = 24; y >= 0; --y)
//			{
//				if (dataAreaMask(x, y) == 1)
//					finalBits += mat(x, y) + '0';
//				if (dataAreaMask(x - 1, y) == 1)
//					finalBits += mat(x - 1, y) + '0';
//			}
//		}
//	}
//	//After the Vertical Timing Pattern
//	for (int x = 5; x >= 0; x -= 2)
//	{
//		if (x % 4 == 1)//upwards
//		{
//			for (int y = 0; y < 25; ++y)
//			{
//				if (dataAreaMask(x, y) == 1)
//					finalBits += mat(x, y) + '0';
//				if (dataAreaMask(x - 1, y) == 1)
//					finalBits += mat(x - 1, y) + '0';
//			}
//		}
//		else//downwards
//		{
//			for (int y = 24; y >= 0; --y)
//			{
//				if (dataAreaMask(x, y) == 1)
//					finalBits += mat(x, y) + '0';
//				if (dataAreaMask(x - 1, y) == 1)
//					finalBits += mat(x - 1, y) + '0';
//			}
//		}
//	}
//	//Correcting the message
//	const int MessageLength = 22;
//	const int EccLength = 22;
//	uint8_t encoded[44];
//	for (int i = 0; i < 44; ++i)
//	{
//		std::string temp = finalBits.substr(8 * i, 8);
//		std::bitset<8>tempBit(temp);
//		encoded[i] = tempBit.to_ulong();
//	}
//	RS::ReedSolomon<MessageLength, EccLength> rsDecoder;
//	uint8_t repaired[22];
//	rsDecoder.Decode(encoded, repaired);
//	std::string repairedMessage;
//	for (int i = 0; i < 22; ++i)
//	{
//		std::bitset<8>tempBit(repaired[i]);
//		repairedMessage += tempBit.to_string();
//	}
//	//Decode Alphanumeric Mode codeword
//	if (repairedMessage.substr(0, 4) != "0010")
//		throw("Not supported encoded mode.\nOnly support Alphanumeric Mode");
//	std::bitset<9> characterCount(repairedMessage.substr(4, 9));
//	int messageSize = characterCount.to_ulong();
//	std::string finalMessage;
//	//Starts form repairedMessage[13]
//	DataDecoder decoder;
//	int i = 0;
//	for (; i < messageSize - 1; i += 2)
//	{
//		//All the letters are combined two by two. Each of the combination cost 11 bits
//		std::bitset<11>tempBits(repairedMessage.substr(13 + 11 * (i / 2), 11));
//		int temp = tempBits.to_ulong();
//		finalMessage += decoder.ReverseMap(temp / 45) + decoder.ReverseMap(temp % 45);
//	}
//	//One letter in the end, 6 bits
//	//last one letter	
//	if (i == messageSize - 1)
//	{
//		std::bitset<6>tempBits(repairedMessage.substr(13 + 11 * (i / 2), 6));
//		int temp = tempBits.to_ulong();
//		finalMessage += decoder.ReverseMap(temp);
//	}
//}

void openqr::QRCode::BinaryzationBigMat(Matrix<int> mat)
{
	//binaryzation
	MatrixDataInitlize();
	functionPatterns.Resize(25, 25);
	maskMode = -1;
	const int threshold = 16 * 16 * 255 / 2;
	for (int x = 0; x < 400; x += 16)
	{
		for (int y = 0; y < 400; y += 16)
		{
			int totalGray = 0;
			for (int i = 0; i<16; ++i)
				for (int j = 0; j < 16; ++j)
				{
					totalGray += mat(x + i, y + j);
				}
			if (totalGray > threshold)
			{
				functionPatterns(x / 16, y / 16) = 0;
			}
			else
			{
				functionPatterns(x / 16, y / 16) = 1;
			}
		}
	}
}

void openqr::QRCode::Demasking()
{
	//Find mask mode
	//Asuming both of the mask mode codeword is correct
	std::string LvQ_formatInfoString[8] = { "011010101011111","011000001101000",
		"011111100110001","011101000000110","010010010110100","010000110000011",
		"010111011011010","010101111101101" };
	std::string maskCodeword;
	for (int y = 0; y <= 6; ++y)
		maskCodeword += functionPatterns(8, y) + '0';
	for (int x = 17; x <25; ++x)
		maskCodeword += functionPatterns(x, 16) + '0';
	for (int i = 0; i<8; ++i)
		if (maskCodeword == LvQ_formatInfoString[i])
		{
			maskMode = i;
			break;
		}

	//Demasking
	Matrix<int> mask = DataMasking(maskMode);
	for (int x = 0; x < 25; ++x)
	{
		for (int y = 0; y < 25; ++y)
		{
			functionPatterns(x, y) ^= mask(x, y);
		}
	}
}
