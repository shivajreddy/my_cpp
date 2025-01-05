#include <raylib.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define SCREEN_TITLE "TIC-TAC-TOE"

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

  SetTargetFPS(60);
  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawText("Hello World!", 190, 200, 40, LIGHTGRAY);

    EndDrawing();
  }

  CloseWindow();  // Close window and OpenGL context

  return 0;
}
