#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>

#define MAX_INPUT 200

//sudo apt-get install sqlite3 libsqlite3-dev
sqlite3 *db;

// Função para criar o banco de dados e tabela
void create_database() {
    int rc = sqlite3_open("todo.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Não foi possível abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS tasks ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "timestamp TEXT NOT NULL,"
                      "titulo TEXT NOT NULL,"
                      "detalhamento TEXT,"
                      "prioridade INTEGER,"
                      "concluida BOOLEAN DEFAULT 0);";
    
    char *err_msg = NULL;
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }
}

// Função para obter input do usuário
void get_input(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    fflush(stdout);
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove nova linha
}

// Função para inserir nova tarefa
void insert_task() {
    char timestamp[20];
    time_t now = time(NULL);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));

    char titulo[MAX_INPUT];
    char detalhamento[MAX_INPUT];
    char prioridade_str[MAX_INPUT];
    int prioridade;

    get_input("Título: ", titulo, MAX_INPUT);
    get_input("Detalhamento: ", detalhamento, MAX_INPUT);
    get_input("Prioridade (1-5): ", prioridade_str, MAX_INPUT);
    prioridade = atoi(prioridade_str);

    const char *sql = "INSERT INTO tasks (timestamp, titulo, detalhamento, prioridade) "
                      "VALUES (?, ?, ?, ?);";
    
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar declaração: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, timestamp, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, titulo, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, detalhamento, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, prioridade);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Erro ao inserir tarefa: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    printf("Tarefa registrada com sucesso!\n\n");
}

// Callback para listar tarefas
int list_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    printf("ID: %s\n", argv[0]);
    printf("Data/Hora: %s\n", argv[1]);
    printf("Título: %s\n", argv[2]);
    printf("Detalhes: %s\n", argv[3]);
    printf("Prioridade: %s\n", argv[4]);
    printf("Concluída: %s\n", strcmp(argv[5], "0") ? "Sim" : "Não");
    printf("-----------------------------------\n");
    return 0;
}


int list_callback_sumary(void *NotUsed, int argc, char **argv, char **azColName) {
    printf("ID: %s; Título: %s; Data/Hora: %s\n", argv[0], argv[2], argv[1]);
    return 0;
}


// Função para listar todas as tarefas
void list_tasks() {
    const char *sql = "SELECT * FROM tasks;";
    char *err_msg = NULL;
    
    printf("\n=== Lista de Tarefas ===\n");
    int rc = sqlite3_exec(db, sql, list_callback, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao listar tarefas: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    printf("\n");
}


void list_tasks_sumary() {
    const char *sql = "SELECT * FROM tasks;";
    char *err_msg = NULL;
    
    printf("\n=== Lista de Tarefas ===\n");
    int rc = sqlite3_exec(db, sql, list_callback_sumary, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao listar tarefas: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    printf("\n");
}



// Função para marcar tarefa como concluída
void mark_completed() {
    char id_str[MAX_INPUT];
    get_input("ID da tarefa para marcar como concluída: ", id_str, MAX_INPUT);
    int id = atoi(id_str);

    const char *sql = "UPDATE tasks SET concluida = 1 WHERE id = ?;";
    sqlite3_stmt *stmt;
    
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar declaração: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_int(stmt, 1, id);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Erro ao atualizar tarefa: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Tarefa marcada como concluída!\n\n");
    }

    sqlite3_finalize(stmt);
}

// Função para excluir tarefa
void delete_task() {
    char id_str[MAX_INPUT];
    get_input("ID da tarefa para excluir: ", id_str, MAX_INPUT);
    int id = atoi(id_str);

    const char *sql = "DELETE FROM tasks WHERE id = ?;";
    sqlite3_stmt *stmt;
    
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar declaração: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_int(stmt, 1, id);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Erro ao excluir tarefa: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Tarefa excluída com sucesso!\n\n");
    }

    sqlite3_finalize(stmt);
}

int main() {
    create_database();
    
    int opcao;
    do {
        printf("=== Menu Todo List ===\n");
        printf("[1] Registrar nova tarefa\n");
        printf("[2] Listar resumo das tarefas\n");
        printf("[3] Marcar tarefa como concluída\n");
        printf("[4] Excluir tarefa\n");
        printf("[5] Sair do programa\n");
        printf("Escolha uma opção: ");

        char input[10];
        fgets(input, sizeof(input), stdin);
        opcao = atoi(input);

        switch(opcao) {
            case 1:
                insert_task();
                break;
            case 2:
                list_tasks_sumary();
                break;
            case 3:
                list_tasks();      
                mark_completed();
                break;
            case 4:
                list_tasks();
                delete_task();
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 4);

    sqlite3_close(db);
    return 0;
}
