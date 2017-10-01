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


	template<typename T>
	Matrix<T>::Matrix() :Matrix(0, 0)
	{
	}
	template<typename T>
	Matrix<T>::Matrix(int rows, int cols, int defaultVal)
	{
		data.resize(rows, std::vector<T>(cols, defaultVal));
	}
	template<typename T>
	Matrix<T>::Matrix(const Matrix &rMat)
	{
		data = rMat;
	}
	template<typename T>
	Matrix<T>& Matrix<T>::operator=(const Matrix &rMat)
	{
		return Matrix(rMat);
	}

	template<typename T>
	Matrix<T>::~Matrix()
	{
	}
}



