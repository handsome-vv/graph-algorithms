#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef struct EdgeNode{
	int adjvex;
	struct EdgeNode*next;
}EdgeNode;

typedef struct VertexNode{
	int data;
	EdgeNode*firstedge;
}VertexNode,AdjList[MAX];

typedef struct{
	int numEdges,numVertexes;
	AdjList adjlist;
}GraphAdjlist;

void Toposort(GraphAdjlist G){
	EdgeNode*p;
	int count=0;
	int Stack[MAX],top=-1;
	int Indegree[MAX]={0};
//计算入度，逐链，按规律，不重不漏，做好！MARX意义！！
for(int i=0;i<G.numVertexes;i++){
	p=G.adjlist[i].firstedge;//获取'指下'，被指向就是有入度！
	while(p){
		Indegree[p->adjvex]++;
		p=p->next;//因为被顶点指向，所以才能被链成员指向，对于计算入度而言是等价的，在转换中，矛盾的特殊性都对应上了所以等价
	}	
}
for(int i=0;i<G.numVertexes;i++){
	if(Indegree[i]==0){//入度为0入栈，即是依赖为0，定义！！
		Stack[++top]=i;
	}
}
//度就是核心算完了就可以打印结果了
	while(top!=-1){//只有栈里的才能输出，这是核心！所以输出循环要用栈来驱动！！这就是拓扑！这就是入度！这就是任务依赖！的意义！语言只是个符号，被我们赋予意义！而问题在于...MARX意义！！多练！理解对应好！！
		int v=Stack[top--];
		printf("%d ",G.adjlist[v].data);
		count++;
		p=G.adjlist[v].firstedge;//这里没有'搭链子',原本指向的空间被覆盖了也没关系，因为...也没有指向它原本指向的空间
		while(p){
			Indegree[p->adjvex]--;//自然，出栈后所有对它有依赖的入度都减1，依旧规律，实现遍历，从而确保哈哈！！
			if(Indegree[p->adjvex]==0){
				Stack[++top]=p->adjvex;//有消除，检查是否入度为零，当然要检查，入度为0就要入栈！这个算法，豪工具，否则算法就失效！
			}
			p=p->next;//谁发生了输入，消度，谁就是'主角',自然转移！因为这是我们的实需！
		}
	}//一直消到，不能再消，自然能完整输出！
	if(count<G.numVertexes){
		printf("\nThere is a circle!  Failed!\n");//卡在环里，谁的度都不能消为0，无法输出，不能使用拓扑排序
	}
	else{
		printf("\nSuccessfully complited!\n");
	}
}

int main(){
	GraphAdjlist G;
	G.numVertexes=4;
	G.numEdges=4;
	EdgeNode*e;
	for(int i=0;i<G.numVertexes;i++){
		G.adjlist[i].firstedge=NULL;//注意初始化！野指针是不确定不稳定的（引起混乱），不让它安顿指向，就消耗后台资源！影响我们物质生产！！MARX意义！！
	}
	G.adjlist[0].data=0;G.adjlist[1].data=1;G.adjlist[2].data=2;G.adjlist[3].data=3;
	e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=1;e->next=G.adjlist[0].firstedge;G.adjlist[0].firstedge=e;
	e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=2;e->next=G.adjlist[0].firstedge;G.adjlist[0].firstedge=e;
	e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=3;e->next=G.adjlist[1].firstedge;G.adjlist[1].firstedge=e;
	e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=3;e->next=G.adjlist[2].firstedge;G.adjlist[2].firstedge=e;
	Toposort(G);//拓扑排序处理的是有向图哦~
	return 0;
}