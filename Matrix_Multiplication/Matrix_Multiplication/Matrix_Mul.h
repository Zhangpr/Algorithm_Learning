#ifndef MATRIX_MUL_H
#define MATRIX_MUL_H

#include <vector>
#include <iostream>

template <typename T>
using Matrix = std::vector<std::vector<T>>;

/* 按常规公式计算矩阵相乘                         
 * A为 m*k 矩阵，B为 k*n 矩阵，时间复杂度为θ(kmn) 
 * 若 m = k = n，时间复杂度为θ(n^3)               */
template <typename T>
const Matrix<T> multiply_naive(const Matrix<T> &A, const Matrix<T> &B)
{
	Matrix<T> result(A.size(), std::vector<T>(B[0].size()));
	for (decltype(A.size()) i = 0; i != A.size(); i++)
		for (decltype(B[0].size()) j = 0; j != B[0].size(); j++)
			for (decltype(B.size()) k = 0; k != B.size(); k++)
				result[i][j] += A[i][k] * B[k][j];
	return result;
}

/* Strassen算法，采用矩阵分块的方法
 * 输入的矩阵A，B均为2的幂次阶方阵
 * 时间复杂度为θ(n^(log 7))                      */

template <typename T>
Matrix<T> Strassen(const Matrix<T> &A, const Matrix<T> &B) {
	auto n = A.size();
	if (n <= 16) {
		return multiply_naive(A, B);
	}
	std::vector<Matrix<T>> A_divided, B_divided;
	Mat_div(A, A_divided);
	Mat_div(B, B_divided);

	std::vector<Matrix<T>> S, P;
	Matrix<T> C;
	compute_S(A_divided, B_divided, S);      
	compute_P(A_divided, B_divided, S, P);   
	compute_C(P, C);
	return C;
}

template <typename T> 
void compute_S(const std::vector<Matrix<T>> &A_divided, 
	           const std::vector<Matrix<T>> &B_divided,
	           std::vector<Matrix<T>> &S)
{
	S.push_back(Mat_sub(B_divided[1], B_divided[3]));
	S.push_back(Mat_add(A_divided[0], A_divided[1]));
	S.push_back(Mat_add(A_divided[2], A_divided[3]));
	S.push_back(Mat_sub(B_divided[2], B_divided[0]));
	S.push_back(Mat_add(A_divided[0], A_divided[3]));
	S.push_back(Mat_add(B_divided[0], B_divided[3]));
	S.push_back(Mat_sub(A_divided[1], A_divided[3]));
	S.push_back(Mat_add(B_divided[2], B_divided[3]));
	S.push_back(Mat_sub(A_divided[0], A_divided[2]));
	S.push_back(Mat_add(B_divided[0], B_divided[1]));
}

template <typename T>
void compute_P(const std::vector<Matrix<T>> &A_divided,
	           const std::vector<Matrix<T>> &B_divided,
	           const std::vector<Matrix<T>> &S,
	           std::vector<Matrix<T>> &P)
{
	P.push_back(Strassen(A_divided[0], S[0]));
	P.push_back(Strassen(S[1], B_divided[3]));
	P.push_back(Strassen(S[2], B_divided[0]));
	P.push_back(Strassen(A_divided[3], S[3]));
	P.push_back(Strassen(S[4], S[5]));
	P.push_back(Strassen(S[6], S[7]));
	P.push_back(Strassen(S[8], S[9]));
}

template <typename T>
void compute_C(const std::vector<Matrix<T>> &P, Matrix<T> &C)
{
	const Matrix<T> &C0 = Mat_add(Mat_sub(Mat_add(P[4], P[3]), P[1]), P[5]);
	const Matrix<T> &C1 = Mat_add(P[0], P[1]);
	const Matrix<T> &C2 = Mat_add(P[2], P[3]);
	const Matrix<T> &C3 = Mat_sub(Mat_sub(Mat_add(P[4], P[0]), P[2]), P[6]);

	auto n = 2 * C0.size();
	C.assign(n, std::vector<T>(n));
	for (unsigned i = 0; i != n; i++)
		for (unsigned j = 0; j != n; j++) {
			if (i < n / 2) {
				if (j < n / 2)
					C[i][j] = C0[i][j];
				else
					C[i][j] = C1[i][j - n / 2];
			}
			else {
				if (j < n / 2)
					C[i][j] = C2[i - n / 2][j];
				else
					C[i][j] = C3[i - n / 2][j - n / 2];
			}
		}
}

template <typename T>
void Mat_div(const Matrix<T> &M, std::vector<Matrix<T>> &M_divided)
{
	auto half_n = M.size() / 2;
	M_divided.assign(4, Matrix<T>(half_n, std::vector<T>(half_n)));
	for (decltype(M.size()) i = 0; i != M.size(); i++)
		for (decltype(M[0].size()) j = 0; j != M[0].size(); j++) {
			if (i < half_n) {
				if (j < half_n)
					M_divided[0][i][j] = M[i][j];
				else
					M_divided[1][i][j - half_n] = M[i][j];
			}
			else {
				if (j < half_n)
					M_divided[2][i - half_n][j] = M[i][j];
				else
					M_divided[3][i - half_n][j - half_n] = M[i][j];
			}
		}
			
}

template <typename T>
const Matrix<T> Mat_add(const Matrix<T> &A, const Matrix<T> &B)
{
	Matrix<T> result(A.size(), std::vector<T>(A.size()));
	for (decltype(result.size()) i = 0; i != result.size(); i++)
		for (decltype(result[0].size()) j = 0; j != result[0].size(); j++)
			result[i][j] = A[i][j] + B[i][j];
	return result;
}

template <typename T>
const Matrix<T> Mat_sub(const Matrix<T> &A, const Matrix<T> &B)
{
	Matrix<T> result(A.size(), std::vector<T>(A.size()));
	for (decltype(result.size()) i = 0; i != result.size(); i++)
		for (decltype(result[0].size()) j = 0; j != result[0].size(); j++)
			result[i][j] = A[i][j] - B[i][j];
	return result;
}

#endif