# Directories

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
ARCH_DIR = dist
TOOL_DIR = tools
DICT_DIR = dict

# Program

EXECUTABLE_NAME = lg
EXECUTABLE = $(BIN_DIR)/./$(EXECUTABLE_NAME)

# Compiler

CC = gcc
CFLAGS = -Wall

# Files and folders

SRCS = $(shell find $(SRC_DIR) -name '*.c')
SRC_DIRS = $(shell find $(SRC_DIR) -type d | sed 's/$(SRC_DIR)/./g' )
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Compiling

$(BIN_DIR)/$(EXECUTABLE_NAME) : title build_dir $(OBJS)
	@echo "> Compiling : "
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run

help:
	@$(EXECUTABLE) -help
trie:
	@$(EXECUTABLE) -sentence -trie
dawg:
	@$(EXECUTABLE) -sentence -dawg
_trie:
	@$(EXECUTABLE) -trie
sentence:
	@$(EXECUTABLE) -sentence
	
# Utils

build_dir:
	@$(call make-obj)

clean:
	@echo "> Cleaning :"
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)
	rm -rf $(ARCH_DIR)
	rm -rf $(DICT_DIR)

dict:
	@./tools/fetch_dict.sh

dist: clean
	@mkdir -p $(ARCH_DIR)
	@echo "> Archiving :"
	tar -czvf $(ARCH_DIR)/SDA2_Projet.tar.gz Makefile README.md $(TOOL_DIR) $(SRC_DIR)

# Functions

# Create obj directory structure
define make-obj
	mkdir -p $(OBJ_DIR)
	for dir in $(SRC_DIRS); \
	do \
		mkdir -p $(OBJ_DIR)/$$dir; \
	done
endef

# Others

title:
	@echo '   __   ___   _  _________  _____  _________  ___  _________________________________  _  __'
	@echo '  / /  / _ | / |/ / ___/ / / / _ |/ ___/ __/ / _ \/ __/_  __/ __/ ___/_  __/  _/ __ \/ |/ /'
	@echo ' / /__/ __ |/    / (_ / /_/ / __ / (_ / _/  / // / _/  / / / _// /__  / / _/ // /_/ /    / '
	@echo '/____/_/ |_/_/|_/\___/\____/_/ |_\___/___/ /____/___/ /_/ /___/\___/ /_/ /___/\____/_/|_/  '
	@echo '                                                                                           '