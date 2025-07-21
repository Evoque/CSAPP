

/**
 * fds between process(parent-child)
 * 1. parent/child have different fds(fd number相同，但来自各自的descriptor table)
 * 2. fds指向的file是同一个（file table共享），即指向的v-node是同一个
 * 3. 结论相同fd号的不同fd，指向相同的中间态（file)的同一个v-node.
 */

#include "csapp.h"

int main()
{
  int fd;
  char c;

  fd = Open("foobar.txt", O_RDONLY, 0);
  if (Fork() == 0) {
    Read(fd, &c, 1);
    exit(0);
  }
  Wait(NULL);
  Read(fd, &c, 1);
  printf("c = %c\n", c);
  exit(0);
}