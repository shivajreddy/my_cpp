#include "coin_change.h"

#include <iostream>
#include <unordered_map>
#include <vector>

using std::cout, std::string, std::vector, std::unordered_map;

int rec(int amount, vector<int> &coins, unordered_map<int, int> &cache);

int Solution::coinChage(vector<int> &coins, int amount) {
  cout << "Running solution" << "\n ";
  unordered_map<int, int> cache;
  rec(amount, coins, cache);
  return -1;
}

int rec(int amount, vector<int> &coins, unordered_map<int, int> &cache) {
  cout << "finding " << amount << "\n";
  return -1;
}