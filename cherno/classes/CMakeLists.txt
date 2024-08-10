cmake_minimum_required(VERSION 3.10)

# project name and version
project(classes VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include all .cpp files from src/
file(GLOB SRC_FILES src/*.cpp src/*.h)

# Add the Executable target
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Include Directories
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/src")
