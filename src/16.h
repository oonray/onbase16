#ifndef _base_16
#define _base_16

#include <stdlib.h>
#include "dbg.h"
#include <stdint.h>

const char *alphabet = "XoOxGwgWyzZYaBAb";

typedef struct Base16{
    void *data; 
    char *encoded;
    char alphabet[16];
} Base16;

#define HIGH(b) ((((b) >> 4) & 0x0F)) //splits AABB into AA
#define LOW(b) (((b) & 0x0F))         //splits AABB into BB

#define CHARSIZE(a) (((a)/sizeof(uint8_t))*2)
#define BYTESIZE(a) ((a)/2)

/*
 * @brief takes a alphabet and creates a b16 object.
 * @param inp_alphabet The alphabet to use.
 *
 * Takes the 16 first char's from the inp_alphabet and makes them the alphabet for base16.
 * This allows for flexibillity in charset.
 * Will use the default alphabet if inp_alphabet is NULL.
 */
Base16 *Base16_create(const char *inp_alphabet);

/*
 * @brief Encodes arbitrary type data.
 * @param data The data to encode, this can be whatever type bcf void *.
 * @param size the size of the data using sizeof()
 * @param inp_alphabe to use when encodign
 *
 * This is the "main" function.
 * Creates and returns a Base16 object with encoded data.
 * eg. Base16_encode(data,sizeof(data),alphabet);
 */
Base16 *Base16_encode(void *data, size_t size, const char *inp_alphabet);

/*
 * @brief Decodes String into byte data.
 * @param encoded the encoded string data.
 * @param size strlen of the string.
 * @param inp_alphabet the alphabet to use must be the same as encoded.
 */
Base16 *Base16_decode(char *encoded,size_t size, const char *inp_alphabet);

/*
 * @brief Destroys the Base16 object.
 */
void Base16_destroy(Base16 *target);

#endif
