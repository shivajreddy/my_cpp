# graphics/YoutubeOpenGL/CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(YoutubeOpenGL)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLFW (Ensure GLFW is installed system-wide or specify its path)
find_package(glfw3 3.3 REQUIRED)

# Include directories for GLAD
include_directories(${CMAKE_SOURCE_DIR}/glad/include)

# Add GLAD as a static library
add_library(glad STATIC glad/src/glad.c)

# Specify include directories for GLAD
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/glad/include)

# Specify the executable and its source files
add_executable(YoutubeOpenGL src/main.cpp)

# Link libraries
target_link_libraries(YoutubeOpenGL
    glad
    glfw
    ${OPENGL_gl_LIBRARY}
)

