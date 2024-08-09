#include <iostream>
using std::cout;

#include <vector>
using std::vector;

#include "coin_change.h"

int main() {
  cout << "Problem: Coin Change \n";

  Solution solution;

  {
    vector<int> coins = vector<int>{1, 2, 5};
    cout << solution.coinChage(coins, 11) << std::endl;
  }

  {
    vector<int> coins = vector<int>{2, 5};
    cout << solution.coinChage(coins, 1) << std::endl;
  }
}
