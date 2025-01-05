# README

- 0. This is a placeholder CMake project, with raylib
- 1. set the project name in CMakeLists.txt  
     `project(????????)`
- 2. Run the project by using `runcmake.sh`

- Compile with out using CMake

```
g++ src/main.cpp \
 -I./lib/raylib/include \
 -L./lib/raylib/lib \
 -lraylib \
 -lGL -lm -lpthread -ldl -lrt -lX11 \
 -o build/game
```

- Watch and run cmake

```
find src -type f \( -name "*.cpp" -o -name "*.h" \) | entr -c sh -c 'cmake --build build/ && clear && ./build/visualize'
```

(or)
