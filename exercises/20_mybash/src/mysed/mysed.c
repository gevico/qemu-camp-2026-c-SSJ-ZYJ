#include "mysed.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    // 检查输入参数有效性
    if (!cmd || !old_str || !new_str) {
        return -1;
    }
    
    // 初始化输出参数
    *old_str = NULL;
    *new_str = NULL;
    
    // 检查是否以 's' 开头
    if (cmd[0] != 's') {
        return -1;
    }
    
    // 获取分隔符（通常是 '/'）
    char delim = cmd[1];
    if (delim == '\0') {
        return -1;
    }
    
    // 查找第二个分隔符
    const char *second_delim = strchr(cmd + 2, delim);
    if (!second_delim) {
        return -1;
    }
    
    // 查找第三个分隔符
    const char *third_delim = strchr(second_delim + 1, delim);
    if (!third_delim) {
        return -1;
    }
    
    // 提取 old_str
    int old_len = second_delim - (cmd + 2);
    *old_str = malloc(old_len + 1);
    if (!*old_str) {
        return -1;
    }
    strncpy(*old_str, cmd + 2, old_len);
    (*old_str)[old_len] = '\0';
    
    // 提取 new_str
    int new_len = third_delim - (second_delim + 1);
    *new_str = malloc(new_len + 1);
    if (!*new_str) {
        free(*old_str);
        *old_str = NULL;
        return -1;
    }
    strncpy(*new_str, second_delim + 1, new_len);
    (*new_str)[new_len] = '\0';

    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new_text) {
    // 检查输入参数有效性
    if (!str || !old || !new_text) {
        return;
    }
    
    // 查找第一个匹配位置
    char *pos = strstr(str, old);
    if (!pos) {
        return;  // 未找到匹配
    }
    
    // 计算长度
    int old_len = strlen(old);
    int new_len = strlen(new_text);
    int str_len = strlen(str);
    
    // 移动后续的字符
    if (new_len != old_len) {
        if (new_len > old_len) {
            // 需要扩展，可能超过缓冲区（这里假设缓冲区足够大）
            memmove(pos + new_len, pos + old_len, str_len - (pos - str) - old_len + 1);
        } else {
            // 需要压缩
            memmove(pos + new_len, pos + old_len, str_len - (pos - str) - old_len + 1);
        }
    }
    
    // 复制新字符串
    memcpy(pos, new_text, new_len);
}

int __cmd_mysed(const char* rules, const char* str) {
    // 检查输入参数有效性
    if (!rules || !str) {
        fprintf(stderr, "Error: NULL rules or str parameter\n");
        return 1;
    }

    printf("rules: %s\n", rules);
    printf("str: %s\n", str);

    char* old_str = NULL;
    char* new_str = NULL;

    // 解析规则，例如 "s/old/new/"
    if (parse_replace_command(rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    if (!old_str || !new_str) {
        fprintf(stderr, "Error: Failed to parse old/new strings from rules\n");
        free(old_str);
        free(new_str);
        return 1;
    }

    // 复制原始字符串，因为我们可能会修改它（避免修改输入参数）
    char line[1024];
    strncpy(line, str, sizeof(line) - 1);
    line[sizeof(line) - 1] = '\0';  // 确保终止

    // 执行替换：在 line 中把 old_str 替换为 new_str（第一次出现）
    replace_first_occurrence(line, old_str, new_str);

    // 输出结果（建议加上换行，除非 str 本身带了）
    printf("%s\n", line);

    // 释放动态分配的内存
    free(old_str);
    free(new_str);

    return 0;
}