#include <iostream>
#include <time.h>
#include <vector>
#include <string>

#define START_MONEY 100;
#define MAX_CARD_NUMBER 11;
#define MIN_CARD_NUMBER 1;
#define MAX_CARD_VALUE 21;
#define NUM_START_CARDS 2;

int max_card_value = MAX_CARD_VALUE;
int num_start_cards = NUM_START_CARDS;
int max_card_number = MAX_CARD_NUMBER;
int min_card_number = MIN_CARD_NUMBER;
void getCarts(int numOfCards, std::vector<int> *playerCards)
{
  for (int i = 0; i < numOfCards; i++)
  {
    int randomNumber = rand() % max_card_number + min_card_number;
    playerCards->push_back(randomNumber);
  }
}

int getSum(std::vector<int> *playerCards)
{
  int sum = 0;
  for (int i = 0; i < playerCards->size(); i++)
  {
    sum += playerCards->at(i);
  }
  return sum;
}

bool aiPlay(std::vector<int> *playerCards, std::vector<int> *aiCards)
{
  int aiSum = getSum(aiCards);
  int playerSum = getSum(playerCards);
  if (playerSum > aiSum && playerSum <= max_card_value)
  {
    return true;
  }
  else if (aiSum >= max_card_value)
  {
    return false;
  }
  else return false;
}

int play(int *money, std::vector<int> *player1Cards, std::vector<int> *player2Cards)
{
  using namespace std;
  int bet;
  int win;

  cout << "How much would you like to bet?" << endl;
  cout << "Plase say a number between $1 and $" << *money << endl;
  cin >> bet;
  
  if (bet > *money)
  {
    cout << "You don't have enough money" << endl;
    cout << "Please try again" << endl;
    play(money, player1Cards, player2Cards);
  }
  else if (bet <= 0)
  {
    cout << "You need to bet something" << endl;
    cout << "Please try again" << endl;
    play(money, player1Cards, player2Cards);
  }
  else 
  {
    getCarts(num_start_cards, player1Cards);
    getCarts(num_start_cards, player2Cards);
    string answer;
    while (true)
    {
      int total = getSum(player1Cards);
      if (total > max_card_value)
      {
        cout << "You busted" << endl;
        answer = "2";
      }
      if ((answer.size() == 0 || answer == "1") && total <= max_card_value)
      {
        total = 0;
        cout << "-------------------------------------" << endl;
        cout << "Your cards are: " << endl;
        cout << " | ";
        for (int i = 0; i < player1Cards->size(); i++)
        {
          cout << player1Cards->at(i) << " | ";
          total += player1Cards->at(i);
        }
        cout << "\nYour total is: " << total << endl;
        cout << "-------------------------------------" << endl;
        cout << "Would you like to hit or stay?" << endl;
        cout << "1: HIT \t 2: STAY" << endl;
        cin >> answer;
      }
      if (answer == "1")
      {
        getCarts(1, player1Cards);
      }
      bool aiWillPlay = aiPlay(player1Cards, player2Cards);
      if (aiWillPlay)
      {
        cout << "The AI will play" << endl;
        getCarts(1, player2Cards);
      }
      if (!aiWillPlay && answer == "2")
      {
        int aiTotal = getSum(player2Cards);
        int playerTotal = getSum(player1Cards);
        cout << "-------------------------------------" << endl;
        cout << "The AI's cards are: " << endl;
        cout << " | ";
        for (int i = 0; i < player2Cards->size(); i++)
        {
          cout << player2Cards->at(i) << " | ";
        }
        cout << "\nThe AI's total is: " << aiTotal << endl;
        cout << "-------------------------------------" << endl;
        cout << "Your cards are: " << endl;
        cout << " | ";
        for (int i = 0; i < player1Cards->size(); i++)
        {
          cout << player1Cards->at(i) << " | ";
        }
        cout << "\nYour total is: " << playerTotal << endl;
        cout << "-------------------------------------" << endl;
        if ((playerTotal > aiTotal && playerTotal <= max_card_value) || (playerTotal < aiTotal && aiTotal >= max_card_value))
        {
          cout << "+--------+" << endl;
          cout << "|You win!|" << endl;
          cout << "+--------+" << endl;
          *money += bet;
          win = 1;
        }
        else if ((playerTotal < aiTotal && aiTotal <= max_card_value) || (playerTotal > aiTotal && playerTotal >= max_card_value))
        {
          cout << "+---------+" << endl;
          cout << "|You lose!|" << endl;
          cout << "+---------+" << endl;
          *money -= bet;
          win = 0;
        }
        else
        {
          cout << "+-----------+" << endl;
          cout << "|It's a tie!|" << endl;
          cout << "+-----------+" << endl;
          win = 2;
        }
        break;
      }
    }
  }
  return win;
}

int main() 
{
  std::vector<int> player1Cards, player2Cards;
  int wins = 0, draws = 0, losses = 0, money = START_MONEY;

  srand(time(NULL));

  std::cout << "Welcome to Blackjack!" << std::endl;
  
  while (true)
  {
    player1Cards.clear();
    player2Cards.clear();
    std::cout << "You have $" << money << "to play with." << std::endl;
    int win = play(&money, &player1Cards, &player2Cards);
    if (win == 1)
    {
      wins++;
    }
    else if (win == 0)
    {
      losses++;
    }
    else draws ++;
    std::cout << "Wins: " << wins << std::endl;
    std::cout << "Losses: " << losses << std::endl;
    std::cout << "Draws: " << draws << std::endl;
    std::cout << "Money: " << money << std::endl;
    if (money <= 0)
    {
      std::cout << "You are out of money" << std::endl;
      break;
    }
    else std::cout << "Would you like to play again? (y/n)" << std::endl;
    char answer;
    std::cin >> answer;
    if (answer == 'n')
    {
      std::cout << "Thanks for playing!" << std::endl;
      std::cout << "You leave with $" << money << std::endl;
      break;
    }
  }
  return 0;
}