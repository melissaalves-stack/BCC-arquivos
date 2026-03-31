# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Nome do executável
TARGET = heap

# Arquivos fonte e objeto
SOURCES = main.c heap.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = heap.h

# Regra padrão: compila o programa
all: $(TARGET)

# Compila o executável
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Compilacao concluida! Execute com: ./$(TARGET)"

# Compila os arquivos objeto
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Executa o programa
run: $(TARGET)
	./$(TARGET)

# Remove arquivos compilados
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Arquivos de compilacao removidos."

# Remove tudo e recompila
rebuild: clean all

# Mostra ajuda
help:
	@echo "Comandos disponiveis:"
	@echo "  make         - Compila o programa"
	@echo "  make run     - Compila e executa o programa"
	@echo "  make clean   - Remove arquivos compilados"
	@echo "  make rebuild - Limpa e recompila"
	@echo "  make help    - Mostra esta mensagem"

.PHONY: all run clean rebuild help