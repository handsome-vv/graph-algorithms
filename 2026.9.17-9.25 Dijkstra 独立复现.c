#include<stdio.h>
#include<stdlib.h>
#define MAX 100
//核心思想：两点论与重点论！！哈哈！！
int visited[MAX]={0};

typedef struct EdgeNode{
	int adjvex;
	int weight;
	struct EdgeNode*next;//表意更清晰&整体功能辩证统一吧，总之能更好...MARX意义！！
	
}EdgeNode;

typedef struct VertexNode{
	int data;
	EdgeNode*firstedge;
	
}VertexNode,Adjlist[MAX];

typedef struct{
	int numVertexes,numEdges;
	Adjlist adjlist;
	
}GraphAdjList;

void Dijkstra(GraphAdjList G,int start){
	int dist[MAX];
	for(int i=0;i<G.numVertexes;i++){
		dist[i]=999;
	}
	dist[start]=0;
	for(int i=0;i<G.numVertexes;i++){//大循环，每次确定一个顶点
		int u=-1,mindist=999;//所以你要在大循环内部，每次都要重置,
		for(int j=0;j<G.numVertexes;j++){
			if(visited[j]==0&&dist[j]<mindist){//看这里的判断条件，不是dist之间的互相比较而是要找每个顶点到源点的最短路径哦，所以只需大于初始化的值就好了！
			//注意看因为这步前没有任何赋值操作！都是靠刚开始的源点到源点"天经地义"的最小来逐个确认的，它的直达邻居，那当然大概率是最小的了，所以只需未访问+大于初始值即可！！所以注意visited=1这一步
			//大于初始值即代表它已被邻居松弛，大概率哦！那就是值得尝试的一次中转！反正也会穷举，这就叫效率！更好！MARX意义！！&规律！！补充：也是因为这规律才高效地确保穷举！
			//而注意看后续的循环能确保所有顶点的邻居都被松弛一遍，所有的直达路径和中转路径都会被检索，从而确保算法正确性！
				u=j;
				mindist=dist[j];
			}
			
		}
		if(u==-1) break;//所有顶点，与源点都不可达，关于该源点的单源最短路径算法结束
		visited[u]=1;//所以此时也并非代表你完全定死了，只是标记一下避免重复松弛，浪费！！
		//上一个for循环确定了它是最小的dist（这就是选它的物质根源！！），那就重点从它突破，把一个一个的最小的都确定下来，两点论与重点论！辩证统一！整体效应！MARX意义！！
		//那么客观事实，它就不会因它的邻居中转而离源点更近了，它本身就是最近了，所有路径的权重都是正值，那它就确定下来了！所以接下来松弛它的邻居
		EdgeNode*p=G.adjlist[u].firstedge;
		while(p){
			int v=p->adjvex;
			if(dist[u]+p->weight<dist[v]){//关键更新！！Dijkstra也要visited更严谨，但没有，不影响正确性，因为有向图，dist从前面已知最小逐确定了，中转就不可能最小！所有边权为正值！
				dist[v]=dist[u]+p->weight;//p->别忘了！！不然表意不清！！
			}
			p=p->next;
		}
	}
	//循环结束，已经全部遍历确保算法正确，接下来该打印结果了~~
	printf("The Dijkstra result of the VertexNode %d is:\n",start);
	for(int i=0;i<G.numVertexes;i++){
		printf("From VertexNOde %d to VertexNode %d :%d\n",start,G.adjlist[i].data,dist[i]);
	}
	
}



int main(){
	GraphAdjList G;
	G.numVertexes=4;
	G.numEdges=5;
	EdgeNode*e;
	for(int i=0;i<G.numVertexes;i++){
		G.adjlist[i].firstedge=NULL;
		G.adjlist[i].data=i;
	}
	e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=1;e->weight=4;e->next=G.adjlist[0].firstedge;G.adjlist[0].firstedge=e;
		e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=2;e->weight=1;e->next=G.adjlist[0].firstedge;G.adjlist[0].firstedge=e;
			e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=1;e->weight=2;e->next=G.adjlist[2].firstedge;G.adjlist[2].firstedge=e;
				e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=3;e->weight=1;e->next=G.adjlist[1].firstedge;G.adjlist[1].firstedge=e;
					e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=3;e->weight=5;e->next=G.adjlist[2].firstedge;G.adjlist[2].firstedge=e;//链子所有者来指向
					//有向图，终点插入起点，约科实
					Dijkstra(G,0);
	return 0;
}

