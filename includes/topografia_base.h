#ifndef TOPOGRAFIA_BASE_H
#define TOPOGRAFIA_BASE_H


typedef struct GrausSexagenarios{
    uint16_t graus;
    uint8_t minutos;
    float segundos;
} graus_sex_t;


typedef enum TipoAngulo {
    AZIMUTE,
    RUMO,
    HORIZONTAL,
    VERTICAL,
} ang_kind_t;


typedef struct AnguloSexagenario{
    ang_kind_t tipo;
    graus_sex_t valor;
} ang_sex_t;


typedef struct AnguloDecimal{
    ang_kind_t tipo;
    int valor;
} ang_dec_t;


typedef enum {
    ANGULOS_EXTERNOS,
    ANGULOS_INTERNOS,
} TipoPoligonal;

typedef enum {
    ANGULOS_E_DISTANCIAS,
    COORDENADAS_CARTESIANAS,
} TipoReferencial;


typedef struct Vec2Doubles{
    double v1;
    double v2;
} v2_t;

typedef struct {
    TipoPoligonal tipo_angulos;
    TipoReferencial tipo_referencial;
    v2_t dados[10];
} Poligonal;



graus_sex_t graus_decimais_para_sexagenarios(double graus_decimais);
double graus_sexagenarios_para_graus_decimais(graus_sex_t graus_sex);
double calcular_azimute(double azimute_anterior, double angulo_horizontal);
graus_sex_t calcular_azimute_angulos_sexagenarios(graus_sex_t azimute_anterior, graus_sex_t angulo_horizontal);
double erro_angular_da_poligonal(Poligonal poligonal_fechada);
graus_sex_t erro_angular_poligonal_angulos_sexagenarios(Poligonal poligonal_fechada);

double calcular_erro_angular_poligonal(int nVert, graus_sex_t sigma_angulos_horizontais);
v2_t calcular_erro_fechamento(v2_t ponto2D_conhecido, v2_t ponto2D_medido);
double calcular_erro_planimetrico(v2_t erro_fechamento);
v2_t calcular_compensacoes_das_componentes(double distancia_horizontal, double perimetro_poligonal, v2_t erro_fechamento);



double taqueometria_dh(double fio_superior, double fio_inferior, graus_sex_t angulo_zenital);
double taqueometria_dv(double fio_superior, double fio_inferior, graus_sex_t angulo_zenital);
double taqueometria_variacao_altura(double ai, double dv, double fm);
double taqueometria_cota_alvo(double cota_estacao, double variacao_altura);


#endif 
