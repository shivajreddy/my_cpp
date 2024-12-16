cmake_minimum_required(VERSION 3.16)
# Project Name
project(visualize)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the executable target
add_executable(visualize src/main.cpp)

# Include Raylib headers
include_directories(${CMAKE_SOURCE_DIR}/lib/raylib/include)

# Link Raylib static library
set(RAYLIB_STATIC_LIB ${CMAKE_SOURCE_DIR}/lib/raylib/lib/libraylib.a)

# Platform-specific settings
if(WIN32)
    target_link_libraries(visualize PRIVATE ${RAYLIB_STATIC_LIB} gdi32 winmm)
elseif(APPLE)
    target_link_libraries(visualize PRIVATE ${RAYLIB_STATIC_LIB} "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreAudio" "-framework CoreVideo")
elseif(UNIX)
    target_link_libraries(visualize PRIVATE ${RAYLIB_STATIC_LIB} pthread dl m)
endif()

# Add dynamic library support if needed
# (Optional: Uncomment if you plan to use the shared library instead)
# find_library(RAYLIB_SHARED_LIB raylib HINTS ${CMAKE_SOURCE_DIR}/lib/raylib/lib)
# target_link_libraries(visualize PRIVATE ${RAYLIB_SHARED_LIB})

# Output message
message(STATUS "Raylib static library linked: ${RAYLIB_STATIC_LIB}")
