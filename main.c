#include <stdio.h>
#include <string.h>
#include "x11.h"

void bin2hex(const char *, char *, size_t);

int main(int argc, char *argv[], char *envp[]) {
    // const char *str = "Dash";
    const char *str = "01234567890123456789012345678901234567890123456789012345678901234567890123456789";
    char output[32];
    char buffer[(sizeof(output) * 2) + 1];

    /*
    unsigned short int num1, num2;
    num1 = sizeof(output); num2 = sizeof(buffer);
    printf("num1 = %d\n", num1); printf("num2 = %d\n", num2);
    */

    memset(output, '\0', sizeof(output));
    memset(buffer, '\0', sizeof(buffer));

    printf("input string = %s\n", str);
    x11_hash(str, output, 32);
    printf("output = %s\n", output);

    bin2hex(output, buffer, sizeof(output));
    printf("buffer = %s\n", buffer);
}


void bin2hex(const char *input, char *output, size_t len) {
    int i = 0;
    const char *hexchars = "0123456789abcdef";
    unsigned char uc;

    printf("entering WHILE loop\n");
    while (i < len) {
        printf("\ti = %d\n", i);

        uc = (unsigned char)input[i];

        printf("\tinput[%d] = %d (0x%02x)\n", i, uc, uc);

        unsigned char first = uc / 16;
        unsigned char sec   = uc % 16;
        printf("\t\tfirst = %d\n", first);
        printf("\t\tsec   = %d\n", sec);

        char hc1 = hexchars[first];
        char hc2 = hexchars[sec];
        printf("\t\thc1 = %c\n", hc1);
        printf("\t\thc2 = %c\n", hc2);

        output[ (i * 2)     ] = hc1;
        output[ (i * 2) + 1 ] = hc2;
        i = i + 1;
        printf("=================================================================\n");
    }
    printf("left     WHILE loop\n");

    output[(i * 2) + 1] = '\0';
}

