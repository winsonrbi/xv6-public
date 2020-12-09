#define PGSIZE 4096
#include "types.h"
#include "user.h"
#include "stat.h"
void thread_create(void* (*start_routine)(void*),void *arg){
  void* stack = malloc(PGSIZE);
  int size = PGSIZE;
  if(clone(stack,size)==0){
    start_routine(arg);
  }
} 

int main()
