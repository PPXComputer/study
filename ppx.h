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

int KMP(string& target, string& mate)
{
	vector<int >next;
	//ָ�� �����ַ�����λ��
	//int target_site = 1, mate_site = 1;
	Next(mate, next);
	int mate_site = -1;
	for (int target_site = 0; target_site < target.size(); ++target_site)
	{
		while (mate_site > -1 && mate[mate_site + 1] != target[target_site])
		{
			mate_site = next[mate_site];//ƥ�䲻�ɹ� ��ǰ����
		}
		if (mate[mate_site + 1] == target[target_site]) ++mate_site;//��ͬ�����
		if (mate_site == mate.size() - 1)
			return (int)(target_site - mate.size());//���ض�Ӧ���±�
	}
	return -1;//ʧ�ܷ���-1
}

//next����ĸĽ�����
//  ��Ϊnext ���Ϊ �ǰ׺������   ���� aaaaak  nextֵΪ[ 0 ,1,2,3,4,-1]
//�ڽ��бȽ�ʱ���һ���ַ���ǰ׺�ַ���ͬ (��ʱ�϶������) ��ҪѰ��ǰ׺�ַ���ǰ׺�ַ�
//������ǰ׺�ַ����������õ�һ����ͬ��ǰ׺  �� aaaaak shink_next [0,0,0,0,0,-1]����ظ�����
vector<int>& shink_Next(string &s, vector<int >&ppx)
{
	ppx.reserve(s.size() + 1);//����ռ�
	for (int i = 0; i < s.size(); ++i)
	{
		int key = 0;//��Ϊ��־
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
		if (temp_size == 0)ppx.push_back(0);//��һ������Ϊ0
		else if (s[temp_size] == s[i])//ǰ׺�ַ���ͬ
			ppx.push_back(ppx[i]);
		else ppx.push_back(key);
	}
	return ppx;
}
#endif // !PPX_H

