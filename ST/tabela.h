#ifndef TABELA_H
#define TABELA_H
#define SIZE 211
#define MAXTOKENLEN 40
#define MAX_NOME_LEN 50
#define MAX_TIPO_LEN 50
#define MAX_RETURN_TYPE_LEN 50 

typedef struct Parametro {
    char nome[MAX_NOME_LEN];
    char tipo[MAX_TIPO_LEN];
    struct Parametro *prox;
} Parametro;

typedef struct RefList{ 
    int lineno;
    struct RefList *next;
}RefList;

typedef struct Simbolo {
    char nome[MAX_NOME_LEN];
    char tipo[MAX_TIPO_LEN];
	char return_type[MAX_RETURN_TYPE_LEN];
	Parametro *parameters;  // Cabeça da lista de parâmetros para funcoes 
	int num_parameters;
    struct Simbolo *prox;
} Simbolo;

// agora tabela de símbolos é uma lista de símbolos
typedef struct TabelaSimbolos {
    Simbolo *head;
} TabelaSimbolos;

// adicionei essa nova estrutura para representar escopos
// cada escopo possui uma tabela de símbolos e um escopo pai
typedef struct Scope {
    TabelaSimbolos *symbol_table;
    struct Scope *parent;
    int level;
} Scope;

extern Scope *current_scope;


/*
typedef struct list_t{
	char st_name[MAXTOKENLEN];
    int st_size;
    int scope;
    RefList *lines;
    
	int st_ival; double st_fval; char st_sval;
    int st_type;
	int inf_type;
	int *i_vals; double *f_vals; char *s_vals;
	int array_size;
	Param *parameters;
	int num_of_pars;
	struct list_t *next;
}list_t;

typedef struct revisit_queue{
	char *st_name;
	int revisit_type;		
	struct revisit_queue *next;
}revisit_queue;*/

void enterScope();
void exitScope();
TabelaSimbolos *criarTabelaSimbolos();
void inserirNaTabela(TabelaSimbolos *table, const char *nome, const char *tipo);
Simbolo *buscarNaTabela(TabelaSimbolos *table, const char *nome);
void liberarTabelaSimbolos(TabelaSimbolos *table);

Simbolo *buscarSimbolo(char *nome);
void imprimirTabelaEscopos();

void register_function_parameters(Simbolo *func_entry, Parametro *param_head);


/*
static list_t **hash_table;
static revisit_queue *queue;*/

#include "../ST/ast.h" // incluindo ast.h para ter acesso a Parametro*
// void register_function_parameters(Simbolo *func_entry, Parametro *param_head);

#endif