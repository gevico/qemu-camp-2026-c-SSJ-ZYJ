#include <stdio.h>
#include <string.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char *url) {
    int err = 0;
    char buf[1024];
    char *query;
    char *pair;
    char *amp;
    char *equal;

    if (url == NULL) {
        return -1;
    }

    strncpy(buf, url, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';

    query = strchr(buf, '?');
    if (query == NULL || *(query + 1) == '\0') {
        return 0;
    }

    query++;

    pair = query;
    while (pair != NULL && *pair != '\0') {
        amp = strchr(pair, '&');
        if (amp != NULL) {
            *amp = '\0';
        }

        equal = strchr(pair, '=');
        if (equal != NULL) {
            *equal = '\0';
            printf("key = %s, value = %s\n", pair, equal + 1);
        } else {
            printf("key = %s, value = \n", pair);
            err = -1;
        }

        if (amp != NULL) {
            pair = amp + 1;
        } else {
            break;
        }
    }

    return err;
}

int main(void) {
    const char *test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}