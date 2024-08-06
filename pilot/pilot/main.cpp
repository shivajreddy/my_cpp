#include <iostream>

using namespace std;

class Player {
 public:
  int x, y;
  int speed;
};

void Move(Player& player, int x, int y) {
  player.x += x * player.speed;
  player.y += y * player.speed;
}

int main() {
  Player player;
  player.x = 5;

  cout << "hi" << endl;
  cout << "hi" << endl;
  cout << "hi" << endl;

  // cout << player << endl;
}
