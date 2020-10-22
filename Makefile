CC = gcc
CFLAGS = -Wall -o

dist = dist
OBJ = obj
BIN = bin
SRC = src

main: title main.o
	@echo "> Compiling : "
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(BIN)/lg $(OBJ)/main.o
%.o: $(SRC)/%.c
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) $(OBJ)/$@ -c $<

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
	tar -czvf $(dist)/SDA2_Projet.tar.gz Makefile README.md fetch_dict.sh $(SRC)

clean: title
	@echo "> Cleaning :"
	rm -rf $(BIN)
	rm -rf $(OBJ)
	rm -rf $(dist)