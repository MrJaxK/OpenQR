#include "DataEncoder.h"



DataEncoder::DataEncoder()
{
}


DataEncoder::~DataEncoder()
{
}

std::string DataEncoder::Encode2_Q(const std::string & message)
{
	if (message.size() > 29)
		throw("SIZE_OUT_OF_RANGE");
	const int bitLength = 22 * 8;
	std::string anModeCode = AlphanumericModeEncoding(message);
	std::bitset<9> characterCount(message.size());
	std::string appendModeIndi = "0010"+characterCount.to_string()+anModeCode;
	//Add a Terminator of 0s if Necessary
	int deltaLength = bitLength - appendModeIndi.length();
	if (deltaLength <= 4)
	{
		for (int i = 0; i < deltaLength; ++i)
			appendModeIndi += "0";
	}
	else
		appendModeIndi += "0000";
	//Add More 0s to Make the Length a Multiple of 8
	int mod8 = appendModeIndi.length() % 8;
	for (int i = 0; i < 8 - mod8; ++i)
		appendModeIndi += "0";
	//Add Pad Bytes if the String is Still too Short
	const std::string repeat1 = "11101100";
	const std::string repeat2 = "00010001";
	int deltaBit = bitLength - appendModeIndi.length();
	for (int i = 0; i < deltaBit / 8; ++i)
	{
		if (i % 2 == 0)
			appendModeIndi += repeat1;
		else
			appendModeIndi += repeat2;
	}
	return appendModeIndi;
}

std::string DataEncoder::AlphanumericModeEncoding(std::string message)
{
	std::string result;
	std::transform(message.begin(), message.end(),message.begin(), ::toupper);
	int i = 0;
	for (; i < message.length()-1; i += 2)
	{
		unsigned long long temp = 45 * Map(message[i]) + Map(message[i + 1]);
		std::bitset<11> biTemp(temp);
		result += biTemp.to_string();
		//result += " ";
	}
	if (i == message.length() - 1)
	{
		unsigned long long temp = Map(message[i]);
		std::bitset<6> biTemp(temp);
		result += biTemp.to_string();
		//result += " ";
	}
	return result;
}

unsigned long long DataEncoder::Map(char a)
{
	if (a <= '9'&&a >= '0')
		return a - '0';
	if (a <= 'Z'&&a >= 'A')
		return a - 55;
	else
	{
		for (int i = 0; i <= 9; ++i)
			if (a == mapChar[i])
				return i + 36;
	}
		return 100;
}
