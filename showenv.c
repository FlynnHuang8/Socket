#include "findenv.h"
int main() {
  char *s = findEnv("foo");
  printf("%s\n", s);

  return 0;
}
