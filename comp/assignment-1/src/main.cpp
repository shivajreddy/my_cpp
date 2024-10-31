#include <SFML/Config.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

#include <imgui/imgui.h>

// Assignment 01
int main(int argc, char *argv[]) {
    // create a new window of size w*h pixels top-left of the window is (0,0)
    // and bottom-right is (w,h) you will read  these from the config file
    const int wWidth = 1280;
    const int wHeight = 720;
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML works!");
    window.setFramerateLimit(60); // limit to 60 FPS

    // Initiazlie IMGUI and create a clock used for its internal timing
    ImGui::SFML::Init(window);
    sf::Clock deltaClock;

    // Scale the imgui ui and text size by 2
    ImGui::GetStyle().ScaleAllSizes(2.0f);
    ImGui::GetIO().FontGlobalScale = 2.0f;

    // The imgui color {r, g, b} wheel requires from 0f-1f instead of from 0-255
    float c[3] = {0.0f, 1.0f, 1.0f};

    // Let's make a shape that we will draw to the screen
    float circleRadius = 50;   // radius to draw the circle
    int circleSegments = 32;   // number of segments to draw the circle with
    float circleSpeedX = 1.0f; // we will use this to move the circle later
    float circleSpeedY = 0.5f; // you will read these values from the file
    bool drawCircle = true;    // whether or not to draw the circle
    bool drawText = true;      // whether or not to draw the text

    // create the sfml circle shape based on our parameters
    // create a circle shape with radius
    sf::CircleShape circle(circleRadius, circleSegments);
    circle.setPosition(10.0f, 10.0f);

    // lets load a font so we can display some text
    sf::Font myFont;

    // attempt to load the font from a file
    if (!myFont.loadFromFile("fonts/tech.ttf")) {
        // if we can't load the font, print an error
        std::cerr << "Could not load font!\n";
        exit(-1);
    }

    // set up teh text object that will be drawn to the screen
    sf::Text text("Sample Text", myFont, 24);

    // position the top-left corner of the text so that the text aligns on the
    // bottom text scharacter size is in pixels. so move the text up from the
    // bottom by its height
    text.setPosition(0, wHeight - (float)text.getCharacterSize());

    // set up a character array to set the text
    char displayString[255] = "Sample Text";

    // main loop continues for each frame while window is open
    while (window.isOpen()) {
        // event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            // pass the event to imgui to be parsed
            ImGui::SFML::ProcessEvent(window, event);

            // this event triggers when the window is closed
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Keyboard::Q) {
                window.close();
            }

            // This event is triggered when a key is pressed
            if (event.type == sf::Event::KeyPressed) {
                // print the key that was pressed to the console
                std::cout << "Key pressed with code=" << event.key.code << "\n";

                // example, what happens when x is presed
                if (event.key.code == sf::Keyboard::X) {
                    // reverse the x direction of the circle on the screen
                    circleSpeedX *= -1.0f;
                }
            }
        }

        // update imgui for this frame with the time that the last frame took
        ImGui::SFML::Update(window, deltaClock.restart());

        // draw the UI
        ImGui::Begin("Window Title");
        ImGui::Text("Window text!");
        ImGui::Checkbox("Draw Circle", &drawCircle);
        ImGui::SameLine();
        ImGui::Checkbox("Draw Text", &drawText);
        ImGui::SliderFloat("Radius", &circleRadius, 0.0f, 300.0f);
        ImGui::SliderInt("Sides", &circleSegments, 3, 64);
        ImGui::ColorEdit3("ColorCircle", c);
        ImGui::InputText("Text", displayString, 255);
        if (ImGui::Button("Set Text")) {
            text.setString(displayString);
        }
        ImGui::SameLine();
        if (ImGui::Button("Reset Circle")) {
            circle.setPostion(0, 0);
        }
        ImGui::End();

        // set the circle properties, because they may have been updated with
        // the ui
        circle.setPointCount(circleSegments);
        circle.setRadius(circleRadius);

        // imgui uses 0-1 float for colors, sfml uses 0-255 for colors
        // we must convert from the ui floats to sfml Uint8
        circle.setFillColor(sf::Color(sf::Uint8(c[0] * 255),
                                      sf::Uint8(c[1] * 255),
                                      sf::Uint8(c[2] * 255)));

        // basic animation - move the each frame if it's still in frame
        circle.setPosition(circle.getPosition().x + circleSpeedX,
                           circle.getPosition().y + circleSpeedY);

        // basic rendering function calls
        window.clear();   // clear the window of anything previously drawn
        if (drawCircle) { // draw the circle if the boolean is true
            window.draw(circle);
        }
        if (drawText) { // draw the text if the boolean is true
            window.draw(text);
        }
        ImGui::SFML::Render(window); // draw the ui last so it's on top
        window.display();
    }

    return 0;
}
