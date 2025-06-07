#ifndef TABELA_H
#define TABELA_H
#define SIZE 211
#define MAXTOKENLEN 40
#define BY_VALUE 1
#define BY_REFER 2
#define PARAM_CHECK 1
static list_t **hash_table;
static revisit_queue *queue;

typedef struct Param{
	int par_type;
	char param_name[MAXTOKENLEN];
	
	int ival; double fval; char *st_sval;
	int passing;
}Param;

typedef struct RefList{ 
    int lineno;
    struct RefList *next;
}RefList;

typedef struct simbolo {
    char nome[32];
    char tipo[16];
    struct simbolo *prox;
} Simbolo;

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
}revisit_queue;

void inserirSimbolo(char *nome, char *tipo);
Simbolo *buscarSimbolo(char *nome);
void imprimirTabela();

#endif