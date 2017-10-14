
#pragma once

#include <string>
typedef long			LONG;
typedef unsigned long	DWORD;
typedef int				BOOL;
typedef unsigned char   BYTE;
typedef unsigned short	WORD;
typedef BYTE			*LPBYTE;
typedef DWORD			*LPDWORD;


#pragma pack(1)
typedef struct tagRGBQUAD
{
	BYTE	rgbBlue;
	BYTE	rgbGreen;
	BYTE	rgbRed;
	BYTE	rgbReserved;
}RGBQUAD;

typedef struct  tagBITMAPFILEHEADER
{  
	WORD	bfType;				
	DWORD	bfSize;				
	WORD	bfReserved1;		
	WORD	bfReserved2;		
	DWORD	bfOffBits;			
}BITMAPFILEHEADER;				

typedef struct tagBITMAPINFOHEADER
{  
	DWORD	biSize;				
	LONG	biWidth;			
	LONG	biHeight;			
	WORD	biPlanes;			
	WORD	biBitCount;			
	DWORD	biCompression;		
	DWORD	biSizeImage;		
	LONG	biXPelsPerMeter;	
	LONG	biYPelsPerMeter;	
	DWORD	biClrUsed;			 
	DWORD	biClrImportant;		
}BITMAPINFOHEADER;				
#pragma pack()

// class BMP
//
// BMP is an image file format that stores bitmap digital images and retains 
// information for each pixel of the image. The BMP format stores color data 
// for each pixel in the image without any compression. For example, a 10x10 
// pixel BMP image will include color data for 100 pixels. This method of 
// storing image information allows for crisp, high-quality graphics, but 
// also produces large file sizes. 
class BMP
{
public:
	BMP();
	BMP(const std::string &location);
	~BMP();

public:
	BYTE*	load(const std::string &location);
	void	save(const std::string &location);

private:
	void	swap(BYTE **src, DWORD width, DWORD height, WORD channel);

public:
	LONG	width();
	LONG	height();
	BYTE	depth();
	BYTE*	data();
	WORD	_channels();

public:
	DWORD	rows;
	DWORD	cols;
	WORD	channels;
private:
	BITMAPFILEHEADER	*head;  
	BITMAPINFOHEADER	*info;  
	RGBQUAD				*palette;  
public:
	BYTE				*pixels;//为了让BMPImageIO.hpp读取数据

}; /* end for class BMP */
