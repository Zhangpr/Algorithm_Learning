//test.cpp

#include "Matrix_Mul.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

int main() {
	srand(unsigned(time(0)));
	Matrix<int> A, B;
	unsigned n = 16;
	for (unsigned i = 0; i != n; i++) {
		A.push_back(std::vector<int>(n));
		B.push_back(std::vector<int>(n));
		for (unsigned j = 0; j != n; j++) {
			A[i][j] = rand() % 10;
			B[i][j] = rand() % 10;
		}
	}

	DWORD Cstart = GetTickCount();
	auto &C = multiply_naive(A, B);
	for (int i = 0; i != C[0].size(); i++) {
		for (int j = 0; j != C.size(); j++)
			std::cout << std::setw(6) << C[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
	DWORD Cused = GetTickCount() - Cstart;

	DWORD Dstart = GetTickCount();
	auto &D = Strassen(A, B);
	for (int i = 0; i != D[0].size(); i++) {
		for (int j = 0; j != D.size(); j++)
			std::cout << std::setw(6) << D[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
	DWORD Dused = GetTickCount() - Dstart;
	
	std::cout << "Equality: " << (C == D) << std::endl;
	std::cout << "Used time: C " << Cused << ", D " << Dused << std::endl;
	std::cout << "D is faster : " << (Dused < Cused) << std::endl;
	return 0;
}