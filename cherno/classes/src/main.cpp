#include <algorithm>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  int coinChange(std::vector<int> &coins, int amount) {
    if (amount == 0) return 0;

    std::unordered_map<int, int> cache;
    int result = rec(amount, coins, cache);
    if (result == std::numeric_limits<int>::max()) return -1;
    return result;
  }

 private:
  int rec(int amount, const std::vector<int> &coins,
          std::unordered_map<int, int> &cache) {
    if (amount == 0) return 0;
    if (amount < 0) return std::numeric_limits<int>::max();

    // Check if the result is already cached
    if (cache.find(amount) != cache.end()) return cache[amount];

    int min_coins = std::numeric_limits<int>::max();
    for (int coin : coins) {
      int remaining = rec(amount - coin, coins, cache);
      if (remaining != std::numeric_limits<int>::max()) {
        min_coins = std::min(min_coins, remaining + 1);
      }
    }

    // Cache the computed result
    cache[amount] = min_coins;
    return min_coins;
  }
};

int main() {
  Solution sol;
  std::vector<int> coins = {1, 2, 5};
  int amount = 11;
  std::cout << "Minimum coins needed: " << sol.coinChange(coins, amount)
            << std::endl;

  return 0;
}

