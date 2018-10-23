#include<iostream>
#include<vector>
#include"sort1.h"
#include"tree1.h"
#include"ppx.h"
using std::cout;
int main()
{
	//有关二叉树的测试部分
	/*string text="ABD##E#F##C##";
	Binary_tree<char >p3(text);
	
	cout << p3.depth();
	string text1 = "ABCDEF";
	Binary_serach_tree<char>p4(text1);
	p4.print();
	List1<int>ppx = { 1,2,3,4,5,6 };
	ppx.print_all();
	int n = 5;
	ppx.reverse(n);
	ppx.print_all();
	std::vector<int> p =
	{ 1,3,4,2,5,6,7,4 };
	Shell_sort(p);
	//AVl 树的部分 结果为421356
	for (auto s : p) { cout << s; }
	auto test = { 1,2,3,4,5,6 };
	Avl_tree<int> ppx(test);
	ppx.print();*/
	/*MaxHeap<int> ppx = { 44,25,31,18,10,55 };
	ppx.DeleteMax();
	ppx.print();**/
	/*vector <int> ppx;
	string s = "ababaca";
	Next(s, ppx);
	for (auto s : ppx)
	{
		cout << s<<" ";
	}*/
	std::vector<int >ppx={ 44,25,31,18,10,55 };
	RB_tree<int> zd(ppx);
	system("pause");
	return 0;
} 