/**
 * @file map_test.c
 * @author Davide Peressoni (dp.d-@live.it)
 * @brief Unit test for map library.
 * @version 1.0.0
 * @date 2020-05-13
 *
 * @copyright Copyright (c) 2020 Davide Peressoni
 */

#include<stdio.h>
#include<assert.h>

#include "../src/map/map.h"

#define ARR_SIZE(A) (sizeof(A)/sizeof(*(A)))

int main(){
  map_t map;

  int source[] = {1,4,6,2,7,35354,554753,7667876,454766,674563476,454657,3547586836,56465753,1,5,73,634,3,4,66,43654,6364,43655427,23652,463,67483,67454,4768386,56543,25257,5753451,4574564,574365,36756357,46767563,547476746,5647457,4331,16683178,3115849,3154873,3154384,13549,1547,456,78,659,32644,169};

  map_init(&map);

  // To store the temp key
  char str[12];

  // Store each number from source, with itself as key
  for(size_t i = 0; i < ARR_SIZE(source); ++i){
    // Convert source[i] to string into str
    sprintf(str, "%d", source[i]);
    map_insert(&map, str, source[i]);
  }
  for(size_t i = 0; i < ARR_SIZE(source); ++i){
    sprintf(str, "%d", source[i]);
    assert(map_find(&map, str)->value == source[i]);
  }

  // Overwrite values in map with itself - 1
  for(size_t i = 0; i < ARR_SIZE(source); ++i){
    sprintf(str, "%d", source[i]);
    map_insert(&map, str, source[i]-1);
  }
  for(size_t i = 0; i < ARR_SIZE(source); ++i){
    sprintf(str, "%d", source[i]);
    assert(map_find(&map, str)->value == source[i]-1);
  }

  map_deallocate(&map);

  return 0;
}
