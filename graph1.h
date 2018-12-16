/*                                       ���ļ����洢�йؼ�����ͼ�Ĵ���
*ʵ�ֹ���ͼ���ڽӱ�(    ����ά���� �� List_[0]={ 2,3      3,4      }  ��ʾ 0--2 Ϊ�� Ȩֵ3  0---3Ϊ��Ȩֵ4  �ʺ�ϡ��ͼ  ȱ����ظ���¼��   )
*ע�� �ڽ̲��� �ڽӱ� �ı�ʾ������ vector<list<T>> List  �� List[0] ={  2->3->4 }��ʾ ����0����2 3 4
*���ڽӾ���(Matrix[3][4]=2 ��ʾ3---4 Ϊ��Ȩֵ 2    ȨֵΪ INT_MAX ��ʾû�б�  �ʺϳ���ͼ     ������������Ǿ���洢���Խ�ʡ�ռ�     )
*  ���ڽӾ���  ����ȱ߽��� vector<list< T>> list   List  �� List[0] ={  2->3->4 }��ʾ ����2 3 4 ����0
* ʮ������ ���ǽ�  ������vector<(out< T> ,in<T >) > >  �����in ����  ���� ��out  ��  ����һ����� ���а� �ڽӱ��д�ǰ �����������ӵ�
* �Ľڵ�  ��Ϊ��ȹ�ϵ��������    ���Ӷ��� �ڽӱ�һ�� O(N+M)  N��  M�ڵ�
*ʵ��BFS  breath  first search  �����������
*���÷�������visited[]   �����ȳ�ʼ�� ȫ��Ϊ0  ������� �� visited[3]=1 ��ʾ ���3 �ѱ�����(����������ɶ����λ��ȷ����)
*���ڽӾ�����ڽӱ� ����  ������ ���Ϊ1    �������������ߵĽ��ȫ����һ��
*ʵ��DFS depth  fisrt search   �����������  ѡ�����  �����ߵĵ� ��������� ���η��ʶ��еĵ� ������Ϊ��� �ظ����� (������������)
*                       BFS�ķ��ʵĽڵ�ɿ���Ϊ һ��������   ����Ϊ �������������
*!!!ע��DijKstra�㷨��floyd�㷨    �����Ǹ�Ȩͼ
*DijKstra�㷨���·�㷨     ������� constr[]      ��·��������������side[]
*�� ������� �������� constr������  ���constr���ڵĵ㰴Ȩֵ�������side[]  (���û���ڽӵ� �����������)
*��ѡ��side��СȨֵ�ĵ���� constr����  ����constr����ӵ����� ˢ�� side[]      �ظ�  ��  ֱ�������յ�
*
*floyd�㷨       ��������������֮������·�� ����Դ���·������
* ���ȹ����������  D���� ����� ͼ���ڽӾ���  D[2][3]=9 ��ʾ ���� 2��3 ֱ����ͨ ȨֵΪ9  INT_MAX����ͨ
*P �������� �����������ת�� (  ���� ��������������   A->B ��Ȩֵ�� Ϊ   ��ʱ ����C�� �� A->C->B =9 <10  ���CΪ��ת��
*   �� ������һ����ʹ��  ���������Ȩֵ�� ����   �Ǵ˵� Ϊ��ת��   ) p[2][3 ]= 1 ��ʾ��ת��ϵΪ 2->1->3  ����1ʹ�� 2 ->3��Ȩֵ�ͼ�С
*P�����ʵ�� ����Ϊ  1.  �Ƚ�P����  ����D�����ʼ�� ���A,B֮���б� �� P[A][B]=A ����Ϊ -1
*2.  �����������Դ� ��������  ���� ����  ����A  �������� C D ���� D[C][A]+D[D][A] <D[C][D]  z��D[C][D]=D[C][A]+D[D][A] (�˴�Ϊ�����������)  P[C][D]=A
*3.  ��������������� �� E    �������� C D ���� P[C][E]+p[D][E] <p[C][E]  z��P[C][D]=E(�˴�Ϊ�����������)   �ظ�����2  ֱ�����ж��㶼����
*
*�� P���鱣�����Ϣ�������·��   ���P[A][B]=C    ��ʾ·��ΪA->C->B��ȨֵΪ D[C][A]+D[D][A]
*
*!!!ע�� Prim  ��kruskal  (�㷨��Ҫ�޻�· �޶�������)
*Prim   ������� constr[] �������  ���constr�����д�ŵ���ٽ�� ��Ȩֵ��С�ķ���constr�� �ظ��˹��� ֱ�����еĶ�����������(N -1 ���� )
*Krsukal  ÿ����¼Ȩֵ��С�ı�  �ظ��˹��� ֱ�����еĶ�����������(N -1 ���� )
*!!!!!���ļ���ȱ��
*�� ʹ�ô�������  ���� ����STL ���³����ڴ�ռ��ƫ��
*��  ��Ʋ�������  ��: vertexes  ��� ������ַ���  ����������������  ��ʾ���  ���� ��Ϣ���� ���ܷ��� Ȩֵ������  ���������̶ȹ���
*����2018-09-20 ʱ��23:36
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
constexpr auto INTmax = 6555;//�����ڽӾ����Ȩֵ�����ֵ;
using Matrix = vector<vector<int>>;//�������ͱ���
using List_ = vector<vector<pair<int, int>>>;//�ڽӱ����   ... ȱ��
//�ڽӱ����ͱ���
//��������ͼ��Ȩͼ ʹ���ٽӱ�洢  ��  ����
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
	Graph &operator=(const Graph&) = delete;
	~Graph() = default;
private:
	string vertexes;//������еĶ��� ���ַ���
	Matrix matrix;//�ڽӾ��� 
	List_ List;//�ڽӱ� pair ��һ���ǽ�� �ڶ�����Ȩֵ
	int numVertexes = 0;//������
	int numEdges = 0;//����
	void BFS(vector<int>&);//Breath First Search ������������㷨
	void DFS(vector<int>&, int);//Depth First Search �����������	�㷨
	void BFSTraverse();//����BFS��ȫ������
	void DFSTraverse();//����DFS��ȫ������
	//��BFS�ķ��ʵĽڵ�ɿ���Ϊ һ��������   ����Ϊ �������������
	void unweighted(int&);//��Ȩͼ�ĵ�Դ���·��  ��Ϊ����ͼ��Ȩ ���Դ˷����� Ĭ�Ͻ�Ȩֵ��Ϊ1  
	void DijKstra(int &);//��Ȩͼ�����·���㷨  �� ÿ�ν���·��ѡ��ʱʹ�����Ž�
	//ͼ��������ͨͼ  �� û�� ����������
	vector<pair<int, int>> tree;//��ʾΪ���·��  ����  tree[1]={2,3}��ʾ  2---3��·��
	//��С������  ʵ�ִ��ͨ  ʵ����Ȩֵ����С������� �������ԵĽ��  
	//����Ĳ��������� �ڶ�����е��±� ��Ϊ���
	void Prim(int &);//�ӵ㷨
	void Kruskal();//  �ӱ߷� kruskal�㷨������С������ÿ��ѡȡ��С�ı� ֱ��ȫ�������¼
	void check_site(int &);//�����������  ����
};

inline void Graph::creat()
{//��ע�͵Ĵ�����ԭ���Ĵ���
	cout << "�����붥�����ͱ���";
	//numVertexes = 8; numEdges=5;
	cin >> numVertexes >> numEdges;
	cout << "���붥����Ϣ���붥���(�ַ���)";
	//���붥����붥���
	//vertexes = "abcdefgh";
	cin >> vertexes;
	/*	����ʾ�� ��ͨ�� ��ӳ�ʼ��vector���������� ��ʱ�ռ����
	for (int i = 0; i < numVertexes; ++i)
		{
			vector<int>retemp;//����Ԥ���ռ�
			for (int p = 0; p < numVertexes; ++p)
			{
				retemp.push_back(INTmax);
			}
			matrix.push_back(retemp);//ȷ����ʼ��
		}*/
	matrix.reserve(numVertexes);//��ʼ���ռ��С
	cout << "�����������������ͼ�� ��Ӧ�±� i,j ����Ȩֵ";
	int weghit1 = 0; int j = 0; int i = 0;
	for (int p1 = 0; p1 < numEdges; ++p1)
	{
		cin >> i >> j >> weghit1;
		matrix[i][j] = weghit1;
		matrix[j][i] = weghit1;//��ΪN*N�ľ���Գ�
	}
	//����ռ�  ��Ҫ���䶯̬����List.reserve(numVertexes);
	//ɨ���ڽӾ����һ��  ������ڽӱ�
	List.reserve(numEdges);
	for (int p1 = 0; p1 < numEdges; ++p1)
		for (int p2 = 0; p2 < numEdges; ++p2)
		{
			int matemp = matrix[p1][p2];
			if (matemp != INTmax)
				List[p1].push_back(std::make_pair(p2, matemp));//Խ��??? 
		}
}

inline void Graph::BFS(vector<int>&visited)
{
	//���ö���ʵ�������ڲ������
	queue<int> contianer;
	//1��ʾ�Ѿ��������
	for (int i = 0; i < numVertexes; i++)//������ɨ�� ��Ӧ ���			
	{
		if (visited[i] == 0)//û�з�����ѹ�����
		{
			visited[i] = 1;
			cout << vertexes[i];//��ӡ����
			contianer.push(vertexes[i]);
			while (!contianer.empty())
			{
				auto temp = contianer.front();
				contianer.pop();
				//ɨ������һ�н���  �ж�����������û�з��ʵĽ��
				for (int j = 0; j < numVertexes; ++j)
				{
					if (matrix[i][j] != INTmax && !visited[j])
					{
						visited[j] = 1;
						cout << vertexes[j];//��ӡ�����
						contianer.push(vertexes[j]);
					}
				}
			}
		}
	}

}

inline void Graph::DFS(vector<int>&visited, int site)
{
	//�������  ��ײ��ǽ����ͷ
	visited[site] = 1;
	int j = 0;
	cout << vertexes[site];//��ӡ����
	for (; j < numVertexes; ++j)
	{
		if (matrix[site][j] != INTmax && !visited[j])//Ϊ�ڽӵ� �� û�б����ʹ�
			DFS(visited, j);//������һ���ڵ�
	}
}

inline void Graph::BFSTraverse()
{
	vector<int> visited;//���ʱ�־����
	for (auto sd = numVertexes; sd > 0; --sd)
	{//0��ʾ δ����
		visited.push_back(0);//ȫ����ʼ��
	}
	cout << "DFS�ı������";
	BFS(visited);
	cout << std::endl;
}

inline void Graph::DFSTraverse()
{
	vector<int> visited;//���ʱ�־����
	for (auto sd = numVertexes; sd > 0; --sd)
	{//0��ʾ δ����
		visited.push_back(0);//ȫ����ʼ��
	}
	cout << "DFS�ı������";
	for (int i = 0; i < numVertexes; ++i)
	{
		if (!visited[i])
			DFS(visited, i);
	}
	cout << std::endl;
}

inline void Graph::unweighted(int& i)
{ //Ĭ��ԭ��  Ϊvertexe[ i ]
	check_site(i);
	vector<int> dist;//distance ��ʼ��Ϊ-1��ʾδ���ʵĽ��      ԭ��Ϊ0  Ȩֵ1
	//dist[] ��ֵ��ʾ�� ԭ��ľ���   
	for (int s = 0; s < numVertexes; ++s)
	{
		dist.push_back(-1);
	}
	vector<int> path;// ��Ӧ�������Ƕ�������±�  path[0]=1��ʾΪ  ��V1~~V0
	for (int s = 0; s < numVertexes; ++s)
	{
		path.push_back(-1);
	}
	queue<int> container;//�����Ӧ���±�
	container.push(i);
	while (!container.empty())
	{
		auto temp = container.front();//���浱ǰ�±�
		for (int i = 0; i < numVertexes; ++i)
		{
			auto sd = matrix[temp][i];
			if (sd != INTmax)//�������ڵ�
				if (dist[sd] == -1)
				{
					dist[sd] = dist[temp] + 1;//���������+Ȩֵ1
					path[sd] = temp;
				}
		}
	}
	cout << "�����ӦֵΪ";
	for (auto s : dist) { cout << s; }cout << std::endl;
	cout << "·��Ϊ";
	for (auto s : path) { cout << s; }//��ӡ��Ϣ
}

inline void Graph::DijKstra(int & i)
{
	//��Ϊ̰���㷨  ÿ��ѡ�����·��
	//1.. ����� ѹ������
	// 2...ѡ�� ������Ԫ�ص� ��̵��ⲿ���  ѹ������  ֱ�����ⲿ���
	//3...  ˢ���ⲿ�����   �ظ� 2
	check_site(i);
	vector<int> visited;//���ʱ�־����
	for (auto sd = numVertexes; sd > 0; --sd)
	{//0��ʾ δ����
		visited.push_back(0);//ȫ����ʼ��
	}
	vector<int>container(vertexes[i]);//����������  ���洢��ֵ��ʾΪ ���
	visited[i] = 1;//������
	vector<int>path;//����Ӧ������  ��  path[1]=2;  ���� container[1]����ʾ�Ľ��  Ȩֵ�� Ϊ2
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
					sentry = i;//��¼Ȩֵ��С��Ľ��
					path[j] = i;//��ʾ  �� J ~~ I 
				}
			}
		if (min != INTmax)//������С��
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
	//��Ϊ��������N����� N-1����  �޻�·
	// ��������   �����еı� �������еĽ��(ͼ������ͨ)
	//Ȩֵ����С(�˲���������DijKstra�㷨  ѡ��һ����Ϊ���ÿ����¼��С )
	check_site(i);
	vector<int> visited;//���ʱ�־����
	for (auto sd = numVertexes; sd > 0; --sd)
	{//0��ʾ δ����
		visited.push_back(0);//ȫ����ʼ��
	}
	vector<int>container(vertexes[i]);//����������  ���洢��ֵ��ʾΪ ���
	visited[i] = 1;//������
	while (container.size() != numVertexes)//�������ж����� �˳�
	{
		int min = INTmax; int sentry = 0; int sign = 0;
		for (auto j : container)
			for (int i = 0; i < numVertexes; ++i)
			{
				if (matrix[j][i] < min&&visited[i] != 0)
				{
					min = matrix[j][i];
					sign = j;//��¼��ʼ�±�
					sentry = i;//��¼Ȩֵ��С��Ľ��
				}
			}
		if (min != INTmax)//������С��
		{
			visited[sentry] = 1;
			container.push_back(sentry);
			tree.push_back({ sign,sentry });//ѹ��·��
		}
		else { cout << "��������������"; break; }
	}

}

inline void Graph::Kruskal()
{
	//ÿ����¼Ȩֵ��С�ı�  ֱ��Ϊ N-1���߾�����
	//ʵ����Сֵ��ɾ�� Ӧʹ����С�� �ɻ�ó���ʱ��ĸ��Ӷ�
	List;//�ڽӱ�
	set<std::tuple<int, int, int>>  container;//ǰ�����int  int  ��ʾһ����  ���ΪȨֵ
	for (int i = 0; i < numEdges; ++i)
		for (int size = 0; size < List.size(); ++size)
		{
			int temp = 0; int temp2 = 0;//������ʱ���������� ��ͬһ���� ����set��  ����С�ķ�ǰ��
			if (size < List[i][size].first) {
				temp = size; temp2 = List[i][size].first;
			}
			else
			{
				temp2 = size; temp = List[i][size].first;
			}
			container.insert(std::make_tuple(temp, temp2, List[i][size].second));
		}
	//����Ȩֵ������ǰ�Ȩֵ��С�ߵļ���
	std::sort(container.begin(), container.end(),
		//lambda���ʽ   
		[](std::tuple<int, int, int > & lhs, std::tuple<int, int, int >& rhs)
	{
		if (std::get<2>(lhs) < std::get<2>(rhs))return true;
		else return  false; //Ȩֵ�Ƚ�
	}
	);

	if (container.size() < numEdges - 1)cout << "����С��";
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
			cout << "������������Ĳ���";
			cin >> i;
		}
	}
}
#endif // !GRAPH1_H
