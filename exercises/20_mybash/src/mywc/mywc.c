#include "mywc.h"

// 创建哈希表
WordCount **wc_create_hash_table() {
  WordCount **hash_table = calloc(HASH_SIZE, sizeof(WordCount *));
  return hash_table;
}

// 简单的哈希函数
unsigned int hash(const char *word) {
  unsigned long hash = 5381;
  int c;
  while ((c = *word++))
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  return hash % HASH_SIZE;
}

// 检查字符是否构成单词的一部分
bool is_valid_word_char(char c) { return isalpha(c) || c == '\''; }

// 转换为小写
char to_lower(char c) { return tolower(c); }

// 添加单词到哈希表
void add_word(WordCount **hash_table, const char *word) {
  // TODO: 在这里添加你的代码
  unsigned int hash_nume = hash(word);
  int i  = 0;
  if(hash_table[hash_nume]== NULL){
    hash_table[hash_nume] = malloc(sizeof(WordCount));
    while(word[i] != '\0'){
      hash_table[hash_nume]->word[i] = word[i];
      i++;
    }
    hash_table[hash_nume]->word[i] = word[i];
    
    hash_table[hash_nume]->count = 1;
  }else{
    hash_table[hash_nume]->count +=1;
  }
}

// 打印单词统计结果
/**
 * @brief 打印哈希表中所有单词的统计信息
 * 
 * 遍历哈希表并输出每个单词及其出现次数。
 * 
 * @param hash_table 指向哈希表的指针数组，每个元素指向 WordCount 结构
 */
void print_word_counts(WordCount **hash_table) {
  printf("Word Count Statistics:\n");
  printf("======================\n");
  for(int i = 0 ; i < HASH_SIZE; i++){
    if (hash_table[i] != NULL){
      printf("%-21s%d\n", hash_table[i]->word, hash_table[i]->count);
    }
  }


}

// 释放哈希表内存
void wc_free_hash_table(WordCount **hash_table) {
  for (int i = 0; i < HASH_SIZE; i++) {
    WordCount *entry = hash_table[i];
    while (entry != NULL) {
      WordCount *temp = entry;
      entry = entry->next;
      free(temp);
    }
  }
  free(hash_table);
}

// 处理文件并统计单词
void process_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  WordCount **hash_table = wc_create_hash_table();
  char word[MAX_WORD_LEN];
  int word_pos = 0;
  int c;

  while ((c = fgetc(file)) != EOF) {
    if (is_valid_word_char(c)) {
      if (word_pos < MAX_WORD_LEN - 1) {
        word[word_pos++] = to_lower(c);
      }
    } else {
      if (word_pos > 0) {
        word[word_pos] = '\0';
        add_word(hash_table, word);
        word_pos = 0;
      }
    }
  }

  // 处理文件末尾的最后一个单词
  if (word_pos > 0) {
    word[word_pos] = '\0';
    add_word(hash_table, word);
  }

  fclose(file);
  print_word_counts(hash_table);
  //wc_free_hash_table(hash_table);
}

int __cmd_mywc(const char* filename) {
  process_file(filename);
  return 0;
}