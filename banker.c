#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0

int print(int a[], int b[], int available){
	printf("available: %d\n", available);
	printf("\talloc\tneed\n");
	printf("p1:\t%d\t%d\n", a[1], b[1]);
	printf("p2:\t%d\t%d\n", a[2], b[2]);
	printf("p3:\t%d\t%d\n", a[3], b[3]);
	return 1;
}
int main(int argc, char const *argv[])
{

	//init simply
	int available = 3;
	int Need[4] = {0, 5, 2, 7};
	//int Max[4] = {0, 10, 4, 9};
	int Alloc[4] = {0, 5, 2, 2};
	//temp
	int t_available;
	int t_Need[4];
	int t_Alloc[4];
	
	int pid, request;
	int i;
	int pass = 0;
	int finish[4]={1,1,1,1};
	while(1){
		//init
		pass = 0;
		for (i = 1; i <= 3; ++i)
		{
			t_Need[i]=Need[i];
			t_Alloc[i]=Alloc[i];
		}
		print(Alloc, Need, available);
		printf("Type a pid(1~3) and its request:\n");
		scanf("%d%d", &pid, &request);
		if ((request > available)||(request > Need[pid])){
			printf("input illegal\n");
			printf("---------------------------------------\n");
			continue;
		}else{
			//temporary
			t_available = available-request;
			t_Need[pid] = Need[pid]-request;
			t_Alloc[pid] = Alloc[pid]+request;
			//初始化finish
			for (i = 1; i <= 3; ++i)
			{
				if (t_Need==0)
				{
					finish[i]=True;
				}else{
					finish[i]=False;
				}
			}
			//安全性检查
			for(i=1; i<=3; i++)
		    {
		        if(finish[i]==False && t_Need[i]<=t_available)
		        {
		        	//尝试分配
		            t_available += t_Alloc[i];
		            t_Alloc[i] += t_Need[i];
		            t_Need[i]=0;
		            finish[i] = True;
		            i = 0;
		        }
		    }
			
		    for (i = 1; i <= 3; ++i)//检查进程是否全部结束
		    {
		    	if (finish[i])
		    	{
		    		pass++;
		    	}
		    }
		    if (pass==3)//进程全部结束，说明此时是安全状态
		    {
		    	printf("Success!\n");
		    	//进行分配
		    	available -= request;
				Need[pid] -= request;
				Alloc[pid] += request;
				if (Need[pid]==0)
				{
					available += Alloc[pid];
				}
		    }else{//若没有通过安全性检查
		    	printf("Cannot devide resource to it!\n");

		    }
		    printf("---------------------------------------\n");
		}


	}
	return 0;
}