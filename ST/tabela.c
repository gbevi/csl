#include "tabela.h" // Inclui as definições das structs e protótipos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variável global para o escopo atual, deve ser inicializada como NULL
Scope *current_scope = NULL;

// Cria e inicializa uma nova tabela de símbolos
TabelaSimbolos *criarTabelaSimbolos() {
    TabelaSimbolos *new_table = malloc(sizeof(TabelaSimbolos));
    if (!new_table) {
        perror("Erro ao alocar TabelaSimbolos");
        exit(EXIT_FAILURE);
    }
    new_table->head = NULL; // A tabela começa vazia
    return new_table;
}

// Insere um símbolo na tabela de símbolos fornecida
void inserirNaTabela(TabelaSimbolos *table, const char *nome, const char *tipo) {
    if (!table) {
        fprintf(stderr, "Erro: Tabela de símbolos nula ao tentar inserir '%s'.\n", nome);
        return;
    }
    printf("DEBUG TS: [inserirNaTabela] Tentando inserir '%s' (tipo: %s) na tabela %p (head: %p)\n", nome, tipo, (void*)table, (void*)table->head);

    Simbolo *novo = malloc(sizeof(Simbolo));
    if (!novo) {
        perror("Erro ao alocar Simbolo");
        exit(EXIT_FAILURE);
    }

    // Copia o nome e garante a terminação nula
    strncpy(novo->nome, nome, MAX_NOME_LEN - 1);
    novo->nome[MAX_NOME_LEN - 1] = '\0';

    // Copia o tipo e garante a terminação nula
    strncpy(novo->tipo, tipo, MAX_TIPO_LEN - 1);
    novo->tipo[MAX_TIPO_LEN - 1] = '\0';

    // Inicializa campos específicos de função (se não for uma função, eles permanecerão vazios/nulos)
    novo->return_type[0] = '\0'; // String vazia
    novo->parameters = NULL;
    novo->num_parameters = 0;

    // Adiciona o novo símbolo no início da lista encadeada da tabela
    novo->prox = table->head;
    table->head = novo;
    printf("DEBUG TS: [inserirNaTabela] '%s' INSERIDO. Nova head da tabela %p: %p\n", nome, (void*)table, (void*)table->head);
}

// Busca um símbolo em uma tabela de símbolos específica
Simbolo *buscarNaTabela(TabelaSimbolos *table, const char *nome) {
    printf("DEBUG TS: [buscarNaTabela] Buscando '%s' na tabela %p (head: %p)\n", nome, (void*)table, (void*)table->head);
    if (!table) {
        printf("DEBUG TS: [buscarNaTabela] Tabela de símbolos nula.\n");
        return NULL;
    }
    // Percorre a lista de símbolos na tabela
    for (Simbolo *s = table->head; s; s = s->prox) {
        printf("DEBUG TS: [buscarNaTabela] Comparando '%s' com '%s'\n", nome, s->nome);
        if (strcmp(s->nome, nome) == 0) {
            printf("DEBUG TS: [buscarNaTabela] '%s' ENCONTRADO na tabela %p.\n", nome, (void*)table);
            return s; // Símbolo encontrado
        }
    }
    printf("DEBUG TS: [buscarNaTabela] '%s' NAO ENCONTRADO nesta tabela.\n", nome);
    return NULL; // Símbolo não encontrado
}

// Libera toda a memória alocada para uma tabela de símbolos e seus símbolos
void liberarTabelaSimbolos(TabelaSimbolos *table) {
    if (!table) return;

    Simbolo *current_simbolo = table->head;
    while (current_simbolo) {
        Simbolo *next_simbolo = current_simbolo->prox;

        // Se o símbolo for uma função, libera a lista de parâmetros
        if (current_simbolo->parameters) {
            Parametro *current_param = current_simbolo->parameters;
            while (current_param) {
                Parametro *next_param = current_param->prox;
                free(current_param); // Libera cada parâmetro
                current_param = next_param;
            }
        }
        free(current_simbolo); // Libera o símbolo
        current_simbolo = next_simbolo;
    }
    free(table); // Libera a própria estrutura da tabela
}

// Busca um símbolo começando do escopo atual e subindo na cadeia de escopos
Simbolo *buscarSimbolo(char *nome) {
    printf("DEBUG TS: [buscarSimbolo] Buscando '%s' a partir do escopo atual (nivel %d).\n", nome, current_scope ? current_scope->level : -1);
    Scope *temp_scope = current_scope;
    while (temp_scope != NULL) {
        printf("DEBUG TS: [buscarSimbolo] Verificando escopo nivel %d (tabela %p).\n", temp_scope->level, (void*)temp_scope->symbol_table);
        Simbolo *simbolo = buscarNaTabela(temp_scope->symbol_table, nome);
        if (simbolo != NULL) {
            printf("DEBUG TS: [buscarSimbolo] '%s' ENCONTRADO no escopo nivel %d.\n", nome, temp_scope->level);
            return simbolo; // Símbolo encontrado no escopo atual ou em um pai
        }
        temp_scope = temp_scope->parent; // Sobe para o escopo pai
    }
    printf("DEBUG TS: [buscarSimbolo] '%s' NAO ENCONTRADO em nenhum escopo.\n", nome);
    return NULL; // Símbolo não encontrado em nenhum escopo acessível
}

// Imprime o conteúdo de todas as tabelas de símbolos na cadeia de escopos
void imprimirTabelaEscopos() {
    printf("\n--- Tabelas de Símbolos por Escopo ---\n");
    Scope *temp_scope = current_scope;
    int level = 0; // Nível 0 é o escopo mais interno (current_scope)
    while (temp_scope != NULL) {
        printf("=== Escopo Nível %d ===\n", level);
        if (temp_scope->symbol_table == NULL || temp_scope->symbol_table->head == NULL) {
            printf("  Escopo vazio.\n");
        } else {
            // Percorre e imprime os símbolos na tabela do escopo atual
            for (Simbolo *s = temp_scope->symbol_table->head; s; s = s->prox) {
                printf("  Nome: %s, Tipo: %s", s->nome, s->tipo);
                // Se for uma função, imprime informações adicionais
                if (strcmp(s->tipo, "function") == 0) {
                    printf(", Retorno: %s, Params: %d", s->return_type, s->num_parameters);
                    if (s->num_parameters > 0 && s->parameters != NULL) {
                        printf(" (");
                        Parametro *p = s->parameters;
                        int param_count = 0;
                        while (p) {
                            printf("%s: %s", p->nome, p->tipo);
                            if (p->prox) printf(", "); // Adiciona vírgula se não for o último
                            p = p->prox;
                            param_count++;
                        }
                        printf(")");
                    }
                }
                printf("\n");
            }
        }
        temp_scope = temp_scope->parent; // Vai para o escopo pai
        level++; // Incrementa o nível para o próximo escopo (pai)
    }
    printf("--------------------------------------\n");
}

// Entra em um novo escopo
void enterScope() {
    Scope *new_scope = malloc(sizeof(Scope));
    if (!new_scope) {
        perror("Erro ao alocar novo escopo");
        exit(EXIT_FAILURE);
    }
    // Define o nível do novo escopo
    new_scope->level = (current_scope == NULL) ? 0 : (current_scope->level + 1);
    new_scope->symbol_table = criarTabelaSimbolos(); // Cria uma nova tabela para este escopo
    new_scope->parent = current_scope; // Define o escopo anterior como pai
    current_scope = new_scope;         // Define que este é o novo escopo atual
    fprintf(stderr, "DEBUG: Entrou no novo escopo. Nivel: %d\n", current_scope->level);
}

// Sai do escopo atual
void exitScope() {
    if (current_scope == NULL) {
        fprintf(stderr, "Erro: Tentativa de sair de um escopo vazio.\n");
        exit(EXIT_FAILURE);
    }
    Scope *old_scope = current_scope;
    current_scope = current_scope->parent; // Volta para o escopo pai
    liberarTabelaSimbolos(old_scope->symbol_table); // Libera a tabela de símbolos do escopo que está saindo
    free(old_scope); // Libera a struct Scope
    fprintf(stderr, "DEBUG: Saiu do escopo. Nivel: %d\n", current_scope ? current_scope->level : -1);
}

// Registra os parâmetros de uma função no seu Simbolo correspondente
void register_function_parameters(Simbolo *func_entry, Parametro *param_head) {
    if (!func_entry) {
        fprintf(stderr, "Erro: func_entry é NULL em register_function_parameters.\n");
        return;
    }

    // Atribui a cabeça da lista de parâmetros à entrada da função
    func_entry->parameters = param_head;

    // Conta o número de parâmetros
    int count = 0;
    Parametro *current_param = param_head;
    while (current_param) {
        count++;
        current_param = current_param->prox;
    }
    func_entry->num_parameters = count;

    printf("DEBUG TS: [register_function_parameters] Registrados %d parâmetros para a função '%s'.\n",
           func_entry->num_parameters, func_entry->nome);
}
