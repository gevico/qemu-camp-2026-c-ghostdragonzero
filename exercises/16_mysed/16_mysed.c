#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }

    // TODO: 在这里添加你的代码
    char *cmd_new = malloc(strlen(cmd));
    memcpy(cmd_new, cmd, strlen(cmd));
    char * token;
    token = strtok((cmd_new + 2), "/");
    char *str_old = malloc(strlen(token));
    memcpy(str_old, token, strlen(token));
    *old_str = str_old;
    token = strtok(NULL, "/");
    char *str_new = malloc(strlen(token));
    memcpy(str_new, token, strlen(token));
    *new_str = str_new;
    //如果不分配内存会重复释放
    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    // TODO: 在这里添加你的代码

    char *token = strstr(str, old);
    
    
    if (token == NULL)
        return;
    int nume = token - str;
    char *new_str = malloc(strlen(str));
    int i;
    strcpy(new_str, str);

    for ( i = 0; i < strlen(new); i++){
        str[nume + i] = new[i];
    }
    str[nume + i] = '\0';
    i = nume + strlen(old);
    strcat(str, (new_str + i));
}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;
    
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    
    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
