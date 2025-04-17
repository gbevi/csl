# Escopo do Compilador

O compilador desenvolvido neste projeto possui um escopo bem definido, com o objetivo de garantir a viabilidade da implementação dentro do prazo. As funcionalidades contempladas foram escolhidas com base em sua relevância no uso prático da linguagem Ruby e na viabilidade de tradução para a linguagem C.

## Tipos de Dados Suportados

O compilador oferece suporte aos seguintes tipos de dados:

* int;
* float;
* double;
* char;
* string;
* boolean.

## Operações e Expressões
As operações implementadas incluem:

* **Operações aritméticas básicas:** adição (+), subtração (-), multiplicação (*), divisão (/) e módulo (%)

* **Operadores relacionais:** ==, !=, <, <=, >, >=

* **Operadores lógicos:** and, or, not (traduzidos para &&, || e ! em C)

## Entrada e Saída
São suportadas as seguintes funções de entrada e saída:

```print``` — para exibir valores na saída padrão

```scan``` — para leitura de valores da entrada padrão

## Estruturas de Controle
O compilador reconhece e traduz as seguintes estruturas de controle de fluxo:

* **Condicionais:** if e else, switch

* **Laços de repetição:** for, while, do while

## Funções
Por fim, também está incluído no escopo o suporte à definição e chamada de funções, permitindo reutilização de trechos lógicos.

<br>
