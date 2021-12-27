#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

const int MAX_NUMBER = 100000;
std::atomic<bool> stopProcess{false};

void print(int n, const std::string &str)
{
	std::string msg = std::to_string(n) + " : " + str;
	std::cout << msg << std::endl;
}

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
	}
	else
	{
		return false;
	}
}

int isPrimeLoop(int start_Number, int end_Number)
{
	std::vector<int> primeNumbers;
	int numberOfPrimes = 0;
	for (int i = start_Number; i < end_Number; i++)
	{
		if (stopProcess.load())
		{
			break;
		}
		if (isPrime(i))
		{
			numberOfPrimes++;
			primeNumbers.push_back(i);
		}
	}
	if (stopProcess.load()) return 0;
	std::cout << "There are " << numberOfPrimes << " prime numbers between " <<  start_Number << " and " << end_Number << ".\n";
	std::cout << "The prime numbers are: ";
	std::cout << "[";
	for (int i = 0; i < numberOfPrimes; i++)
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
	stopProcess.store(true);
	std::cout << "]\n";
	return 0;
}

int main()
{
	const auto processor_count = std::thread::hardware_concurrency();

	std::thread threads[processor_count];
	std::cout << threads[0].joinable() << std::endl;
	for (int i = 0; i < processor_count; i++)
	{
		threads[i] = std::thread(isPrimeLoop, i * MAX_NUMBER, (i + 1) * MAX_NUMBER);
	}
	std::cout << threads[0].joinable() << std::endl;
	for (auto &th : threads)
	{
		th.join();
	}
	std::cout << threads[0].joinable() << std::endl;
	std::cout << "Done" << std::endl;
	std::cout << stopProcess << std::endl;

	return 0;
}
