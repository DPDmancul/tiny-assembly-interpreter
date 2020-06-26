/**
 * @file vector.h
 * @author Davide Peressoni (dp.d-@live.it)
 * @brief Library for managing automatic growing vectors.
 * @version 1.0.0
 * @date 2020-05-08
 *
 * @copyright Copyright (c) 2020 Davide Peressoni
 */

#ifndef _VECTOR
#define _VECTOR

#include<stddef.h>
#include<inttypes.h>

/// Generic growable vector.
typedef struct{
  /// Pointer to first vector element
  void *p;
  /// Size of a vector element
  size_t element_size;
  /// Number of elements in the vector
  size_t size;
  /// Number of elements the vector can contain
  size_t capacity;
} vector_t;

/**
 * @brief Allocates memory for the given vector.
 *
 * @param v Vector to allocate.
 *
 * Not required if the init capacity is zero.
 */
void vector_allocate(vector_t *v);

/**
 * @brief Deallocates a given vector.
 *
 * @param v Vector to deallocate.
 */
void vector_deallocate(vector_t *v);

/**
 * @brief Returns an element from a vector.
 *
 * @param v Vector.
 * @param index Element index.
 * @return void* Pointer to the chosen element.
 */
void *vector_at(vector_t *v, size_t index);

/**
 * @brief Push a new element in the end of the given vector.
 *
 * @param v Vector.
 * @param e Pointer to element to push.
 * @return void* Pointer to the inserted element into the vector.
 */
void *vector_push(vector_t *v, void *e);

/**
 * @brief Push a new element of type T in the end of the given vector.
 *
 * @param V Vector.
 * @param T Element type
 * @param E Pointer to element to push.
 */
#define VECTOR_T_PUSH(V, T, E){\
  size_t _e_size = (V)->element_size;\
  size_t _packs = sizeof(T)/_e_size + ((sizeof(T)%_e_size) ? 1 : 0);\
  for(ptrdiff_t _i = 0; _i < _packs; ++_i)\
    vector_push(V, (uint8_t*)(E) + _i * _e_size);\
}

/**
 * @brief Returns an element of type T from a vector.
 *
 * @param V Vector.
 * @param T Element type
 * @param INDEX Element index.
 * @return T* Pointer to the chosen element.
 */
#define VECTOR_T_AT(V, T, INDEX) ((T*)vector_at(V, INDEX))

#endif
