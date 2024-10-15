cmake_minimum_required(VERSION 3.10)

# project name and version
project(function-pointers VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include all .cpp files from src/
# file(GLOB SRC_FILES src/*.cpp src/*.h)
file(GLOB SRC_FILES *.cpp *.h)

# Add the Executable target
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Include Directories
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/src")

# Platform-specific settings
if (WIN32)
    message(STATUS "Configuring for Windows")
    # Add any Windows-specific settings here
elseif(UNIX)
    message(STATUS "Configuring for Linux/Unix")
    # Add any Linux-specific settings here
endif()
