//Power.h

#ifndef POWER_H
#define POWER_H

//�����㷨��ʱ�临�Ӷ�Ϊ��(n)
template <typename T>
T pow_naive(T x, unsigned n)  //xΪ������nΪָ������������
{
	T tmp = 1;
	for (unsigned i = 0; i != n; i++)
		tmp *= x;
	return tmp;
}

//���η���ʱ�临�Ӷ�Ϊ��(log n)
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