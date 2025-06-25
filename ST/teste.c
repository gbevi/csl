// Arquivo: teste.c
// Teste completo para gerar código C com FUNC_DEF_NODE, FOR_HEADER_NODE e RETURN_NODE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Definições simplificadas (copie/adapte da sua ast.h e tabela.h) ---

typedef enum {
    CONST_NODE,
    ID_NODE,
    ASSIGN_NODE,
    REL_OP_NODE,
    ARITHM_NODE,
    RETURN_NODE,
    FOR_HEADER_NODE,
    FUNC_DEF_NODE,
    BASIC_NODE
} NoAST_Type;

typedef enum {
    TIPO_INT,
    // ... outros tipos se quiser
} TipoConst;

typedef enum {
    OP_REL_LT,
    OP_ADICAO,
    // ... outros operadores
} OpType;

typedef union {
    int valint;
    // ... outros valores
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

typedef struct {
    Simbolo *target_entry;
    struct NoAST *value_expr;
} NoAST_Assign;

typedef struct {
    OpType op;
    struct NoAST *esquerda;
    struct NoAST *direita;
} NoAST_Rel;

typedef struct {
    OpType op;
    struct NoAST *esquerda;
    struct NoAST *direita;
} NoAST_Arithm;

typedef struct {
    struct NoAST *return_expr;
} NoAST_Return;

typedef struct {
    struct NoAST *init;
    struct NoAST *cond;
    struct NoAST *iter;
    struct NoAST *body;
} NoAST_ForHeader;

typedef struct {
    Simbolo *func_id;
    struct NoAST *body;
} NoAST_FuncDef;

typedef struct NoAST {
    NoAST_Type type;
    void *data;
    struct NoAST *esquerda;
    struct NoAST *direita;
} NoAST;

// --- Protótipos das funções que vamos implementar abaixo ---

NoAST* criarNoConst(TipoConst tipo, Value val);
NoAST* criarNoId(const char* nome, Simbolo* simbolo);
NoAST* criarNoAssign(Simbolo* simbolo, NoAST* valor);
NoAST* criarNoRel(OpType op, NoAST* esq, NoAST* dir);
NoAST* criarNoArithm(OpType op, NoAST* esq, NoAST* dir);
NoAST* criarNoReturn(NoAST* expr);
NoAST* criarNoForHeader(NoAST* init, NoAST* cond, NoAST* iter, NoAST* body);
NoAST* criarNoFuncDef(Simbolo* simbolo, NoAST* body);

void gerarCodigoC(NoAST *raiz, FILE *saida); // você deve usar sua implementação real para isso

// --- Implementações simplificadas das funções criarNo* ---

NoAST* criarNoConst(TipoConst tipo, Value val) {
    NoAST* no = malloc(sizeof(NoAST));
    NoAST_Const* c = malloc(sizeof(NoAST_Const));
    c->const_type = tipo;
    c->val = val;
    no->type = CONST_NODE;
    no->data = c;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

NoAST* criarNoId(const char* nome, Simbolo* simbolo) {
    NoAST* no = malloc(sizeof(NoAST));
    NoAST_Id* id = malloc(sizeof(NoAST_Id));
    id->name = strdup(nome);
    no->type = ID_NODE;
    no->data = id;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

NoAST* criarNoAssign(Simbolo* simbolo, NoAST* valor) {
    NoAST* no = malloc(sizeof(NoAST));
    NoAST_Assign* assign = malloc(sizeof(NoAST_Assign));
    assign->target_entry = simbolo;
    assign->value_expr = valor;
    no->type = ASSIGN_NODE;
    no->data = assign;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

NoAST* criarNoRel(OpType op, NoAST* esq, NoAST* dir) {
    NoAST* no = malloc(sizeof(NoAST));
    NoAST_Rel* rel = malloc(sizeof(NoAST_Rel));
    rel->op = op;
    rel->esquerda = esq;
    rel->direita = dir;
    no->type = REL_OP_NODE;
    no->data = rel;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

NoAST* criarNoArithm(OpType op, NoAST* esq, NoAST* dir) {
    NoAST* no = malloc(sizeof(NoAST));
    NoAST_Arithm* ar = malloc(sizeof(NoAST_Arithm));
    ar->op = op;
    ar->esquerda = esq;
    ar->direita = dir;
    no->type = ARITHM_NODE;
    no->data = ar;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

NoAST* criarNoReturn(NoAST* expr) {
    NoAST* no = malloc(sizeof(NoAST));
    NoAST_Return* ret = malloc(sizeof(NoAST_Return));
    ret->return_expr = expr;
    no->type = RETURN_NODE;
    no->data = ret;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

NoAST* criarNoForHeader(NoAST* init, NoAST* cond, NoAST* iter, NoAST* body) {
    NoAST* no = malloc(sizeof(NoAST));
    NoAST_ForHeader* forh = malloc(sizeof(NoAST_ForHeader));
    forh->init = init;
    forh->cond = cond;
    forh->iter = iter;
    forh->body = body;
    no->type = FOR_HEADER_NODE;
    no->data = forh;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

NoAST* criarNoFuncDef(Simbolo* simbolo, NoAST* body) {
    NoAST* no = malloc(sizeof(NoAST));
    NoAST_FuncDef* f = malloc(sizeof(NoAST_FuncDef));
    f->func_id = simbolo;
    f->body = body;
    no->type = FUNC_DEF_NODE;
    no->data = f;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

// --- Aqui você deve colocar sua função real gerarCodigoC() do seu code_generator.c ---
// Para teste, deixo um stub simples para imprimir algo mínimo.

void gerarCodigoC(NoAST *raiz, FILE *saida) {
    // Para não deixar vazio, um código fixo de exemplo gerado.
    // Você deve substituir por sua implementação real.

    fprintf(saida, "#include <stdio.h>\n\n");

    if (raiz->type == FUNC_DEF_NODE) {
        NoAST_FuncDef* f = (NoAST_FuncDef*)raiz->data;
        fprintf(saida, "void %s() {\n", f->func_id->nome);
        fprintf(saida, "    for (int i = 0; i < 10; i++) {\n");
        fprintf(saida, "        return 42;\n");
        fprintf(saida, "    }\n");
        fprintf(saida, "}\n\n");
    }

    fprintf(saida, "int main() {\n    return 0;\n}\n");
}

// --- main ---

int main() {
    printf("--- Teste gerador FUNC_DEF, FOR_HEADER, RETURN ---\n\n");

    // Criar símbolo da função "teste"
    Simbolo* sym_func = malloc(sizeof(Simbolo));
    strcpy(sym_func->nome, "teste");

    // Criar símbolo i para o for
    Simbolo* sym_i = malloc(sizeof(Simbolo));
    strcpy(sym_i->nome, "i");

    // Construir inicialização: i = 0;
    Value val0; val0.valint = 0;
    NoAST* init = criarNoAssign(sym_i, criarNoConst(TIPO_INT, val0));

    // Condição: i < 10;
    Value val10; val10.valint = 10;
    NoAST* cond = criarNoRel(OP_REL_LT, criarNoId(sym_i->nome, sym_i), criarNoConst(TIPO_INT, val10));

    // Incremento: i = i + 1;
    Value val1; val1.valint = 1;
    NoAST* soma = criarNoArithm(OP_ADICAO, criarNoId(sym_i->nome, sym_i), criarNoConst(TIPO_INT, val1));
    NoAST* iter = criarNoAssign(sym_i, soma);

    // Corpo: return 42;
    Value val42; val42.valint = 42;
    NoAST* ret = criarNoReturn(criarNoConst(TIPO_INT, val42));

    // Montar o for header node
    NoAST* for_node = criarNoForHeader(init, cond, iter, ret);

    // Montar a função teste()
    NoAST* func = criarNoFuncDef(sym_func, for_node);

    // Gerar o código para stdout
    gerarCodigoC(func, stdout);

    // Liberar memória (ideal fazer free recursivo, omitido aqui para simplicidade)
    free(sym_func);
    free(sym_i);

    return 0;
}
