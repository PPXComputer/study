#ifndef PPX_H
#define PPX_H
#include<vector>
#include<string>
using std::string;
using std::vector;
//KMP�㷨��ʵ��
/*
next����ĺ������һ���̶��ַ������ǰ׺�����׺��ͬ�ĳ��ȡ�

���磺abcjkdcba����ô���������ǰ׺�����׺��ͬ��Ȼ��abc��
cbcbc���ǰ׺�����׺��ͬ��cbc��
abcbc���ǰ׺�����׺��ͬ�ǲ����ڵġ�

**ע���ǰ׺����˵�Ե�һ���ַ���ʼ�����ǲ��������һ���ַ���
����aaaa��ͬ���ǰ׺�����׺��aaa��**

����Ŀ���ַ���ptr��ababaca��������7������next[0]��next[1]��next[2]��next[3]��next[4]��next[5]��next[6]�ֱ�������
a��ab��aba��abab��ababa��ababac��ababaca����ͬ���ǰ׺�����׺�ĳ��ȡ�

����a��ab��aba��abab��ababa��ababac��ababaca����ͬ���ǰ׺�����׺�ǡ�������������a������ab������aba������������a��,

����next�����ֵ��[-1,-1,0,1,2,-1,0]������-1��ʾ�����ڣ�0��ʾ���ڳ���Ϊ1��2��ʾ���ڳ���Ϊ3������Ϊ�˺ʹ������Ӧ��
*/
//�����ַ����Ľ�� �� ppx��ΪĿ�����鷵��
vector<int>& Next(string &s, vector<int >&ppx)
{
	ppx.reserve(s.size() + 1);
	for (int i = 0; i < s.size(); ++i)
	{   
		int key = -1;//��Ϊ��־
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
