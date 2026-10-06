#include<stdio.h>
#include<stdlib.h>
#define MAX 100
//dist的值代表路径！！
//最小生成树，总权值最小而完整（即高度最高）的树，一级一级往下连嘛~就像树~，都说最值临界条件才是我们处理分析矛盾的主矛嘛！实需！客观事实！
//修：不一定是最高，而是必须完整！即：没有连接的了
//那么又是图，图的邻接表来作为算法的传入参数，图的另一种数字额、计算机表示是邻接矩阵，我们这里就用邻接表
typedef struct EdgeNode{
	int adjvex;
	int weight;
	struct EdgeNode*next;
}EdgeNode;

typedef struct VertexNode{
	int data;
	EdgeNode*firstedge;
}VertexNode,AdjList[MAX];

typedef struct{
	int numVertexes,numEdges;
	AdjList adjlist;
}GraphAdjlist;

void Prim(GraphAdjlist G,int start){
	int visited[MAX]={0};
	//int dist[MAX]={999};错误！这里只会有dist[0]=999,只有={0}，可以不对称完全赋值！约科实！
	int dist[MAX];
	int parent[MAX];//生成树嘛~父节点和孩子嘛~所以要一个形象生动的parent数组！
	for(int i=0;i<G.numVertexes;i++){
		dist[i]=999;
	}
	dist[start]=0;
	EdgeNode*p;
	for(int i=0;i<G.numVertexes;i++){//大循环次数为顶点数，高效精准保证能穷举，遍历！总框架保证！
		int u=-1,mindist=999;//被松弛过的，都是从目前已知的最小出发的，那就是值得去访问的，穷举？实核在于高效与稳定！MARX意义！
		for(int j=0;j<G.numVertexes;j++){//里面的小循环每次大循环依旧穷举遍历，确保锁死，嗯~高效确保！所有邻居松弛！,注意变量作用域！这里否则会污染变量的值！小循环的变量用j!不用i!
			if(visited[j]==0&&dist[j]<mindist){
				u=j;
				mindist=dist[j];//这也是一个循环！程序执行顺序！！这个循环要被执行完，穷举！再找目前已知最小！！并非只要被松弛！而是要被松弛&最小！！之前，有误！
				//大于初始值，仅仅是赋一下值！循环还没结束呢！会继续检索、可能更新的！所以mindist也要赋值更新并非没用！这里就是它把Dijkstra和Prim统一起来了！
				//Dijkstra,mindist不是决定！但有它更高效！MARX!!意义！！而最小生成树就是决定了！因为要总的最小！所以每次加入的成员必须是已知最小！就选这条路走了！
				//修：都是决定！反正都代表着连通了，每次都从最短的路径出发！精准高效！算法的定义！实需！！MARX!!意义！必需选当前已知最小！！哦！因为后续的更新有需要判断它是否，已访问！它可能通过其它中转更短但被标记了就无法更新了！
				//这样更高效更优更好MARX意义！！！  额我们也有一定合理性（Dijkstra确实穷举遍历确保了啊），那还是MARX标准、更优吧！但确实是mindist把两个算法统一起来了！那好好豪啊！！
				//每次从已知最小！那当然精准高效！！主要是为了统一吧，那个松弛判断条件里其实还应有个visited[v]==0的~
			}
		}
		if(u==-1) break;
		visited[u]=1;
		p=G.adjlist[u].firstedge;
		while(p){
			int v=p->adjvex;
			int weight=p->weight;
			if(visited[v]==0&&weight<dist[v]){//不加visited 会出问题的！就不是最小生成树了，并非从源点一直连通，因为无向图，没有visited，它的dist会被成员顶点给更新，注意dist是代表路径的！dist变了路径就变了！
				dist[v]=weight;//接上，这里如果没有dist，dist更新之后的值代表的路径就会出现断裂，并非源点为根的"最小生成树"！即是错误！！
				parent[v]=u;//v的父亲是u，因为v是u松弛，加入树的
			}
			p=p->next;//尤其注意循环控制变量的数据变化啊！我们需要循环正确！！
		}
		
	}
	int totalweight=0;
	for(int i=0;i<G.numVertexes;i++){
		if(i!=start){
			printf("edge:%d-%d weight:%d\n",G.adjlist[parent[i]].data,G.adjlist[i].data,dist[i]);//有些边它就不走嘛，左右孩子嘛~~~
			totalweight+=dist[i];
		}
		
	}
	printf("totalweight:%d\n",totalweight);
	
}
int main(){
	GraphAdjlist G;
	EdgeNode*e;
	G.numVertexes=4;
	G.numEdges=4;
	for(int i=0;i<G.numVertexes;i++){
		G.adjlist[i].data=i;//数据域别忘了！key啊啊~~
		G.adjlist[i].firstedge=NULL;
	}
	e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=1;e->weight=4;e->next=G.adjlist[0].firstedge;G.adjlist[0].firstedge=e;
	e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=0;e->weight=4;e->next=G.adjlist[1].firstedge;G.adjlist[1].firstedge=e;
		e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=2;e->weight=1;e->next=G.adjlist[0].firstedge;G.adjlist[0].firstedge=e;
			e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=0;e->weight=1;e->next=G.adjlist[2].firstedge;G.adjlist[2].firstedge=e;
			e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=1;e->weight=2;e->next=G.adjlist[2].firstedge;G.adjlist[2].firstedge=e;
			e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=2;e->weight=2;e->next=G.adjlist[1].firstedge;G.adjlist[1].firstedge=e;
				e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=3;e->weight=1;e->next=G.adjlist[1].firstedge;G.adjlist[1].firstedge=e;
				e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=1;e->weight=1;e->next=G.adjlist[3].firstedge;G.adjlist[3].firstedge=e;
					e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=3;e->weight=5;e->next=G.adjlist[2].firstedge;G.adjlist[2].firstedge=e;
					e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=2;e->weight=5;e->next=G.adjlist[3].firstedge;G.adjlist[3].firstedge=e;
					Prim(G,0);//调用函数！
	
	return 0;
}


