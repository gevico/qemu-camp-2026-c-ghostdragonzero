#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char* url) {
    int err = 0;
    char *url_new = malloc(strlen(url));
    memcpy(url_new, url, strlen(url));
    //因为是const 先拷贝才能使用strtok  因为strtok会修改字符串
    

    // TODO: 在这里添加你的代码
    char *token;
    token = strtok(url_new, "?");
    if (token == NULL)
        return err;
    while((token = strtok(NULL, "=")) != NULL){
        char * value;
        value = strtok(NULL, "&");
        printf("key = %s, value = %s\n", token, value);
    }

exit:
    return err;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}