#include <stdio.h>
#include <unistd.h>

int main()
{
  unsigned long long int n = 1, lastValuenN = 1;
  long int x = 1, lastValuenX = x;
  int y = 1, lastValuenY = y;
  int count = 0, countx = 0, county = 0;

  for (n; ; n *= 2)
  {
    if (n != 0)
    {
      lastValuenN = n;
      count++;
    }
    if (x != 0)
    {
      lastValuenX = x;
      countx++;
    }
    if (y != 0)
    {
      lastValuenY = y;
      county++;
    }
    if (x == 0 && y == 0 && n == 0)
    {
      printf("unsigned long int %i %llu\n", count, lastValuenN);
      printf("long int %i %lu\n", countx, lastValuenX);
      printf("int %i %u\n", county, lastValuenY);
      break;
    }
    x *= 2;
    y *= 2;
  };
};