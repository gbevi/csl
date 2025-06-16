# Compilador
CC := $(shell command -v clang || command -v gcc)
FLEX = flex
YACC = bison

# Diretório de build
BUILD_DIR = build

# Flags do compilador
# -I. para o diretório atual (onde o Makefile está)
# -I$(BUILD_DIR) para onde parser.tab.h está
# -IST para ast.h e tabela.h (que agora são incluídos diretamente sem o ST/ no nome)
CFLAGS = -Wall -Wextra -g -I. -I$(BUILD_DIR) -IST
LDFLAGS = -lfl -lm

# Nome do executável do compilador
COMPILER_EXEC = $(BUILD_DIR)/meu_compilador

.PHONY: all run clean debug

# Regra padrão: gera o compilador
all: $(COMPILER_EXEC)

# REGRA PRINCIPAL PARA GERAR O EXECUTÁVEL
# Ela faz todas as etapas de geração (bison, flex) e depois compila/linka tudo.
$(COMPILER_EXEC):
	@echo "--- Criando diretório de build ---"
	@mkdir -p $(BUILD_DIR)

	@echo "--- Gerando parser.tab.c e parser.tab.h com Bison ---"
	$(YACC) -d -o $(BUILD_DIR)/parser.tab.c parser/parser.y

	@echo "--- Gerando lexer.c com Flex ---"
	$(FLEX) -o $(BUILD_DIR)/lexer.c lexer/lexer.l

	@echo "--- Compilando e linkando todos os arquivos .c ---"
	$(CC) $(CFLAGS) \
		$(BUILD_DIR)/parser.tab.c \
		$(BUILD_DIR)/lexer.c \
		ST/ast.c \
		ST/tabela.c \
		-o $@ $(LDFLAGS)

	@echo "--- Compilador gerado em $@ ---"

# Regra para executar o compilador com um arquivo de teste
# Ex: make run TEST_FILE=test/meu_programa.txt
run: $(COMPILER_EXEC)
	@echo "--- Executando o compilador com $(TEST_FILE) ---"
	@$(COMPILER_EXEC) $(TEST_FILE)
	@echo "--- Fim da execução ---"

# Regra para depuração com GDB
# Ex: make debug TEST_FILE=test/meu_programa.txt
debug: $(COMPILER_EXEC)
	@echo "--- Iniciando GDB com $(TEST_FILE) ---"
	@gdb --args $(COMPILER_EXEC) $(TEST_FILE)

# Limpa os arquivos gerados no diretório de build
clean:
	@echo "--- Limpando arquivos gerados ---"
	@rm -rf $(BUILD_DIR)/* $(BUILD_DIR)
	@echo "--- Limpeza concluída ---"