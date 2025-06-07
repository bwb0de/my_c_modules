#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <C:\sqlite3\sqlite3.h>
#include <string.h>
#include <stdbool.h>
#include "siur_db_create.c"
#include "siur_db_write.c"

#define SIUR_DB "siur.db"

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



int main(int argc, char *argv[]) {
    // srand(time(NULL));
    sqlite3 *db = open_db(SIUR_DB);
    bool has_db = check_db(db); if (!(has_db)) { siur_db(db); }

    add_game(db);


    bool command_error = true;


    /*
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

    */

    return 0;
}



