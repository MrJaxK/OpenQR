#pragma once
#include<string>
#include"Matrix.hpp"
namespace openqr
{
	template<typename T>
	class IImageIn
	{
	public:
		IImageIn();
		virtual Matrix<T> ImageRead(const std::string& filePath) = 0;
		~IImageIn();
	};
}

