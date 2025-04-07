# Compilador
CC := $(shell command -v clang || command -v gcc)
FLEX = flex
YACC = bison

# Diretório de build
BUILD_DIR = build

# Regra padrão: gera o compilador
all:
	# Gera parser (Bison)
	$(YACC) -d -o $(BUILD_DIR)/parser.tab.c parser/parser.y
	# Gera lexer (Flex)
	$(FLEX) -o $(BUILD_DIR)/lexer.c lexer/lexer.l
	# Compila o compilador
	$(CC) -o $(BUILD_DIR)/compiler \
		$(BUILD_DIR)/parser.tab.c \
		$(BUILD_DIR)/lexer.c \
		src/main.c

# Executa o compilador com hello.rb e gera hello.c
# Para testar outros arquivos Ruby:
# ./build/compiler < test/nomedoarquivo.rb > build/nomedoarquivo.c
run:
	./$(BUILD_DIR)/compiler < test/hello.rb > $(BUILD_DIR)/hello.c
# Para testar outros arquivos Ruby:
# ./build/compiler < test/nomedoarquivo.rb > build/nomedoarquivo.c

# Limpa os arquivos gerados
clean:
	rm -f $(BUILD_DIR)/*

