### How to get started with running C++

1. Go to the project folder that you want to create the program for
   - As an example, lets use the project name to be `my_game`
   - This is how the project directory will look like
   ```bash
   my_game/
   |- out/
   |  |- build/
   |- main.cpp
   |- CMakeLists.txt
   ```

2. This is a good starting point for the CMakeLists.txt file
- CMakeLists.txt
```bash
cmake_minimum_required(VERSION 3.10)

# project name and version
project(my_game VERSION 1.0)

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
```

3. Commands to build and run
```bash
cmake -S . -B out/build
cmake --build out/build
```
Here is how you can combine both commands into one:
- Linux
```bash 
cmake -S . -B out/build && cmake --build out/build
```
- Windows PowerShell
```bash 
cmake -S . -B out/build; cmake --build out/build
```


