#!/bin/bash

# --- Configurações ---
COMPILER_EXECUTABLE="./build/meu_compilador" # Caminho para o seu executável do compilador
DEFAULT_COMPILER_OUTPUT="output.c"           # Nome do arquivo C que seu compilador sempre gera (ajuste se for diferente)
TEST_DIR="test/exemplos"                     # Diretório onde os testes e outputs serão salvos

# --- Funções Auxiliares ---
log_step() {
    echo "--- $1 ---"
}

create_file() {
    local filepath=$1
    local content=$2
    log_step "Criando arquivo: $filepath"
    mkdir -p "$(dirname "$filepath")"
    echo "$content" > "$filepath"
}

run_test() {
    local test_name=$1
    local ruby_code=$2

    log_step "Processando exemplo: $test_name"

    local ruby_file="$TEST_DIR/${test_name}.rb"
    local c_file="$TEST_DIR/${test_name}.c"

    create_file "$ruby_file" "$ruby_code"

    # Limpa qualquer arquivo de saída padrão anterior para evitar confusão
    if [ -f "$DEFAULT_COMPILER_OUTPUT" ]; then
        rm "$DEFAULT_COMPILER_OUTPUT"
    fi

    # Garante que um arquivo C seja criado, mesmo que vazio, se o compilador não gerar nada
    touch "$DEFAULT_COMPILER_OUTPUT"

    # 1. Rodar seu compilador para gerar o código C
    log_step "Rodando seu compilador em $ruby_file..."

    if ! "$COMPILER_EXECUTABLE" "$ruby_file" 2>&1; then
        echo "ERRO: Seu compilador falhou com o arquivo $ruby_file."
        echo "### SAÍDA DE ERRO DO SEU COMPILADOR (VERIFIQUE AS MENSAGENS ACIMA) ###"
        echo "" # Linha em branco para melhor separação
    else
        echo "Compilação Ruby-like para C finalizada para $ruby_file."
    fi

    # 2. Renomear o arquivo C gerado pelo seu compilador (ou o vazio, se falhou)
    if [ -f "$DEFAULT_COMPILER_OUTPUT" ]; then
        mv "$DEFAULT_COMPILER_OUTPUT" "$c_file"
        echo "Código C (ou arquivo placeholder) salvo em: $c_file"
    else
        echo "AVISO: O arquivo C esperado ('$DEFAULT_COMPILER_OUTPUT') não foi encontrado para $ruby_file. Um arquivo C vazio deveria ter sido criado pelo 'touch'."
    fi

    echo "" # Linha em branco para melhor separação visual
    return 0 # Sempre retorna 0 para continuar processando, mesmo se o compilador falhou
}

# --- Limpar diretório de testes anterior (opcional) ---
if [ -d "$TEST_DIR" ]; then
    log_step "Limpando diretório de testes existente: $TEST_DIR"
    rm -rf "$TEST_DIR"
fi
mkdir -p "$TEST_DIR"

# --- Definição dos Exemplos ---

# Exemplo 1: Declaração e Atribuição de Variáveis
VAR_DECL_EXAMPLE='
idade = 30
preco = 99.99
nome = "Dani"
is_active = true
puts idade
puts preco
puts nome
puts is_active
'
run_test "01_var_declaracao" "$VAR_DECL_EXAMPLE"

# Exemplo 2: Operações Aritméticas
ARITH_OPS_EXAMPLE='
a = 10
b = 5
soma = a + b
subtracao = a - b
multiplicacao = a * b
divisao = a / b
resultado_complexo = (a + b) * 2 - divisao
puts soma
puts subtracao
puts multiplicacao
puts divisao
puts resultado_complexo
'
run_test "02_aritmeticas" "$ARITH_OPS_EXAMPLE"

# Exemplo 3: Operações Lógicas
LOGIC_OPS_EXAMPLE='
condicao1 = true
condicao2 = false

res_and = condicao1 and condicao2
res_or = condicao1 or condicao2
res_not = not condicao1
puts res_and
puts res_or
puts res_not
'
run_test "03_logicas" "$LOGIC_OPS_EXAMPLE"

# Exemplo 4: Loop For (Range)
FOR_RANGE_EXAMPLE='
puts "For (1..3):"
for i in 1..3 do
  puts i
end

puts "For (0...2):"
for j in 0..2 do
  puts j
end
'
run_test "04_for_range" "$FOR_RANGE_EXAMPLE"

# Exemplo 5: Loop While
WHILE_LOOP_EXAMPLE='
i = 0
while i < 3 do
  puts(i)
  i = i + 1
end
'
run_test "05_while_loop" "$WHILE_LOOP_EXAMPLE"

# Exemplo 6: Declaração e Chamada de Funções
FUNC_CALL_EXAMPLE='
def soma(a, b)
  return a + b
end

resultado_soma = soma(10, 20)
'
run_test "06_funcoes" "$FUNC_CALL_EXAMPLE"

log_step "Todos os exemplos processados!"
echo "Verifique a pasta '$TEST_DIR' para os arquivos .rb e .c."
echo "Os arquivos .c contêm o código C gerado (ou são arquivos placeholder)."