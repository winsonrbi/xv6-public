#define PGSIZE 4096
#include "types.h"
#include "user.h"
#include "stat.h"
#include  "x86.h"

void initlock(lock_t *lock);
void lock_acquire(lock_t *lock);
void lock_release(lock_t *lock);

int num_players = 0;
int num_passes = 0;
int counter = 0;
int thread_ids[15] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
lock_t lock = 0;
//initlock(&lock);

void initlock(lock_t *lock){
  *lock = 0;
  //printf(1,"Initalized Lock\n");
}

void lock_acquire(lock_t *lock){  
  while(xchg(lock, 1) != 0);
}
void lock_release(lock_t *lock){
  xchg(lock,0);
}
void thread_create(void (*start_routine)(void*),void *arg){
  void* stack = malloc(PGSIZE*2);
  if((uint)stack % 4096){
	stack = stack + (4096 - (uint)stack % 4096);
  }
  //if (stack == 0){
  //  printf(1,"malloc fail \n");
  //}
  int clone_ret = clone(stack,start_routine,arg);
  if(clone_ret != 0){
   return;
  }
} 

void frisbee(void* arg){
  int tid = *(int*) arg;
  lock_acquire(&lock);
  while(counter< num_passes){
    if(tid == counter%(num_players)){
      printf(1,"Pass number no:  %d, Thread %d is passing the token to thread %d\n", counter, tid, tid+1);
      counter++;
    }
    lock_release(&lock);
    sleep(20);
  	lock_acquire(&lock);
  }
  for(;;);
}

int main(int argc, char *argv[]){
  if(argc != 3)
  {
    printf(1,"Error incorrect amount of parameters\n");
    return 0;
  }
  num_players = atoi(argv[1]);
  num_passes = atoi(argv[2]); 
  for(int i=0; i < num_players;i++){
    thread_create(frisbee, &thread_ids[i]); 
  } 
  for(;;);
  return 0;
}

