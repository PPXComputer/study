#ifndef  TREE1_H
#define TREE1_H
/*
*此头文件 使用 儿子兄弟法来表示结点属性
*保存着 二叉树  二叉搜索树  平衡二叉树  哈弗曼树  最大堆
*基本实现 一般二叉树的 三种遍历方式 前(根左右 右) 中(左根右 左) 后(左右根)  层(根左右根)  已经非递归 方式写法
*注意  后序遍历的非递归写法   反转 根 右左的答案    获得后序  左右根的答案
*二叉搜索树是满足  左小 右大
*平衡二叉树 是在满足二叉搜索树的前提下  同时满足 |左右子树的高度差 | <2 在进行插入操作时
*根据  插入结点在 被破坏结点的 左右位置进行  旋转操作   (不是什么逆时针就是右旋)
*哈弗曼树 每次选取权值最小的二个 结点构造成新的结点   重复选择  所以 原来的结点全部在叶子结点
*同时根据  根据遍历 左右 结点产生的 0 1生成最简化的信息表示
*最大堆 是 利用 数组存储 在  vector[0]=MAX  进行哨兵监测   坐标*2  或/2进行与父结点 ,左结点比较
*!!!!!!  !!!!!!  !!!!!!  !!!!!!
*此头文件缺点是
*1. 二叉树作为基类的抽象化模板参数 不应该是 一般的类型参数 template<T>进行抽象int,double 之类   
应该为template<typename T,typename A=tree_node<T>>
*    应该通过对于基类所存储结点的抽象化参数
*2.  二叉树作为基类大量进行 vitual 接口   子类应该  override 覆盖而不是进行调用基类  增加了类的依赖程度
*
*3.命名不规范如vecpo作为数组别名 时 部分代码使用了 container命名  导致复写难度增加
*完成日期2018-09-19  11:59 
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
//常量数据定义
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
//avl树的结点 注意应该在初始化的过程中进行 实例化
template<typename T>
struct AvlNode
{
	AvlNode() = default;
	AvlNode(T& s) :data(s) {}
	shared_ptr<AvlNode<T>>left = nullptr;
	shared_ptr<AvlNode<T>>right = nullptr;
	T data = T();
	int height = 0;//平衡因子 有左子树高度-  右子树高度//绝对值不能超过1
	AvlNode<T> & operator =(const AvlNode<T>&) = delete;
	AvlNode<T> & operator =(const AvlNode<T>&&) = delete;
	~AvlNode() = default;
};
// 红黑树的结点
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
	//黑为0  红为1
	bool color=true;//默认红  与插入操作进行统一
};

template<typename T>
using RBpoint = shared_ptr<RB_node<T>>;//红黑树指针别名
template<typename T>
using Apoint = shared_ptr<AvlNode<T> >;//AVl指针别名
template<typename T>
using Ve_Apoint = vector < shared_ptr<AvlNode<T> > >;// Avl指针数组别名
template<typename T>
using point = shared_ptr<T>;//指针别名
template<typename T>
using vecpo = vector<shared_ptr<T>>;//指针数组别名

//二叉树这里作为  基类 定义打印操作  和 保存一个 protected的指针指向头结点
template<typename T>
class Binary_tree
{
public:
	Binary_tree() :root(nullptr) {}
	template<typename A>
	Binary_tree(A &s) {
		int pos = -1;
		root = create(s, pos);//意图从++后为0开始  并每次递增
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
	//用于获得遍历的结果 非递归后序遍历  反转 根 右左的答案    获得后序  左右根的答案
	vector<T> vec = {};//!!!!注意在改变结点类型 这时T 代表则结点structure
	//转入引用来进行不断递增   ,否则在进入Right循环时 无法进行正常的索引
	inline point<T> create(string & s, int &pos);
	//使用递归的版本  ForwardTravesal
	void ForTra(const  point<T> &s);// 前序遍历与print形成接口
	void MiTra(const point<T> &s);//中序遍历结果
	void PosTra(const  point<T> &s);
	//后序结果
   //层序遍历 队列实现
	void LeveTra(point<T> s);
	//非递归的版本
	void forward(point<T> s);
	void mide(point<T> s);
	void  postore(point<T> s);
	int depthCopy(point<T>& s);
protected:
	point<T> root;//因为二叉树搜索树 中需要改变其值所以进行 protected
};

//因为二叉搜索树(二叉排序树)的性质  全部结点满足左小右大   所以 结点的元素不会重复
template<typename T>
class Binary_serach_tree :public Binary_tree<T>
{
public:
	Binary_serach_tree() {}
	template<typename A>
	Binary_serach_tree(A&s) :Binary_tree<T>() {
		for (auto sd : s) insert(sd);
	}
	template<>//对于int的特例化
	Binary_serach_tree(int&s) : Binary_tree<T>() {
		insert(s);
	}
	//如果插入有重复的元素不做改动
	//这里传入的为值而不是指针
	void insert(T&s) { insertCopy(s, this->root); }
	void delet(T&s)//delete  实在想不到解决递归使用root的办法了
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

//哈夫曼树又称为最优二叉树    即带权路径长度    每个结点的权值*长度之和最小 
//每个结点信息都在叶结点上   此时取得叶结点信息 对应 为  左0右1  
//打印方式 形成不同  不用BInary_tree的方法
template<typename T>//优化权值的树 所有信息在根节点上 
class Huffman_tree
{
public:
	Huffman_tree() :Binary_tree() {}
	template<typename A>
	Huffman_tree(A&s)
	{
		//转入create之前   pointCopy中元素类型应为对应的指针
		vecpo<T> pointCopy;//完成后进入构析
		for (auto sd : s)
		{
			pointCopy.push_back(std::make_shared<tree_node<T>>(sd));
		}
		create(pointCopy);//每个元素类型为T
	}
	~Huffman_tree() = default;
	//打印操作使用 是 左为0  右1 打印根结点的编码
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

//平衡二叉树 左右子树的深度不相差1 同时各子树同时满足性质
template<typename T >
class Avl_tree
{
public:
	Avl_tree() {}
	template<typename A = vector<T>>//A类型为以T为元素的数组
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
	//二叉树作为基类时使用的是 Tree_node 与此时不同 应该使用Apoint<T>进行实例化参数z
	//返回改变元素分配的指针 即返回子树部分 来通过修改
	Apoint<T> root = nullptr;//默认初始化
	Apoint<T>insert(T&s) { return insertCopy(s, this->root); }
	//在进行插入时判断需要的旋转操作  并返回调整的AVL 树
	// L =left  R=right 接受的参数是被破坏的结点指针
	//注意旋转操作的左右命名是 因为破坏平衡的结点加入时 对于 所破坏平衡因子的结点 
	//比如 插入结点在被破坏结点的右子树 的右子树上(不管在此树上的左右位置) 则为 RR旋转(而不是什么逆时针旋转)
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

//最大堆  最大值在根结点上  采取数组存储满足完美二叉树 可以在常树时间索引到最大值   则左右结点的大小不做要求  
//进行存储时 使用数组 则 如 INT_MAX 5 1 3 
//代表着最大为 5 左 1  右 3   对应数组下标为  1 2 3则进行叶子结点比较时  进行坐标 /2进行与父结点比较的方式
template<typename T>
class MaxHeap
{
public:
	MaxHeap() = default;
	template<typename A = vector<T>>//日常进行列表初始化
	MaxHeap(A &sd) {
		for (auto &s : sd)  insertCopy(s);
	}
	MaxHeap(std::initializer_list<T> sd)//不可以传入模板引用
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
	//第一个值为最大 为int_max 作为哨兵使用 因为叶结点 进行与父结点比较时 为坐标/2
	vector<T> container = { INT_MAX };
	void insertCopy(T &);

};

/*第一个是基础类型抽象  第二个 代表为 所指向的指针
    红黑树 有 以下 规则
1 . 结点  为 黑 或者 红
2. 空结点和根结点 为 黑
3. 红结点的 子结点为 黑色
4. 任意结到nullptr(树尾端)  的任何路径 ,所含的 黑结点数 必须相同

在进行插入时候进行的维护 如果插入为 红结点时  在根节点时违反 2 
      父节点为红色时违反性质3                          
	  如果插入黑结点 的时候 违反 4 需要大规模调整 所以 默认为红
*/ 
template<typename A,typename T=RB_node<A>>
class RB_tree
{
public:
	RB_tree() = default;
	template<typename Z=vecotr<A>> //默认为数组
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
private://插入的结点 默认为红
	void prinfCopy(const RBpoint<A>&sd)
	{
		cout << sd->data << "颜色" << sd->color;
		printCopy(sd->left);
		printCopy(sd->right);
	}
	shared_ptr<T> root ;
	bool insert(A&x);//插入成功 true    重复插入失败 false
	//调整红黑树的操作 参考STL的做法  第一个是 新增结点  第二个是 root
	RBpoint<A>& fa_node(RBpoint<A>&x);//父节点
	RBpoint<A>& gfa_node(RBpoint<A>&x);//祖父结点
	RBpoint<A>& un_node(RBpoint<A>&x);//伯父结点
    //自上而下的程序 进行调整的总程序   注意事项:rt存放祖父结点 同时保存则 修改子树的祖结点
	void RB_tree_rebalance(RBpoint<A>& x, point<T>& rt, RBpoint<A>&fa,RBpoint<A>&un);
protected:
	size_t node_count=0;//结点计数
    //比较大小的操作应该使用 function来进行泛化  这里使用  std::max<lsh ,rhs>; 相等于 lsh>rhs
	//auto & compare = std::max(lhs, rhs);//比较大小的   这里 不用 因为碰到相等情况因为返回 false 
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
		//提取其复制进入循环
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
		//一直向左走  到达叶子结点  切换右结点
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
	cout << "前序遍历结果为" << std::endl;
	ForTra(this->root);
	cout << std::endl << "中序遍历结果为" << std::endl;
	MiTra(this->root);
	cout << std::endl << "后序遍历结果为" << std::endl;
	PosTra(this->root);
	cout << std::endl << "层序遍历结果为" << std::endl;
	LeveTra(this->root);
}

template<typename T>
inline void Binary_tree<T>::print_no_recursion() 
{
	cout << std::endl << "非递归的前序遍历" << std::endl;
	forward(this->root);
	cout << std::endl << "非递归的中序遍历" << std::endl;
	mide(this->root);
	cout << std::endl << "非递归的后序遍历" << std::endl;
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
		point = std::make_shared<tree_node<T>>(s[pos]);//进入子树时 先分配子树部分
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
		return;//相等return
	}
}

template<typename T>
inline point<T>
Binary_serach_tree<T>::deleteCopy(T &s, point<T> temp)
{
	shared_ptr<tree_node<T>> tmp;
	if (temp == nullptr)cout << "没找到元素";
	else if (s > temp->data) deleteCopy(temp->right);
	else if (s < temp->data) deleteCopy(temp->left);
	else if (temp->left != nullptr&&temp->right != nullptr)
	{
		tmp = Finmin(temp->right);//找到右子树的最小值 进行填充
		temp->data = tmp->data;
		temp->right = deleteCopy(temp->data, temp->right);
	}
	else
	{
		tmp = temp;
		if (temp->right != nullptr) temp = temp->right;
		if (temp->left != nullptr) temp = temp->left;
		//退出后唯一指向 temp的指针tmp被销毁    temp同样销毁
	}
	return temp;
}

// 传入的是容器    每个元素的值代表权值
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
	create(temp);//进行递归
}

template<typename T>
inline vecpo<T>
Huffman_tree<T>::select(vecpo<T>& s, int&size)
{
	//site 获得最小的两个下标  并移到0 1坐标处
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
	s.erase(s.begin());     //删除二个最小的值  注意删除会使得迭代器失效	
	s.erase(s.begin());     //删除二个最小的值  注意删除会使得迭代器失效	
	s.push_back(ppx1);//压入更新值
	return s;
}

template<typename T>
inline void Huffman_tree<T>::printcopy(point<T> &s, int len)
{
	//len为拷贝记录当前访问的深度
	static int a[100];
	if (s == nullptr) return;
	else
	{
		if (s->right == nullptr&&s->left == nullptr)
		{
			cout << " 结点权值为" << s->data << "的编码是";
			for (int i = 0; i < len; i++)
				cout << a[i];
			cout << std::endl;
		}
		//不是叶子叶点进入递归就进行编码
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
//第二个参数是方便与insert子树部分和进行 对应当前根节点的解析
inline Apoint<T> Avl_tree<T>::insertCopy(T data, Apoint<T>& site)
{
	if (site == nullptr)
	{
		site = make_shared<AvlNode<T>>(data);
	}
	else if (data < site->data)
	{
		//进入左子树部分 左+1 右-1 查看是否有左子树偏大的情况
		site->left = insertCopy(data, site->left);
		if (depthCopy(site->left) - depthCopy(site->right) == 2)
		{
			if (data < site->left->data) site = Lrotation(site);//左单旋
			else site = LRrotation(site);//左右旋
		}
	}
	else if (data > site->data)
	{
		//进入右子树部分 左+1 右-1 查看是否有右子树偏大的情况
		site->right = insertCopy(data, site->right);
		if (depthCopy(site->left) - depthCopy(site->right) == -2)
		{
			if (data > site->right->data)site = Rrotation(site);//右单旋
			else site = RLrotation(site);//右左旋
		}
	}
	//相等不做事
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
	//删除最大值即在位置 1坐标的值
	if (container.size() == 1) {
		cout << "删除的最大堆为空";
		return  container[0];
	}
	//删除操作是将用最后一个值进行交换 再重新排序整个数组 
	int site = container.size() - 1;//最后一个值的坐标
	std::swap(container[1], container[site]);
	int &Max = container[site];//最大值
	container.pop_back();
	//与插入操作相反的是 在进行与子结点比较时 *2 同时比较 左右结点时会进行
	for (int temp = 1; temp * 2 <= site - 1; )
	{
		int tempCopy = temp;//记录当前坐标
		temp *= 2;//     因为最大堆的左右结点并不存在大小关系  先对左结点进行判断 这里的  temp*2对应则左结点
		if (container[tempCopy] < container[temp]) {
			std::swap(container[tempCopy], container[temp]);
		}
		else if (temp + 1 <= site - 2){		
			++temp;//变成右结点
			if (container[tempCopy] < container[temp])
				std::swap(container[tempCopy], container[temp]);
			else  break; //未进行更改 则退出循环
		}
	}
	return Max;
}

template<typename T>
inline void MaxHeap<T>::insertCopy(T &data)
{
	int site = container.size();//获得当前插入最后时的坐标
	container.push_back(data);
	while (container[site / 2] < data&&site != 1) {//极端情况威胁 哨兵的 值不进行交换	
		std::swap(container[site / 2], container[site]);
		site = site / 2;
	}
}

template<typename A, typename T>
inline bool RB_tree<A, T>::insert(A & x)//A 为value_type
{
	if (root == nullptr) root = make_shared<RB_node<A>>(x, false);//根结点为黑色
	auto rootCopy = root;//获得根结点 复制
	auto & father = root->parent;
	bool flag_size = true;//标志比较
	while (rootCopy != nullptr)
	{
		if (rootCopy->data == x) return false;//相等 则失败
		flag_size = (rootCopy->data >= x);
		father = rootCopy;//保存父结点作为 x结点的 索引
		rootCopy = flag_size ? rootCopy->left : rootCopy->right;//左小右大
	}
	rootCopy = make_shared<RB_node<A>>(x,true,father);//设置父节点
	++node_count;//计数加1
	if (father->color == false)return true;//父结点为黑 直接插入
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
           //如果父结点为  祖父的左结点  伯父则为 右 从而返回 伯父结点
		if (granfather->left == fa_node(x))return granfather->right;
		else return granfather->left;
	}		
}

template<typename A, typename T>
inline void RB_tree<A, T>::RB_tree_rebalance(RBpoint<A>& x, point<T>& rt, RBpoint<A>&fa, RBpoint<A>&un)
{
	/*
	红黑树 有 以下 规则
	1 . 结点  为 黑 或者 红
	2. 空结点和根结点 为 黑
	3. 红结点的 子结点为 黑色
	4. 任意结到nullptr(树尾端)  的任何路径 ,所含的 黑结点数 必须相同

	在进行插入时候进行的维护 如果插入为 红结点时  在根节点时违反 2
	父节点为红色时违反性质3
	如果插入黑结点 的时候 违反 4 需要大规模调整 所以 默认为红
	*/
	//分为以下的情况  
	// 1. root为空  将 x作为黑结点插入
	//2. 父结点 为黑结点 直接插入  因为插入的新的结点 Left 和right 为 nullptr 黑色结点 数依然相同
	//3(4) 父结点为红 (祖父肯定是黑) 伯父结点 (黑)  (3) 两种情况  ( 这里默认父结点 在祖父的左结点上  因为判断左边的情况 右结点的情况镜像处理就行了)
	// 3.1    x在父结点的 左结点上  右旋 然后 父结点与祖父结点 颜色交换
	// 3.2   x在父结点的 右结点上    将父结点 作为X的左结点  x代替 父节点的位置
	//  这时  可以将 原来父结点作为  3.1中的 X 处理
	//4.父结点为红 (祖父肯定是黑) 伯父结点 (红)  
	//4.1  只需要颜色改变就行了  祖->红     父  和伯父 ->黑
	auto & tree = rt->parent;//操作子树的结点
	if (un->color == false)
	{
		if (fa == rt->left)
		{
			if (x == fa->left) //3.1情况
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
		else //镜像处理
		{
			if (x == fa->right) //3.1情况
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