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


void dice_eval2(int d6_dices_num, int extra, int dif) { // maior ou igual
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


void dice_eval3(int dices_num, int dice_sides, int dif) { // menor ou igual
    if (dices_num < 2 || dices_num > 10) {
        printf("A quantidade de D6 deve estar entre 2 e 10...\n");
        return;
    }

    int dA, dB, dC, dD, dE, dF, dG, dH, dI, dJ, soma;
    dA = 1; dB = 1; dC = 1; dD = 1, dE = 1, dF = 1, dG = 1, dH = 1, dI = 1, dJ = 1;

    soma = 0;
    float sucess = 0;
    float total = 0;

    switch (dices_num) {
        case 2: {
            for (dA = 1; dA < dice_sides+1; dA++) {
                for (dB = 1; dB < dice_sides+1; dB++) {
                    soma = dA + dB;
                    if (soma <= dif) {
                        sucess++;
                    }
                    total++;
                    soma = 0;
                }
            }
            break;
        }
        case 3: {
            for (dC = 1; dC < dice_sides+1; dC++) {
                for (dA = 1; dA < dice_sides+1; dA++) {
                    for (dB = 1; dB < dice_sides+1; dB++) {
                        soma = dA + dB + dC;
                        if (soma <= dif) {
                            sucess++;
                        }
                        total++;
                        soma = 0;
                    }
                }
            }
            break;
        }
        case 4: {
            for (dD = 1; dD < dice_sides+1; dD++) {
                for (dC = 1; dC < dice_sides+1; dC++) {
                    for (dA = 1; dA < dice_sides+1; dA++) {
                        for (dB = 1; dB < dice_sides+1; dB++) {
                            soma = dA + dB + dC + dD;
                            if (soma <= dif) {
                                sucess++;
                            }
                            total++;
                            soma = 0;
                        }
                    }
                }
            }
            break;
        }
        case 5: {
            for (dE = 1; dE < dice_sides+1; dE++) {
                for (dD = 1; dD < dice_sides+1; dD++) {
                    for (dC = 1; dC < dice_sides+1; dC++) {
                        for (dA = 1; dA < dice_sides+1; dA++) {
                            for (dB = 1; dB < dice_sides+1; dB++) {
                                soma = dA + dB + dC + dD + dE;
                                if (soma <= dif) {
                                    sucess++;
                                }
                                total++;
                                soma = 0;
                            }
                        }
                    }
                }
            }
            break;
        }
        case 6: {
            for (dF = 1; dF < dice_sides+1; dF++ ) {
                for (dE = 1; dE < dice_sides+1; dE++) {
                    for (dD = 1; dD < dice_sides+1; dD++) {
                        for (dC = 1; dC < dice_sides+1; dC++) {
                            for (dA = 1; dA < dice_sides+1; dA++) {
                                for (dB = 1; dB < dice_sides+1; dB++) {
                                    soma = dA + dB + dC + dD + dE + dF;
                                    if (soma <= dif) {
                                        sucess++;
                                    }
                                    total++;
                                    soma = 0;
                                }
                            }
                        }
                    }
                }
            }
            break;
        }
        case 7: {
            for (dG = 1; dG < dice_sides+1; dG++ ) {
                for (dF = 1; dF < dice_sides+1; dF++ ) {
                    for (dE = 1; dE < dice_sides+1; dE++) {
                        for (dD = 1; dD < dice_sides+1; dD++) {
                            for (dC = 1; dC < dice_sides+1; dC++) {
                                for (dA = 1; dA < dice_sides+1; dA++) {
                                    for (dB = 1; dB < dice_sides+1; dB++) {
                                        soma = dA + dB + dC + dD + dE + dF + dG;
                                        if (soma <= dif) {
                                            sucess++;
                                        }
                                        total++;
                                        soma = 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
        }



    }

    float percentual = 0.0;
    percentual = (sucess / total) * 100.0;

    printf("Num Dices: %d, Dice type: D%d, Dif: %d, Sucessos: %d, Total: %d, Percentual:%f\n", dices_num, dice_sides, dif, (int)sucess, (int)total, percentual);
}





int main(int argc, char *argv[]) {
    srand(time(NULL));
    int dif = atoi(argv[1]);

    /*
    printf("=======================\n");

    printf("Num capacidades 2: vref = 2 * 3 + (4)[Muito fácil]; "); dice_eval3(2,6,10);
    printf("Num capacidades 3: vref = 3 * 3 + (4)[-----------]; "); dice_eval3(3,6,13);
    printf("Num capacidades 4: vref = 4 * 3 + (4)[-----------]; "); dice_eval3(4,6,16);
    printf("Num capacidades 5: vref = 5 * 3 + (4)[-----------]; "); dice_eval3(5,6,19);
    printf("Num capacidades 6: vref = 6 * 3 + (4)[-----------]; "); dice_eval3(6,6,22);
    printf("Num capacidades 7: vref = 7 * 3 + (4)[-----------]; "); dice_eval3(7,6,25);

    printf("=======================\n");

    printf("Num capacidades 2: vref = 2 * 3 + (2)[Fácil]; "); dice_eval3(2,6,8);
    printf("Num capacidades 3: vref = 3 * 3 + (2)[-----]; "); dice_eval3(3,6,11);
    printf("Num capacidades 4: vref = 4 * 3 + (2)[-----]; "); dice_eval3(4,6,14);
    printf("Num capacidades 5: vref = 5 * 3 + (2)[-----]; "); dice_eval3(5,6,17);
    printf("Num capacidades 6: vref = 6 * 3 + (2)[-----]; "); dice_eval3(6,6,20);
    printf("Num capacidades 7: vref = 7 * 3 + (2)[-----]; "); dice_eval3(7,6,23);


    printf("=======================\n");

    printf("Num capacidades 2: vref = 2 * 3 + (1)[Trivial]; "); dice_eval3(2,6,7);
    printf("Num capacidades 3: vref = 3 * 3 + (1)[Trivial]; "); dice_eval3(3,6,10);
    printf("Num capacidades 4: vref = 4 * 3 + (1)[Trivial]; "); dice_eval3(4,6,13);
    printf("Num capacidades 5: vref = 5 * 3 + (1)[Trivial]; "); dice_eval3(5,6,16);
    printf("Num capacidades 6: vref = 6 * 3 + (1)[Trivial]; "); dice_eval3(6,6,19);
    printf("Num capacidades 7: vref = 7 * 3 + (1)[Trivial]; "); dice_eval3(7,6,22);

    printf("=======================\n");

    printf("Num capacidades 2: vref = 2 * 3 + (0)[Médio]; "); dice_eval3(2,6,6); // Referencia
    printf("Num capacidades 3: vref = 3 * 3 + (0)[Médio]; "); dice_eval3(3,6,9);
    printf("Num capacidades 4: vref = 4 * 3 + (0)[Médio]; "); dice_eval3(4,6,12);
    printf("Num capacidades 5: vref = 5 * 3 + (0)[Médio]; "); dice_eval3(5,6,15);
    printf("Num capacidades 6: vref = 6 * 3 + (0)[Médio]; "); dice_eval3(6,6,18);
    printf("Num capacidades 7: vref = 7 * 3 + (0)[Médio]; "); dice_eval3(7,6,21);

    printf("=======================\n");

    printf("Num capacidades 2: vref = 2 * 3 + (-1)[Desafiador]; "); dice_eval3(2,6,5);
    printf("Num capacidades 3: vref = 3 * 3 + (-1)[----------]; "); dice_eval3(3,6,8);
    printf("Num capacidades 4: vref = 4 * 3 + (-1)[----------]; "); dice_eval3(4,6,11);
    printf("Num capacidades 5: vref = 5 * 3 + (-1)[----------]; "); dice_eval3(5,6,14);
    printf("Num capacidades 6: vref = 6 * 3 + (-1)[----------]; "); dice_eval3(6,6,17);
    printf("Num capacidades 7: vref = 7 * 3 + (-1)[----------]; "); dice_eval3(7,6,20);

    printf("=======================\n");

    printf("Num capacidades 2: vref = 2 * 3 + (-2)[Dificil]; "); dice_eval3(2,6,4);
    printf("Num capacidades 3: vref = 3 * 3 + (-2)[-------]; "); dice_eval3(3,6,7);
    printf("Num capacidades 4: vref = 4 * 3 + (-2)[-------]; "); dice_eval3(4,6,10);
    printf("Num capacidades 5: vref = 5 * 3 + (-2)[-------]; "); dice_eval3(5,6,13);
    printf("Num capacidades 6: vref = 6 * 3 + (-2)[-------]; "); dice_eval3(6,6,16);
    printf("Num capacidades 7: vref = 7 * 3 + (-2)[-------]; "); dice_eval3(7,6,19);

    printf("=======================\n");

    printf("Num capacidades 2: vref = 2 * 3 + (-3)[Extremamente difícil]; "); dice_eval3(2,6,3);
    printf("Num capacidades 3: vref = 3 * 3 + (-3)[--------------------]; "); dice_eval3(3,6,6);
    printf("Num capacidades 4: vref = 4 * 3 + (-3)[--------------------]; "); dice_eval3(4,6,9);
    printf("Num capacidades 5: vref = 5 * 3 + (-3)[--------------------]; "); dice_eval3(5,6,12);
    printf("Num capacidades 6: vref = 6 * 3 + (-3)[--------------------]; "); dice_eval3(6,6,15);
    printf("Num capacidades 7: vref = 7 * 3 + (-3)[--------------------]; "); dice_eval3(7,6,18);

    printf("=======================\n");

    printf("Num capacidades 2: vref = 2 * 3 + (-4)[Praticamente impossível]; "); dice_eval3(2,6,2);
    printf("Num capacidades 3: vref = 3 * 3 + (-4)[-----------------------]; "); dice_eval3(3,6,5);
    printf("Num capacidades 4: vref = 4 * 3 + (-4)[-----------------------]; "); dice_eval3(4,6,8);
    printf("Num capacidades 5: vref = 5 * 3 + (-4)[-----------------------]; "); dice_eval3(5,6,11);
    printf("Num capacidades 6: vref = 6 * 3 + (-4)[-----------------------]; "); dice_eval3(6,6,14);
    printf("Num capacidades 7: vref = 7 * 3 + (-4)[-----------------------]; "); dice_eval3(7,6,17);
    */

    /*
    printf("Avaliação 3D8\n");
    for (int i = 3; i < 25; i++) {
        dice_eval3(3,8,i);
    }

    printf("Avaliação 3D12\n");
    for (int i = 3; i < 37; i++) {
        dice_eval3(3,12,i);
    }
    */

    printf("Avaliação 5D6\n");
    for (int i = 5; i < 31; i++) {
        dice_eval3(5,6,i);
    }


    /*
    printf("Avaliação 2D12\n");
    for (int i = 2; i < 25; i++) {
        dice_eval3(2,12,i);
    }
    */


    /*
    printf("Avaliação 3D10\n");
    for (int i = 3; i < 31; i++) {
        dice_eval3(3,10,i);
    }
    */



    return 0;
}  

