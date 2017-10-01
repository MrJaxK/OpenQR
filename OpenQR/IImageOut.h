#pragma once
#include<string>
#include"Matrix.h"
namespace openqr
{
	class IImageOut
	{
	public:
		IImageOut();
		virtual bool ImageSave(const std::string& filePath)=0;
		~IImageOut();
	};
}

