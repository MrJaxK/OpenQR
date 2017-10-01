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
		
		virtual Matrix<T> ImageRead(const std::string& filePath)override= 0;
		virtual bool ImageSave(const std::string& filePath,Matrix<T>& mat)override = 0;
		~IImageIO();
	};
	template<typename T>
	inline IImageIO<T>::IImageIO()
	{
	}
	template<typename T>
	inline IImageIO<T>::~IImageIO()
	{
	}
}
