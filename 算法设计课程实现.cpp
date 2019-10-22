#include <iostream>
#include <random>
#include <math.h>
#include <vector>
#include <assert.h>
using std::vector;
struct MyQuickSort
{
	// 快速排序的过程 看做为 分治挖坑 方法
	// 假设 一段 序列  left , right  即 index_t partition(array, left, right);
	// 将第一个数作为 基准  则 坑为 arrray[left]=base
	// 先 从后向前找 比base 小于等于的数 right--
	// 找到则  array[left]=array[right] 此时 left处放上 了 比base小的数
	// 坑为 arrray[left]  从前往后找 大于 base的数 left++
	// 找到则 array[right]=array[left]  right放上了比base大的数
	// 重复这个过程 直到 left>=right 最后返回 时 arrray[left]=base;//在中间的位置放上基准数
	// 此时 这个序列 按照 base作为了分水岭  左边 比base小 右边比 base 大 
	// 但是左右两边的数中大小不一 而且不一定对称  将 index= partiton返回的 left即 基准位置
	// 重复 partition(array, index+1, right);
	//partition(array, left, index-1);
	// //自己写的 部分
	using index_t = unsigned int; //长度单位
	index_t partition(vector<int> &array, index_t left, index_t right)
	{
		auto base = array[left]; // 取 第一个数为基准
		bool backward = true;
		while (left < right) {
			if (backward) {
				if (array[right] < base) {
					array[left] = array[right];
					right++;// 因为当前满足后进行了填坑 而right仍然要-1  所以这里加1
					backward = false;
				}
				right--;
			}
			else {
				if (array[left] >= base) {
					array[right] = array[left];
					left--;//抵消后面的++ 
					backward = true;
				}
				left++;
			}
		}
		array[left] = base;
		return left;
	}

	index_t usua_partition(vector<int> &array, index_t left, index_t right)
	{
		//这里是平常的 快速排序的写法
		auto base = array[left]; //取第一个数为基准数
		while (left < right) {
			while ((left < right) && (array[right] >= base)) {
				right--;
			}
			if (left < right) {
				array[left] = array[right];
				left++;
			}
			while ((left < right) && (array[left] < base)) {
				left++;
			}
			if (left < right) {
				array[right] = array[left];
				right--;
			}
		}
		array[left] = base;
		return left;
	}

	void quickSort(vector<int> &array)
	{
		if (array.size() <= 1)
			return;

		quickSort(array, 0, array.size() - 1);
	}
	void quickSort(vector<int> &array, index_t head, index_t tail)
	{
		if (head < tail) {
			auto index = partition(array, head, tail);
			quickSort(array, index + 1, tail);
			if (index != 0)
			{
				quickSort(array, head, index - 1); //为0的情况下 会溢出
			}

		}
	}
	void test() {
		using std::cout;
		vector<int> array;
		array.resize(20);
		std::uniform_int_distribution<int> u(0, 100);
		std::default_random_engine e;
		std::generate(array.begin(), array.end(), [&]() {return u(e); });
		std::for_each(array.begin(), array.end(), [=](int sd) {cout << " " << sd; });
		std::cout << std::endl;
		//array.shrink_to_fit();
		quickSort(array);
		std::for_each(array.begin(), array.end(), [=](int sd) {cout << " " << sd; });
		std::cout << std::endl;

	}
};

struct findNearestPair {

	// 实际问题 : 求解数组中 最接近的两个数

	// 快快排划分的时候 index =返回的坐标表示 这个数
	// 在这个坐标之前 均小于等于  在这个坐标之后 均大于他

	// 使用快排思路 来进行求解最大的K位数
	// 当 K=n/2的时候就是中位数的情况
	// 返回中位数 使用快排 寻找第k的数
	//快排中是使用 分割中 就已经 进行了划分
	// 最开始 left=0 right=size-1		返回值为 索引
	int find_parition(vector<int> &array, int left, int right) {
		if (array.empty()) {
			return -1;
		}
		int par = array[left];// 默认将第一个作为 哨兵
		bool backward = true;// 默认向后找
		while (left < right) {
			if (backward) {
				if (array[right] < par) {
					array[left] = array[right];
					backward = false;
					right++;
				}
				right--;
			}
			else {
				if (array[left] >= par) {
					array[right] = array[left];
					backward = true;
					left--;
				}
				left++;
			}
		}
		array[left] = par;
		return left;
	}
	// 返回值是  类似于排序后坐标为size/2的数 而不是在偶数的情况下的 两数的平均值
	int findMid(vector<int>& array) {
		if (array.size() <= 1)return -1;
		int midIndex = array.size() / 2; // n/的时候所求为 中位数
		int currentIndex = -1;

		//用在标注 使用的界限
		int left = 0;
		int right = array.size() - 1;
		while (currentIndex != midIndex) {
			// 使用 分治 后 产生的 currentIndex有
			//在 currnetIndex的左边的数据均小于 【cuurentIndex】
			// 在右边的数据 均大于[currentIndex]
			// 等在 mideIndex=n/2 及成功完成了 求解中位数的结果

			currentIndex = find_parition(array, left, right);
			if (currentIndex < midIndex) {
				left = currentIndex + 1;
			}
			else {
				right = currentIndex - 1;
			}
		}
		return array[midIndex];
	}

	// 返回值 是 返回的两个点(X的值)
	int finMinDistance(vector<int> & array) {
		if (array.size()<2)
		{
			return std::numeric_limits<int>::max();
		}
		int median = findMid(array);
		// 使用中位将数组分为 两个部分
		vector<int> left;
		left.resize(20);

		vector<int> right;
		right.resize(20);

		// 将数组分好类
		std::for_each(array.begin(), array.end(), [&](int sd) {
			if (sd < median)
			{
				left.push_back(sd);
			}
			else
			{
				right.push_back(sd);
			}
		});
		//然后找到最近的点
		auto leftData = finMinDistance(left);
		auto rightData = finMinDistance(right);

		// 这里是找出最大 最小 值 因为在临界点处 只有 交集值 才能达成最小
		int maxLeft = std::numeric_limits<int>::min();
		std::for_each(left.begin(), left.end(), [&](int sd) {if (sd>maxLeft)
		{
			maxLeft = sd;
		}
		});
		int minRight = std::numeric_limits<int>::max();
		std::for_each(right.begin(), right.end(), [&](int sd) {if (sd <minRight)
		{
			minRight = sd;
		}
		});

		int distanceMin = minRight - maxLeft;
		int distanceLeft = abs(leftData - leftData);
		int distanceRight = abs(rightData - rightData);

		// 选择多位中的最小值
		return std::min({ distanceLeft,distanceRight,distanceMin });
	}
	void test() {
		using std::cout;
		//std::for_each(array.begin(), array.end(), [&](int sd) {cout << " "<<sd; });
		vector<int > array;
		array.resize(20);
		std::default_random_engine e;
		std::uniform_int_distribution<int> u{ 0,100 };

		std::generate(array.begin(), array.end(), [&]() {return u(e); });

		cout << "生成的随机数序列为" << std::endl;
		std::for_each(array.begin(), array.end(), [&](int sd) {cout << " " << sd; });

		auto other = array;
		MyQuickSort s;
		s.quickSort(array);
		cout << "排列好的数列为" << std::endl;
		std::for_each(array.begin(), array.end(), [&](int sd) {cout << " " << sd; });

		cout << std::endl;
		cout << " 寻找最接近的两个数" << "原本的中位数是" << array[array.size() / 2] << std::endl;
		auto result = finMinDistance(array); // findMid没有问题
		cout << "最近的数据为 "<< " 最短距离为" <<result;

	}
};

int main()

{
	findNearestPair pair;
	pair.test();
	system("pause");
	return 0;
}
