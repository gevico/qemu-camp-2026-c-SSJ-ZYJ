#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    const char* old_start;
    const char* old_end;
    const char* new_start;
    const char* new_end;
    size_t old_len;
    size_t new_len;

    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }

    old_start = cmd + 2;
    old_end = strchr(old_start, '/');
    if (old_end == NULL) {
        return -1;
    }

    new_start = old_end + 1;
    new_end = strchr(new_start, '/');
    if (new_end == NULL || *(new_end + 1) != '\0') {
        return -1;
    }

    old_len = (size_t)(old_end - old_start);
    new_len = (size_t)(new_end - new_start);

    *old_str = (char*)malloc(old_len + 1);
    *new_str = (char*)malloc(new_len + 1);
    if (*old_str == NULL || *new_str == NULL) {
        free(*old_str);
        free(*new_str);
        *old_str = NULL;
        *new_str = NULL;
        return -1;
    }

    memcpy(*old_str, old_start, old_len);
    (*old_str)[old_len] = '\0';
    memcpy(*new_str, new_start, new_len);
    (*new_str)[new_len] = '\0';

    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new_text) {
    char* pos;
    char temp[MAX_LINE_LENGTH];
    size_t prefix_len;
    size_t old_len;

    if (str == NULL || old == NULL || new_text == NULL || old[0] == '\0') {
        return;
    }

    pos = strstr(str, old);
    if (pos == NULL) {
        return;
    }

    prefix_len = (size_t)(pos - str);
    old_len = strlen(old);

    snprintf(temp, sizeof(temp), "%.*s%s%s", (int)prefix_len, str, new_text, pos + old_len);
    strncpy(str, temp, MAX_LINE_LENGTH - 1);
    str[MAX_LINE_LENGTH - 1] = '\0';
}

int main(int argc, char* argv[]) {
    const char* replace_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;

    if (parse_replace_command(replace_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
