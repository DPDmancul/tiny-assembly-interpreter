/**
 * @file vector.c
 * @author Davide Peressoni (dp.d-@live.it)
 * @brief Library for managing automatic growing vectors.
 * @version 1.0.0
 * @date 2020-05-08
 *
 * @copyright Copyright (c) 2020 Davide Peressoni
 */

#include<stdlib.h>
#include<string.h>

#include "vector.h"

void vector_allocate(vector_t *v){
  if(!v)
    return;
  if(v->p)
    // If the vector is already allocated, deallocate it.
    vector_deallocate(v);
  v->p = malloc(v->capacity * v->element_size);
  v->size = 0;
}

void vector_deallocate(vector_t *v){
  free(v->p);
}

/**
 * @brief Extends the capacity of a too small vector.
 *
 * @param v Vector to extend.
 *
 * The capacity is doubled in order to make insert O(1) in average.
 */
static void vector_extend(vector_t *v){
  if(!v)
    return;
  if(v->capacity)
    v->capacity *= 2;
  else
    v->capacity = 1;
  v->p = realloc(v->p, v->capacity * v->element_size);
}

void *vector_at(vector_t *v, size_t index){
  if(index >= v->size || !v->p)
    return NULL;
  return (uint8_t*)v->p + index * v->element_size;
}

void *vector_push(vector_t *v, void *e){
  if(!e)
    return NULL;
  if(v->size == v-> capacity)
    if(vector_extend(v), !v->p)
      return NULL;
  return memcpy((uint8_t*)v->p + (v->size++) * v->element_size, e, v->element_size);
}