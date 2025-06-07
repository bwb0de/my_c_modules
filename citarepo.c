#include <stdio.h>
#include <sqlite3.h>

int criar_tabelas(sqlite3 *db) {
    const char *sql =
        "CREATE TABLE IF NOT EXISTS autores ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    nome TEXT NOT NULL"
        ");"

        "CREATE TABLE IF NOT EXISTS disciplinas ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    nome TEXT NOT NULL"
        ");"

        "CREATE TABLE IF NOT EXISTS tipos_midia ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    nome TEXT NOT NULL"
        ");"

        "CREATE TABLE IF NOT EXISTS midias ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    nome TEXT NOT NULL,"
        "    id_autores TEXT,"
        "    id_genero INTEGER REFERENCES generos(id),"
        "    id_tipo INTEGER REFERENCES tipos_midia(id),"
        "    ano INTEGER NOT NULL,"
        "    idsn TEXT,"
        "    link TEXT,"
        "    descricao TEXT"
        ");"

        "CREATE TABLE IF NOT EXISTS tags ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    nome TEXT NOT NULL"
        ");"

        "CREATE TABLE IF NOT EXISTS citacao ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    id_autor INTEGER REFERENCES autores(id),"
        "    id_midia INTEGER REFERENCES midias(id),"
        "    ano INTEGER NOT NULL,"
        "    pagina TEXT,"
        "    tags TEXT"
        ");";

    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao criar tabelas: %s\n", err_msg);
        sqlite3_free(err_msg);
        return rc;
    }

    printf("Tabelas criadas com sucesso!\n");
    return SQLITE_OK;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("biblioteca.db", &db);

    if (rc) {
        fprintf(stderr, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    rc = criar_tabelas(db);

    sqlite3_close(db);
    return rc;
}

