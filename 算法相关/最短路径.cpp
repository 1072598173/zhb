#include <iostream>
#include<stdlib.h>
using namespace std;
#define INF 99
#define NUM 7
typedef struct MGraph		/* 邻接表存储结构 */
{
     int edges[NUM][NUM];
     int n,e;
}MGraph;
MGraph *build_mgraph();
void Dijkstra(MGraph *mgraph, int v,int des);
void Dispath(int dis[],int pre[],int visited[], int n, int v,int des);
void Ppath(int path[], int i, int v);
int main(void)
{    MGraph *mgraph;
     cout<<"\n*************************************************************\n";
     cout<<"该图的矩阵表示为:"<<endl;
     mgraph=build_mgraph();
     cout<<"\n*************************************************************\n";
     int origin,dest;
     cout<<"输入原点和目的地:"<<endl;
     cin>>origin>>dest;
     cout<<endl;
     cout<<"dijkstra 算法:"<<endl;
     Dijkstra(mgraph,origin,dest);
     cout<<"\n*************************************************************\n";
     return 0;
}
MGraph *build_mgraph()
{
     int i,j;
     int num_e=0;
     MGraph *mgraph=(MGraph *)malloc(sizeof(MGraph));
     int matrix[NUM][NUM]={
        {0,4,6,6,INF,INF,INF},
        {INF,0,1,INF,7,INF,INF},
        {INF,INF,0,INF,6,4,INF},
        {INF,INF,2,0,INF,5,INF},
        {INF,INF,INF,INF,0,INF,6},
        {INF,INF,INF,INF,1,0,8},
        {INF,INF,INF,INF,INF,INF,0}};
     for(i=0;i<NUM;i++)
     {
	  for(j=0;j<NUM;j++)
	  {
	       mgraph->edges[i][j]=matrix[i][j];
	       if(matrix[i][j]!=0 && matrix[i][j]!=INF)
		    num_e++;
	  }}
     mgraph->n=NUM;
     mgraph->e=num_e;

     cout<<"点="<<mgraph->n<<"边="<<mgraph->e<<endl;
     for(i=0;i<NUM;i++)
     {
	  for(j=0;j<NUM;j++)
	  {
	       if(mgraph->edges[i][j]!=INF)
		    cout<<mgraph->edges[i][j]<<" ";
	       else
		    cout<<"∞ ";
	  }
	  cout<<"\n";
     }

     return mgraph;}

void Dijkstra(MGraph *mgraph, int v,int des)
{
     int i,j;
     int no;
     int min_dis;
     int dis[NUM];
     int visited[NUM]={0};
     int pre[NUM];
     visited[v]=1;
     for(i=0;i<mgraph->n;i++)
     {
	  dis[i]=mgraph->edges[v][i];
	  pre[i]=v;
     }

     for(i=0;i<mgraph->n;i++)
     {
	  min_dis=INT_MAX;
	  for(j=0;j<mgraph->n;j++)
	  {
	       if(!visited[j] && dis[j]<min_dis)
	       {
		    min_dis=dis[j];
		    no=j;
	       }
	  }
	  visited[no]=1;
	  for(j=0;j<mgraph->n;j++)
	  {
	       if(!visited[j] && mgraph->edges[no][j]!=INT_MAX && dis[no]+mgraph->edges[no][j] < dis[j])
	       {
		    dis[j]=dis[no]+mgraph->edges[no][j];
		    pre[j]=no;}}}
     Dispath(dis,pre,visited,mgraph->n,v,des);
}

void Dispath(int dis[],int pre[],int visited[], int n, int v,int des)
{
     int i;
    for(i=des;i<=des;i++)
     {
      if(dis[i]==99)
      {
          cout<<"no path"<<endl;
      }
	  else if(visited[i])
	  {
	      cout<<"从"<<v<<"到"<<i<<"的最短路径长度为:"<<dis[i]<<endl;
	      cout<<"路径为:";
	       cout<<v<<"->";
	       Ppath(pre,des,v);
	       cout<<des<<endl;
	  }
	  else
	      cout<<"no path\n";
     }
}
void Ppath(int pre[], int i, int v)
{
     int k;
     k=pre[i];
     if(k==v)
	  return;
     Ppath(pre,k,v);
     cout<<k<<"->";
}
