CC = gcc
CFLAGS = -Wall -o

DDIR = dist
ODIR = obj
BDIR = bin

main: main.o
	@echo '   __   ___   _  _________  _____  _________  ___  _________________________________  _  __'
	@echo '  / /  / _ | / |/ / ___/ / / / _ |/ ___/ __/ / _ \/ __/_  __/ __/ ___/_  __/  _/ __ \/ |/ /'
	@echo ' / /__/ __ |/    / (_ / /_/ / __ / (_ / _/  / // / _/  / / / _// /__  / / _/ // /_/ /    / '
	@echo '/____/_/ |_/_/|_/\___/\____/_/ |_\___/___/ /____/___/ /_/ /___/\___/ /_/ /___/\____/_/|_/  '
	@echo '                                                                                           '
	@echo "> Compiling : "
	@mkdir -p $(BDIR)
	$(CC) $(CFLAGS) $(BDIR)/$@ $(ODIR)/main.o
%.o: %.c
	@mkdir -p $(ODIR)
	$(CC) $(CFLAGS) $(ODIR)/$@ -c $<

run:
	@bin/./main

dist: main.o
	@mkdir -p $(DDIR)
	@echo "> Archiving :"
	tar -czvf $(DDIR)/SDA2_Projet.tar.gz Makefile README.md main.c errors.c erros.h trie.c trie.h utils.c utils.h

clean:
	@echo "> Cleaning :"
	rm -rf $(BDIR)
	rm -rf $(ODIR)
	rm -rf $(DDIR)