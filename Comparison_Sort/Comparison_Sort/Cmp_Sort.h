//Cmp_Sort.h

#ifndef CMP_SORT_H
#define CMP_SORT_H

#include <algorithm>
#include <ctime>
#include <random>
#include <vector>
#include <utility>

// ð������ʱ�临�Ӷ�ΪTheta(n^2)
// Input: һ�Ե�������ָ���Ԫ���趨����'<'���㣩 
// Output: void                                 
template <typename It_type>
void bubbleSort(It_type beg, It_type end) {
	for (auto it1 = beg; it1 != end; ++it1) {
		for (auto it2 = it1; it2 != end; ++it2) 
			if (*it2 < *it1)
				std::swap(*it1, *it2);
	}
}

// �������� ʱ�临�Ӷ�ΪTheta(n^2)
// Input: һ�Ե�������ָ���Ԫ���趨����'<'���㣩 
// Output: void 
template <typename It_type>
void insertionSort(It_type beg, It_type end) {
	for (auto it1 = beg; it1 != end; ++it1)
		for (auto it2 = beg; it2 != it1; ++it2) {
			if (*it1 < *it2) {
				//����Ԫ�غ���һλ�Բ���СԪ��
				auto less = *it1;
				It_type it2_tmp = it2;
				auto tmp2 = *it2, tmp1 = tmp2;
				while (it2 != it1) {
					tmp1 = tmp2;
					tmp2 = *++it2;
					*it2 = tmp1;
				}
				*it2_tmp = less;
				break;
			}
		}
}


// �鲢����ʱ�临�Ӷ�ΪTheta(nlgn)
// Input: һ�Ե��������趨�����������㣬ָ���Ԫ���趨����'<'���㣩 
// Output: void
template <typename It_type>
void mergeSort(It_type beg, It_type end) {
	if (beg + 1 == end)
		return;
	auto mid = beg + (end - beg) / 2;
	mergeSort(beg, mid);
	mergeSort(mid, end);

	//�鲢������������
	auto mid_tmp = mid;
	auto beg_tmp = beg;
	auto ele_type = *beg;   //����ȷ������Ԫ�ص�����
	std::vector<decltype(ele_type)> sorted_arr;
	while (beg_tmp != mid || mid_tmp != end) {
		if (beg_tmp == mid)
			sorted_arr.push_back(*mid_tmp++);
		else if (mid_tmp == end)
			sorted_arr.push_back(*beg_tmp++);
		else if (*mid_tmp < *beg_tmp)
			sorted_arr.push_back(*mid_tmp++);
		else
			sorted_arr.push_back(*beg_tmp++);
	}
	//�ƶ��鲢�����е�Ԫ�ص�ԭ������
	auto sorted_arr_it = sorted_arr.begin();
	for (auto it = beg; it != end; ++it, ++sorted_arr_it)
		*it = *sorted_arr_it;
}

// �������������ʱ�临�Ӷ�ΪTheta(nlgn)
// Input: һ�Ե�������ָ���Ԫ���趨����'<'���㣩 
// Output: void
template <typename It_type>
void quicksort(It_type beg, It_type end) {
	if (beg == end)
		return;

	//���ѡ����Ԫ
	unsigned size = 0;
	for (auto it = beg; it != end; ++it)
		++size;
	std::uniform_int_distribution<unsigned> u(0, size-1);
	std::default_random_engine e(static_cast <unsigned>(std::time(0)));
	unsigned pos = u(e);
	auto pivot = beg;
	while (pos--)
		++pivot;
	std::swap(*beg, *pivot);

	//�����з�ΪС�ںʹ�����Ԫ����������
	It_type boundary = beg;
	for (auto it = beg; it != end; ++it) 
		if (*it < *beg) 
			std::swap(*it, *++boundary);
	std::swap(*beg, *boundary);
	
	//�ݹ������������������
	quicksort(beg, boundary);
	quicksort(++boundary, end);
}


#endif 
