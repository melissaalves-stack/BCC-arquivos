# Makefile para o Trabalho Prático 3 - AEDS 2
# Compilador e flags

CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99
TARGET = tp3
SRC = main.c

# Regra padrão
all: $(TARGET)

# Compilar o programa
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Executar com Selection Sort
run1: $(TARGET)
	./$(TARGET) 1

# Executar com Quick Sort
run2: $(TARGET)
	./$(TARGET) 2

# Executar com Radix Sort LSD
run3: $(TARGET)
	./$(TARGET) 3

# Limpar arquivos compilados
clean:
	rm -f $(TARGET) *.o

# Regra para mostrar ajuda
help:
	@echo "Uso do Makefile:"
	@echo "  make all    - Compila o programa"
	@echo "  make run1   - Executa Selection Sort"
	@echo "  make run2   - Executa Quick Sort"
	@echo "  make run3   - Executa Radix Sort LSD"
	@echo "  make clean  - Remove arquivos compilados"
	@echo "  make help   - Mostra esta mensagem"

.PHONY: all run1 run2 run3 clean help