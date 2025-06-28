#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Definições simplificadas ---

typedef enum {
    CONST_NODE,
    ID_NODE,
    RETURN_NODE,
    SWITCH_NODE,
    CASE_NODE,  // só pra exemplo
} NoAST_Type;

typedef enum {
    TIPO_INT,
} TipoConst;

typedef union {
    int valint;
} Value;

typedef struct NoAST NoAST;

typedef struct {
    TipoConst const_type;
    Value val;
} NoAST_Const;

typedef struct {
    char *name;
} NoAST_Id;

typedef struct {
    NoAST *return_expr;
} NoAST_Return;

typedef struct NoAST_Case {
    NoAST *case_value;   // expressão do case (ex: constante)
    NoAST *case_body;    // corpo do case (ex: return)
    struct NoAST_Case *next;
} NoAST_Case;

typedef struct {
    NoAST *expr;           // expressão do switch (ex: variável)
    NoAST_Case *cases;     // lista ligada de cases
    NoAST *default_case;   // default case (opcional)
} NoAST_Switch;

struct NoAST {
    NoAST_Type type;
    void *data;
    NoAST *esquerda;
    NoAST *direita;
};

// --- Funções de criação simplificadas ---

NoAST* criarNoConst(int val) {
    NoAST* no = malloc(sizeof(NoAST));
    NoAST_Const* c = malloc(sizeof(NoAST_Const));
    c->const_type = TIPO_INT;
    c->val.valint = val;
    no->type = CONST_NODE;
    no->data = c;
    no->esquerda = no->direita = NULL;
    return no;
}

NoAST* criarNoId(const char* nome) {
    NoAST* no = malloc(sizeof(NoAST));
    NoAST_Id* id = malloc(sizeof(NoAST_Id));
    id->name = strdup(nome);
    no->type = ID_NODE;
    no->data = id;
    no->esquerda = no->direita = NULL;
    return no;
}

NoAST* criarNoReturn(NoAST* expr) {
    NoAST* no = malloc(sizeof(NoAST));
    NoAST_Return* ret = malloc(sizeof(NoAST_Return));
    ret->return_expr = expr;
    no->type = RETURN_NODE;
    no->data = ret;
    no->esquerda = no->direita = NULL;
    return no;
}

NoAST_Case* criarNoCase(NoAST* valor, NoAST* corpo) {
    NoAST_Case* c = malloc(sizeof(NoAST_Case));
    c->case_value = valor;
    c->case_body = corpo;
    c->next = NULL;
    return c;
}

NoAST* criarNoSwitch(NoAST* expr, NoAST_Case* cases, NoAST* default_case) {
    NoAST* no = malloc(sizeof(NoAST));
    NoAST_Switch* sw = malloc(sizeof(NoAST_Switch));
    sw->expr = expr;
    sw->cases = cases;
    sw->default_case = default_case;
    no->type = SWITCH_NODE;
    no->data = sw;
    no->esquerda = no->direita = NULL;
    return no;
}

// --- Função geradora simples ---

void gerarNoAST(NoAST* no);

void gerarSwitch(NoAST_Switch* sw) {
    printf("switch(");
    gerarNoAST(sw->expr);
    printf(") {\n");

    NoAST_Case* c = sw->cases;
    while (c) {
        printf("    case ");
        gerarNoAST(c->case_value);
        printf(":\n        ");
        gerarNoAST(c->case_body);
        printf("\n        break;\n");
        c = c->next;
    }

    if (sw->default_case) {
        printf("    default:\n        ");
        gerarNoAST(sw->default_case);
        printf("\n        break;\n");
    }

    printf("}\n");
}

void gerarNoAST(NoAST* no) {
    if (!no) return;

    switch (no->type) {
        case CONST_NODE: {
            NoAST_Const* c = (NoAST_Const*)no->data;
            printf("%d", c->val.valint);
            break;
        }
        case ID_NODE: {
            NoAST_Id* id = (NoAST_Id*)no->data;
            printf("%s", id->name);
            break;
        }
        case RETURN_NODE: {
            NoAST_Return* ret = (NoAST_Return*)no->data;
            printf("return ");
            gerarNoAST(ret->return_expr);
            printf(";");
            break;
        }
        case SWITCH_NODE: {
            NoAST_Switch* sw = (NoAST_Switch*)no->data;
            gerarSwitch(sw);
            break;
        }
        default:
            printf("/* Nodo nao implementado */");
    }
}

// --- MAIN ---

int main() {
    // switch (x) {
    //   case 1: return 1;
    //   case 2: return 2;
    //   default: return 0;
    // }

    NoAST* expr_switch = criarNoId("x");

    NoAST* case1_val = criarNoConst(1);
    NoAST* case1_body = criarNoReturn(criarNoConst(1));
    NoAST_Case* case1 = criarNoCase(case1_val, case1_body);

    NoAST* case2_val = criarNoConst(2);
    NoAST* case2_body = criarNoReturn(criarNoConst(2));
    NoAST_Case* case2 = criarNoCase(case2_val, case2_body);
    case1->next = case2;

    NoAST* default_body = criarNoReturn(criarNoConst(0));

    NoAST* switch_node = criarNoSwitch(expr_switch, case1, default_body);

    printf("#include <stdio.h>\n\nint foo(int x) {\n");
    gerarNoAST(switch_node);
    printf("}\n");

    return 0;
}
