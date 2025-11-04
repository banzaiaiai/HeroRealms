# Nom de l'exécutable
TARGET := program

# Dossiers
SRC_DIR := src
BUILD_DIR := build
INC_DIR := include

# Compilateur et options
CXX := g++
CXXFLAGS := -Wall -Wextra -g -std=c++17 -I$(INC_DIR)
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system

# Mode par défaut (release ou debug)
BUILD ?= release
ifeq ($(BUILD),debug)
    CXXFLAGS += -g -O0
else
    CXXFLAGS += -O2
endif

# Trouve tous les fichiers sources
SRCS := $(shell find $(SRC_DIR) -name "*.cpp")

# Transforme src/xxx.cpp -> build/xxx.o
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Fichiers de dépendances (.d) générés automatiquement
DEPS := $(OBJS:.o=.d)

# Règle par défaut
all: $(TARGET)

# Link final
$(TARGET): $(OBJS)
	@echo "🔗 Edition de liens -> $@"
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compilation des .cpp vers .o + génération des dépendances
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "⚙️ Compilation -> $<"
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Inclure automatiquement les dépendances
-include $(DEPS)

# Nettoyage
clean:
	@echo "🧹 Nettoyage"
	rm -rf $(BUILD_DIR) $(TARGET)

# Exécution
run: all
	./$(TARGET)

# Mode debug
debug:
	$(MAKE) BUILD=debug

# Mode release
release:
	$(MAKE) BUILD=release

# Ajouter une nouvelle classe
addclass:
ifndef NAME
	$(error ❌ Utilisation: make addclass NAME=NomClasse)
endif
	@echo "➕ Création de la classe $(NAME)"
	@mkdir -p $(SRC_DIR) $(INC_DIR)
	@if [ ! -f $(INC_DIR)/$(NAME).hpp ]; then \
		echo "#pragma once" > $(INC_DIR)/$(NAME).hpp; \
		echo "" >> $(INC_DIR)/$(NAME).hpp; \
		echo "class $(NAME) {" >> $(INC_DIR)/$(NAME).hpp; \
		echo "public:" >> $(INC_DIR)/$(NAME).hpp; \
		echo "    $(NAME)();" >> $(INC_DIR)/$(NAME).hpp; \
		echo "    ~$(NAME)();" >> $(INC_DIR)/$(NAME).hpp; \
		echo "};" >> $(INC_DIR)/$(NAME).hpp; \
		echo "✅ Header créé: $(INC_DIR)/$(NAME).hpp"; \
	else \
		echo "⚠️  Header déjà existant: $(INC_DIR)/$(NAME).hpp"; \
	fi
	@if [ ! -f $(SRC_DIR)/$(NAME).cpp ]; then \
		echo "#include \"$(NAME).hpp\"" > $(SRC_DIR)/$(NAME).cpp; \
		echo "" >> $(SRC_DIR)/$(NAME).cpp; \
		echo "$(NAME)::$(NAME)() {}" >> $(SRC_DIR)/$(NAME).cpp; \
		echo "$(NAME)::~$(NAME)() {}" >> $(SRC_DIR)/$(NAME).cpp; \
		echo "✅ Source créé: $(SRC_DIR)/$(NAME).cpp"; \
	else \
		echo "⚠️  Source déjà existante: $(SRC_DIR)/$(NAME).cpp"; \
	fi

.PHONY: all clean run debug release addclass

