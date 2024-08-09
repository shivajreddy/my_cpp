#include <iostream>
using std::cout;

#include <vector>
using std::vector;

#include "coin_change.h"

int main() {
  cout << "Problem: Coin Change \n";

  Solution solution;

  {
    cout << "\n";
    vector<int> coins = vector<int>{1, 2, 5};
    int amount = 11;
    int answer = 3;
    cout << solution.coinChage(coins, amount) << " | " << answer << std::endl;
  }
  {
    cout << "\n";
    vector<int> coins = vector<int>{2, 5};
    int amount = 1;
    int answer = 0;
    cout << solution.coinChage(coins, amount) << " | " << answer << std::endl;
  }
}
