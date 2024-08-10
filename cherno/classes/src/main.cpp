#include <iostream>
#include <vector>

#include "solution.cpp"

int main() {
  Solution sol;
  {
    std::vector<int> coins = {1, 2, 5};
    int amount = 11;
    int answer = 3;
    std::cout << answer << " | " << sol.coinChange(coins, amount) << std::endl;
  }
  {
    std::vector<int> coins = {1, 2, 5};
    int amount = 0;
    int answer = 0;
    std::cout << answer << " | " << sol.coinChange(coins, amount) << std::endl;
  }
  {
    std::vector<int> coins = {2, 5};
    int amount = 1;
    int answer = -1;
    std::cout << answer << " | " << sol.coinChange(coins, amount) << std::endl;
  }

  return 0;
}
