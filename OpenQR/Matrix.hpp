#pragma once
#include<vector>
#include <iostream>
#include <typeinfo>
namespace openqr
{

	template<typename T>
	class Matrix
	{
	public:
		///default MatrixType: MatDouble
		Matrix();
		Matrix(int rows, int cols, T defaultVal=0);
		Matrix(const Matrix&);
		Matrix& operator=(const Matrix&);
		inline T& operator()(int x,int y){return data[x][y]; }

		inline int getRowNumber(){return rowNumber;}
		inline int getColNumber(){return colNumber;}
		friend std::ostream& operator<<(std::ostream& os,Matrix& mat)
		{
			os<<"[ ";
			for(int i=0;i<mat.rowNumber;++i)
			{
				if(i!=0)
					os<<"  ";
				for(int j=0;j<mat.colNumber;++j)
					os<<mat(i,j)<<" ";
				if(i!=mat.rowNumber-1)
					os<<std::endl;
			}
			os<<"]"<<std::endl;
			return  os;
		}
		~Matrix();
	private:
		std::vector<std::vector<T> >data;
		int rowNumber;
		int colNumber;
		inline void setRowColNumber(int row,int col);
	};


	template<typename T>
	Matrix<T>::Matrix() :Matrix(0, 0)
	{
	}
	template<typename T>
	Matrix<T>::Matrix(int rows, int cols,T defaultVal)
	{
		data.resize(rows, std::vector<T>(cols, defaultVal));
		setRowColNumber(rows,cols);
	}
	template<typename T>
	Matrix<T>::Matrix(const Matrix &rMat)
	{
		data = rMat.data;
		setRowColNumber(rMat.rowNumber,rMat.colNumber);
	}
	template<typename T>
	Matrix<T>& Matrix<T>::operator=(const Matrix &rMat)
	{
		data=rMat.data;
		setRowColNumber(rMat.rowNumber,rMat.colNumber);
		return *this;
	}
	template <typename T>
	void Matrix<T>::setRowColNumber(int row, int col)
	{
		rowNumber=row;
		colNumber=col;
	}
	template<typename T>
	Matrix<T>::~Matrix()
	{
	}
}



