#include <iostream>
#include <cstring>
#include <thread>
#include <vector>
#include <sstream>
#include <algorithm>
#include <atomic>
#include <openssl/sha.h>
#include <iomanip>
#include <chrono>

std::atomic<bool> stopProcess{false};
std::atomic<int> nonce{0};

std::string sha256(std::string stringToHash)
{
  unsigned char hash[SHA256_DIGEST_LENGTH];

  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, stringToHash.c_str(), stringToHash.size());
  SHA256_Final(hash, &sha256);

  std::stringstream ss;

  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
  }
  return ss.str();
};

void nonceCalculator(std::string string, int difficulty, int* nonceResult)
{
  while (!stopProcess.load())
  {
    int curNonce = nonce.load();
    std::string hash = sha256(string + std::to_string(curNonce));
    if (hash.substr(0, difficulty) == std::string(difficulty, '0'))
    {
      stopProcess.store(true);
      *nonceResult = curNonce;
    }
    nonce++;
  }
};

int nonceCalculatorWThreads(std::string string, int numOfThreads, int difficulty)
{
  int nonceResult;
  std::thread threads[numOfThreads];
  for (int i = 0; i < numOfThreads; i++) {
    threads[i] = std::thread(nonceCalculator, string, difficulty, &nonceResult);
  }
  for (auto &th : threads) 
  {
    th.join();
  }
  return nonceResult;
};

void printHelpMessage(char **argv, int processor_count)
{
  using std::cout;
  cout << "Usage: " << argv[0] << " <command> [param] \n";
  cout << "Commands:\n";
  cout << "-s : String to Hash eg: [nonce-calc -s \"String to hash\"] REQUIRED\n";
  cout << "-d : Difficulty can be 1 to 32 Default: 6\n";
  cout << "-t : Num of threads [full or 1 to " << processor_count << "] Default: full\n";
  cout << "-e : This will ONLY hash your string (No params) [\"-d\" and \"-t\" will not work]\n";
  cout << "-n : Nonce, it only works with \"-e\" command\n";
  cout << "-h : Print this message\n";
}

int main(int argc, char **argv)
{
  using std::cout;
  const auto processor_count = std::thread::hardware_concurrency();
  
  std::string stringToHash;
  unsigned int difficulty = 6, numOfThreads = processor_count, nonceResult = 0;
  bool onlyHash = false, withNonce = false;

  std::vector<std::string> args = {"-s", "-d", "-t", "-e", "-n", "-h"};
  for (int i = 1; i < argc; i += 2)
  {
    if (std::find(args.begin(), args.end(), argv[i]) != args.end() && std::strcmp(argv[i], "-h") != 0)
    {
      if (std::strcmp(argv[i], "-s") == 0)
      {
        stringToHash = argv[i + 1];
      }
      else if (std::strcmp(argv[i], "-d") == 0)
      {
        int newDifficulty;
        std::stringstream number(argv[i + 1]);
        number >> newDifficulty;
        if (newDifficulty > 0 && newDifficulty <= 32)
        {
          difficulty = newDifficulty;
        }
        else
        {
          cout << "\n\nDifficulty out of range [0-32]\n\n";
          return 1;
        }
      }
      else if (std::strcmp(argv[i], "-t") == 0)
      {
        if (std::strcmp(argv[i + 1], "full") == 0)
        {
          numOfThreads = processor_count;
        }
        else
        {
          int newThreadNum;
          std::stringstream number(argv[i + 1]);
          number >> newThreadNum;
          if (newThreadNum > 0 && newThreadNum <= processor_count)
          {
            numOfThreads = newThreadNum;
          }
          else
          {
            cout << "\n\nThreads out of range [1-" << processor_count << "]\n\n";
            return 1;
          }
        }
      }
      else if (std::strcmp(argv[i], "-e") == 0)
      {
        onlyHash = true;
        i--;
      }
      else if (std::strcmp(argv[i], "-n") == 0)
      {
        std::stringstream number(argv[i + 1]);
        number >> nonceResult;
        withNonce = true;
      }
    } else {
      printHelpMessage(argv, processor_count);
      return 1;
    }
  }

  cout << "String: \"" << stringToHash << "\"\n";
  if (onlyHash)
  {
    std::string hash;
    if (!withNonce)
    {
      hash = sha256(stringToHash);
    }
    else
    {
      hash = sha256(stringToHash + std::to_string(nonceResult));
      cout << "Nonce: " << nonceResult << "\n";
      cout << "Full string: \"" << stringToHash + std::to_string(nonceResult) << "\"\n";
    }
    cout << "Hash result: \"" << hash << "\"\n";
    return 0;
  }
  cout << "Difficulty: " << difficulty << "\n";
  cout << "Num of Threads: " << numOfThreads << "\n";
  cout << "\n\Calculating...\n\n\n";

  auto t1 = std::chrono::high_resolution_clock::now();
  nonceResult = nonceCalculatorWThreads(stringToHash, numOfThreads, difficulty);
  auto t2 = std::chrono::high_resolution_clock::now();
  auto execTime = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1);
  std::string hash = sha256(stringToHash + std::to_string(nonceResult));
  cout << "Nonce: " << nonceResult << "\n";
  cout << "Full string: \"" << stringToHash + std::to_string(nonceResult) << "\"\n";
  cout << "Hash result: \"" << hash << "\"\n";
  cout << "Exec Time: " << execTime.count() << "s\n";
  return 0;
};