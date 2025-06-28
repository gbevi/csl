#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tipos simplificados para o teste
typedef enum {
    CONST_NODE,
    ID_NODE,
    SWITCH_NODE,
    CASE_NODE,
    RETURN_NODE,
} NoAST_Type;

typedef struct NoAST {
    NoAST_Type type;
    void *data;
    struct NoAST *esquerda; // geralmente usado para lista, filho, etc
    struct NoAST *direita;  // idem
} NoAST;

typedef struct {
    int val;
} NoAST_Const;

typedef struct {
    char *name;
} NoAST_Id;

typedef struct {
    NoAST *expr;       // expressão do switch
    NoAST *case_list;  // lista ligada de cases
    NoAST *default_case; // case default (pode ser NULL)
} NoAST_Switch;

typedef struct {
    int case_value;  // valor do case
    NoAST *stmt;     // statement dentro do case
    struct NoAST *next_case; // próximo case na lista
} NoAST_Case;

typedef struct {
    NoAST *ret_expr; // expressão do return
} NoAST_Return;

// Funções para criar nós

NoAST* criarNoConst(int val) {
    NoAST* no = malloc(sizeof(NoAST));
    NoAST_Const* c = malloc(sizeof(NoAST_Const));
    c->val = val;
    no->type = CONST_NODE;
    no->data = c;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

NoAST* criarNoReturn(NoAST* expr) {
    NoAST* no = malloc(sizeof(NoAST));
    NoAST_Return* r = malloc(sizeof(NoAST_Return));
    r->ret_expr = expr;
    no->type = RETURN_NODE;
    no->data = r;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

NoAST* criarNoCase(int val, NoAST* stmt) {
    NoAST* no = malloc(sizeof(NoAST));
    NoAST_Case* c = malloc(sizeof(NoAST_Case));
    c->case_value = val;
    c->stmt = stmt;
    c->next_case = NULL;
    no->type = CASE_NODE;
    no->data = c;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

NoAST* criarNoSwitch(NoAST* expr, NoAST* case_list, NoAST* default_case) {
    NoAST* no = malloc(sizeof(NoAST));
    NoAST_Switch* s = malloc(sizeof(NoAST_Switch));
    s->expr = expr;
    s->case_list = case_list;
    s->default_case = default_case;
    no->type = SWITCH_NODE;
    no->data = s;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

// Função simples para concatenar cases na lista ligada
void adicionarCase(NoAST* lista, NoAST* novo_case) {
    if (!lista) return;
    NoAST_Case* c = (NoAST_Case*)lista->data;
    NoAST* atual = lista;
    while (c->next_case) {
        atual = c->next_case;
        c = (NoAST_Case*)atual->data;
    }
    c->next_case = novo_case;
}

// Função de geração de código simplificada para teste

void gerarStatement(NoAST* no) {
    if (!no) return;
    switch(no->type) {
        case CONST_NODE: {
            NoAST_Const* c = (NoAST_Const*)no->data;
            printf("%d", c->val);
            break;
        }
        case RETURN_NODE: {
            NoAST_Return* r = (NoAST_Return*)no->data;
            printf("return ");
            gerarStatement(r->ret_expr);
            printf(";\n");
            break;
        }
        case CASE_NODE: {
            NoAST_Case* c = (NoAST_Case*)no->data;
            printf("case %d:\n", c->case_value);
            gerarStatement(c->stmt);
            break;
        }
        case SWITCH_NODE: {
            NoAST_Switch* s = (NoAST_Switch*)no->data;
            printf("switch (");
            gerarStatement(s->expr);
            printf(") {\n");

            // Cases
            NoAST* c = s->case_list;
            while (c) {
                gerarStatement(c);
                NoAST_Case* cc = (NoAST_Case*)c->data;
                c = cc->next_case;
            }

            // Default
            if (s->default_case) {
                printf("default:\n");
                gerarStatement(s->default_case);
            }
            printf("}\n");
            break;
        }
        default:
            printf("/* nó não tratado */\n");
    }
}

int main() {
    // construir a AST do switch

    NoAST* expr = criarNoConst(1);  // switch(1)

    NoAST* case1 = criarNoCase(1, criarNoReturn(criarNoConst(1)));
    NoAST* case2 = criarNoCase(2, criarNoReturn(criarNoConst(2)));
    // liga os cases na lista
    adicionarCase(case1, case2);

    NoAST* default_case = criarNoReturn(criarNoConst(0));

    NoAST* switch_node = criarNoSwitch(expr, case1, default_case);

    // gerar código
    gerarStatement(switch_node);

    // liberar memória omitido

    return 0;
}
