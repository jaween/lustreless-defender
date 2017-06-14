CXX = g++
FLAGS = -std=c++11
OUTPUT = diffraction
LIBRARIES = -lSDL2

SOURCE = main.cpp engine.cpp

all : $(OUTPUT)

$(OUTPUT) : $(SOURCE)
	$(CXX) $(FLAGS) -o $(OUTPUT) $(SOURCE) $(LIBRARIES)
