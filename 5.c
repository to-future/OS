#include <stdio.h>
#include <string.h>
int main(int argc, char const *argv[])
{
	//创建页表
	int PT[10] = {32102,443217,6723,8985,11238,29065,234205,45812,240561,300451};
	int l_addr;//logical address
	int p_addr;//physical address
	int i_addr;
	int Pno;
	char c;
	//2G = 2^21B =2097152   4K = 2^12B=4096
	while(1){
		printf("Decimal input 'D'\n");
		printf("Hexadecimal input 'H'\n:");
		scanf("%c", &c);
		getchar();
		if (c=='D')
		{
			printf("Input logical address:");
			scanf("%d", &l_addr);
			getchar();
			Pno = l_addr/4096; //4KB
			if (Pno>9)
			{
				printf("out of memory!\n");
				continue;
			}
			p_addr = PT[Pno]*4096+(l_addr % 4096);
			printf("%d\n", p_addr);
		}else{
			if (c=='H')
			{
				printf("Input logical address:");
				scanf("%x", &l_addr);
				getchar();
				i_addr = l_addr&0x00000fff; //取后12位作为页内地址
				Pno = l_addr&0xfffff000; //取前19位作为页号
				Pno = Pno>>12; //右移12位
				if (Pno>9)
				{
					printf("out of memory!\n");
					continue;
				}
				p_addr = (PT[Pno]<<12)|i_addr;
				printf("%x\n", p_addr);
			}else{
				printf("ERROR\n");
				getchar();
			}
		} 
	}
	
	return 0;
}