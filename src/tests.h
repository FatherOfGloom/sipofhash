#ifndef TESTS_H_
#define TESTS_H_

#include "stdint.h"
#include "stdio.h"
#include "utils.h"
#include "siphash.h"

#define b_to_cstr(x) (x ? "true" : "false")
#define HASH_BUF_SIZE 8

static uint8_t sip_test_key[] = {0xFF, 0x01, 0xFF, 0x02, 0xFF, 0x03, 0xFF, 0x04,
                                 0xFF, 0x05, 0xFF, 0x06, 0x00, 0x07, 0x00, 0x08};

int hash_eq_uint64_t(void* hash1, void* hash2) {
    return *(uint64_t*)hash1 == *(uint64_t*)hash2;
}

int sip_test(void) {
    int result = 0;

    assert(sizeof(sip_test_key) == 16 && "invalid hash key size");

#ifdef _WIN32
    system("powershell -ExecutionPolicy Bypass -File ..\\mover.ps1");
#else // TODO
  #error "Brother... it's a win32 slop"
#endif

    const char* input_1 = "test input data";
    const char* input_2 = "test input data";

    uint8_t hash_buf_1[HASH_BUF_SIZE] = {0};
    uint8_t hash_buf_2[HASH_BUF_SIZE] = {0};

    printf("hash1: 0x%08x\n", *(uint64_t*)hash_buf_1);
    printf("hash2: 0x%08x\n", *(uint64_t*)hash_buf_2);

    (void)siphash(input_1, strlen(input_1), &sip_test_key, hash_buf_1,
                  sizeof(hash_buf_1));
    (void)siphash(input_2, strlen(input_2), &sip_test_key, hash_buf_2,
                  sizeof(hash_buf_2));

    printf("hash1: 0x%08x\n", *(uint64_t*)hash_buf_1);
    printf("hash2: 0x%08x\n", *(uint64_t*)hash_buf_2);

    printf("hash1 == hash2:\n%s", b_to_cstr(hash_eq_uint64_t(hash_buf_1, hash_buf_2)));

    FILE* f = fopen("hash.out", "w");

    if (f == NULL) {
        return_defer(-1);
    }

    (void)fwrite(hash_buf_1, sizeof(hash_buf_1), 1, f);
defer:
    if (f) fclose(f);
}
#endif  // TESTS_H_