#include <iostream>
#include <fstream>
#include <cassert>
#include "bmp.h"

BMP::BMP()
{
	head	= NULL;
	info	= NULL;
	palette = NULL;
	pixels	= NULL;

	rows = -1;
	cols = -1;
}

BMP::BMP(const std::string &location)
{
	head	= NULL;
	info	= NULL;
	palette = NULL;
	pixels	= NULL;

	rows = -1;
	cols = -1;

	this->load(location);
}

BMP::~BMP()
{
	if (pixels != NULL)
		delete[] pixels;
	if (palette != NULL)
		delete[] palette;
	if (info != NULL)
		delete info;
	if (head != NULL)
		delete head;
}

BYTE* BMP::load(const std::string &location)
{
	std::ifstream file(location, std::ios::binary);
	if(!file)
	{
		std::cout << "Failed to open bitmap file.\n";
		return NULL;
	}

	head = new BITMAPFILEHEADER;
	info = new BITMAPINFOHEADER;

	file.read((char*)head, sizeof(BITMAPFILEHEADER));
	file.read((char*)info, sizeof(BITMAPINFOHEADER));

	if(head->bfType != 0x4D42)
	{
		std::cout << "File \"" << location << "\" isn't a bitmap file\n";
		return pixels;
	}

	this->rows		= (DWORD)info->biHeight;
	this->cols		= (DWORD)info->biWidth;
	this->channels	= this->_channels();

	if (info->biBitCount == 8)
	{
		palette = new RGBQUAD[256];
		file.read((char*)palette, 256 * sizeof(RGBQUAD));
	}

	LONG size = info->biWidth * info->biHeight * this->_channels();
	pixels = new BYTE[size];

	file.seekg(head->bfOffBits, std::ios::beg);
	file.read((char*)pixels, size);


	//this->swap(&pixels, cols, rows, channels);

	return pixels;
}

bool BMP::save(const std::string &location)
{
	std::ofstream file(location, std::ios::binary);
	if (!file)
	{
		std::cout << "Failed to open or create bitmap file." << std::endl;
		return false;
	}

	if (head == NULL || info == NULL || pixels == NULL)
	{
		std::cout << "Failed to save bitmap file." << std::endl;
		return false;
	}

	file.write((char*)head, sizeof(BITMAPFILEHEADER));
	file.write((char*)info, sizeof(BITMAPINFOHEADER));

	if (info->biBitCount < 24)
		file.write((char*)palette, sizeof(RGBQUAD) * 256);

	//this->swap(&pixels, cols, rows, channels);
	file.write((char*)pixels, this->rows * this->cols * this->channels);
	//othis->swap(&pixels, cols, rows, channels);
	return true;
}

void BMP::swap(BYTE **src, DWORD width, DWORD height, WORD channel)
{
	BYTE temp;
	for (unsigned long w = 0; w < width * channel; w++)
	{
		for (DWORD i = 0, j = height - 1; i <= j; i++, j--)
		{
			temp							= (*src)[i * width * channel + w];
			(*src)[i * width * channel + w]	= (*src)[j * width * channel + w];
			(*src)[j * width * channel + w]	= temp;
		}
	}
}

LONG BMP::width()
{
	assert(info != NULL);

	return info->biWidth;
}

LONG BMP::height()
{
	assert(info != NULL);

	return info->biHeight;
}

BYTE BMP::depth()
{
	assert(info != NULL);

	if (info->biBitCount <= 8)
		return info->biBitCount;
	else
		return 8;
}

BYTE* BMP::data()
{
	return pixels;
}

WORD BMP::_channels()
{
	assert(info != NULL);

	switch (info->biBitCount)
	{
		case 1:
		case 2:
		case 4:
		case 8:
			return 1;
		case 16:
			return 2;
		case 24:
			return 3;
		case 32:
			return 4; 
	}
}
