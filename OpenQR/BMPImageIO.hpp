#pragma once
#include "core.h"
#include <string>
#include <cstdlib>
#include "bmp.h"
namespace openqr
{
	template<typename T>
	class BMPImageIO :public IImageIO<T>
	{
	public:
		BMPImageIO();
		//return a Matrix contains converted to gray bitmap
		virtual Matrix<T> ImageRead(const std::string& filePath)override;
		virtual bool ImageSave(const std::string& filePath,Matrix<T>& mat)override;
		~BMPImageIO();
	private:
		Matrix<T> Convert2Gray();
	private:
		BMP bmpData;
	};


	template<typename T>
	BMPImageIO<T>::BMPImageIO()
	{
	}
	template<typename T>
	Matrix<T> openqr::BMPImageIO<T>::ImageRead(const std::string & filePath)
	{
		bmpData.load(filePath);
		return Convert2Gray();
	}
	template<typename T>
	bool openqr::BMPImageIO<T>::ImageSave(const std::string & filePath,Matrix<T>& mat)
	{
		bmpData.save(filePath);
		return false;
	}

	template<typename T>
	BMPImageIO<T>::~BMPImageIO()
	{
	}
	template<typename T>
	inline Matrix<T> BMPImageIO<T>::Convert2Gray()
	{
		Matrix<T> grayImg(bmpData.rows, bmpData.cols,-5);
		BYTE R, G, B;
		T gray;
		BYTE* ImgValue_s = bmpData.pixels;
		int height = bmpData.rows;
		int width = bmpData.cols;
		for (int y = 0; y <height; y++) {
			for (int x = 0; x < width; x++) {

				R = ImgValue_s[3 * (width*y + x) + 2];
				G = ImgValue_s[3 * (width*y + x) + 1];
				B = ImgValue_s[3 * (width*y + x) + 0];
				//cout << (int)R << " " << (int)G << " " << (int)B << endl;
				gray = (R * 11 + G * 16 + B * 5) / 32; // define gray color
				grayImg(y,x) = gray;
			}
		}
		return grayImg;
	}
}

