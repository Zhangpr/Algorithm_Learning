//Fibonacci_Num.cpp

#include "Fibonacci_Num.h"
#include <vector>
using std::vector;

//递归算法，时间复杂度为θ(ψ^n)，ψ为黄金比例
unsigned Fibo_recu(unsigned n) {
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return Fibo_recu(n - 1) + Fibo_recu(n - 2);
}

//顺序依次计算，时间复杂度为θ(n)
unsigned Fibo_succ(unsigned n) {
	if (n == 0)
		return 0;
	unsigned tmp1 = 0, tmp2 = 1, result = 1;
	for (unsigned i = 1; i != n; i++) {
		result = tmp1 + tmp2;
		tmp1 = tmp2;
		tmp2 = result;
	}
	return result;
}

//矩阵幂次计算，时间复杂度为θ(log n)
void pow_matrix(vector<unsigned> &Matrix, unsigned n) 
{
	if (n == 1) {
		Matrix = { 1, 1, 1, 0 };
		return;
	}
	pow_matrix(Matrix, n / 2);
	Matrix = { Matrix[0] * Matrix[0] + Matrix[1] * Matrix[2],
			   Matrix[0] * Matrix[1] + Matrix[1] * Matrix[3],
			   Matrix[0] * Matrix[2] + Matrix[2] * Matrix[3],
			   Matrix[1] * Matrix[2] + Matrix[3] * Matrix[3] };
	//n为偶数
	if (n % 2 == 0)
		return;
	//n为奇数
	Matrix = { Matrix[0]+ Matrix[1], Matrix[0],
	           Matrix[2]+ Matrix[3], Matrix[2] };	
}

unsigned Fibo_matrix(unsigned n) {
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	vector<unsigned> tmp = { 1, 1, 1, 0 };
	pow_matrix(tmp, n - 1);
	return tmp[0];
}