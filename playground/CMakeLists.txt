cmake_minimum_required(VERSION 3.16)

project(playground)

# Add the executable
add_executable(${PROJECT_NAME} main.cpp)

# Define a custom target to run the executable
add_custom_target(run
  COMMAND ${PROJECT_NAME}
  DEPENDS ${PROJECT_NAME}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  # COMMENT "Building and running the executable"
)

# Ensure the executable is built before running
add_dependencies(run ${PROJECT_NAME})

