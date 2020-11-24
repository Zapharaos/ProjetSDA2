# Directories

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
ARCH_DIR = dist
TOOL_DIR = tools
DICT_DIR = dict

# Program

EXECUTABLE_NAME = ald
EXECUTABLE = $(BIN_DIR)/./$(EXECUTABLE_NAME)

# Compiler

CC = gcc
CFLAGS = -Wall -Wextra -Wvla -Werror

# Files and folders

SRCS = $(shell find $(SRC_DIR) -name '*.c')
SRC_DIRS = $(shell find $(SRC_DIR) -type d | sed 's/$(SRC_DIR)/./g' )
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Compiling

$(BIN_DIR)/$(EXECUTABLE_NAME) : title tips build_dir $(OBJS)
	@echo "\n> Compiling : "
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run

trie: title tips
	@./bin/ald -sentence -trie

dawg: title tips
	@./bin/ald -sentence -dawg

help: tips
	@./bin/ald -help

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
	@echo "> Loading dictionnary : "
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

list:
	@echo "> List of commands :"
	@echo "make -> compiles the program"
	@echo "make dict -> creates the dictionnary files"
	@echo "make trie -> runs the program using a trie"
	@echo "make dawg -> runs the program using a dawg"
	@echo "make clean -> clears the directory"
	@echo "make dist -> creates an archive"
	@echo "make help -> to have all informations"

title:
	@echo '   __   ___   _  _________  _____  _________  ___  _________________________________  _  __'
	@echo '  / /  / _ | / |/ / ___/ / / / _ |/ ___/ __/ / _ \/ __/_  __/ __/ ___/_  __/  _/ __ \/ |/ /'
	@echo ' / /__/ __ |/    / (_ / /_/ / __ / (_ / _/  / // / _/  / / / _// /__  / / _/ // /_/ /    / '
	@echo '/____/_/ |_/_/|_/\___/\____/_/ |_\___/___/ /____/___/ /_/ /___/\___/ /_/ /___/\____/_/|_/  '
	@echo '                                                                                           '

tips:
	@echo "> You may want to run <make> and <make dict> before starting the program :)"
	@echo "> Tips : type <make list> to check out the list of commands\n"