// src/main.cpp
#include <GLFW/glfw3.h>
/* #include <glad/glad.h> */
#include <iostream>

// Callback function for window resizing
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

// Process input
void processInput(GLFWwindow *window);

int main() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    return -1;
  }

  // Configure GLFW (OpenGL version 3.3 Core Profile)
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a GLFW window
  GLFWwindow *window =
      glfwCreateWindow(800, 600, "GLFW & GLAD in WSL", nullptr, nullptr);
  if (window == nullptr) {
    std::cerr << "Failed to create GLFW window\n";
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Set the framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Initialize GLAD before calling any OpenGL functions
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD\n";
    return -1;
  }

  // Render loop
  while (!glfwWindowShouldClose(window)) {
    // Handle input
    processInput(window);

    // Rendering commands here
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap buffers and poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Clean up and exit
  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow *window) {
  // Close the window when the ESC key is pressed
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // Adjust the viewport when the window size changes
  glViewport(0, 0, width, height);
}
