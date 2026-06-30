#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <wincrypt.h>
#include <stdbool.h>

#pragma comment(lib, "advapi32.lib")

int main() {
    const char *base = "reyedfim";

    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;

    BYTE hash[16];
    DWORD hashLen = sizeof(hash);

    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL,
                             CRYPT_VERIFYCONTEXT)) {
        printf("CryptAcquireContext failed: %lu\n", GetLastError());
        return 1;
    }
    int pos = 0;
    char answer[8];
    char second[9];
    int secondused = 0;
    int ansindex = 0;
    for (long index = 0; index < 1000000000; index++) {
        // 1. Build the input string: base + index
        char numstr[20];
        itoa(index, numstr, 10);

        size_t passLen = strlen(base) + strlen(numstr) + 1;
        char *pass = malloc(passLen);
        strcpy(pass, base);
        strcat(pass, numstr);

        // 2. Create a fresh hash object each iteration
        if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
            printf("CryptCreateHash failed: %lu\n", GetLastError());
            free(pass);
            break;
        }

        // 3. Hash the input
        if (!CryptHashData(hHash, (BYTE *)pass, (DWORD)strlen(pass), 0)) {
            printf("CryptHashData failed: %lu\n", GetLastError());
            CryptDestroyHash(hHash);
            free(pass);
            break;
        }

        // 4. Get the hash value
        hashLen = sizeof(hash);
        if (!CryptGetHashParam(hHash, HP_HASHVAL, hash, &hashLen, 0)) {
            printf("CryptGetHashParam failed: %lu\n", GetLastError());
            CryptDestroyHash(hHash);
            free(pass);
            break;
        }
        if (hash[0] != 0 && hash[1] != 0) {
            CryptDestroyHash(hHash);
            free(pass);
            continue;
        }

        // 5. Convert to hex string
        char hexHash[33];
        for (int i = 0; i < 16; i++) {
            sprintf(hexHash + i * 2, "%02x", hash[i]);
            //            printf("%02x", hexHash[i]);
        }
        hexHash[32] = '\0';

        // 6. Check for 5 leading zeros
        if (strncmp(hexHash, "00000", 5) == 0) {
            printf("Winner! index=%ld  input=\"%s\"  MD5=%s\n", index, pass,
                   hexHash);
            if (ansindex < 8) {
                answer[ansindex++] = hexHash[5];
            }

            if (secondused < 8) {
                //               answer[ansindex++] = hexHash[5];
                // pos = hexHash[5];
                pos = hexHash[5] - '0';
                if (pos < 8) {
                    if (second[pos] == '\0') {
                        second[pos] = hexHash[6];
                        secondused++;
                    }
                }
                CryptDestroyHash(hHash);
                free(pass);
                // ansindex++;
                continue;
            } else
                break;
        }

        CryptDestroyHash(hHash);
        free(pass);
    }
    second[8] = '\0';
    printf("\n%s\n%s", answer, second);
    CryptReleaseContext(hProv, 0);
    return 0;
}