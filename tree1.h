#ifndef  TREE1_H
#define TREE1_H
/*
*��ͷ�ļ� ʹ�� �����ֵܷ�����ʾ�������
*������ ������  ����������  ƽ�������  ��������  ����  �����(�������)
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

�ڶ����޸�2018��12��11��16:40:12  ��������������  ��Ҫ�� ����ͨ�������Ŀսڵ�   ָ���� ǰ�� �����
������RootCopy�ڵ���Ϊ ����ѭ������Ļ��Ŀ�ʼ�ͽ�β  δ��ɲ���: ����ͨ������ת��Ϊ ����������    (���)
( ��Ϊ����ĳ��󲻹�, ��ͨ������ֻ�ܱ��� tree_node ���  �޷�����ת��  �̳� ����ʹ�ô�ǰ�Ĺ���)

�������޸�2018-12-13 11:33  ʹ��using ��ģ������ ���� _Node���� �� ������  template<typename Ty ,typename Node=default_node<T> >
��һ��Ϊ���Ͳ��� �ڶ���������   ����� ��һ��ȱ��
!!!  ���ֵ�ȱ�� :
1.��Ϊ �������޸�ֻ�޸��� Binary_tree �� Binary_search_tree  .Thread_tree ��û�� ���������� ���� �������д������ظ����캯��
Ӧ�ó���� point<Ty,Node>
2.��Ʋ��� ����  ��Ϊ����Ĵ��� ���ģʽ��û������
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

template<typename Ty>
struct tree_node
{
	tree_node(Ty s = Ty()) :data(s), left(nullptr), right(nullptr) {}
	Ty data = Ty();
	shared_ptr<tree_node<Ty>>left;
	shared_ptr<tree_node<Ty>> right;
	tree_node<Ty> &operator =(const tree_node<Ty>&) = delete;
	tree_node<Ty> &operator =(const tree_node<Ty>&&) = delete;
	~tree_node() = default;
};
//avl���Ľ�� ע��Ӧ���ڳ�ʼ���Ĺ����н��� ʵ����
template<typename Ty>
struct AvlNode
{
	AvlNode() = default;
	AvlNode(Ty& s) :data(s) {}
	shared_ptr<AvlNode<Ty>>left = nullptr;
	shared_ptr<AvlNode<Ty>>right = nullptr;
	Ty data = Ty();
	int height = 0;//ƽ������ ���������߶�-  �������߶�//����ֵ���ܳ���1
	AvlNode<Ty> & operator =(const AvlNode<Ty>&) = delete;
	AvlNode<Ty> & operator =(const AvlNode<Ty>&&) = delete;
	~AvlNode() = default;
};
// ������Ľ��
template<typename Ty>
struct RB_node
{
	friend std::ostream &operator << (std::ostream &os, const RB_node<Ty>& rd) {
		os << rd.data; return os;
	}
	RB_node() = default;
	RB_node(Ty& sd, bool rd = true, shared_ptr<RB_node<Ty> >par = nullptr) :parent(par), data(sd), color(rd) {}
	RB_node(bool rd) :color(rd) {}
	~RB_node() = default;
	RB_node<Ty> & operator =(const RB_node<Ty>&sd) = default;
	shared_ptr<RB_node<Ty>> left = nullptr;
	shared_ptr<RB_node<Ty>>right = nullptr;
	shared_ptr<RB_node<Ty>> parent = nullptr;
	Ty data = Ty();
	//��Ϊ0  ��Ϊ1
	bool color = true;//Ĭ�Ϻ�  ������������ͳһ
};

template <typename Ty>
struct Thread_node 
{
	//������ ��ʾ�� ���� �ڵ� �Ƿ� ָ�����ǰ�� ���ߺ���  
	//Ĭ����ָ��ڵ�
	Thread_node() {}; //= default;=default;�����
	Thread_node(Ty sd):data(sd){}
	Thread_node(bool sd):Lthread(sd){}
	Thread_node(const Thread_node&) = default;
	shared_ptr<Thread_node<Ty> >left=nullptr;
	shared_ptr<Thread_node<Ty> >right = nullptr;
	Thread_node<Ty> & operator =(const Thread_node<Ty>&rhs)
	{
		this->data = rhs->data;
		this->left = rhs->left;
		this->right = rhs->right;
		this->Lthread = rhs->Lthread;
		this->Rthread = rhs->Rthread;
	}
	Ty data = Ty();
	bool Lthread = false;
	bool Rthread = false;
	~Thread_node() = default;
};

template<typename Ty>
using Ve_Apoint = vector < shared_ptr<AvlNode<Ty> > >;// Avlָ���������
template<typename Ty, typename Node = tree_node<Ty >>
using point = shared_ptr<Node>;//  ָ�����   ���˱����޸�Ϊ ����ָ��
template<typename Ty, typename Node = tree_node<Ty>>
using vecpo = vector<point<Ty, Node> >;//ָ���������
template<typename Ty, typename Node = RB_node<Ty >>
using RBpoint = shared_ptr<Node>;//�����ָ�����
/*template<typename _Ty, typename _Node = AvlNode<_Ty >>
using point = shared_ptr<_Node >;//AVlָ�����*/
//������������Ϊ  ���� �����ӡ����  �� ����һ�� protected��ָ��ָ��ͷ���
template<typename Ty,typename Node>
class Threaded_tree;
template<typename Ty, typename Node = tree_node<Ty > >
class Binary_tree
{
	
public:
	friend class Threaded_tree<Ty,Thread_node< Ty> >;
	Binary_tree() :root(nullptr) {}
	Binary_tree(string s) {
		int pos = -1;
		root = create(s, pos);//��ͼ��++��Ϊ0��ʼ  ��ÿ�ε���
	}
	virtual void print();
    void print_no_recursion()   ;
	virtual ~Binary_tree() = default;
	virtual int depth()
	{
		cout << "\n  �������ĸ߶���";
		return depthCopy(this->root);
	}
	Binary_tree<Ty, Node>& operator =(const  Binary_tree<Ty,Node>&) = delete;
private:
	//���ڻ�ñ����Ľ�� �ǵݹ�������  ��ת �� ����Ĵ�    ��ú���  ���Ҹ��Ĵ�
	vector<Ty> vec = {};//!!!!ע���ڸı������� ��ʱT ��������structure
	//ת�����������в��ϵ���   ,�����ڽ���Rightѭ��ʱ �޷���������������
	inline point<Ty,Node> create(string & s, int &pos);//ר�Ź�����ͨ������
	//ʹ�õݹ�İ汾  ForwardTravesal
	void ForTra(const  point<Ty, Node> &s);// ǰ�������print�γɽӿ�
	void MiTra(const point<Ty, Node> &s);//����������
	void PosTra(const  point<Ty, Node> &s);
	//������
   //������� ����ʵ��
	void LeveTra(point<Ty, Node> s);
	//�ǵݹ�İ汾
	void forward(point<Ty, Node> s);
	void mide(point<Ty, Node> s);
	void  postore(point<Ty, Node>& s);
	int depthCopy(point<Ty, Node>& s);
protected:
	point<Ty, Node > root;//��Ϊ������������ ����Ҫ�ı���ֵ���Խ��� protected
};

//��Ϊ����������(����������)������  ȫ�����������С�Ҵ�   ���� ����Ԫ�ز����ظ�
template<typename Ty, typename Node = tree_node<Ty >>
class Binary_serach_tree :public Binary_tree<Ty, Node>
{
public:
	Binary_serach_tree() = default;
	template<typename Node>
	Binary_serach_tree(Node&s)  {
		for (auto sd : s) insert(sd);
	}
	template<>//����int��������
	Binary_serach_tree(int&s) {
		insert(s);
	}
	//����������ظ���Ԫ�ز����Ķ�
	//���ﴫ���Ϊֵ������ָ��
	void insert(Ty&s) { insertCopy(s, this->root); }
	void Delete(Ty&s)//delete  ʵ���벻������ݹ�ʹ��root�İ취��
	{
		deleteCopy(s, this->root);
	};
	~Binary_serach_tree() {}
	void print()
	{
		Binary_tree<Ty,Node>::print();
	}
	void print_no_recursion()
	{
		Binary_tree<Ty,Node>::print_no_recursion();
	}
private:
	void insertCopy(Ty&s, point<Ty,Node>&);
	point<Ty,Node> deleteCopy(Ty&, point<Ty,Node>);
};

//���������ֳ�Ϊ���Ŷ�����    ����Ȩ·������    ÿ������Ȩֵ*����֮����С 
//ÿ�������Ϣ����Ҷ�����   ��ʱȡ��Ҷ�����Ϣ ��Ӧ Ϊ  ��0��1  
//��ӡ��ʽ �γɲ�ͬ  ����BInary_tree�ķ���
template<typename Ty, typename Node = tree_node<Ty > >//�Ż�Ȩֵ���� ������Ϣ�ڸ��ڵ��� 
class Huffman_tree :public Binary_tree<Ty, Node>
{
public:
	Huffman_tree() = default;
	template<typename A>
	Huffman_tree(A &s)
	{
		//ת��create֮ǰ   pointCopy��Ԫ������ӦΪ��Ӧ��ָ��
		vecpo<Ty> pointCopy;//��ɺ���빹��
		for (auto& sd : s)
		{
			pointCopy.push_back(std::make_shared<Node>(sd));
		}
		create(pointCopy);//ÿ��Ԫ������ΪT
	}
	~Huffman_tree() = default;
	//��ӡ����ʹ�� �� ��Ϊ0  ��1 ��ӡ�����ı���
	void print() override
	{
		int len = 0;
		printcopy(this->root, len);
	}
	const Huffman_tree<Ty>& operator =(const Huffman_tree<Ty>&) = delete;
	const Huffman_tree<Ty>& operator =(const Huffman_tree<Ty>&&) = delete;
private:
	void create(vecpo<Ty>&s);
	vecpo<Ty> select(vecpo<Ty>&s, int &);
	void printcopy(point<Ty,Node>&, int);
	//point<_Ty> root;
};

//ƽ������� ������������Ȳ����1 ͬʱ������ͬʱ��������
template<typename Ty, typename Node=AvlNode<Ty> >
class Avl_tree :public Binary_tree<Ty, Node>
{
	Avl_tree() = default;
public:
	template<typename vp = vector<Ty>>//A����Ϊ��TΪԪ�ص�����
	Avl_tree(vp&s) {
		for (auto sd : s)
			insert(sd);
	}
	inline int depth()
	{
		return depthCopy(this->root);
	}
	const Avl_tree<Ty, Node>& operator =(const Avl_tree<Ty, Node>&) = delete;
	const Avl_tree<Ty, Node>& operator =(const Avl_tree<Ty, Node>&&) = delete;
	~Avl_tree() = default;
private:
	//��������Ϊ����ʱʹ�õ��� Tree_node ���ʱ��ͬ Ӧ��ʹ��Apoint<T>����ʵ��������z
	//���ظı�Ԫ�ط����ָ�� �������������� ��ͨ���޸�
	//Apoint<_Ty> root = nullptr;Ĭ�ϳ�ʼ��
	point<Ty,Node>insert(Ty&s) { return insertCopy(s, this->root); }
	//�ڽ��в���ʱ�ж���Ҫ����ת����  �����ص�����AVL ��
	// L =left  R=right ���ܵĲ����Ǳ��ƻ��Ľ��ָ��
	//ע����ת���������������� ��Ϊ�ƻ�ƽ��Ľ�����ʱ ���� ���ƻ�ƽ�����ӵĽ�� 
	//���� �������ڱ��ƻ����������� ����������(�����ڴ����ϵ�����λ��) ��Ϊ RR��ת(������ʲô��ʱ����ת)
	point<Ty, Node> insertCopy(Ty, point<Ty, Node>&);
	point<Ty, Node> Rrotation(point<Ty, Node>&);
	point<Ty, Node> Lrotation(point<Ty, Node>&);
	point<Ty, Node> RLrotation(point<Ty, Node>&);
	point<Ty, Node> LRrotation(point<Ty, Node>&);
	int depthCopy(point<Ty,Node>&);
	/*void printCopy(Apoint<_Ty>& t)
	{
		if (t != nullptr)
		{
			cout << t->data;
			printCopy(t->left);
			printCopy(t->right);
		}
	}*/
};

//����  ���ֵ�ڸ������  ��ȡ����洢�������������� �����ڳ���ʱ�����������ֵ   �����ҽ��Ĵ�С����Ҫ��  
//���д洢ʱ ʹ������ �� �� INT_MAX 5 1 3 
//���������Ϊ 5 �� 1  �� 3   ��Ӧ�����±�Ϊ  1 2 3�����Ҷ�ӽ��Ƚ�ʱ  �������� /2�����븸���Ƚϵķ�ʽ
template<typename Ty>
class MaxHeap
{
public:
	MaxHeap() = default;
	template<typename Node = vector<Ty>>//�ճ������б��ʼ��
	MaxHeap(Node &sd) {
		for (auto &s : sd)  insertCopy(s);
	}
	MaxHeap(std::initializer_list<Ty> sd)//�����Դ���ģ������
	{
		for (auto s : sd)  insertCopy(s);
	}
	void insert(Ty &sd) {
		insertCopy(sd);
	}
	void print() {
		for (size_t s = 1; s < container.size(); ++s) {
			cout << container[s] << " ";
		}
	}
	Ty & DeleteMax();
	MaxHeap<Ty>&operator =(const MaxHeap<Ty>&) = delete;
	MaxHeap<Ty>&operator =(const MaxHeap<Ty>&&) = delete;
	~MaxHeap() = default;
private:
	//��һ��ֵΪ��� Ϊint_max ��Ϊ�ڱ�ʹ�� ��ΪҶ��� �����븸���Ƚ�ʱ Ϊ����/2
	vector<Ty> container = { INT_MAX };
	void insertCopy(Ty &);

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
template<typename Ty, typename Node = RB_node<Ty>>
class RB_tree
{
public:
	RB_tree() = default;
	template<typename Z = vector<Ty> > //Ĭ��Ϊ����
	RB_tree(Z &sd)
	{
		for (auto &s : sd)
		{
			RB_tree::insert(s);
		}
	}
	RB_tree<Ty, Node> &operator =(const RB_tree<Ty, Node>&) = delete;
	RB_tree<Ty, Node> &operator =(const RB_tree<Ty, Node>&&) = delete;
	size_t size()const { return node_count; }
	void print() {
		printCopy(root);
	}
	~RB_tree() = default;
private://����Ľ�� Ĭ��Ϊ��
	void printCopy(const RBpoint<Ty>&sd)
	{
		cout << sd->data << "��ɫ" << sd->color;
		printCopy(sd->left);
		printCopy(sd->right);
	}
	point<Ty, Node> root;
	bool insert(Ty&x);//����ɹ� true    �ظ�����ʧ�� false
	//����������Ĳ��� �ο�STL������  ��һ���� �������  �ڶ����� root
	point<Ty, Node>& fa_node(RBpoint<Ty>&x);//���ڵ�
	point<Ty, Node>& gfa_node(RBpoint<Ty>&x);//�游���
	point<Ty, Node>& un_node(RBpoint<Ty>&x);//�������
	//���϶��µĳ��� ���е������ܳ���   ע������:rt����游��� ͬʱ������ �޸�����������
	void RB_tree_rebalance(point<Ty,Node>& x, point<Ty, Node>& rt, point<Ty, Node>&fa, point<Ty, Node>&un);
protected:
	size_t node_count = 0;//������
	//�Ƚϴ�С�Ĳ���Ӧ��ʹ�� function�����з���  ����ʹ��  std::max<lsh ,rhs>; ����� lsh>rhs
	//auto & compare = std::max(lhs, rhs);//�Ƚϴ�С��   ���� ���� ��Ϊ������������Ϊ���� false 
};

/*���������������ķ�ʽ�� ���������Ŀսڵ� �ı��ǰ�����ߺ���
����ǰ���� ���� ֻ��ͨ�������õ� ���� ������������ �ַ�Ϊ ǰ�к� ����
��Ϊ ��������������
���ptr->lchildΪ�գ�����ָ��������������иý���ǰ����㡣�������Ϊptr������ǰ����
���ptr->RchildΪ�գ�����ָ��������������иý��ĺ�����㡣�������Ϊptr�����������
*/
template<typename Ty, typename Node = Thread_node<Ty>>
class Threaded_tree :public Binary_tree<Ty, Node>
{
public:
	//using Binary_tree<Ty, Node>::Binary_tree;
	Threaded_tree() {}
	Threaded_tree(string &sd):Binary_tree<Ty,Node>(sd)
	{
		
	point<Ty,Node> pre = make_shared<Node>(nullptr);
	InThreading(this->root, pre);
	 AddRootCopy(this->root);
	}
	
	void print() override {
		MiTra(this->RootCopy);
	}
	Threaded_tree<Ty, Node> & operator = (const Threaded_tree<Ty, Node> &) = delete;
	Threaded_tree<Ty, Node>&& operator = (const Threaded_tree<Ty, Node> &&) = delete;
	~Threaded_tree() = default;
private:
	//shared_ptr<Binary_tree<Ty, Node>> rt = nullptr;������������root
	point<Ty, Node> RootCopy = nullptr;//��Ϊ������ͷ���
	//   pre ��ʱ���� ������InThreading�д洢Btree��ǰ��
	void InThreading(point<Ty, Node>& Btree, point<Ty, Node>&pre);   //����ͨ�Ķ���������������
	void MiTra(point<Ty, Node> & rt);//ע�� root�ڵ㲢���� ԭ���Ķ������ĸ��ڵ�  root->Lnode����	
	//ת�� Ҫ�ı�Ķ������ĸ��ڵ�  ����ͷ���rootCopy
	void AddRootCopy(point<Ty, Node> & Btree);
};

template<typename Ty, typename Node>
inline void Binary_tree<Ty, Node>::ForTra(const point<Ty, Node> &s)
{
	if (s != nullptr)
	{
		cout << s->data;
		ForTra(s->left);
		ForTra(s->right);
	}
}

template<typename Ty, typename Node>
inline void Binary_tree<Ty, Node >::MiTra(const point<Ty, Node> &s)
{
	if (s != nullptr) {
		MiTra(s->left);
		cout << s->data;
		MiTra(s->right);
	}
}

template<typename Ty, typename Node>
inline void Binary_tree<Ty, Node>::PosTra(const  point<Ty, Node>&s)
{
	if (s != nullptr)
	{
		PosTra(s->left);
		PosTra(s->right);
		cout << s->data;
	}
}

template<typename Ty, typename Node>
inline void Binary_tree<Ty, Node>::LeveTra(point<Ty, Node> s)
{
	if (s == nullptr)return;
	else
	{
		//��ȡ�临�ƽ���ѭ��
		queue< shared_ptr<Node > > slove;
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

template<typename Ty, typename Node>
inline void Binary_tree<Ty, Node>::forward(point<Ty, Node> s)
{
	if (s == nullptr)return;
	stack<shared_ptr<Node>> container;
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

template<typename Ty, typename Node>
inline void Binary_tree<Ty, Node>::mide(point<Ty, Node> s)
{
	if (s == nullptr)return;
	else
	{
		stack<shared_ptr<Node > > container;
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

template<typename Ty, typename Node>
inline void Binary_tree<Ty, Node>::postore(point<Ty, Node>& s)
{
	if (s != nullptr)
	{
		vec.push_back(s->data);
		postore(s->right);
		postore(s->left);
	}
}

template<typename Ty, typename Node>
inline int Binary_tree<Ty, Node>::depthCopy(point<Ty, Node>& s)
{

	if (s == nullptr)return 0;
	int maxRight = depthCopy(s->right);
	int maxLeft = depthCopy(s->left);
	return maxLeft > maxRight ? maxLeft + 1 : maxRight + 1;

}

template<typename Ty, typename Node>
inline void Binary_tree<Ty, Node>::print()
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

template<typename Ty, typename Node>
inline void Binary_tree<Ty, Node>::print_no_recursion()
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

template<typename Ty, typename Node>
inline point<Ty,Node> Binary_tree<Ty, Node >::create(string & s, int& pos)
{
	++pos;
	shared_ptr<Node> point = nullptr;
	if (pos >= (int)s.size())
		return nullptr;
	else if ((unsigned)s[pos] == '#') point = nullptr;
	else
	{
		point = std::make_shared<Node>(s[pos]);//��������ʱ �ȷ�����������
		point->left = create(s, pos);
		point->right = create(s, pos);
	}
	return point;
}

template<typename Ty, typename Node>
inline void Binary_serach_tree<Ty, Node>::insertCopy(Ty & s, point<Ty,Node> &temp)
{
	if (temp == nullptr)  temp = std::make_shared<Node>(s);
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

template<typename Ty, typename Node>
inline point<Ty,Node>
Binary_serach_tree<Ty, Node>::deleteCopy(Ty &s, point<Ty,Node> temp)
{
	shared_ptr<Node> tmp;
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
template<typename Ty, typename Node >
inline void Huffman_tree<Ty, Node>::create(vecpo<Ty> & s)
{
	int size = s.size();
	if (size == 1) {
		this->root = s[0];
		return;
	}
	else if (size == 2)
	{
		auto ppx = std::make_shared<Ty>(s[0]->data + s[1]->data);
		ppx->right = s[0];
		ppx->left = s[1];
		this->root = ppx;
		return;
	}
	//size>=3
	auto temp = select(s, size);
	create(temp);//���еݹ�
}

template<typename Ty, typename Node >
inline vecpo<Ty>
Huffman_tree<Ty, Node>::select(vecpo<Ty>& s, int&size)
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
	auto ppx1 = std::make_shared<Node >> (s[0]->data + s[1]->data);
	ppx1->right = s[0];
	ppx1->left = s[1];
	s.erase(s.begin());     //ɾ��������С��ֵ  ע��ɾ����ʹ�õ�����ʧЧ	
	s.erase(s.begin());     //ɾ��������С��ֵ  ע��ɾ����ʹ�õ�����ʧЧ	
	s.push_back(ppx1);//ѹ�����ֵ
	return s;
}

template<typename Ty, typename Node>
inline void Huffman_tree<Ty, Node>::printcopy(point<Ty,Node> &s, int len)
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

template<typename Ty, typename Node>
//�ڶ��������Ƿ�����insert�������ֺͽ��� ��Ӧ��ǰ���ڵ�Ľ���
inline point<Ty, Node> Avl_tree<Ty, Node>::insertCopy(Ty data, point<Ty, Node>& site)
{
	if (site == nullptr)
	{
		site = make_shared<Node>(data);
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

template<typename Ty, typename Node>
inline point<Ty, Node> Avl_tree<Ty, Node>::Rrotation(point<Ty, Node>&s)
{
	auto temp = s->right;
	s->right = temp->left;
	temp->left = s;
	s->height = std::max(depthCopy(s->left), depthCopy(s->right)) + 1;
	temp->height = std::max(depthCopy(temp->right), s->height) + 1;
	return temp;
}

template<typename Ty, typename Node>
inline point<Ty, Node> Avl_tree<Ty, Node>::Lrotation(point<Ty, Node>&s)
{
	auto temp = s->left;
	s->left = temp->right;
	temp->right = s;
	s->height = std::max(depthCopy(s->left), depthCopy(s->right)) + 1;
	temp->height = std::max(depthCopy(temp->left), s->height) + 1;
	return temp;
}

template<typename Ty, typename Node>
inline point<Ty, Node> Avl_tree<Ty, Node>::RLrotation(point<Ty, Node>&s)
{
	s->right = Lrotation(s->right);
	return Rrotation(s);
}

template<typename Ty, typename Node>
inline point<Ty, Node> Avl_tree<Ty, Node>::LRrotation(point<Ty, Node>&s)
{
	s->left = Rrotation(s->left);
	return Lrotation(s);
}

template<typename Ty ,typename Node>
 inline int Avl_tree<Ty,Node>::depthCopy(point<Ty,Node>&s)
{
	if (s == nullptr)return 0;
	int max1 = depthCopy(s->left);
	int max2 = depthCopy(s->right);
	return max1 > max2 ? max1 + 1 : max2 + 1;
}

template<typename Ty>
inline Ty & MaxHeap<Ty>::DeleteMax()
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
		else if (temp + 1 <= site - 2) {
			++temp;//����ҽ��
			if (container[tempCopy] < container[temp])
				std::swap(container[tempCopy], container[temp]);
			else  break; //δ���и��� ���˳�ѭ��
		}
	}
	return Max;
}

template<typename Ty>
inline void MaxHeap<Ty>::insertCopy(Ty &data)
{
	int site = container.size();//��õ�ǰ�������ʱ������
	container.push_back(data);
	while (container[site / 2] < data&&site != 1) {//���������в �ڱ��� ֵ�����н���	
		std::swap(container[site / 2], container[site]);
		site = site / 2;
	}
}

template<typename Ty, typename Node>
inline bool RB_tree<Ty, Node>::insert(Ty & x)//A Ϊvalue_type
{
	if (root == nullptr) root = make_shared<Node>(x, false);//�����Ϊ��ɫ
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
	rootCopy = make_shared<Node>(x, true, father);//���ø��ڵ�
	++node_count;//������1
	if (father->color == false)return true;//�����Ϊ�� ֱ�Ӳ���
	RB_tree_rebalance(rootCopy, gfa_node(rootCopy), fa_node(rootCopy), un_node(rootCopy));
	return true;
}

template<typename Ty, typename Node>
inline point<Ty, Node>& RB_tree<Ty, Node>::fa_node(RBpoint<Ty>& x)
{
	return x->parent;
}

template<typename Ty, typename Node>
inline point<Ty, Node>& RB_tree<Ty, Node>::gfa_node(RBpoint<Ty>& x)
{
	if (fa_node(x) == nullptr)return fa_node(x);
	else return fa_node(x)->parent;
}

template<typename Ty, typename Node>
inline point<Ty,Node>& RB_tree<Ty, Node>::un_node(RBpoint<Ty>& x)
{
	auto & granfather = gfa_node(x);
	if (granfather == nullptr) return granfather;
	else {
		//��������Ϊ  �游������  ������Ϊ �� �Ӷ����� �������
		if (granfather->left == fa_node(x))return granfather->right;
		else return granfather->left;
	}
}

template<typename Ty, typename Node>
inline void RB_tree<Ty, Node>::RB_tree_rebalance(point<Ty,Node>& x, point<Ty,Node>& rt, point<Ty,Node>&fa, point<Ty,Node>&un)
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
	else {
		rt->color = true;
		fa->color = false; un->color = false;
	}
}

template<typename Ty, typename Node >
void Threaded_tree<Ty, Node>::AddRootCopy(point<Ty, Node>& Btree)
{
	//���ｫ root �ڵ� �������� Btree
	RootCopy = std::make_shared<Node>();
	RootCopy->Rthread = false;//�����ҽڵ������ָ���� 
	RootCopy->right = RootCopy;
	point<Ty, Node> pre = std::make_shared<Node>();
	if (Btree == nullptr) //���������Ϊ�� �� ������ָ����
	{
		RootCopy->Lthread = true;
		RootCopy->left = Btree;
	}
	else//��Ϊ�յ�����½��� ���root
	{
		//��һ�����ڴ����ݽṹ��193ҳ  ��Ӧ���� 1~4
		InThreading(Btree, pre);//��ʱpre��� ������������һ�����  Btree��Ȼ��δ�ı�
		pre->right = RootCopy;//���һ������ ������ָ��ͷ���
		pre->Rthread = true;

		//����  ����Ľڵ�
		point<Ty,Node> right_node = Btree;
		while (right_node->left != nullptr) right_node = right_node->left;//���ｫҪ  ���� ����ߵĽڵ� 
		right_node->Lthread = true;
		right_node->left = RootCopy;

		//����RootCopy  ����ָ��ԭ����ͷ���
		RootCopy->Lthread = true;
		RootCopy->left = Btree;
	}
	Btree = RootCopy;//ʹ����������� ����һ����ͷ���
}

//Btree��ָ��ǰ�Ľڵ� pre ������ǰ�� 
template<typename Ty, typename Node>
inline void Threaded_tree<Ty, Node>::InThreading(point<Ty, Node>& Btree, point<Ty, Node>& pre)
{
	if (Btree == nullptr)
	{
		//�˴εݹ麯��  ÿ�εĵ���ʱ  pre����ֵ�ڵ�ǰBtree  ����
		//���� ���ҽڵ�Ϊ�յ������ �� preû�и�ֵ�ڵ�ǰBtree  �� pre��Ϊ Btree��ǰ������
		InThreading(Btree->left, pre);//���������� �ݹ� ������ �ҵ� ��ڵ�Ϊ�յĽڵ�
		if (Btree->left == nullptr && pre != nullptr)//��ڵ�Ϊ�� ��  ָ��ǰ��
		{
			Btree->left = pre;// ��ʱpre ��û����ɸ�ֵ    �������Btree��ǰ�� 
			Btree->Lthread = false;
		}
		// ��Ϊ��ʱ��Btree ���� ��û�з��ʵ� 
		// ���ڴ�ʱ ������ pre��ΪBtree��ǰ��  Btree Ϊpre�ĺ���   
		//�ж�pre��Ϊǰ��  �Ƿ� û���ҽڵ�  ��Btree��Ϊ�������б��   � �
		if (pre != nullptr&& pre->right == nullptr)//����ǰ���ڵ�ĺ�������
		{
			pre->right = Btree;
			pre->Rthread = false;
		}
		pre = Btree;// ��ʱ pre ��Btree����һ���ڵ�   ����Ϊ��ǰBtree
		InThreading(Btree->right, pre);
	}
}

template<typename Ty, typename Node>
inline void Threaded_tree<Ty, Node>::MiTra(point<Ty, Node>& rt)
{
	if (rt == nullptr) return;
	point<Ty, Node> head = rt->left;//�ҵ�������ͷ���
	//   ��ʱ�������������ɿ���һ��˫��ѭ������  �� ����յ� ��root         
		//��Ϊ���ں��� ���� ��Ϊ �����ѭ����������
		while (head!=nullptr&&head != rt)//���ϵ������ǰ��  ֱ���ص�root
		{
			while(!head->Lthread)//�ǽ���� ����
			head = head->left;
			cout << head->data << " \n";
		
		while (head->Rthread&&head->right != rt)
		{
			head = head->right;//�����������Ĳ���
			cout << head->data;
		}
		head = head->right;
		}
}

#endif // !TREE1_H