

#include "csapp.h"

/**
  Two fds, read the same file, 证明：
  每个fd(descriptor table)对应的file(file table), 虽然对应同一个v-node(v-node table)
 */

int main() 
{
  int fd1, fd2;
  char c1;
  char c2;
  char c3;

  fd1 = Open("foobar.txt", O_RDONLY, 0);
  fd2 = Open("foobar.txt", O_RDONLY, 0);

  Read(fd2, &c2, 1);
  Read(fd2, &c3, 1);


  Read(fd1, &c1, 1);

  printf("c1 = %c \n", c1);
  printf("c2 = %c \n", c2);
  printf("c3 = %c \n", c3);

  exit(0);
}