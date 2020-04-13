#ifndef _base_16
#include "16/16.h"
#endif
#include "dbg.h"
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

char *inp_file;
char *out_file;
bool ed[] = {false,false};
char *xfoa[] = {NULL,NULL,NULL,NULL};

void *read_file(char *filename){    
    FILE *f = fopen(filename,"rb");
    check(f!=NULL,"Could not open file.");
    int filelen = 0;
    void * buffer;

    fseek(f, 0, SEEK_END);          
    filelen = ftell(f);             
    rewind(f);                      
    
    buffer = (char *)malloc(filelen * sizeof(char)); 
    fread(buffer, filelen, 1, f); 
    fclose(f); 
    return buffer;
error:
    return NULL;
}

int write_file(char *filename,void *data,size_t size){
   FILE *f = fopen(filename,"wb"); 
   check(f!=NULL,"Could not open file");
   int ret = fwrite(data,size,1,f); 
   fclose(f);
   return ret;
error:
   return 0;
}

void print_str(char *data){
    printf("%s\n",data);
}

void print_byte(void *data,int size){ 
    uint8_t *pd = data;
    for(int i=0;i<size/sizeof(uint8_t);i++){
        printf("%x",*pd); 
        ++pd;
    }
}

int print_help(char *name){
    printf("%s -[edf] [data/inpfile] [-o] [outfile] [-a] [alphabet]",name);
    printf("\nEncodes input data/file to base16.");
    printf("\nIf no output file is specified it will printthe data to stdout");
    printf("\n\t-h\tHelp");
    printf("\n\t-e\tEncode");
    printf("\n\t-d\tDecode");
    printf("\n\t-x\tData");
    printf("\n\t-f\tInput File");
    printf("\n\t-o\tOutput File");
    printf("\n\t-a\tAlphabet. If none is provided default will be used.");
    return 0;
}


int main(int argc,char *argv[]){
  int c = 0;
  while ((c = getopt (argc, argv, "edfoax:")) != -1){
    switch (c)
      {
      case 'e':
        ed[0] = true;
        break;
      case 'd':
        ed[1] = true;
        break;
      case 'x':
        xfoa[0] = optarg;
        break;
      case 'f':
        xfoa[1] = optarg;
        break;
      case 'o':
        xfoa[2] = optarg;
        break;
      case 'a':
        xfoa[3] = optarg;
        break;
      case '?':
        if (optopt == 'f' || optopt == 'o' || optopt == 'a')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt); 
        else if (isprint(optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        print_help(argv[0]);
        return -1;
        break;
      default:
        print_help(argv[0]);
        abort();
        }     
    }

    if(ed[0] && ed[1]){
        log_err("You must choose eigther encode or decode!");
        exit(-1);
    } 
    if(!ed[0] && !ed[1]){
        log_err("Must eigter decode or encode");
    }
    if(xfoa[0] != NULL && xfoa[1] != NULL){
        log_err("Cannot read from file and suply data!");
        exit(-1);
    }
    if(xfoa[0] == NULL && xfoa[1] == NULL){
        log_err("Must suply eigther file or data");
    }


    Base16 *out = NULL;

    if(ed[0]){
        log_info("encoding.");
        if(xfoa[1]!=NULL){
            void *data = read_file(xfoa[1]);
            out = Base16_encode(data,sizeof(*data),xfoa[3]);
        }
        if(xfoa[0]!=NULL){
            out = Base16_encode(xfoa[0],strlen(xfoa[0])*sizeof(char),xfoa[3]);
        }
        if(xfoa[2]!=NULL){
            write_file(xfoa[2],out->encoded,strlen(out->encoded)*sizeof(char)); 
        }else{
            print_str(out->encoded);
        }
    }

    if(ed[1]){
        log_info("decoding.");
        if(xfoa[1]!=NULL){
            void *data = read_file(xfoa[1]);
            out = Base16_decode(data,sizeof(*data),xfoa[3]);
        }
        if(xfoa[0]!=NULL){
            out = Base16_decode(xfoa[0],strlen(xfoa[0])*sizeof(char),xfoa[3]);
        }
        if(xfoa[2]!=NULL){
            write_file(xfoa[2],out->data,sizeof(*out->data));
        }else{
            print_str(out->data);
        }
    }
}


