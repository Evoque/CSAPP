
#include "../code/csapp.h"

int readcnt; 
sem_t mutex, w;

void reader(void)
{
  while (1) {
    P(&mutex);
    readcnt++;
    if (readcnt == 1) /* First in */
      P(&w); 
    V(&mutex);

    /* Critical section */
    /* Reading happens */

    P(&mutex);
    readcnt--;
    if (readcnt == 0) /* Last out */
        V(&w);
    V(&mutex);
  }
}

void writer(void) 
{
  while (1) {
    P(&w);

    /* Critical section */
    /* Writing happens */
    V(&w);
  }
}