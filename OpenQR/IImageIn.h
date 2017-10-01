#pragma once
#include<string>
#include"Matrix.h"
namespace openqr
{
	class IImageIn
	{
	public:
		IImageIn();
		template<typename T>
			virtual Matrix<T> ImageRead(const std::string& filePath) = 0;
		~IImageIn();
	};
}

