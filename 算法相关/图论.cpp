
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<queue>
using namespace std;

const int MAXVEX = 100;
typedef char VertexType;
typedef int EdgeType;
//邻接矩阵
typedef struct
{
	int num;
	EdgeType weight;
}ElemType;	//矩阵中元素的类型

typedef struct{
	int edges[MAXVEX][MAXVEX];//邻接矩阵
	int numNodes, numEdges;
	ElemType vex[MAXVEX];//存放顶点信息
}GraphAdjArray;

//邻接表
//边表结点
typedef struct EdgeNode
{
	int adjvex;
	EdgeType weight;
	struct EdgeNode *next;
}EdgeNode;
//顶点表结点
typedef struct VextexNode {
	VertexType data;
	bool visited;//表示该节点是否被访问
	EdgeNode *firstedge;
}VetexNode,AdjList[MAXVEX];
//邻接表
typedef struct
{
	AdjList adjList;
	int numNodes, numEdges;
}GraphAdjList;

//创建邻接列表
//传入 边界点begin 边界点end 权重
void CreateALGraph(GraphAdjList *Gp, int arr[][3],int numNodes, int numEdges)
{
	int i;
	EdgeNode *pe;
	Gp->numNodes = numNodes;
	Gp->numEdges = numEdges;
	//输入顶点信息，将边表置为0
	for (i = 0;i < Gp->numNodes;++i) {
		Gp->adjList[i].data = i;
		Gp->adjList[i].firstedge = NULL;
	}
	//建立边表
	for (i = 0;i < Gp->numEdges;++i) {
		pe = (EdgeNode*)malloc(sizeof(EdgeNode));
		pe->adjvex = arr[i][1];
		pe->weight = arr[i][2];
		pe->next = Gp->adjList[arr[i][0]].firstedge;
		Gp->adjList[arr[i][0]].firstedge = pe;
		//重复上面的操作
		pe = (EdgeNode*)malloc(sizeof(EdgeNode));
		pe->adjvex = arr[i][0];
		pe->weight = arr[i][2];
		pe->next = Gp->adjList[arr[i][1]].firstedge;
		Gp->adjList[arr[i][1]].firstedge = pe;
	}
}

//创建邻接矩阵
void CreateALArray(GraphAdjArray *Ga, int arr[][18], int numNodes, int numEdges)
{
	Ga->numEdges = numEdges;
	Ga->numNodes = numNodes;
	int i, j;
	//直接将邻接矩阵写到edges中，没有用到ElemType vex[MAXVEX]
	for (i = 0;i < Ga->numNodes;++i) {
		for (j = 0;j < Ga->numNodes;++j)
			Ga->edges[i][j] = arr[i][j];
	}
}

//输出邻接表
void DispAdjList(GraphAdjList *Gp) {
	int i;
	EdgeNode *p;
	for (i = 0;i < Gp->numNodes;++i) {
		p = Gp->adjList[i].firstedge;
		cout << i << ": ";
		while (p != NULL) {
			cout << p->adjvex << " ";
			p = p->next;
		}
		cout << endl;
	}
}

//输出邻接矩阵
void DispAdjArray(GraphAdjArray *Ga) {
	int i, j;
	for (i = 0;i < Ga->numNodes;++i) {
		for (j = 0;j < Ga->numNodes;++j) {
			cout << Ga->edges[i][j] << " ";
		}
		cout << endl;
	}
}

//邻接矩阵转化成邻接表
void ArratToList(GraphAdjArray *Ga, GraphAdjList *GatoGp) {
	GatoGp->numEdges = Ga->numEdges;
	GatoGp->numNodes = Ga->numNodes;
	//输入顶点信息，将边表置为0
	int i,j;
	for (i = 0;i < GatoGp->numNodes;++i) {
		GatoGp->adjList[i].data = i;
		GatoGp->adjList[i].firstedge = NULL;
	}
	EdgeNode *pe;
	pe = (EdgeNode*)malloc(sizeof(EdgeNode));
	for (i = 0;i < Ga->numNodes;++i) {
		for (j = 0;j < Ga->numNodes;++j) {
			if (Ga->edges[i][j] != 0) {
				pe = (EdgeNode*)malloc(sizeof(EdgeNode));
				pe->adjvex = j;
				pe->weight = Ga->edges[i][j];
				pe->next = GatoGp->adjList[i].firstedge;
				GatoGp->adjList[i].firstedge = pe;
			}
		}
	}

}
//邻接表转化成邻接矩阵
void ListToArray(GraphAdjList *Gp, GraphAdjArray *GptoGa) {
	EdgeNode *pe;
	GptoGa->numEdges = Gp->numEdges;
	GptoGa->numNodes = Gp->numNodes;
	int i, j;
	//先将邻接矩阵的元素全部置0
	for (i = 0;i < GptoGa->numNodes;++i) {
		for (j = 0;j < GptoGa->numNodes;++j)
			GptoGa->edges[i][j] = 0;
	}
	for (i = 0;i < Gp->numNodes;++i) {
		pe = Gp->adjList[i].firstedge;
		while (pe != NULL) {
			GptoGa->edges[i][pe->adjvex] = pe->weight;
			pe = pe->next;
		}
	}
}
//初始化节点的访问
void initVisted(GraphAdjList *Gp) {
	for (int i = 0;i < Gp->numNodes;++i) {
		Gp->adjList[i].visited = 0;
	}
}

//邻接表的深度搜索遍历,将结果保存到vector中
void DFS(GraphAdjList *Gp,int start,vector<int> *vec) {
	vec->push_back(start);
	cout << start << "　";
	Gp->adjList[start].visited = 1;
	EdgeNode *pe;
	pe = (EdgeNode*)malloc(sizeof(EdgeNode));
	pe = Gp->adjList[start].firstedge;	//pe指向表头
	while (pe != NULL) {				//遍历Gp->adjList[start]的边表，找到未遍历的
		if (!Gp->adjList[pe->adjvex].visited) {
			DFS(Gp, pe->adjvex,vec);
		}
		pe = pe->next;
	}
}
//邻接表的广度搜索
void BFS(GraphAdjList *Gp, int start, vector<int> *vec) {
	queue<int> q;
	q.push(start);
	Gp->adjList[start].visited = 1;
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		vec->push_back(current);
		EdgeNode *pe;
		pe = (EdgeNode*)malloc(sizeof(EdgeNode));
		pe = Gp->adjList[current].firstedge;//pe指向头结点，遍历边表
		while ((pe !=NULL )&& (!Gp->adjList[pe->adjvex].visited)) {
			q.push(pe->adjvex);
			Gp->adjList[pe->adjvex].visited = 1;
			pe = pe->next;
		}
	}
}
int main(){
	GraphAdjList Gp;
	int arr1[][3] = { {1,0,3},
	{2,0,1},
	{3,0,1},
	{2,1,1},
	{4,1,1},
	{9,1,4},
	{3,2,1},
	{4,2,2},
	{5,2,1},
	{5,3,2},
	{6,3,2},
	{7,3,1},
	{5,4,1},
	{9,4,1},
	{6,5,1},
	{9,5,3},
	{10,5,1},
	{12,5,3},
	{7,6,1},
	{8,6,2},
	{12,6,2},
	{13,6,4},
	{14,6,3},
	{8,7,1},
	{14,8,1},
	{15,8,3},
	{10,9,1},
	{11,9,1},
	{11,10,1},
	{12,10,2},
	{16,11,1},
	{13,12,2},
	{16,12,1},
	{14,13,1},
	{15,13,2},
	{16,13,2},
	{17,13,1},
	{15,14,1},
	{17,15,4},
	{17,16,1 }};
	CreateALGraph(&Gp, arr1,18, 40);
	cout << "***********Gp**************" << endl;
	DispAdjList(&Gp);

	//输出邻接表
	GraphAdjArray Ga;
	int arr2[18][18] = { { 0,3,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 3,0,1,0,1,0,0,0,0,4,0,0,0,0,0,0,0,0 },
	{ 1,1,0,1,2,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 1,0,1,0,0,2,2,1,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,2,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,1,2,1,0,1,0,0,3,1,0,3,0,0,0,0,0 },
	{ 0,0,0,2,0,1,0,1,2,0,0,0,2,4,3,0,0,0 },
	{ 0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,2,1,0,0,0,0,0,0,1,3,0,0 },
	{ 0,4,0,0,1,3,0,0,0,0,1,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,0,1,0,1,2,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,0 },
	{ 0,0,0,0,0,3,2,0,0,0,2,0,0,2,0,0,1,0 },
	{ 0,0,0,0,0,0,4,0,0,0,0,0,2,0,1,2,2,1 },
	{ 0,0,0,0,0,0,3,0,1,0,0,0,0,1,0,1,0,0 },
	{ 0,0,0,0,0,0,0,0,3,0,0,0,0,2,1,0,0,4 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,1,2,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,4,1,0 }};
	CreateALArray(&Ga, arr2, 18, 40);
	DispAdjArray(&Ga);
	GraphAdjList GatoGp;
	ArratToList( &Ga, &GatoGp);
	cout << "********邻接数组转化为邻接表的结果***********" << endl;
	DispAdjList(&GatoGp);
	GraphAdjArray GptoGa;
	ListToArray(&GatoGp, &GptoGa);
	cout << "********邻接表转化为邻接矩阵的结果***********" << endl;
	DispAdjArray(&GptoGa);

	//根据Gp学习深度遍历
	vector <int> vec1;
	initVisted(&Gp);
	cout << "输出深度遍历的结果" << endl;
	DFS(&Gp, 0, &vec1);
	cout<<endl;
	//根据Gp学习广度遍历
	cout << "输出广度遍历的结果" << endl;
	vector<int> vec2 ;
	initVisted(&Gp);
	BFS(&Gp, 0, &vec2);
	system("pause");
	return 0;
}
