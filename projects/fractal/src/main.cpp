#include "../lib/raylib/include/raylib.h"
#include "helpers.h"

#include <chrono>
#include <ctime>
#include <string>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define SCREEN_TITLE "FRACTALS"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    auto primary_color = hexToRaylibColor("FFDD33");

    int counter = 0;
    // std::chrono::

    // Set program start time
    std::chrono::time_point program_start_time =
        std::chrono::system_clock().now();

    SetTargetFPS(540);           // Set our game to run at 60 frames-per-second
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw FPS
        counter += 1;
        int fps;

        auto current_time = std::chrono::system_clock().now();

        std::chrono::duration duration = current_time - program_start_time;

        auto time_elapsed_in_seconds =
            std::chrono::duration_cast<std::chrono::seconds>(duration).count();

        char fps_str[20];
        snprintf(fps_str, sizeof(fps_str), "FPS: %zu", time_elapsed_in_seconds);

        // Check if 1 sec has passed
        // if () {
        // Update fps
        // snprintf(fps_str, sizeof(fps_str), "%d", counter);
        // }

        // Draw FPS
        DrawText(fps_str, SCREEN_WIDTH - 500, 80, 60, primary_color);

        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}
