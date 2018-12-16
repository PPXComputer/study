#ifndef PPX_H
#define PPX_H
#include<vector>
#include<string>
using std::string;
using std::vector;
//KMP算法的实现
/*
next数组的含义就是一个固定字符串的最长前缀和最长后缀相同的长度。

比如：abcjkdcba，那么这个数组的最长前缀和最长后缀相同必然是abc。
cbcbc，最长前缀和最长后缀相同是cbc。
abcbc，最长前缀和最长后缀相同是不存在的。

**注意最长前缀：是说以第一个字符开始，但是不包含最后一个字符。
比如aaaa相同的最长前缀和最长后缀是aaa。**

对于目标字符串ptr，ababaca，长度是7，所以next[0]，next[1]，next[2]，next[3]，next[4]，next[5]，next[6]分别计算的是
a，ab，aba，abab，ababa，ababac，ababaca的相同的最长前缀和最长后缀的长度。

由于a，ab，aba，abab，ababa，ababac，ababaca的相同的最长前缀和最长后缀是“”，“”，“a”，“ab”，“aba”，“”，“a”,

所以next数组的值是[-1,-1,0,1,2,-1,0]，这里-1表示不存在，0表示存在长度为1，2表示存在长度为3。这是为了和代码相对应。
*/
//解析字符串的结果 将 ppx作为目标数组返回
vector<int>& Next(string &s, vector<int >&ppx)
{
	ppx.reserve(s.size() + 1);
	for (int i = 0; i < s.size(); ++i)
	{   
		int key = -1;//作为标志
		for (int j = 0; j < i; ++j)
		{
			if (s[j] == s[i - j])++key;
			else break;
		}
		ppx.push_back(key);
	}
	return ppx;
}

int KMP(string& target, string& mate)
{
	vector<int >next;
	//指向 两个字符串的位置
	//int target_site = 1, mate_site = 1;
	Next(mate, next);
	int mate_site = -1;
	for (int target_site = 0; target_site < target.size(); ++target_site)
	{
		while (mate_site > -1 && mate[mate_site + 1] != target[target_site])
		{
			mate_site = next[mate_site];//匹配不成功 向前回溯
		}
		if (mate[mate_site + 1] == target[target_site]) ++mate_site;//相同则递增
		if (mate_site == mate.size() - 1)
			return (int)(target_site - mate.size());//返回对应的下标
	}
	return -1;//失败返回-1
}

//next数组的改进方案
//  因为next 最初为 最长前缀的坐标   比如 aaaaak  next值为[ 0 ,1,2,3,4,-1]
//在进行比较时如果一个字符与前缀字符相同 (此时肯定不相等) 还要寻找前缀字符的前缀字符
//不如在前缀字符的坐标设置第一个不同的前缀  则 aaaaak shink_next [0,0,0,0,0,-1]解决重复问题
vector<int>& shink_Next(string &s, vector<int >&ppx)
{
	ppx.reserve(s.size() + 1);//分配空间
	for (int i = 0; i < s.size(); ++i)
	{
		int key = 0;//作为标志
		int temp_size = 0;
		for (int j = 0; j < i; ++j)
		{
			if (s[j] == s[i - j])
			{
				temp_size = j;
				++key;
			}
			else break;
		}
		if (temp_size == 0)ppx.push_back(0);//第一个设置为0
		else if (s[temp_size] == s[i])//前缀字符相同
			ppx.push_back(ppx[i]);
		else ppx.push_back(key);
	}
	return ppx;
}
#endif // !PPX_H

