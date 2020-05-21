#include <stdio.h>
#include <string.h>
#include <string.h>
#include <omp.h>
#include <openssl/sha.h>

int main(void)
{
    const unsigned char s[5] = "tan0";
    unsigned char *d = SHA256(s, strlen(s), 0);

    int i;

    for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        printf("%02x-", d[i]);
    }
    // dc-34-80-85-d1-4f-ef-a6-92-ad-f1-e7-d9-7e-2d-59-25-3c-01-18-93-59-87-31-86-d3-76-eb-e0-f3-ad-3a-
    putchar('\n');
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        printf("%d-", d[i]);
    }
    // 220-52-128-133-209-79-239-166-146-173-241-231-217-126-45-89-37-60-1-24-147-89-135-49-134-211-118-235-224-243-173-58-
    putchar('\n');
    return 0;
}