#include <stdio.h>
#include <stdlib.h>


int percentual_base(int n_capacidades, int somatorio_capacidades) {
    if (n_capacidades < 1 || n_capacidades > 6) {
        printf("Invalid number of capacities...\n");
        return 0;
    }

    if (somatorio_capacidades < n_capacidades || somatorio_capacidades > (n_capacidades * 6)) {
        printf("Invalid capacities sigma...\n");
        return 0;
    }

    
    switch (n_capacidades) {
        case 1: {
            switch (somatorio_capacidades) {
                case 1: return 16;
                case 2: return 32;
                case 3: return 48;
                case 4: return 64;
                case 5: return 80;
                case 6: return 96;
            }
            break;
        }
        case 2: {
            switch (somatorio_capacidades) {
                case 2: return 16;
                case 3: return 24;
                case 4: return 32;
                case 5: return 40;
                case 6: return 48;
                case 7: return 56;
                case 8: return 64;
                case 9: return 72;
                case 10: return 80;
                case 11: return 88;
                case 12: return 96;
          }
            break;
        }
        case 3: {
            switch (somatorio_capacidades) {
                case 3: return 16;
                case 4: return 21;
                case 5: return 27;
                case 6: return 32;
                case 7: return 37;
                case 8: return 43;
                case 9: return 48;
                case 10: return 53;
                case 11: return 59;
                case 12: return 64;
                case 13: return 69;
                case 14: return 75;
                case 15: return 80;
                case 16: return 85;
                case 17: return 91;
                case 18: return 96;
            }
            break;
        }
        case 4: {
            switch (somatorio_capacidades) {
                case 4: return 16;
                case 5: return 20;
                case 6: return 24;
                case 7: return 28;
                case 8: return 32;
                case 9: return 36;
                case 10: return 40;
                case 11: return 44;
                case 12: return 48;
                case 13: return 52;
                case 14: return 56;
                case 15: return 60;
                case 16: return 64;
                case 17: return 68;
                case 18: return 72;
                case 19: return 76;
                case 20: return 80;
                case 21: return 84;
                case 22: return 88;
                case 23: return 92;
                case 24: return 96;
            }
            break;
        }
        case 5: {
            switch (somatorio_capacidades) {
                case 5: return 16;
                case 6: return 19;
                case 7: return 22;
                case 8: return 26;
                case 9: return 29;
                case 10: return 32;
                case 11: return 35;
                case 12: return 38;
                case 13: return 42;
                case 14: return 45;
                case 15: return 48;
                case 16: return 51;
                case 17: return 54;
                case 18: return 58;
                case 19: return 61;
                case 20: return 64;
                case 21: return 68;
                case 22: return 70;
                case 23: return 74;
                case 24: return 77;
                case 25: return 80;
                case 26: return 83;
                case 27: return 86;
                case 28: return 90;
                case 29: return 93;
                case 30: return 96;
            }
            break;
        }
        case 6: {
            switch (somatorio_capacidades) {
                case 6: return 16;
                case 7: return 19;
                case 8: return 21;
                case 9: return 24;
                case 10: return 27;
                case 11: return 29;
                case 12: return 32;
                case 13: return 35;
                case 14: return 37;
                case 15: return 40;
                case 16: return 43;
                case 17: return 45;
                case 18: return 48;
                case 19: return 51;
                case 20: return 53;
                case 21: return 56;
                case 22: return 59;
                case 23: return 61;
                case 24: return 64;
                case 25: return 67;
                case 26: return 69;
                case 27: return 72;
                case 28: return 75;
                case 29: return 77;
                case 30: return 80;
                case 31: return 82;
                case 32: return 85;
                case 33: return 88;
                case 34: return 91;
                case 35: return 93;
                case 36: return 96;
            }
            break;
        }
    }
    return 0;
}


int main(int argc, char *argv[]) {
    int resp; resp = percentual_base(atoi(argv[1]), atoi(argv[2]));
    if ( resp == 0 ) {
        printf("Finalizando o programa...\n");
        return 1;
    }

    printf("Percentual base: %i\n", resp);
    return 0;
}
