#pragma once
#include<vector>
namespace openqr
{

	template<typename T>
	class Matrix
	{
	public:
		///default MatrixType: MatDouble
		Matrix();
		Matrix(int rows, int cols, int defaultVal=0);
		Matrix(const Matrix&);
		Matrix& operator=(const Matrix&);
		inline T& operator()(int x,int y){return data[x][y] }
		~Matrix();
	private:
		std::vector<std::vector<T> >data;
	};
}



