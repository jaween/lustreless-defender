CXX = g++
FLAGS = -std=c++11 -MMD -MP

BUILD_DIR = build
OUTPUT = bin/diffraction

SOURCE_DIR = src
SOURCES = $(wildcard $(SOURCE_DIR)/*.cc)

OBJECTS = $(addprefix $(BUILD_DIR)/,$(SOURCES:$(SOURCE_DIR)/%.cc=%.o))

LIBRARIES = -lSDL2 -lSDL2_gpu -lGL -lGLEW
LINKER_FLAGS = -Wl,-rpath,/usr/local/lib

INCLUDE_DIR = include
INCLUDE_FLAGS = -I/usr/include/SDL2 -I/usr/local/include/SDL2 -I./$(INCLUDE_DIR)

DEPENDENCIES = $(OBJECTS:.o=.d)

all : $(OUTPUT)

$(OUTPUT) : $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(INCLUDE_FLAGS) $(LINKER_FLAGS) $(LIBRARIES)

$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.cc $(BUILD_DIR)
	$(CXX) -o $@ -c $< $(FLAGS) $(INCLUDE_FLAGS)

$(BUILD_DIR) :
	mkdir -p $(BUILD_DIR)

clean :
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d $(OUTPUT)
	rmdir $(BUILD_DIR)

-include $(DEPENDENCIES)
