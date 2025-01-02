#include "helpers.h"
#include <sstream>

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
