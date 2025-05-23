#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <C:\sqlite3\sqlite3.h>
#include <string.h>
#include <stdbool.h>


bool check_db(sqlite3 *db) {
    const char *sql = "SELECT * FROM jogadores;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}


int siur_db(sqlite3 *db) {
    char *errmsg = NULL;

    const char *queries[] = {
        "CREATE TABLE IF NOT EXISTS jogadores ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "nome TEXT NOT NULL"
        ");",

        "CREATE TABLE IF NOT EXISTS emails ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "id_jogador INTEGER REFERENCES jogadores(id), "
            "email TEXT NOT NULL"
        ");",

        "CREATE TABLE IF NOT EXISTS telefones ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "id_jogador INTEGER REFERENCES jogadores(id), "
            "ddd INTEGER, "
            "numero INTEGER"
        ");",

        "CREATE TABLE IF NOT EXISTS metatipos ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "metatipo TEXT"
        ");",

        "CREATE TABLE IF NOT EXISTS cenarios ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "cenario TEXT, "
            "metatipos TEXT, "  // inteiros separados por virgula
            "nt INTEGER"        // nível tecnológico
        ");",

        "CREATE TABLE IF NOT EXISTS jogos ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "id_cenario INTEGER REFERENCES cenarios(id), "
            "titulo TEXT, "
            "descricao TEXT"
       ");",


        "CREATE TABLE IF NOT EXISTS armas_modelos ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "nome TEXT, "
            "nt INTEGER, "
            "alcance REAL, "
            "min_forca INTEGER, "
            "min_destreza INTEGER, "
            "peso REAL, "
            "tamanho CHAR, "
            "resistencia INTEGER"
        ");",

        "CREATE TABLE IF NOT EXISTS armas_manobras ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "id_armas INTEGER REFERENCES armas_modelos(id), "
            "manobra TEXT, "
            "modificador_dif_ INTEGER, "    /* Removido o símbolo '%' do nome */
            "dano TEXT"
        ");",

        "CREATE TABLE IF NOT EXISTS armas_gatilho_modelos ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "nome TEXT, "
            "nt INTEGER, "
            "valor_medio REAL, "
            "alcance INTEGER, "
            "min_forca INTEGER, "
            "modificador_dif_ INTEGER, "    /* Removido o '%' */
            "dano TEXT, "
            "peso REAL, "
            "tamanho CHAR, "
            "resistencia INTEGER"
        ");",

        "CREATE TABLE IF NOT EXISTS equipamentos_modelos ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "nome TEXT, "
            "nt INTEGER, "
            "valor_medio REAL, "
            "peso REAL, "
            "tamanho CHAR, "
            "resistencia INTEGER"
        ");",

        "CREATE TABLE IF NOT EXISTS vestimentas_modelos ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "nome TEXT, "
            "nt INTEGER, "
            "valor_medio REAL, "
            "blindagem INTEGER, "
            "peso REAL, "
            "tamanho CHAR, "
            "resistencia INTEGER"
        ");",

        "CREATE TABLE IF NOT EXISTS escudos_modelos ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "nome TEXT, "
            "nt INTEGER, "
            "valor_medio REAL, "
            "dano TEXT, "
            "blindagem INTEGER, "
            "peso REAL, "
            "tamanho CHAR, "
            "resistencia INTEGER"
        ");",

        "CREATE TABLE IF NOT EXISTS locais ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "nome TEXT, "
            "descricao TEXT, "
            "ids_armas TEXT, "
            "ids_armas_gatilhos TEXT, "
            "ids_equipamentos TEXT, "
            "ids_vestimentas TEXT, "
            "ids_escudos TEXT"
        ");",

        "CREATE TABLE IF NOT EXISTS armas ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, " 
            "id_arma_modelo INTEGER REFERENCES armas_modelos(id), "
            "caracteristicas TEXT, "
            "hp INTEGER"
        ");",

        "CREATE TABLE IF NOT EXISTS armas_gatilho ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "id_arma_gatilho INTEGER REFERENCES armas_gatilho_modelos(id), "
            "caracteristicas TEXT, "
            "hp INTEGER"
        ");",

        "CREATE TABLE IF NOT EXISTS equipamentos ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "id_equipamento INTEGER REFERENCES equipamentos_modelos(id), "
            "caracteristicas TEXT, "
            "hp INTEGER"
        ");",

        "CREATE TABLE IF NOT EXISTS vestimentas ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "id_vestimenta INTEGER REFERENCES vestimentas_modelos(id), "
            "caracteristicas TEXT, "
            "hp INTEGER"
        ");",

        "CREATE TABLE IF NOT EXISTS escudos ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "id_escudo INTEGER REFERENCES escudos_modelos(id), "
            "caracteristicas TEXT, "
            "hp INTEGER"
        ");",

        "CREATE TABLE IF NOT EXISTS personagens ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "id_jogador INTEGER REFERENCES jogadores(id), "
            "nome TEXT, "
            "metodo TEXT, "           /* [expresso / convencional] */
            "id_metatipo INTEGER REFERENCES metatipos(id), "
            "id_cenario INTEGER REFERENCES cenarios(id), "
            "etnia_tribo_grupo TEXT, "
            "religiao_afiliacao TEXT, "
            "genero TEXT, "
            "arquetipo TEXT, "
            "idade INTEGER, "
            "naturalidade TEXT, "
            "atributos_fisicos INTEGER, "
            "atributos_sociais INTEGER, "
            "atributos_mentais INTEGER, "
            "atributo_fisico_forca INTEGER, "
            "atributo_fisico_destreza INTEGER, "
            "atributo_fisico_agilidade INTEGER, "
            "atributo_fisico_vigor INTEGER, "
            "atributo_social_presenca INTEGER, "
            "atributo_social_manipulacao INTEGER, "
            "atributo_social_compostura INTEGER, "
            "atributo_mental_inteligencia INTEGER, "
            "atributo_mental_raciocinio INTEGER, "
            "atributo_mental_sagacidade INTEGER, "
            "atributo_mental_determinacao INTEGER, "
            "capacidades_praticas INTEGER, "
            "capacidades_relacionais INTEGER, "
            "capacidades_tecnicas INTEGER, "
            "capacidade_pratica_armas_brancas INTEGER, "
            "capacidade_pratica_armas_gatilho INTEGER, "
            "capacidade_pratica_arqueirismo INTEGER, "
            "capacidade_pratica_briga INTEGER, "
            "capacidade_pratica_conducao INTEGER, "
            "capacidade_pratica_dissimulacao INTEGER, "
            "capacidade_pratica_esportes INTEGER, "
            "capacidade_pratica_furto INTEGER, "
            "capacidade_pratica_sobrevivencia INTEGER, "
            "capacidade_relacional_astucia INTEGER, "
            "capacidade_relacional_empatia INTEGER, "
            "capacidade_relacional_expressao INTEGER, "
            "capacidade_relacional_intimidacao INTEGER, "
            "capacidade_relacional_manha INTEGER, "
            "capacidade_relacional_persuasao INTEGER, "
            "capacidade_relacional_socializacao INTEGER, "
            "capacidade_relacional_trato_com_animais INTEGER, "
            "capacidade_mental_ciencias INTEGER, "
            "capacidade_mental_erudicao INTEGER, "
            "capacidade_mental_tecnologia INTEGER, "
            "capacidade_mental_investigacao INTEGER, "
            "capacidade_mental_medicina INTEGER, "
            "capacidade_mental_psicologia INTEGER, "
            "capacidade_mental_ocultismo INTEGER, "
            "capacidade_mental_oficios INTEGER, "
            "capacidade_mental_politica INTEGER, "
            "carga REAL, "
            "arremesso REAL, "
            "mvt_velocidade_base REAL, "
            "mvt_inst_padrao INTEGER, "
            "mvt_inst_investida INTEGER, "
            "salto_horizontal REAL, "
            "salto_vertical REAL, "
            "iniciativa INTEGER, "
            "blindagem INTEGER, "
            "ataque_desarmado_ INTEGER, "      /* removido o '%' do nome */
            "ataque_armado_ INTEGER, "
            "ataque_enpecialidade_ INTEGER, "   /* corrigido para 'especialidade' */
            "ataque_arremesso_ INTEGER, "
            "defesa_passiva_ INTEGER, "
            "defesa_bloquear_ INTEGER, "
            "defesa_aparar_ INTEGER, "
            "defesa_esquivar_ INTEGER, "
            "marcador_fadiga INTEGER, "
            "marcador_sede INTEGER, "
            "marcador_fome INTEGER, "
            "marcador_estresse INTEGER, "
            "marcador_pavor INTEGER, "
            "marcador_melancolia INTEGER, "
            "marcador_vontade INTEGER, "
            "marcador_sangue INTEGER, "
            "marcador_ferimento_significativo INTEGER, "
            "marcador_ferimento_incapacitante INTEGER"
        ");",

        "CREATE TABLE IF NOT EXISTS profissoes ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "id_personagem INTEGER REFERENCES personagens(id), "
            "profissao TEXT, "
            "especialidade TEXT"
        ");",

        "CREATE TABLE IF NOT EXISTS preludios ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "id_personagem INTEGER REFERENCES personagens(id), "
            "preludio TEXT"
        ");",

        "CREATE TABLE IF NOT EXISTS imagem_personagens ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "id_personagem INTEGER REFERENCES personagens(id), "
            "imagem BLOB"
        ");",

        "CREATE TABLE IF NOT EXISTS qualidades ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "id_personagem INTEGER REFERENCES personagens(id), "
            "nome TEXT, "
            "nivel INTEGER"
        ");",

        "CREATE TABLE IF NOT EXISTS defeitos ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "id_personagem INTEGER REFERENCES personagens(id), "
            "nome TEXT, "
            "nivel INTEGER"
        ");",

        "CREATE TABLE IF NOT EXISTS antecedentes ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "id_personagem INTEGER REFERENCES personagens(id), "
            "nome TEXT, "
            "nivel INTEGER"
        ");",

        "CREATE TABLE IF NOT EXISTS habilidades_sobrenaturais ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "id_personagem INTEGER REFERENCES personagens(id), "
            "nome TEXT, "
            "nivel INTEGER"
        ");",

        "CREATE TABLE IF NOT EXISTS inventario_armas ("
            "id_personagem INTEGER REFERENCES personagens(id), "
            "id_arma INTEGER REFERENCES armas(id)"
        ");",

        "CREATE TABLE IF NOT EXISTS inventario_armas_gatilho ("
            "id_personagem INTEGER REFERENCES personagens(id), "
            "id_arma_gatilho INTEGER REFERENCES armas_gatilho(id)"
        ");",

        "CREATE TABLE IF NOT EXISTS inventario_equipamento ("
            "id_personagem INTEGER REFERENCES personagens(id), "
            "id_equipamento INTEGER REFERENCES equipamentos(id)"
        ");",

        "CREATE TABLE IF NOT EXISTS inventario_vestimentas ("
            "id_personagem INTEGER REFERENCES personagens(id), "
            "id_vestimenta INTEGER REFERENCES vestimentas(id)"
        ");",

        "CREATE TABLE IF NOT EXISTS inventario_escudos ("
            "id_personagem INTEGER REFERENCES personagens(id), "
            "id_escudo INTEGER REFERENCES escudos(id)"
        ");",

        "CREATE TABLE IF NOT EXISTS itens_encantados ("
            "id INTEGER PRIMARY KEY, "
            "encanto TEXT NOT NULL, "
            "id_arma INTEGER REFERENCES armas(id), "
            "id_arma_gatilho INTEGER REFERENCES armas_gatilho(id), "
            "id_equipamento INTEGER REFERENCES equipamentos(id), "
            "id_vestimenta INTEGER REFERENCES vestimentas(id), "
            "id_escudo INTEGER REFERENCES escudos(id), "
            "descricao TEXT, "
            "caracteristica_alvo TEXT, "
            "modificador TEXT, "
            "CHECK ("
                "(id_arma IS NOT NULL AND id_arma_gatilho IS NULL AND id_equipamento IS NULL AND id_vestimenta IS NULL AND id_escudo IS NULL) OR "
                "(id_arma IS NULL AND id_arma_gatilho IS NOT NULL AND id_equipamento IS NULL AND id_vestimenta IS NULL AND id_escudo IS NULL) OR "
                "(id_arma IS NULL AND id_arma_gatilho IS NULL AND id_equipamento IS NOT NULL AND id_vestimenta IS NULL AND id_escudo IS NULL) OR "
                "(id_arma IS NULL AND id_arma_gatilho IS NULL AND id_equipamento IS NULL AND id_vestimenta IS NOT NULL AND id_escudo IS NULL) OR "
                "(id_arma IS NULL AND id_arma_gatilho IS NULL AND id_equipamento IS NULL AND id_vestimenta IS NULL AND id_escudo IS NOT NULL)"
            ")"
        ");"
    };

    int numQueries = sizeof(queries) / sizeof(queries[0]);
    int rc;
    for (int i = 0; i < numQueries; i++) {
        rc = sqlite3_exec(db, queries[i], 0, 0, &errmsg);
        if (rc != SQLITE_OK) {
            sqlite3_free(errmsg);
        } else {
            //printf("Query %d executada com sucesso.\n", i + 1);
        }
    }
    return 0;
}


