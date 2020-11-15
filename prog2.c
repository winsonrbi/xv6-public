#include "types.h"
#include "stat.h"
#include "user.h"
int main(int argc, char *argv[])
{
	int num_tickets = settickets(20);
	printf(1,"Number of tickets for prog2 %d\n",num_tickets);
	// write your own function here
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
	printf(1,"Number of executions for prog2 %d\n",countexec());
	exit();
}
