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


#define STRUCT(TYPE) typedef struct _##TYPE TYPE;\
                     extern void sjb_bind_##TYPE(cJSON* json  /* sjb_bind_TYPE */ \
                                    , int m                   /* 0: to josn, 1: from josn */ \
                                    , TYPE *str               /* C struct */ \
                                    , int i                   /* 0 */ \
                                    , int size);              /* 0 */ \
                     struct _##TYPE
                 
#define string        char
#define uint64        unsigned long long
#define uint32        unsigned int
#define uint16        unsigned short
#define uint8         unsigned char

#define STRING(X,Y)   char X[Y]
#define FIELD(X,Y)    X Y
#if 0 // not define K;
#define UNION_B(K) int K; union { char __      /* UNION_B(union_type); */
#else
#define UNION_B(K)    union { char __          /* UNION_B(union_type); */
#endif
#define UNION_C(cond, type, val) type val      /* UNION_C(union_type_xxx, type, val); */
#define UNION_S(cond, val, size) char val[size]/* UNION_S(union_type_xxx, val, size); */ 
#define UNION_E() }                            /* UNION_E(); */


#ifdef __ELE__
#define __ELE_DEF(e)  int e##__;
#define ELE_VAL(e)    e##__
#define ELE_SIZE(e)   e##__
#else
#define __ELE_DEF(e)
static  int __ele__;  //dummy;
#define ELE_VAL(e)    __ele__
#define ELE_SIZE(e)   (sizeof(e)/sizeof(e[0]))
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
#undef uint32
#undef uint16
#undef uint8
#undef UNION_B
#undef UNION_C
#undef UNION_S
#undef UNION_E


#endif //__sjb_struct_api_h__