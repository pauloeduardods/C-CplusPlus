# My first makefile
 
all: calcPrimes.out clean
 
calcPrimes.out: isPrime.o calcPrimeNumbers.o
	g++ -o calcPrimes.out calcPrimeNumbers.o isPrime.o
 
isPrime.o: isPrime.c isPrime.h
	gcc -c -o isPrime.o isPrime.c
 
calcPrimeNumbers.o: calcPrimeNumbers.cpp
	g++ -c -o calcPrimeNumbers.o calcPrimeNumbers.cpp
 
clean:
	rm -rf *.o *~ calcPrime.out