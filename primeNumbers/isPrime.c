#include <stdbool.h>
#include "isPrime.h"

bool isPrime(int number)
{
  int numOfDivisors = 0;
  for (int i = 1; i < number; i++)
  {
    if (number % i == 0)
    {
      numOfDivisors++;
    }
  }
  if (numOfDivisors == 2)
  {
    return true;
  } else {
    return false;
  } 
}