#!/bin/bash

# clear

# Compile the code
g++ -o output *.cpp

# Check if compilation was successful
if [ $? -eq 0 ]; then
  # Run the compiled program
  ./output
else
  echo "Compilation failed."
fi
