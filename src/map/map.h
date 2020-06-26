/**
 * @file map.h
 * @author Davide Peressoni (dp.d-@live.it)
 * @brief Library for managing (string, size_t) maps.
 * @version 1.0.0
 * @date 2020-05-11
 *
 * @copyright Copyright (c) 2020 Davide Peressoni
 */

#ifndef _MAP
#define _MAP

#include<stdlib.h>

#define HASH_SIZE 101

/// Struct for items of the map.
typedef struct map_item {
  /// Pointer to the next item with the same hash.
  struct map_item *next;
  /// Key of the item.
  char *key;
  /// Value of the item.
  size_t value;
} map_item_t;

/// Map (string, size_t).
typedef struct{
  /// Hash table of pointers to map items.
  map_item_t *hash_table [HASH_SIZE];
} map_t;

/**
 * @brief Clones a string.
 *
 * @param s String to clone
 * @return char* Pointer to cloned string
 */
char *strcln(const char *s);

/**
 * @brief Init a map.
 *
 * @param map Map to init.
 */
void map_init(map_t *map);

/**
 * @brief Finds an item in the map by key and returns it.
 *
 * @param map Map where to find.
 * @param key Key to find.
 * @return map_item_t* Pointer to map item or NULL if not found.
 */
map_item_t *map_find(map_t *map, const char *key);

/**
 * @brief Insert a pair (key, value) into the map.
 *
 * @param map Map where to insert.
 * @param key Key to insert.
 * @param value Value to insert.
 * @return map_item_t* Pointer to inserted element.
 *
 * If an item with that key exists it will be update with the new value.
 */
map_item_t *map_insert(map_t *map, const char *key, const size_t value);

/**
 * @brief Deallocates a map.
 *
 * @param map Map to deallocate.
 */
void map_deallocate(map_t *map);

#endif
