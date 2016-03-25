//test.cpp

#include "Power.h"
#include <iostream>


int main() {
	double base = 0;
	unsigned expo = 1;
	std::cin >> base >> expo;
	std::cout << pow_naive(base, expo) << std::endl
		      << pow_recu(base, expo) << std::endl;
	return 0;
}