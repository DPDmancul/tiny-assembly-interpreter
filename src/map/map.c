/**
 * @file map.c
 * @author Davide Peressoni (dp.d-@live.it)
 * @brief Library for managing (string, size_t) maps.
 * @version 1.0.0
 * @date 2020-05-11
 *
 * @copyright Copyright (c) 2020 Davide Peressoni
 */

#include<string.h>

#include "map.h"

void map_init(map_t *map){
  memset(map, 0, sizeof(map_t));
}

/**
 * @brief Returns the hash of a given string.
 *
 * @param s String to hash.
 * @return size_t Hash of the string.
 */
size_t hash(const char *s){
  size_t h;
  for (h = 0; *s; ++s)
    h = *s + 31 * h;
  return h % HASH_SIZE;
}

map_item_t *map_find(map_t *map, const char *key){
  for(map_item_t *p = map->hash_table[hash(key)]; p; p = p-> next)
    if(!strcmp(key, p->key))
      return p;
  return NULL;
}

char *strcln(const char *s){
  char *p = (char *) malloc(strlen(s)+1);
  if (p)
    strcpy(p, s);
  return p;
}

map_item_t *map_insert(map_t *map, const char *key, const size_t value){
  // Check if an item with this key already exists
  map_item_t *item = map_find(map, key);
  if(!item){
    // Since it doesn't exist create a new element
    if(!( item = (map_item_t*)malloc(sizeof(map_item_t)) ))
      return NULL;
    item->key = strcln(key);
    if(! item->key){
      // If the key cloning failed delete the created item
      free(item);
      return NULL;
    }
    // Put the new item in the hash table, in front of the linked list of the items with the same hash
    map_item_t **table_item = map->hash_table+hash(key);
    item->next = *table_item;
    *table_item = item;
  }
  // Update the value
  item->value = value;
  return item;
}

void map_deallocate(map_t *map){
  for(size_t i = 0; i < HASH_SIZE; ++i)
    for(map_item_t *p = map->hash_table[i]; p;){
      free(p->key); // free the key
      map_item_t *t = p->next;
      free(p); // free the item
      p = t;
    }
}
