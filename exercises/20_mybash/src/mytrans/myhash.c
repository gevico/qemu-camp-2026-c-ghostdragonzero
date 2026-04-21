// hash_table.c
#include "myhash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// djb2 哈希函数（经典字符串哈希，分布均匀）
unsigned long hash_function(const char *str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  return hash;
}

// 创建哈希表
HashTable *create_hash_table() {
  HashTable *table = malloc(sizeof(HashTable));
  if (!table)
    return NULL;
  for (int i = 0; i < HASH_TABLE_SIZE; i++) {
    table->buckets[i] = NULL;
  }
  return table;
}

// 释放单个节点
void free_node(HashNode *node) {
  if (node) {
    free(node->key);
    free(node->value);
    free(node);
  }
}

// 释放整个哈希表
void free_hash_table(HashTable *table) {
  if (!table)
    return;
  for (int i = 0; i < HASH_TABLE_SIZE; i++) {
    HashNode *curr = table->buckets[i];
    while (curr) {
      HashNode *tmp = curr;
      curr = curr->next;
      free_node(tmp);
    }
  }
  free(table);
}

// 插入键值对
int hash_table_insert(HashTable *table, const char *key, const char *value) {
  if (!table || !key || !value)
    return 0;

  unsigned long hash = hash_function(key) % HASH_TABLE_SIZE;
  HashNode *node = table->buckets[hash];

  //printf("%s\n hash %d \n%s\n", key,hash, value);
  HashNode *new = malloc(sizeof(HashNode));
  //这里因为结构体里还是指针所以还是不能直接用strcpy来拷贝
  new->key = strdup(key);
  new->value = strdup(value);
  //这里不能直接用key 由于key是局部变量要拷贝过去
  new->next = NULL;
  
  //这里我创建了一个指向节点指针
  if (table->buckets[hash] == NULL){
    //printf("add new node\n");
    table->buckets[hash] = new;
  }else{
    new->next= table->buckets[hash];
    table->buckets[hash] = new;
  }

  return 1;
}

// 查找键
const char *hash_table_lookup(HashTable *table, const char *key) {
  if (!table || !key)
    return NULL;

    unsigned long hash = hash_function(key) % HASH_TABLE_SIZE;
    HashNode *node = table->buckets[hash];
  
    while(node){
      if(strcmp(node->key, key) == 0){
        return node->value;
      }
      node = node->next;
    }

  return NULL; // 未找到
}
