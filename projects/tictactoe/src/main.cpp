#include <raylib.h>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <system_error>
#include <thread>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define SCREEN_TITLE "TIC-TAC-TOE"
#define ROWS 3
#define COLS 3

class Board {};

enum class Player { Player_X, Player_O };

class Game {
  bool started;
  Player current_player;
};

enum class TileState { Empty, Player_X, Player_O };

class Tile {
 public:
  int id;
  int position_x;
  int position_y;
  TileState tile_state;

  static constexpr int width = 200;
  static constexpr int height = 200;
  Color tile_color = Color{136, 57, 239, 255};
  Color border_color = WHITE;

  // Default Constructor
  Tile() = default;

  Tile(int id, int x = 0, int y = 0, TileState tile_state = TileState::Empty)
      : id(id), position_x(x), position_y(y), tile_state(tile_state) {

    DrawRectangle(position_x, position_y, width, height, tile_color);
    for (int i = 0; i < 1; i++) {
      DrawRectangleLines(position_x - i, position_y - i, width + 2 * i,
                         height + 2 * i, border_color);
    }
  }

  void change_color(Player player) {
    if (player == Player::Player_O) {
      tile_color = RED;
      DrawRectangle(position_x, position_y, width, height, tile_color);
      for (int i = 0; i < 1; i++) {
        DrawRectangleLines(position_x - i, position_y - i, width + 2 * i,
                           height + 2 * i, border_color);
      }
    } else {
      tile_color = PINK;
      DrawRectangle(position_x, position_y, width, height, tile_color);
      for (int i = 0; i < 1; i++) {
        DrawRectangleLines(position_x - i, position_y - i, width + 2 * i,
                           height + 2 * i, border_color);
      }
    }
  }
};

// Draw's Tiles on the screen
class Grid {

 public:
  Tile tiles[9] = {};

  // Create Grid
  Grid() {
    // Array to hold 9 tiles

    int pos_x = 0, pos_y = 0;
    for (int i = 0; i < 9; i++) {
      // std::cout << "pos_x" << ":" << pos_y << std::endl;
      tiles[i] = {i, pos_x, pos_y, TileState::Empty};
      pos_x = (Tile::Tile::width + pos_x) % (Tile::width * 3);
      pos_y = ((i + 1) / 3) * Tile::height;
    };
  }
};

int find_tile_id(Vector2 mouse_position) {
  int x = mouse_position.x;
  int y = mouse_position.y;

  if (x > ROWS * Tile::width || y > COLS * Tile::height) {
    return -1;
  }

  int row_id = y / Tile::height;
  int col_id = x / Tile::width;
  return (row_id * ROWS) + col_id;
}

int main() {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

  ClearBackground(BLACK);
  Grid grid = Grid{};
  Player current_player = Player::Player_X;

  SetTargetFPS(60);
  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    BeginDrawing();

    auto mouse_position = GetMousePosition();

    DrawText(TextFormat("Mouse Position: (%.0f, %.0f)", mouse_position.x,
                        mouse_position.y),
             SCREEN_WIDTH - 400, SCREEN_HEIGHT - 30, 30, DARKGRAY);

    // Create Grid

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      system("clear");
      std::cout << mouse_position.x << ":" << mouse_position.y << std::endl;
      int tile_id = find_tile_id(mouse_position);
      std::cout << tile_id << std::endl;

      if (tile_id != -1) {
        auto tile = grid.tiles[tile_id];
        tile.change_color(current_player);
        if (current_player == Player::Player_X) {
          current_player = Player::Player_O;
        } else {
          current_player = Player::Player_X;
        }
      }
    }

    EndDrawing();
  }

  CloseWindow();  // Close window and OpenGL context

  return 0;
}
