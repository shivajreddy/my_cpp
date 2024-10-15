cmake_minimum_required(VERSION 3.10)

# project name and version
project(function-pointers VERSION 1.0)

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
