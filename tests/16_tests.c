#include "minunit.h"
#include <string.h>
#include <16.h>

Base16 *out;
Base16 *out1;
Base16 *out2;


uint32_t test1 = 0xdeadbeef;       // 11 14 14 15 YAAb
uint8_t test2 = 0x00000001; //0000 0001 
char *test3 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";       //65 66 67 0100 0001 0100 0010 0100 0011

char *expected1 = "AbYAZBBA";
char *expected2 = "Xo";
char *expected3 = "GoGOGxGGGwGgGWGyGzGZGYGaGBGAGbwXwowOwxwGwwwgwWwywzwZ";

char *test_create(){
    out = Base16_create(NULL);
    mu_assert(out->data == NULL,"Data not NULL after create.");
    mu_assert(out->encoded == NULL,"Encoded not NULL after create");
    mu_assert(strcmp(out->alphabet,alphabet)==0,"Alphabet not set properly");
    return NULL;
}

char *test_destroy(){
    Base16_destroy(out); 
    return NULL;
}

char *test_encode(){
    out = Base16_encode(&test1,sizeof(uint32_t),NULL);  
    test_info("Value: %s",out->encoded);
    mu_assert(strcmp(out->encoded,expected1)==0,"Encoded Value not correnct!");
    
    out1 = Base16_encode(&test2,sizeof(uint8_t),NULL);  
    test_info("Value: %s",out1->encoded);
    mu_assert(strcmp(out1->encoded,expected2)==0,"Encoded Value not correnct!");
    
    out2 = Base16_encode(test3,strlen(test3)*sizeof(char),NULL);  
    test_info("Value: %s",out2->encoded);
    mu_assert(strcmp(out2->encoded,expected3)==0,"Encoded Value not correnct!");    
}

char *test_decode(){
    out = Base16_decode(out->encoded,strlen(out->encoded),NULL);
    test_error("%x",*((uint32_t *)out->data));
    mu_assert(*((uint32_t *)out->data)==test1,"Wrong value decoded"); 
    
    out1 = Base16_decode(out1->encoded,strlen(out1->encoded),NULL);
    test_error("%x",*((uint8_t *)out1->data));
    mu_assert(*((uint8_t *)out1->data)==test2,"Wrong value decoded"); 
    
    out2 = Base16_decode(out2->encoded,strlen(out2->encoded),NULL);
    test_error("%s",(char *)out2->data);
    mu_assert(*((char *)out2->data)==*(test3),"Wrong value decoded"); 
    return NULL;
}


char *all_tests(){
    mu_suite_start();
    mu_run_test(test_create);
    mu_run_test(test_encode);
    mu_run_test(test_decode);
    mu_run_test(test_destroy);
    return NULL;
}

RUN_TESTS(all_tests);
