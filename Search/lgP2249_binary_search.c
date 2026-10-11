#include<stdio.h>
//遍历正常情况下都是实质与核心，那这种情况下，算法的实质与核心就在于完成遍历的效率！
int a[1000005];//n最大10的六次方，开大点，多五个&全局数组哈哈~3
int binarySearch(int target,int n){//数组a要先于声明的原因也是因为它的参数设计里没有数组a,但里面又要用a，
	int left=1,right=n;
	int ans=-1;
	while(left<=right){//left与right交汇的那一刻，遍历已经完成了，客观事实
		int mid=(left+right)/2;//不理解什么溢出，所以就直接这样写了
		if(a[mid]==target) {
		 ans=mid;//return mid;//这里并非是第一个哦，mid就是最终答案！
		 right=mid-1;//更先出现只可能在左边，排出已确定的继续查找左半边区间！！
	}
		else if(a[mid]<target){
			left=mid+1;
		}
		else{
			right=mid-1;//对于有序数列，就可以用高效的二分查找手段哈哈，if&else结构是个整体，有整体效应的哦，相互之间可以互相补充确定范围哈哈
		}
	}
 return ans;//循环遍历结束再返回答案，便能确保是第一次出现的位置哈哈！	//return -1;//循环结束，完成遍历，找不到那就是找不到
}
//注意程序执行顺序啊，老忘多多注意！！不然不认识！！
//你把 int a[1000005]; 写在了 binarySearch 的后面。C 语言是严格从上往下读的，binarySearch 里用到的 a，必须在这个函数之前被声明



int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);//题目说下标从1开始，所以我们数组也从1开始存，看开大点的好处，牺牲一个空间换取便利哈哈，聪明啊，宝贝，木马~
	}
	for(int i=0;i<m;i++){
	int target;
	scanf("%d",&target);
	printf("%d ",binarySearch(target,n));
	}
	
	return 0;
}
