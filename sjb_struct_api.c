#include "sjb_struct_api.h"

// 类型绑定;
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

void sjb_bind_string(cJSON* json, int m, char *str, int i, int size) 
{
  if(m)
  {
		if( json && json->type == cJSON_String)
			strncpy(str, json->valuestring, size);
  }
  else
  {
    json->type = cJSON_String;
    cJSON_SetStrValue(json, str);
  }
}
void sjb_bind_binary(cJSON* json, int m, int *str, int i, int size) 
{
  int ii = 0;
  int *n = str++;
  if(m)
  {
		if( json && json->type == cJSON_String)
		{
		  *n = strlen(json->valuestring)/2;
		  *n = (*n > size)?size:*n;
		  for(ii = 0; ii < *n*2; ii+=2)
		  {
		      char t[4];
		      t[0] = json->valuestring[ii];
		      t[1] = json->valuestring[ii+1];
		      t[2] = '\0';
		      *((char*)str+ii/2) = strtol(t, 0, 16);
		  }
		}
  }
  else
  {
    json->type = cJSON_String;
    if(*n > 0)
    {
      char *e = (char*)malloc(*n*2);
      for(ii = 0; ii < *n; ii++)
      {
        char t[4]; sprintf(t, "%02X", *((char*)str+ii));
        strcat(e, t);
      }
      cJSON_SetStrValue(json, e);
      free(e);
    }
    else
      cJSON_SetStrValue(json, "");
  }
}

// 数组绑定;
void sjb_array_bind(cJSON* json, int m, int *str, char *tag, int size, sjb_bind_T *cb)
{
  int i = 0;
  int *n = str++;
  if ( m ) //from json
  	{
  		cJSON* arr = cJSON_GetObjectItem(json,tag);
  		if( arr != NULL && arr->type == cJSON_Array)
  		{
  		  *n = cJSON_GetArraySize(arr);
  		  *n = (*n > size)?size:*n;
    		for ( i=0; i<*n; i++)
    		{
    			cJSON* child=cJSON_GetArrayItem(arr,i);
    			cb(child, m, str, i, size);
    		}
  	  }
  	}
  	else //to json
  	{
  		cJSON* arr = cJSON_CreateArray();
  		cJSON_AddItemToObject(json, tag, arr);
  		for ( i=0; i<*n; i++)
  		{
  			cJSON* jani = cJSON_CreateObject();
  			cb(jani, m, str, i, size);
  			cJSON_AddItemToArray(arr, jani);
  		}
  	}
}

// 代码生成;
#define STRING(HOLDER,SIZE)      do { \
  if(m) { cJSON* jani = cJSON_GetObjectItem(json, #HOLDER); sjb_bind_string( jani, m, (str+i)-> HOLDER, 0, SIZE);}\
  else {cJSON* jani = cJSON_CreateObject(); sjb_bind_string( jani, m, (str+i)-> HOLDER, 0, SIZE); cJSON_AddItemToObject(json, #HOLDER, jani);}\
}while(0)

#define FIELD(TYPE, HOLDER)      do { \
  if (m) { cJSON* jani = cJSON_GetObjectItem(json, #HOLDER); sjb_bind_##TYPE( jani, m, &(str+i)-> HOLDER, 0, 1);}\
  else {cJSON* jani = cJSON_CreateObject(); sjb_bind_##TYPE( jani, m, &(str+i)-> HOLDER, 0, 1); cJSON_AddItemToObject(json, #HOLDER, jani);}\
}while(0)
#define BINARY(HOLDER,SIZE)      do { \
  if (m) { cJSON* jani = cJSON_GetObjectItem(json, #HOLDER); sjb_bind_binary( jani, m, (int*)&(str+i)-> __##HOLDER, 0, SIZE);}\
  else {cJSON* jani = cJSON_CreateObject(); sjb_bind_binary( jani, m, (int*)&(str+i)-> __##HOLDER, 0, SIZE); cJSON_AddItemToObject(json, #HOLDER, jani);}\
}while(0)

#define ARRAY(TYPE,HOLDER,SIZE) sjb_array_bind(  json, m, (int*)&(str+i)-> __##HOLDER, #HOLDER, SIZE, (sjb_bind_T*)sjb_bind_##TYPE)


#include "sjb_struct_def.h"

#undef STRUCT
#undef STRING
#undef FIELD
#undef ARRAY
#undef BINARY
