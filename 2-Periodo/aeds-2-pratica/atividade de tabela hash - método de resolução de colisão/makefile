# Automatizando o makefile

# Nome do projeto
PROJ_NAME=hash

# Arquivos .c
C_SOURCE=$(wildcard *.c)

# Arquivos .h
H_SOURCE=$(wildcard *.h)

# Arquivos objeto
OBJ=$(C_SOURCE:.c=.o)

# Compilador
CC=gcc

# Flags (opções) para o compilador
CC_FLAGS=-c         \
         -Wall      \
         -g         \
         -pedantic

#########################
# Compilação e linkagem #
#########################
all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c %.h
	$(CC) -o $@ $< $(CC_FLAGS)

main.o: main.c $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)

# Como main está dentro de hash.c, precisamos compilar apenas hash.c
hash.o: hash.c hash.h
	$(CC) -o $@ $< $(CC_FLAGS)

clean:
	rm -rf *.o $(PROJ_NAME) *~

run: $(PROJ_NAME)
	./$(PROJ_NAME)

# Comando para debug com valgrind (verificar vazamento de memória)
valgrind: $(PROJ_NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROJ_NAME)