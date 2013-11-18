#include <stdio.h>
#include <stdlib.h>

#include "heap.h"


/* Test the heap. */
int main(int argc, char **argv)
{
  float_heap h;
  int i;
  float lastval;

  init_heap(&h);

  /* Use a seed so that the sequence of random values
   * is always the same.
   */
  srand(11);

  /* Fill up the heap with random values. */
  for (i = 0; i < MAX_HEAP_ELEMS; i++)
    add_value(&h, rand() % 1000);

  /*
   * Print out the results.  If anything is out of order,
   * flag it.  (Pull the very first value separately so that
   * we don't have to set lastval to something strange just
   * to get the test to work...)
   */

  lastval = get_first_value(&h);
  printf("Value 0 = %f\n", lastval);

  for (i = 1; i < MAX_HEAP_ELEMS; i++)
  {
    float val = get_first_value(&h);

    printf("Value %d = %f\n", i, val);
    if (val < lastval)
      printf("  ERROR:  OUT OF ORDER.\n");

    lastval = val;
  }

  return 0;
}

