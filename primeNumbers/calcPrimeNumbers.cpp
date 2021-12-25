#include <iostream>
#include <vector>

extern "C"
{
  #include "isPrime.h"
}

const int MAX_NUMBER = 10000;

int main()
{
  std::vector<int> primeNumbers;
  int numberOfPrimes = 0;
  for(int i = 0; i < MAX_NUMBER; i++)
  {
    if(isPrime(i))
    {
      numberOfPrimes++;
      primeNumbers.push_back(i);
    }
  }
  std::cout << "There are " << numberOfPrimes << " prime numbers between 0 and " << MAX_NUMBER << ".\n";
  std::cout << "The prime numbers are: ";
  std::cout << "[";
  for(int i = 0; i < numberOfPrimes; i++)
  {
    if (i == numberOfPrimes - 1)
    {
      std::cout << primeNumbers[i];
    }
    else
    {
      std::cout << primeNumbers[i] << ", ";
    }
  }
  std::cout << "]\n";
}