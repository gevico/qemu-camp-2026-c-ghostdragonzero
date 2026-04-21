// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim(char *str) {
  if (str == NULL) return;

  // 1. 去除首部空格
  char *start = str;
  // 使用 isspace 可以识别空格、制表符(\t)、换行符(\n)等
  while (isspace((unsigned char)*start)) {
      start++;
  }

  // 如果字符串全是空格，start 会指向 '\0'
  if (*start == '\0') {
      *str = '\0';
      return;
  }

  // 2. 去除尾部空格
  char *end = str + strlen(str) - 1;
  while (end > start && isspace((unsigned char)*end)) {
      end--;
  }
  // 在最后一个有效字符后面加上结束符
  *(end + 1) = '\0';

  // 3. 移动字符串
  // 如果首部有空格被跳过，start 就不等于 str
  // 我们需要把中间的有效部分移动到 str 的起始位置
  if (start != str) {
      // 使用 memmove 处理内存重叠（源地址和目标地址重叠）
      memmove(str, start, strlen(start) + 1);
  }
}

int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("无法打开词典文件");
    return -1;
  }

  char line[1024];
  char current_word[100] = {0};
  char current_translation[1024] = {0};
  int in_entry = 0;

    
  while(fgets(line, 1024, file)!= NULL){
    line[strcspn(line, "\n")] = '\0';
    trim(line);
    strcpy(current_word, line + 1);
    fgets(line, 1024, file);
    line[strcspn(line, "\n")] = '\0';
    char *token_next = strchr(line, ':')+1;
    trim(token_next);
    strcpy(current_translation, token_next);
    //
    hash_table_insert(table, current_word, current_translation);
    in_entry++;
  }
  *dict_count = in_entry;

  fclose(file);
  return 0;
}

void to_lowercase(char *str) {
  for (; *str; ++str)
    *str = tolower((unsigned char)*str);
}

int __cmd_mytrans(const char* filename) {
  HashTable *table = create_hash_table();
  if (!table) {
    fprintf(stderr, "无法创建哈希表\n");
    return 1;
  }

  printf("=== 哈希表版英语翻译器（支持百万级数据）===\n");
  uint64_t dict_count = 0;
  if (load_dictionary("/workspace/exercises/20_mybash/src/mytrans/dict.txt", table, &dict_count) != 0) {
    fprintf(stderr, "加载词典失败，请确保 dict.txt 存在。\n");
    free_hash_table(table);
    return 1;
  }
  printf("词典加载完成，共计%ld词条。\n", dict_count);

  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "无法打开文件 dict.txt。\n");
    free_hash_table(table);
    return 1;
  }

  char line[256];
  while (fgets(line, sizeof(line), file) != NULL) {
    line[strcspn(line, "\n")] = '\0';

    if (strlen(line) == 0) {
        continue;
    }

    // 使用 strtok 按空格分割单词
    char *word = strtok(line, " ");
    while (word != NULL) {
      const char *translation = hash_table_lookup(table, word);
      printf("原文: %s\t", word);
      if (translation) {
          printf("翻译: %s\n", translation);
      } else {
          printf("未找到该单词的翻译。\n");
      }

      word = strtok(NULL, " ");
    }
  }

  free_hash_table(table);
  return 0;
}