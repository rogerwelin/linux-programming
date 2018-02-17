#include <stdio.h>
#include <stdlib.h>

char globBuf[65536];            /* uninitialized data segment */
int primes[] = { 2, 3, 5, 7};   /* initialized data semgent */

static int square(int x) {      /* allocated in frame for square() */
  int result;                   /* allocated in frame for square() */

  result = x * x;
  return result;                /* return value passed via register */
}

static void doCalc(int val) {   /* allocated in frame for doCalc() */
  printf("The square of %d is %d\n", val, square(val));

  if (val < 1000) {
    int t;                      /* allocated in frame for doCalc() */

    t = val * val * val;
    printf("The cube of %d is %d\n", val, t);
  }

}

int main(int argc, char *argv[]) {  /* Allocated in frame for main() */
  static int key = 9973;            /* initialized data segment */
  static char mbuf[10240000];       /* uninitialized data segment */
  char *p;                          /* allocated in frame ... */

  p = malloc(1024);                 /* points to memory in heap segment */
  doCalc(key);

  exit(EXIT_SUCCESS);

}
