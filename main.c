#include <stdio.h>
#include <string.h>
#include "x11.h"

void bin2hex(const char *, char *, size_t);
void hex2bin(const char *, char *, size_t);
unsigned short int hexdigit2dec(unsigned char);

int main(int argc, char *argv[], char *envp[]) {
    const char *str = "02000000b67a40f3cd5804437a108f105533739c37e6229bc1adcab385140b59fd0f0000a71c1aade44bf8425bec0deb611c20b16da3442818ef20489ca1e2512be43eef814cdb52f0ff0f1edbf70100";
    // const char *str = "0200000040671063c3723d92122b9b3921ab24fc5131286ca407c36e24a502000000000094042ca1ec29fbc59a60a20e2ec37ed5418d39eec78fdd3acbc63b7993085084b8d30e556cb10b1b1e570100";
    char buffer2[80];

    // convert input to binary data buffer
    hex2bin(str, buffer2, 160);

    char output[32];
    char hexout[65];
    hexout[64] = '\0';

    x11_hash(buffer2, output, sizeof(buffer2));
    bin2hex(output, hexout, sizeof(output));

    printf("%s\n", hexout);
}

unsigned short int hexdigit2dec(unsigned char hex) {
    const char *hexchars = "0123456789abcdef";
    unsigned short int index = 0;

    while (hexchars[index] != hex) {
        index = index + 1;
    }

    return index;
}

void hex2bin(const char *input, char *output, size_t len) {
    unsigned short int i = 0;
    unsigned short int j = 0;

    while (i < len) {
        // first the tens place, then the ones
        unsigned short tens = hexdigit2dec((unsigned char)input[i]);
        unsigned short ones = hexdigit2dec((unsigned char)input[i + 1]);

        // multiply/add to get the value
        output[j] = (tens * 16) + ones;
        
        // increment counters
        i = i + 2;
        j = j + 1;
    }
}

void bin2hex(const char *input, char *output, size_t len) {
    int i = 0;
    const char *hexchars = "0123456789abcdef";

    while (i < len) {
        output[ (i * 2)     ] = hexchars[(unsigned char)input[i] / 16];
        output[ (i * 2) + 1 ] = hexchars[(unsigned char)input[i] % 16];
        i = i + 1;
    }
}
