//test.cpp

#include "Fibonacci_Num.h"
#include <iostream>

int main() {
	for (unsigned i = 0; i != 20; i++)
		std::cout << Fibo_recu(i) << " "
		          << Fibo_succ(i) << " "
		          << Fibo_matrix(i) << std::endl;
	return 0;
}