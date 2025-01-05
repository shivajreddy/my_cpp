// #include "../lib/raylib/include/raylib.h"
#include <raylib.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define SCREEN_TITLE "APP"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    SetTargetFPS(60);
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Hello World!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}
