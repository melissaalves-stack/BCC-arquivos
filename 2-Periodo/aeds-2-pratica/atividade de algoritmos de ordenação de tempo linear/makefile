# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2

# Nome do executável
TARGET = sorting

# Arquivos objeto
OBJS = sorting.o

# Regra principal
all: $(TARGET)

# Linkagem
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compilação
sorting.o: sorting.c sorting.h
	$(CC) $(CFLAGS) -c sorting.c

# Executar
run: $(TARGET)
	./$(TARGET)

# Limpeza
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all run clean