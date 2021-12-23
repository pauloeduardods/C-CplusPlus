#include <iostream>
#include <time.h>
#include <vector>
#include <string>

#define MAX_CARD_NUMBER 11;
#define MIN_CARD_NUMBER 1;

void getCarts(int numOfCards, std::vector<int> *playerCards)
{
  for (int i = 0; i < numOfCards; i++)
  {
    int randomNumber = rand() % MAX_CARD_NUMBER + MIN_CARD_NUMBER;
    playerCards->push_back(randomNumber);
  }
}

int play(int *money, std::vector<int> *player1Cards, std::vector<int> *player2Cards)
{
  using namespace std;
  int bet;

  cout << "How much would you like to bet?" << endl;
  cout << "Plase say a number between $1 and $" << *money << endl;
  cin >> bet;
  
  if (bet > *money)
  {
    cout << "You don't have enough money" << endl;
    cout << "Please try again" << endl;
    play(money, player1Cards, player2Cards);
  }
  else 
  {
    getCarts(2, player1Cards);
    getCarts(2, player2Cards);
    while (true)
    {
      cout << "Your cards are: " << endl;
      int total = 0;
      for (int i = 0; i < player1Cards->size(); i++)
      {
        cout << player1Cards->at(i) << endl;
        total += player1Cards->at(i);
      }
      cout << "Your total is: " << total << endl;
      string answer;
      cout << "Would you like to hit or stay?" << endl;
      cout << "Hit type something stay press enter" << endl;
      cin >> answer;
      if (answer.size() == 0) break;
      getCarts(1, player1Cards);
    }
  }
  return 0;
}

int main() 
{
  std::vector<int> player1Cards, player2Cards;
  int money=100;
  int randNum1, randNum2;

  srand(time(NULL));

  std::cout << "Welcome to Blackjack!" << std::endl;
  std::cout << "You have $" << money << "to play with." << std::endl;
  
  

  while (true)
  {
    player1Cards.clear();
    player2Cards.clear();
    play(&money, &player1Cards, &player2Cards);
    break;
  }
  
  return 0;
}

