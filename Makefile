CC = gcc
CFLAGS = -Wall

dist = dist
OBJ = obj
BIN = bin
SRC = src
TOOLS = tools

SRCS := $(shell find . -name '*.c')
OBJS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

$(BIN)/lg: $(OBJS)
	@echo "> Compiling : "
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) $^ -o $@

title:
	@echo '   __   ___   _  _________  _____  _________  ___  _________________________________  _  __'
	@echo '  / /  / _ | / |/ / ___/ / / / _ |/ ___/ __/ / _ \/ __/_  __/ __/ ___/_  __/  _/ __ \/ |/ /'
	@echo ' / /__/ __ |/    / (_ / /_/ / __ / (_ / _/  / // / _/  / / / _// /__  / / _/ // /_/ /    / '
	@echo '/____/_/ |_/_/|_/\___/\____/_/ |_\___/___/ /____/___/ /_/ /___/\___/ /_/ /___/\____/_/|_/  '
	@echo '                                                                                           '

run: title
	@bin/./lg

dist: title main.o
	@mkdir -p $(dist)
	@echo "> Archiving :"
	tar -czvf $(dist)/SDA2_Projet.tar.gz Makefile README.md $(TOOLS) $(SRC)

clean: title
	@echo "> Cleaning :"
	rm -rf $(BIN)
	rm -rf $(OBJ)
	rm -rf $(dist)