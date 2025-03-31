#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <C:\sqlite3\sqlite3.h>
#include <string.h>
#include <stdbool.h>


int add_phone(sqlite3 *db, int jogador_id, int ddd, int numero) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO telefones (id_jogador, ddd, numero) VALUES (?, ?, ?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) return 0;
    sqlite3_bind_int(stmt, 1, jogador_id);
    sqlite3_bind_int(stmt, 2, ddd);
    sqlite3_bind_int(stmt, 3, numero);
    if (sqlite3_step(stmt) != SQLITE_DONE) return -1;
    sqlite3_finalize(stmt);
    int id = sqlite3_last_insert_rowid(db);
    return id;
}


int add_email(sqlite3 *db, int jogador_id, const char *email) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO emails (id_jogador, email) VALUES (?, ?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) return 0;
    sqlite3_bind_int(stmt, 1, jogador_id);
    sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE) return -1;
    sqlite3_finalize(stmt);
    int id = sqlite3_last_insert_rowid(db);
    return id;
}


int has_player(sqlite3 *db, const char *nome) {
    const char *sql_select = "SELECT id FROM jogadores WHERE nome = ?";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, NULL) != SQLITE_OK ) {
        printf("Erro ao preparar a consulta em jogadores: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    sqlite3_bind_text(stmt, 1, nome, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return id;
    }
    sqlite3_finalize(stmt);
    return -1;
}


int add_player(sqlite3 *db, const char *nome, const char *email, int ddd, int numero) {
    int id = has_player(db, nome);
    if (id != -1) {return id;}
 
    char *errmsg = NULL;
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO jogadores (nome) VALUES (?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) return 0;
    sqlite3_bind_text(stmt, 1, nome, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE) return 0;
    sqlite3_finalize(stmt);

    id = sqlite3_last_insert_rowid(db);
    if (email)  { add_email(db, id, email); }
    if (numero) { add_phone(db, id, ddd, numero); }
    return id;
}


int has_metatipo(sqlite3 *db, const char *metatipo) {
    const char *sql_select = "SELECT id FROM metatipos WHERE metatipo = ?";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Erro ao preparar a consulta de cenário: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_bind_text(stmt, 1, metatipo, -1, SQLITE_STATIC);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return id;
    }
    sqlite3_finalize(stmt);
    return -1;
}


int add_metatipo(sqlite3 *db, const char *metatipo) {
    int id = has_metatipo(db, metatipo);
    if (id != -1) {return id;}

    const char *sql = "INSERT INTO metatipos (metatipo) VALUES (?)";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Erro ao preparar a inserção de metatipo: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_bind_text(stmt, 1, metatipo, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Erro ao inserir metatipo: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    id = sqlite3_last_insert_rowid(db);
    sqlite3_finalize(stmt);
    return id;
}


int has_cenario(sqlite3 *db, const char *cenario) {
    const char *sql_select = "SELECT id FROM cenarios WHERE cenario = ?";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Erro ao preparar a consulta de cenário: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_bind_text(stmt, 1, cenario, -1, SQLITE_STATIC);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return id;
    }
    sqlite3_finalize(stmt);
    return -1;
}


int add_cenario(sqlite3 *db, const char *cenario, const char *metatipos, int nt) {
    int id = has_cenario(db, cenario);
    if (id != -1) {return id;}

    sqlite3_stmt *stmt;
    const char *sql_insert = "INSERT INTO cenarios (cenario, metatipos, nt) VALUES (?, ?, ?)";
    if (sqlite3_prepare_v2(db, sql_insert, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Erro ao preparar a inserção de cenário: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_bind_text(stmt, 1, cenario, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, metatipos, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, nt);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Erro ao inserir cenário: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    id = sqlite3_last_insert_rowid(db);
    sqlite3_finalize(stmt);
    return id;
}


int add_game(sqlite3 *db, const char *titulo, const char *descricao, const char *cenario, const char *metatipos, int nt) {
    int id_cenario = add_cenario(db, cenario, metatipos, nt);
    if (id_cenario == -1) return -1;

    const char *sql = "INSERT INTO jogos (id_cenario, titulo, descricao) VALUES (?, ?, ?)";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Erro ao preparar a inserção de jogo: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_bind_int(stmt, 1, id_cenario);
    sqlite3_bind_text(stmt, 2, titulo, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, descricao, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Erro ao inserir jogo: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    int id = sqlite3_last_insert_rowid(db);
    sqlite3_finalize(stmt);
    return id;
}




