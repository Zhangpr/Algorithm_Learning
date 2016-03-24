//Power.h

#ifndef POWER_H
#define POWER_H

//朴素算法，时间复杂度为θ(n)
template <typename T>
T pow_naive(T x, unsigned n)  //x为底数，n为指数（正整数）
{
	T tmp = 1;
	for (unsigned i = 0; i != n; i++)
		tmp *= x;
	return tmp;
}

//分治法，时间复杂度为θ(log n)
template <typename T>
T pow_recu(T x, unsigned n)
{
	if (n == 0)
		return 1;
	T tmp = pow_recu(x, n / 2);
	if (n % 2)
		return tmp * tmp * x;
	else
		return tmp * tmp;
}

#endif