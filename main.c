#include <stdio.h>
#include <string.h>
#include "x11.h"

void bin2hex(const char *, char *, size_t);
void hex2bin(const char *, char *, size_t);
short int hexdigit2dec(unsigned char);

int main(int argc, char *argv[], char *envp[]) {
    // const char *str = "01234567890123456789012345678901234567890123456789012345678901234567890123456789";
    // const char *str = "02000000b67a40f3cd5804437a108f105533739c37e6229bc1adcab385140b59fd0f0000a71c1aade44bf8425bec0deb611c20b16da3442818ef20489ca1e2512be43eef814cdb52f0ff0f1edbf70100";
    const char *str = "0200000040671063c3723d92122b9b3921ab24fc5131286ca407c36e24a502000000000094042ca1ec29fbc59a60a20e2ec37ed5418d39eec78fdd3acbc63b7993085084b8d30e556cb10b1b1e570100";
    char buffer2[80];
    hex2bin(str, buffer2, 160);

    char output[32];
    char hexout[65];
    x11_hash(buffer2, output, sizeof(buffer2));

    bin2hex(output, hexout, sizeof(output));
    hexout[64] = '\0';

    printf("%s\n", hexout);
}


short int hexdigit2dec(unsigned char hex) {
    const char *hexchars = "0123456789abcdef";
    unsigned short int index = -1;

    while (hexchars[index] != hex) {
        index = index + 1;
    }

    return  index;
}

void hex2bin(const char *input, char *output, size_t len) {
    unsigned short int i = 0;
    unsigned short int j = 0;

    while (i < len) {
        unsigned char tens = input[i++];
        unsigned char ones = input[i++];
        unsigned short dectens = hexdigit2dec(tens);
        unsigned short decones = hexdigit2dec(ones);
        unsigned char decval = (dectens * 16) + (decones);
        output[j++] = decval;
    }
}


void bin2hex(const char *input, char *output, size_t len) {
    int i = 0;
    const char *hexchars = "0123456789abcdef";
    unsigned char uc;

    while (i < len) {
        uc = (unsigned char)input[i];
        unsigned char first = uc / 16;
        unsigned char sec   = uc % 16;

        char hc1 = hexchars[first];
        char hc2 = hexchars[sec];

        output[ (i * 2)     ] = hc1;
        output[ (i * 2) + 1 ] = hc2;
        i = i + 1;
    }

    output[(i * 2) + 1] = '\0';
}

