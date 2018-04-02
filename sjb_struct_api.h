/*
* simple josn binding
* email: 25088970@qq.com
*/

#ifndef __sjb_struct_api_h__
#define __sjb_struct_api_h__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON/cJSON.h"

#define STRUCT(TYPE) typedef struct _##TYPE TYPE;\
                     extern void sjb_bind_##TYPE(cJSON* json  /* sjb_bind_TYPE */ \
                                    , int m                   /* 0: to josn, 1: from josn */ \
                                    , TYPE *str               /* C struct */ \
                                    , int i                   /* 0 */ \
                                    , int size);              /* 0 */ \
                     struct _##TYPE
                     
#define STRING(X,Y)   char X[Y]
#define FIELD(X,Y)    X Y
#define ARRAY(X,Y,Z)  int __##Y; X Y[Z]
#define BINARY(X,Y)   int __##X; char X[Y]
#define ARRAYSTR(X,Y,Z) int __##X; char X[Y][Z]

#include "sjb_struct_def.h"

#undef STRUCT
#undef STRING
#undef FIELD
#undef ARRAY
#undef BINARY
#undef ARRAYSTR

#endif //__sjb_struct_api_h__