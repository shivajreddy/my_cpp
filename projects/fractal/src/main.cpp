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

    auto program_start_time = std::chrono::system_clock().now();

    int fps_counter = 0; // Counts frames within current second
    int current_fps = 0; // Stores the calculated FPS to display
    std::chrono::time_point last_time = std::chrono::system_clock().now();

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Increment fram counter
        fps_counter++;

        // Get current time
        auto current_time = std::chrono::system_clock().now();

        // Calcuate elapsed time since last update
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                           current_time - last_time)
                           .count();

        // One second passed
        if (elapsed >= 1000) {
            current_fps = fps_counter; // Update FPS Value
            fps_counter = 0;           // Reset counter
            last_time = current_time;  // Reset time
        }

        // Display fps
        char fps_str[20];
        snprintf(fps_str, sizeof(fps_str), "FPS: %d /second", current_fps);
        DrawText(fps_str, 50, 400, 60, primary_color);

        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}
