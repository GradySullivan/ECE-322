#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>

#define PAGES 65536
#define WORDS_PAGE (4096/4)

int main() {
  int * ptr; 

  ptr = (int *) mmap (NULL,
             4096 * PAGES,
             PROT_READ | PROT_WRITE,
             MAP_ANONYMOUS | MAP_PRIVATE,
             -1,
             0);
  if(ptr == MAP_FAILED) {
    fprintf(stderr, "mmap is failed with error %s.\n", strerror(errno));
  }
  unsigned long i;
  int j;

  for(j = 0; j < 1024; j++) {
    for(i = 0; i < WORDS_PAGE*PAGES; i++) {
     ptr[i] = i;
    }
  }
} 

