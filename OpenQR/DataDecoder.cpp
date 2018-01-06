#include "DataDecoder.h"



DataDecoder::DataDecoder()
{
}


DataDecoder::~DataDecoder()
{
}

std::string DataDecoder::ReverseMap(int i)
{
	if (i < 0 || i>44)
		throw("para i Out of range");
	std::string result;
	if (i >= 0 && i <= 9)
	{
		result += i + '0';
		return result;
	}
	if (i >= 10 && i <= 35)
	{
		result += i - 10 + 'A';
		return result;
	}
	const char* mapChar = " $%*+-./:";
	if (i <= 44 && i >= 36)
	{
		result += mapChar[i - 36];
		return result;
	}

}
