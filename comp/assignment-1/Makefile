# Compiler and flags
CXX := g++
CXXFLAGS := -Ilibs/imgui -I$(PWD)/libs/imgui-sfml -Ilibs/sfml/include -std=c++17 -Wall -Wextra

# Libraries and paths
LIBS := -lsfml-graphics -lsfml-window -lsfml-system -pthread
SFML_LIB_PATH := libs/sfml/lib
IMGUI_SOURCES := libs/imgui/imgui.cpp libs/imgui/imgui_draw.cpp libs/imgui/imgui_widgets.cpp libs/imgui/imgui_tables.cpp
IMGUI_SFML_SOURCES := libs/imgui-sfml/imgui-SFML.cpp

# Source and output
SRC := src/main.cpp $(IMGUI_SOURCES) $(IMGUI_SFML_SOURCES)
OBJ := $(SRC:.cpp=.o)
TARGET := your_project_executable

# Build target
$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ -L$(SFML_LIB_PATH) $(LIBS)

# Compile each .cpp file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)

# Run the project
run: $(TARGET)
	./$(TARGET)

