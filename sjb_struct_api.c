#include "sjb_struct_api.h"

#ifndef DEBUG
#define printf(...)
#endif

// ���Ͱ�;
#define STRUCT(TYPE) void sjb_bind_##TYPE(cJSON* json, int m, TYPE *str, int i, int size)

typedef void (sjb_bind_T)(cJSON* json, int m, void *str, int i, int size);

void sjb_bind_int(cJSON* json, int m, int *str, int i, int size) 
{
  if(m)
  {
    if( json && json->type == cJSON_Number)
    			*(str+i) = json->valueint;
  }
  else
  {
    json->type=cJSON_Number;
    cJSON_SetIntValue(json, *(str+i));
  }
}

void sjb_bind_short(cJSON* json, int m, short *str, int i, int size) 
{
  if(m)
  {
    if( json && json->type == cJSON_Number)
    			*(str+i) = json->valueint;
  }
  else
  {
    json->type=cJSON_Number;
    cJSON_SetIntValue(json, *(str+i));
  }
}

void sjb_bind_char(cJSON* json, int m, char *str, int i, int size) 
{
  if(m)
  {
    if( json && json->type == cJSON_Number)
    			*(str+i) = json->valueint;
  }
  else
  {
    json->type=cJSON_Number;
    cJSON_SetIntValue(json, *(str+i));
  }
}

void sjb_bind_float(cJSON* json, int m, float *str, int i, int size) 
{
  if(m)
  {
    if( json && json->type == cJSON_Number)
    			*(str+i) = json->valuedouble;
  }
  else
  {
    json->type=cJSON_Number;
    cJSON_SetIntValue(json, *(str+i));
  }
}


void sjb_bind_double(cJSON* json, int m, double *str, int i, int size) 
{
  if(m)
  {
    if( json && json->type == cJSON_Number)
    			*(str+i) = json->valuedouble;
  }
  else
  {
    json->type=cJSON_Number;
    cJSON_SetIntValue(json, *(str+i));
  }
}

typedef unsigned long long uint64;

void sjb_bind_uint64(cJSON* json, int m, uint64 *str, int i, int size) 
{  
  if(m)
  {
		if( json && json->type == cJSON_String)
    {
		  *(str+i) = strtoull(json->valuestring, NULL, 16);
      printf("json >>>>>> struct: valuestring[%s], uint64[%llx]\n", json->valuestring, *(str+i));
    }
  }
  else
  {
    json->type = cJSON_String;
    char t[64];
    sprintf(t, "%llx", *(str+i));
    cJSON_SetStrValue(json, t);
    printf("struct >>>>>> json: t[%s], uint64[%llx]\n", t, *(str+i));
  }
}


void sjb_bind_string(cJSON* json, int m, char *str, int i, int size) 
{
  if(m)
  {
		if( json && json->type == cJSON_String)
			strncpy((char*)str + i*size, json->valuestring, size);
  }
  else
  {
    json->type = cJSON_String;
    cJSON_SetStrValue(json, (char*)str + i*size);
  }
}



void sjb_bind_binary(cJSON* json, int m, char *str, int i, int size) 
{
  int j = 0;
  if(m) // from json;
  {
		if( json && json->type == cJSON_String)
		{
		  for(j = 0; j < size*2; j+=2)
		  {
		      char t[4];
		      t[0] = json->valuestring[j];
		      t[1] = json->valuestring[j+1];
		      t[2] = '\0';
		      *((char*)str+j/2) = strtol(t, 0, 16);
		  }
		}
  }
  else  // to json;
  {
    json->type = cJSON_String;
    if(size > 0)
    {
      char *e = (char*)malloc(size*2 + 1);
      e[0] = '\0';
      for(j = 0; j < size; j++)
      {
        char t[4]; sprintf(t, "%02X", *((char*)str+j));
        strcat(e, t);
      }
      cJSON_SetStrValue(json, e);
      free(e);
    }
    else
      cJSON_SetStrValue(json, "");
  }
}


#define ARR_STRING(sub)  sub[0]        // string flag;
#define ARR_CURR(sub)    sub[1]        // curr array level;
#define ARR_SUBN(sub)    sub[2]        // total array level number;
#define ARR_SUBS(sub)    sub[3+sub[1]] // curr level elem number;
#define ARR_DUP(dst,sub) int dst[64]; memcpy(dst, sub, 64)
#define ARR_SKIP(sub, tsize)  ({int i = 0; int ret = tsize; /* bytes [from curr level to end level] */\
                                for(i = ARR_CURR(sub); i < (ARR_STRING(sub)?ARR_SUBN(sub)-1:ARR_SUBN(sub)); i++) \
                                  ret *= sub[3+i]; \
                                ret=ret;\
                              })

// �����;
void sjb_bind_array(cJSON* json, int m, char *str, int size, int* sub, sjb_bind_T *cb, int tsize)
{
  int j = 0;
 
  ARR_CURR(sub) += 1;
  printf("s:%d, curr:%d, num:%d, [%d, %d, %d, %d], size:%d\n"
    , ARR_STRING(sub), ARR_CURR(sub), ARR_SUBN(sub), sub[3+0], sub[3+1], sub[3+2], sub[3+3]
    , size);
    
  if ( m ) //from json
  	{
  		if( json != NULL && json->type == cJSON_Array)
  		{
    		for ( j=0; j<size; j++)
    		{
    			cJSON* child=cJSON_GetArrayItem(json,j);
    			
    			if( ARR_STRING(sub) && ARR_CURR(sub) + 1 == ARR_SUBN(sub))
    			{
    			  printf("<<<<<< string j:%d, tsize:%d\n", j, tsize);
    			  cb(child, m, str, j, tsize);
    			}
    			else if (ARR_CURR(sub) == ARR_SUBN(sub))
    		  {
    		    printf("<<<<<< !!!!!! j:%d, tsize:%d\n", j, tsize);
    		    cb(child, m, str, j, tsize);
    		  }
    			else
    		  {
    		    ARR_DUP(_sub, sub);
            printf("<<<<<< [ ] j:%d, size:%d, skip:%d, tsize:%d\n", j, size, j*ARR_SKIP(sub,tsize), tsize);
    		    sjb_bind_array(child, m, str+j*ARR_SKIP(sub,tsize), ARR_SUBS(sub), _sub, cb, tsize);
    		  }
    		}
  	  }
  	}
  	else //to json
  	{
  		for ( j=0; j<size; j++)
  		{
  		  cJSON* jani = cJSON_CreateObject();
  		  
  		  if( ARR_STRING(sub) && ARR_CURR(sub) + 1 == ARR_SUBN(sub))
  		  {
  		    printf(">>>>>> string j:%d, tsize:%d\n", j, tsize);
    			cb(jani, m, str, j, tsize);
  		  }
  		  else if(ARR_CURR(sub) == ARR_SUBN(sub))
  		  {
  		    printf(">>>>>> !!!!!! j:%d, tsize:%d\n", j, tsize);
    			cb(jani, m, str, j, tsize);
  		  }
  		  else
  		  {
    			jani->type = cJSON_Array;
    			ARR_DUP(_sub, sub);
    			printf(">>>>>> [ ] j:%d, size:%d, skip:%d, tsize:%d\n", j, size, j*ARR_SKIP(sub,tsize), tsize);
    			sjb_bind_array(jani, m, str+j*ARR_SKIP(sub,tsize), ARR_SUBS(sub), _sub, cb, tsize);
  		  }
  		  cJSON_AddItemToArray(json, jani);
  		}
  	}
}

// ��������;
#define STRING(HOLDER,SIZE)      do { \
  if(m) { if(!json) break; cJSON* jani = cJSON_GetObjectItem(json, #HOLDER); sjb_bind_string( jani, m, (str+i)-> HOLDER, 0, SIZE);}\
  else {cJSON* jani = cJSON_CreateObject(); sjb_bind_string( jani, m, (str+i)-> HOLDER, 0, SIZE); cJSON_AddItemToObject(json, #HOLDER, jani);}\
}while(0)

#define FIELD(TYPE, HOLDER)      do { \
  if (m) { if(!json) break; cJSON* jani = cJSON_GetObjectItem(json, #HOLDER); sjb_bind_##TYPE( jani, m, &(str+i)-> HOLDER, 0, 1);}\
  else {cJSON* jani = cJSON_CreateObject(); sjb_bind_##TYPE( jani, m, &(str+i)-> HOLDER, 0, 1); cJSON_AddItemToObject(json, #HOLDER, jani);}\
}while(0)


#ifdef __ELE__
#define __ELE_SIZE(HOLDER,SIZE)  int *n = (int*)&(str+i)-> HOLDER##__
#else
#define __ELE_SIZE(HOLDER,SIZE)  int _n = SIZE; int *n = &_n;
#endif

#define BINARY(HOLDER,SIZE)      do { \
  __ELE_SIZE(HOLDER,SIZE); \
  if (m) { if(!json) break;  cJSON* jani = cJSON_GetObjectItem(json, #HOLDER); if(!jani) break;\
      *n = strlen(jani->valuestring)/2; *n = (*n > SIZE)?SIZE:*n;\
      sjb_bind_binary( jani, m, (char*)((str+i)-> HOLDER), 0, *n);}\
  else {cJSON* jani = cJSON_CreateObject(); \
      sjb_bind_binary( jani, m, (char*)((str+i)-> HOLDER), 0, *n); \
      cJSON_AddItemToObject(json, #HOLDER, jani);}\
}while(0)

#define __ARRAY(TYPE,HOLDER,SIZE,SUB,TSIZE) do { \
  __ELE_SIZE(HOLDER,SIZE); \
  if(m) { if(!json) break; cJSON* jani = cJSON_GetObjectItem(json, #HOLDER); if(!jani) break;\
      *n = cJSON_GetArraySize(jani); *n = (*n > SIZE)?SIZE:*n;\
      printf("<<<<<< @@@ %s [%d] @@@\n", #HOLDER, *n);\
      sjb_bind_array(jani, m, (char*)((str+i)-> HOLDER), *n, SUB, (sjb_bind_T*)sjb_bind_##TYPE, TSIZE);}\
  else {cJSON* jani = cJSON_CreateArray(); \
  		printf(">>>>>> @@@ %s [%d] @@@\n", #HOLDER, *n);\
  		cJSON_AddItemToObject(json, #HOLDER, jani);\
      sjb_bind_array( jani, m, (char*)((str+i)-> HOLDER), *n, SUB, (sjb_bind_T*)sjb_bind_##TYPE, TSIZE);}\
}while(0)

typedef char string;

#define ARRAY(TYPE,HOLDER,SIZE) do { \
    int sub[64] = {0, 0, 1, SIZE}; \
    sub[0] = strstr( #TYPE, "string")?1:0;    \
    __ARRAY(TYPE,HOLDER,SIZE,sub, sizeof(TYPE)); \
}while(0)

#define ARRAY2(TYPE,HOLDER,SIZE,TSIZE) do { \
    int sub[64] = {0, 0, 2, SIZE, TSIZE}; \
    sub[0] = strstr( #TYPE, "string")?1:0;    \
    __ARRAY(TYPE,HOLDER,SIZE,sub,sub[0]?TSIZE:sizeof(TYPE)); \
}while(0)

#define ARRAY3(TYPE,HOLDER,SIZE, SIZE2, TSIZE) do { \
    int sub[64] = {0, 0, 3, SIZE, SIZE2, TSIZE}; \
    sub[0] = strstr( #TYPE, "string")?1:0;    \
    __ARRAY(TYPE,HOLDER,SIZE,sub,sub[0]?TSIZE:sizeof(TYPE)); \
}while(0)

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
