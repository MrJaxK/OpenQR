#pragma once
#include"IImageIn.hpp"
#include"IImageOut.hpp"
#include"Matrix.hpp"
#include<string>
namespace openqr
{
	template<typename T>
	class IImageIO:public IImageIn<T>,public IImageOut<T>
	{
	public:
		IImageIO();
		
		virtual Matrix<T> ImageRead(const std::string& filePath)= 0;
		virtual bool ImageSave(const std::string& filePath) = 0;
		~IImageIO();
	};
}
