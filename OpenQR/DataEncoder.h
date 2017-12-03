#pragma once
#include<string>
#include<bitset>
#include<vector>
#include<algorithm>
#include<cctype>
#include"core.h"
class DataEncoder
{
public:
	DataEncoder();
	~DataEncoder();
	std::string Encode2_Q(const std::string& message);
private:
	std::string AlphanumericModeEncoding(std::string message);
	unsigned long long Map(char a);
	const char* mapChar = " $%*+-./:";
};

