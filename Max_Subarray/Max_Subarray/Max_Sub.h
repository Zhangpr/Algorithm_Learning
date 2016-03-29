//Max.Sub.h

#ifndef MAX_SUB_H
#define MAX_SUB_H

#include <iostream>

//��¼����Ľṹ��
template <typename Elt_type,  typename It_type>
struct Result {
	Elt_type sum;             //����Ӵ��ĺ�
	It_type beg_it, end_it;   //ָ������Ӵ���Χ��һ�Ե�����
};

/* ������п��ܵı����ⷨ��ʱ�临�Ӷ�Ϊ��(n^2),
 *  Input: һ�Ե���������ʾѰ������Ӵ��ķ�Χ,
           һ����ʾԪ�����͵Ķ���,
 * Output: ��¼����Ľṹ��                    */
template <typename Elt_type, typename It_type>
Result<Elt_type, It_type> maxSub_naive(It_type beg, It_type end, Elt_type ele) {
	Result<Elt_type, It_type> maxSubarray{*beg, beg, ++It_type(beg)};
	for (auto sub_beg = beg; sub_beg != end; ++sub_beg) {
		auto sub_end = sub_beg;
		//�����Ӵ��е�һ��Ԫ��
		Elt_type sub_sum = *sub_end++;
		if (sub_sum > maxSubarray.sum) {
			maxSubarray.sum = sub_sum;
			maxSubarray.beg_it = sub_beg;
			maxSubarray.end_it = sub_end;
		}
		//�����Ӵ���ʣ��Ԫ��
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

/* ���η�������Ӵ���ʱ�临�Ӷ�Ϊ��(),
 *  Input: һ�Ե�������ֻ��Ϊ�ɽ�����������ĵ��������ͣ�,
           һ������ָ��Ԫ�����͵Ĳ���,
 * Output: ��¼����Ľṹ��                    */
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

/* Ѱ�ҿ���м�λ�õ�����Ӵ�
 * Input: beg ��Ԫ�ص�����, mid �м�Ԫ�غ�һ��������, 
          end β�������, ele ����ָ��Ԫ�����͵Ĳ���
 * Output: ��¼����м�λ������Ӵ��Ľṹ��                                */
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