#pragma once
///This field contains all *ImageIO.hpp
#include"BMPImageIO.hpp"
//....
#include"core.h"
#include<string>
#include<algorithm>

namespace openqr
{
	
	class ImageIO
	{

	public:
		ImageIO();
		template<typename T>
		Matrix<T> ImageRead(const std::string& filePath);
		template<typename T>
		bool ImageSave(const std::string& filePath, Matrix<T> mat);
		~ImageIO();
	private:
		enum ImageType
		{
			BMP,
			JPG,
			GIF,
			PNG,
			UNKNOWN
		};
	private:
		ImageType ImageTypeCheck(const std::string& filePath)
		{
			std::string fileSuffix = filePath.substr(filePath.find_last_of(".") + 1);
			transform(fileSuffix.begin(), fileSuffix.end(), fileSuffix.begin(), ::tolower);
			ImageType fileType;
			if (fileSuffix == "bmp")
				fileType = ImageType::BMP;
			else
				fileType=ImageType::UNKNOWN;
			return fileType;
		}
		template<typename T>
		IImageIO<T>* ImageTypeSet(ImageType& type);
		
	};
	inline ImageIO::ImageIO()
	{
	}
	inline ImageIO::~ImageIO()
	{
	}

	template<typename T>
	inline Matrix<T> ImageIO::ImageRead(const std::string & filePath)
	{
		ImageType type = ImageTypeCheck(filePath);
		IImageIO<T>* imageProcesser=ImageTypeSet<T>(type);
		Matrix<T> matImage = imageProcesser->ImageRead(filePath);
		delete imageProcesser;
		imageProcesser = nullptr;
		return matImage;
	}
	template<typename T>
	inline bool ImageIO::ImageSave(const std::string & filePath,Matrix<T> mat)
	{
		ImageType type = ImageTypeCheck(filePath);
		IImageIO<T>* imageProcesser = ImageTypeSet<T>(type);
		bool saveFlag = imageProcesser->ImageSave(filePath, mat);
		delete imageProcesser;
		imageProcesser = nullptr;
		return saveFlag;
	}

	template<typename T>
	inline IImageIO<T>* ImageIO::ImageTypeSet(ImageType & type)
	{
		if (type == ImageType::BMP)
			return new BMPImageIO<T>();
		else
			return nullptr;
	}

}