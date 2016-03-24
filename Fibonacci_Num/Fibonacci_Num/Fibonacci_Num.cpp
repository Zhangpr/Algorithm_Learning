//Fibonacci_Num.cpp

#include "Fibonacci_Num.h"
#include <vector>
using std::vector;

//�ݹ��㷨��ʱ�临�Ӷ�Ϊ��(��^n)����Ϊ�ƽ����
unsigned Fibo_recu(unsigned n) {
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return Fibo_recu(n - 1) + Fibo_recu(n - 2);
}

//˳�����μ��㣬ʱ�临�Ӷ�Ϊ��(n)
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

//�����ݴμ��㣬ʱ�临�Ӷ�Ϊ��(log n)
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
	//nΪż��
	if (n % 2 == 0)
		return;
	//nΪ����
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