#include <iomanip>
#include <iostream>
#include <vector>

#include "solution.h"

int main() {
  Solution sol;
  {
    std::vector<int> coins = {1, 2, 5};
    int amount = 11;
    int answer = 3;
    std::cout << std::setw(3) << answer << "  |  "
              << sol.coinChange(coins, amount) << "\n";
  }
  {
    std::vector<int> coins = {1, 2, 5};
    int amount = 0;
    int answer = 0;
    std::cout << std::setw(3) << answer << "  |  "
              << sol.coinChange(coins, amount) << "\n";
  }
  {
    std::vector<int> coins = {2, 5};
    int amount = 1;
    int answer = -1;
    std::cout << std::setw(3) << answer << "  |  "
              << sol.coinChange(coins, amount) << "\n";
  }

  return 0;
}
