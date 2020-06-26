/**
 * @file vector_test.c
 * @author Davide Peressoni (dp.d-@live.it)
 * @brief Unit test for vector library.
 * @version 1.0.0
 * @date 2020-05-13
 *
 * @copyright Copyright (c) 2020 Davide Peressoni
 */

#include<assert.h>

#include "../src/vector/vector.h"

#define ARR_SIZE(A) (sizeof(A)/sizeof(*(A)))

int main(){

  // Storing elements of the same type

  int source[] = {1,4,6,2,7,35354,-554753,7667876,454766,-674563476,454657,-35486836,56465753,1,-5,73,634};

  vector_t a = {.element_size = sizeof(int)};
  vector_t b = {.element_size = sizeof(int)};
  vector_t c = {.element_size = sizeof(int), .capacity = 5};

  vector_allocate(&b);
  vector_allocate(&c);

  for(size_t i = 0; i < ARR_SIZE(source); ++i){
    assert(a.size == i);
    assert(b.size == i);
    assert(c.size == i);

    vector_push(&a, source+i);
    vector_push(&b, source+i);
    vector_push(&c, source+i);

    assert(*(int*)vector_at(&a, i) == source[i]);
    assert(*(int*)vector_at(&b, i) == source[i]);
    assert(*(int*)vector_at(&c, i) == source[i]);
  }

  vector_deallocate(&b);
  vector_deallocate(&c);

  /*****************************************************************/

  // Storing elements of different types

  size_t index;

  unsigned long lng = -2;
  index = a.size;
  VECTOR_T_PUSH(&a, unsigned long, &lng);
  assert(*VECTOR_T_AT(&a, unsigned long, index) == lng);

  unsigned char chr = -2;
  index = a.size;
  VECTOR_T_PUSH(&a, unsigned char, &chr);
  assert(*VECTOR_T_AT(&a, unsigned char, index) == chr);

  vector_deallocate(&a);

  unsigned short shr = -2;
  vector_t d = {.element_size = 1};
  VECTOR_T_PUSH(&d, unsigned short, &shr);
  assert(*VECTOR_T_AT(&d, unsigned short, 0) == shr);


  vector_deallocate(&d);

  return 0;
}