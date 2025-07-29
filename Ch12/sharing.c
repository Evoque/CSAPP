#include "../code/csapp.h"
#define N 2
void *thread(void *vargp);

char **ptr; /* Global variable */

int main()
{
  int i;
  pthread_t tid;
  char *msgs[N] = {
      "Hello from foo",
      "Hello from bar"};

  ptr = msgs;
  for (i = 0; i < N; i++)
    Pthread_create(&tid, NULL, thread, (void *)(intptr_t)i);
  Pthread_exit(NULL);
}

void *thread(void *vargp)
{
  int myid = (int)(intptr_t)vargp;
  static int cnt = 1;
  cnt *= 10;
  printf("[%d]: %s (cnt=%d)\n", myid, ptr[myid], ++cnt);
  return NULL;
}