
#include "../code/csapp.h"

void *thread_routine(void *vargp);

int main()
{
  pthread_t tid;
  Pthread_create(&tid, NULL, thread_routine, NULL);
  Pthread_join(tid, NULL);
  exit(0);
}

void *thread_routine(void *vargp)
{
  printf("Hello from thread \n");
  return NULL;
}