#include "tabela.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Scope *current_scope = NULL;

TabelaSimbolos *criarTabelaSimbolos() {
    TabelaSimbolos *new_table = malloc(sizeof(TabelaSimbolos));
    if (!new_table) {
        perror("Erro ao alocar TabelaSimbolos");
        exit(EXIT_FAILURE);
    }
    new_table->head = NULL;
    return new_table;
}

// insere um símbolo na tabela
void inserirNaTabela(TabelaSimbolos *table, const char *nome, const char *tipo) {
    printf("DEBUG TS: [inserirNaTabela] Tentando inserir '%s' (tipo: %s) na tabela %p (head: %p)\n", nome, tipo, (void*)table, (void*)table->head);
    Simbolo *novo = malloc(sizeof(Simbolo));
    strncpy(novo->nome, nome, MAX_NOME_LEN - 1);
    novo->nome[MAX_NOME_LEN - 1] = '\0';

    strncpy(novo->tipo, tipo, MAX_TIPO_LEN - 1);
    novo->tipo[MAX_TIPO_LEN - 1] = '\0';

    novo->return_type[0] = '\0';
    novo->parameters = NULL;
    novo->num_parameters = 0;

    novo->prox = table->head;
    table->head = novo;
    printf("DEBUG TS: [inserirNaTabela] '%s' INSERIDO. Nova head da tabela %p: %p\n", nome, (void*)table, (void*)table->head);
}


// para buscar símbolo numa tabela específica
Simbolo *buscarNaTabela(TabelaSimbolos *table, const char *nome) {
    printf("DEBUG TS: [buscarNaTabela] Buscando '%s' na tabela %p (head: %p)\n", nome, (void*)table, (void*)table->head);
    if (!table) {
        printf("DEBUG TS: [buscarNaTabela] Tabela de símbolos nula.\n");
        return NULL;
    }
    for (Simbolo *s = table->head; s; s = s->prox) {
        printf("DEBUG TS: [buscarNaTabela] Comparando '%s' com '%s'\n", nome, s->nome);
        if (strcmp(s->nome, nome) == 0) {
            printf("DEBUG TS: [buscarNaTabela] '%s' ENCONTRADO na tabela %p.\n", nome, (void*)table);
            return s;
        }
    }
    printf("DEBUG TS: [buscarNaTabela] '%s' NAO ENCONTRADO nesta tabela.\n", nome);
    return NULL;
}

// pra liberar uma tabela de símbolos (a tabela e todos os seus símbolos)
void liberarTabelaSimbolos(TabelaSimbolos *table) {
    if (!table) return;
    Simbolo *current = table->head;
    while (current) {
        Simbolo *next = current->prox;
        if (current->parameters) {
            free(current->parameters);
        }
        free(current);
        current = next;
    }
    free(table);
}

// adaptado para buscar símbolos em um escopo
Simbolo *buscarSimbolo(char *nome) {
    printf("DEBUG TS: [buscarSimbolo] Buscando '%s' a partir do escopo atual (nivel %d).\n", nome, current_scope ? current_scope->level : -1);
    Scope *temp_scope = current_scope;
    while (temp_scope != NULL) {
        printf("DEBUG TS: [buscarSimbolo] Verificando escopo nivel %d (tabela %p).\n", temp_scope->level, (void*)temp_scope->symbol_table);
        Simbolo *simbolo = buscarNaTabela(temp_scope->symbol_table, nome);
        if (simbolo != NULL) {
            printf("DEBUG TS: [buscarSimbolo] '%s' ENCONTRADO no escopo nivel %d.\n", nome, temp_scope->level);
            return simbolo;
        }
        temp_scope = temp_scope->parent;
    }
    printf("DEBUG TS: [buscarSimbolo] '%s' NAO ENCONTRADO em nenhum escopo.\n", nome);
    return NULL;
}

void imprimirTabelaEscopos() {
    printf("\n--- Tabelas de Símbolos por Escopo ---\n");
    Scope *temp_scope = current_scope;
    int level = 0;
    while (temp_scope != NULL) {
        printf("=== Escopo Nível %d ===\n", level);
        if (temp_scope->symbol_table == NULL || temp_scope->symbol_table->head == NULL) {
            printf("  Escopo vazio.\n");
        } else {
            for (Simbolo *s = temp_scope->symbol_table->head; s; s = s->prox) {
                printf("  Nome: %s, Tipo: %s", s->nome, s->tipo);
                if (strcmp(s->tipo, "function") == 0) {
                    printf(", Retorno: %s, Params: %d", s->return_type, s->num_parameters);
                    if (s->num_parameters > 0 && s->parameters != NULL) {
                        printf(" (");
                        for (int i = 0; i < s->num_parameters; i++) {
                            if (s->parameters[i] != NULL) {
                                printf("%s: %s%s", s->parameters[i]->nome, s->parameters[i]->tipo,
                                       (i == s->num_parameters - 1) ? "" : ", ");
                            } else {
                                printf("NULL"); 
                            }
                        }
                        printf(")");
                    }
                }
                printf("\n");
            }
        }
        temp_scope = temp_scope->parent;
        level++;
    }
    printf("--------------------------------------\n");
}

void enterScope() {
    Scope *new_scope = malloc(sizeof(Scope));
    if (!new_scope) {
        perror("Erro ao alocar novo escopo");
        exit(EXIT_FAILURE);
    }
    new_scope->level = (current_scope == NULL) ? 0 : (current_scope->level + 1);
    new_scope->symbol_table = criarTabelaSimbolos(); // cria uma nova tabela para este escopo
    new_scope->parent = current_scope; // define o escopo anterior como pai
    current_scope = new_scope;         // define q este é o novo escopo atual
    // fprintf(stderr, "DEBUG: entrou no novo escopo. Nivel: %d\n", obterNivelEscopo());
}

void exitScope() {
    if (current_scope == NULL) {
        fprintf(stderr, "Erro: Tentativa de sair de um escopo vazio.\n");
        exit(EXIT_FAILURE);
    }
    Scope *old_scope = current_scope;
    current_scope = current_scope->parent; // volta para o escopo pai
    liberarTabelaSimbolos(old_scope->symbol_table); // libera a tabela de símbolos do escopo que está saindo
    free(old_scope); // libera a struct Scope
    // fprintf(stderr, "DEBUG: saiu do escopo. Nivel: %d\n", obterNivelEscopo());
}



// função nova para registrar parâmetros de uma função
void register_function_parameters(Simbolo *func_entry, Parametro *param_head) {
    if (!func_entry || !param_head) return;

    int count = 0;
    Parametro *current_param = param_head;
    while (current_param) {
        count++;
        current_param = current_param->prox;
    }

    func_entry->parameters = malloc(count * sizeof(Simbolo*));
    func_entry->num_parameters = count;

    current_param = param_head;
    int i = 0;
    while (current_param && i < count) {
        // buscar o simb. do param. no escopo atual (da função)
        Simbolo *param_symbol = buscarNaTabela(current_scope->symbol_table, current_param->nome);

        if (param_symbol) {
            func_entry->parameters[i] = param_symbol;
        } else {
            fprintf(stderr, "Erro interno: Símbolo do parâmetro '%s' não encontrado no escopo da função.\n", current_param->nome);
            func_entry->parameters[i] = NULL;
        }
        i++;
        current_param = current_param->prox;
    }
}
