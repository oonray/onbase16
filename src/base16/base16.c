#include <onbase16/16.h>
#include <onbase16/dbg.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <argp.h>

typedef struct filedata {
    char *data;
    int lengt;
} filedata;

struct flags {
    bool e;
    bool d;
    char *f;
    char *x;
    char *o;
    char *a;
} flags = {false,false,NULL,NULL,NULL,NULL};

static struct argp_option options[] = {
  {"Encode",        'e', 0,         0,  "Encode input" },
  {"Decode",        'd', 0,         0,  "Decode input" },
  {"InputFile",     'f', "FILE",    0,  "Take input from file" },
  {"Data",          'x', "DATA",    0,  "Take input from stdin" },
  {"output",        'o', "FILE",    0,  "Output to FILE instead of standard output" },
  { 0 }
};

const char *argp_program_bug_address =
  "<oonra@localhost>";

static char doc[] =
  "base16 -- Encode data/file using base16";

static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  switch (key)
    {
    case 'e':
      flags.e = true;
      break;
    case 'd':
      flags.d = true;
      break;
    case 'x':
      flags.x = arg;
      break;
    case 'f':
      flags.f = arg;
      break;
    case 'o':
      flags.o = arg;
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}


filedata *read_file(char *filename){   
    log_info("Reading file %s",filename);
    FILE *f = fopen(filename,"r");
    check(f!=NULL,"Could not open file.");
    int filelen = 0;

    fseek(f, 0, SEEK_END);          
    filelen = ftell(f);             
    rewind(f);                      
    
    filedata *buffer = calloc(1,sizeof(filedata)); 
    buffer->lengt = filelen;
    buffer->data = calloc(1,sizeof(filelen));
    fread(buffer->data, filelen, 1, f); 
    log_info("%s",buffer->data);
    fclose(f); 
    return buffer;
error:
    return 0;
}

int write_file(char *filename,void *data,size_t size){
   FILE *f = fopen(filename,"w"); 
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

static struct argp argp = { options, parse_opt, 0, doc };

int main(int argc,char *argv[]){
  int c = 0;
  bool error = false;
  
  argp_parse(&argp,argc,argv,0,0,&flags);

  if(flags.e && flags.d){
        argp_error(0,"You must choose eigther encode or decode!");
        error = true;
    } 
  if(!flags.e && !flags.d){
        argp_error(0,"Must eigter decode or encode");
        error = true;

    }
    if(flags.x != NULL && flags.f != NULL){
        argp_error(0,"Cannot read from file and suply data!");
        error = true;
    }
    if(flags.x == NULL && flags.f == NULL){
        argp_error(0,"Must suply eigther file or data");
        error = true;
    }
    if(error){
        exit(1);
    }


    Base16 *out = NULL;

    if(flags.e){
        log_info("encoding.");
        if(flags.f!=NULL){
            filedata *data = read_file(flags.f);
            log_info("%s",data->data);
            out = Base16_encode(data->data,data->lengt,flags.a);
        }
        if(flags.x!=NULL){
            out = Base16_encode(flags.x,strlen(flags.x)*sizeof(char),flags.a);
        }
        if(flags.o!=NULL){
            write_file(flags.o,out->encoded,strlen(out->encoded)*sizeof(char)); 
        }else{
            print_str(out->encoded);
        }
    }

    if(flags.d){
        log_info("decoding.");
        if(flags.f!=NULL){
            filedata *data = read_file(flags.f);
            out = Base16_decode(data->data,strlen(data->data)*sizeof(char),flags.a);
        }
        if(flags.x!=NULL){
            out = Base16_decode(flags.x,strlen(flags.x)*sizeof(char),flags.a);
        }
        if(flags.o!=NULL){
            write_file(flags.o,out->data,sizeof(*out->data));
        }else{
            print_str(out->data);
        }
    }
}


