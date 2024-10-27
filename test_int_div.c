#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int _c_return_int_division_form_int(int n, int v) {
    int resposta = n/v;
    return resposta;
}

int _c_return_int_division_form_float(float n, int v) {
    int resposta = (int)trunc(n/v);
    return resposta;
}

void _c_return_binary_indexes(int num_elements) {
    int tmp = num_elements;
    int subarrays_indexes = 0;
    int current_idx = 0;

    // 2 4 8 16 32 64 128 256 512

    while (1) {
        if (tmp >= 512) {
            printf("(%d, %d)\n", current_idx, current_idx+512);
            subarrays_indexes += 2;
            current_idx += 512;
            tmp -= 512;
        } else if (tmp < 512 && tmp >= 256) {
            printf("(%d, %d)\n", current_idx, current_idx+256);
            subarrays_indexes += 2;
            current_idx += 256;
            tmp -= 256;
        } else if (tmp < 256 && tmp >= 128) {
            printf("(%d, %d)\n", current_idx, current_idx+128);
            subarrays_indexes += 2;
            current_idx += 128;
            tmp -= 128;
        } else if (tmp < 128 && tmp >= 64) {
            printf("(%d, %d)\n", current_idx, current_idx+64);
            subarrays_indexes += 2;
            current_idx += 64;
            tmp -= 64;
        } else if (tmp < 64 && tmp >= 32) {
            printf("(%d, %d)\n", current_idx, current_idx+32);
            subarrays_indexes += 2;
            current_idx += 32;
            tmp -= 32;
        } else if (tmp < 32 && tmp >= 16) {
            printf("(%d, %d)\n", current_idx, current_idx+16);
            subarrays_indexes += 2;
            current_idx += 16;
            tmp -= 16;
        } else if (tmp < 16 && tmp >= 8) {
            printf("(%d, %d)\n", current_idx, current_idx+8);
            subarrays_indexes += 2;
            current_idx += 8;
            tmp -= 8;
        } else if (tmp < 8 && tmp >= 4) {
            printf("(%d, %d)\n", current_idx, current_idx+4);
            subarrays_indexes += 2;
            current_idx += 4;
            tmp -= 4;
        } else {
            printf("(%d, %d)\n", current_idx, current_idx+tmp);
            break;
        }
    }
}

int main() {
    int r1 = _c_return_int_division_form_float(23.4, 7);
    int r2 = _c_return_int_division_form_int(23, 7);
    int r3 = _c_return_int_division_form_int(34, 5);
    int r4 = _c_return_int_division_form_int(32, 5);

    printf("%d\n", r1);
    printf("%d\n", r2);
    printf("%d\n", r3);
    printf("%d\n", r4);

    _c_return_binary_indexes(2222);

    return 0;
}

