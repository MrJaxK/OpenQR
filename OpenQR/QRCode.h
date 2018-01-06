#pragma once
#include<cmath>
#include"core.h"
#include"DataEncoder.h"
#include"SupFunction.h"
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
		Matrix<int>	BitConvertToGray();
		Matrix<int>	BitConvertToGray(Matrix<int> mat);
		bool GenerateQRCode(const std::string& message);
	//Test functions
	private:
		void GenerateDataMaskTest();
		void GenerateQRCodeTest();
	private:
		Matrix<int>functionPatterns;
		Matrix<int>dataAreaMask;
		int maskMode;
	private:
		void MatrixDataInitlize();
		void GenerateFunctionPatterns();//Use 2-Q specification
		void AddFinderPatterns(int x,int y);
		void AddSeparators();
		void AddAlignmentPatterns(int centerx,int centery);
		void AddTimingPatterns();
		//Only For Version2
		std::string GenerateFinalBits(const std::string& message);
		/*
		*Use gray 180 stand for reservation
		*Use this function before Adding Timing Patterns
		*/
		void ReserveFormatArea();
		/*
		*Use gray 50 stand for reservation
		*/
		void ReserveVersionArea();
		/*
		* This function must be used 
		* instantly after the GenerateFunctionPatterns() is called
		*/
		void GenerateDataAreaMask();
		void PlaceMessage(const std::string& message);
		void AddFormatInformation();
		void AddFormatInformation(int bestMaskID);
	private:
		void MaskingEvalute();
		int EvaluteMaskQuality(Matrix<int> masked);
		Matrix<int> DataMasking(int maskNumber);
	};
}
