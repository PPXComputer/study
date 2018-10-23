/*
*此文件来存储有关图的代码
*实现关于图的邻接表(    即二维数组 如 List_[0]={ 2,3      3,4      }  表示 0--2 为边 权值3  0---3为边权值4 类似   适合稀疏图  缺点会重复收录边   )
*和邻接矩阵(Matrix[3][4]=23  表示3---4 为边权值 23    如果权值为 INT_MAX 表示没有边  适合稠密图     如果利用上三角矩阵存储可以节省空间     )
*实现BFS  breath  first search  深度优先搜索  设置访问数组visited[]  从起点出发把能走的结点全部走一遍
*实现DFS depth  fisrt search   广度优先搜索  选择起点  将能走的点 放入队列中 依次访问队列的点 将其作为起点 重复过程 (类似与层序遍历) 
*DijKstra算法最短路算法     存放数组 constr[]      按路径最短排序的数组side[]
*㈠ 设置起点 将起点放入 constr数组中  检查constr相邻的点按权值排序放入side[]  (如果没有邻接点 重新设置起点)
*㈡选择side最小权值的点进入 constr数组  根据constr的领接点重新 刷新 side[]      重复  ㈠  直到到达终点
*!!!注意 Prim  和kruskal  (算法需要无回路 无独立顶点)
*Prim    存放数组 constr[] 设置起点  检查constr数组中存放点的临结点 将权值最小的放入constr中 重复此过程 直到所有的顶点在数组中(N -1 条边 )
*Krsukal  每次收录权值最小的边  重复此过程 直到所有的顶点在数组中(N -1 条边 )
*!!!!!此文件的缺点
*㈠ 使用大量容器  过度 依赖STL 导致程序内存占用偏高
*㈡  设计不够清晰  如: vertexes  存放 顶点的字符串  其他相关数组存坐标  表示结点  导致 信息混乱 不能分清 权值和坐标  各项依赖程度过高
*日期2018-09-20 时间23:36  
*/
#ifndef GRAPH1_H
#define GRAPH1_H
#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<set>
#include<utility>
#include<memory>
#include<tuple>
using std::cin;
using std::cout;
using std::shared_ptr;
using std::vector;
using std::make_shared;
using std::queue;
using std::pair;
using std::set;
using std::string;
constexpr auto INTmax = 6555;//定义邻接矩阵的权值的最大值;
using Matrix = vector<vector<int>>;//矩阵类型别名
using List_ = vector<vector<pair<int, int>>>;
//邻接表类型别名
//构造无向图有权图 使用临接表存储  和  矩阵
class Graph
{
public:
	Graph() = default;
	void creat();
	void print()
	{
		BFSTraverse();
		DFSTraverse();
	}
	const  Graph &operator=(const Graph&) = delete;
	~Graph() = default;
private:
	string vertexes;//顶点表
	Matrix matrix;//邻接矩阵 
	List_ List;//邻接表 pair 第一个是结点 第二个是权值
	int numVertexes = 0;//顶点数
	int numEdges = 0;//边数
	void BFS(vector<int>&);//Breath First Search 广度优先搜索算法
	void DFS(vector<int>&, int);//Depth First Search 深度优先搜索	算法
	void BFSTraverse();//利用BFS的全部遍历
	void DFSTraverse();//利用DFS的全部遍历
	void unweighted(int&);//无权图的单源最短路径  此为无向图有权 所以此方案将 默认将权值看为1  
	void DijKstra(int &);//有权图的最短路径算法  即 每次进行路径选择时使用最优解
	//图必须是连通图  即 没有 单独结点存在
	vector<pair<int, int>> tree;//表示为结点路径  比如  tree[1]={2,3}表示  2---3的路径
	//最小生成树  实现村村通  实现在权值和最小的情况下 连接所以的结点  
	//传入的参数代表则 在顶点表中的下标 作为起点
	void Prim(int &);
	void Kruskal();//kruskal算法构造最小生成树每次选取最小的边 直到全部结点收录
	void check_site(int &);//检查输入的起点  坐标
};

inline void Graph::creat()
{//所注释的代码是原来的代码
	cout << "请输入顶点数和边数";
	//numVertexes = 8; numEdges=5;
	cin >> numVertexes >> numEdges;
	cout << "输入顶点信息进入顶点表(字符串)";
	//输入顶点进入顶点表
	//vertexes = "abcdefgh";
	cin >> vertexes;
	/*	错误示范 在通过 添加初始化vector来扩大容量 会时空间剧增
	for (int i = 0; i < numVertexes; ++i)
		{
			vector<int>retemp;//分配预留空间
			for (int p = 0; p < numVertexes; ++p)
			{
				retemp.push_back(INTmax);
			}
			matrix.push_back(retemp);//确保初始化
		}*/
	matrix.reserve(numVertexes);//初始化空间大小
	cout << "接下来请输入此无向图的 对应下标 i,j 和其权值";
	int weghit1 = 0; int j = 0; int i = 0;
	for (int p1 = 0; p1 < numEdges; ++p1)
	{
		cin >> i >> j >> weghit1;
		matrix[i][j] = weghit1;
		matrix[j][i] = weghit1;//此为N*N的矩阵对称
	}
	//分配空间  需要分配动态数组List.reserve(numVertexes);
	//扫描邻接矩阵的一行  相等于邻接表
	List.reserve(numEdges);
	for (int p1 = 0; p1 < numEdges; ++p1)
		for (int p2 = 0; p2 < numEdges; ++p2)
		{
			int matemp = matrix[p1][p2];
			if (matemp != INTmax)
				List[p1].push_back(std::make_pair(p2, matemp));//越界??? 
		}
}

inline void Graph::BFS(vector<int>&visited)
{
	//利用队列实现类似于层序遍历
	queue<int> contianer;
	//1表示已经访问完成
	for (int i = 0; i < numVertexes; i++)//进行列扫描 对应 结点
	{
		if (!visited[i])//没有访问则压入队列
		{
			visited[i] = 1;
			cout << vertexes[i];//打印顶点
			contianer.push(vertexes[i]);
			while (!contianer.empty())
			{
				auto temp = contianer.front();
				contianer.pop();
				//扫描矩阵的一行进行  判断与其相连并没有访问的结点
				for (int j = 0; j < numVertexes; ++j)
				{
					if (matrix[i][j] != INTmax && !visited[j])
					{
						visited[j] = 1;
						cout << vertexes[j];//打印顶点表
						contianer.push(vertexes[j]);
					}
				}
			}
		}
	}

}

inline void Graph::DFS(vector<int>&visited, int site)
{
	//深度优先  不撞南墙不回头
	visited[site] = 1;
	int j = 0;
	cout << vertexes[site];//打印顶点
	for (; j < numVertexes; ++j)
	{
		if (matrix[site][j] != INTmax && !visited[j])
			DFS(visited, j);
	}
}

inline void Graph::BFSTraverse()
{
	vector<int> visited;//访问标志数组
	for (auto sd = numVertexes; sd > 0; --sd)
	{//0表示 未访问
		visited.push_back(0);//全部初始化
	}
	cout << "DFS的遍历结果";
	BFS(visited);
	cout << std::endl;
}

inline void Graph::DFSTraverse()
{
	vector<int> visited;//访问标志数组
	for (auto sd = numVertexes; sd > 0; --sd)
	{//0表示 未访问
		visited.push_back(0);//全部初始化
	}
	cout << "DFS的遍历结果";
	for (int i = 0; i < numVertexes; ++i)
	{
		if (!visited[i])
			DFS(visited, i);
	}
	cout << std::endl;
}

inline void Graph::unweighted(int& i)
{ //默认原点  为vertexe[ i ]
	check_site(i);
	vector<int> dist;//distance 初始化为-1表示未访问的结点      原点为0  权值1
	//dist[] 的值表示到 原点的距离   
	for (int s = 0; s < numVertexes; ++s)
	{
		dist.push_back(-1);
	}
	vector<int> path;// 对应的数字是顶点表格的下标  path[0]=1表示为  从V1~~V0
	for (int s = 0; s < numVertexes; ++s)
	{
		path.push_back(-1);
	}
	queue<int> container;//保存对应的下标
	container.push(i);
	while (!container.empty())
	{
		auto temp = container.front();//保存当前下标
		for (int i = 0; i < numVertexes; ++i)
		{
			auto sd = matrix[temp][i];
			if (sd != INTmax)//搜索各节点
				if (dist[sd] == -1)
				{
					dist[sd] = dist[temp] + 1;//在其基础上+权值1
					path[sd] = temp;
				}
		}
	}
	cout << "距离对应值为";
	for (auto s : dist) { cout << s; }cout << std::endl;
	cout << "路径为";
	for (auto s : path) { cout << s; }//打印信息
}

inline void Graph::DijKstra(int & i)
{
	//此为贪心算法  每次选择最断路径
	//1.. 将起点 压入容器
	// 2...选择 容器中元素的 最短的外部结点  压入容器  直到无外部结点
	//3...  刷新外部结点数   重复 2
	check_site(i);
	vector<int> visited;//访问标志数组
	for (auto sd = numVertexes; sd > 0; --sd)
	{//0表示 未访问
		visited.push_back(0);//全部初始化
	}
	vector<int>container(vertexes[i]);//结点访问数组  所存储的值表示为 结点
	visited[i] = 1;//起点访问
	vector<int>path;//所对应的坐标  如  path[1]=2;  到达 container[1]所表示的结点  权值和 为2
	for (int i = 0; i < numVertexes; ++i) {
		path.push_back(0);
	}
	while (true)
	{
		int min = INTmax; int sentry = 0;
		for (auto j : container)
			for (int i = 0; i < numVertexes; ++i)
			{
				if (matrix[j][i] < min&&visited[i] != 0)
				{
					min = matrix[j][i];
					sentry = i;//记录权值最小点的结点
					path[j] = i;//表示  从 J ~~ I 
				}
			}
		if (min != INTmax)//存在最小点
		{
			visited[sentry] = 1;
			container.push_back(sentry);

		}
		else break;
	}
	for (auto sd : container) { cout << sd; }
	for (auto sd : path) { cout << sd; }
}

inline void Graph::Prim(int & i)
{
	//因为是树所以N个结点 N-1条边  无回路
	// 是生成树   用现有的边 连接所有的结点(图必须连通)
	//权值和最小(此部分类似于DijKstra算法  选择一个作为起点每次收录最小 )
	check_site(i);
	vector<int> visited;//访问标志数组
	for (auto sd = numVertexes; sd > 0; --sd)
	{//0表示 未访问
		visited.push_back(0);//全部初始化
	}
	vector<int>container(vertexes[i]);//结点访问数组  所存储的值表示为 结点
	visited[i] = 1;//起点访问
	while (container.size() != numVertexes)//保存所有顶点则 退出
	{
		int min = INTmax; int sentry = 0; int sign = 0;
		for (auto j : container)
			for (int i = 0; i < numVertexes; ++i)
			{
				if (matrix[j][i] < min&&visited[i] != 0)
				{
					min = matrix[j][i];
					sign = j;//记录起始下标
					sentry = i;//记录权值最小点的结点
				}
			}
		if (min != INTmax)//存在最小点
		{
			visited[sentry] = 1;
			container.push_back(sentry);
			tree.push_back({ sign,sentry });//压入路径
		}
		else { cout << "这样的树不存在"; break; }
	}

}

inline void Graph::Kruskal()
{
	//每次收录权值最小的边  直到为 N-1条边就行了
	//实现最小值的删除 应使用最小堆 可获得常数时间的复杂度
	List;//邻接表
	set<std::tuple<int, int, int>>  container;//前面二个int  int  表示一条边  最后为权值
	for (int i = 0; i < numEdges; ++i)
		for (int size = 0; size < List.size(); ++size)
		{
			int temp = 0; int temp2 = 0;//利用临时变量来进行 将同一条边 加入set中  坐标小的放前面
			if (size < List[i][size].first) {
				temp = size; temp2 = List[i][size].first;
			}
			else
			{
				temp2 = size; temp = List[i][size].first;
			}
			container.insert(std::make_tuple(temp, temp2, List[i][size].second));
		}
	//进行权值排序就是按权值最小边的集合
	std::sort(container.begin(), container.end(),
		[](std::tuple<int, int, int > & lhs, std::tuple<int, int, int >& rhs)
	{
		if (std::get<2>(lhs) < std::get<2>(rhs))return true; else false; }
	);

	if (container.size() < numEdges - 1)cout << "无最小树";
}
inline void Graph::check_site(int &i)
{
	int size = vertexes.size();
	if (i<0 || i>size - 1) {
		try
		{
			throw i;
		}
		catch (const int&)
		{
			cout << "请你重新输入的参数";
			cin >> i;
		}
	}
}
#endif // !GRAPH1_H
