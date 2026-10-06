#include<stdio.h>
#include<stdlib.h>
#define MAX 100
//多源最短路径！图论算法！它比较特殊！同样都是要传入图参数，它不要邻接表形式它要邻接矩阵的形式作为参数传入
/*
    0
   / \
 (4) (2)
 /     \
1       2
 \     /
 (3) (1)
   \ /
    3

你创建的图的邻接表是：
顶点 0：2-> 1-> NULL
顶点 1：3-> 0-> NULL
顶点 2：3-> 0-> NULL
顶点 3：2-> 1-> NULL
*/
void Floyd(){
	int Graph[4][4]={
	{0,4,2,999},
	{4,0,999,3},
	{2,999,0,1},
	{999,3,1,0},
};//一行一行地来计算机里的约科实！！所以还有有向图里的那个行下标代表起点、行高级于列...
  int dist[MAX][MAX];
  for(int i=0;i<4;i++){
  	for(int j=0;j<4;j++){
  		dist[i][j]=Graph[i][j];
	  }
  }
  for(int k=0;k<4;k++){
  	for(int i=0;i<4;i++){
  		for(int j=0;j<4;j++){
  			if(dist[i][k]+dist[k][j]<dist[i][j]){
  				dist[i][j]=dist[i][k]+dist[k][j];
			  }
		  }
	  }
  }
  for(int i=0;i<4;i++){
  	for(int j=0;j<4;j++){
  		printf("%d ",dist[i][j]);
	  }
	  printf("\n");
  }
}
//多源最短路径就是所有两个点对的最短距离，注意程序执行步骤和顺序！！
int main(){
	Floyd();
	return 0;
}

