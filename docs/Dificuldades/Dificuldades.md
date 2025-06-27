# Dificuldades e Soluções no Desenvolvimento do Compilador

Durante o desenvolvimento do nosso compilador, enfrentamos diversas dificuldades que exigiram pesquisa, estudo e colaboração para serem superadas. Abaixo, listamos os principais desafios enfrentados e como conseguimos contorná-los:

---

## 1. Compreensão da Gramática da Linguagem Ruby

**Dificuldade:**  
Como nenhum membro do grupo tinha experiência prévia com Ruby, nossa primeira dificuldade foi entender a gramática da linguagem.

**Como contornamos:**  
Realizamos um estudo aprofundado sobre Ruby e elaboramos um documento com os principais pontos relevantes para a construção do compilador.

---

## 2. Aprendizado das Ferramentas (Bison e Lexer)

**Dificuldade:**  
Aprender a usar o Bison e o gerador de analisadores léxicos (Lexer) foi um grande desafio no início do projeto.

**Como contornamos:**  
Estudamos materiais e exemplos disponíveis para entender o funcionamento dessas ferramentas e implementamos corretamente as fases de análise léxica e sintática.

---

## 3. Construção da AST (Árvore Sintática Abstrata)

**Dificuldade:**  
Tivemos dificuldades para estruturar os nós e representar corretamente as expressões da linguagem.

**Como contornamos:**  
Pesquisamos exemplos de compiladores existentes, estudamos diferentes abordagens para construção de AST e, com isso, conseguimos avançar no desenvolvimento dessa etapa.

---

## 4. Depuração de Erros nos Testes

**Dificuldade:**  
Foi difícil identificar a origem de muitos erros, pois não sabíamos se estavam na análise léxica, na AST ou em outro componente.

**Como contornamos:**  
Adotamos uma abordagem modular, testando cada componente separadamente. Isso nos ajudou a isolar e corrigir os problemas com mais precisão.

---

## 5. Integração entre os Módulos

**Dificuldade:**  
A divisão do trabalho em duplas dificultou a integração entre os módulos (léxico, parser, AST, tabela de símbolos, etc.), pois foram implementados separadamente ao longo das sprints.

**Como contornamos:**  
Estudamos o código produzido por outros membros, adaptamos partes do código e, quando necessário, refatoramos trechos para garantir compatibilidade entre os módulos.

---

## 6. Implementação dos Laços de Repetição

**Dificuldade:**  
A implementação dos laços `for`, `while` e outros foi um desafio, tanto para estruturá-los na AST quanto para traduzi-los corretamente na geração de código.

**Como contornamos:**  
Pesquisamos como essas estruturas são representadas em compiladores reais e fizemos ajustes na AST para representar esses comandos corretamente.

---

## 7. Geração do Código Final

**Dificuldade:**  
Durante essa fase, surgiram diversos erros relacionados à estrutura da AST e à tradução da linguagem de origem para a linguagem alvo.

**Como contornamos:**  
Revisamos partes anteriores do compilador, realizamos testes e ajustes contínuos até garantir que o código fosse gerado corretamente.

---

## Conclusão

Apesar dos desafios, conseguimos superar as dificuldades com muita pesquisa, comunicação e colaboração em equipe. O desenvolvimento do compilador foi uma experiência de grande aprendizado, que nos permitiu aplicar na prática conceitos fundamentais da construção de linguagens de programação.
