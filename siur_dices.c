#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>



typedef enum DiceMethod{
    NO_METOHD,
    SUM_LE, //soma dos valores obtidos menor ou igual dificuldade
    SUM_GE, //soma dos valores obtidos maior ou igual dificuldade
    N_GE,   //quantidade de dados com valor igual ou maior que a dificuldade
    N_LE    //quantidade de dados com valor igual ou menor que a dificuldade
} dice_method_t;


void dice_info(int n_dices, int sides, dice_method_t method, int dif) {
    char m[60];

    switch (method) {
        case N_LE: strcpy(m, "'dados com valor <= a dificuldade'"); break;
        case N_GE: strcpy(m, "'dados com valor >= a dificuldade'"); break;
        case SUM_LE: strcpy(m, "'somatório <= à dificuldade'"); break;
        case SUM_GE: strcpy(m, "'somatório >= à dificuldade'"); break;
        case NO_METOHD: strcpy(m, "'sem método definido'"); break;
    }


    if ( n_dices > 1 ) {
       printf("Rolando %d dados D%d, método %s, dificuldade %d: \n", n_dices, sides, m, dif);
    } else {
       printf("Rolando um D%d: \n", sides);
    }
}




int dice_roller(int n_dices, int sides, dice_method_t method, int dif) {
    int result = 0;
    int tmp_v = 0;

    switch (method) {
        case NO_METOHD: {
            int number = 1;
            /*
            if ( n_dices > 1 ) {
               printf("Rolando %d dados D%d: \n", n_dices, sides);
            } else {
               printf("Rolando um D%d: \n", sides);
            }
            */

            while (n_dices) {
                tmp_v =  (rand() % sides) + 1;
                result += tmp_v;
                //printf("[%d]  ", tmp_v);
                n_dices--;
                number++;
            }
            return result;

        }

        case SUM_LE: {
            dice_info(n_dices, sides, method, dif);
            while (n_dices) {
                tmp_v =  (rand() % sides) + 1;
                result += tmp_v;

                if (n_dices == 1) {
                   printf("[%d] => %d ", tmp_v, result);
                } else {
                   printf("[%d] ", tmp_v);
                }

                n_dices--;
            }

            if (result <= dif ) {
                printf("Sucesso! margem: %d\n", dif - result);
            } else {
                printf("Falha! margem: %d\n", dif - result);
            }

            return dif - result;
        }

        case SUM_GE: {
            dice_info(n_dices, sides, method, dif);
            while (n_dices) {
                tmp_v =  (rand() % sides) + 1;
                result += tmp_v;

                if (n_dices == 1) {
                   printf("[%d] => %d ", tmp_v, result);
                } else {
                   printf("[%d] ", tmp_v);
                }

                n_dices--;
            }

            if (result >= dif ) {
                printf("Sucesso! margem: %d\n", result - dif);
            } else {
                printf("Falha! margem: %d\n", result - dif);
            }

            return result - dif;
        }

        case N_LE: {
            dice_info(n_dices, sides, method, dif);
            while (n_dices) {
                tmp_v =  (rand() % sides) + 1;
                if ( tmp_v <= dif ) {
                    result++;
                    printf("[%d]Ok! ", tmp_v);
                } else {
                    if ( tmp_v == 10) { 
                        result--;
                        printf("[%d]FC! ", tmp_v);
                    } else {
                        printf("[%d]    ", tmp_v);
                    }
                }
                n_dices--;
            }

            return result;
        }
 

        case N_GE: {
            dice_info(n_dices, sides, method, dif);
            while (n_dices) {
                tmp_v =  (rand() % sides) + 1;
                if ( tmp_v >= dif ) {
                    result++;
                    printf("[%d]Ok! ", tmp_v);
                } else {
                    if ( tmp_v == 1) { 
                        result--;
                        printf("[%d]FC! ", tmp_v);
                    } else {
                        printf("[%d]    ", tmp_v);
                    }
                }
                n_dices--;
            }

            return result;
       }
   }
}


void dice_simulation(int d1sides, int d2sides, int d3sides, int extra, int dif) {
    int dA, dB, dC;

    int max = 500000;
    int sigma = 0;
    float sigma_margens = 0;
    int sigma_steps = 0;
    float count = 0;
    float sucess = 0;
    double average = 0;
    int step = 0;

    while (max) {
        dA = dice_roller(1, 6, NO_METOHD, 0);
        dB = dice_roller(1, 6, NO_METOHD, 0);
        dC = dice_roller(1, 6, NO_METOHD, 0);
        step = (dA + dB + dC + extra);
        if (step > dif) { 
            sucess++;
            sigma_margens += step - dif;
            sigma_steps += step;
        }
        sigma += step;
        count++;
        max--;
    }

    average = (double)(sigma_margens / count);
    double tx_sucess = (sucess / count);

    printf("%d;D%d;D%d;D%d;%d;%f;%d\n", dif, d1sides, d2sides, d3sides, extra, average, sigma_steps);
}

void dice_eval(int d1max, int d2max, int d3max, int extra, int dif) {
    int dA, dB, dC, step;
    dA = 1; dB = 1; dC = 1;
    float sucess = 0;
    float total = 0;

    while (true) {
        step = (dA + dB + dC + extra);
        if (step > dif) {
            sucess++;
        }
        total++;

        if (d1max == dA && d2max == dB && d3max == dC) {break;}

        if (dC < d3max) {
            dC++; continue;
        }

        if (dC == d3max && dB < d2max) {
            dC = 1;
            dB++; continue;
        }

        if (dB == d2max && dA < d1max ) {
            dB = 1;
            dA++; continue;
        }
    }
    printf("%d;D%d;D%d;D%d;%d;%f\n", dif, d1max, d2max, d3max, extra, (sucess/total) * 100);
}


int main(int argc, char *argv[]) {
    srand(time(NULL));
    int dif = atoi(argv[1]);
    while ( dif != 2 ) {
        dice_eval(6, 6, 6, 0, dif);
        dice_eval(6, 6, 8, 0, dif);
        dice_eval(6, 8, 8, 0, dif);
        dice_eval(8, 8, 8, 0, dif);
        dice_eval(8, 8, 10, 0, dif);
        dice_eval(8, 10, 10, 0, dif);
        dice_eval(10, 10, 10, 0, dif);
        dice_eval(10, 10, 12, 0, dif);
        dice_eval(10, 12, 12, 0, dif);
        dice_eval(12, 12, 12, 0, dif);
        dif--;
    }
    return 0;
}


