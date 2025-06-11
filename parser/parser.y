%{
#define YYDEBUG 1

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
    inserirSimbolo("print", "function");
    inserirSimbolo("puts", "function");
    inserirSimbolo("scan", "function");
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

%left  OR
%left  AND
%left  EQ NEQ LT GT LE GE
%left RANGE_INCLUSIVE RANGE_EXCLUSIVE
%left  PLUS MINUS
%left  MULTIPLY DIVIDE
%right NOT UMINUS
%right ASSIGN
%nonassoc LPAREN_GROUP
%nonassoc CALL

%type <node> program statements stmt_terminator stmt expr
%type <param_list_head> param_list param
%type <node> func_call
%type <node> expr_list
%type <node> atom_expr
%type <node> call_or_id_expr
%type <node> elsif_else_parts
%type <node> elsif_clause_list
%type <node> elsif_clause
%type <node> optional_else_part
%type <node> else_clause

%%

program:
    statements YYEOF            { raiz = $1; }
    | YYEOF                     { raiz = NULL; }
    ;

statements:
    stmt { $$ = $1; }
    | statements stmt { $$ = criarNo(BASIC_NODE, $1, $2); }
    | EOL { $$ = NULL; }
    | statements EOL { $$ = $1; }
    ;

// adicionado para permitir que o programa com statemets possa
// encerrar com EOL ou EOF
stmt_terminator:
    EOL { }
    | YYEOF { }
    ;

stmt:
    expr stmt_terminator { $$ = $1; }
    | PUTS LPAREN expr RPAREN stmt_terminator {
        Simbolo *puts_entry = buscarSimbolo("puts");
        if (!puts_entry) {
             inserirSimbolo("puts", "builtin_function");
             puts_entry = buscarSimbolo("puts");
        }
        $$ = criarNoFuncCall(puts_entry, $3);
    }
    | PRINT LPAREN expr_list RPAREN stmt_terminator {
        Simbolo *print_entry = buscarSimbolo("print");
        if (!print_entry) {
             inserirSimbolo("print", "builtin_function");
             print_entry = buscarSimbolo("print");
        }
        $$ = criarNoFuncCall(print_entry, $3);
    }
    | GETS LPAREN RPAREN stmt_terminator {
        Simbolo *gets_entry = buscarSimbolo("gets");
        if (!gets_entry) {
             inserirSimbolo("gets", "builtin_function");
             gets_entry = buscarSimbolo("gets");
        }
        $$ = criarNoFuncCall(gets_entry, NULL);
    }
    | IF expr EOL statements elsif_else_parts END stmt_terminator {
        $$ = criarNoIfElseChain(IF_NODE, $2, $4, $5);
    }
    | FOR ID IN expr DO EOL statements END stmt_terminator { // for com range
        $$ = criarNoForIn(criarNoId($2, NULL), $4, $7);
    }
    | WHILE expr DO EOL statements END stmt_terminator {
        $$ = criarNoWhile($2, $5);
    }
    ;
    | DEF ID LPAREN param_list RPAREN DO EOL statements END stmt_terminator
            {
                Simbolo *func_entry = buscarSimbolo($2);
                if (func_entry != NULL) {
                    fprintf(stderr, "Erro semântico na linha %d: O nome '%s' já está em uso (função ou variável). Redefinição não permitida.\n", yylineno, $2);
                    tem_erro = 1;
                    $$ = NULL;
                } else {
                    inserirSimbolo($2, "function");
                    func_entry = buscarSimbolo($2);

                    enterScope(); // aq entramos no escopo da funcao

                    Parametro *current_param = $4; 
                    while (current_param != NULL) {
                        if (buscarNaTabela(current_scope->symbol_table, current_param->nome) != NULL) {
                            fprintf(stderr, "Erro semântico na linha %d: Parâmetro '%s' duplicado na função '%s'.\n", yylineno, current_param->nome, func_entry->nome);
                            tem_erro = 1;
                        } else {
                            inserirSimbolo(current_param->nome, "parameter");
                        }
                        current_param = current_param->prox;
                    }
                    register_function_parameters(func_entry, $4); 

                    $$ = criarNoFuncDef(func_entry, $4, $8);
                    exitScope(); // Sai do escopo da função
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
                                    Simbolo *id_entry = buscarSimbolo($1);
                                    if (!id_entry) {
                                        inserirSimbolo($1, "variable");
                                        id_entry = buscarSimbolo($1);
                                    }
                                    $$ = criarNoAssign((void*)id_entry, $3);
                                }
    | expr PLUS expr            { $$ = criarNoArithm(OP_ADICAO, $1, $3); }
    | expr MINUS expr           { $$ = criarNoArithm(OP_SUBTRACAO, $1, $3); }
    | expr MULTIPLY expr        { $$ = criarNoArithm(OP_MULTIPLICACAO, $1, $3); }
    | expr DIVIDE expr          { $$ = criarNoArithm(OP_DIVISAO, $1, $3); }
    | expr AND expr             { $$ = criarNoLogic(OP_AND, $1, $3); }
    | expr OR expr              { $$ = criarNoLogic(OP_OR, $1, $3); }
    | NOT expr %prec UMINUS     { $$ = criarNoLogic(OP_NOT, $2, NULL); }
    | expr EQ expr              { $$ = criarNoRel(OP_REL_EQ, $1, $3); }
    | expr NEQ expr             { $$ = criarNoRel(OP_REL_NEQ, $1, $3); }
    | expr LT expr              { $$ = criarNoRel(OP_REL_LT, $1, $3); }
    | expr GT expr              { $$ = criarNoRel(OP_REL_GT, $1, $3); }
    | expr LE expr              { $$ = criarNoRel(OP_REL_LE, $1, $3); }
    | expr GE expr              { $$ = criarNoRel(OP_REL_GE, $1, $3); }
    | expr RANGE_INCLUSIVE expr { $$ = criarNoRange($1, $3, 0); }
    | expr RANGE_EXCLUSIVE expr { $$ = criarNoRange($1, $3, 1); }
    ;


atom_expr:
    NUM                         { $$ = criarNoConst(TIPO_INT, (Value){.valint = $1}); }
    | STRING                    { $$ = criarNoConst(TIPO_STRING, (Value){.valstring = $1}); }
    | FLOAT_LITERAL             { $$ = criarNoConst(TIPO_DOUBLE, (Value){.valfloat = $1}); }
    | BOOL_LITERAL              { $$ = criarNoConst(TIPO_BOOLEAN, (Value){.valint = $1}); }
    | CHAR_LITERAL              { $$ = criarNoConst(TIPO_CHAR, (Value){.valchar = $1}); }
    ;

// call_or_id_expr foi criado para elimitar o shift/reduce q estava sendo
// causado porque o bison estava enxergando ambiguidades em ID e ID LPAREN
// q poderia ser uma expr ou uma func_call

call_or_id_expr:
    ID                 {
                        Simbolo *id_entry = buscarSimbolo($1);
                        if (!id_entry) {
                            fprintf(stderr, "Erro semântico na linha %d: Uso de variável não definida '%s'.\n", yylineno, $1);
                            $$ = NULL;
                        } else {
                            $$ = criarNoId($1, (void*)id_entry);
                        }
                        }
    | func_call %prec CALL { $$ = $1; }
    ;

func_call:
    ID LPAREN RPAREN {
            Simbolo *func_entry = buscarSimbolo($1);
            if (!func_entry) {
                fprintf(stderr, "Erro semântico na linha %d: Função '%s' não declarada.\n", yylineno, $1);
                tem_erro = 1;
                $$ = NULL;
            } else {
                $$ = criarNoFuncCall(func_entry, NULL);
            }
        }
    | ID LPAREN expr_list RPAREN {
            Simbolo *func_entry = buscarSimbolo($1);
            if (!func_entry) {
                fprintf(stderr, "Erro semântico na linha %d: Função '%s' não declarada.\n", yylineno, $1);
                tem_erro = 1;
                $$ = NULL;
            } else {
                $$ = criarNoFuncCall(func_entry, $3);
            }
        }
    ;

expr_list:
    expr                     { $$ = criarNoExprList($1, NULL); }
    | expr_list COMMA expr   { $$ = criarNoExprList($3, $1); } 
    ;

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
    ELSIF expr EOL statements {
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
    yydebug = 1;
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