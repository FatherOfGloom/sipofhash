#include "siphash.h"
#include "stdio.h"

typedef unsigned short u16;
typedef unsigned char u8;
typedef int i32;
typedef unsigned long long u64;
typedef int err_t;

#define HASH_BUF_SIZE 8
#define Ok 0
#define Err -1

#define SET_HASH_HEY 0x05d0

typedef struct SipSet {
    void* table;
} SipSet;

#define return_defer(x) \
    do {                \
        result = (x);   \
        goto defer;     \
    } while (0)

i32 hash_eq_u64(void* hash1, void* hash2) {
    return *(u64*)hash1 == *(u64*)hash2;
}

#define b_to_cstr(x) (x ? "true" : "false")

#define DEBUG_SIPHASH

i32 main(void) {
    err_t result = Ok;

    const char* input_1 = "test input data";
    const char* input_2 = "test input data";

    u16 key = 0x05d0;
    u8 hash_buf_1[HASH_BUF_SIZE] = {0};
    u8 hash_buf_2[HASH_BUF_SIZE] = {0};

    printf("hash1: 0x%08x\n", *(u64*)hash_buf_1);
    printf("hash2: 0x%08x\n", *(u64*)hash_buf_2);

    (void)siphash(input_1, strlen(input_1), &key, hash_buf_1, sizeof(hash_buf_1));
    (void)siphash(input_2, strlen(input_2), &key, hash_buf_2, sizeof(hash_buf_2));

    printf("hash1: 0x%08x\n", *(u64*)hash_buf_1);
    printf("hash2: 0x%08x\n", *(u64*)hash_buf_2);

    printf("hash1 == hash2:\n%s", b_to_cstr(hash_eq_u64(hash_buf_1, hash_buf_2)));

    FILE* f = fopen("hash.out", "w");

    if (f == NULL) {
        return_defer(Err);
    }

    (void)fwrite(hash_buf_1, sizeof(hash_buf_1), 1, f);

defer:
    if (f) fclose(f);

    return result;
}