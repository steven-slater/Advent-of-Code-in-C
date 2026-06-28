#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincrypt.h>

#pragma comment(lib, "advapi32.lib")
int main() {
    char *input = "abc";

    char *pass = calloc(strlen(input) + 2, sizeof(char));
    pass = strdup(input);
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;

    DWORD dataLen = (DWORD)strlen(pass);

    BYTE hash[16]; // MD5 = 16 bytes
    DWORD hashLen = sizeof(hash);

    // Acquire crypto provider context
    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL,
                             CRYPT_VERIFYCONTEXT)) {
        printf("CryptAcquireContext failed: %lu\n", GetLastError());
        return 1;
    }

    // Create MD5 hash object
    if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
        printf("CryptCreateHash failed: %lu\n", GetLastError());
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    // Hash data
    if (!CryptHashData(hHash, (BYTE *)pass, dataLen, 0)) {
        printf("CryptHashData failed: %lu\n", GetLastError());
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    // Get hash value
    if (!CryptGetHashParam(hHash, HP_HASHVAL, hash, &hashLen, 0)) {
        printf("CryptGetHashParam failed: %lu\n", GetLastError());
    } else {
        // Print as hex
        long index = 0;

        printf("MD5(\"%s\") = ", input);
        printf("\n");
        while (index++ < 1000000000) {
            for (DWORD i = 0; i < hashLen; i++) {
                printf("%02x", hash[i]);
                if (hash[i] != 0) {
                    input = calloc(strlen(pass) + 1, sizeof(char));
                    input = strdup(pass);
                    char numstr[612];
                    itoa(index, numstr, 10);
                    strcat(input, numstr);
                    pass = strdup(input);
                    if (!CryptHashData(hHash, (BYTE *)pass, dataLen, 0)) {
                        printf("CryptHashData failed: %lu\n", GetLastError());
                        CryptDestroyHash(hHash);
                        CryptReleaseContext(hProv, 0);
                    }
                    continue;
                }
            }
            printf("\n");
        }
    }

    // Cleanup
    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);

    return 0;
}