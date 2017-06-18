CXX = g++
FLAGS = -std=c++11
OUTPUT = diffraction
LIBRARIES = -lSDL2 -lSDL2_gfx

SOURCE = main.cpp engine.cpp room.cpp entity.cpp vector.cpp wave.cpp

all : $(OUTPUT)

$(OUTPUT) : $(SOURCE)
	$(CXX) $(FLAGS) -o $(OUTPUT) $(SOURCE) $(LIBRARIES)
