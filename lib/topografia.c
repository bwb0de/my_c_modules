#include <math.h>
#include <stdio.h>
#include "topografia.h"


Graus_Sexagenarios graus_decimais_para_sexagenarios(double graus_decimais) {
    //Isolando parte inteira
    double graus_decimais_parte_inteira = floor(graus_decimais);
    double graus_decimais_parte_decimal = graus_decimais - graus_decimais_parte_inteira;

    // Encontrando valor correspondente em minutos e isolando parte inteira
    //  1 -------- 60'
    //  dec ------ x
    double minutos_totais = graus_decimais_parte_decimal * 60.0;
    double minutos_parte_inteira = floor(minutos_totais);
    double minutos_parte_decimal = minutos_totais - minutos_parte_inteira;

    // Encontrando valor correspondente aos segundos
    //  1' -------- 60''
    //  min_dec --- y
    float segundos_totais = minutos_parte_decimal * 60.0;

    Graus_Sexagenarios resposta;
    resposta.graus = (int)graus_decimais_parte_inteira;
    resposta.minutos = (int)minutos_parte_inteira;
    resposta.segundos = segundos_totais;

    return resposta;
}



double graus_sexagenarios_para_graus_decimais(Graus_Sexagenarios graus_sex) {
    double resposta_segundos = graus_sex.segundos / 3600.0;
    double resposta_minutos = graus_sex.minutos / 60.0;
    double resposta = resposta_segundos + resposta_minutos + (double)graus_sex.graus;
    return resposta;
}



double calcular_azimute(double azimute_anterior, double angulo_horizontal) {
    double resposta = azimute_anterior + angulo_horizontal - 180;
    
    while (resposta > 360) {
        resposta -= 360;
    }

    return resposta;
}



Graus_Sexagenarios calcular_azimute_angulos_sexagenarios(Graus_Sexagenarios azimute_anterior, Graus_Sexagenarios angulo_horizontal) {
    double azimute_anterior_convertido = graus_sexagenarios_para_graus_decimais(azimute_anterior);
    double angulo_horizontal_convertido = graus_sexagenarios_para_graus_decimais(angulo_horizontal);
    double resposta_em_graus_decimais = calcular_azimute(azimute_anterior_convertido, angulo_horizontal_convertido);
    Graus_Sexagenarios resposta = graus_decimais_para_sexagenarios(resposta_em_graus_decimais);
    return resposta;
}



double erro_angular_da_poligonal(Poligonal poligonal_fechada) {

}


Graus_Sexagenarios erro_angular_poligonal_angulos_sexagenarios(Poligonal p) {


}



void _teste_conversao_graus() {
    double v = 160.345676;
    Graus_Sexagenarios v2 = graus_decimais_para_sexagenarios(v);
    printf("%f\n", v);
    printf("%iº%i'%f\"\n", v2.graus, v2.minutos, v2.segundos);
    double v3 = graus_sexagenarios_para_graus_decimais(v2);
    printf("%f\n\n", v3);

 
    v = 180.0;
    v2 = graus_decimais_para_sexagenarios(v);
    printf("%f\n", v);
    printf("%iº%i'%f\"\n", v2.graus, v2.minutos, v2.segundos);
    v3 = graus_sexagenarios_para_graus_decimais(v2);
    printf("%f\n\n", v3);

   
    v = 128.98767556;
    v2 = graus_decimais_para_sexagenarios(v);
    printf("%f\n", v);
    printf("%iº%i'%f\"\n", v2.graus, v2.minutos, v2.segundos);
    v3 = graus_sexagenarios_para_graus_decimais(v2);
    printf("%f\n\n", v3);

    
    v = 280.555555555;
    v2 = graus_decimais_para_sexagenarios(v);
    printf("%f\n", v);
    printf("%iº%i'%f\"\n", v2.graus, v2.minutos, v2.segundos);
    v3 = graus_sexagenarios_para_graus_decimais(v2);
    printf("%f\n\n", v3);

  
    v = 320.345432321;
    v2 = graus_decimais_para_sexagenarios(v);
    printf("%f\n", v);
    printf("%iº%i'%f\"\n", v2.graus, v2.minutos, v2.segundos);
    v3 = graus_sexagenarios_para_graus_decimais(v2);
    printf("%f\n\n", v3);

 
    v = 180.66666666;
    v2 = graus_decimais_para_sexagenarios(v);
    printf("%f\n", v);
    printf("%iº%i'%f\"\n", v2.graus, v2.minutos, v2.segundos);
    v3 = graus_sexagenarios_para_graus_decimais(v2);
    printf("%f\n\n", v3);
}
