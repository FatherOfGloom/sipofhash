#include "siphash.h"
#include "stdio.h"
#include "stdlib.h"
#include <assert.h>

typedef unsigned short u16;
typedef unsigned char u8;
typedef int i32;
typedef unsigned long long u64;
typedef int err_t;

#define HASH_BUF_SIZE 8
#define Ok 0
#define Err -1

#define SET_HASH_HEY 0x05d0
#define EXE_NAME "siphash"

#define HASHER_LOG_ERRORS
#define HASHER_ENABLE_STDOUT

#define HEW_KEY_BUF_LEN 16

#define HASHER_AK_SIPHASH 0

static u8 hex_key_buf[HEW_KEY_BUF_LEN];
typedef size_t usize;


#if !defined(EPRINTFLN_TAG)
  #define EPRINTFLN_TAG "Hasher.Error"
#endif

#if !defined(eprintfln)
  #define eprintfln(...)                          \
      do {                                        \
          fprintf(stderr, "%s: ", EPRINTFLN_TAG); \
          fprintf(stderr, __VA_ARGS__);           \
          fprintf(stderr, "\n");                  \
      } while (0);
#endif

#ifdef HASHER_LOG_ERRORS
  #define hasher_log_e(...) eprintfln(__VA_ARGS__)
#else
  #define hasher_log_e(...)
#endif

void hasher_siphash(u8* key, u8 key_len, const void* input_buf, usize input_buf_len,
                    void* output_buf, usize output_buf_len) {
    hasher_log_e("DEBUG: sip_hash called");
}

void hasher_run_ex(u8* key, u8 key_len, const void* input_buf, usize input_buf_len,
                   void* output_buf, usize output_buf_len, u8 algo_kind) {
    switch (algo_kind) {
        case HASHER_AK_SIPHASH:
            hasher_siphash(key, key_len, input_buf, input_buf_len, output_buf,
                           output_buf_len);
            break;
        default:
            hasher_log_e("unimplemented hashing algorithm kind '%d'.", algo_kind);
            exit(1);
    }
}

err_t hasher_parse_hex_key(const char* cstr_hex_key, usize hex_key_len, u8* out_key_buf, u8 out_key_buf_len) {
    err_t result = Ok;

defer:
    return result;
}

void _print_usage(void) {
    fprintf(stderr, "Usage: %s [hexadecimal-key] [target-data]\n", EXE_NAME);
}

#ifdef HASHER_ENABLE_STDOUT
#define print_usage _print_usage 
#else
#define print_usage __preproc_discard
#endif

#define __preproc_discard()

i32 main(i32 argc, char* argv[]) {
    err_t result = Ok;

    sip_test();
    return Ok;

    if (argc != 3) {
        print_usage();
        exit(1);
    }

    hasher_log_e("test '%s %d'", "lol", 3);
defer:
    return result;
} 