#include "types.h"
#include "stat.h"
#include "user.h"

int 
main(void)
{
	printf(1,"Testing lab 1 syscall info number of processes running %d\n",info(1));
	int pid = fork();
	if (pid == 0)
	{
		printf(1,"Testing after fork, number of processes runing now is %d\n",info(1));
	}
	else{
		wait();
		printf(1,"Testing after child process is terminated, number of processes running now is %d\n",info(1));
		printf(1,"Testing lab 1 syscall info total number of syscalls %d\n",info(2));
		//account for count from zero
		counter = counter + 1;
		printf(1,"Testing after allocating int array of size %d, total number of memory pages %d\n",counter,info(3));
		printf(1,"Printing pid %d \n", getpid());
		
	}
	exit();
}
