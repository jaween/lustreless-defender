CXX = g++
FLAGS = -std=c++11
OUTPUT = diffraction
LIBRARIES = -lSDL2 -lSDL2_gpu -lGL -lGLEW
INCLUDE = -I/usr/include/SDL2 -I/usr/local/include/SDL2 -I./lib/
LINKER_FLAGS = -Wl,-rpath,/usr/local/lib

HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
SOURCE = main.cpp engine.cpp shader.cpp image.cpp sprite.cpp entity.cpp room.cpp vector.cpp wave.cpp solid_shader.cpp texture_shader.cpp occlusion_mask_shader.cpp shadow_map_shader.cpp shadow_mask_shader.cpp highlight_shader.cpp light.cpp

all : $(OUTPUT)

%.o : %.cpp $(HEADERS)
	$(CXX) -o $@ $(INCLUDE) -c $(FLAGS) $<

$(OUTPUT) : $(OBJECTS)
	$(CXX) $(FLAGS) -o $@ $(OBJECTS) $(LIBRARIES) $(LINKER_FLAGS)

clean :
	rm -f *.o $(OUTPUT)
