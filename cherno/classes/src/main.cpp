#include <iostream>
using std::cout;

#include <vector>
using std::vector;

#include "coin_change.h"

int main() {
  Solution solution;

  {
    vector<int> coins = vector<int>{1, 2, 5};
    int amount = 11;
    int answer = 3;
    cout << answer << " | " << solution.coinChage(coins, amount) << std::endl;
  }
  {
    vector<int> coins = vector<int>{2};
    int amount = 3;
    int answer = -1;
    cout << answer << " | " << solution.coinChage(coins, amount) << std::endl;
  }
  {
    vector<int> coins = vector<int>{1};
    int amount = 0;
    int answer = 0;
    cout << answer << " | " << solution.coinChage(coins, amount) << std::endl;
  }
}
