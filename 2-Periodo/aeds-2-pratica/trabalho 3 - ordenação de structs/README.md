# Trabalho Prático 3 - Ordenação de Structs
## DCE792 - Algoritmos e Estruturas de Dados 2

---

## 📋 Descrição

Este projeto implementa e compara três algoritmos de ordenação aplicados a uma estrutura de dados (struct) contendo informações de jogadores de futebol. Os algoritmos são ordenados pelo campo "nome" e avaliados em termos de tempo de execução, número de comparações, número de trocas e uso de memória.

---

## 🎯 Algoritmos Implementados

### 1️⃣ Selection Sort (Método Simples)
- **Complexidade:** O(n²)
- **Característica:** Simples, previsível, pouquíssimas trocas

### 2️⃣ Quick Sort (Método Ótimo)
- **Complexidade:** O(n log n) médio
- **Característica:** Rápido, recursivo, in-place

### 3️⃣ Radix Sort LSD (Método Linear)
- **Complexidade:** O(n × k)
- **Característica:** Não-comparativo, estável, linear

---

## 📁 Estrutura do Projeto

```
trabalho-pratico-3/
│
├── 📄 jogador.h              # Cabeçalho com definições
├── 📄 main.c                 # Programa principal
├── 📄 io.c                   # Funções de entrada/saída
├── 📄 selection_sort.c       # Implementação Selection Sort
├── 📄 quick_sort.c           # Implementação Quick Sort
├── 📄 radix_sort.c           # Implementação Radix Sort LSD
├── 📄 utils.c                # Funções auxiliares
├── 📄 Makefile               # Sistema de compilação
├── 📄 jogadores.csv          # Dados de entrada
└── 📄 README.md              # Este arquivo
```

---

## 🚀 Como Compilar e Executar

### Requisitos
- **GCC** (GNU Compiler Collection)
- **Make**
- Sistema operacional Linux/Unix

### Compilação

```bash
# Compilar o projeto
make all
```

### Execução

#### Executar algoritmos individuais:

```bash
# Selection Sort
make run1
# ou
./tp3 1

# Quick Sort
make run2
# ou
./tp3 2

# Radix Sort LSD
make run3
# ou
./tp3 3
```

#### Executar todos os algoritmos:

```bash
make runall
```

### Limpeza

```bash
# Remover arquivos compilados
make clean

# Recompilar tudo
make rebuild
```

---

## 📊 Formato de Saída

O programa produz duas partes na saída:

### 1. Lista Ordenada de Jogadores (CSV)
```
Nome,Posição,Naturalidade,Clube,Idade
Aaron Ramsdale,Goleiro,England,Arsenal FC,25
Aaron Wan-Bissaka,Lateral direito,England,Manchester United,25
...
```

### 2. Métricas de Desempenho (4 linhas)
```
15.43          # Tempo em milissegundos
245003         # Número de comparações
983            # Número de trocas
524288         # Memória utilizada em bytes
```

---

## 🧪 Exemplo de Uso Completo

```bash
# 1. Compilar
make all

# 2. Executar com Quick Sort
./tp3 2

# Ou executar com redirecionamento
./tp3 2 > resultado_quicksort.txt

# 3. Ver apenas as métricas (últimas 4 linhas)
./tp3 2 | tail -n 4
```

---

## 📈 Comparação de Desempenho

### Características Esperadas

| Algoritmo | Tempo | Comparações | Trocas | Memória |
|-----------|-------|-------------|--------|---------|
| **Selection Sort** | Lento | Máximas | Mínimas | Mínima |
| **Quick Sort** | Rápido | Moderadas | Moderadas | Baixa |
| **Radix Sort LSD** | Muito Rápido* | N/A** | Muitas | Alta |

\* Para strings de tamanho limitado  
\*\* Não usa comparações diretas

---

## 🔧 Comandos do Makefile

| Comando | Descrição |
|---------|-----------|
| `make all` | Compila o projeto completo |
| `make run1` | Executa Selection Sort |
| `make run2` | Executa Quick Sort |
| `make run3` | Executa Radix Sort LSD |
| `make runall` | Executa todos os algoritmos |
| `make clean` | Remove arquivos compilados |
| `make rebuild` | Limpa e recompila |
| `make help` | Mostra ajuda |
| `make info` | Mostra informações do projeto |

---

## 📚 Estrutura de Dados

### Struct Jogador

```c
typedef struct {
    char nome[100];           // Nome completo
    char posicao[50];         // Posição em campo
    char naturalidade[50];    // País de origem
    char clube[50];           // Clube atual
    int idade;                // Idade
} Jogador;
```

---

## 🔍 Detalhes de Implementação

### Selection Sort
- Algoritmo in-place
- Sempre O(n²) comparações
- Mínimo de trocas
- Arquivo: `selection_sort.c`

### Quick Sort
- Pivô do meio
- Recursivo
- Particionamento in-place
- Arquivo: `quick_sort.c`

### Radix Sort LSD
- Processa da direita para esquerda
- Counting Sort como sub-rotina
- Estável
- Arquivo: `radix_sort.c`

---

## ⚙️ Flags de Compilação

```makefile
CFLAGS = -Wall -Wextra -O2 -std=c99 -pedantic
```

- `-Wall`: Todos os warnings comuns
- `-Wextra`: Warnings adicionais
- `-O2`: Otimização nível 2
- `-std=c99`: Padrão C99
- `-pedantic`: Conformidade estrita

---

## 🐛 Troubleshooting

### Erro: "Arquivo jogadores.csv não encontrado"
**Solução:** Certifique-se de que o arquivo está no mesmo diretório do executável.

### Erro: "make: command not found"
**Solução:** Instale o make:
```bash
sudo apt-get install build-essential  # Ubuntu/Debian
```

### Erro de compilação com memória
**Solução:** O código usa `getrusage()` que é POSIX. Compile em Linux/Unix.

---

## 👥 Autores

**Integrantes do Grupo:**
- Melissa Alves
- Julia Rocha
- Mell Dias

**Orientador:**
- Prof. Iago Augusto de Carvalho

**Instituição:**
- Universidade Federal de Alfenas (UNIFAL-MG)
- Bacharelado em Ciência da Computação

---

## 📝 Licença

Este projeto foi desenvolvido para fins acadêmicos como parte da disciplina DCE792 - Algoritmos e Estruturas de Dados 2.

---

## 🎓 Referências

1. CORMEN, T. H. et al. **Algoritmos: Teoria e Prática**. 3ª ed. Elsevier, 2012.
2. SEDGEWICK, R.; WAYNE, K. **Algorithms**. 4th ed. Addison-Wesley, 2011.
3. ZIVIANI, N. **Projeto de Algoritmos**. 3ª ed. Cengage Learning, 2010.

---

**Status:** ✅ Completo e testado