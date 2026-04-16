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


    // TODO: 在这里添加你的代码

  fclose(file);
  return 0;
}
