/*
* simple json binding
* email: 25088970@qq.com
*/

#ifndef __sjb_struct_api_h__
#define __sjb_struct_api_h__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON/cJSON.h"

#if 0
#define DEBUG // for printf;
#define __ELE // for int __ele;
#endif

#define STRUCT(TYPE) typedef struct _##TYPE TYPE;\
                     extern void sjb_bind_##TYPE(cJSON* json  /* sjb_bind_TYPE */ \
                                    , int m                   /* 0: to josn, 1: from josn */ \
                                    , TYPE *str               /* C struct */ \
                                    , int i                   /* 0 */ \
                                    , int size);              /* 0 */ \
                     struct _##TYPE
                 
#define string        char
#define uint64        unsigned long long
#define STRING(X,Y)   char X[Y]
#define FIELD(X,Y)    X Y

#ifdef __ELE
#define __ELE_DEF(e) int __##e;
#else
#define __ELE_DEF(e)
#endif

#define ARRAY(X,Y,Z)      __ELE_DEF(Y) X Y[Z]
#define ARRAY2(X,Y,Z,D)   __ELE_DEF(Y) X Y[Z][D]
#define ARRAY3(X,Y,Z,D,F) __ELE_DEF(Y) X Y[Z][D][F]
#define BINARY(X,Y)       __ELE_DEF(X) char X[Y]

#include "sjb_struct_def.h"

#undef STRUCT
#undef STRING
#undef FIELD
#undef ARRAY
#undef BINARY
#undef ARRAY2
#undef ARRAY3
#undef string
#undef uint64

#endif //__sjb_struct_api_h__