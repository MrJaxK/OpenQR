#pragma once
#include<string>
#include"Matrix.hpp"
namespace openqr
{
	template<typename T>
	class IImageOut
	{
	public:
		IImageOut();
		virtual bool ImageSave(const std::string& filePath,Matrix<T>& mat)=0;
		~IImageOut();
	};
	template<typename T>
	inline IImageOut<T>::IImageOut()
	{
	}
	template<typename T>
	inline IImageOut<T>::~IImageOut()
	{
	}
}

