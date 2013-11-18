#ifndef __HEAP_H__
#define __HEAP_H__

/* Maximum number of values that can be stored in the heap. */
#define MAX_HEAP_ELEMS 100

/*
 * A simple heap data structure, for storing floats.
 */
typedef struct
{
  /* Number of values currently in the heap. */
  int num_values;

  /* The values in the heap. */
  float values[MAX_HEAP_ELEMS];
} float_heap;


/* Initialize a heap data structure. */
void init_heap(float_heap *pHeap);

/* Returns the first (i.e. smallest) value in the heap. */
float get_first_value(float_heap *pHeap);

/* Adds another value to the heap, in the proper place. */
void add_value(float_heap *pHeap, float newval);

#endif /* __HEAP_H__ */

