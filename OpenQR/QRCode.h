#pragma once
#include"core.h"
namespace openqr
{
	class QRCode
	{
	public:
		QRCode();
		~QRCode();
		Matrix<int>BitConvertToGray();
		
	private:
		Matrix<int>functionPatterns;
		void GenerateFunctionPatterns();//Use 2-Q specification
		void AddFinderPatterns(int x,int y);
		void AddSeparators();
		void AddAlignmentPatterns(int centerx,int centery);
		void AddTimingPatterns();
	};
}
