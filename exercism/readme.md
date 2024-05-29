
Pre-reqs:
gcc, g++ ,cmake, entr

1. Create a build folder in the exercise directory
2. Go to the exercise directory
3. you are in the `build` directory, and the outside folder i.e., exercise folder has `CMakeLists.txt` file, now run:
```bash
cmake -G "Unix Makefiles" ..
```
4. Now execute the following
```bash
find ../<name_of_the_exercise_file>.cpp | entr -c make
```
