# Minimum CMake version
cmake_minimum_required(VERSION 3.14)

# Set the project name dynamically based on the folder name
get_filename_component(PROJECT_NAME ${CMAKE_SOURCE_DIR} NAME)
project(${PROJECT_NAME})

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# FetchContent module
include(FetchContent)

# Fetch the ASIO library
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-24-0 # Adjust the tag to the desired ASIO version
)

# Make ASIO available
FetchContent_MakeAvailable(asio)

# Add source files
file(GLOB_RECURSE SOURCES
    src/*.cpp
    include/*.h
    include/*.hpp
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include ASIO headers
target_include_directories(${PROJECT_NAME} PRIVATE ${asio_SOURCE_DIR}/asio/include)

# Link libraries if necessary (e.g., pthread on Linux)
if(UNIX)
    target_link_libraries(${PROJECT_NAME} pthread)
endif()

# Output build messages
message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "ASIO Library Fetched From: ${asio_SOURCE_DIR}")
