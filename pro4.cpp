#include <iostream>
#include <cstring>
#include <queue>
#include <stack>
#include <iomanip>
using namespace std;
#define max_vex 25 /* 最大顶点数*/

struct ghedge // 邻接多重表边结构体 
{
	int mark;
	int ve1;
	int ve2;
	int weight;
	ghedge* path1;
	ghedge* path2;
	ghedge()
	{
		mark = 0;
		path1 = NULL;
		path2 = NULL;
	}
};

struct vex // 邻接多重表的结点结构体 
{
	int data;
	ghedge* first;
	vex()
	{
		first = NULL;
	}
};

struct graph //图的结构体 
{
	vex adj[max_vex];
	int vexnum;
	int edgenum;
};

struct Lvex //邻接表边的结构体 
{
	int data;
	int weight;
	Lvex* next;
	Lvex()
	{
		next = NULL;
	}
};

struct Vexnode //邻接表结点的结构体 
{
	int data;
	Lvex* adj;
	Vexnode()
	{
		adj = NULL;
	}	
};


void path(int vex1 , int vex2 , graph* g, int weight)//vex1和vex2 间建立边的函数 
{
	ghedge *tmp , *p , *q;
	tmp = new ghedge;
	tmp->ve1 = vex1;
	tmp->ve2 = vex2;
	tmp->weight = weight;
	if(g->adj[vex1].first == NULL)
	{
		g->adj[vex1].first = tmp;
	}
	else
	{
		p = g->adj[vex1].first;
		if(g->adj[vex1].first->ve1 == vex1)
		{
			q = p->path1;
		}
		else if(g->adj[vex1].first->ve2 == vex1)
		{
			q = p->path2;
		}
		while(q)
		{
			if(q->ve1 == vex1)
			{
				p = q;
				q = q->path1;
			}
			else if(q->ve2 == vex1)
			{
				p = q;
				q = p->path2;
			}
		}
		if(p->ve1 == vex1) p->path1 = tmp;
		else if(p->ve2 == vex1) p->path2 = tmp;
	}
	if(g->adj[vex2].first == NULL) g->adj[vex2].first = tmp;
	else
	{
		p = g->adj[vex2].first;
		q = p->path2;
		while(q)
		{
			p = q;
			q = p->path2;
		}
		p->path2 = tmp;
	} 
} 

graph* creategraph() //创建图的函数,默认图为testcase的图，起点为北京 
{
	graph *g = new graph;
	ghedge *p; 
	g->vexnum = 25;
	g->edgenum = 30;
	for(int i = 0 ; i < max_vex ; i++)
	{
		g->adj[i].data = i;
		if(i == 0)
		{
			path(0,1,g,668);
			path(0,6,g,695);
			path(0,8,g,137);
		}
		else if(i == 1)
		{
			path(1,2,g,1145);
		}
		else if(i == 2)
		{
			path(2,3,g,216);
			path(2,4,g,1892);
			path(2,5,g,676);
		}
		else if(i == 5)
		{
			path(5,6,g,511);
			path(5,15,g,842);
		}
		else if(i == 6)
		{
			path(6,7,g,349);
			path(6,14,g,534);
		}
		else if(i == 7)
		{
			path(7,8,g,674);
			path(7,13,g,651);
		}
		else if(i == 8)
		{
			path(8,9,g,704);
		}
		else if(i == 9)
		{
			path(9,10,g,397);
			path(9,11,g,305);
		}
		else if(i == 11)
		{
			path(11,12,g,242);
		}
		else if(i == 13)
		{
			path(13,19,g,825);
		}
		else if(i == 14)
		{
			path(14,18,g,409);
		}
		else if(i == 15)
		{
			path(15,16,g,1100);
			path(15,17,g,967);
		}
		else if(i == 16)
		{
			path(16,17,g,639);
		}
		else if(i == 17)
		{
			path(17,18,g,902);
			path(17,21,g,607);
		}
		else if(i == 18)
		{
			path(18,19,g,367);
			path(18,21,g,672);
			path(18,23,g,675);
		}
		else if(i == 19)
		{
			path(19,20,g,622);
		}
		else if(i == 21)
		{
			path(21,22,g,255);
		}
		else if(i == 23)
		{
			path(23,24,g,140);
		}
	}
	return g;
}

void BFS(graph *g , int v , string *place) //广度优先遍历 
{
	int n = g->vexnum;
	int *visit = new int[n];
	for ( int i = 0; i < n; i++ )
		visit[i] = 0;
	visit[v] = 1;
	cout << setw(8) << place[g->adj[v].data] << endl;
	queue<int> q;
	q.push(v);
	int pos;
	while(!q.empty()) //队列出列一个节点，输出周围节点并且把周围节点压入队列 
	{
		pos = q.front();
		q.pop();
		ghedge* p;
		p = g->adj[pos].first;
		while(p)
		{
			if(p->ve1 == pos)
			{
				if(!visit[p->ve2])
				{
					cout << setw(8)<< place[p->ve2]   << "  路径为： ";
					cout << place[p->ve1] << "-->" << place[p->ve2] << endl;
					visit[p->ve2] = 1;
					q.push(p->ve2);
				}
				p = p->path1;
			}
			else if(p->ve2 == pos)
			{
				if(!visit[p->ve1])
				{
					cout <<  setw(8)  << place[p->ve1]  << "  路径为： ";
					cout << place[p->ve1] << "-->" << place[p->ve2] << endl;
					visit[p->ve1] = 1;
					q.push(p->ve1);
				}
				p = p->path2;
			}	
		}
	}
	cout << "END";
}

void DFS(graph *g , int v , string *place) //广度优先搜索 
{
	int n = g->vexnum;
	int *visit = new int [n];
	for ( int i = 0; i < n; i++ )
		visit[i] = 0;
	visit[v] = 1;
	cout << setw(8) << place[g->adj[v].data] << endl;
	stack<int> s;
	s.push(v);
	int pos;
	while(!s.empty()) //读取栈顶头节点 ，输出下一个周围没有遍历的结点并且压入栈，如果周围节点都被访问过，则删除顶头节点 
	{
		pos = s.top();
		ghedge* p;
		p = g->adj[pos].first;
		while(p)
		{
			if(p->ve1 == pos)
			{
				if(!visit[p->ve2])
				{
					cout << setw(8)<< place[p->ve2]   << "  路径为： ";
					cout << place[p->ve1] << "-->" << place[p->ve2] << endl;
					visit[p->ve2] = 1;
					s.push(p->ve2);
					pos = s.top();
					p = g->adj[pos].first;
				}
				else
				{
					p = p->path1;			
				}
			}
			else if(p->ve2 == pos)
			{
				if(!visit[p->ve1])
				{
					cout <<  setw(8)  << place[p->ve1]  << "  路径为： ";
					cout << place[p->ve1] << "-->" << place[p->ve2] << endl;
					visit[p->ve1] = 1;
					s.push(p->ve1);
					pos = s.top();
					p = g->adj[pos].first;
				}
				else
				{
					p = p->path2;
				}
			}	
		}
		s.pop();
	}
	cout << "END";
}

Vexnode* DSPT( graph* g , int v , string* place) //邻接表存储的深度遍历生成树 
{
	int n = g->vexnum;
	int *visit = new int [n];
	Vexnode *st = new Vexnode [25];
	Lvex *adj , *box;
	for ( int i = 0; i < n; i++ )
		visit[i] = 0;
	visit[v] = 1;
	stack<int> s;
	s.push(v);
	int pos;
	while(!s.empty())
	{
		pos = s.top();
		ghedge* p;
		p = g->adj[pos].first;
		while(p)
		{
			if(p->ve1 == pos)
			{
				if(!visit[p->ve2])
				{
					adj = new Lvex;
					adj->data = p->ve2;
					adj->weight = p->weight;
					
					if(st[p->ve1].adj == NULL) st[p->ve1].adj = adj;
					else
					{
						box = st[p->ve1].adj;
						while(box->next)
						{
							box = box->next;
						}
						box->next = adj;
					}
					
					visit[p->ve2] = 1;
					s.push(p->ve2);
					pos = s.top();
					p = g->adj[pos].first;
				}
				else
				{
					p = p->path1;			
				}
			}
			else if(p->ve2 == pos)
			{
				if(!visit[p->ve1])
				{
					adj = new Lvex;
					adj->data = p->ve1;
					adj->weight = p->weight;
					
					if(st[p->ve2].adj == NULL) st[p->ve2].adj = adj;
					else
					{
						box = st[p->ve2].adj;
						while(box->next)
						{
							box = box->next;
						}
						box->next = adj;
					}
					visit[p->ve1] = 1;
					s.push(p->ve1);
					pos = s.top();
					p = g->adj[pos].first;
				}
				else
				{
					p = p->path2;
				}
			}	
		}
		s.pop();
	}
	return st;	
}

Vexnode* BSPT( graph* g , int v , string* place) //广度优先遍历的生成树 
{
	int n = g->vexnum;
	int *visit = new int[n];
	for ( int i = 0; i < n; i++ )
		visit[i] = 0;
	visit[v] = 1;
	Vexnode *st = new Vexnode [25];
	Lvex *adj , *box;
	queue<int> q;
	q.push(v);
	int pos;
	while(!q.empty())
	{
		pos = q.front();
		q.pop();
		ghedge* p;
		p = g->adj[pos].first;
		while(p)
		{
			if(p->ve1 == pos)
			{
				if(!visit[p->ve2])
				{
					adj = new Lvex;
					adj->data = p->ve2;
					adj->weight = p->weight;
					
					if(st[p->ve1].adj == NULL) st[p->ve1].adj = adj;
					else
					{
						box = st[p->ve1].adj;
						while(box->next)
						{
							box = box->next;
						}
						box->next = adj;
					}
					
					visit[p->ve2] = 1;
					q.push(p->ve2);
				}
				p = p->path1;
			}
			else if(p->ve2 == pos)
			{
				if(!visit[p->ve1])
				{
					adj = new Lvex;
					adj->data = p->ve1;
					adj->weight = p->weight;
					
					if(st[p->ve2].adj == NULL) st[p->ve2].adj = adj;
					else
					{
						box = st[p->ve2].adj;
						while(box->next)
						{
							box = box->next;
						}
						box->next = adj;
					}
					visit[p->ve1] = 1;
					q.push(p->ve1);
				}
				p = p->path2;
			}	
		}
	}
	return st;
}

void Preorder(Vexnode *st , int v , int *visit,string * place) //对生成树的前序遍历 
{
	visit[v] = 1;
	Lvex *p;
	p = st[v].adj;
	cout << place[v] <<"->"; 
	if(p == NULL) return;
	else
	{
		while(p)
		{
			if( visit[p->data] == 1)
			{
				p = p->next;
			}
			else
			{
				Preorder(st,p->data,visit,place);
			}
		}
	}
}

void Preorder_edge(Vexnode *st , int v , int *visit,string * place) //对生成树的前序遍历 ,边的输出 
{
	visit[v] = 1;
	Lvex *p;
	p = st[v].adj; 
	if(p == NULL) return;
	else
	{
		while(p)
		{
			if( visit[p->data] == 1)
			{
				p = p->next;
			}
			else
			{
				cout << "  路径为： " << setfill(' ') << setw(8) << place[v] << setfill('-') << setw(10) << ">" << place[p->data] << "  " << p->weight << endl;
				Preorder_edge(st,p->data,visit,place);
			}
		}
	}
}

void Inorder(Vexnode *st , int v , int *visit , string *place)//对生成树的中序遍历 
{
	Lvex *p;
	int count = 0;
	if(st[v].adj == NULL)
	{
		cout << place[v] << "->";
		visit[v] = 1;
		return; 
	}
	else
	{
		p = st[v].adj;
		while(p)
		{
			if(count == 1) 
			{
				cout << place[v] << "->";
				visit[v] = 1;
			}
			if(visit[p->data] == 1)
			{
				p = p->next;
			}
			else
			{
				Inorder(st,p->data,visit,place);
			}
			count++;
		}
	}
}

void Inorder_edge(Vexnode *st , int v , int *visit , string *place)//对生成树的中序遍历 ，边的输出 
{
	Lvex *p;
	int count = 0;
	if(st[v].adj == NULL)
	{
		visit[v] = 1;
		return; 
	}
	else
	{
		p = st[v].adj;
		while(p)
		{
			if(count == 1) 
			{
				visit[v] = 1;
			}
			if(visit[p->data] == 1)
			{
				p = p->next;
			}
			else
			{
				Inorder_edge(st,p->data,visit,place);
				cout << "  路径为： " << setfill(' ') << setw(8) << place[v] << setfill('-') << setw(10) << ">" << place[p->data] << "  " << p->weight << endl;	
			}
			count++;
		}
	}
}

void Postorder(Vexnode *st , int v , int *visit , string *place) //对生成树的后序遍历 
{
	Lvex *p;
	if(st[v].adj == NULL)
	{
		cout << place[v] << "->";
		visit[v] = 1;
		return; 
	}
	else
	{
		p = st[v].adj;
		while(p)
		{
			if(visit[p->data] == 1)
			{
				p = p->next;
			}
			else
			{
				Postorder(st,p->data,visit,place);
			}
		}
		cout << place[v] << "->";
		visit[v] = 1;
	}
}

void Postorder_edge(Vexnode *st , int v , int *visit , string *place)//对生成树的后序遍历 ，边的输出 
{
	Lvex *p;
	if(st[v].adj == NULL)
	{
		visit[v] = 1;
		return; 
	}
	else
	{
		p = st[v].adj;
		while(p)
		{
			if(visit[p->data] == 1)
			{
				p = p->next;
			}
			else
			{
				Postorder_edge(st,p->data,visit,place);
				if(!p->next)
				{
					cout << "  路径为： " << setfill(' ') << setw(8) << place[v] << setfill('-') << setw(10) << ">" << place[p->data] << "  " << p->weight << endl;
				}
				//else cout << "    地点： " << setfill(' ') << setw(8) << place[p->data] << endl;
			}
		}
		visit[v] = 1;
	}
}

struct tnode//兄弟孩子树的节点结构 
{
	int data;
	tnode* child;
	tnode* brother; 
	tnode()
	{
		child = NULL;
		brother = NULL;
	}
};

void buildtree(Vexnode*st , int v , tnode* root)//邻接表存储的树转为兄弟孩子树 
{
	tnode *p ,*tmp;
	Lvex* q;
	q = st[v].adj;
	if(q == NULL) return;
	tmp = new tnode;
	tmp->data = q->data;
	root->child = tmp;
	p = tmp;
	buildtree(st,p->data,p);
	q = q->next;
	while(q)
	{
		tmp = new tnode;
		tmp->data = q->data;
		p->brother = tmp;
		buildtree(st,tmp->data,tmp);
		p = tmp; 
		q = q->next; 
	}		
}

void printtree(tnode* root , string* place) //树的打印 
{
	int i ;
	static int deep = 0 ;
	if(root == NULL)
	{
		cout << "| | | | | | | | | | |"<< endl;
		return;
	}
	for(i = 0 ; i < deep ; i++)
	{
		cout << "| ";
	}
	cout << "depth[" << deep  << "] " << place[root->data] << endl;
	++deep;
	printtree(root->child,place);
	--deep;
	printtree(root->brother,place);
} 

string *name() //地点的函数 
{
	string *p;
	p = new string [26];
	p[0] = "北京"; p[1] = "呼和浩特"; p[2] = "兰州";
	p[3] = "西宁"; p[4] = "乌鲁木齐"; p[5] = "西安";
	p[6] = "郑州"; p[7] = "徐州"; p[8] = "天津";
	p[9] = "沈阳"; p[10] = "大连"; p[11] = "长春";
	p[12] = "哈尔滨"; p[13] = "上海"; p[14] = "武汉"; 
	p[15] = "成都"; p[16] = "昆明"; p[17] = "贵阳";
	p[18] = "株洲"; p[19] = "南昌"; p[20] = "福州";
	p[21] = "柳州"; p[22] = "南宁"; p[23] = "广州";
	p[24] = "深圳"; 
	return p;
}

void reset(int *visit)
{
	for(int i = 0 ; i < 25 ; i++)
		visit[i] = 0;
}

int main()
{
	string *place;
	place = name();
	
	graph *g;
	ghedge *p;
	g = creategraph();
	
	Vexnode *dst , *bst;
	dst = DSPT(g,0,place);
	bst = BSPT(g,0,place);
	int *visit = new int [25];
	int n; 
	string s = "";
	cout <<  "               -------------------------------------" << endl;
	cout <<  "               ---------  中国城市图遍历  ----------" << endl;
	cout <<  "               -------------------------------------" << endl;
	cout << "-----------------------------------------------------"<< endl;
	cout << "--- 1、 输入 1  输出深度遍历图的地点序列            -"<< endl;
	cout << "--- 2、 输入 2  输出广度遍历图的地点序列            -"<< endl;
	cout << "-----------------------------------------------------"<< endl;
	cout << "--- 3、 输入 3  输出深度优先生成树的前序遍历地点序列-"<< endl;
	cout << "--- 4、 输入 4  输出深度优先生成树的中序遍历地点序列-"<< endl;
	cout << "--- 5、 输入 4  输出深度优先生成树的后序遍历地点序列-"<< endl;
	cout << "-----------------------------------------------------"<< endl;
	cout << "--- 6、 输入 6  输出广度优先生成树的前序遍历地点序列-"<< endl;
	cout << "--- 7、 输入 7  输出广度优先生成树的中序遍历地点序列-"<< endl;
	cout << "--- 8、 输入 8  输出广度优先生成树的后序遍历地点序列-"<< endl;
	cout << "-----------------------------------------------------"<< endl;
	cout << "--- 9、 输入 9  输出深度优先生成树的前序遍历路径序列-"<< endl;
	cout << "--- 10、输入 10 输出深度优先生成树的中序遍历路径序列-"<< endl;
	cout << "--- 11、输入 11 输出深度优先生成树的后序遍历路径序列-"<< endl;
	cout << "-----------------------------------------------------"<< endl;
	cout << "--- 12、输入 12 输出广度优先生成树的前序遍历路径序列-"<< endl;
	cout << "--- 13、输入 13 输出广度优先生成树的中序遍历路径序列-"<< endl;
	cout << "--- 14、输入 14 输出广度优先生成树的后序遍历路径序列-"<< endl;
	cout << "-----------------------------------------------------"<< endl;
	cout << "--- 15、输入 15 打印深度优先生成树                  -"<< endl;
	cout << "--- 16、输入 16 打印广度优先生成树                  -"<< endl;
	cout << "-----------------------------------------------------"<< endl;
	cout << "--- 0、输入 0 退出-----------------------------------"<< endl;
	cout << "-----------------------------------------------------"<< endl;
	cout << "      请输入要使用的功能：" ; 
	while(cin >> n) 
	{
		if(n == 1)
		{
			cout << "深度遍历图的地点序列为：" << endl;
			DFS(g,0,place);
			cout << endl;
		}
		else if(n == 2)
		{
			cout << "广度遍历图的地点序列为：" << endl;
			BFS(g,0,place);
			cout << endl;
		}
		else if(n == 3)
		{
			cout << "深度优先生成树的前序遍历地点序列为：" << endl;
			reset(visit);
			Preorder(dst,0,visit,place);
			cout << "END";
			cout << endl;
		}
		else if(n == 4)
		{
			cout << "深度优先生成树的中序遍历地点序列为：" << endl;
			reset(visit);
			Inorder(dst,0,visit,place);
			cout << "END";
			cout << endl;
		}
		else if(n == 5)
		{
			cout << "深度优先生成树的后序遍历地点序列为：" << endl;
			reset(visit);
			Postorder(dst,0,visit,place);
			cout << "END";
			cout << endl;
		}
		else if(n == 6)
		{
			cout << "广度优先生成树的前序遍历地点序列为：" << endl;
			reset(visit);
			Preorder(bst,0,visit,place);
			cout << "END";
			cout << endl;
		}
		else if(n == 7)
		{
			cout << "广度优先生成树的中序遍历地点序列为：" << endl;
			reset(visit);
			Inorder(bst,0,visit,place);
			cout << "END";
			cout << endl;
		}
		else if(n == 8)
		{
			cout << "广度优先生成树的后序遍历地点序列为：" << endl;
			reset(visit);
			Postorder(bst,0,visit,place);
			cout << "END";
			cout << endl;
		}
		else if(n == 9)
		{
			cout << "深度优先生成树的先序遍历路径序列为： " << endl;
			reset(visit);
			Preorder_edge(dst,0,visit,place);
			cout << endl;
		}
		else if(n == 10)
		{
			cout << "深度优先生成树的中序遍历路径序列为： " << endl;
			reset(visit);
			Inorder_edge(dst,0,visit,place);
			cout << endl;	
		}
		else if(n == 11)
		{
			cout << "深度优先生成树的后序遍历路径序列为： " << endl;
			reset(visit);
			Postorder_edge(dst,0,visit,place);
			cout << endl;	
		}
		else if(n == 12)
		{
			cout << "广度优先生成树的先序遍历路径序列为： " << endl;
			reset(visit);
			Preorder_edge(bst,0,visit,place);
			cout << endl;
		}
		else if(n == 13)
		{
			cout << "广度优先生成树的中序遍历路径序列为： " << endl;
			reset(visit);
			Inorder_edge(bst,0,visit,place);
			cout << endl;	
		}
		else if(n == 14)
		{
			cout << "广度优先生成树的后序遍历路径序列为： " << endl;
			reset(visit);
			Postorder_edge(bst,0,visit,place);
			cout << endl;	
		}
		else if(n == 15)
		{
			tnode* root = new tnode;
			root->data = 0;
			root->brother = NULL;
			root->child = NULL;
			buildtree(dst , 0 , root);
			cout << "  深度优先生成树为： " << endl;
			printtree( root ,place);
		} 
		else if(n == 16)
		{
			tnode* root = new tnode;
			root->data = 0;
			root->brother = NULL;
			root->child = NULL;
			buildtree(bst , 0 , root);
			cout << "  广度优先生成树为： " << endl;
			printtree( root ,place);
		} 
		else if( n == 0) break;
		else
		{
			cout << "-----------输入有误 ， 请重新输入 ！！！！！！！-------" << endl;
		}
		cout << "-----------------------------------------------------"<< endl;
		cout << "--- 1、 输入 1  输出深度遍历图的地点序列            -"<< endl;
		cout << "--- 2、 输入 2  输出广度遍历图的地点序列            -"<< endl;
		cout << "-----------------------------------------------------"<< endl;
		cout << "--- 3、 输入 3  输出深度优先生成树的前序遍历地点序列-"<< endl;
		cout << "--- 4、 输入 4  输出深度优先生成树的中序遍历地点序列-"<< endl;
		cout << "--- 5、 输入 4  输出深度优先生成树的后序遍历地点序列-"<< endl;
		cout << "-----------------------------------------------------"<< endl;
		cout << "--- 6、 输入 6  输出广度优先生成树的前序遍历地点序列-"<< endl;
		cout << "--- 7、 输入 7  输出广度优先生成树的中序遍历地点序列-"<< endl;
		cout << "--- 8、 输入 8  输出广度优先生成树的后序遍历地点序列-"<< endl;
		cout << "-----------------------------------------------------"<< endl;
		cout << "--- 9、 输入 9  输出深度优先生成树的前序遍历路径序列-"<< endl;
		cout << "--- 10、输入 10 输出深度优先生成树的中序遍历路径序列-"<< endl;
		cout << "--- 11、输入 11 输出深度优先生成树的后序遍历路径序列-"<< endl;
		cout << "-----------------------------------------------------"<< endl;
		cout << "--- 12、输入 12 输出广度优先生成树的前序遍历路径序列-"<< endl;
		cout << "--- 13、输入 13 输出广度优先生成树的中序遍历路径序列-"<< endl;
		cout << "--- 14、输入 14 输出广度优先生成树的后序遍历路径序列-"<< endl;
		cout << "-----------------------------------------------------"<< endl;
		cout << "--- 15、输入 15 打印深度优先生成树                  -"<< endl;
		cout << "--- 16、输入 16 打印广度优先生成树                  -"<< endl;
		cout << "-----------------------------------------------------"<< endl;
		cout << "--- 0、输入 0 退出-----------------------------------"<< endl;
		cout << "-----------------------------------------------------"<< endl;
		cout << endl << "              请输入要使用的功能：      " ; 
	}
//	int i = 16;
//	p = g->adj[i].first;
//	while(p)
//	{
//		if(p->ve1 == i)
//		{
//			cout << p->ve1 <<" "<< p->ve2 << " " << p->weight<< endl;
//			p = p->path1;
//		}
//		else if(p->ve2 == i)
//		{
//			cout << p->ve1 <<" "<< p->ve2  <<" " << p->weight<< endl;
//			p = p->path2;
//		}
//	}

	
	return 0;
} 
