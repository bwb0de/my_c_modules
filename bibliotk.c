#include <stdio.h>
#include <sqlite3.h>

int criar_tabelas_extra(sqlite3 *db) {
    const char *sql =
        "CREATE TABLE IF NOT EXISTS autores ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    nome TEXT NOT NULL"
        ");"

        "CREATE TABLE IF NOT EXISTS generos ("
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
        "    id_autor INTEGER REFERENCES autores(id),"
        "    id_genero INTEGER REFERENCES generos(id),"
        "    id_tipo INTEGER REFERENCES tipos_midia(id),"
        "    descricao TEXT"
        ");"

        "CREATE TABLE IF NOT EXISTS usuarios ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    nome TEXT NOT NULL"
        ");"

        "CREATE TABLE IF NOT EXISTS telefone ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    id_user INTEGER REFERENCES usuarios(id),"
        "    ddd TEXT NOT NULL,"
        "    numero TEXT NOT NULL"
        ");"

        "CREATE TABLE IF NOT EXISTS email ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    id_user INTEGER REFERENCES usuarios(id),"
        "    email TEXT NOT NULL"
        ");"

        "CREATE TABLE IF NOT EXISTS moradias ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    id_user INTEGER REFERENCES usuarios(id),"
        "    uf TEXT NOT NULL,"
        "    municipio TEXT NOT NULL,"
        "    cidade TEXT NOT NULL,"
        "    bairro TEXT NOT NULL,"
        "    numero TEXT NOT NULL"
        ");"

        "CREATE TABLE IF NOT EXISTS emprestimos ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,"
        "    id_midia INTEGER REFERENCES midias(id),"
        "    id_user INTEGER REFERENCES usuarios(id),"
        "    devolvido BOOLEAN DEFAULT 0"
        ");";

    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao criar tabelas extras: %s\n", err_msg);
        sqlite3_free(err_msg);
        return rc;
    }

    printf("Tabelas extras criadas com sucesso!\n");
    return SQLITE_OK;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("biblioteca.db", &db);

    if (rc) {
        fprintf(stderr, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    rc = criar_tabelas_extra(db);

    sqlite3_close(db);
    return rc;
}

