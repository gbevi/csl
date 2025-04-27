# Estudo da Linguagem Ruby (Focado no Escopo do Compilador CSL)

## Introdução

Este documento descreve o subconjunto da linguagem Ruby que é suportado pelo compilador CSL, que traduz código Ruby para C. O foco está nas características definidas no escopo do projeto, garantindo que a documentação seja relevante para a implementação do compilador.

Ruby é uma linguagem de programação interpretada, orientada a objetos e de tipagem dinâmica. Para a compilação para C (uma linguagem estaticamente tipada), foram feitas adaptações e seleções específicas.

## Tipos de Dados Suportados

O compilador CSL suporta um mapeamento direto dos seguintes tipos Ruby para tipos C:

| Tipo C    | Tipo Ruby Correspondente | Exemplo Ruby      | Exemplo C (Compilado)       |
|-----------|--------------------------|-------------------|-----------------------------|
| `int`     | `Integer`                | `idade = 25`      | `int idade = 25;`           |
| `float`   | `Float`                  | `altura = 1.75`   | `float altura = 1.75f;`     |
| `double`  | `Float`                  | `pi = 3.14159265` | `double pi = 3.14159265;`   |
| `char`    | `String` (tamanho 1)     | `inicial = 'B'`   | `char inicial = 'B';`       |
| `string`  | `String`                 | `msg = "Olá"`     | `char msg[] = "Olá";`      |
| `boolean` | `TrueClass`/`FalseClass` | `ativo = true`    | `bool ativo = true;` /* ou int ativo = 1; */ |

**Observações:**

*   Ruby não distingue `float` de `double` nativamente (usa `Float`). O compilador CSL deve definir como tratar `Float` (provavelmente como `double` por padrão, ou exigir alguma sintaxe especial se ambos forem suportados).
*   Ruby não tem `char`. Strings de um caractere são usadas. O compilador CSL mapeia strings de tamanho 1 para `char`.
*   Para `boolean` em C, o uso de `bool` requer `#include <stdbool.h>`. Alternativamente, pode-se usar `int` (1 para `true`, 0 para `false`).

## Operações e Expressões Suportadas

### Operações Aritméticas

As operações aritméticas básicas são traduzidas diretamente:

| Operação      | Ruby | C (Compilado) |
|---------------|------|---------------|
| Adição        | `+`  | `+`           |
| Subtração     | `-`  | `-`           |
| Multiplicação | `*`  | `*`           |
| Divisão       | `/`  | `/`           |
| Módulo        | `%`  | `%`           |

**Exemplo Ruby:**
```ruby
a = 10
b = 3
soma = a + b
diferenca = a - b
produto = a * b
quociente = a / b
resto = a % b
```

**Exemplo C (Compilado):**
```c
int a = 10;
int b = 3;
int soma = a + b;
int diferenca = a - b;
int produto = a * b;
int quociente = a / b; // Divisão inteira resulta em 3
int resto = a % b;
```

### Operadores Relacionais

Usados para comparações, traduzidos diretamente (exceto para strings):

| Operação         | Ruby | C (Compilado) |
|------------------|------|---------------|
| Igual a          | `==` | `==`          |
| Diferente de     | `!=` | `!=`          |
| Menor que        | `<`  | `<`           |
| Menor ou igual a | `<=` | `<=`          |
| Maior que        | `>`  | `>`           |
| Maior ou igual a | `>=` | `>=`          |

**Exemplo Ruby:**
```ruby
x = 5
y = 10
igual = (x == y)
maior = (y > x)
```

**Exemplo C (Compilado):**
```c
int x = 5;
int y = 10;
bool igual = (x == y); // false (0)
bool maior = (y > x); // true (1)
```
*Nota: Comparação de strings em C requer `strcmp`.* 
```ruby
# Ruby
if nome == "admin"
# C (Compilado)
if (strcmp(nome, "admin") == 0)
```

### Operadores Lógicos

O compilador traduz as palavras-chave `and`, `or`, `not` para os operadores C.

| Operação | Ruby | C (Compilado) |
|----------|------|---------------|
| E lógico | `and`| `&&`          |
| Ou lógico| `or` | `||`          |
| Negação  | `not`| `!`           |

**Exemplo Ruby:**
```ruby
cond1 = true
cond2 = false
resultado = (cond1 and cond2) or not cond2
```

**Exemplo C (Compilado):**
```c
bool cond1 = true;
bool cond2 = false;
bool resultado = (cond1 && cond2) || !cond2; // true (1)
```

## Entrada e Saída

O escopo define `print` e `scan`.

### Saída (`print`)

O `print` do Ruby exibe valores na saída padrão sem adicionar uma nova linha automaticamente.

**Exemplo Ruby:**
```ruby
print "Digite seu nome: "
print 123
```

**Exemplo C (Compilado):**
```c
printf("Digite seu nome: ");
printf("%d", 123);
```
*Nota: O compilador mapeia `print` para `printf` em C, cuidando da formatação adequada baseada no tipo do argumento.*

### Entrada (`scan`)

O `scan` (não é um método Ruby padrão, mas definido no escopo) lê valores da entrada padrão.

**Exemplo Ruby (conceitual, baseado no escopo):**
```ruby
idade = scan(:int) # Conceito: ler um inteiro
nome = scan(:string) # Conceito: ler uma string
```

**Exemplo C (Compilado):**
```c
int idade;
scanf("%d", &idade);

char nome[100]; // Precisa definir um tamanho
scanf("%99s", nome); // Leitura de string (cuidado com buffer overflow)
```
*Nota: O compilador mapeia `scan` para `scanf` em C, usando o especificador de formato correto e gerenciando a passagem de endereço (`&`). A leitura de strings requer atenção especial em C.* 
*Ruby normalmente usa `gets` para ler strings. `gets.to_i`, `gets.to_f` são comuns para ler números.* 
*O compilador CSL precisa definir exatamente como `scan` funcionará.*

## Estruturas de Controle de Fluxo

### Condicionais (`if`, `else`)

A estrutura `if`/`else` é traduzida diretamente.

**Exemplo Ruby:**
```ruby
nota = 75
if nota >= 60
  print "Aprovado"
else
  print "Reprovado"
end
```

**Exemplo C (Compilado):**
```c
int nota = 75;
if (nota >= 60) {
  printf("Aprovado");
} else {
  printf("Reprovado");
}
```
*Nota: Ruby também tem `elsif`, que seria traduzido para `else if` em C.* 
*O `unless` do Ruby não está no escopo.* 

### Condicional (`switch` / `case`)

O escopo menciona `switch`, que corresponde ao `case` em Ruby.

**Exemplo Ruby:**
```ruby
dia = 3
case dia
when 1
  print "Domingo"
when 2
  print "Segunda"
when 3
  print "Terça"
# ... outros dias
else
  print "Dia inválido"
end
```

**Exemplo C (Compilado):**
```c
int dia = 3;
switch (dia) {
  case 1:
    printf("Domingo");
    break;
  case 2:
    printf("Segunda");
    break;
  case 3:
    printf("Terça");
    break;
  // ... outros dias
  default:
    printf("Dia inválido");
    break;
}
```
*Nota: O `case` do Ruby é mais flexível que o `switch` do C (pode usar intervalos, regex, etc.), mas o compilador CSL provavelmente suportará apenas a comparação direta de valores, similar ao `switch`.* 

### Laços de Repetição

#### `while`

Executa enquanto a condição for verdadeira.

**Exemplo Ruby:**
```ruby
i = 0
while i < 5
  print i
  i = i + 1
end
```

**Exemplo C (Compilado):**
```c
int i = 0;
while (i < 5) {
  printf("%d", i);
  i = i + 1; // ou i++;
}
```

#### `for`

O `for` em Ruby geralmente itera sobre coleções ou intervalos. A tradução para C dependerá do que está sendo iterado.

**Exemplo Ruby (intervalo):**
```ruby
for j in 0..4
  print j
end
```

**Exemplo C (Compilado):**
```c
for (int j = 0; j <= 4; j++) {
  printf("%d", j);
}
```
*Nota: O compilador CSL precisa definir como tratará o `for` do Ruby, provavelmente focando em intervalos numéricos simples.* 

#### `do while`

Ruby não tem `do while` direto. Usa-se `loop do ... break if`. O compilador CSL traduzirá essa estrutura para `do while` em C.

**Exemplo Ruby (equivalente):**
```ruby
k = 0
loop do
  print k
  k = k + 1
  break if k >= 5
end
```

**Exemplo C (Compilado):**
```c
int k = 0;
do {
  printf("%d", k);
  k = k + 1; // ou k++;
} while (k < 5);
```

## Funções

O escopo inclui definição e chamada de funções.

**Exemplo Ruby:**
```ruby
def calcular_area(largura, altura)
  return largura * altura
end

area_retangulo = calcular_area(10, 5)
print area_retangulo
```

**Exemplo C (Compilado):**
```c
// Definição da função
// O tipo de retorno e dos parâmetros precisam ser definidos/inferidos
int calcular_area(int largura, int altura) {
  return largura * altura;
}

// Chamada da função (dentro de main ou outra função)
int main() {
  int area_retangulo = calcular_area(10, 5);
  printf("%d", area_retangulo);
  return 0;
}
```
*Nota: O compilador CSL precisará inferir ou exigir a declaração dos tipos de retorno e parâmetros das funções para gerar o código C correspondente.* 

## Considerações Finais

Este estudo focado no escopo do CSL visa guiar a implementação do compilador, mostrando como as construções Ruby selecionadas podem ser mapeadas para a linguagem C. A tradução exigirá atenção à tipagem estática do C e ao mapeamento correto de operações e estruturas de controle.
