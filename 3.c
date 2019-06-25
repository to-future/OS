#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

#define READY 1
#define BLOCKED 0
#define SIZE 5   //盘子容量
#define EMPTY 0
#define ORANGE 1
#define APPLE 2

typedef struct Pcb{
        char name[20];  //名称
        int Pid;        //进程内部标识符
        int Pstatus;    //进程目前状态
}Pcb;

typedef struct Plate
{
	int num;       //当前水果数量
	int ap_num;    //当前苹果数量
	int or_num;    //当前橘子数量
	int fru[SIZE];
}Plate;

void See_Plate(Plate p){
	int i;
	printf("|");
	for (i = 0; i < SIZE; ++i)
	{
		if (p.fru[i]==ORANGE)
		{
			printf("%c|", 'O');
		}else if (p.fru[i]==APPLE)
		{
			printf("%c|", 'A');
		}else{
			printf(" |");
		}
		
	}
}

void Father_act(Plate *p, Pcb *m){
	int i;
	if (p->num >= SIZE)
	{
		m->Pstatus = BLOCKED;
		printf("father is blocked\n");
	}else{
		p->num++;    //总数加一
		if(rand()%2==0){
			p->or_num++;//橘子数目加一
            printf("father: put an 'O'range\n");
            for (i = 0; i < SIZE; ++i) //找空处
            {
            	if (p->fru[i]==EMPTY)
            	{
            		p->fru[i] = ORANGE; //将空处放置橘子
            		break;
            	}
            }
        }
        else{
			p->ap_num++;//苹果数目加一
            printf("father: put an 'A'pple\n");
            for (i = 0; i < SIZE; ++i)
            {
            	if (p->fru[i]==EMPTY)
            	{
            		p->fru[i] = APPLE; //将空处放置苹果
            		break;
            	}
            }
        }
	}
}

void Son_act(Plate *p, Pcb *m){
	int i;
	if (p->or_num <= 0)
	{
		m->Pstatus = BLOCKED;
		printf("son is blocked\n");
	}else{
		p->or_num--;//橘子数目减一
		p->num--;
        printf("son: take an 'O'range\n");
        for (i = 0; i < SIZE; ++i)
        {
        	if (p->fru[i]==ORANGE)
        	{
        		p->fru[i] = EMPTY; //拿走一个橘子
        		break;
        	}
        }
	}
}

void Daughter_act(Plate *p, Pcb *m){
	int i;
	if (p->ap_num <= 0)
	{
		m->Pstatus = BLOCKED;
		printf("daughter is blocked\n");
	}else{
		p->ap_num--;//苹果数目减一
		p->num--;
        printf("daughter: take an 'A'pple\n");
        for (i = 0; i < SIZE; ++i)
        {
        	if (p->fru[i]==APPLE)
        	{
        		p->fru[i] = EMPTY; //拿走一个苹果
        		break;
        	}
        }
	}
}

int main(int argc, char const *argv[])
{

    int num;
    int choice;
    Pcb dad = {"father",0, FREE};
    Pcb son = {"son", 1, FREE};
    Pcb daughter = {"daughter", 2, FREE};

    Plate f_plate = {0,0,0,{0,0,0,0,0}}
	printf("Input the scheduling count:\n");
	scanf("%d",&num);
	srand((unsigned) time(NULL));   //产生种子用于随机调度

    while(num--){
        choice = rand()%3;
        if(choice == 0){
        	printf("sched: father\n");
        	Father_act(&dad, &f_plate);
        	See_Plate(f_plate);
        }
        else if(choice == 1){
        	printf("sched: son\n");
        	Son_act(&son, &f_plate);
        	See_Plate(f_plate);
        }
        else if(choice == 2){
        	printf("sched: daughter\n");
        	Daughter_act(&daughter, &f_plate);
        	See_Plate(f_plate);
        }

    }
	return 0;
}