#pragma once
#include "core.h"
#include <string>
#include<cstdlib>
namespace openqr
{
	template<typename T>
	class BMPImageIO :public IImageIO<T>
	{
	public:
		BMPImageIO();

		virtual Matrix<T> ImageRead(const std::string& filePath)override;
		virtual bool ImageSave(const std::string& filePath,Matrix<T>& mat)override;
		~BMPImageIO();
	//private:
		int data;
	};


	template<typename T>
	BMPImageIO<T>::BMPImageIO() :data(1)
	{
	}
	template<typename T>
	Matrix<T> openqr::BMPImageIO<T>::ImageRead(const std::string & filePath)
	{
		data = atoi(filePath.c_str());
		return Matrix<T>();
	}
	template<typename T>
	bool openqr::BMPImageIO<T>::ImageSave(const std::string & filePath,Matrix<T>& mat)
	{
		data = 3;
		return false;
	}

	template<typename T>
	BMPImageIO<T>::~BMPImageIO()
	{
	}
}

