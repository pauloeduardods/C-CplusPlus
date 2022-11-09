#include <stdio.h>
#include <math.h>

const int DEFAULT_NUM = 7;
int gDefaultCount = 0;
int gCount = 0;

int g(int x) {
  gCount++;
  if (x == DEFAULT_NUM) {
    gDefaultCount++;
  }
  if (x == 0) {
    return 2; 
  }
  if (1 <= x && x <= 2) {
    return pow(x, 2);
  }
  if (2 < x && x <= 5) {
    return x * g(x - 1);
  }
  if (x > 5) {
    return g(x - 3) + g(x - 2);
  }
}

int main() {
  int x;
  printf("Fale o numero de x:\n\n");
  scanf("%d", &x);
  int result = g(x);
  printf("g(%d) = %d \n", x, result);
  printf("g foi chamada %d vezes\n", gCount);
  printf("g(%d) foi chamada %d vezes", DEFAULT_NUM, gDefaultCount);
}