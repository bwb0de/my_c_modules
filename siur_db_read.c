#include <stdio.h>
#include <sqlite3.h>
#include <stdbool.h>


bool list_players(sqlite3 *db) {
    const char *sql = {
        "SELECT jogadores.id, jogadores.nome, telefones.ddd, telefones.numero, emails.email "
        "FROM jogadores "
        "LEFT JOIN telefones ON jogadores.id = telefones.id_jogador "
        "LEFT JOIN emails ON jogadores.id = emails.id_jogador "
        "ORDER BY jogadores.id;"
    };

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        printf("Erro ao preparar a consulta: %s\n", sqlite3_errmsg(db));
        return false;
    }


    printf("ID | Nome | DDD | Telefone | Email\n");
    printf("------------------------------------\n");

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char *nome = (const char *)sqlite3_column_text(stmt, 1);
        int ddd = sqlite3_column_type(stmt, 2) != SQLITE_NULL ? sqlite3_column_int(stmt, 2) : 0;
        int numero = sqlite3_column_type(stmt, 3) != SQLITE_NULL ? sqlite3_column_int(stmt, 3) : 0;
        const char *email = (const char *)sqlite3_column_text(stmt, 4);
        printf("%d | %s | %d | %d | %s\n", id, nome, ddd, numero, email ? email : "Sem email");
    }

    sqlite3_finalize(stmt);
    return true;
}



