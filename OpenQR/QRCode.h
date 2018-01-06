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
		//Only accept 400*400 mat
		std::string DecodeQRCode(Matrix<int> mat);
		//This function is used for general usage
		//TODO: finish this function
		//inline std::string DecodeCore(Matrix<int> mat);
	//Test functions
	public:
		void GenerateDataMaskTest();
		void GenerateQRCodeTest();
		std::string DecodeQRCodeTest(Matrix<int> mat);
	//Vars
	//private:
	public:
		Matrix<int>functionPatterns;
		Matrix<int>dataAreaMask;
		int maskMode;
	//Initlize functions
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
	//Data masking functions
	private:
		void MaskingEvalute();
		int EvaluteMaskQuality(Matrix<int> masked);
		Matrix<int> DataMasking(int maskNumber);
	//Decode functions
	private:
		//Accept 2Q standard QRCode
		inline std::string DecodeCore();
		
		//Chage functionPatterns to standard 25*25 and binary matrix
		inline void BinaryzationBigMat(Matrix<int> mat);
		void Demasking();
	};
}
