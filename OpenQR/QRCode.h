#pragma once
#include"core.h"
#include<string>
#include<bitset>
namespace openqr
{
	class QRCode
	{
	public:
		QRCode();
		QRCode(const std::string& message);
		~QRCode();
		Matrix<int>BitConvertToGray();

	private:
		Matrix<int>functionPatterns;
		void GenerateFunctionPatterns();//Use 2-Q specification
		void AddFinderPatterns(int x,int y);
		void AddSeparators();
		void AddAlignmentPatterns(int centerx,int centery);
		void AddTimingPatterns();

		/*
		*Use gray 180 stand for reservation
		*Use this function before Adding Timing Patterns
		*/
		void ReserveFormatArea();
		/*
		*Use gray 50 stand for reservation
		*/
		void ReserveVersionArea();

	};
}
