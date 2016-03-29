//Max.Sub.h

#ifndef MAX_SUB_H
#define MAX_SUB_H

#include <iostream>

//记录结果的结构体
template <typename Elt_type,  typename It_type>
struct Result {
	Elt_type sum;             //最大子串的和
	It_type beg_it, end_it;   //指出最大子串范围的一对迭代器
};

/* 穷举所有可能的暴力解法，时间复杂度为Θ(n^2),
 *  Input: 一对迭代器，表示寻找最大子串的范围,
           一个表示元素类型的对象,
 * Output: 记录结果的结构体                    */
template <typename Elt_type, typename It_type>
Result<Elt_type, It_type> maxSub_naive(It_type beg, It_type end, Elt_type ele) {
	Result<Elt_type, It_type> maxSubarray{*beg, beg, ++It_type(beg)};
	for (auto sub_beg = beg; sub_beg != end; ++sub_beg) {
		auto sub_end = sub_beg;
		//处理子串中第一个元素
		Elt_type sub_sum = *sub_end++;
		if (sub_sum > maxSubarray.sum) {
			maxSubarray.sum = sub_sum;
			maxSubarray.beg_it = sub_beg;
			maxSubarray.end_it = sub_end;
		}
		//处理子串中剩余元素
		while (sub_end != end) {
			sub_sum += *sub_end++;
			if (sub_sum > maxSubarray.sum) {
				maxSubarray.sum = sub_sum;
				maxSubarray.beg_it = sub_beg;
				maxSubarray.end_it = sub_end;
			}
		}
	}
	return maxSubarray;
}

/* 分治法求最大子串，时间复杂度为Θ(nlgn),
 *  Input: 一对迭代器（只能为可进行算术运算的迭代器类型）,
           一个用以指明元素类型的参数,
 * Output: 记录结果的结构体                    */
template <typename Elt_type, typename It_type>
Result<Elt_type, It_type> maxSub_recu(It_type beg, It_type end, Elt_type ele) {
	if (beg + 1 == end)
		return Result<Elt_type, It_type>{ *beg, beg, end };
	else {
		It_type mid = beg + (end - beg) / 2;
		auto maxLeft = maxSub_recu(beg, mid, ele);
		auto maxRight = maxSub_recu(mid, end, ele);
		auto maxCross = find_maxCross(beg, mid, end, ele);
		if (maxLeft.sum >= maxRight.sum) {
			if (maxLeft.sum >= maxCross.sum)
				return maxLeft;
			else
				return maxCross;
		}
		else {
			if (maxRight.sum > maxCross.sum)
				return maxRight;
			else
				return maxCross;
		}
	}
}

/* 寻找跨过中间位置的最大子串
 * Input: beg 首元素迭代器, mid 中间元素后一个迭代器, 
          end 尾后迭代器, ele 用以指明元素类型的参数
 * Output: 记录跨过中间位置最大子串的结构体                                */
template <typename Elt_type, typename It_type>
Result<Elt_type, It_type> find_maxCross(It_type beg, It_type mid, 
	                                    It_type end, Elt_type ele)
{
	It_type sub_beg, sub_end;
	Result<Elt_type, It_type> maxLeft{ *(mid - 1), mid - 1, mid };
	Elt_type sum = *(mid - 1);
	for (sub_beg = mid - 1; sub_beg != beg;) {
		--sub_beg;
		sum += *sub_beg;
		if (sum >= maxLeft.sum) {
			maxLeft.sum = sum;
			maxLeft.beg_it = sub_beg;
		}
	}
	Result<Elt_type, It_type> maxRight{ *mid, mid, mid + 1 };
	sum = *mid;
	for (sub_end = mid + 1; sub_end != end; ) {
		sum += *sub_end++;
		if (sum > maxRight.sum) {
			maxRight.sum = sum;
			maxRight.end_it = sub_end;
		}
	}
	return Result<Elt_type, It_type>{ maxLeft.sum + maxRight.sum,
	                                  maxLeft.beg_it, maxRight.end_it };
}

#endif
