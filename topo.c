#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
//#include <sqlite3.h>
#include "topografia.h"
#include "io_cli.h"

#define REG_N 50
#define STRING_BUFFER_SIZE 100


typedef struct {
    double angulo_horizontal_medido;
    double angulo_zenital_medido;
    double teodolito_fio_superior;
    double teodolito_fio_medio;
    double teodolito_fipo_inferior;
    double dh_para_vante;
    double dv;
    double variacao_altura;
    double cota;
    double erro_angulo_horizontal;
    double angulo_horizontal_compensado;
    double azimute;
    double x_parcial;
    double y_parcial;
    double Cx;
    double Cy;
    double x;
    double y;
    uint8_t integra_a_poligonal;
    uint8_t id;
    uint8_t re;
    uint8_t vante;
} PontoInteresse;


/*
sqlite3 *db;

// Função para criar o banco de dados e tabela
void create_database() {
    int rc = sqlite3_open("topo.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Não foi possível abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS poligonal ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "re TEXT NOT NULL,"
                      "estacao TEXT NOT NULL,"
                      "vante TEXT,"
                      "integra_a_poligonal BOOLEAN DEFAULT 1,"
                      "angulo_horizontal_medido REAL NOT NULL,"
                      "angulo_zenital_medido REAL NOT NULL,"
                      "fio_inferior REAL NOT NULL,"
                      "fio_medio REAL NOT NULL,"
                      "fio_superior REAL NOT NULL,"
                      "dh REAL,"
                      "erro_angulo_horizontal REAL,"
                      "dv REAL,"
                      "variacao_altura REAL,"
                      "cota REAL,"
                      "erro_angulo_horizontal REAL," // Resulta da avaliação: (SigmaAng - RefAng) / nVert; 
                                                     //  em que RefAng = (nVert + 2) * 180 para angulos horizontais externos
                                                     //  e      RefAng = (nVert - 2) * 180 para angulos horizontais internos
                                                     //  nVert é o total de pontos que integra a poligonal
                                                     //  os erros de leitura no angulo horizontal podem ser distribuidos igualmente
                                                     //  ou nos angulos correspondentes às menores distâncias 
                                                    
                      "angulo_horizontal_compensado REAL,"
                      "azimute REAL,"
                      "x_parcial REAL,"
                      "y_parcial REAL,"              // Calcular erro planimétrico a partir desse ponto...
                                                     //  definido por (errx² + erry²) ** 0.5
                      "Cx REAL,"
                      "Cy REAL,"
                      "x REAL,"
                      "y REAL,"
                      "observacoes TEXT);";
    
    char *err_msg = NULL;
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }
}
*/

int main() {
    //create_database();
    
    //printf("%zu", sizeof(PontoInteresse));

    uint8_t numero_registros; ler_input_uint8("Informe a quantidade de pontos a ser registrada:", &numero_registros);
    uint8_t numero_registros_originais = numero_registros;
    
    //Preparando variáveis inputs
    char input_string[STRING_BUFFER_SIZE]; memset(input_string, 0, STRING_BUFFER_SIZE);
    float input_float;
    int input_int;
    const char *ops[3] =  {"Distância", "Fios", "Nenhuma"};

    int selecionado = selecionar_opcoes("Quais dados sero registrados", ops, 2);

    printf("Selecionado: %d \n", selecionado);




    //Definindo arrays que acumularão valores de entrada, em seguida serão persistidos.
    PontoInteresse *lista_pontos = malloc(numero_registros * sizeof(PontoInteresse));

    while (numero_registros > 0) {
        uint8_t i = numero_registros_originais - numero_registros;
        ler_input("Ângulo: ", input_string);

        Graus_Sexagenarios g1 = graus_sexagenarios_from_string(input_string);
        //Se formato inválido: 0º0'0.0", repete...
        if ( g1.graus == 0 && g1.minutos == 0 && g1.segundos == 0.0 ) { continue; }

        ler_input_float("Distância: ", &input_float);

        lista_pontos[i].id = i;
        lista_pontos[i].angulo_horizontal_medido = graus_sexagenarios_para_graus_decimais(g1);
        lista_pontos[i].dh_para_vante = input_float;

        numero_registros--;
        memset(input_string, 0, STRING_BUFFER_SIZE);
    }

    //Realizar a presistencia em um arquivo de dados sqlite...
    for ( int8_t i = 0; i < numero_registros_originais; i++) {
        print_graus_sexagenarios(graus_decimais_para_sexagenarios(lista_pontos[i].angulo_horizontal_medido));
        printf("distancia:  %f\n\n", lista_pontos[i].dh_para_vante);
    }
    
  
    free(lista_pontos);



    /*

    char input_string[STRING_BUFFER_SIZE]; memset(input_string, 0, STRING_BUFFER_SIZE);
    float input_double;

    ler_input_float("Altura teodolito: ", &input_double);
    double ai = (double)input_double;

    ler_input_float("Altura cota estação: ", &input_double);
    double cota_estacao = (double)input_double;

    ler_input("Ângulo: ", input_string);
    Graus_Sexagenarios g1 = graus_sexagenarios_from_string(input_string);

    ler_input_float("Valor FS: ", &input_double);
    double fs = (double)input_double;

    ler_input_float("Valor FM: ", &input_double);
    double fm = (double)input_double;

    ler_input_float("Valor FI: ", &input_double);
    double fi = (double)input_double;

    double dh = taqueometria_dh(fs, fi, g1);
    double dv = taqueometria_dv(fs, fi, g1);
    double delta_h = taqueometria_variacao_altura(ai, dv, fm);
    double cota_alvo = taqueometria_cota_alvo(cota_estacao, delta_h);

    printf("A distancia horizontal é: %f\n", dh);
    printf("A distancia vertical é: %f\n", dv);
    printf("A variação na altura foi de: %f\n", delta_h);
    printf("A cota do ponto visado é: %f\n", cota_alvo);

    */


    // Recebendo dados para construção da poligonal...
    /*
    uint8_t numero_registros; ler_input_uint8("Informe a quantidade de pontos a ser registrada:", &numero_registros);
    uint8_t numero_registros_originais = numero_registros;
    
    //Preparando variáveis inputs
    char input_string[STRING_BUFFER_SIZE]; memset(input_string, 0, STRING_BUFFER_SIZE);
    float input_float;

    //Definindo arrays que acumularão valores de entrada, em seguida serão persistidos.
    Graus_Sexagenarios angulos[REG_N];
    float distancias[REG_N];

    while (numero_registros > 0) {
        uint8_t i = numero_registros_originais - numero_registros;
        ler_input("Ângulo: ", input_string);

        Graus_Sexagenarios g1 = graus_sexagenarios_from_string(input_string);
        //Se formato inválido: 0º0'0.0", repete...
        if ( g1.graus == 0 && g1.minutos == 0 && g1.segundos == 0.0 ) { continue; }

        ler_input_float("Distância: ", &input_float);
        angulos[i] = g1;
        distancias[i] = input_float;
        numero_registros--;
        memset(input_string, 0, STRING_BUFFER_SIZE);
    }

    //Realizar a presistencia em um arquivo de dados sqlite...
    for ( int8_t i = 0; i < numero_registros_originais; i++) {
        print_graus_sexagenarios(angulos[i]);
        printf("distancia:  %f\n\n", distancias[i]);
    }
    */
    return 0;
}
