#include <math.h>
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


void dice_simulation2(int d6_dices_num, int extra, int dif) {
    if (d6_dices_num < 3 || d6_dices_num > 10) {
        printf("A quantidade de D6 deve estar entre 3 e 10...\n");
        return;
    }

    int dA, dB, dC, dD, dE, dF, dG, dH, dI, dJ;

    int max = 500000;
    int sigma = 0;
    float sigma_margens = 0;
    int sigma_steps = 0;
    float count = 0;
    float sucess = 0;
    double average = 0;
    int step = 0;

    while (max) {
        switch (d6_dices_num) {
            case 3: {
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
                break;
            }
            case 4: {
                dA = dice_roller(1, 6, NO_METOHD, 0);
                dB = dice_roller(1, 6, NO_METOHD, 0);
                dC = dice_roller(1, 6, NO_METOHD, 0);
                dD = dice_roller(1, 6, NO_METOHD, 0);
                step = (dA + dB + dC + dD + extra);
                if (step > dif) { 
                    sucess++;
                    sigma_margens += step - dif;
                    sigma_steps += step;
                }
                sigma += step;
                count++;
                max--;

                break;
            }
            case 5: {
                dA = dice_roller(1, 6, NO_METOHD, 0);
                dB = dice_roller(1, 6, NO_METOHD, 0);
                dC = dice_roller(1, 6, NO_METOHD, 0);
                dD = dice_roller(1, 6, NO_METOHD, 0);
                dE = dice_roller(1, 6, NO_METOHD, 0);
                step = (dA + dB + dC + dD + dE + extra);
                if (step > dif) { 
                    sucess++;
                    sigma_margens += step - dif;
                    sigma_steps += step;
                }
                sigma += step;
                count++;
                max--;

                break;
            }
            case 6: {
                dA = dice_roller(1, 6, NO_METOHD, 0);
                dB = dice_roller(1, 6, NO_METOHD, 0);
                dC = dice_roller(1, 6, NO_METOHD, 0);
                dD = dice_roller(1, 6, NO_METOHD, 0);
                dE = dice_roller(1, 6, NO_METOHD, 0);
                dF = dice_roller(1, 6, NO_METOHD, 0);
                step = (dA + dB + dC + dD + dE + dF + extra);
                if (step > dif) { 
                    sucess++;
                    sigma_margens += step - dif;
                    sigma_steps += step;
                }
                sigma += step;
                count++;
                max--;

                break;
            }
            case 7: {
                dA = dice_roller(1, 6, NO_METOHD, 0);
                dB = dice_roller(1, 6, NO_METOHD, 0);
                dC = dice_roller(1, 6, NO_METOHD, 0);
                dD = dice_roller(1, 6, NO_METOHD, 0);
                dE = dice_roller(1, 6, NO_METOHD, 0);
                dF = dice_roller(1, 6, NO_METOHD, 0);
                dG = dice_roller(1, 6, NO_METOHD, 0);
                step = (dA + dB + dC + dD + dE + dF + dG + extra);
                if (step > dif) { 
                    sucess++;
                    sigma_margens += step - dif;
                    sigma_steps += step;
                }
                sigma += step;
                count++;
                max--;

                break;
            }
            case 8: {
                dA = dice_roller(1, 6, NO_METOHD, 0);
                dB = dice_roller(1, 6, NO_METOHD, 0);
                dC = dice_roller(1, 6, NO_METOHD, 0);
                dD = dice_roller(1, 6, NO_METOHD, 0);
                dE = dice_roller(1, 6, NO_METOHD, 0);
                dF = dice_roller(1, 6, NO_METOHD, 0);
                dG = dice_roller(1, 6, NO_METOHD, 0);
                dH = dice_roller(1, 6, NO_METOHD, 0);
                step = (dA + dB + dC + dD + dE + dF + dG + dH + extra);
                if (step > dif) { 
                    sucess++;
                    sigma_margens += step - dif;
                    sigma_steps += step;
                }
                sigma += step;
                count++;
                max--;

                break;
            }
            case 9: {
                dA = dice_roller(1, 6, NO_METOHD, 0);
                dB = dice_roller(1, 6, NO_METOHD, 0);
                dC = dice_roller(1, 6, NO_METOHD, 0);
                dD = dice_roller(1, 6, NO_METOHD, 0);
                dE = dice_roller(1, 6, NO_METOHD, 0);
                dF = dice_roller(1, 6, NO_METOHD, 0);
                dG = dice_roller(1, 6, NO_METOHD, 0);
                dH = dice_roller(1, 6, NO_METOHD, 0);
                dI = dice_roller(1, 6, NO_METOHD, 0);
                step = (dA + dB + dC + dD + dE + dF + dG + dH + dI + extra);
                if (step > dif) { 
                    sucess++;
                    sigma_margens += step - dif;
                    sigma_steps += step;
                }
                sigma += step;
                count++;
                max--;

                break;
            }
            case 10: {
                dA = dice_roller(1, 6, NO_METOHD, 0);
                dB = dice_roller(1, 6, NO_METOHD, 0);
                dC = dice_roller(1, 6, NO_METOHD, 0);
                dD = dice_roller(1, 6, NO_METOHD, 0);
                dE = dice_roller(1, 6, NO_METOHD, 0);
                dF = dice_roller(1, 6, NO_METOHD, 0);
                dG = dice_roller(1, 6, NO_METOHD, 0);
                dH = dice_roller(1, 6, NO_METOHD, 0);
                dI = dice_roller(1, 6, NO_METOHD, 0);
                dJ = dice_roller(1, 6, NO_METOHD, 0);
                step = (dA + dB + dC + dD + dE + dF + dG + dH + dI + dJ + extra);
                if (step > dif) { 
                    sucess++;
                    sigma_margens += step - dif;
                    sigma_steps += step;
                }
                sigma += step;
                count++;
                max--;

                break;
            }
        }
    }

    average = (double)(sigma_margens / count);
    double tx_sucess = (sucess / count);

    printf("%d;D6_n:%d;%d;%f;%d\n", dif, d6_dices_num, extra, average, sigma_steps);
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


void dice_eval2(int d6_dices_num, int extra, int dif) {
    if (d6_dices_num < 2 || d6_dices_num > 10) {
        printf("A quantidade de D6 deve estar entre 2 e 10...\n");
        return;
    }

    int dA, dB, dC, dD, dE, dF, dG, dH, dI, dJ;
    int step;
    dA = 1; dB = 1; dC = 1; dD = 1, dE = 1, dF = 1, dG = 1, dH = 1, dI = 1, dJ = 1;
    float sucess = 0;
    float total = 0;

    int n = 1;
    int max_loop = pow(6, d6_dices_num);

    printf("\n");
    while (n != max_loop) {
        printf("\r");
        n++;
        printf("D6_num:%d ; steps:%d ; dif:%d ; ", d6_dices_num, n, dif);
        switch (d6_dices_num) {
            case 2: {
                step = (dA + dB + extra);
                if (step > dif) {
                    sucess++;
                }
                total++;

                if (6 == dA && 6 == dB && 6 == dC) {break;}

                if (dB < 6) {
                    dB++; break;
                }

                if (dB == 6 && dA < 6 ) {
                    dB = 1;
                    dA++; break;
                }
                break;
            }

            case 3: {
                step = (dA + dB + dC + extra);
                if (step > dif) {
                    sucess++;
                }
                total++;

                if (6 == dA && 6 == dB && 6 == dC) {break;}

                if (dC < 6) {
                    dC++; continue;
                }

                if (dC == 6 && dB < 6) {
                    dC = 1;
                    dB++; continue;
                }

                if (dB == 6 && dA < 6 ) {
                    dB = 1;
                    dA++; continue;
                }
                break;
            }
            case 4: {
                step = (dA + dB + dC + dD + extra);
                if (step > dif) {
                    sucess++;
                }
                total++;

                if (6 == dA && 6 == dB && 6 == dC) {break;}

                if (dD < 6) {
                    dD++; continue;
                }

                if (dD == 6 && dC < 6) {
                    dD = 1;
                    dC++; continue;
                }

                if (dC == 6 && dB < 6) {
                    dC = 1;
                    dB++; continue;
                }

                if (dB == 6 && dA < 6 ) {
                    dB = 1;
                    dA++; continue;
                }
                break;
            }
            case 5: {
                step = (dA + dB + dC + dD + dE + extra);
                if (step > dif) {
                    sucess++;
                }
                total++;

                if (6 == dA && 6 == dB && 6 == dC) {break;}

                if (dE < 6) {
                    dE++; continue;
                }

                if (dE == 6 && dD < 6) {
                    dE = 1;
                    dD++; continue;
                }

                if (dD == 6 && dC < 6) {
                    dD = 1;
                    dC++; continue;
                }

                if (dC == 6 && dB < 6) {
                    dC = 1;
                    dB++; continue;
                }

                if (dB == 6 && dA < 6 ) {
                    dB = 1;
                    dA++; continue;
                }
                break;
            }
            case 6: {
                step = (dA + dB + dC + dD + dE + dF + extra);
                if (step > dif) {
                    sucess++;
                }
                total++;

                if (6 == dA && 6 == dB && 6 == dC) {break;}

                if (dF < 6) {
                    dF++; continue;
                }

                if (dF == 6 && dE < 6) {
                    dF = 1;
                    dE++; continue;
                }

                if (dE == 6 && dD < 6) {
                    dE = 1;
                    dD++; continue;
                }

                if (dD == 6 && dC < 6) {
                    dD = 1;
                    dC++; continue;
                }

                if (dC == 6 && dB < 6) {
                    dC = 1;
                    dB++; continue;
                }

                if (dB == 6 && dA < 6 ) {
                    dB = 1;
                    dA++; continue;
                }
                break;
            }
            case 7: {
                step = (dA + dB + dC + dD + dE + dF + dG + extra);
                if (step > dif) {
                    sucess++;
                }
                total++;

                if (6 == dA && 6 == dB && 6 == dC) {break;}

                if (dG < 6) {
                    dG++; continue;
                }

                if (dG == 6 && dF < 6) {
                    dG = 1;
                    dF++; continue;
                }

                if (dF == 6 && dE < 6) {
                    dF = 1;
                    dE++; continue;
                }

                if (dE == 6 && dD < 6) {
                    dE = 1;
                    dD++; continue;
                }

                if (dD == 6 && dC < 6) {
                    dD = 1;
                    dC++; continue;
                }

                if (dC == 6 && dB < 6) {
                    dC = 1;
                    dB++; continue;
                }

                if (dB == 6 && dA < 6 ) {
                    dB = 1;
                    dA++; continue;
                }
                break;
            }
            case 8: {
                step = (dA + dB + dC + dD + dE + dF + dG + dH + extra);
                if (step > dif) {
                    sucess++;
                }
                total++;

                if (6 == dA && 6 == dB && 6 == dC) {break;}

                if (dH < 6) {
                    dH++; continue;
                }

                if (dH == 6 && dG < 6) {
                    dH = 1;
                    dG++; continue;
                }

                if (dG == 6 && dF < 6) {
                    dG = 1;
                    dF++; continue;
                }

                if (dF == 6 && dE < 6) {
                    dF = 1;
                    dE++; continue;
                }

                if (dE == 6 && dD < 6) {
                    dE = 1;
                    dD++; continue;
                }

                if (dD == 6 && dC < 6) {
                    dD = 1;
                    dC++; continue;
                }

                if (dC == 6 && dB < 6) {
                    dC = 1;
                    dB++; continue;
                }

                if (dB == 6 && dA < 6 ) {
                    dB = 1;
                    dA++; continue;
                }
                break;
            }
            case 9: {
                step = (dA + dB + dC + dD + dE + dF + dG + dH + dI + extra);
                if (step > dif) {
                    sucess++;
                }
                total++;

                if (6 == dA && 6 == dB && 6 == dC) {break;}

                if (dI < 6) {
                    dI++; continue;
                }

                if (dI == 6 && dH < 6) {
                    dI = 1;
                    dH++; continue;
                }

                if (dH == 6 && dG < 6) {
                    dH = 1;
                    dG++; continue;
                }

                if (dG == 6 && dF < 6) {
                    dG = 1;
                    dF++; continue;
                }

                if (dF == 6 && dE < 6) {
                    dF = 1;
                    dE++; continue;
                }

                if (dE == 6 && dD < 6) {
                    dE = 1;
                    dD++; continue;
                }

                if (dD == 6 && dC < 6) {
                    dD = 1;
                    dC++; continue;
                }

                if (dC == 6 && dB < 6) {
                    dC = 1;
                    dB++; continue;
                }

                if (dB == 6 && dA < 6 ) {
                    dB = 1;
                    dA++; continue;
                }
                break;
            }
            case 10: {
                step = (dA + dB + dC + dD + dE + dF + dG + dH + dI + dJ + extra);
                if (step > dif) {
                    sucess++;
                }
                total++;

                if (6 == dA && 6 == dB && 6 == dC) {break;}

                if (dJ < 6) {
                    dJ++; continue;
                }

                if (dJ == 6 && dI < 6) {
                    dJ = 1;
                    dI++; continue;
                }

                if (dI == 6 && dH < 6) {
                    dI = 1;
                    dH++; continue;
                }

                if (dH == 6 && dG < 6) {
                    dH = 1;
                    dG++; continue;
                }

                if (dG == 6 && dF < 6) {
                    dG = 1;
                    dF++; continue;
                }

                if (dF == 6 && dE < 6) {
                    dF = 1;
                    dE++; continue;
                }

                if (dE == 6 && dD < 6) {
                    dE = 1;
                    dD++; continue;
                }

                if (dD == 6 && dC < 6) {
                    dD = 1;
                    dC++; continue;
                }

                if (dC == 6 && dB < 6) {
                    dC = 1;
                    dB++; continue;
                }

                if (dB == 6 && dA < 6 ) {
                    dB = 1;
                    dA++; continue;
                }
                break;
            }
        }
    }
    printf("%f\n", (sucess/total) * 100);
}



int main(int argc, char *argv[]) {
    srand(time(NULL));
    int dif = atoi(argv[1]);

    while (dif != 4) {
        dice_eval2(2, 0, dif);
        dice_eval2(3, 0, dif);
        dice_eval2(4, 0, dif);

        /*
        dice_eval2(5, 0, dif);
        dice_eval2(6, 0, dif);
        dice_eval2(7, 0, dif);
        dice_eval2(8, 0, dif);
        dice_eval2(9, 0, dif);
        dice_eval2(10, 0, dif);
        */
        dif--;

    }
    
    /*
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
    */
    return 0;
}


