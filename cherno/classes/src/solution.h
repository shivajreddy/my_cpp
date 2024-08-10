#include <algorithm>
#include <limits>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  int coinChange(std::vector<int> &coins, int amount);

 private:
  int rec(int amount, const std::vector<int> &coins,
          std::unordered_map<int, int> &cache);
};
