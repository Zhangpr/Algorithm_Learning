//test.cpp

#include "Cmp_Sort.h"
#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include <random>
using namespace std;

int main() {
	uniform_real_distribution<double> u(0, 30);
	default_random_engine e(static_cast <unsigned>(time(0)));
	int scale = 5000;
	vector<double> arr1(scale);
	for (auto &tmp : arr1) 
		cout << (tmp = u(e)) << " ";
	auto arr2(arr1), arr3(arr1), arr4(arr1), arr5(arr1);
	cout << endl << endl;

	bubbleSort(arr1.begin(), arr1.end());
	cout << "Bubble sort: ";
	for (auto tmp : arr1)
		cout << tmp << " ";
	cout << endl << endl;

	insertionSort(arr2.begin(), arr2.end());
	cout << "Insertion sort: ";
	for (auto tmp : arr2)
		cout << tmp << " ";
	cout << endl << endl;

	mergeSort(arr3.begin(), arr3.end());
	cout << "Merge sort: ";
	for (auto tmp : arr3)
		cout << tmp << " ";
	cout << endl << endl;

	quicksort(arr5.begin(), arr5.end());
	cout << "Quicksort: ";
	for (auto tmp : arr5)
		cout << tmp << " ";
	cout << endl << endl;

	cout << "Equality: " << (arr1 == arr2 && arr2 == arr5 && arr3 == arr5) << endl;
	return 0;
}