#ifndef  TREE1_H
#define TREE1_H
/*
*��ͷ�ļ� ʹ�� �����ֵܷ�����ʾ�������
*������ ������  ����������  ƽ�������  ��������  ����
*����ʵ�� һ��������� ���ֱ�����ʽ ǰ(������ ��) ��(����� ��) ��(���Ҹ�)  ��(�����Ҹ�)  �Ѿ��ǵݹ� ��ʽд��
*ע��  ��������ķǵݹ�д��   ��ת �� ����Ĵ�    ��ú���  ���Ҹ��Ĵ�
*����������������  ��С �Ҵ�
*ƽ������� �������������������ǰ����  ͬʱ���� |���������ĸ߶Ȳ� | <2 �ڽ��в������ʱ
*����  �������� ���ƻ����� ����λ�ý���  ��ת����   (����ʲô��ʱ���������)
*�������� ÿ��ѡȡȨֵ��С�Ķ��� ��㹹����µĽ��   �ظ�ѡ��  ���� ԭ���Ľ��ȫ����Ҷ�ӽ��
*ͬʱ����  ���ݱ��� ���� �������� 0 1������򻯵���Ϣ��ʾ
*���� �� ���� ����洢 ��  vector[0]=MAX  �����ڱ����   ����*2  ��/2�����븸��� ,����Ƚ�
*!!!!!!  !!!!!!  !!!!!!  !!!!!!
*��ͷ�ļ�ȱ����
*1. ��������Ϊ����ĳ���ģ����� ��Ӧ���� һ������Ͳ��� template<T>���г���int,double ֮��   
Ӧ��Ϊtemplate<typename T,typename A=tree_node<T>>
*    Ӧ��ͨ�����ڻ������洢���ĳ��󻯲���
*2.  ��������Ϊ����������� vitual �ӿ�   ����Ӧ��  override ���Ƕ����ǽ��е��û���  ��������������̶�
*
*3.�������淶��vecpo��Ϊ������� ʱ ���ִ���ʹ���� container����  ���¸�д�Ѷ�����
*�������2018-09-19  11:59 
*/
#include<iostream>
#include<memory>
#include<string>
#include<queue>
#include<stack>
#include<vector>
#include<algorithm>
using std::vector;
using std::stack;
using std::queue;
using std::string;
using std::cout;
using std::shared_ptr;
using std::sort;
using std::make_shared;
//�������ݶ���
template<typename T>
struct tree_node
{
	tree_node(T s = T()) :data(s), left(nullptr), right(nullptr) {}
	T data;
	shared_ptr<tree_node<T>>left;
	shared_ptr<tree_node<T>> right;
	tree_node<T> &operator =(const tree_node<T>&) = delete;
	tree_node<T> &operator =(const tree_node<T>&&) = delete;
	~tree_node() = default;
};
//avl���Ľ�� ע��Ӧ���ڳ�ʼ���Ĺ����н��� ʵ����
template<typename T>
struct AvlNode
{
	AvlNode() = default;
	AvlNode(T& s) :data(s) {}
	shared_ptr<AvlNode<T>>left = nullptr;
	shared_ptr<AvlNode<T>>right = nullptr;
	T data = T();
	int height = 0;//ƽ������ ���������߶�-  �������߶�//����ֵ���ܳ���1
	AvlNode<T> & operator =(const AvlNode<T>&) = delete;
	AvlNode<T> & operator =(const AvlNode<T>&&) = delete;
	~AvlNode() = default;
};
// ������Ľ��
template<typename A>
struct RB_node
{
	friend std::ostream &operator << (std::ostream &os, const RB_node<A>& rd) {
		os << rd.data; return os;
	}
	RB_node() = default;
	RB_node( A& sd,bool rd=true,shared_ptr<RB_node<A> >par=nullptr):parent(par),data(sd),color(rd){}
	RB_node(bool rd ):color(rd){}
	~RB_node() = default;
	RB_node<A> & operator =(const RB_node<A>&sd) = default;
	shared_ptr<RB_node<A>> left=nullptr;
	shared_ptr<RB_node<A>>right = nullptr;
	shared_ptr<RB_node<A>> parent = nullptr;
	A data =A();
	//��Ϊ0  ��Ϊ1
	bool color=true;//Ĭ�Ϻ�  ������������ͳһ
};

template<typename T>
using RBpoint = shared_ptr<RB_node<T>>;//�����ָ�����
template<typename T>
using Apoint = shared_ptr<AvlNode<T> >;//AVlָ�����
template<typename T>
using Ve_Apoint = vector < shared_ptr<AvlNode<T> > >;// Avlָ���������
template<typename T>
using point = shared_ptr<T>;//ָ�����
template<typename T>
using vecpo = vector<shared_ptr<T>>;//ָ���������

//������������Ϊ  ���� �����ӡ����  �� ����һ�� protected��ָ��ָ��ͷ���
template<typename T>
class Binary_tree
{
public:
	Binary_tree() :root(nullptr) {}
	template<typename A>
	Binary_tree(A &s) {
		int pos = -1;
		root = create(s, pos);//��ͼ��++��Ϊ0��ʼ  ��ÿ�ε���
	}
	virtual void print();
	virtual void print_no_recursion()  ;
	virtual ~Binary_tree() {}
	virtual int depth()
	{
		return depthCopy(this->root);
	}
	const Binary_tree<T>& operator =(const  Binary_tree<T>&) = delete;
private:
	//���ڻ�ñ����Ľ�� �ǵݹ�������  ��ת �� ����Ĵ�    ��ú���  ���Ҹ��Ĵ�
	vector<T> vec = {};//!!!!ע���ڸı������� ��ʱT ��������structure
	//ת�����������в��ϵ���   ,�����ڽ���Rightѭ��ʱ �޷���������������
	inline point<T> create(string & s, int &pos);
	//ʹ�õݹ�İ汾  ForwardTravesal
	void ForTra(const  point<T> &s);// ǰ�������print�γɽӿ�
	void MiTra(const point<T> &s);//����������
	void PosTra(const  point<T> &s);
	//������
   //������� ����ʵ��
	void LeveTra(point<T> s);
	//�ǵݹ�İ汾
	void forward(point<T> s);
	void mide(point<T> s);
	void  postore(point<T> s);
	int depthCopy(point<T>& s);
protected:
	point<T> root;//��Ϊ������������ ����Ҫ�ı���ֵ���Խ��� protected
};

//��Ϊ����������(����������)������  ȫ�����������С�Ҵ�   ���� ����Ԫ�ز����ظ�
template<typename T>
class Binary_serach_tree :public Binary_tree<T>
{
public:
	Binary_serach_tree() {}
	template<typename A>
	Binary_serach_tree(A&s) :Binary_tree<T>() {
		for (auto sd : s) insert(sd);
	}
	template<>//����int��������
	Binary_serach_tree(int&s) : Binary_tree<T>() {
		insert(s);
	}
	//����������ظ���Ԫ�ز����Ķ�
	//���ﴫ���Ϊֵ������ָ��
	void insert(T&s) { insertCopy(s, this->root); }
	void delet(T&s)//delete  ʵ���벻������ݹ�ʹ��root�İ취��
	{
		deleteCopy(s, this->root);
	};
	~Binary_serach_tree() {}
	void print()
	{
		Binary_tree<T>::print();
	}
	void print_no_recursion()  
	{
		Binary_tree<T>::print_no_recursion();
	}
private:
	void insertCopy(T&s, point<T>&);
	point<T> deleteCopy(T&, point<T>);
};

//���������ֳ�Ϊ���Ŷ�����    ����Ȩ·������    ÿ������Ȩֵ*����֮����С 
//ÿ�������Ϣ����Ҷ�����   ��ʱȡ��Ҷ�����Ϣ ��Ӧ Ϊ  ��0��1  
//��ӡ��ʽ �γɲ�ͬ  ����BInary_tree�ķ���
template<typename T>//�Ż�Ȩֵ���� ������Ϣ�ڸ��ڵ��� 
class Huffman_tree
{
public:
	Huffman_tree() :Binary_tree() {}
	template<typename A>
	Huffman_tree(A&s)
	{
		//ת��create֮ǰ   pointCopy��Ԫ������ӦΪ��Ӧ��ָ��
		vecpo<T> pointCopy;//��ɺ���빹��
		for (auto sd : s)
		{
			pointCopy.push_back(std::make_shared<tree_node<T>>(sd));
		}
		create(pointCopy);//ÿ��Ԫ������ΪT
	}
	~Huffman_tree() = default;
	//��ӡ����ʹ�� �� ��Ϊ0  ��1 ��ӡ�����ı���
	void print()
	{
		int len = 0;
		printcopy(this->root, len);
	}
	const Huffman_tree<T>& operator =(const Huffman_tree<T>&) = delete;
private:
	void create(vecpo<T>&s);
	vecpo<T> select(vecpo<T>&s, int &);
	void printcopy(point<T>&, int);
	point<T> root;
};

//ƽ������� ������������Ȳ����1 ͬʱ������ͬʱ��������
template<typename T >
class Avl_tree
{
public:
	Avl_tree() {}
	template<typename A = vector<T>>//A����Ϊ��TΪԪ�ص�����
	Avl_tree(A &s) {
		for (auto sd : s)
			insert(sd);
	}
	inline int depth()
	{
		return depthCopy(this->root);
	}
	inline void print() {
		printCopy(this->root);
	};
	const Avl_tree<T>& operator =(const Avl_tree<T>&) = delete;
	const Avl_tree<T>& operator =(const Avl_tree<T>&&) = delete;
	~Avl_tree() = default;
private:
	//��������Ϊ����ʱʹ�õ��� Tree_node ���ʱ��ͬ Ӧ��ʹ��Apoint<T>����ʵ��������z
	//���ظı�Ԫ�ط����ָ�� �������������� ��ͨ���޸�
	Apoint<T> root = nullptr;//Ĭ�ϳ�ʼ��
	Apoint<T>insert(T&s) { return insertCopy(s, this->root); }
	//�ڽ��в���ʱ�ж���Ҫ����ת����  �����ص�����AVL ��
	// L =left  R=right ���ܵĲ����Ǳ��ƻ��Ľ��ָ��
	//ע����ת���������������� ��Ϊ�ƻ�ƽ��Ľ�����ʱ ���� ���ƻ�ƽ�����ӵĽ�� 
	//���� �������ڱ��ƻ����������� ����������(�����ڴ����ϵ�����λ��) ��Ϊ RR��ת(������ʲô��ʱ����ת)
	Apoint<T> insertCopy(T, Apoint<T>&);
	Apoint<T> Rrotation(Apoint<T>&);
	Apoint<T> Lrotation(Apoint<T>&);
	Apoint<T> RLrotation(Apoint<T>&);
	Apoint<T> LRrotation(Apoint<T>&);
	int depthCopy(Apoint<T>&);
	void printCopy(Apoint<T>& t)
	{
		if (t != nullptr)
		{
			cout << t->data;
			printCopy(t->left);
			printCopy(t->right);
		}
	}
};

//����  ���ֵ�ڸ������  ��ȡ����洢�������������� �����ڳ���ʱ�����������ֵ   �����ҽ��Ĵ�С����Ҫ��  
//���д洢ʱ ʹ������ �� �� INT_MAX 5 1 3 
//���������Ϊ 5 �� 1  �� 3   ��Ӧ�����±�Ϊ  1 2 3�����Ҷ�ӽ��Ƚ�ʱ  �������� /2�����븸���Ƚϵķ�ʽ
template<typename T>
class MaxHeap
{
public:
	MaxHeap() = default;
	template<typename A = vector<T>>//�ճ������б��ʼ��
	MaxHeap(A &sd) {
		for (auto &s : sd)  insertCopy(s);
	}
	MaxHeap(std::initializer_list<T> sd)//�����Դ���ģ������
	{
		for (auto s : sd)  insertCopy(s);
	}
	void insert(T &sd) {
		insertCopy(sd);
	}
	void print() {
		for (size_t s = 1; s < container.size(); ++s) {
			cout << container[s] << " ";
		}
	}
	T & DeleteMax();
	MaxHeap<T>&operator =(const MaxHeap<T>&) = delete;
	MaxHeap<T>&operator =(const MaxHeap<T>&&) = delete;
	~MaxHeap() = default;
private:
	//��һ��ֵΪ��� Ϊint_max ��Ϊ�ڱ�ʹ�� ��ΪҶ��� �����븸���Ƚ�ʱ Ϊ����/2
	vector<T> container = { INT_MAX };
	void insertCopy(T &);

};

/*��һ���ǻ������ͳ���  �ڶ��� ����Ϊ ��ָ���ָ��
    ����� �� ���� ����
1 . ���  Ϊ �� ���� ��
2. �ս��͸���� Ϊ ��
3. ����� �ӽ��Ϊ ��ɫ
4. ����ᵽnullptr(��β��)  ���κ�·�� ,������ �ڽ���� ������ͬ

�ڽ��в���ʱ����е�ά�� �������Ϊ ����ʱ  �ڸ��ڵ�ʱΥ�� 2 
      ���ڵ�Ϊ��ɫʱΥ������3                          
	  �������ڽ�� ��ʱ�� Υ�� 4 ��Ҫ���ģ���� ���� Ĭ��Ϊ��
*/ 
template<typename A,typename T=RB_node<A>>
class RB_tree
{
public:
	RB_tree() = default;
	template<typename Z=vecotr<A>> //Ĭ��Ϊ����
	RB_tree(Z &sd)
	{
		for (auto &s : sd)
		{
			RB_tree::insert(s);
		}
	}
	RB_tree<A, T> &operator =(const RB_tree<A, T>&) = delete;
	RB_tree<A, T> &operator =(const RB_tree<A, T>&&) = delete;
	size_t size()const { return node_count; }
	void print() {
		printCopy(root);
	}
	~RB_tree() = default;
private://����Ľ�� Ĭ��Ϊ��
	void prinfCopy(const RBpoint<A>&sd)
	{
		cout << sd->data << "��ɫ" << sd->color;
		printCopy(sd->left);
		printCopy(sd->right);
	}
	shared_ptr<T> root ;
	bool insert(A&x);//����ɹ� true    �ظ�����ʧ�� false
	//����������Ĳ��� �ο�STL������  ��һ���� �������  �ڶ����� root
	RBpoint<A>& fa_node(RBpoint<A>&x);//���ڵ�
	RBpoint<A>& gfa_node(RBpoint<A>&x);//�游���
	RBpoint<A>& un_node(RBpoint<A>&x);//�������
    //���϶��µĳ��� ���е������ܳ���   ע������:rt����游��� ͬʱ������ �޸�����������
	void RB_tree_rebalance(RBpoint<A>& x, point<T>& rt, RBpoint<A>&fa,RBpoint<A>&un);
protected:
	size_t node_count=0;//������
    //�Ƚϴ�С�Ĳ���Ӧ��ʹ�� function�����з���  ����ʹ��  std::max<lsh ,rhs>; ����� lsh>rhs
	//auto & compare = std::max(lhs, rhs);//�Ƚϴ�С��   ���� ���� ��Ϊ������������Ϊ���� false 
};

template<typename T>
inline void Binary_tree<T>::ForTra(const point<T> &s)
{
	if (s != nullptr)
	{
		cout << s->data;
		ForTra(s->left);
		ForTra(s->right);
	}
}

template<typename T>
inline void Binary_tree<T>::MiTra(const point<T> &s)
{
	if (s != nullptr) {
		MiTra(s->left);
		cout << s->data;
		MiTra(s->right);
	}
}

template<typename T>
inline void Binary_tree<T>::PosTra(const  point<T>&s)
{
	if (s != nullptr)
	{
		PosTra(s->left);
		PosTra(s->right);
		cout << s->data;
	}
}

template<typename T>
inline void Binary_tree<T>::LeveTra(point<T> s)
{
	if (s == nullptr)return;
	else
	{
		//��ȡ�临�ƽ���ѭ��
		queue< shared_ptr<tree_node<T> > > slove;
		slove.push(s);
		while (!slove.empty())
		{
			cout << slove.front()->data;
			s = slove.front();
			slove.pop();
			if (s->left != nullptr) slove.push(s->left);
			if (s->right != nullptr) slove.push(s->right);
		}
	}
}

template<typename T>
inline void Binary_tree<T>::forward(point<T> s)
{
	if (s == nullptr)return;
	stack<shared_ptr<tree_node<T>>> container;
	while (!container.empty() || s != nullptr)
	{
		//һֱ������  ����Ҷ�ӽ��  �л��ҽ��
		while (s != nullptr)
		{
			cout << s->data;
			container.push(s);
			s = s->left;
		}
		if (!container.empty())
		{
			s = container.top();
			container.pop();
			s = s->right;
		}

	}
}

template<typename T>
inline void Binary_tree<T>::mide(point<T> s)
{
	if (s == nullptr)return;
	else
	{
		stack<shared_ptr<tree_node<T> > > container;
		while (s != nullptr || !container.empty())
		{
			while (s != nullptr)
			{
				container.push(s);
				s = s->left;
			}
			if (!container.empty())
			{
				s = container.top();
				container.pop();
				cout << s->data;
				s = s->right;
			}
		}

	}
}

template<typename T>
inline void Binary_tree<T>::postore(point<T> s)
{
	if (s != nullptr)
	{
		vec.push_back(s->data);
		postore(s->right);
		postore(s->left);
	}
}

template<typename T>
inline int Binary_tree<T>::depthCopy(point<T>& s)
{

	if (s == nullptr)return 0;
	int maxRight = depthCopy(s->right);
	int maxLeft = depthCopy(s->left);
	return maxLeft > maxRight ? maxLeft + 1 : maxRight + 1;

}

template<typename T>
inline void Binary_tree<T>::print()
{
	cout << "ǰ��������Ϊ" << std::endl;
	ForTra(this->root);
	cout << std::endl << "����������Ϊ" << std::endl;
	MiTra(this->root);
	cout << std::endl << "����������Ϊ" << std::endl;
	PosTra(this->root);
	cout << std::endl << "����������Ϊ" << std::endl;
	LeveTra(this->root);
}

template<typename T>
inline void Binary_tree<T>::print_no_recursion() 
{
	cout << std::endl << "�ǵݹ��ǰ�����" << std::endl;
	forward(this->root);
	cout << std::endl << "�ǵݹ���������" << std::endl;
	mide(this->root);
	cout << std::endl << "�ǵݹ�ĺ������" << std::endl;
	postore(this->root);
	for (int s = (int)vec.size() - 1; s >= 0; s--)
	{
		cout << vec[s];
	}
}

template<typename T>
inline point<T> Binary_tree<T>::create(string & s, int& pos)
{
	++pos;
	shared_ptr<tree_node<T>> point = nullptr;
	if (pos >= s.size())
		return nullptr;
	else if ((unsigned)s[pos] == '#') point = nullptr;
	else
	{
		point = std::make_shared<tree_node<T>>(s[pos]);//��������ʱ �ȷ�����������
		point->left = create(s, pos);
		point->right = create(s, pos);
	}
	return point;
}

template<typename T>

inline void Binary_serach_tree<T>::insertCopy(T & s, point<T> &temp)
{
	if (temp == nullptr)  temp = std::make_shared<tree_node<T>>(s);
	else
	{
		if (s > temp->data) {
			insertCopy(s, temp->right);
		}
		else if (s < temp->data) {
			insertCopy(s, temp->left);
		}
		return;//���return
	}
}

template<typename T>
inline point<T>
Binary_serach_tree<T>::deleteCopy(T &s, point<T> temp)
{
	shared_ptr<tree_node<T>> tmp;
	if (temp == nullptr)cout << "û�ҵ�Ԫ��";
	else if (s > temp->data) deleteCopy(temp->right);
	else if (s < temp->data) deleteCopy(temp->left);
	else if (temp->left != nullptr&&temp->right != nullptr)
	{
		tmp = Finmin(temp->right);//�ҵ�����������Сֵ �������
		temp->data = tmp->data;
		temp->right = deleteCopy(temp->data, temp->right);
	}
	else
	{
		tmp = temp;
		if (temp->right != nullptr) temp = temp->right;
		if (temp->left != nullptr) temp = temp->left;
		//�˳���Ψһָ�� temp��ָ��tmp������    tempͬ������
	}
	return temp;
}

// �����������    ÿ��Ԫ�ص�ֵ����Ȩֵ
template<typename T>
inline void Huffman_tree<T>::create(vecpo<T> & s)
{
	int size = s.size();
	if (size == 1) {
		this->root = s[0];
		return;
	}
	else if (size == 2)
	{
		auto ppx = std::make_shared<tree_node<T>>(s[0]->data + s[1]->data);
		ppx->right = s[0];
		ppx->left = s[1];
		this->root = ppx;
		return;
	}
	//size>=3
	auto temp = select(s, size);
	create(temp);//���еݹ�
}

template<typename T>
inline vecpo<T>
Huffman_tree<T>::select(vecpo<T>& s, int&size)
{
	//site �����С�������±�  ���Ƶ�0 1���괦
	auto first = s[0]->data;  int site = 0;
	for (int sd = 1; sd <= size - 1; ++sd)
	{
		if (first > s[sd]->data)
		{
			first = s[sd]->data; site = sd;
		}
	}
	std::swap(s[0], s[site]);  first = s[1]->data; site = 0;
	for (int sd = 2; sd <= size - 1; ++sd)
	{
		if (first > s[sd]->data)
		{
			first = s[sd]->data; site = sd;
		}
	}
	std::swap(s[1], s[site]);
	auto ppx1 = std::make_shared<tree_node<T>>(s[0]->data + s[1]->data);
	ppx1->right = s[0];
	ppx1->left = s[1];
	s.erase(s.begin());     //ɾ��������С��ֵ  ע��ɾ����ʹ�õ�����ʧЧ	
	s.erase(s.begin());     //ɾ��������С��ֵ  ע��ɾ����ʹ�õ�����ʧЧ	
	s.push_back(ppx1);//ѹ�����ֵ
	return s;
}

template<typename T>
inline void Huffman_tree<T>::printcopy(point<T> &s, int len)
{
	//lenΪ������¼��ǰ���ʵ����
	static int a[100];
	if (s == nullptr) return;
	else
	{
		if (s->right == nullptr&&s->left == nullptr)
		{
			cout << " ���ȨֵΪ" << s->data << "�ı�����";
			for (int i = 0; i < len; i++)
				cout << a[i];
			cout << std::endl;
		}
		//����Ҷ��Ҷ�����ݹ�ͽ��б���
		else
		{
			a[len] = 0;
			printcopy(s->left, len + 1);
			a[len] = 1;
			printcopy(s->right, len + 1);

		}
	}

}

template<typename T >
//�ڶ��������Ƿ�����insert�������ֺͽ��� ��Ӧ��ǰ���ڵ�Ľ���
inline Apoint<T> Avl_tree<T>::insertCopy(T data, Apoint<T>& site)
{
	if (site == nullptr)
	{
		site = make_shared<AvlNode<T>>(data);
	}
	else if (data < site->data)
	{
		//�������������� ��+1 ��-1 �鿴�Ƿ���������ƫ������
		site->left = insertCopy(data, site->left);
		if (depthCopy(site->left) - depthCopy(site->right) == 2)
		{
			if (data < site->left->data) site = Lrotation(site);//����
			else site = LRrotation(site);//������
		}
	}
	else if (data > site->data)
	{
		//�������������� ��+1 ��-1 �鿴�Ƿ���������ƫ������
		site->right = insertCopy(data, site->right);
		if (depthCopy(site->left) - depthCopy(site->right) == -2)
		{
			if (data > site->right->data)site = Rrotation(site);//�ҵ���
			else site = RLrotation(site);//������
		}
	}
	//��Ȳ�����
	site->height = std::max(depthCopy(site->left), depthCopy(site->right)) + 1;
	return site;
}

template<typename T >
inline Apoint<T> Avl_tree<T>::Rrotation(Apoint<T>&s)
{
	auto temp = s->right;
	s->right = temp->left;
	temp->left = s;
	s->height = std::max(depthCopy(s->left), depthCopy(s->right)) + 1;
	temp->height = std::max(depthCopy(temp->right), s->height) + 1;
	return temp;
}

template<typename T  >
inline Apoint<T> Avl_tree<T>::Lrotation(Apoint<T>&s)
{
	auto temp = s->left;
	s->left = temp->right;
	temp->right = s;
	s->height = std::max(depthCopy(s->left), depthCopy(s->right)) + 1;
	temp->height = std::max(depthCopy(temp->left), s->height) + 1;
	return temp;
}

template<typename T >
inline Apoint<T> Avl_tree<T>::RLrotation(Apoint<T>&s)
{
	s->right = Lrotation(s->right);
	return Rrotation(s);
}

template<typename T   >
inline Apoint<T> Avl_tree<T>::LRrotation(Apoint<T>&s)
{
	s->left = Rrotation(s->left);
	return Lrotation(s);
}

template<typename T >
inline int Avl_tree<T>::depthCopy(Apoint<T>&s)
{
	if (s == nullptr)return 0;
	int max1 = depthCopy(s->left);
	int max2 = depthCopy(s->right);
	return max1 > max2 ? max1 + 1 : max2 + 1;
}

template<typename T>
inline T & MaxHeap<T>::DeleteMax()
{
	//ɾ�����ֵ����λ�� 1�����ֵ
	if (container.size() == 1) {
		cout << "ɾ��������Ϊ��";
		return  container[0];
	}
	//ɾ�������ǽ������һ��ֵ���н��� ������������������ 
	int site = container.size() - 1;//���һ��ֵ������
	std::swap(container[1], container[site]);
	int &Max = container[site];//���ֵ
	container.pop_back();
	//���������෴���� �ڽ������ӽ��Ƚ�ʱ *2 ͬʱ�Ƚ� ���ҽ��ʱ�����
	for (int temp = 1; temp * 2 <= site - 1; )
	{
		int tempCopy = temp;//��¼��ǰ����
		temp *= 2;//     ��Ϊ���ѵ����ҽ�㲢�����ڴ�С��ϵ  �ȶ���������ж� �����  temp*2��Ӧ������
		if (container[tempCopy] < container[temp]) {
			std::swap(container[tempCopy], container[temp]);
		}
		else if (temp + 1 <= site - 2){		
			++temp;//����ҽ��
			if (container[tempCopy] < container[temp])
				std::swap(container[tempCopy], container[temp]);
			else  break; //δ���и��� ���˳�ѭ��
		}
	}
	return Max;
}

template<typename T>
inline void MaxHeap<T>::insertCopy(T &data)
{
	int site = container.size();//��õ�ǰ�������ʱ������
	container.push_back(data);
	while (container[site / 2] < data&&site != 1) {//���������в �ڱ��� ֵ�����н���	
		std::swap(container[site / 2], container[site]);
		site = site / 2;
	}
}

template<typename A, typename T>
inline bool RB_tree<A, T>::insert(A & x)//A Ϊvalue_type
{
	if (root == nullptr) root = make_shared<RB_node<A>>(x, false);//�����Ϊ��ɫ
	auto rootCopy = root;//��ø���� ����
	auto & father = root->parent;
	bool flag_size = true;//��־�Ƚ�
	while (rootCopy != nullptr)
	{
		if (rootCopy->data == x) return false;//��� ��ʧ��
		flag_size = (rootCopy->data >= x);
		father = rootCopy;//���游�����Ϊ x���� ����
		rootCopy = flag_size ? rootCopy->left : rootCopy->right;//��С�Ҵ�
	}
	rootCopy = make_shared<RB_node<A>>(x,true,father);//���ø��ڵ�
	++node_count;//������1
	if (father->color == false)return true;//�����Ϊ�� ֱ�Ӳ���
	RB_tree_rebalance(rootCopy, gfa_node(rootCopy), fa_node(rootCopy), un_node(rootCopy));
	return true;
}

template<typename A, typename T>
inline RBpoint<A>& RB_tree<A, T>::fa_node(RBpoint<A>& x)
{
	return x->parent;
}

template<typename A, typename T>
inline RBpoint<A>& RB_tree<A, T>::gfa_node(RBpoint<A>& x)
{
	if (fa_node(x) == nullptr)return fa_node(x);
	else return fa_node(x)->parent;
}

template<typename A, typename T>
inline RBpoint<A>& RB_tree<A, T>::un_node(RBpoint<A>& x)
{
	auto & granfather = gfa_node(x);
	if (granfather == nullptr) return granfather;
	else {
           //��������Ϊ  �游������  ������Ϊ �� �Ӷ����� �������
		if (granfather->left == fa_node(x))return granfather->right;
		else return granfather->left;
	}		
}

template<typename A, typename T>
inline void RB_tree<A, T>::RB_tree_rebalance(RBpoint<A>& x, point<T>& rt, RBpoint<A>&fa, RBpoint<A>&un)
{
	/*
	����� �� ���� ����
	1 . ���  Ϊ �� ���� ��
	2. �ս��͸���� Ϊ ��
	3. ����� �ӽ��Ϊ ��ɫ
	4. ����ᵽnullptr(��β��)  ���κ�·�� ,������ �ڽ���� ������ͬ

	�ڽ��в���ʱ����е�ά�� �������Ϊ ����ʱ  �ڸ��ڵ�ʱΥ�� 2
	���ڵ�Ϊ��ɫʱΥ������3
	�������ڽ�� ��ʱ�� Υ�� 4 ��Ҫ���ģ���� ���� Ĭ��Ϊ��
	*/
	//��Ϊ���µ����  
	// 1. rootΪ��  �� x��Ϊ�ڽ�����
	//2. ����� Ϊ�ڽ�� ֱ�Ӳ���  ��Ϊ������µĽ�� Left ��right Ϊ nullptr ��ɫ��� ����Ȼ��ͬ
	//3(4) �����Ϊ�� (�游�϶��Ǻ�) ������� (��)  (3) �������  ( ����Ĭ�ϸ���� ���游��������  ��Ϊ�ж���ߵ���� �ҽ�����������������)
	// 3.1    x�ڸ����� ������  ���� Ȼ�� ��������游��� ��ɫ����
	// 3.2   x�ڸ����� �ҽ����    ������� ��ΪX������  x���� ���ڵ��λ��
	//  ��ʱ  ���Խ� ԭ���������Ϊ  3.1�е� X ����
	//4.�����Ϊ�� (�游�϶��Ǻ�) ������� (��)  
	//4.1  ֻ��Ҫ��ɫ�ı������  ��->��     ��  �Ͳ��� ->��
	auto & tree = rt->parent;//���������Ľ��
	if (un->color == false)
	{
		if (fa == rt->left)
		{
			if (x == fa->left) //3.1���
			{
				fa->parent = tree;
				rt->parent = fa;
				fa->color = false;
				if (fa->right != nullptr) {
					rt->left = fa->right;
					rt->left->parent = rt;
				}

				rt->color = true;
			}
			else {//3.2
				x->parent = tree;
				x->left = fa;
				fa->parent = x;
				rt->parent = x;
				x->right = rt;
			}
		}
		else //������
		{
			if (x == fa->right) //3.1���
			{
				fa->parent = tree;
				rt->parent = fa;
				fa->color = false;
				if (fa->left != nullptr) {
					rt->right = fa->left;
					rt->right->parent = rt;
				}

				rt->color = true;
			}
			else {
				x->parent = tree;
				x->right = fa;
				fa->parent = x;
				rt->parent = x;
				x->left = rt;
			}
		}
	}
	else{
	rt->color = true;
	fa->color = false; un->color = false;
	}
}
#endif // !TREE1_H