CXX = g++
FLAGS = -std=c++11
OUTPUT = diffraction
LIBRARIES = -lSDL2 -lSDL2_gpu -lGL -lGLEW
INCLUDE = -I/usr/include/SDL2 -I/usr/local/include/SDL2
LINKER_FLAGS = -Wl,-rpath,/usr/local/lib

SOURCE = main.cpp engine.cpp room.cpp entity.cpp vector.cpp wave.cpp image.cpp sprite.cpp

all : $(OUTPUT)

$(OUTPUT) : $(SOURCE)
	$(CXX) $(FLAGS) -o $(OUTPUT) $(SOURCE) $(LIBRARIES) $(INCLUDE) $(LINKER_FLAGS)
