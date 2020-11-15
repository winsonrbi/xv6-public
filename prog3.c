#include "types.h"
#include "stat.h"
#include "user.h"
int main(int argc, char *argv[])
{
	int num_tickets = settickets(10);
	int init_cpu_exec = countglobalexec();
	// write your own function here
	
	printf(1,"Number of tickets for prog3 %d\n",num_tickets);
	int i,k;
	const int loop=43000;
	for(i=0;i<loop;i++)
	{
		asm("nop");   //in order to prevent the compiler from optimizing the for loop
		for(k=0;k<loop;k++)
			{
				asm("nop");
			}
	}
	int proc_count = countexec();
	int total_cycles =  (countglobalexec()-init_cpu_exec);
	printf(1,"Number of executions for prog3 %d and total CPU executions since prog3 start %d\n",proc_count, total_cycles);
	exit();
}
