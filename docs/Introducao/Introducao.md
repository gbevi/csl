# Introdução
Este documento apresenta o desenvolvimento de um compilador para a linguagem Ruby, com tradução para C, realizado como parte do projeto da disciplina Compiladores 1 (2025/1), ministrada pelo professor Sergio Antônio Andrade de Freitas na Universidade de Brasília (UnB). O objetivo do projeto é consolidar os conhecimentos adquiridos ao longo da disciplina por meio da aplicação prática dos principais conceitos de compiladores. Dessa forma, a equipe se dedicará não apenas à implementação do compilador, mas também à análise, planejamento, projeto, documentação e justificativa das decisões técnicas adotadas.

### Motivação
A escolha pela criação de um compilador da linguagem Ruby para C surgiu do interesse da equipe em trabalhar com uma linguagem de alto nível, dinâmica e amplamente conhecida pela simplicidade sintática (Ruby), e traduzir para uma linguagem de mais baixo nível e estruturada (C). Esse contraste entre paradigmas e níveis de abstração oferece um excelente desafio técnico e educacional.

### Objetivo Geral
Desenvolver um compilador funcional que receba como entrada um subconjunto bem definido da linguagem Ruby e produza como saída um programa equivalente em C, com foco em legibilidade, estrutura e semântica corretas.

### Metodologia
Para organização do trabalho, a equipe adotou a metodologia Scrum, com o projeto sendo dividido em sprints semanais. As tarefas são distribuídas de forma equilibrada entre os membros e todas as decisões técnicas são registradas em reuniões semanais e documentadas no repositório do GitHub.

O projeto é composto pelas seguintes atividades principais:

1. Definição da gramática e escopo da linguagem Ruby suportada

2. Análise léxica (scanner) com uso do Flex

3. Análise sintática (parser) com Bison

4. Análise semântica e construção de árvore sintática abstrata (AST)

5. Geração de código intermediário e tradução para C

6. Testes e validação com exemplos práticos

7. Documentação contínua com planejamento, justificativas e dificuldades

# Justificativas

Esta seção apresenta e justifica as principais decisões técnicas adotadas no desenvolvimento do compilador.

### Gramática e Escopo da Linguagem suportada

O Ruby é uma linguagem grande e dinâmica, o que a torna difícil de ser implementada completamente dentro do tempo disponível. Por isso, foi necessário definir um subconjunto da linguagem, focando em funcionalidades essenciais para simplificar o desenvolvimento, os testes e a documentação.

Dessa forma, foi decidido que o compilador a ser desenvolvido suportará: tipos (int, float, double, char, string, boolean), operadores (+, -, *, /, %, ==, !=, <, <=, >, >=, &&, ||, !), funções de entrada e saída (print, scan), estruturas de controle (if, else, for, while) e suporte à definição e chamada de funções, permitindo a reutilização de trechos lógicos.

A escolha desse subconjunto foi feita pensando em um escopo que permita a entrega de um compilador funcional até o dia 27/06.

### Ferramentas Utilizadas

* Flex
* Bison
* GitHub
* Microsoft Teams
* MkDocs
* Visual Studio Code
* WhatsApp

Ferramentas escolhidas por recomendação do professor ou facilidade de uso pela equipe.

### Analisador Léxico

Para a geração do analisador léxico, foi decidido utilizar o Flex.
Essa escolha foi baseada na facilidade de integração com o Bison, na familiaridade adquirida em sala de aula e na recomendação do professor. Além disso, o Flex automatiza a criação do scanner de forma eficiente e confiável.

### Analisador Sintático

Para a construção do analisador sintático, foi decidido utilizar o Bison.
Essa escolha foi baseada na facilidade de integração com o Flex, na orientação recebida em sala de aula e na familiaridade desenvolvida pela equipe, o que proporciona maior segurança e agilidade no desenvolvimento.

### Representação de Código Interno (AST)

### Geração de Código