#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Enum e structs simplificadas para o teste ---

typedef enum {
    CONST_NODE,
    ID_NODE,
    ASSIGN_NODE,
    SWITCH_NODE,
    CASE_LIST_NODE,
    CASE_NODE,
    DEFAULT_NODE,
    RETURN_NODE,
    BASIC_NODE
} NoAST_Type;

typedef enum {
    TIPO_INT,
} TipoConst;

typedef union {
    int valint;
} Value;

typedef struct {
    TipoConst const_type;
    Value val;
} NoAST_Const;

typedef struct {
    char *name;
} NoAST_Id;

typedef struct Simbolo {
    char nome[64];
} Simbolo;

typedef struct NoAST {
    NoAST_Type type;
    void *data;
    struct NoAST *esquerda;
    struct NoAST *direita;
} NoAST;

typedef struct {
    NoAST *expr;  // expressão a ser avaliada no case
    NoAST *corpo; // corpo do case (statements)
} NoAST_Case;

typedef struct NoAST_CaseList {
    NoAST_Case *case_item;
    struct NoAST_CaseList *next;
} NoAST_CaseList;

typedef struct {
    NoAST *expr;            // expressão do switch
    NoAST_CaseList *cases;  // lista ligada de cases
    NoAST *default_case;    // default case
} NoAST_Switch;

// --- Funções para criar nós ---

NoAST* criarNoConstInt(int v) {
    NoAST *no = malloc(sizeof(NoAST));
    NoAST_Const *c = malloc(sizeof(NoAST_Const));
    c->const_type = TIPO_INT;
    c->val.valint = v;
    no->type = CONST_NODE;
    no->data = c;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

NoAST* criarNoReturn(NoAST *expr) {
    NoAST *no = malloc(sizeof(NoAST));
    no->type = RETURN_NODE;
    no->data = expr; // neste teste, só guardamos a expressão diretamente
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

NoAST_Case* criarCase(NoAST *expr, NoAST *corpo) {
    NoAST_Case *c = malloc(sizeof(NoAST_Case));
    c->expr = expr;
    c->corpo = corpo;
    return c;
}

NoAST_CaseList* adicionarCase(NoAST_CaseList *lista, NoAST_Case *novo_case) {
    NoAST_CaseList *no = malloc(sizeof(NoAST_CaseList));
    no->case_item = novo_case;
    no->next = lista;
    return no;
}

NoAST* criarSwitch(NoAST *expr, NoAST_CaseList *cases, NoAST *default_case) {
    NoAST *no = malloc(sizeof(NoAST));
    NoAST_Switch *swt = malloc(sizeof(NoAST_Switch));
    swt->expr = expr;
    swt->cases = cases;
    swt->default_case = default_case;
    no->type = SWITCH_NODE;
    no->data = swt;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

// --- Protótipos ---

void gerarCodigoC(NoAST *raiz, FILE *saida); // sua implementação real

// --- main do teste ---

int main() {
    // Criar expressão do switch: switch(x)
    Simbolo sym_x;
    strcpy(sym_x.nome, "x");
    NoAST_Id *id_x = malloc(sizeof(NoAST_Id));
    id_x->name = sym_x.nome;

    NoAST *expr_x = malloc(sizeof(NoAST));
    expr_x->type = ID_NODE;
    expr_x->data = id_x;
    expr_x->esquerda = NULL;
    expr_x->direita = NULL;

    // Criar cases:
    // case 1: return 1;
    NoAST *ret1 = criarNoReturn(criarNoConstInt(1));
    NoAST_Case *case1 = criarCase(criarNoConstInt(1), ret1);

    // case 2: return 2;
    NoAST *ret2 = criarNoReturn(criarNoConstInt(2));
    NoAST_Case *case2 = criarCase(criarNoConstInt(2), ret2);

    // default: return 0;
    NoAST *ret0 = criarNoReturn(criarNoConstInt(0));

    // Lista ligada dos cases (adiciona à lista para ficar na ordem correta)
    NoAST_CaseList *cases = NULL;
    cases = adicionarCase(cases, case2);
    cases = adicionarCase(cases, case1);

    // Criar nó switch
    NoAST *switch_node = criarSwitch(expr_x, cases, ret0);

    // Gerar código (sua implementação deve suportar SWITCH_NODE)
    gerarCodigoC(switch_node, stdout);

    return 0;
}
