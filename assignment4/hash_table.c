#include <stdlib.h>
#include <string.h> 
#include "hash_table.h"

#ifndef HASH_TABLE_SIZE
#define HASH_TABLE_SIZE 5
#endif

// According to http://www.cse.yorku.ca/~oz/hash.html

int compute_hash(const char *key, int size){
  unsigned long hash = 5381;
  int c;
  
  do{
    c = *key;
    hash = hash*33 + c;
    key++;
  }while(c);
  
  return hash % size;
}


struct hash_elem *pop(struct hash_elem **bucket){
  struct hash_elem *current = *bucket;
  
  if(current == NULL)
    return NULL;
  
  *bucket = current->next;
  current->next = NULL;
  return current;
}

void push(struct hash_elem *elem, struct hash_elem **bucket){
  elem->next = *bucket;
  *bucket = elem;
}


void hash_create(struct hash_table **t, hash_data_free_fn f){
  struct hash_table *hash_table = malloc(sizeof(struct hash_table));

  if(hash_table == NULL)
    return NULL;

  hash_table->data_free = f;
  hash_table->num_buckets = HASH_TABLE_SIZE;
  hash_table->buckets = malloc(hash_table->num_buckets * sizeof(struct hash_elem*));

  if(hash_table->buckets == NULL){
    free(hash_table);
    return NULL;
  }

  t = &hash_table;
}

void hash_release(struct hash_table *hash_table){
  for(int i=0; i<hash_table->num_buckets; ++i){
    struct hash_elem *bucket = hash_table->buckets[i];
    while(bucket != NULL){
      free(pop(&bucket));
    }
  }
  free(hash_table->buckets);
  free(hash_table);
}


void hash_insert(struct hash_table *hash_table, const char* key, void *data){
  int index = compute_hash(key, hash_table->num_buckets);
  struct hash_elem *bucket = hash_table->buckets[index];
  if(bucket->key == NULL){
    bucket->key = key;
    bucket->data = data;
  }else{
    struct hash_elem *new_elem = malloc(sizeof(struct hash_elem));
    new_elem->key = key;
    new_elem->data = data;
    push(new_elem, &hash_table->buckets[index]);
  }
}


void* hash_find(struct hash_table *hash_table, const char* key){
  int index = compute_hash(key, hash_table->num_buckets);
  struct hash_elem *bucket = hash_table->buckets[index];
  while(bucket != NULL){
    if(strcmp(bucket->key, key) == 0){
      return bucket->data;
    }
    bucket = bucket->next;
  }
  return NULL;
}


void hash_delete(struct hash_table *hash_table, const char* key){
  int index = compute_hash(key, hash_table->num_buckets);
  struct hash_elem **bucket = &hash_table->buckets[index];
  struct hash_elem *prev, *curr;
  for(prev=NULL, curr=*bucket; curr!=NULL; prev=curr, curr=curr->next){
    if(strcmp(curr->key, key) == 0){
      if(prev == NULL){
        *bucket = curr->next;
      }else{
        prev->next = curr->next;
      }
      free(curr);
      break;
    }
  }
}
