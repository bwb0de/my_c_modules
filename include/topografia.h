#ifndef TOPOGRAFIA_H
#define TOPOGRAFIA_H

typedef struct {
    uint16_t graus;
    uint8_t minutos;
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
    double v1;
    double v2;
} ParValores;

typedef struct {
    TipoPoligonal tipo_angulos;
    TipoReferencial tipo_referencial;
    ParValores dados[10];
} Poligonal;


Graus_Sexagenarios parse_graus_sexagenarios(char* string_angulo);
void print_graus_sexagenarios(Graus_Sexagenarios g);


Graus_Sexagenarios graus_decimais_para_sexagenarios(double graus_decimais);
double graus_sexagenarios_para_graus_decimais(Graus_Sexagenarios graus_sex);
double calcular_azimute(double azimute_anterior, double angulo_horizontal);
Graus_Sexagenarios calcular_azimute_angulos_sexagenarios(Graus_Sexagenarios azimute_anterior, Graus_Sexagenarios angulo_horizontal);
double erro_angular_da_poligonal(Poligonal poligonal_fechada);
Graus_Sexagenarios erro_angular_poligonal_angulos_sexagenarios(Poligonal poligonal_fechada);

double calcular_erro_angular_poligonal(int nVert, Graus_Sexagenarios sigma_angulos_horizontais);
ParValores calcular_erro_fechamento(ParValores ponto2D_conhecido, ParValores ponto2D_medido);
double calcular_erro_planimetrico(ParValores erro_fechamento);
ParValores calcular_compensacoes_das_componentes(double distancia_horizontal, double perimetro_poligonal, ParValores erro_fechamento);



double taqueometria_dh(double fio_superior, double fio_inferior, Graus_Sexagenarios angulo_zenital);
double taqueometria_dv(double fio_superior, double fio_inferior, Graus_Sexagenarios angulo_zenital);
double taqueometria_variacao_altura(double ai, double dv, double fm);
double taqueometria_cota_alvo(double cota_estacao, double variacao_altura);


#endif 
