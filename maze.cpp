#include<iostream>
#include<Windows.h>
#include<ctime>
using namespace std;

const int N = 20;
const int M = 20;
enum  
{
	//这个EMPTY_again是原来是已经遍历过的空节点
	//█ →←↑↓□×★
	ROAD,//□
	OUTWALL,//█
	INWALL, //█
	EMPTY,//□
	UP, //↑
	DOWN,//↓
	LEFT, //←
	RIGHT,//→
	END,//★
	EMPTY_again//×
};

//以下为Windows的函数 隐藏光标
void hideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info  = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//刷新屏幕 
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}


// position 表示坐标
// x,y初始化为1
struct Pos
{
	Pos() 
	{
		x = 1;
		y = 1;
	};

	Pos(int a, int b)
	{
		x = a;
		y = b;
	}
	
	int x ;
	int y ;
};


//定义自己的堆栈 因为 下面要用到
// pop 弹出一个元素 push 推入一个 元素 ,看看是否为空
//top 查看现在栈顶的元素 empty查看站是否为空
class MyStack
{
public:
	MyStack();
	void push(Pos i);
	//如果不是到了 底部 则可以弹出元素 
	void pop();
	Pos top();
	bool empty();
	~MyStack();

private:
	//最大情况是全部元素 进入 栈中
	Pos sd[M*N];
	
	//指明现在堆栈元素的位置
	int index; //初始化为 -1 
};

MyStack::MyStack()
{
	//堆栈全部初始化 (1,1)
	for (int i = 0; i < 400; i++)
	{
		sd[i] = Pos();
	}
	index=-1;
}

void MyStack::push(Pos i)
{
	index++;
	sd[index] = i;
}

void MyStack::pop()
{
	if (index != -1)
	{
		index--;
	}
}

Pos MyStack::top()
{
	if (index != -1)
	{
		return sd[index];
	}
	return Pos();
}

bool MyStack::empty()
{
	if (index == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

MyStack::~MyStack()
{
}

class maze
{
public:
	maze();

	void show();
	
	~maze();
private:
	
	int ppx [M+1][N+1] ;
	//标记数组 访问为 1 默认为 0
	int visited[M+1][N+1];
	//对应着四个坐标
	Pos area[4]; 
	//周围的上下左右坐标+方便 进行 方向判断
	//	start+dir[0]-->上 start+dir[1]-->下
	int dir[4][2]; 

	void init() {
		for (int i = 0; i < M+1; i++)
		{
			for (int j = 0; j < N+1; j++)
			{
				//初始化 全部为 墙
				ppx[i][j] = INWALL;
				//默认未 标记状态
				visited[i][j] = 0;
			}
		}
		for (int i = 0; i < 4; ++i) {
			area[i] = Pos(-1, -1);
		}
		//分别对应上下左右 
		//-1,0 1,0  0,-1 ,0,1
		
			dir[0][0]=-1; dir[0][1]=0;

			dir[1][0]=1;dir[1][1]=0;
		
			dir[2][0]=0;dir[2][1]=-1;
			
			dir[3][0]=0;dir[3][1]=1;
	}
	//生成当前允许 从上下左右方向   0 1 2 3的坐标

	//int [][]
	Pos* Inarea(int x, int y,int&size);
	
	void mazeCopy();

	bool direction(Pos& cur);

	void path();

	void print();
	
	//判断坐标是否 合法 并且 没有被访问
	bool Inarea(Pos on);
	
	void updateMaze(unsigned int sleep=70)
	{
		hideCursor();
		gotoxy(0, 0);
		print();
		//ctime.h中的函数 进行 暂停一段时间
		Sleep(sleep);
	}
};

maze::maze()
{
}

void maze::show()
{
	init();
	mazeCopy();
	path();
}

maze::~maze()
{
}

//查看上下左右是否可以走  返回数组和 数组的大小
Pos* maze::Inarea(int x, int y,int &size)
{  //上下左右的坐标  查看是否合格
	//默认为 -1,-1作为标记
	size = 0;
	for (int i = 0; i < 4; ++i)
	{
		Pos cur(x, y);
		cur.x += dir[i][0];
		cur.y += dir[i][1];
		if (Inarea(cur))
		{
			area[size] = cur; 
			size = size + 1;
		}
	}
	return area;
}

void maze::mazeCopy()
{
	Pos my;
	//使得每次生成的随机数不同
	srand((unsigned)time(NULL));
	MyStack container;
	container.push(my);//将初始化坐标为1 ,1
	visited[my.x][my.y] = 1;//初始点 应该访问了
	while (!container.empty())
	{
		my = container.top();
		int size = 0;//指明ve中 可以访问坐标数
		 Inarea(my.x, my.y,size);//将可访问的坐标 放在areaCopy中
		if (size>0)
		{//生成一个在size以内的随机数 
			int seed = rand() % size;
			Pos next = area[seed];
			//访问旁边坐标  走1个方向  但是标记size-seed个其他方向
			for (int i = seed; i < size; i++)
			{
				int x = area[i].x;
				int y = area[i].y;
				visited[x][y] = 1;
			}
			ppx[next.x][next.y] = EMPTY;
			my = next;
			container.push(my);
			updateMaze();
		}
		else{
			container.pop();//break; 
			}
	}
}

//找路的 坐标显示  转入当前坐标从上下左右中 找到一个 并更换图标  没有路就返回

bool maze::direction(Pos &cur)
{
	//0 123对应上下左右
	int VE[4] = {-1,-1,-1,-1};//保持下一个坐标
	int size = 0;
	//使得每次生成的随机数不同
	srand((unsigned)time(NULL));
	
	for (int i = 0; i < 4; ++i)//上下左右
	{
		Pos next = cur;
		next.x += dir[i][0];
		next.y += dir[i][1];
		if (ppx[next.x][next.y] == EMPTY || ppx[next.x][next.y]==END)
			{	
				VE[size]=i;
				size++;
			}
	}
	if (size<=0)
	{
		return false;
	}
	int di = VE[0];//对应方向
	switch (di)
	{
	//对应上下左右改变原先坐标
	case 0: ppx[cur.x][cur.y] = UP;
	 break;
	 
	case 1:ppx[cur.x][cur.y] = DOWN;
	 break;
	 
	case 2:ppx[cur.x][cur.y] = LEFT;
	 break;
	 
	case 3:ppx[cur.x][cur.y] = RIGHT;
	 break;
	 
	default:
	break;
	
	}
	cur.x += dir[di][0];
	
	cur.y += dir[di][1];//改变当前坐标
	
	return true;
}
//深度优先遍历
void maze::path()
{
	MyStack container;
	Pos start;//起点
	
	ppx[M-1][N-1] = END;//终点
	
	container.push(start);
	
	//非空或者 到达 mn 处
	while (!container.empty() && (start.x != M-1 || start.y != N-1))
	{
		start = container.top();
		ppx[start.x][start.y] = EMPTY_again;//进行标记
		//如果有下一个坐标
		if (direction(start))
		{
		 
		container.push(start);
		}
	
		else{
			
			ppx[start.x][start.y] = EMPTY_again;
			container.pop();
			updateMaze(500);
		}
	}
	
	if (!container.empty())
	{
	updateMaze(500);
	cout << std::endl << "happy ending";
	} 
	else
	{
		cout << std::endl << "bad ending";
	}
}

 void maze::print()
{
	//打印作为 遍历
	cout << "               "<<std::endl;
	for(int i=0;i<M+1;i++){

		for(int j=0;j<N+1;j++){
		int s = ppx[i][j];
			//█ →←↑↓□×★
			switch (s)
			{
			case INWALL: cout << "█";
			 break;
			case EMPTY: cout << "□";
			 break;
			case EMPTY_again: cout << "×";
			 break;
			case LEFT: cout << "←";
			 break;
			case RIGHT: cout << "→";
			 break;
			case UP: cout << "↑";
			 break;
			case DOWN: cout << "↓";
			 break;
			case END: cout << "★";
			 break;
			default:cout << "█"; 
			break; 
			}
			//Sleep(sleep);
		}
		cout << std::endl;
	}
}

bool maze::Inarea(Pos on)
{
	if ((1 <= on.x&& on.x <= M - 1) && (1 <= on.y&& on.y <= N - 1))
	{
		if (visited[on.x][on.y] == 0)
			return true;
	}

	return false;
}

int main()
{
	//创建迷宫
	maze ppx;
	ppx.show();
	system("pause");
	return 0;
}


