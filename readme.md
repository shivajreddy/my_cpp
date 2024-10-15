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
    # This runs the executable
    COMMAND ${PROJECT_NAME}   
    # Ensure the executable is built before running
    DEPENDS ${PROJECT_NAME}   
    # Set working directory to the build directory
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}  
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

### 4. Opening a project folder in Visual Studio, by creating solution
- 1. Open `Visual Studio 2022`
- 2. Choose `Continue without code`
- 3. Go to `File` > `New` > `Project From Existing Code`
- 4. Choose `Visual C++` as the type of project to create
- 5.  - Choose the location of `my_game` as the `Project file location`
       Example: `C:\Users\shiva\projects\my_game`
      - For 'Project Name' use the same name as the project folder name, 
        otherwise it will create a sub-folder.
      - Check the 'Show all fines in Solution Explorer', then hit next
- 6.  - Choose 'use Visual Studio'
      - For 'Project Type', choose 'Console application project'
      - Check 'Add support for the Common Language Runtime' and for drop down
        choose default option i.e., 'Common Language Runtime Support'
- 7. Hit finish
