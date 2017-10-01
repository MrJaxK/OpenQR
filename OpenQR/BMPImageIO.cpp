#include "BMPImageIO.h"
#include<cstdlib>
namespace openqr
{


	BMPImageIO::BMPImageIO()
	{
		data = 1;
	}

	Matrix openqr::BMPImageIO::ImageRead(const std::string & filePath)
	{
		data = atoi(filePath.c_str());
		return Matrix();
	}

	bool openqr::BMPImageIO::ImageSave(const std::string & filePath)
	{
		data = 3;
		return false;
	}


	BMPImageIO::~BMPImageIO()
	{
	}
}