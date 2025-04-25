# Estudo da Linguagem Ruby
## Visão Geral da Linguagem Ruby
Ruby é uma linguagem de programação interpretada, orientada a objetos e de tipagem dinâmica. É conhecida por sua sintaxe limpa e legível, que favorece a produtividade do desenvolvedor. A linguagem permite que tudo seja tratado como objeto, inclusive tipos primitivos, e oferece grande flexibilidade para expressar lógica de programação de forma concisa.

## Adaptação para o Compilador
Dado o escopo do projeto e o tempo disponível, foi selecionado um subconjunto funcional da linguagem Ruby, priorizando aspectos mais utilizados e com tradução direta para a linguagem C. Este estudo visa identificar como essas construções se comportam em Ruby e como serão tratadas pelo compilador desenvolvido.

## Tipos de Dados
Ruby não exige declaração explícita de tipo, pois é dinamicamente tipada. Um mesmo identificador pode receber valores de tipos diferentes ao longo da execução. No entanto, para facilitar a análise semântica e a geração de código C (linguagem estaticamente tipada), foi adotado um sistema de tipagem explícita e estática no compilador.


| Ruby (dinâmico) | Exemplo    | Tradução C           |
|------------------|------------|-----------------------|
| `a = 10`         | `int`      | `int a = 10;`         |
| `b = "abc"`      | `string`   | `char b[] = "abc";`   |
| `c = true`       | `boolean`  | `bool c = true;`      |

## Operações e Expressões


### Operações Aritméticas
Em Ruby, operadores aritméticos são similares aos do C. O compilador mantém essas operações, traduzindo diretamente.

```ruby
a = 3 + 5
```

Traduzido para:

```c
int a = 3 + 5;
```

###  Relacionais e Lógicos

Ruby usa `and`, `or`, `not` como palavras-chave, mas também permite `&&`, `||`, `!`. Para uniformidade, o compilador suporta `and`, `or`, `not`, traduzindo para os equivalentes em C.

| Ruby | C   |
|------|-----|
| and  | &&  |
| or   | \|\| |
| not  | !   |


## Entrada e Saída
Ruby:

```ruby
print "Digite um número: "
x = gets.to_i
```

C (compilador):

```c
printf("Digite um número: ");
scanf("%d", &x);
```

No compilador, print será mapeado para printf e scan para scanf.

## Estruturas de Controle

### Condicional `if` e `else`, `switch`

**Ruby:**
```ruby
if a > b
  print "Maior"
else
  print "Menor"
end
```

**C:**

```c
if (a > b) {
  printf("Maior");
} else {
  printf("Menor");
}
```

### Laços: `for`, `while`, `do while`

**Ruby:**

```ruby
for i in 1..5
  print i
end
```

C:

```c
for (int i = 1; i <= 5; i++) {
  printf("%d", i);
}
```

O compilador traduz essas estruturas diretamente para os equivalentes em C, exigindo um controle explícito de contadores e blocos delimitados por chaves {}.
## Funções

**Ruby:**

```ruby
def soma(a, b)
  return a + b
end
```

C:

```c
int soma(int a, int b) {
  return a + b;
}
```

A definição de funções em Ruby será mapeada para funções padrão em C, com necessidade de declarar tipo de retorno e parâmetros.

## Considerações Finais
O estudo da linguagem Ruby permitiu delimitar claramente o escopo da tradução viável para C. Foram feitas adaptações quanto à tipagem e estrutura de código para permitir uma compilação correta e eficiente. Os exemplos apresentados servem como base para a construção dos analisadores léxico, sintático e semântico.