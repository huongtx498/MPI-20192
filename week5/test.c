#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include <omp.h>
#include <openssl/sha.h>

typedef unsigned char byte;

byte *StringHashToByteArray(const char *s)
{
    byte *hash = (byte *)malloc(32);
    char two[3];
    two[2] = 0; // two[2] = NULL, để tránh bộ nhớ tự random kí tự vào vị trí này, thì hàm strtol sẽ chuyển đổi cả kí tự ngẫu nhiên đó.
    char *stop;
    for (int i = 0; i < 32; i++)
    {
        two[0] = s[i * 2];
        two[1] = s[i * 2 + 1];
        hash[i] = (byte)strtol(two, &stop, 16); // chuyển đổi string sang byte array [32] [Ascii]
    }
    return hash;
}

void main(void)
{
    char *stopstring;
    char str[6] = "abcd4";
    byte hash;

    // hash: 6f32ebbc1ee9cf3867df5f86f071ee147c6190ac7bfd88330fd8996a0abb512e

    char sha[3];
    sha[2] = 0; // [2] = NULL

    sha[0] = '3';
    sha[1] = '2';

    hash = (byte)strtol(sha, &stopstring, 16);
    printf("string = %s\n", sha);
    printf("strtol = %c\n", hash);
    printf("Stopped scan at: %s\n\n", stopstring);

    printf("%d \n", str[4]);
    printf("%02x \n\n", str[4]);

    char password[5] = "toan";

    char sPass[5];
    memcpy(sPass, password, 4);
    sPass[4] = 0;
    printf("%s", sPass);
    byte *n = StringHashToByteArray("6f32ebbc1ee9cf3867df5f86f071ee147c6190ac7bfd88330fd8996a0abb512e");
    printf("%hhn\n", n);

    // getch();
}