# Seção de Resultados: Compilador Ruby-like para C

Esta seção detalha as funcionalidades implementadas e testadas no compilador, demonstrando sua capacidade de processar código-fonte Ruby-like e gerar sua representação em C.

-----

## 1\. Declaração e Atribuição de Variáveis

O compilador processa corretamente a **declaração e atribuição de variáveis**. Ele consegue lidar com diferentes tipos, como numéricos (inteiros e ponto flutuante), strings e booleanos, inferindo seus tipos conforme o uso no código Ruby-like.

**Exemplo de Código Ruby-like Processado:**

```ruby
idade = 30
preco = 99.99
nome = "Dani"
is_active = true
puts idade
puts preco
puts nome
puts is_active
```

-----

## 2\. Operações Aritméticas e Lógicas

A capacidade de realizar **operações aritméticas** básicas (adição, subtração, multiplicação e divisão) e **operações lógicas** (`and`, `or`, `not`) foi implementada com sucesso. O compilador consegue gerar as estruturas C correspondentes para essas operações.

**Exemplo de Código Ruby-like Processado:**

```ruby
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

condicao1 = true
condicao2 = false

res_and = condicao1 and condicao2
res_or = condicao1 or condicao2
res_not = not condicao1
puts res_and
puts res_or
puts res_not
```

-----

## 3\. Estruturas de Repetição: `for` (com `range`) e `while`

O compilador é capaz de traduzir **loops `for`** que utilizam a sintaxe de `range` (incluindo `..` para intervalos inclusivos e `...` para exclusivos) e **loops `while`** para as estruturas de repetição correspondentes em C. Isso permite a execução de blocos de código repetidamente com base em condições ou iterações sobre ranges.

**Exemplo de Código Ruby-like Processado:**

```ruby
puts "For (1..3):"
for i in 1..3 do
  puts i
end

puts "For (0...2):"
for j in 0..2 do
  puts j
end

i = 0
while i < 3 do
  puts(i)
  i = i + 1
end
```

-----

## 4\. Declaração e Chamada de Funções

A **definição de funções**, incluindo a passagem de parâmetros e o retorno de valores, é suportada. O compilador consegue traduzir a estrutura das funções Ruby-like para funções C, permitindo a modularização e reutilização de código.

**Exemplo de Código Ruby-like Processado:**

```ruby
def soma(a, b)
  return a + b
end

resultado_soma = soma(10, 20)
```