#include <stdio.h>
#include "memalloc_j/memalloc_j.h"

int main() {
  printf("Hello memalloc_j\n");
  int *numbers = (int*)malloc_j(sizeof(int));
  numbers[0] = 42;
  printf("%d: %d\n", numbers, *numbers);
  free_j(numbers);

  return 0;
}
