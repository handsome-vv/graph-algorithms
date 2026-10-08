#include<stdio.h>

void swap(int*x,int*y){
	int t=*x;
	*x=*y;
	*y=t;
}//哈哈注意程序执行步骤！swap要在它被调用前声明否则后面不认识！！！哈哈！约科实！！MARX!!

void quicksort(int a[],int left,int right){
	//递归首先考虑终止条件：如果left>=right，直接return，我们后续调用它时，要正确传入参数！健壮性完善也是递归终止条件哈哈
	if(left>=right) return;//说明数据已被遍历穷举了，这就是实质与核心！后面科学的设计是为了高效！！哈哈MARX意义！！！MARX意义！！！MARX意义！！
	//选基准值（一定要选中间的或随机的！否则数据大则容易超时！）
	int mid=a[(left+right)/2];
	//定义双指针
	int i=left,j=right;//简化哈哈！
	//核心循环：while(i<=j)
	while(i<=j){
		//左边找一个>=mid的
		while(a[i]<mid) i++;
		//右边找一个<=mid的
		while(a[j]>mid) j--;//注意是j--,i是初始化为'最左边'的下标，j是初始化为'最右边'的下标！！
		//因为我们的排序小的在左边，现在在排序，所以把左边大于中间的找出来，即把不符合排序的找出来！二分法豪用！豪工具！！
		if(i<=j){//说明找到了两边需要交换的数
			swap(&a[i],&a[j]);
			i++;
			j--;//程序执行步骤!!循环控制变量！值相应变化进入下一轮循环！！
		}
	}
	//递归左边和右边,上一步的基准值mid的数值并非正好就是中位数，但是位置的中位，排序也相应完成一部分，这就是递归大问题变成多个相同的小问题
	quicksort(a,left,j);//定义的变量在作用域内生效，且是我们需要的数据！！key！！别搞错！！
	quicksort(a,i,right);//嗯~左右开弓 
	//left和right,就是真正实际上的最左和最右！！所以递归的参数位置，为了算法的正确性是不能写错的！因为i,j在上面的步骤后值变化且不确定，但算法执行时i,j相对位置确定！
	//i<=j!,所以这样放置参数位置才能确保完全覆盖！所有数据均可访问，才能实现完全排列！！
}



int main(){
	int n;
	scanf("%d",&n);
	int a[100005];
	for(int i=0;i<n;i++){
	scanf("%d",&a[i]);
	}
	quicksort(a,0,n-1);//名字里不能包含减号！约科实！
	for(int i=0;i<n;i++){
		printf("%d ",a[i]);
	}
	return 0;
}
