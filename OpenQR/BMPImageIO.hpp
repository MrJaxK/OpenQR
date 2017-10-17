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
		///return a Matrix contains converted to gray bitmap
		virtual Matrix<T> ImageRead(const std::string& filePath)override;
		virtual bool ImageSave(const std::string& filePath,Matrix<T>& mat)override;
		~BMPImageIO();
	private:
		Matrix<T> Convert2Gray();
        void ConstructNewBMP(BMP* bmp,Matrix<T>& mat);
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
        BMP* bmpSaveFile=new BMP();
        ConstructNewBMP(bmpSaveFile,mat);
		if (bmpSaveFile->pixels == nullptr)
			return false;
		BYTE* ImgValue_s = bmpSaveFile->pixels;
		int height = bmpSaveFile->info->biHeight;
		int width = bmpSaveFile->info->biWidth;
		for (int y = 0; y <height; y++) {
			for (int x = 0; x < width; x++) {
				BYTE gray = mat(y, x);
				ImgValue_s[3 * (width*y + x) + 2] = gray;
				ImgValue_s[3 * (width*y + x) + 1] = gray;
				ImgValue_s[3 * (width*y + x) + 0] = gray;
			}
		}
        bool saveFlag=bmpSaveFile->save(filePath);
        delete bmpSaveFile;
		return saveFlag;
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
    template <typename T>
    void BMPImageIO<T>::ConstructNewBMP(BMP* bmpSaveFile,Matrix<T>& mat) {
        bmpSaveFile->head=new BITMAPFILEHEADER;
        bmpSaveFile->info = new BITMAPINFOHEADER;

        bmpSaveFile->head->bfType=0x4d42;
        //Only save 3 channels bmp image. In other words, biBitCount=24.
        bmpSaveFile->head->bfSize= 54+mat.getColNumber()*mat.getRowNumber()*3;
        bmpSaveFile->head->bfReserved1=0;
        bmpSaveFile->head->bfReserved2=0;
        bmpSaveFile->head->bfOffBits=54;

        bmpSaveFile->info->biSize=40;
        bmpSaveFile->info->biWidth=mat.getColNumber();
        bmpSaveFile->info->biHeight=mat.getRowNumber();
        bmpSaveFile->info->biPlanes=1;
        bmpSaveFile->info->biBitCount=24;
        bmpSaveFile->info->biCompression=0;
        bmpSaveFile->info->biSizeImage=mat.getRowNumber()*mat.getColNumber()*3;
        bmpSaveFile->info->biXPelsPerMeter=4724;
        bmpSaveFile->info->biYPelsPerMeter=4724;
        bmpSaveFile->info->biClrUsed=0;
        bmpSaveFile->info->biClrImportant=0;

        bmpSaveFile->rows=bmpSaveFile->info->biHeight;
        bmpSaveFile->cols=bmpSaveFile->info->biWidth;
        bmpSaveFile->channels=3;
        bmpSaveFile->palette= nullptr;
        bmpSaveFile->pixels=new BYTE[mat.getColNumber()*mat.getRowNumber()*3];

    }
}

