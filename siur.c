#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sqlite3.h>
#include <string.h>
#include <stdbool.h>

#define SIUR_DB "siur.db"


bool check_db(sqlite3 *db) {
    const char *sql = "SELECT * FROM jogadores;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}


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
            "nt INTEGER" // nível tecnológico
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


int add_phone(sqlite3 *db, int jogador_id, int ddd, int numero) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO telefones (id_jogador, ddd, numero) VALUES (?, ?, ?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) return 0;
    sqlite3_bind_int(stmt, 1, jogador_id);
    sqlite3_bind_int(stmt, 2, ddd);
    sqlite3_bind_int(stmt, 3, numero);
    if (sqlite3_step(stmt) != SQLITE_DONE) return 0;
    sqlite3_finalize(stmt);
    return 1;
}

int add_email(sqlite3 *db, int jogador_id, const char *email) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO emails (id_jogador, email) VALUES (?, ?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) return 0;
    sqlite3_bind_int(stmt, 1, jogador_id);
    sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE) return 0;
    sqlite3_finalize(stmt);
    return 1;
}


// Função para adicionar um novo jogador com opcionalmente email e telefone
int add_player(sqlite3 *db, const char *nome, const char *email, int ddd, int numero) {
    char *errmsg = NULL;
   
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO jogadores (nome) VALUES (?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) return 0;
    sqlite3_bind_text(stmt, 1, nome, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE) return 0;
    sqlite3_finalize(stmt);

    int jogador_id = sqlite3_last_insert_rowid(db);
    if (email)  { add_email(db, jogador_id, email); }
    if (numero) { add_phone(db, jogador_id, ddd, numero); }


    return 1;
}

int adicionar_telefone_email(sqlite3 *db, int jogador_id, int ddd, int numero, const char *email) {
    return add_phone(db, jogador_id, ddd, numero) && add_email(db, jogador_id, email);
}


sqlite3 *open_db(char *dbname) {
    sqlite3 *db;
    int rc;
    rc = sqlite3_open(dbname, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    return db;
}


int str2int(char *string) {
    int v = 0;
    int len = strlen(string);
    for (int i = 0; i < len; i++) {
        v += (int)string[i];
    }
    return v;
}


typedef enum DiceMethod{
    NO_METOHD,
    SUM_LE, //soma dos valores obtidos menor ou igual dificuldade
    SUM_GE, //soma dos valores obtidos maior ou igual dificuldade
    N_GE,   //quantidade de dados com valor igual ou maior que a dificuldade
    N_LE    //quantidade de dados com valor igual ou menor que a dificuldade
} dice_method_t;


int dice_roller(int n_dices, int sides, dice_method_t method, int dif) {
    //srand(time(NULL));

    int result = 0;
    int tmp_v = 0;

    switch (method) {
        case NO_METOHD: {
            int number = 1;
            if ( n_dices > 1 ) {
               printf("Rolando %d dados D%d: \n", n_dices, sides);
            } else {
               printf("Rolando um D%d: \n", sides);
            }
            while (n_dices) {
                tmp_v =  (rand() % sides) + 1;
                result += tmp_v;
                printf("[%d]  ", tmp_v);
                n_dices--;
                number++;
            }
            return 0;

        }

        case SUM_LE: {
            while (n_dices) {
                tmp_v =  (rand() % sides) + 1;
                result += tmp_v;
                printf("d%d: %d\n", sides, tmp_v);
                n_dices--;
            }

            if (result <= dif ) {
                printf("Sucesso! [%d]\n", dif - result);
            } else {
                printf("Falha! [%d]\n", dif - result);
            }

            return dif - result;
        }

        case SUM_GE: {
            while (n_dices) {
                tmp_v =  (rand() % sides) + 1;
                result += tmp_v;
                printf("d%d: %d\n", sides, tmp_v);
                n_dices--;
            }

            if (result >= dif ) {
                printf("Sucesso! [%d]\n", result - dif);
            } else {
                printf("Falha! [%d]\n", result - dif);
            }

            return result - dif;
        }

        case N_LE: {
            while (n_dices) {
                tmp_v =  (rand() % sides) + 1;
                if ( tmp_v <= dif ) {
                    result++;
                    printf("d%d: %d (Sucesso!)\n", sides, tmp_v);
                } else {
                    printf("d%d: %d (Falha!)\n", sides, tmp_v);
                }
                n_dices--;
            }

            return result;
        }
 

        case N_GE: {
             while (n_dices) {
                tmp_v =  (rand() % sides) + 1;
                if ( tmp_v >= dif ) {
                    result++;
                    printf("d%d: %d (Sucesso!)\n", sides, tmp_v);
                } else {
                    printf("d%d: %d (Falha!)\n", sides, tmp_v);
                }
                n_dices--;
            }

            return result;
       }
   }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    sqlite3 *db = open_db(SIUR_DB);
    bool has_db = check_db(db); if (!(has_db)) { siur_db(db); }

    bool command_error = true;

    if ( argc < 2 ) {
        printf("É necessário fornecer comandos e subcomandos para siur funcionar...\n\n");
        printf("Exemplos de uso:\n");
        printf("  siur add player <nome> <email> <DDD> <telefone>\n");
        printf("   adiciona um jogador ao banco de dados...\n\n");
        printf("  siur list characters\n");
        printf("   lista os protagonistas registrados do banco de dados...\n\n");
        printf("  ...\n\n");
        printf("Digite 'siur help' para obter uma lista completa dos comandos disponíveis.\n");
        exit(1);
    }

    
    for (int i = 1; i < argc; i++) {
        switch (str2int(argv[i])) {
            case 297: { //add
                command_error = false;
                if      ( str2int(argv[i+1]) == 653 ) { //add player
                    printf("Adicionando jogador...\n"); 
                    //add_player(db, str2int(argv[i+2], argv[i+3], atoi(argv[i+4]), atoi(argv[i+5]));
                    i = i + 5;
                }
                
                else if ( str2int(argv[i+1]) == 941 ) { //add character
                    printf("Adicionando personagem...\n");
                    i = i + 1;
                }

                else if ( str2int(argv[i+1]) == 321 ) { //add npc
                    printf("Adicionando npc...\n");
                    i = i + 1;
                }
               
                
                else if ( str2int(argv[i+1]) == 659 ) { //add equipo 
                    printf("Adicionando equipamento...\n");
                    i = i + 1;
                }
                
                else if ( str2int(argv[i+1]) == 450 ) { //add vest
                    printf("Adicionando vestimenta...\n"); 
                    i = i + 1;
                }
                
                else if ( str2int(argv[i+1]) == 650 ) {
                    if      ( str2int(argv[i+2]) == 520 ) { //add weapon meele
                        printf("Adicionando arma de combate corpo-a-corpo...\n");
                        i = i + 2;
                    }

                    else if ( str2int(argv[i+2]) == 446 ) { //add wapon shot
                        printf("Adicionando arma de combate a distância...\n"); 
                        i = i + 2;
                    }

                    else { command_error = true; }
                }

                else if ( str2int(argv[i+1]) == 737 ) { //add cenario

                }

                else if ( str2int(argv[i+1]) == 410 ) { //add game

                }

                else if ( str2int(argv[i+1]) == 411 ) { //add cene

                }


                else { command_error = true; }
                break;
            }

            case 410: {  //game
                command_error = false;
                if      ( str2int(argv[i+1]) == 640 ) { //game select
                    printf("Selecionando jogo...\n"); 
                    list_players(db);
                    i = i + 1;
                }
                
                else if ( str2int(argv[i+1]) == 411 ) { //game cene
                    printf("Selecionando cena no jogo...\n"); 
                    i = i + 1;
                }

                else { command_error = true; }
                break;
            }


            case 444: {  //list
                command_error = false;
                if      ( str2int(argv[i+1]) == 653 ) { //list players
                    printf("Listando jogadores...\n"); 
                    list_players(db);
                    i = i + 1;
                }
                
                else if ( str2int(argv[i+1]) == 941 ) { //list characters
                    printf("Listando personagens...\n"); 
                    i = i + 1;
                }

                else if ( str2int(argv[i+1]) == 436 ) { //list npcs
                    printf("Listando npcs...\n"); 
                    i = i + 1;
                }

                else if ( str2int(argv[i+1]) == 659 ) { //list equipos
                    printf("Listando equipamentos...\n"); 
                    i = i + 1;
                }

                else if ( str2int(argv[i+1]) == 659 ) { //list cenarios
                    printf("Listando equipamentos...\n"); 
                    i = i + 1;
                }

                else if ( str2int(argv[i+1]) == 659 ) { //list games
                    printf("Listando equipamentos...\n"); 
                    i = i + 1;
                }



                else { command_error = true; }
                break;
            }

            case 441: { // roll
                command_error = false;
                if      (str2int(argv[i+2]) == 154 || str2int(argv[i+2]) == 122 ) { //roll d6
                    int n = atoi(argv[i+1]);
                    dice_roller(n, 6, NO_METOHD, 0);
                    i = i + 2;
                }

                else if (str2int(argv[i+2]) == 156 || str2int(argv[i+2]) == 124 ) { //roll d8
                    int n = atoi(argv[i+1]);
                    dice_roller(n, 8, NO_METOHD, 0);
                    i = i + 2;
                }

                else if (str2int(argv[i+2]) == 197 || str2int(argv[i+2]) == 165 ) { //roll d10
                    int n = atoi(argv[i+1]);
                    dice_roller(n, 10, NO_METOHD, 0);
                    i = i + 2;
                }

                else if (str2int(argv[i+2]) == 199 || str2int(argv[i+2]) == 167 ) { //roll d12
                    int n = atoi(argv[i+1]);
                    dice_roller(n, 12, NO_METOHD, 0);
                    i = i + 2;
                }

                else if (str2int(argv[i+2]) == 198 || str2int(argv[i+2]) == 166 ) { //roll d20
                    int n = atoi(argv[i+1]);
                    dice_roller(n, 20, NO_METOHD, 0);
                    i = i + 2;
                }

                else if (str2int(argv[i+2]) == 245 || str2int(argv[i+2]) == 213 ) { //roll d100
                    int n = atoi(argv[i+1]);
                    dice_roller(n, 100, NO_METOHD, 0);
                    i = i + 2;
                }

                else { command_error = true; }
                break;

            }

            case 448: { // test
                command_error = false;

                int n = atoi(argv[i+2]);
                int dice = 0;
                int dificulty = atoi(argv[i+4]);


                if  (str2int(argv[i+3]) == 154 || str2int(argv[i+3]) == 122 ) {     //test ... d6
                    dice = 6;
                }

                else if (str2int(argv[i+3]) == 156 || str2int(argv[i+3]) == 124 ) { //test ... d8
                    dice = 8;
                }

                else if (str2int(argv[i+3]) == 197 || str2int(argv[i+3]) == 165 ) { //test ... d10
                    dice = 10;
                }

                else if (str2int(argv[i+3]) == 199 || str2int(argv[i+3]) == 167 ) { //test ... d12
                    dice = 12;
                }

                else if (str2int(argv[i+3]) == 198 || str2int(argv[i+3]) == 166 ) { //test ... d20
                    dice = 20;
                }

                else if (str2int(argv[i+3]) == 245 || str2int(argv[i+3]) == 213 ) { //test ... d100
                    dice = 100;

                }

                else { command_error = true; break; }


                if (str2int(argv[i+1]) == 645 ) {      //test sum_le 
                    dice_roller(n, dice, SUM_LE, dificulty);
                }

                else if (str2int(argv[i+1]) == 640 ) { //test sum_ge
                    dice_roller(n, dice, SUM_GE, dificulty);
                }

                else if (str2int(argv[i+1]) == 209 ) { //test le
                    dice_roller(n, dice, N_LE, dificulty);
                }
                
                else if (str2int(argv[i+1]) == 204 ) { //test ge
                    dice_roller(n, dice, N_GE, dificulty);
                }

                else { command_error = true; break; }
                break;

            }



            case 425:{  //help
                printf("Forma de uso:\n");
                printf(" siur <commando> <subcomando> [<parametros...>]\n");
                printf("\n");
                printf(" register metatipo\n");
                printf(" register equipo\n");
                printf(" register cenario\n");
                printf(" register monster\n");

                printf(" roll <n> <dice>\n");

                printf(" test sum_le <n> <dice> <dif>\n");
                printf(" test sum_ge <n> <dice> <dif>\n");
                printf(" test le <n> <dice> <dif>\n");
                printf(" test ge <n> <dice> <dif>\n");
         
                
                printf(" create player               -> registro de jogadores\n");
                printf(" create character            -> registro de personagens\n");
                printf(" create npc                  -> registro de npcs\n");
                printf(" create random npc                  -> registro de npcs\n");

                printf(" add equipo               -> registro de equipamento\n");
                printf(" add waepon meele         -> registro de arma para combate corpo-a-corpo\n");
                printf(" add weapon shot          -> registro de armas de longo alcance\n");
                printf(" add cenario              -> registro de um novo cenário\n");
                printf(" add game                 -> registro de um novo jogo ou aventura\n");
                printf(" add cene                 -> adiciona uma cena ao jogo selecionado\n");
                printf(" game select              -> atinva um jogo ou aventura\n"); 
                printf(" game cene <n>            -> seleciona a cena número <n> em um jogo\n");
                printf(" list players             -> lista os jogadores cadastrados\n");
                printf(" list characters          -> lista os protagonistas criados\n");
                printf(" list npcs                -> lista os extras, monstros e coadjuvantes\n");
                printf(" list equipos             -> lista todos equipamentos cadastrados\n");
                printf(" list cenarios            -> registro de um novo cenário\n");
                printf(" list games               -> registro de um novo jogo ou aventura (requer\n");
                printf(" list character <n> items -> lista equipamento do inventário\n");
                break;
            }
        }
    }
    
    sqlite3_close(db);

    if (command_error) {
        printf("Opção incorreta. Digite 'siur help' para mais informações.\n");
    }

    return 0;
}


