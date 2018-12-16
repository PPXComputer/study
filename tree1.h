#ifndef  TREE1_H
#define TREE1_H
/*
*此头文件 使用 儿子兄弟法来表示结点属性
*保存着 二叉树  二叉搜索树  平衡二叉树  哈弗曼树  最大堆  红黑树(代码错误)
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

第二次修改2018年12月11日16:40:12  增加线索二叉树  主要是 将普通二叉树的空节点   指向其 前驱 或后续
并创建RootCopy节点作为 二叉循环链表的环的开始和结尾  未完成部分: 将普通二叉树转化为 线索二叉树    (完成)
( 因为基类的抽象不够, 普通二叉树只能保存 tree_node 结点  无法进行转化  继承 则不能使用此前的功能)

第三次修改2018-12-13 11:33  使用using 的模板特性 增加 _Node参数 即 结点参数  template<typename Ty ,typename Node=default_node<T> >
第一个为类型参数 第二个结点参数   解决了 第一个缺陷
!!!  发现的缺陷 :
1.因为 第三次修改只修改了 Binary_tree 和 Binary_search_tree  .Thread_tree 并没有 更改其他类 所以 其他类有大量的重复构造函数
应该抽象成 point<Ty,Node>
2.设计不够 清晰  因为过早的代码 设计模式并没有运用
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
//avl树的结点 注意应该在初始化的过程中进行 实例化
template<typename Ty>
struct AvlNode
{
	AvlNode() = default;
	AvlNode(Ty& s) :data(s) {}
	shared_ptr<AvlNode<Ty>>left = nullptr;
	shared_ptr<AvlNode<Ty>>right = nullptr;
	Ty data = Ty();
	int height = 0;//平衡因子 有左子树高度-  右子树高度//绝对值不能超过1
	AvlNode<Ty> & operator =(const AvlNode<Ty>&) = delete;
	AvlNode<Ty> & operator =(const AvlNode<Ty>&&) = delete;
	~AvlNode() = default;
};
// 红黑树的结点
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
	//黑为0  红为1
	bool color = true;//默认红  与插入操作进行统一
};

template <typename Ty>
struct Thread_node 
{
	//这两个 表示者 左右 节点 是否 指向的是前驱 或者后驱  
	//默认是指向节点
	Thread_node() {}; //= default;=default;会出错
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
using Ve_Apoint = vector < shared_ptr<AvlNode<Ty> > >;// Avl指针数组别名
template<typename Ty, typename Node = tree_node<Ty >>
using point = shared_ptr<Node>;//  指针别名   将此别名修改为 结点的指针
template<typename Ty, typename Node = tree_node<Ty>>
using vecpo = vector<point<Ty, Node> >;//指针数组别名
template<typename Ty, typename Node = RB_node<Ty >>
using RBpoint = shared_ptr<Node>;//红黑树指针别名
/*template<typename _Ty, typename _Node = AvlNode<_Ty >>
using point = shared_ptr<_Node >;//AVl指针别名*/
//二叉树这里作为  基类 定义打印操作  和 保存一个 protected的指针指向头结点
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
		root = create(s, pos);//意图从++后为0开始  并每次递增
	}
	virtual void print();
    void print_no_recursion()   ;
	virtual ~Binary_tree() = default;
	virtual int depth()
	{
		cout << "\n  二叉树的高度是";
		return depthCopy(this->root);
	}
	Binary_tree<Ty, Node>& operator =(const  Binary_tree<Ty,Node>&) = delete;
private:
	//用于获得遍历的结果 非递归后序遍历  反转 根 右左的答案    获得后序  左右根的答案
	vector<Ty> vec = {};//!!!!注意在改变结点类型 这时T 代表则结点structure
	//转入引用来进行不断递增   ,否则在进入Right循环时 无法进行正常的索引
	inline point<Ty,Node> create(string & s, int &pos);//专门构造普通二叉树
	//使用递归的版本  ForwardTravesal
	void ForTra(const  point<Ty, Node> &s);// 前序遍历与print形成接口
	void MiTra(const point<Ty, Node> &s);//中序遍历结果
	void PosTra(const  point<Ty, Node> &s);
	//后序结果
   //层序遍历 队列实现
	void LeveTra(point<Ty, Node> s);
	//非递归的版本
	void forward(point<Ty, Node> s);
	void mide(point<Ty, Node> s);
	void  postore(point<Ty, Node>& s);
	int depthCopy(point<Ty, Node>& s);
protected:
	point<Ty, Node > root;//因为二叉树搜索树 中需要改变其值所以进行 protected
};

//因为二叉搜索树(二叉排序树)的性质  全部结点满足左小右大   所以 结点的元素不会重复
template<typename Ty, typename Node = tree_node<Ty >>
class Binary_serach_tree :public Binary_tree<Ty, Node>
{
public:
	Binary_serach_tree() = default;
	template<typename Node>
	Binary_serach_tree(Node&s)  {
		for (auto sd : s) insert(sd);
	}
	template<>//对于int的特例化
	Binary_serach_tree(int&s) {
		insert(s);
	}
	//如果插入有重复的元素不做改动
	//这里传入的为值而不是指针
	void insert(Ty&s) { insertCopy(s, this->root); }
	void Delete(Ty&s)//delete  实在想不到解决递归使用root的办法了
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

//哈夫曼树又称为最优二叉树    即带权路径长度    每个结点的权值*长度之和最小 
//每个结点信息都在叶结点上   此时取得叶结点信息 对应 为  左0右1  
//打印方式 形成不同  不用BInary_tree的方法
template<typename Ty, typename Node = tree_node<Ty > >//优化权值的树 所有信息在根节点上 
class Huffman_tree :public Binary_tree<Ty, Node>
{
public:
	Huffman_tree() = default;
	template<typename A>
	Huffman_tree(A &s)
	{
		//转入create之前   pointCopy中元素类型应为对应的指针
		vecpo<Ty> pointCopy;//完成后进入构析
		for (auto& sd : s)
		{
			pointCopy.push_back(std::make_shared<Node>(sd));
		}
		create(pointCopy);//每个元素类型为T
	}
	~Huffman_tree() = default;
	//打印操作使用 是 左为0  右1 打印根结点的编码
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

//平衡二叉树 左右子树的深度不相差1 同时各子树同时满足性质
template<typename Ty, typename Node=AvlNode<Ty> >
class Avl_tree :public Binary_tree<Ty, Node>
{
	Avl_tree() = default;
public:
	template<typename vp = vector<Ty>>//A类型为以T为元素的数组
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
	//二叉树作为基类时使用的是 Tree_node 与此时不同 应该使用Apoint<T>进行实例化参数z
	//返回改变元素分配的指针 即返回子树部分 来通过修改
	//Apoint<_Ty> root = nullptr;默认初始化
	point<Ty,Node>insert(Ty&s) { return insertCopy(s, this->root); }
	//在进行插入时判断需要的旋转操作  并返回调整的AVL 树
	// L =left  R=right 接受的参数是被破坏的结点指针
	//注意旋转操作的左右命名是 因为破坏平衡的结点加入时 对于 所破坏平衡因子的结点 
	//比如 插入结点在被破坏结点的右子树 的右子树上(不管在此树上的左右位置) 则为 RR旋转(而不是什么逆时针旋转)
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

//最大堆  最大值在根结点上  采取数组存储满足完美二叉树 可以在常树时间索引到最大值   则左右结点的大小不做要求  
//进行存储时 使用数组 则 如 INT_MAX 5 1 3 
//代表着最大为 5 左 1  右 3   对应数组下标为  1 2 3则进行叶子结点比较时  进行坐标 /2进行与父结点比较的方式
template<typename Ty>
class MaxHeap
{
public:
	MaxHeap() = default;
	template<typename Node = vector<Ty>>//日常进行列表初始化
	MaxHeap(Node &sd) {
		for (auto &s : sd)  insertCopy(s);
	}
	MaxHeap(std::initializer_list<Ty> sd)//不可以传入模板引用
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
	//第一个值为最大 为int_max 作为哨兵使用 因为叶结点 进行与父结点比较时 为坐标/2
	vector<Ty> container = { INT_MAX };
	void insertCopy(Ty &);

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
template<typename Ty, typename Node = RB_node<Ty>>
class RB_tree
{
public:
	RB_tree() = default;
	template<typename Z = vector<Ty> > //默认为数组
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
private://插入的结点 默认为红
	void printCopy(const RBpoint<Ty>&sd)
	{
		cout << sd->data << "颜色" << sd->color;
		printCopy(sd->left);
		printCopy(sd->right);
	}
	point<Ty, Node> root;
	bool insert(Ty&x);//插入成功 true    重复插入失败 false
	//调整红黑树的操作 参考STL的做法  第一个是 新增结点  第二个是 root
	point<Ty, Node>& fa_node(RBpoint<Ty>&x);//父节点
	point<Ty, Node>& gfa_node(RBpoint<Ty>&x);//祖父结点
	point<Ty, Node>& un_node(RBpoint<Ty>&x);//伯父结点
	//自上而下的程序 进行调整的总程序   注意事项:rt存放祖父结点 同时保存则 修改子树的祖结点
	void RB_tree_rebalance(point<Ty,Node>& x, point<Ty, Node>& rt, point<Ty, Node>&fa, point<Ty, Node>&un);
protected:
	size_t node_count = 0;//结点计数
	//比较大小的操作应该使用 function来进行泛化  这里使用  std::max<lsh ,rhs>; 相等于 lsh>rhs
	//auto & compare = std::max(lhs, rhs);//比较大小的   这里 不用 因为碰到相等情况因为返回 false 
};

/*将二叉树线索化的方式是 将二叉树的空节点 改变成前驱或者后驱
但是前驱和 后驱 只能通过遍历得到 所以 将线索二叉树 又分为 前中后 三种
此为 中序线索二叉树
如果ptr->lchild为空，则存放指向中序遍历序列中该结点的前驱结点。这个结点称为ptr的中序前驱；
如果ptr->Rchild为空，则存放指向中序遍历序列中该结点的后驱结点。这个结点称为ptr的中序后驱；
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
	//shared_ptr<Binary_tree<Ty, Node>> rt = nullptr;保存着真正的root
	point<Ty, Node> RootCopy = nullptr;//此为新增的头结点
	//   pre 临时变量 用于在InThreading中存储Btree的前驱
	void InThreading(point<Ty, Node>& Btree, point<Ty, Node>&pre);   //将普通的二叉树中序线索化
	void MiTra(point<Ty, Node> & rt);//注意 root节点并不是 原来的二叉树的根节点  root->Lnode才是	
	//转入 要改变的二叉树的根节点  加入头结点rootCopy
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
		//提取其复制进入循环
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
	cout << "前序遍历结果为" << std::endl;
	ForTra(this->root);
	cout << std::endl << "中序遍历结果为" << std::endl;
	MiTra(this->root);
	cout << std::endl << "后序遍历结果为" << std::endl;
	PosTra(this->root);
	cout << std::endl << "层序遍历结果为" << std::endl;
	LeveTra(this->root);
}

template<typename Ty, typename Node>
inline void Binary_tree<Ty, Node>::print_no_recursion()
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
		point = std::make_shared<Node>(s[pos]);//进入子树时 先分配子树部分
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
		return;//相等return
	}
}

template<typename Ty, typename Node>
inline point<Ty,Node>
Binary_serach_tree<Ty, Node>::deleteCopy(Ty &s, point<Ty,Node> temp)
{
	shared_ptr<Node> tmp;
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
	create(temp);//进行递归
}

template<typename Ty, typename Node >
inline vecpo<Ty>
Huffman_tree<Ty, Node>::select(vecpo<Ty>& s, int&size)
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
	auto ppx1 = std::make_shared<Node >> (s[0]->data + s[1]->data);
	ppx1->right = s[0];
	ppx1->left = s[1];
	s.erase(s.begin());     //删除二个最小的值  注意删除会使得迭代器失效	
	s.erase(s.begin());     //删除二个最小的值  注意删除会使得迭代器失效	
	s.push_back(ppx1);//压入更新值
	return s;
}

template<typename Ty, typename Node>
inline void Huffman_tree<Ty, Node>::printcopy(point<Ty,Node> &s, int len)
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

template<typename Ty, typename Node>
//第二个参数是方便与insert子树部分和进行 对应当前根节点的解析
inline point<Ty, Node> Avl_tree<Ty, Node>::insertCopy(Ty data, point<Ty, Node>& site)
{
	if (site == nullptr)
	{
		site = make_shared<Node>(data);
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
		else if (temp + 1 <= site - 2) {
			++temp;//变成右结点
			if (container[tempCopy] < container[temp])
				std::swap(container[tempCopy], container[temp]);
			else  break; //未进行更改 则退出循环
		}
	}
	return Max;
}

template<typename Ty>
inline void MaxHeap<Ty>::insertCopy(Ty &data)
{
	int site = container.size();//获得当前插入最后时的坐标
	container.push_back(data);
	while (container[site / 2] < data&&site != 1) {//极端情况威胁 哨兵的 值不进行交换	
		std::swap(container[site / 2], container[site]);
		site = site / 2;
	}
}

template<typename Ty, typename Node>
inline bool RB_tree<Ty, Node>::insert(Ty & x)//A 为value_type
{
	if (root == nullptr) root = make_shared<Node>(x, false);//根结点为黑色
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
	rootCopy = make_shared<Node>(x, true, father);//设置父节点
	++node_count;//计数加1
	if (father->color == false)return true;//父结点为黑 直接插入
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
		//如果父结点为  祖父的左结点  伯父则为 右 从而返回 伯父结点
		if (granfather->left == fa_node(x))return granfather->right;
		else return granfather->left;
	}
}

template<typename Ty, typename Node>
inline void RB_tree<Ty, Node>::RB_tree_rebalance(point<Ty,Node>& x, point<Ty,Node>& rt, point<Ty,Node>&fa, point<Ty,Node>&un)
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
	else {
		rt->color = true;
		fa->color = false; un->color = false;
	}
}

template<typename Ty, typename Node >
void Threaded_tree<Ty, Node>::AddRootCopy(point<Ty, Node>& Btree)
{
	//这里将 root 节点 进行连接 Btree
	RootCopy = std::make_shared<Node>();
	RootCopy->Rthread = false;//根的右节点的线索指向本身 
	RootCopy->right = RootCopy;
	point<Ty, Node> pre = std::make_shared<Node>();
	if (Btree == nullptr) //如果二叉树为空 则 左线索指向本身
	{
		RootCopy->Lthread = true;
		RootCopy->left = Btree;
	}
	else//不为空的情况下进行 添加root
	{
		//这一部分在大话数据结构的193页  对应步骤 1~4
		InThreading(Btree, pre);//此时pre变成 中序遍历的最后一个结点  Btree仍然是未改变
		pre->right = RootCopy;//最后一个结点的 右线索指向头结点
		pre->Rthread = true;

		//处理  最左的节点
		point<Ty,Node> right_node = Btree;
		while (right_node->left != nullptr) right_node = right_node->left;//这里将要  保存 最左边的节点 
		right_node->Lthread = true;
		right_node->left = RootCopy;

		//处理RootCopy  让其指向原本的头结点
		RootCopy->Lthread = true;
		RootCopy->left = Btree;
	}
	Btree = RootCopy;//使基类二叉树的 保存一样的头结点
}

//Btree是指向当前的节点 pre 是他的前驱 
template<typename Ty, typename Node>
inline void Threaded_tree<Ty, Node>::InThreading(point<Ty, Node>& Btree, point<Ty, Node>& pre)
{
	if (Btree == nullptr)
	{
		//此次递归函数  每次的调用时  pre都辅值于当前Btree  则在
		//出现 左右节点为空的情况下 则 pre没有辅值于当前Btree  即 pre做为 Btree的前驱存在
		InThreading(Btree->left, pre);//进行线索化 递归 二叉树 找到 左节点为空的节点
		if (Btree->left == nullptr && pre != nullptr)//左节点为空 则  指向前驱
		{
			Btree->left = pre;// 此时pre 并没有完成赋值    保存的是Btree的前驱 
			Btree->Lthread = false;
		}
		// 因为此时的Btree 后续 并没有访问到 
		// 并在此时 我们有 pre作为Btree的前驱  Btree 为pre的后驱   
		//判断pre作为前驱  是否 没有右节点  将Btree作为后驱进行标记   妙啊 妙啊
		if (pre != nullptr&& pre->right == nullptr)//建立前驱节点的后续线索
		{
			pre->right = Btree;
			pre->Rthread = false;
		}
		pre = Btree;// 此时 pre 由Btree的上一个节点   保存为当前Btree
		InThreading(Btree->right, pre);
	}
}

template<typename Ty, typename Node>
inline void Threaded_tree<Ty, Node>::MiTra(point<Ty, Node>& rt)
{
	if (rt == nullptr) return;
	point<Ty, Node> head = rt->left;//找到真正的头结点
	//   此时的线索二叉树可看做一个双向循环链表  环 起点终点 是root         
		//因为存在后续 所以 此为 链表的循环遍历过程
		while (head!=nullptr&&head != rt)//不断的向后续前进  直到回到root
		{
			while(!head->Lthread)//是结点则 进入
			head = head->left;
			cout << head->data << " \n";
		
		while (head->Rthread&&head->right != rt)
		{
			head = head->right;//进入右子树的部分
			cout << head->data;
		}
		head = head->right;
		}
}

#endif // !TREE1_H