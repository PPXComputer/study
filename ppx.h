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

#endif // !PPX_H

