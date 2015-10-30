#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>


#include "hash.h"
#include "argon2.h"

static char* Run(uint8_t *out, uint32_t t_cost, uint32_t m_cost, uint32_t lanes, uint32_t threads,const char* type,
    bool print, const char* clear_text_password) {
    int idx=0;
    const unsigned out_length = 32;
    const unsigned pwd_length = 32;
    const unsigned salt_length = 16;
    const unsigned secret_length = 8;
    const unsigned ad_length = 12;
    bool clear_memory = false;
    bool clear_secret = false;
    bool clear_password = false;
    uint8_t pwd[pwd_length];
    uint8_t salt[salt_length];
    uint8_t secret[secret_length];
    uint8_t ad[ad_length];

    int offset = 0;
    char* hashed_password = NULL;

    memset(pwd, '\0', pwd_length);
    memcpy(pwd, clear_text_password, strlen(clear_text_password));
    memset(salt, 2, salt_length);
    memset(secret, 3, secret_length);
    memset(ad, 4, ad_length);

    Argon2_Context context={out, out_length, pwd, pwd_length, salt, salt_length,
            secret, secret_length, ad, ad_length, t_cost, m_cost, lanes, lanes,
            NULL, NULL,
            clear_password, clear_secret, clear_memory,print};

    Argon2d(&context);

    hashed_password = (char*)calloc( 1, 512 );
        for( idx=0; idx<context.outlen; idx++ ) {
        sprintf( &hashed_password[offset], "%02x", context.out[idx] );
        offset+=2;
    }

    return hashed_password;
}

static char* do_hash( const char* clear_text_password ) {
    unsigned char out[32];
    uint32_t m_cost = 1 << 18;
    uint32_t t_cost = 3;
    uint32_t lanes=4;
    uint32_t threads = 4;

    char* hashed_password = Run(out,  t_cost, m_cost, lanes, threads, "Argon2d", false, clear_text_password);
    return  hashed_password;
}


char* hash_password( const char* clear_text_password ) {
    return do_hash(clear_text_password);
}

