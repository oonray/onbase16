#include "16.h"
#include <stdint.h>
#include <string.h>

Base16 *Base16_create(const char *inp_aphabet){ 
    Base16 *out = (Base16 *)calloc(1,sizeof(Base16));
    check_mem(out); 
    
    const char *alpha = inp_aphabet == NULL ? "XoOxGwgWyzZYaBAb":inp_aphabet;
    strcpy(out->alphabet,alpha);

    return out;
error:
    return NULL;
}

void Base16_destroy(Base16 *target){
    if(target->data != NULL){
       free(target->data);  
    }

    if(target->encoded!=NULL){
       free(target->encoded); 
    }

    free(target);
}

static inline int get_b16_char(char *encoded,uint8_t *offsett,size_t size,char alphabet[16]){
    //uint8_t offsett =  AAAABBBB
    if(size <= 0) return 0;
    *encoded = alphabet[HIGH(*offsett)];
    encoded++;
    *encoded = alphabet[LOW(*offsett)];
    encoded++;
    offsett++;
    check(get_b16_char(encoded,offsett,size-sizeof(uint8_t),alphabet)==0,"Error getting characters");
    return 0;
error:
    return -1;
}

Base16 *Base16_encode(void *data,size_t size, const char *inp_alphabet){
   Base16 *out = Base16_create(inp_alphabet);  
   check(out != NULL,"Could not create Base16.");

   uint8_t *Pdata = (uint8_t *)data;
   out->encoded = calloc(CHARSIZE(size),sizeof(char)); 
   check_mem(out->encoded);
   get_b16_char(out->encoded,Pdata,size,out->alphabet);
   check(out->encoded != NULL, "Could not encode data.");
   return out;
error:
   return NULL;
}

static inline uint8_t get_pos_in_alpha(Base16 *base,char a){
    for(uint8_t i = 0;i<16;i++){
        if(base->alphabet[i]==a){
            return i;}
    }
    return 0;
}

static inline int get_b16_data(Base16 *base,char *string,int size){
    base->data = calloc(BYTESIZE(size),sizeof(uint8_t));
    check_mem(base->data);
    uint8_t *Pbad = base->data;

    for(int i = 0;i<size;i+=2){
    uint8_t al = 0;
    uint8_t bl = 0;

    al = get_pos_in_alpha(base,string[i]);
    bl = get_pos_in_alpha(base,string[i+1]);

    uint8_t data =((al<<4)|bl); 

    *(Pbad) = data;
    ++Pbad;
    }
    return 0;
error:
    return -1;
}

Base16 *Base16_decode(char *encoded,size_t size,const char *inp_alphabet){
    Base16 *out = Base16_create(inp_alphabet);
    check(out != NULL,"Could not create Base16");

    char *data = encoded;
    get_b16_data(out,data,size);

    check(out->data != NULL,"Could not Decode data.");
    return out;
error:
    return NULL;
}
