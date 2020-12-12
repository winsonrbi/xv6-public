#define PGSIZE 4096
#include "types.h"
#include "user.h"
#include "stat.h"
#include  "x86.h"

struct params{
  int num_passes;
  int tid;
  lock_t *lock;
  int num_players;
};

void initlock(lock_t *lock){
  *lock = 0;
  printf(1,"Initalized Lock\n");
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
  if (stack == 0){
	printf(1,"malloc fail \n");
  }
  int size = PGSIZE*2;
  int tid = clone(stack,size);
  if(tid != 0){
    return;
  }
  printf(2,"Starting Routine \n");
  (start_routine)(arg);
  printf(1,"Routine finished\n");
  free(stack);
  exit();
} 

void frisbee(void* p){
  printf(1,"Entered frisbee \n");
  struct params * args = p;
  int num_passes = args->num_passes;
  int tid = args->tid;
  int num_players = args->num_players;
  lock_t *lock = args->lock;
  int counter = 0;
  while(counter< num_passes){
    if(tid == counter%(num_players)){
      printf(1, "Acquiring Lock");
      lock_acquire(lock);
      printf(1,"Pass number no:  %d, Thread %d is passing the token to thread %d\n", counter, tid, tid+1);
      counter++;
      lock_release(lock);
    }
  }
}

void test(void* p){
  printf(1,"Thread Created!");
}
int main(int argc, char *argv[]){
  printf(1,"Starting Main of frisbee\n");
  if(argc != 3)
  {
    printf(1,"Error incorrect amount of parameters\n");
    return 0;
  }
  int players = atoi(argv[1]);
  int num_passes = atoi(argv[2]); 
  lock_t *lock = malloc(sizeof(lock_t));
  initlock(lock);
  for(int i=0; i < players;i++){
    struct params p= {num_passes, i, lock,players};
    thread_create(frisbee,(void*) &p); 
  } 
  return 0;
}

