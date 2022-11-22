#include <stdio.h>

int main() {
  int a, b, *c;
  a = 2;
  b = 3;
  printf("A: %d, &A: %p, B: %d, &B: %p, C: %d, &C: %p \n", a, &a, b, &b, *c, c);
  c = &a;
  printf("A: %d, &A: %p, B: %d, &B: %p, C: %d, &C: %p \n", a, &a, b, &b, *c, c);
  c = &b;
  printf("A: %d, &A: %p, B: %d, &B: %p, C: %d, &C: %p \n", a, &a, b, &b, *c, c);
}