# C-CplusPlus

Relearning C and C++

## Como compilar e rodar o bitcoinMiningNonceCalc.cpp

### Ubuntu

1. Instalar a biblioteca OpenSSL `sudo apt install libssl-dev`

2. Compilar o código `g++ bitcoinMiningNonceCalc.cpp -o bitcoin.out -lcrypto`

3. Rodar o programa `./bitcoin.out`

### Macos

1. Instalar a biblioteca OpenSSL `brew install openssl`

2. Compilar o código `g++ bitcoinMiningNonceCalc.cpp -I /opt/homebrew/opt/openssl/include -L /opt/homebrew/opt/openssl/lib -lcrypto -o bitcoin.out`

3. Rodar o programa `./bitcoin.out`

OBS: Caso seu openssl tenha sido instalado em outro diretorio aponte o caminho corretamente.

## multiThreadNonceCalc.cpp

### Compilar

#### Ubuntu

1. Instalar a biblioteca OpenSSL `sudo apt install libssl-dev`

2. Compilar o código `g++ multiThreadNonceCalc.cpp -o nonce-calc.out -lcrypto -pthread`

#### Macos

1. Instalar a biblioteca OpenSSL `brew install openssl`

2. Compilar o código `g++ -std=c++11 multiThreadNonceCalc.cpp -o nonce-calc.out -I /opt/homebrew/opt/openssl/include -L /opt/homebrew/opt/openssl/lib -pthread -lcrypto`

### Como utilizar

Para conseguir ver todos os comandos disponíveis para o programa, digite `./nonce-calc.out -h`

"-s" String que será utilizada para gerar o hash
"-d" Dificuldade do problema [numeros de "0" na frente do hash(default: 6)]
"-t" Número de threads (default: full)
"-e" Apenas fazer o hash da string, sem fazer o cálculo do nonce [Sem parametro]
"-n" Nonce inicial, para conferir resultado ou testar outros nonces manualmente [Apenas funciona com o comando "-e"]
"-h" Mostrar mensagem de ajuda

## Como compilar e rodar o primeNumbers

### Ubuntu && Macos

1. Entrar no diretorio `cd primeNumbers`

2. Compilar o código `make all`

3. Rodar o programa `./calcPrimes.out`

## Como compilar e rodar o multiThreadTest

### Ubuntu

1. Compilar o arquivo multiThreadTest.cpp `g++ multiThreadTest.cpp -o multiThreadTest.out -pthread`

2. Rodar o arquivo `./multiThreadTest.out`

## Como compilar e rodar o gFunc

### Ubuntu && Macos

1. Compular o código `gcc -o output.o gFunc.c`

2. Rodar o programa `./output.o`
