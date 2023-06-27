#include <stdio.h>
#include <unistd.h>

void test() {
  printf("Test!");
}

int main() {
  int a[3] = {1, 2, 3};
  for(int i = 0; i < 3; ++i) {
    printf("%d, ", a[i]);
  }

  test();

  write(1, "Hello World\n", 12);
  printf("%d + %d = %d\n", 1, 1, 1 + 1);
}