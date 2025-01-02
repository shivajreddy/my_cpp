#include "../lib/raylib/include/raylib.h"
#include <sstream>
#include <stdexcept>
#include <string>

// Convert a hex color string to Raylib Color
Color hexToRaylibColor(const std::string &hexColor)
{
    // Remove '#' if present
    std::string hex = (hexColor[0] == '#') ? hexColor.substr(1) : hexColor;

    // Validate hex string length
    if (hex.length() != 6 && hex.length() != 8) {
        throw std::invalid_argument(
            "Invalid hex color. Must be #RRGGBB or #RRGGBBAA");
    }

    // If 6-digit hex, add full opacity
    if (hex.length() == 6) {
        hex += "FF";
    }

    // Convert hex to integer values
    unsigned int rgba;
    std::stringstream ss;
    ss << std::hex << hex;
    ss >> rgba;

    // Extract color components
    unsigned char r = (rgba >> 24) & 0xFF;
    unsigned char g = (rgba >> 16) & 0xFF;
    unsigned char b = (rgba >> 8) & 0xFF;
    unsigned char a = rgba & 0xFF;

    // Return Raylib Color
    return Color { r, g, b, a };
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib");

    SetTargetFPS(60);            // Set our game to run at 60 frames-per-second
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLACK);

        int current_pos_x = 0, current_pos_y = 0;

        DrawText("Array visual lets go c++!", current_pos_x, current_pos_y, 20,
                 hexToRaylibColor("FFDD33"));
        current_pos_y += 20;

        int total_boxes = 10;

        // Create Boxes
        const int REC_WIDTH = 50, REC_HEIGHT = 50; // Box-Size
        int x = current_pos_x, y = current_pos_y;  // Box-Postion
        int box_padding = 10;

        for (int i = 0; i < total_boxes; i++) {
            // Rectangle
            DrawRectangle(x, y, REC_WIDTH, REC_HEIGHT, PURPLE);
            x += (REC_WIDTH + box_padding);
        }

        int padding = 10;

        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}
