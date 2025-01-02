#include "../lib/raylib/include/raylib.h"
#include "helpers.h"

#include <chrono>
#include <string>
#include <thread>

// Show a counter
void start_count_down(int *count_from)
{
    auto start_time = std::chrono::steady_clock::now();
    int elapsed_seconds = 0;

    while (*count_from > 0) {
        // Calculate elapsed time
        auto current_time = std::chrono::steady_clock::now();

        int new_elapsed_seconds =
            std::chrono::duration_cast<std::chrono::seconds>(current_time -
                                                             start_time)
                .count();

        // Ensure a full second has passed
        if (new_elapsed_seconds > elapsed_seconds) {
            elapsed_seconds = new_elapsed_seconds;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        (*count_from)--;
    }
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib");

    auto start_time = std::chrono::steady_clock::now();
    int elapsed_seconds = 0;

    int start_time_count = 10;
    int *ptr = &start_time_count;

    SetTargetFPS(540);           // Set our game to run at 60 frames-per-second
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLACK);

        *ptr += 1;

        // Calculate elapsed time
        auto current_time = std::chrono::steady_clock::now();

        int new_elapsed_seconds =
            std::chrono::duration_cast<std::chrono::seconds>(current_time -
                                                             start_time)
                .count();
        // Ensure a full second has passed
        if (new_elapsed_seconds > elapsed_seconds) {
            elapsed_seconds = new_elapsed_seconds;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // start_count_down(&start_time);
        std::string num_str = std::to_string(*ptr);
        auto str = num_str.c_str();

        // RLAPI void DrawText(const char *text, int posX, int posY, int
        // fontSize, Color color); // Draw text (using default font)
        DrawText(str, 40, 80, 20, hexToRaylibColor("FFDD33"));

        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}
