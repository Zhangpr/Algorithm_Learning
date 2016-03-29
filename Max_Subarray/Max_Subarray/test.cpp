//test.cpp

#include "Max_Sub.h"
#include <iostream>
#include <vector>
#include <list>
#include <ctime>
using namespace std;

int main() {
//	vector<int> arr{ 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22,  15, -4, 7 };
//	vector<int> arr{ -17, 0, 7, 15, 18, 3, -10, 14, 14, 17, 19, -18, -6, 12, 2, 11, -17, 10, -12, 9 };
	int scale = 5000;
	vector<int> arr;
	srand(unsigned(time(0)));
	for (int i = 0; i != scale; i++)
		arr.push_back(rand() % 40 - 20);
	for (auto tmp : arr)
		cout << tmp << " ";
	cout << endl << endl;

	Result<int, decltype(arr.end())> maxSubarray1, maxSubarray2;
	maxSubarray1 = maxSub_naive(arr.begin(), arr.end(), 0);
	cout << "The sum of the maximum subarray: " << maxSubarray1.sum << endl;
	cout << "The maximum subarray: ";
	for (auto beg = maxSubarray1.beg_it; beg != maxSubarray1.end_it; beg++)
		cout << *beg << " ";
	cout << endl << endl;

	maxSubarray2 = maxSub_recu(arr.begin(), arr.end(), 0);
	cout << "The sum of the maximum subarray: " << maxSubarray2.sum << endl;
	cout << "The maximum subarray: ";
	for (auto beg = maxSubarray2.beg_it; beg != maxSubarray2.end_it; beg++)
		cout << *beg << " ";
	cout << endl << endl;

	cout << "sum equality: " << (maxSubarray1.sum == maxSubarray2.sum) << endl
		 << "beg_it equality: " << (maxSubarray1.beg_it == maxSubarray2.beg_it) << endl
		 << "end_it equality: " << (maxSubarray1.end_it == maxSubarray2.end_it) << endl;

	return 0;

}