#TRABALHO 2 DE AEDS PRATICA
#MELISSA ALVES, JULIA ROCHA E MELL DIAS

# Compilador C
CC = gcc
# Flags de compilação: -O2 para otimização, -Wall para avisos, -g para debug
CFLAGS = -O2 -Wall -Wextra -g

# Nome do executável final
TARGET = external_sorter

# Arquivos fonte
SOURCES = main.c external_sort.c min_heap.c utils.c

# Arquivos objeto (gerados a partir dos fontes .c)
OBJECTS = $(SOURCES:.c=.o)

# Regra padrão: compila o programa inteiro
all: $(TARGET)

# Regra de ligação (linking): cria o executável a partir dos arquivos objeto
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Regra de compilação: compila um arquivo .c em um arquivo .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra de limpeza: remove os arquivos gerados (objetos e executável)
clean:
	rm -f $(OBJECTS) $(TARGET)

# Regra para remover arquivos temporários gerados pela ordenação
clean_temp:
	rm -f temp_chunk_*.bin

.PHONY: all clean clean_temp