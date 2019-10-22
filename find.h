#ifndef FiND_H
#define FIND_H
#include<vector>
#include<string>
#include<memory>
#include<algorithm>
using std::vector;
using std::string;
using std::shared_ptr;
using std::make_shared;
//此头文件 放入查找相关的算法
//顺序 分块 折半 B树和其基本操作  B+   散列表
//统一返回  下标site
//顺序
int Sequeue(vector<int>& container, int &number)
{
	int site = 0;
	for (auto &sd : container)
	{
		if (number == sd)return site;
		else ++site;
	}
	return -1;
}
int Binary(vector<int> &container, int &number)
{
	//需要是 有顺序的
	std::sort(container.begin(), container.end(), [](const int &rhs, const int &lhs)
	{
		if (rhs < lhs)return true;
		else false;
	}		);
	int mid = 0, left = 0, right = container.size()-1;
	while (left <= right)
	{
		mid =  (right+left) / 2;
		if (number == container[mid])return mid;
		else if (number < container[mid]) right = mid-1;
		else if (number > container[mid]) left = mid+1;
	}
	return -1;
}
//插值查找 
// 对于排序为1~1000的数组  查找 5时候 需要向低地址索引  来加快速度
//二分为 mid=(right+left)/2  
//插值为 mid =left+(key-container [left])/(container[right]-container[left])*(right-left) key是要查找的值
int Insert(vector<int>container, int left, int right, int key)
{
	int mid = left + (key - container[left]) / (container[right] - container[left])*(right - left);
	if (left > right)return -1;
	if (container[mid] == key)return mid;
	else if (container[mid] < key)return Insert(container, mid + 1, right, key);
	else if (container[mid] > key)return Insert(container, mid , right-1, key);
}
/*斐波那契 查找 作为二分查找的提升 
对于斐波那契数列：1、1、2、3、5、8、13、21、34、55、89……（也可以从0开始），
前后两个数字的比值随着数列的增加，越来越接近黄金比值0.618。
比如这里的89，把它想象成整个有序表的元素个数，而89是由前面的两个斐波那契数34和55相加之后的和，
也就是说把元素个数为89的有序表分成由前55个数据元素组成的前半段和由后34个数据元素组成的后半段，
那么前半段元素个数和整个有序表长度的比值就接近黄金比值0.618，
假如要查找的元素在前半段，那么继续按照斐波那契数列来看，55 = 34 + 21，所以继续把前半段分成前34个数据元素的前半段和后21个元素的后半段，
继续查找，如此反复，直到查找成功或失败，这样就把斐波那契数列应用到查找算法中了
*/
//此时 数组的长度需满足 size=F[n]斐波那契数列的其中一项值 不满足 则使用最大值进行填充
void Fibonacci(vector<int >& ppx)
{
	//构造数组 方便 进行 分组大小的确定
	ppx[0] = 1;
	ppx[1] = 1;
	int  max_size = 20;
	ppx.reserve(20);
	for (int i = 2; i < max_size; ++i)
	{
		ppx[i] = ppx[i - 1] + ppx[i - 2];
	}
}
//注意这里 ppx拷贝 因为在 大小不满足的情况下需要 添加元素
int FibonacciSerach(vector<int > ppx, int& key)
{
	vector<int > Fib;
	Fibonacci(Fib);
	//对应查找大小与 此数列的对应关系  注意 是Fib[n]-1 而不是Fib [n]
	int n = 0;
	while(ppx.size()>Fib[n]-1)
	{
		++n;
	}
	int varsize = ppx.size();//记录原来的大小 方便在查找到进行判断
	//需要填充
	auto s = Fib[n + 1] - 1 - ppx.size();
	for (int i = 0; i < s; ++i)
	{
		ppx.push_back(INT_MAX);
	}
	int left = 0, right = ppx.size();
	int mid = 0; 
	while (left <= right)
	{
		mid = left + Fib[n - 1]-1;
		if (key < ppx[mid])
		{
			right = mid - 1;
			n -= 1;
		}
		else if(key>ppx[mid]) {
			left = mid + 1;
			n -= 2;
		}
		else
		{
			if (mid > varsize-1)return -1;//为扩充的值 未找到
			else return mid;
		}
	}
	return -1;//皮皮虾 遍历完了 未找到 -1
}
#endif // !FiND_H

