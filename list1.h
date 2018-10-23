//线性表的类 实现  查找  插入 反转 删除 销毁
#ifndef LIST1_H
#define LIST1_H
#include<iostream>
#include<memory>
#include<string>
#include<initializer_list>
#include<algorithm>
using std::shared_ptr;
using std::initializer_list;
using std::cout;
using std::cin;
using std::string;
using std::make_shared;
template<typename T>
class List1;
template<typename T>
class NODE
	{
	public:
	NODE(T & s) :data(s), next1(nullptr) {}// 进入传人参数时 指针置空
	T data;
	shared_ptr<NODE> next1 = nullptr;
	};
template<typename T>
class List1
{
public:
	List1():node(nullptr){}
	List1(initializer_list<T> ppx);
	List1(const List1<T>&rh);
	void erase(int&& site);//删除从0开始
	void	operator  = (const List1<T>&rh) { this->node = rh.node; }
	inline void serach(int site);
	inline   int  length() ;
	inline const  int length() const;
	inline void print_all();
	void reverse(int n);//反转链表中前为n个的结点
	 //不允许传递除头结点的指针  以免无法删除
	//销毁所有节点 只需要销毁头节点 
	~List1()
	{
		this->node = nullptr;
	}
private:	
	shared_ptr<NODE<T>> node;//只拥有头节点
//用于检查数据越界问题 并抛出异常  传入的参数是拷贝的 避免错误
  inline	int check_available(int &site);
};

template<typename T>List1<T>::
List1(initializer_list<T> ppx)
{
	int i = 1;
	if (ppx.size() != 0)
	{
		shared_ptr<NODE<T>>p = nullptr;
		for (auto s :ppx)
		{
			if (i == 1)
			{
				this->node = make_shared<NODE<T>>(s);
				p = this->node;
			}
			else
			{
				shared_ptr<NODE<T>>mp(new NODE<T>(s));
                   p ->next1= mp;//上一个的结构指针赋值
			       p = mp;//后移
			}
			++i;
		}
	}

}

template<typename T>
inline List1<T>::List1(const List1<T> &rh)
{
	this->node = rh.node;
}

template<typename T>
inline int List1<T>::length()
{
	return  //通过const类型转换类提高代码重用性
		(static_cast<const List1<T>&>(*this)).length();
}

template<typename T>
inline const int List1<T>::length() const
{
	int count = 0;
	shared_ptr<NODE<T>> p = this->node;
	while (p != nullptr)
	{
		++count;
		p = p->next1;
	}
	const int &ppxd = count;
	return ppxd;
}

template<typename T>
inline  void List1<T>::print_all()
{
	auto s = this->node;
	while(s!=nullptr)
	{
		cout << s->data << " ";
		s = s->next1;
	}
}

template<typename T>
inline void List1<T>::reverse(int n)
{
	if (n > length()-1)
	{
		cout << "反转长度违规"; return;
	}
	if (this->node == nullptr)return;//空不做任何事情
	auto save = this->node;//保留头指针
	auto ne = this->node;
	auto  old = this->node->next1;
	while (n!=0)
	{
		auto temp = old->next1;
		old->next1 = ne;
		ne = old;
		old = temp;
		--n;
	}
	save->next1 = old;
	this->node = ne;
}

template<typename T>
inline int List1<T>::check_available(int& site)
{
	if(site<0 || site>this->length())
	{
		try {
			throw site;
		}
		catch (int)
		{
			cout << "输入错误   请重新输入site" << std::endl;
			cin >> site;
		}
	}
	return site;
}

template<typename T>
void List1<T>::erase(int&& site)
{
	int right_site=  check_available(site);
	shared_ptr<NODE<T>> p = this->node;
	shared_ptr<NODE<T>> s = nullptr;;
	if (right_site == 0) this->node = p->next1;
	else
	{
		while (right_site > 0)
		{
			s = p;
			p = p->next1;
			--right_site;
		} 
			s->next1 = p->next1;
	}
}

template<typename T>
inline void   List1<T>::serach(int site)
{ 
	auto p = this->node;
	auto right_site =check_available(site);
	auto s1 = right_site;
	while (p != nullptr&&right_site!=0) {
		p = p->next1;
		--right_site;
	}
	if (right_site == 0) cout << "第" << s1 << "位置上的数据是 " << p->data;
	else if(p == nullptr) cout << "查询越界";
}
#endif // !LIST1_H

