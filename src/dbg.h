#ifndef __dbg_h__
#define __dbg_h__
#endif
#ifndef __color_h
#include "colors.h"
#endif

#include <stdio.h>
#include <errno.h> 
#include <string.h>

#ifdef NDEBUG
#define debug(M, ...)
#else 
#define debug(M, ...) fprintf(stderr, "%s (%s:%d:%s) " M "\n",KINF, __FILE__, __LINE__, __func__, ##__VA_ARGS__) 
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))
 
#define log_err(M, ...) fprintf(stderr,"%s (%s:%d:%s: errno: %s) " M "\n", KWAR, __FILE__, __LINE__, __func__, clean_errno(), ##__VA_ARGS__) 
 
#define log_warn(M, ...) fprintf(stderr, "%s (%s:%d:%s: errno: %s) " M "\n",KWAR, __FILE__, __LINE__, __func__, clean_errno(), ##__VA_ARGS__) 
 
#define log_info(M, ...) fprintf(stdout, "%s (%s:%d:%s) " M "\n",KINF, __FILE__, __LINE__, __func__, ##__VA_ARGS__) 

#define log_sucess(M, ...) fprintf(stdout, "%s (%s:%d:%s) " M "\n",KNOK, __FILE__, __LINE__, __func__, ##__VA_ARGS__) 

#define test_error(M, ...) fprintf(stderr, "%s (%s:%d:%s) " M "\n",KWAR, __FILE__, __LINE__, __func__, ##__VA_ARGS__) 

#define test_info(M, ...) fprintf(stderr, "%s (%s:%d:%s) " M "\n",KINF, __FILE__, __LINE__, __func__, ##__VA_ARGS__) 

#define test_sucess(M, ...) fprintf(stderr, "%s (%s:%d:%s) " M "\n",KNOK, __FILE__, __LINE__, __func__, ##__VA_ARGS__) 



#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; } 

#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno=0; goto error; } 

#define check_mem(A) check((A), "Out of memory.")
 
#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; } 
