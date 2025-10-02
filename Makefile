# Nom de l'exécutable
TARGET := program

# Dossiers
SRC_DIR := src
BUILD_DIR := build

# Compilateur et options
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -O2

# Trouve tous les fichiers sources
SRCS := $(shell find $(SRC_DIR) -name "*.cpp")

# Transforme src/xxx.cpp -> build/xxx.o
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Règle par défaut
all: $(TARGET)

# Link final
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilation des .cpp vers .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@


.phony: all clean

# nettoyage
clean:
	rm -rf $(build_dir) $(target)

# Exécution
run: all
	./$(TARGET)
