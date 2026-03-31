CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = fila_prioridade

SRCS = main.c jogador.c vetor_ordenado.c lista_encadeada.c lista_nao_ordenada.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run