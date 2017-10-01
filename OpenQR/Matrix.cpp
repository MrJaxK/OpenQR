#include "Matrix.h"
namespace openqr
{
	template<typename T>
	Matrix<T>::Matrix():Matrix(0,0)
	{
	}
	template<typename T>
	Matrix<T>::Matrix(int rows, int cols, int defaultVal)
	{
		
	}
	template<typename T>
	Matrix<T>::Matrix(const Matrix &)
	{
		
	}
	template<typename T>
	Matrix<T>& Matrix<T>::operator=(const Matrix &)
	{
		return Matrix();
	}

	template<typename T>
	Matrix<T>::~Matrix()
	{
		delete data;
	}
}
