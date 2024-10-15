## How to get started with running C++

### 1. Go to the project folder that you want to create the program for
   - As an example, lets use the project name to be `my_game`
   - This is how the project directory will look like
   ```bash
   my_game/
   |- out/
   |  |- build/
   |- src/
   |  |- main.cpp
   |- CMakeLists.txt
   ```

### 2. This is a good starting point for the CMakeLists.txt file
- CMakeLists.txt
```bash
cmake_minimum_required(VERSION 3.10)

# project name and version
project(my_game VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include all .cpp files from src/
file(GLOB SRC_FILES src/*.cpp src/*.h)

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

# Define a custom target 'run' that builds the project and runs the executable
add_custom_target(run
    COMMAND ${PROJECT_NAME}   # This runs the executable
    DEPENDS ${PROJECT_NAME}   # Ensure the executable is built before running
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}  # Set working directory to the build directory
    COMMENT "Building and running the executable"
)

# Ensure the executable is built before the 'run' target
add_dependencies(run ${PROJECT_NAME})
```

### 3. Commands to build and run
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


