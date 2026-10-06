#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define MAXVEX 100
//哦！！这是还没开工，开工前的分析！！！这个算法的结果告诉我们在真正的实际工程中要重点抓好哪几个任务！！哈哈！！MARX！！两点论和重点论！！客观事实！！！哈哈！！效率！！哈哈！！问题在于改造世界！！！意义！！！！
//哈哈！！MARX！！问题导向！！！我们的实需！！！意义！！！！！！！！！！啊哈哈！！MARX！！！！！！
typedef struct EdgeNode {//“权重”是属于“边”，属于“路径”&......的
    int adjvex;
    int weight;//所有涉及最短、最优、关键...什么的，出现差异的实质就是有“权值”！这就是物质根源！划分的标准，这就是差异本身，它就是这种物质存在形式！
    //“权值”在计算机里是一个广大的概念！！，这里具化为：工期！！够用豪用！约科实！更具体地说，是一个前置到它的后置（前置->后置）进行好相应物质准备的时间@
    struct EdgeNode*next;
}EdgeNode;

typedef struct VertexNode{//顶点结点结构体
    int data;
    EdgeNode*firstedge;//注意权值属于边，顶点结构体里是没有权值成员的，所以指下指针来访问获取，注意这关系!指下指针访问获取的权值属于这两点之间的边
}VertexNode,AdjList[MAXVEX];

typedef struct{
    AdjList adjlist;
    int numEdges,numVertexes;
}GraphAdjList;


void TopologicalSort(GraphAdjList G){
    int indegree[MAXVEX]={0};
    int stack[MAXVEX],top=-1;
    int count=0;
    int stack2[MAXVEX],top2=-1;//存拓扑排序序列，供逆序计算用
    int etv[MAXVEX]={0};//最早发生时间：每个任务最早什么时候能开始
    int ltv[MAXVEX];//最晚发生时间：每个任务最晚必须什么时候开始，否者会延误整个工期，
    //啊~你看这就是处理一类特定工程问题的算法！！哈哈！！因为拓扑算法，所以表明任务之间有“依赖”关系，所以便会有上面的延误我们预期的整个工期的情况！哈哈！！客观事实！！我们有实需！！MARX！！意义！！！
    
    for(int i=0;i<G.numVertexes;i++){
        EdgeNode*p=G.adjlist[i].firstedge;
        while(p){
            indegree[p->adjvex]++;//有被指向，即有前置，即有入度，这里是把现实问题，抽象转化为了...等价的整体代换！！一一对应是核心！！一一对应啊！！很重要的思想&客观事实 所以函数这个工具这么强大而深邃！！通俗地说，教育课本里的占比那么大！客观事实！豪用工具！！！
            p=p->next;       
        }
    }
    for(int i=0;i<G.numVertexes;i++){
        if(indegree[i]==0){
            stack[++top]=i;
        }
    }
    printf("拓扑排序的结果：");
    while(top!=-1){
        int v=stack[top--];
        stack2[++top2]=v;//把弹出的顶点v保存起来，供后面的逆序计算使用
        printf("%d ",G.adjlist[v].data);
        count++;
        EdgeNode*p=G.adjlist[v].firstedge;
        while(p){
            int w=p->adjvex;
            if(etv[v]+p->weight>etv[w]){//前置的最早时间+权重>相应后置的最早时间，那后置的最早时间就是前置+权重嘛很合情合理！！可能会有不同路径吧（&受开始的初始化影响！），这里反正又是穷举！！遍历！！
                etv[w]=etv[v]+p->weight;//正向计算最早时间，取最大值,w是v的指下，w依赖于v，所以w必然在v之后开始，所以w的最早时间就为v的最早时间 + v->w 的权重（权重在这里具化为完成v后提供的物质基础到能实现建立能开始做w的物质基础所需的时间吧，这当然是客观存在的！MARX!意义！！！）
                //所以这里拓扑排序的结果的实际价值就体现出来了，一个顶点，只有等它的前置顶点全部弹出，它才能弹出，即可以推广且实践证明（推广并非严格的逻辑推理，所以需要实践证明），看下面一条 拓扑排序的结果 =>所有任务都完成了
                //这是关键路径的第一个核心思想： 一个任务必须等它所有前置任务中“最晚完成”的那个完成后才能开始，所以取最大值，“必须等它所有”很合情合理啊！这就是定义啊！所以取最大值！就是最值才更有实需价值！
            }
            indegree[w]--;
            if(indegree[w]==0){
                stack[++top]=w;
            }
            p=p->next;
        }
    }
    if(count<G.numVertexes){
        printf("\n图中有环，无法完成拓扑排序！\n");
        return ;//拓扑排序都无法完成，那它就不属于最短路径算法解决的问题，不满条件啊，直接结束
    }
    else{
        printf("\n拓扑排序完成！\n");
    } 
    //初始化最晚时间：全部设为最后一个顶点的最早时间（整个工程的最短工期）约科实，无伤大雅，豪用！！最后置的最晚时间就是它的最早时间嗯哼，，，~~ 已经确定的最短（优）工期，我们的期望
    for(int i=0;i<G.numVertexes;i++){
        ltv[i]=etv[stack2[top2]];//这里的时间代表一个时间点，嘿嘿~  注意这里的栈的名字叫stack2 !! 这样你才能取到我们实需的内容！！
    }   
    //逆序计算最晚时间，从后往前，取最小值
    while(top2!=-1){//先弹出的先入栈了，所以这里是逆序，前置都先入栈了！
        int v=stack2[top2--];
        EdgeNode*p=G.adjlist[v].firstedge;//第一次无效循环，因为“最后置”在栈顶，它没有指下
        while(p){
            int w=p->adjvex;//最后一个入栈的，它没有指下啊，那第一次是无效循环~~~嗯~~~
            if(ltv[w]-p->weight<ltv[v]){//如果后置的最晚时间-权重<（早于）相应前置的最晚时间，那这个前置的最晚时间我们就取最早的，抛开最值，这本也就是计算其开始时间的合情合理...同上..不同路径...
                ltv[v]=ltv[w]-p->weight;//逆向计算最晚时间，取最小值，那是因为是有不同路径的，这里又一次穷举了嗯哼~~ 算法能解决的问题计算机都能解决！最早里找最晚！最晚里找最早！哈哈！！
                //计算机就是强大的计算机器！！就是转化为各种运算问题，这就是实质与核心！！“桥梁”！！！
            }
            p=p->next;
        }
    }
    //判断关键路径：最早时间=最晚时间，说明该任务无缓冲，不可延期，很合情合理的客观事实！！呢~~ 为了不延误整个工期！！
    printf("\n关键路径：\n");
    for(int v=0;v<G.numVertexes;v++){
        EdgeNode*p=G.adjlist[v].firstedge;
        while(p){
            int w=p->adjvex;
            if(etv[v]==ltv[v]&&etv[w]==ltv[w]&&etv[v]+p->weight==etv[w]){//不可缓冲的前置&&不可缓冲的后置&&明确两者为前后置关系（有边），，，即为关键路径，按格式打印！哈哈！！
            	printf(" %d -> %d(权值：%d)\n",G.adjlist[v].data,G.adjlist[w].data,p->weight);//通过前置的指下指针获得相应权值，注意有向！前面始终是v，所以不用担心，打印的前置是正确的哈哈！！而前边那计算入度，即使“前置”变动但对于计算入度，而言是等价的！！哈哈！！因为物质根源一一对应，条件支撑！！
            	//条件本身也是一种物质，再一次物质根源，特定的物质支撑这特定的物质聚集形式，支撑着特定的物质的特定运动！！MARX! hhh~ 客观事实！！客观现象，感性材料呢~~哈哈~~
			}
			p=p->next;
        }
        
    }
      
}
/*
拓扑排序的结果：0 1 2 3
拓扑排序完成！

关键路径：
 0 -> 2(权值：3)
 0 -> 1(权值：5)
 1 -> 3(权值：2)
 2 -> 3(权值：4)
四条路径首尾相接合成两条
0->2->3(权值：7)
0->1->3(权值：7)
这是两条关键路径
也就说明上面四条路径，其实也都可以说是关键路径
所有任务的 etv 和 ltv 都相等，意味着这条路上的每一天都是计划好的，毫无缓冲。那条连接这些毫无缓冲的顶点的边，就是关键路径。所以我们这次的测试样例是特例！恰好所有顶点都毫无缓冲，所有指向边都是关键路径！！！
*/
int main(){
    system("chcp 65001");
    GraphAdjList G;
    G.numVertexes=4;
    G.numEdges=4;
    for(int i=0;i<4;i++){
        G.adjlist[i].data=i;
        G.adjlist[i].firstedge=NULL;
    }
    EdgeNode*e;//中间桥梁的优势更多体现于循环（“自动化”处理），两两特指才能连接好你的链子！哈哈！(否者你就要不断的手动去找那个用于连接的指针，才能不损坏现有数据，繁琐！）有中间桥梁就可以在循环中很好的成链
    e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=1;e->weight=5;e->next=G.adjlist[0].firstedge;G.adjlist[0].firstedge=e;//0->1权5   所以从开始任务0到开始任务1之间的物质准备时间为5
    e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=2;e->weight=3;e->next=G.adjlist[0].firstedge;G.adjlist[0].firstedge=e;//0->2权3   所以从开始任务0到开始任务2之间的物质准备时间为3  
    e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=3;e->weight=2;e->next=G.adjlist[1].firstedge;G.adjlist[1].firstedge=e;//1->3权2  以此类推！！嘿嘿！并且任务0没有前置，所需的“物质准备时间”为0 直接开始！
    e=(EdgeNode*)malloc(sizeof(EdgeNode));e->adjvex=3;e->weight=4;e->next=G.adjlist[2].firstedge;G.adjlist[2].firstedge=e;//2->3权4
    TopologicalSort(G);
    return 0;
}
