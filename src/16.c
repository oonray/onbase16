#include <16.h>

Base16 *Base16_create(const char *inp_aphabet){
    Base16 *out = (Base16 *)calloc(1,sizeof(Base16));
    check_mem(out); 
    
    const char *alpha = inp_aphabet == NULL ? alphabet:inp_aphabet;
    memccpy(out->alphabet,alpha,16,sizeof(char));

    out->data=NULL;
    out->encoded=NULL;

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

Base16 *Base16_encode(void *data,int size, const char *alphabet){
   Base16 out = Base16_create()   
}
