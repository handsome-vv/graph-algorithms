#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100

int visited[MAXSIZE]={0};

typedef struct EdgeNode{//边结点结构体
	int adjvex;
	struct EdgeNode*next;//struct 别忘了！typedef还没完成！！科学设计！！程序执行步骤！！没有这物质基础！什么都不可能！！MARX!就是科学！真理！！意义！！
}EdgeNode;//“中间桥梁”！！！便于我们后续使用高效的循环
//“中间桥梁”！！！使用循环实现高效&保护数据!当我们有实需的时候它是个可以考虑的豪工具！！！
typedef struct VertexNode{//顶点结点结构体
	int data;//顶点才叫数据域更合适一点，上面那个边结点结构体叫对应点的下标。这样各司其职哈哈~
	EdgeNode*firstedge;//发现没，与边结点结构体一模一样，存自己和高效的指针,上面的边结点结构体的本质也是当数据域用的，链表就是自己加访下指针！这就是成链！一个一个两两相连嘛！
}VertexNode,AdjList[MAXSIZE];

typedef struct {
	AdjList adjlist;
	int numEdges,numVertexes;
}GraphAdjList;//这就是链表结构体了，理所当然包含所有的顶点（所以有那个数组），和顶点数、边数！这些都是实需的感性材料，当然要标明整合！

void CreateALGraph(GraphAdjList*G){//创建邻接表的函数，这里再一次类型+名称，其实就是手动开辟了新的内存空间！有别于在同一作用域内的重复定义！哈哈~这就是物质条件支持！！实需&科学设计！！
	int i,j,k;
	EdgeNode*e;//中间桥梁，后续插边用
	printf("please input numVertexes and numEdges\n");
    scanf("%d %d",&G->numVertexes,&G->numEdges);//这里""內采用与终端输入形式对应的科学设计，便于终端输入嘛~除此之外函数=内部还是','“小心”精准处理哈哈~  还有指针也是访问内容哦，而scanf是一个函数哦！新作用域出现，例如还会有屏蔽‘外界’等等哦，动态分配内存！在一次程序执行中唯有地址唯一确定哦！科学设计，辩证统一！MARX意义！！
	//第二步初始化~特别注意指针的初始化，小心“野指针”哦~  好好看你传入的参数，好好分析它去思考~
	//这里开始前别忘了，顶点和边都还是变量，要先确定它们的！
		printf("Please input data of Vertex:\n");
	for(i=0;i<G->numVertexes;i++){//所有顶点都要初始化！&注意是借助指针访问！

	scanf("%d",&G->adjlist[i].data);	//G->adjlist[i]=i;简单设计，顶点的数据就是下标 NO!用scan啊~要简单，你终端可以输入简单！还有别忘了".data"!!
		G->adjlist[i].firstedge=NULL;
	}
	//插入指定边，当然要终端输入呐~循环！不止一条！！
	printf("please input Edge(vi,vj)\n");
	for(k=0;k<G->numEdges;k++){	
	
	scanf("%d %d",&i,&j);
	//头插法
	e=(EdgeNode*)malloc(sizeof(EdgeNode));//malloc申请开辟空间，但返回的是这块空间的无类型指针（首地址），所以要注意转换！线性连续&指针可偏移，所以首地址给指针就能实现完整访问这块空间！因为能访问到所有地址，地址即代表空间！科学设计！
	e->adjvex=i;//桥梁来获取新的成员信息，所以这样我们就是再把i插入“j拥有的链表”中，这里e->adjvex=i会更好，如下！！就是要存下标，深度优先遍历就是借助下标进行数组访问的！已改
	//顶点的 data 恰好等于下标，那没问题。但如果以后 data 和下标不一致，adjvex 就会找不到正确的数组位置。更严谨的做法是存下标 i 和 j，而不是 data。
	e->next=G->adjlist[j].firstedge;//指下直接为源顶点拥有的链表的头
	G->adjlist[j].firstedge=e;//源顶点的指下在直接为它，就实现了插入，而新成员在“头部”（除源顶点），故为头插法！！
	//无向图，双向插入
	e=(EdgeNode*)malloc(sizeof(EdgeNode));//注意“生命周期”内不要重复的声明：类型+变量名  哦！！实质是这种声明会开辟空间（即是有新的地址），如果名字重复，则就像一个变量有两个地址，表意不清，引起混乱，地址是唯一的！毕竟是科学设计的豪工具，C语言那就是个方便我们使用计算机的豪工具！联系和发展，辩证统一！系统！整体效应！！MARX意义！！
		e->adjvex=j;//地址唯一确定不变！！所以这里必须再重新开辟一块空间！否者，例如这里，你就改变了破坏了上面原本的插入！上面的firstedge指向的地址的内容被这里新赋值覆盖了，然后又...混乱~~
		e->next=G->adjlist[i].firstedge;
		G->adjlist[i].firstedge=e;
}
	
	
}

void DFS(GraphAdjList G,int start){//被深度遍历的链表，和开始深度遍历的起点
	EdgeNode*p;//中间桥梁，来获取数据，只是一个访问操作!数据是key！原数据更是key中之key！实需！当然要好好保存！！
	visited[start]=1;//起点是入口，第一个被访问
	printf("%d ",G.adjlist[start].data);//这就是访问！“访问”这个文字符号代表的物质运动！！
	p=G.adjlist[start].firstedge;//获取它的第一个邻居！！
	while(p){//直到p=NULL实现完全访问！当然不能遗漏！我们的设计能确保p=NULL时链表已被完全访问
		if(!visited[p->adjvex]){//你看这里所以要存下标！
			DFS(G,p->adjvex);//第一个邻居优先递归调用访问，这就是深度遍历！我们的头插法设计，不断地一直优先找第一个邻居，就是快速地遍历完所有的链，这就是深度遍历！
			//你回看之前代码链表的打印你就会发现，第一个邻居其实是顶点所拥有链的链头！而每一个邻居其实也是一个顶点，也有自己拥有的链！这样就能很快很深！哈哈！
			
		}
		p=p->next;//当递归结束说明，如第一次递归结束则说明处于链头的都被访问过了，接下来该到“第二梯队”！
	}
	
}

int main(){
	GraphAdjList G;
	CreateALGraph(&G);//直接填入，这里是有设计好的赋值指令的
	printf("The result of DFS is:\n");
	DFS(G,0);//从0顶点开始访问
	//输入边的顺序就是插入顺序了
	return 0;
}




