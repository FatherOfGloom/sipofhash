#include "siphash.h"
#include "stdio.h"
#include "stdlib.h"
#include "tests.h"
#include <assert.h>
#include <gmp.h>
#include <ctype.h>

typedef unsigned short u16;
typedef unsigned char u8;
typedef int i32;
typedef unsigned long long u64;
typedef int err_t;

#define HASH_BUF_SIZE 8
#define Ok 0
#define Err -1

#define EXE_NAME "siphash"

#define HASHER_LOG_ERRORS
#define HASHER_ENABLE_CLI

#define HEX_KEY_BUF_LEN 16

#define HASHER_AK_SIPHASH 0

static u8 hex_key_buf[HEX_KEY_BUF_LEN];
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

void _eprint_usage(void) {
    fprintf(stderr, "Usage: %s [hexadecimal-key] [target-data]\n", EXE_NAME);
}

#define __preproc_discard()

#ifdef HASHER_ENABLE_CLI
#define eprint_usage _eprint_usage 
#else
#define eprint_usage __preproc_discard
#endif

typedef struct Slice {
    void* raw;
    usize len;
} Slice;

Slice slice_from_cstr(const char* cstr) {
    return (Slice) {
        .raw = (void*)cstr,
        .len = strlen(cstr),
    };
}

Slice slice_from_buf(const u8 buf[], usize buf_len) {
    return (Slice) {
        .raw = (void*)buf,
        .len = buf_len,
    };
}

#define hasher_assert(predicate, errmsg) { if (!(predicate)) { hasher_log_e(errmsg); exit(1); }}

u8 hex_char_to_u8(char c) {
    if (c > 127) {
        hasher_assert(0, "The input string must be ASCII only");
        return 0;
    }

    c = toupper(c);

    if (c > 64 && c < 71) {
        return c - 55;
    }

    if (c > 47 && c < 58) {
        return c - 48;
    }

    hasher_assert(0, "The input must be a valid hexadecimal value");
    return 0;
}

void parse_hex_16_byte_key(const Slice* key_cstr, Slice* out_buf) {
    hasher_assert(out_buf->len == 16, "Output buffer must be 16 bytes");
    hasher_assert(key_cstr->len == 16 * 2 || key_cstr->len == 16 * 2 + 2, "Input string must be 18 or 16 chars long");
    
    for (i32 i = 0; i < out_buf->len; ++i) {
        char c_high = *((char*)key_cstr->raw + i * 2);
        char c_low = *((char*)key_cstr->raw + i * 2 + 1);

        u8 c_high_out = hex_char_to_u8(c_high);
        u8 c_low_out = hex_char_to_u8(c_low);

        *((char*)out_buf->raw + i) = c_high_out << 4 | c_low_out;
    }
}

int hash_to_file(const char* file_path, Slice* s) {
    err_t result = Ok;

    FILE* f = fopen(file_path, "w");

    if (f == NULL) {
        return_defer(-1);
    }

    (void)fwrite(s->raw, s->len, 1, f);

defer:
    if (f) fclose(f);

    if (result == 0) {
#ifdef _WIN32
        system(
            "powershell -ExecutionPolicy Bypass -Command \"& { ..\\mover.ps1 | Out-Host }\"");
#else  // TODO
  #error "Brother... it's a win32 slop"
#endif
    }
    return result;
}

i32 main(i32 argc, char* argv[]) {
    err_t result = Ok;
    Slice out_key_buf =  {0};
    Slice input_key_cstr = {0}; 
    Slice hashed_val_buf = {0};

    // if (argc != 3) {
    //     eprint_usage();
    //     exit(1);
    // }

    char* key = "7b173d3eb6afd82d04d70256b4bf5a98";
    char* value = "value";

    out_key_buf = slice_from_buf((u8[16]) {0}, 16);
    input_key_cstr = slice_from_cstr(key);
    hashed_val_buf = slice_from_buf((u8[16]) {0}, 16);

    parse_hex_16_byte_key(&input_key_cstr, &out_key_buf);

    hasher_run_ex(out_key_buf.raw, out_key_buf.len, value, strlen(value),
                  hashed_val_buf.raw, hashed_val_buf.len, HASHER_AK_SIPHASH);

    hash_to_file("hash_test.out", &hashed_val_buf);

defer:
    return result;
} 