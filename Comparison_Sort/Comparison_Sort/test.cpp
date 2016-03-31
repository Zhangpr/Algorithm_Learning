//test.cpp

#include "Cmp_Sort.h"
#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include <random>
#include <deque>
using namespace std;

int main() {
	uniform_real_distribution<double> u(0, 50);
	default_random_engine e(static_cast <unsigned>(time(0)));
	constexpr int scale = 5000;
	deque<double> arr1(scale);
//	double arr1[scale];
	for (auto &tmp : arr1) 
		cout << (tmp = u(e)) << " ";
	auto arr2(arr1), arr3(arr1), arr4(arr1), arr5(arr1);
/*
	double arr2[scale], arr3[scale], arr4[scale], arr5[scale];
	for (unsigned i = 0; i != scale; ++i)
		arr2[i] = arr3[i] = arr4[i] = arr5[i] = arr1[i];
*/	
	cout << endl << endl;

	bubbleSort(begin(arr1), end(arr1));
	cout << "Bubble sort: ";
	for (auto tmp : arr1)
		cout << tmp << " ";
	cout << endl << endl;

	insertionSort(begin(arr2), end(arr2));
	cout << "Insertion sort: ";
	for (auto tmp : arr2)
		cout << tmp << " ";
	cout << endl << endl;

	mergeSort(begin(arr3), end(arr3));
	cout << "Merge sort: ";
	for (auto tmp : arr3)
		cout << tmp << " ";
	cout << endl << endl;

	heapsort(begin(arr4), end(arr4));
	cout << "Heapsort: ";
	for (auto tmp : arr4)
		cout << tmp << " ";
	cout << endl << endl;

	quicksort(begin(arr5), end(arr5));
	cout << "Quicksort: ";
	for (auto tmp : arr5)
		cout << tmp << " ";
	cout << endl << endl;

	cout << "Equality: " << (arr1 == arr2 && arr2 == arr5 && arr5 == arr3 && arr3 == arr4) << endl;
	return 0;
}