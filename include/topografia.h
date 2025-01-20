#ifndef TOPOGRAFIA_H
#define TOPOGRAFIA_H


typedef struct {
    int graus;
    int minutos;
    float segundos;
} Graus_Sexagenarios;


typedef enum {
    AZIMUTE,
    RUMO,
    HORIZONTAL,
    VERTICAL,
} TipoAngulo;


typedef struct {
    TipoAngulo tipo;
    Graus_Sexagenarios valor;
} AnguloSexagenario;


typedef struct {
    TipoAngulo tipo;
    int valor;
} AnguloDecimal;






typedef enum {
    ANGULOS_EXTERNOS,
    ANGULOS_INTERNOS,
} TipoPoligonal;

typedef enum {
    ANGULOS_E_DISTANCIAS,
    COORDENADAS_CARTESIANAS,
} TipoReferencial;

typedef struct {
    float v1;
    float v2;
} ParValores;


typedef struct {
    TipoPoligonal tipo_angulos;
    TipoReferencial tipo_referencial;
    ParValores dados[10];
} Poligonal;


Graus_Sexagenarios graus_sexagenarios_from_string(char* string_angulo);
void print_graus_sexagenarios(Graus_Sexagenarios g);


Graus_Sexagenarios graus_decimais_para_sexagenarios(double graus_decimais);
double graus_sexagenarios_para_graus_decimais(Graus_Sexagenarios graus_sex);
double calcular_azimute(double azimute_anterior, double angulo_horizontal);
Graus_Sexagenarios calcular_azimute_angulos_sexagenarios(Graus_Sexagenarios azimute_anterior, Graus_Sexagenarios angulo_horizontal);
double erro_angular_da_poligonal(Poligonal poligonal_fechada);
Graus_Sexagenarios erro_angular_poligonal_angulos_sexagenarios(Poligonal poligonal_fechada);


AnguloDecimal criar_azimute_decimal();
AnguloDecimal criar_rumo_decimal();
AnguloDecimal criar_angulo_horizontal_decimal();
AnguloDecimal criar_angulo_vertical_decimal();
AnguloSexagenario criar_azimute_sexagenario();
AnguloSexagenario criar_rumo_sexagenario();
AnguloSexagenario criar_angulo_horizontal_sexagenario();
AnguloSexagenario criar_angulo_vertical_sexagenario();




#endif 
