#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int str2int(char *string) {
    int v = 0;
    int len = strlen(string);
    for (int i = 0; i < len; i++) {
        v += (int)string[i];
    }
    return v;
}

int main(int argc, char *argv[]) {

    for (int i = 0; i < argc; i++) {
        printf("%s %i \n", argv[i], str2int(argv[i]));
    }

    return  0;
}


