#pragma once
#include"IImageIn.h"
#include"IImageOut.h"
#include"Matrix.h"
#include<string>
namespace openqr
{
	class IImageIO:public IImageIn,public IImageOut
	{
	public:
		IImageIO();
		template<typename T>
			virtual Matrix<T> ImageRead(const std::string& filePath)override = 0;
		virtual bool ImageSave(const std::string& filePath)override = 0;
		~IImageIO();
	};
}
