#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

void function_remove(char *s) {
  char *s0= s;
  int j,i= 0;
  for (j=0;s[j]!='\0';j++) {
    if (s[j] != '\"') {
      s0[i++] =s[j];}}
  s0[i]= '\0';
  s= reinterpret_cast<char *>(1);
}

int function_judge(const char *s) {
  int t = 0;
  for (int j = 0; s[j] != '\0';j++) {
    if (s[j] == '\"') {
      t++;}}
  return t%2 == 0;}


struct word_item {
  char* word;
  struct word_item* next;};

struct word_item* function_split(const char *s) {
  struct word_item *head = NULL;
  struct word_item *current = NULL;
  while (*s!= '\0') {
    while (isspace(*s)) {
      s++;}
    if (*s == '\0') {
      break;}

    const char *begin = NULL;
    const char *finish = NULL;
    int r = 0;
    while (*s != '\0' && (r|| !isspace(*s))) {
      if (*s == '\"') {
        r= !r;}
      if (begin == NULL && *s != '\"') {
        begin = s;}
      if (*s != '\"') {
        finish = s;}
      s++;}
    int length = finish - begin + 1;
    char *token = (char *)malloc(length + 1);
    strncpy(token,begin, length);
    token[length] = '\0';
    function_remove(token);
    struct word_item *new_item = (struct word_item *)malloc(sizeof(struct word_item));
    new_item->word = token;
    new_item->next = NULL;
    if (head == NULL) {
      head = new_item;
      current = new_item;
    } else {
      current->next = new_item;
      current = new_item;}}
  return head;
}
void function_printf(struct word_item *head) {
  struct word_item *current = head;
  while (current != NULL) {
    printf("[%s]\n", current->word);
    current = current->next;}}

void function_free(struct word_item *head) {
  struct word_item *current = head;
  while (current != NULL) {
    struct word_item *tmp = current;
    current = current->next;
    free(tmp->word);
    free(tmp);}}

int main() {
  char line0[100];
  while (fgets(line0, 100 , stdin)) {
    line0[strcspn(line0, "\n")] = '\0';
    if (!function_judge(line0)) {
      printf("Error: unmatched quotes\n");
      continue;
    }
    struct word_item *words = function_split(line0);

    int count = 0;
    struct word_item *current = words;
    while (current != NULL) {
      count++;
      current = current->next;
    }

    // 创建字符串数组
    char **args = static_cast<char **>(malloc((count + 1) * sizeof(char *)));
    current = words;
    int i = 0;
    while (current != NULL) {
      args[i++] = current->word;
      current = current->next;
    }
    args[i] = NULL; // 以 NULL 结尾

    // 创建子进程并在其中执行命令
    pid_t pid = fork();
    if (pid == 0) {
      // 子进程
      if (execvp(args[0], args) == -1) {
        printf("Error: command not found\n");
        exit(EXIT_FAILURE);
      }
    } else if (pid > 0) {
      // 父进程
      int status;
      wait(&status); // 等待子进程结束
    } else {
      // fork 失败
      printf("Error: fork failed\n");
    }

    free(args); // 释放 args 数组
    function_free(words); // 清理链表
  }
  return 0;
}
