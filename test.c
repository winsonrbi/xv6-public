#include "types.h"
#include "stat.h"
#include "user.h"

int 
main(void)
{
	printf(1,"Testing lab 1 syscall info number of processes running %d\n",info(1));
	printf(1,"Testing lab 1 syscall info total number of syscalls %d\n",info(2));
	printf(1,"Testing lab 1 syscall info total number of memory page %d\n",info(3));
	printf(1,"Printing pid %d \n", getpid());
	exit();
}
