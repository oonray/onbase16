#ifndef _base_16
#define _base_16

#include <stdlib.h>
#include <dbg.h>
#include <stdint.h>

const char *alphabet = "XoOxGwgWYzZYaBAb";

typedef struct Base16{
    char *data; 
    char *encoded;
    char alphabet[16];
} Base16;

char *get_char(uint8_t data);

Base16 *Base16_create(const char *alphabet);
Base16 *Base16_encode(void *data, int size, const char *alphabet);
Base16 *Base16_decode(char *encoded, const char *alphabet);
void Base16_destroy(Base16 *target);

#endif
