#include <stdio.h>
#include <sqlite3.h>

int criar_tabelas_estudantes(sqlite3 *db) {
    const char *sql =
        "CREATE TABLE IF NOT EXISTS estudantes ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    nome TEXT NOT NULL,"
        "    nome_mae TEXT NOT NULL,"
        "    nome_pai TEXT,"
        "    dn DATE,"
        "    nivel TEXT"
        ");"

        "CREATE TABLE IF NOT EXISTS telefone_etd ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    id_estudante INTEGER REFERENCES estudantes(id),"
        "    ddd TEXT NOT NULL,"
        "    numero TEXT NOT NULL"
        ");"

        "CREATE TABLE IF NOT EXISTS esocs ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    id_estudante INTEGER REFERENCES estudantes(id),"
        "    periodo TEXT NOT NULL,"
        "    obs TEXT"
        ");"

        "CREATE TABLE IF NOT EXISTS moradias ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    id_estudante INTEGER REFERENCES estudantes(id),"
        "    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,"
        "    uf TEXT NOT NULL,"
        "    municipio TEXT NOT NULL,"
        "    cidade TEXT NOT NULL,"
        "    bairro TEXT NOT NULL,"
        "    numero TEXT NOT NULL,"
        "    ativo BOOLEAN DEFAULT 1"
        ");"

        "CREATE TABLE IF NOT EXISTS residencia ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    id_estudante INTEGER REFERENCES estudantes(id),"
        "    id_moradia INTEGER REFERENCES moradias(id),"
        "    id_esoc INTEGER REFERENCES esocs(id),"
        "    integrantes TEXT NOT NULL"
        ");"

        "CREATE TABLE IF NOT EXISTS grupo_familiar ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    id_estudante INTEGER REFERENCES estudantes(id),"
        "    id_esoc INTEGER REFERENCES esocs(id),"
        "    obs TEXT"
        ");"

        "CREATE TABLE IF NOT EXISTS integrantes ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    id_estudante INTEGER REFERENCES estudantes(id),"
        "    id_grp INTEGER REFERENCES grupo_familiar(id),"
        "    nome TEXT NOT NULL,"
        "    vinculo TEXT NOT NULL,"
        "    natureza_ocupacao TEXT NOT NULL,"
        "    renda TEXT NOT NULL,"
        "    pcd BOOLEAN NOT NULL,"
        "    dc BOOLEAN NOT NULL,"
        "    dg BOOLEAN NOT NULL,"
        "    asm BOOLEAN NOT NULL,"
        "    reside_com_etd BOOLEAN NOT NULL,"
        "    obs TEXT"
        ");"

        "CREATE TABLE IF NOT EXISTS professores ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    nome TEXT NOT NULL"
        ");"

        "CREATE TABLE IF NOT EXISTS disciplinas ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    id_prof INTEGER REFERENCES professores(id),"
        "    nome TEXT NOT NULL"
        ");"

        "CREATE TABLE IF NOT EXISTS telefones_prof ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    id_prof INTEGER REFERENCES professores(id),"
        "    ddd TEXT NOT NULL,"
        "    numero TEXT NOT NULL"
        ");"

        "CREATE TABLE IF NOT EXISTS planos_aula ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    id_prof INTEGER REFERENCES professores(id),"
        "    id_disciplina INTEGER REFERENCES disciplinas(id),"
        "    titulo TEXT NOT NULL,"
        "    sintese_conteudo TEXT NOT NULL,"
        "    ativo BOOLEAN DEFAULT 1"
        ");"

        "CREATE TABLE IF NOT EXISTS conteudo_programa ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    id_prof INTEGER REFERENCES professores(id),"
        "    id_disciplina INTEGER REFERENCES disciplinas(id),"
        "    id_aula INTEGER REFERENCES planos_aula(id),"
        "    topico TEXT NOT NULL,"
        "    ativo BOOLEAN DEFAULT 1"
        ");"

        "CREATE TABLE IF NOT EXISTS provas ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    id_prof INTEGER REFERENCES professores(id),"
        "    id_disciplina INTEGER REFERENCES disciplinas(id),"
        "    ano INTEGER,"
        "    periodo INTEGER,"
        "    tipo TEXT NOT NULL,"
        "    titulo TEXT"
        ");"

        "CREATE TABLE IF NOT EXISTS questoes_provas ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    id_prova INTEGER REFERENCES provas(id),"
        "    conteudo TEXT NOT NULL,"
        "    q INTEGER NOT NULL,"
        "    enunciado TEXT,"
        "    tipo TEXT NOT NULL,"
        "    img BLOB"
        ");"

        "CREATE TABLE IF NOT EXISTS subitens_questoes ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    id_q INTEGER REFERENCES questoes_provas(id),"
        "    texto TEXT"
        ");"

        "CREATE TABLE IF NOT EXISTS turmas ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    id_profs TEXT NOT NULL,"
        "    id_estudantes TEXT NOT NULL,"
        "    nome TEXT NOT NULL,"
        "    periodo TEXT,"
        "    ativo BOOLEAN DEFAULT 1"
        ");"

        "CREATE TABLE IF NOT EXISTS frequencia ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    id_estudante INTEGER REFERENCES estudantes(id),"
        "    id_turma INTEGER REFERENCES turmas(id),"
        "    date DATE NOT NULL,"
        "    presente BOOLEAN NOT NULL"
        ");";

    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao criar tabelas de estudantes: %s\n", err_msg);
        sqlite3_free(err_msg);
        return rc;
    }

    printf("Tabelas de estudantes criadas com sucesso!\n");
    return SQLITE_OK;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("escola.db", &db);

    if (rc) {
        fprintf(stderr, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    rc = criar_tabelas_estudantes(db);

    sqlite3_close(db);
    return rc;
}

