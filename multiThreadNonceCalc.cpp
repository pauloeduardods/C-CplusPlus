#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <openssl/sha.h>
#include <iomanip>

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

int main() {
  int nonceResult;

  const auto processor_count = std::thread::hardware_concurrency();

  std::thread threads[processor_count];

  for (int i = 0; i < processor_count; i++) {
    threads[i] = std::thread(nonceCalculator, "teste", 6, &nonceResult);
  }

  for (auto &th : threads) {
    th.join();
  }

  std::cout << nonceResult << "\n";
}