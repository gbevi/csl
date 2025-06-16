%{
//#define YYDEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ST/tabela.h"
#include "ST/ast.h"

extern FILE *yyin;
extern int yylineno;

int tem_erro = 0;

void yyerror(const char *s);
int yylex(void);
NoAST *raiz;

void inicializarTabelaBuiltins() {
    if (current_scope == NULL || current_scope->symbol_table == NULL) {
        fprintf(stderr, "Erro: Escopo global nao inicializado para adicionar built-ins.\n");
        exit(EXIT_FAILURE);
    }
    inserirNaTabela(current_scope->symbol_table, "print", "builtin_function");
    inserirNaTabela(current_scope->symbol_table, "puts", "builtin_function");
    inserirNaTabela(current_scope->symbol_table, "scan", "builtin_function");
}

%}

%code requires {
    #include "ST/tabela.h"
    #include "ST/ast.h"
}

%union {
    char char_val_token;
    int int_val_token;  
    double double_val_token;
    char* str_val_token; 

    Simbolo* symtab_item;
    NoAST* node;
    Parametro* param_list_head;
}

%token <str_val_token> STRING ID
%token <int_val_token> NUM BOOL_LITERAL
%token <double_val_token> FLOAT_LITERAL
%token <char_val_token> CHAR_LITERAL

%token PUTS PRINT GETS IF ELSE ELSIF WHILE FOR IN DO END DEF RETURN
%token EQ NEQ LE GE LT GT ASSIGN PLUS MINUS MULTIPLY DIVIDE RANGE_EXCLUSIVE RANGE_INCLUSIVE
%token LPAREN RPAREN LBRACE RBRACE COMMA SEMICOLON
%token AND OR NOT

%token EOL

%right ASSIGN
%left  OR
%left  AND
%left  EQ NEQ
%left  LT GT LE GE
%left RANGE_INCLUSIVE RANGE_EXCLUSIVE
%left  PLUS MINUS
%left  MULTIPLY DIVIDE
%right NOT
%right UMINUS
%nonassoc CALL
%nonassoc LPAREN_GROUP

%type <node> program statements statements_list stmt expr
%type <param_list_head> param_list param
%type <node> func_call for_init_block func_declaration_and_scope
%type <node> expr_list
%type <node> atom_expr
%type <node> call_or_id_expr 
%type <node> elsif_else_parts
%type <node> elsif_clause_list elsif_clause optional_else_part else_clause
%type <node> optional_args optional_args_list optional_empty_paren
%type <node> opt_terminators

%%

// permite um programa com statements ou vazio antes do EOF
program:
    statements YYEOF { raiz = $1; } 
    ;

// zero ou mais statements, cada um com seus terminadores
statements:
    { $$ = NULL; } // permite programa vazio
    | statements_list { $$ = $1; } // ou uma lista de statements
;

statements_list:
    stmt opt_terminators { $$ = $1; } // um unico statement seguido de terminadores
    | statements_list stmt opt_terminators { $$ = criarNo(BASIC_NODE, $1, $2); } // multiplos statements
;

opt_terminators:
    { }
    | opt_terminators stmt_terminator { } // zero ou mais terminadores
;

stmt_terminator:
    EOL     { } // new line
    | SEMICOLON { } // ponto e virgula
;

stmt:
    expr  { $$ = $1; }
    | PUTS optional_args        {
        Simbolo *puts_entry = buscarSimbolo("puts");
        if (!puts_entry) {
            inserirNaTabela(current_scope->symbol_table, "puts", "builtin_function");
            puts_entry = buscarSimbolo("puts");
        }
        $$ = criarNoFuncCall(puts_entry, $2);
    }
    | PRINT optional_args_list {
        Simbolo *print_entry = buscarSimbolo("print");
        if (!print_entry) {
            inserirNaTabela(current_scope->symbol_table, "print", "builtin_function");
            print_entry = buscarSimbolo("print");
        }
        $$ = criarNoFuncCall(print_entry, $2);
    }
    | GETS optional_empty_paren {
        Simbolo *gets_entry = buscarSimbolo("gets");
        if (!gets_entry) {
            inserirNaTabela(current_scope->symbol_table, "gets", "builtin_function");
            gets_entry = buscarSimbolo("gets");
        }
        $$ = criarNoFuncCall(gets_entry, NULL);
    }
    | IF expr EOL statements elsif_else_parts END {
        $$ = criarNoIfElseChain(IF_NODE, $2, $4, $5);
    }
    | FOR for_init_block statements END {
        NoAST *header_node = $2;
        NoAST *for_var_node = header_node->esquerda; 
        NoAST *range_expr = header_node->direita;
        NoAST *body_statements = $3;

        $$ = criarNoForIn(for_var_node, range_expr, body_statements);
        
        exitScope();
        free(header_node); 
    }
    | WHILE expr DO EOL statements END {
        $$ = criarNoWhile($2, $5);
    }
    | DEF func_declaration_and_scope EOL statements END
    {
        Simbolo *func_entry = $2;
        Parametro *params = func_entry->parameters; 
        $$ = criarNoFuncDef(func_entry, params, $4);
        exitScope();
    }
    | RETURN expr {
        $$ = criarNoReturn($2); 
    }
    | RETURN { 
        $$ = criarNoReturn(NULL);
    }
    ;

optional_args: // para 'puts', 'print' (um unico argumento)
    expr               { $$ = $1; } // ex: puts "hello"
    | LPAREN expr RPAREN { $$ = $2; } // ex: puts("hello")
    ;

optional_args_list: // para 'print' (lista de argumentos)
    expr_list               { $$ = $1; } // ex: print "a", "b"
    | LPAREN expr_list RPAREN { $$ = $2; } // ex: print("a", "b")
    ;

optional_empty_paren: // para 'gets' (parênteses vazios opcionais)
    { $$ = NULL; } // ex: gets
    | LPAREN RPAREN    { $$ = NULL; } // ex: gets()
    ;

for_init_block:
    ID IN expr DO EOL 
    {
        char *for_var_name = strdup($1); 
        if (!for_var_name) { yyerror("Memory allocation error."); YYABORT; }

        enterScope();

        inserirNaTabela(current_scope->symbol_table, for_var_name, "loop_variable"); 

        Simbolo *loop_item_entry = buscarNaTabela(current_scope->symbol_table, for_var_name);
        if (!loop_item_entry) {
            fprintf(stderr, "Erro interno CRITICO: Simbolo '%s' nao encontrado APOS insercao no escopo FOR (linha %d).\n", for_var_name, yylineno);
            tem_erro = 1; $$ = NULL; free(for_var_name); exitScope(); return;
        }

        $$ = criarNo(FOR_HEADER_NODE, criarNoId(strdup(for_var_name), loop_item_entry), $3);
        free(for_var_name); 
    }
;

func_declaration_and_scope:
    ID LPAREN param_list RPAREN // consome o nome da func e a lista de parâmetros
    {
        char *func_name = strdup($1);
        if (!func_name) { yyerror("Memory allocation error."); YYABORT; return NULL; }

        // registra o nome da função no escopo atual
        Simbolo *func_entry = buscarSimbolo(func_name);
        if (func_entry != NULL) {
            // se o símbolo já existe e é ou não é uma função
            if (strcmp(func_entry->tipo, "function") != 0 && strcmp(func_entry->tipo, "builtin_function") != 0) {
                fprintf(stderr, "Erro semântico na linha %d: O nome '%s' já está em uso como '%s'. Redefinição como função não permitida.\n", yylineno, func_name, func_entry->tipo);
                tem_erro = 1; $$ = NULL; free(func_name); YYABORT; return NULL;
            }
            fprintf(stderr, "Erro semântico na linha %d: Função '%s' já declarada. Redefinição não permitida.\n", yylineno, func_name);
            tem_erro = 1; $$ = NULL; free(func_name); YYABORT; return NULL;
        } else {
            // insere o nome da função na tabela de símbolos do escopo global
            inserirNaTabela(current_scope->symbol_table, func_name, "function");
            func_entry = buscarSimbolo(func_name); 
            if (!func_entry) { fprintf(stderr, "Erro interno: Símbolo '%s' da funcao nao encontrado APOS insercao (linha %d).\n", func_name, yylineno); tem_erro = 1; YYABORT; return NULL; }
            func_entry->parameters = $3;
            $$ = func_entry;
            free(func_name);
        }

        // entra no escopo da função
        enterScope();

        // insere os parametros no novo escopo 
        Parametro *current_param = $3; 
        while (current_param != NULL) {
            if (buscarNaTabela(current_scope->symbol_table, current_param->nome) != NULL) {
                fprintf(stderr, "Erro semântico na linha %d: Parâmetro '%s' duplicado na função '%s'.\n", yylineno, current_param->nome, func_entry->nome);
                tem_erro = 1;
            } else {
                inserirNaTabela(current_scope->symbol_table, current_param->nome, "parameter");
            }
            current_param = current_param->prox;
        }
    }
;

param_list:
    param                       { $$ = $1; }
    | param_list COMMA param    {
                                    Parametro *head = $1;
                                    Parametro *current = head;
                                    while(current->prox != NULL) {
                                        current = current->prox;
                                    }
                                    current->prox = $3;
                                    $$ = head;
                                }
    ;

param:
    ID                          {
                                    Parametro *p = malloc(sizeof(Parametro));
                                    if (!p) { yyerror("Erro de alocação de memória para parâmetro."); YYABORT; }
                                    strncpy(p->nome, $1, sizeof(p->nome) - 1);
                                    p->nome[sizeof(p->nome) - 1] = '\0';
                                    p->prox = NULL;
                                    $$ = p; 
                                }
    ;


expr:
    atom_expr
    | call_or_id_expr
    | ID ASSIGN expr            {
                                    char *var_name = strdup($1);
                                    if (!var_name) { yyerror("Memory allocation error."); YYABORT; }

                                    Simbolo *id_entry = buscarSimbolo(var_name);
                                    if (!id_entry) {
                                        inserirNaTabela(current_scope->symbol_table, var_name, "variable");
                                        id_entry = buscarSimbolo(var_name);
                                    }
                                    $$ = criarNoAssign(id_entry, $3);
                                    free(var_name); 
                                }
    | expr PLUS expr            { $$ = criarNoArithm(OP_ADICAO, $1, $3); }
    | expr MINUS expr           { $$ = criarNoArithm(OP_SUBTRACAO, $1, $3); }
    | expr MULTIPLY expr        { $$ = criarNoArithm(OP_MULTIPLICACAO, $1, $3); }
    | expr DIVIDE expr          { $$ = criarNoArithm(OP_DIVISAO, $1, $3); }
    | expr AND expr             { $$ = criarNoLogic(OP_AND, $1, $3); }
    | expr OR expr              { $$ = criarNoLogic(OP_OR, $1, $3); }
    | NOT expr %prec NOT          { $$ = criarNoLogic(OP_NOT, $2, NULL); }
    | expr EQ expr              { $$ = criarNoRel(OP_REL_EQ, $1, $3); }
    | expr NEQ expr             { $$ = criarNoRel(OP_REL_NEQ, $1, $3); }
    | expr LT expr              { $$ = criarNoRel(OP_REL_LT, $1, $3); }
    | expr GT expr              { $$ = criarNoRel(OP_REL_GT, $1, $3); }
    | expr LE expr              { $$ = criarNoRel(OP_REL_LE, $1, $3); }
    | expr GE expr              { $$ = criarNoRel(OP_REL_GE, $1, $3); }
    | expr RANGE_INCLUSIVE expr { $$ = criarNoRange($1, $3, 0); }
    | expr RANGE_EXCLUSIVE expr { $$ = criarNoRange($1, $3, 1); }
    | LPAREN expr RPAREN %prec LPAREN_GROUP { $$ = $2; }
    ;

atom_expr: // pra expressões literais
    NUM                         { $$ = criarNoConst(TIPO_INT, (Value){.valint = $1}); }
    | STRING                    { $$ = criarNoConst(TIPO_STRING, (Value){.valstring = strdup($1)}); }
    | FLOAT_LITERAL             { $$ = criarNoConst(TIPO_DOUBLE, (Value){.valfloat = $1}); }
    | BOOL_LITERAL              { $$ = criarNoConst(TIPO_BOOLEAN, (Value){.valint = $1}); }
    | CHAR_LITERAL              { $$ = criarNoConst(TIPO_CHAR, (Value){.valchar = $1}); }
    ;

// call_or_id_expr foi criado para elimitar o shift/reduce q estava sendo
// causado porque o bison estava enxergando ambiguidades em ID e ID LPAREN
// q poderia ser uma expr ou uma func_call

call_or_id_expr:
    ID                {
                        char *id_name = strdup($1);
                        if (!id_name) { yyerror("Memory allocation error."); YYABORT; }

                        Simbolo *id_entry = buscarSimbolo(id_name);
                        if (!id_entry) {
                            fprintf(stderr, "Erro semântico na linha %d: Uso de variável não definida '%s'.\n", yylineno, id_name);
                            tem_erro = 1;
                            $$ = NULL;
                            free(id_name); 
                        } else {
                            $$ = criarNoId(strdup(id_name), id_entry);
                            free(id_name);
                        }
                    }
    | func_call %prec CALL { $$ = $1; }
    ;

func_call:
    ID LPAREN RPAREN {
            char *func_name = strdup($1);
            if (!func_name) { yyerror("Memory allocation error."); YYABORT; }

            Simbolo *func_entry = buscarSimbolo(func_name);
            if (!func_entry) {
                fprintf(stderr, "Erro semântico na linha %d: Função '%s' não declarada.\n", yylineno, func_name);
                tem_erro = 1;
                $$ = NULL;
            } else {
                $$ = criarNoFuncCall(func_entry, NULL);
            }
            free(func_name); 
        }
    | ID LPAREN expr_list RPAREN {
            char *func_name = strdup($1);
            if (!func_name) { yyerror("Memory allocation error."); YYABORT; }

            Simbolo *func_entry = buscarSimbolo(func_name);
            if (!func_entry) {
                fprintf(stderr, "Erro semântico na linha %d: Função '%s' não declarada.\n", yylineno, func_name);
                tem_erro = 1;
                $$ = NULL;
            } else {
                $$ = criarNoFuncCall(func_entry, $3);
            }
            free(func_name);
        }
    ;

expr_list: // lista de expressoes (para argumentos de funções)
    expr                     { $$ = criarNoExprList($1, NULL); }
    | expr_list COMMA expr   { $$ = criarNoExprList($3, $1); }
    ;

// regras para IF/ELSIF/ELSE
elsif_else_parts:
    elsif_clause_list optional_else_part {
        // $1 é a cabeça da cadeia de elsifs (pode ser NULL)
        // $2 é o nó do else (pode ser NULL)

        if ($1 && $2) {
            // se tem elsifs e um else, conecta o último elsif ao else
            NoAST *current = $1;
            NoAST_if *current_data = (NoAST_if *)(current->data);
            while (current_data->next_branch != NULL) {
                current = current_data->next_branch;
                current_data = (NoAST_if *)(current->data);
            }
            current_data->next_branch = $2;
            $$ = $1; 
        } else if ($1) {
            // caso 2: só tem elsifs
            $$ = $1;
        } else if ($2) {
            // caso 3: tem else
            $$ = $2;
        } else {
            // último caso: tem nem elsifs nem else
            $$ = NULL;
        }
    }
    ;

// regra para lista de elsif (pode ser vazia)
elsif_clause_list:
    elsif_clause elsif_clause_list {
        // $1: o elsif atual (o primeiro desta regra)
        // $2: a cabeça do resto da lista de elsifs
        NoAST_if *current_elsif_data = (NoAST_if *)($1->data);
        current_elsif_data->next_branch = $2; // Faz o elsif atual apontar para o próximo
        $$ = $1; // Retorna o elsif atual
    }
    |   {
        $$ = NULL; 
    }
    ;

// regra para uma unica clausula ELSIF
elsif_clause:
    ELSIF expr EOL statements{
        // $2: condição do ELSIF
        // $4: bloco de statements do ELSIF
        // o último parâmetro é null pq será ligado na regra 'elsif_clause_list'
        $$ = criarNoIfElseChain(ELSIF_NODE, $2, $4, NULL);
    }
    ;

optional_else_part:
    else_clause { $$ = $1; } 
    |   { $$ = NULL; }
    ;

else_clause:
    ELSE EOL statements {
        // $3: bloco de statements do ELSE
        // condição é NULL para ELSE
        // o último parâmetro é null porque else é o final da cadeia
        $$ = criarNoIfElseChain(ELSE_NODE, NULL, $3, NULL);
    }
    ;

%%


void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático na linha %d: %s\n", yylineno, s);
    tem_erro = 1;
}

int main(int argc, char **argv) {
    // yydebug = 1;
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Não foi possível abrir o arquivo: %s\n", argv[1]);
            return 1;
        }
    } else {
        fprintf(stderr, "Uso: %s <arquivo_entrada>\n", argv[0]);
        return 1;
    }

    enterScope(); // adicionado pra criar o escopo global
    inicializarTabelaBuiltins();

    yyparse();

    if (tem_erro) {
        fprintf(stderr, "Erros sintáticos ou semânticos encontrados. AST não foi gerada completamente.\n");
        exitScope();
        if (yyin != stdin) {
            fclose(yyin);
        }
        return 1;
    }

    if (!tem_erro && raiz != NULL) {
        printf("\nAnálise Sintática Concluída. AST gerada:\n");
        imprimirAST(raiz, 0);
        printf("\n");
        imprimirTabelaEscopos();
    } else if (tem_erro) {
        fprintf(stderr, "Erros sintáticos ou semânticos encontrados. AST não foi gerada completamente.\n");
    } else {
        printf("Programa vazio. Nenhuma AST gerada.\n");
    }

    exitScope(); // antes de sair do programa, sai do escopo global tbm
    if (current_scope != NULL) {
        fprintf(stderr, "Erro de escopo: Nem todos os escopos foram fechados corretamente.\n");
    }

    if (yyin != stdin) {
        fclose(yyin);
    }
    return 0;
}