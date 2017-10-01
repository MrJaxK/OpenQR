#pragma once
#include<string>
#include"Matrix.h"
namespace openqr
{
	class IImageIn
	{
	public:
		IImageIn();
		virtual Matrix ImageRead(const std::string& filePath) = 0;
		~IImageIn();
	};
}

