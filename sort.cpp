#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000 // 最大行数
#define MAX_LINE_LENGTH 1024 // 每行的最大长度

int compare(const void *a, const void *b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int main() {
    printf("sort starting\n");
    char *lines[MAX_LINES];
    char buffer[MAX_LINE_LENGTH];
    int line_count = 0;

    // 读取标准输入的每一行
    while (fgets(buffer, MAX_LINE_LENGTH, stdin) && line_count < MAX_LINES) {
        lines[line_count] = strdup(buffer); // 复制行内容
        line_count++;
    }

    // 使用 qsort 对行进行排序
    qsort(lines, line_count, sizeof(char*), compare);

    // 输出排序后的行
    for (int i = 0; i < line_count; i++) {
        printf("%s", lines[i]);
        free(lines[i]); // 释放内存
    }

    return 0;
}
