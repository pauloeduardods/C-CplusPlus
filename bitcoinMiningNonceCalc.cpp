#include <iostream>
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>

std::string sha256(const std::string str)
{
  unsigned char hash[SHA256_DIGEST_LENGTH];

  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, str.c_str(), str.size());
  SHA256_Final(hash, &sha256);

  std::stringstream ss;

  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
  }
  return ss.str();
}

int main()
{
  int nonce = 0, difficulty = 5;
  std::string stringToHash = "stringToHash";
  while (true)
  {
    std::string newString = stringToHash + std::to_string(nonce);
    std::string hash = sha256(newString);
    if (hash.substr(0, difficulty) == std::string(difficulty, '0'))
    {
      std::cout << "String: " << stringToHash << std::endl;
      std::cout << "Hash: " << hash << std::endl;
      std::cout << "Nonce: " << nonce << std::endl;
      break;
    }
    nonce++;
  }
  return 0;
}