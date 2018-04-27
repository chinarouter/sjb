#include "sjb_struct_api.h"

cJSON* _cJSON_FromFile(const char* filename)
{
	FILE *f=fopen(filename,"rb");fseek(f,0,SEEK_END);long len=ftell(f);fseek(f,0,SEEK_SET);
	char *data=(char*)malloc(len+1);fread(data,1,len,f);fclose(f);
	cJSON* json = cJSON_Parse(data);
	free(data);
	if (!json)
	{
		printf("Error before: [%s]\n",cJSON_GetErrorPtr());
		return 0;
	}
	return json;
}
cJSON* _cJSON_CreateNode(cJSON* json, const char* name)
{
	cJSON* node = cJSON_CreateObject();
	cJSON_AddItemToObject( json, name, node);
	return node;
}

void _cJSON_Print(cJSON* json, FILE* out)
{
	char* print = cJSON_Print(json);
	if(print)
	{
	  fprintf( out, "%s", print);
	  free(print);
	}
}


#ifdef __ELE
#define ELE(e)  e
#else
static int __dummy;
#define ELE(e) __dummy
#endif


int main(int argc, char *argv[])
{
  #if 1
  fruit f;

  memset(&f, 0, sizeof(f));

  snprintf(f.name, sizeof(f.name), "%s", "fruit");
  f.color = 0xffffffff;
  ELE(f.__local) = 2;

  f.local[0] = 1.11;
  f.local[1] = 2.22;
  
  ELE(f.__fruitstrarray) = 2;
  snprintf(f.fruitstrarray[0], sizeof(f.fruitstrarray[0]), "%s", "fruitstr1111");
  snprintf(f.fruitstrarray[1], sizeof(f.fruitstrarray[1]), "%s", "fruitstr2222");
  
  ELE(f.__creams) = 2;
  snprintf(f.creams[0].name, sizeof(f.creams[0].name), "%s", "cream1");
  snprintf(f.creams[1].name, sizeof(f.creams[1].name), "%s", "cream2");
  
  
  f.creams[0].sweetness = 0xfffffff1;
  f.creams[0].sweetness64 = 0xfffffffffffffff2;
  
  ELE(f.creams[0].__array64) = 2;
  f.creams[0].array64[0] = 0xfffffffffffffff1;
  f.creams[0].array64[1] = 0xfffffffffffffff2;
  
  
  ELE(f.creams[0].__picture) = 5;
  memset(f.creams[0].picture, 0x51, sizeof(f.creams[0].picture));

  ELE(f.creams[0].__creamstrarray) = 3;
  snprintf(f.creams[0].creamstrarray[0], sizeof(f.creams[0].creamstrarray[0]), "%s", "creamstrarray111");
  snprintf(f.creams[0].creamstrarray[1], sizeof(f.creams[0].creamstrarray[1]), "%s", "creamstrarray222");

  ELE(f.creams[0].__int2) = 3;
  f.creams[0].int2[0][0] = 61; f.creams[0].int2[0][1] = 62;
  f.creams[0].int2[1][0] = 71; f.creams[0].int2[1][1] = 72;
  f.creams[0].int2[2][0] = 81; f.creams[0].int2[2][1] = 82;

  ELE(f.creams[0].__int3) = 3;
  f.creams[0].int3[0][0][0] = 61; f.creams[0].int3[0][0][1] = 62;
  f.creams[0].int3[1][0][0] = 71; f.creams[0].int3[1][0][1] = 72;
  f.creams[0].int3[2][0][0] = 81; f.creams[0].int3[2][0][1] = 82;


  ELE(f.creams[1].__string3) = 2;
  strcpy(f.creams[1].string3[0][1], "f.creams_1.string3_0_1");
  

  snprintf(f.cream.name, sizeof(f.cream.name), "%s", "cream11111111");
  ELE(f.cream.__picture) = 3;
  memset(f.cream.picture, 0x11, sizeof(f.cream.picture));
  
  ELE(f.cream.__string3) = 2;
  strcpy(f.cream.string3[0][0], "f.creams_1.string3_0_0");
  strcpy(f.cream.string3[0][1], "f.creams_1.string3_0_1");
  strcpy(f.cream.string3[1][0], "f.creams_1.string3_1_0");
  strcpy(f.cream.string3[1][1], "f.creams_1.string3_1_1");
  
  
  printf("\n>>>>> create json >>>>>>\n");
  cJSON* out = cJSON_CreateObject();

  sjb_bind_fruit(out, 0, &f, 0, 0);
  
  _cJSON_Print( out, stdout);

	cJSON_Delete(out);
  #endif
  
  int a = 0;
  ELE(a) = 1;
  
  
  printf("\n>>>> parse tt.json >>>>>>>\n");
  
  int i, j, k;
  fruit fr;
  memset(&fr, 0, sizeof(fr));
  cJSON* json=_cJSON_FromFile("tt.json");
  _cJSON_Print( json, stdout);
 
  sjb_bind_fruit(json, 1, &fr, 0, 0);
 
	cJSON_Delete(json);
  
  printf("fr.name:[%s]\n", 	fr.name);
  printf("fr.color:[%d]\n", 	fr.color);
  printf("fr.local:%d, [%f,%f]\n", 	ELE(fr.__local), fr.local[0], fr.local[1]);
  
  printf("fr.__creams:[%d]\n", 	ELE(fr.__creams));
  for(i = 0; i < ELE(fr.__creams); i++)
  {
    printf("fr.creams[%d].name:[%s]\n", i, fr.creams[i].name);
    printf("fr.creams[%d].sweetness:[%x]\n", i, fr.creams[i].sweetness);
    printf("fr.creams[%d].sweetness64:[%llx]\n", i, fr.creams[i].sweetness64);
    
    printf("fr.creams[%d].__array64[%d]\n", i, ELE(fr.creams[i].__array64));
    
    for(j = 0; j < ELE(fr.creams[i].__array64); j++)
    {
      printf("fr.creams[%d].array64[%d]:[%llx]\n", i, j, fr.creams[i].array64[j]);
    }
    
    printf("fr.creams[%d].__picture[%d]\n", i, ELE(fr.creams[i].__picture));
    char spic[1024] = {0};
    for(j = 0; j < ELE(fr.creams[i].__picture); j++)
    {
      char t[4];sprintf(t, "%02X", fr.creams[i].picture[j]);
      strcat(spic, t);
    }
    printf("fr.creams[%d].picture[%s]\n", i, spic);
    
    printf("fr.creams[%d].__creamstrarray[%d]\n", i, ELE(fr.creams[i].__creamstrarray));
    printf("fr.creams[%d].creamstrarray[%s]\n", i, fr.creams[i].creamstrarray[i]);
    
    printf("fr.creams[%d].__int2[%d]\n", i, ELE(fr.creams[i].__int2));
    printf("fr.creams[%d].int2[ [%d, %d], [%d, %d]]\n", i
        , fr.creams[i].int2[0][0], fr.creams[i].int2[0][1]
        , fr.creams[i].int2[1][0], fr.creams[i].int2[1][1]);
    
    
  }
  
  printf("fr.cream.name:[%s]\n", 	fr.cream.name);
  printf("fr.cream.__picture:[%d]\n", 	ELE(fr.cream.__picture));
  char spic[1024] = {0};
  for(j = 0; j < ELE(fr.cream.__picture); j++)
  {
    char t[4];sprintf(t, "%02X", fr.cream.picture[j]);
    strcat(spic, t);
  }
  printf("fr.cream.picture[%s]\n", spic);
  
  printf("fr.cream.__string3[%d]\n", ELE(fr.cream.__string3));
  printf("fr.cream.string3[ [%s, %s], [%s, %s]]\n"
      , fr.cream.string3[0][0], fr.cream.string3[0][1]
      , fr.cream.string3[1][0], fr.cream.string3[1][1]);
  
  
  printf("fr.cream.__int3[%d]\n", ELE(fr.cream.__int3));
  printf("fr.cream.int3[ \n"
                        "[ [%d, %d] ] \n"
                        "[ [%d, %d] ] \n"
                        "[ [%d, %d] ] \n"
                      "]\n"
      , fr.cream.int3[0][0][0], fr.cream.int3[0][0][1]
      , fr.cream.int3[1][0][0], fr.cream.int3[1][0][1]
      , fr.cream.int3[2][0][0], fr.cream.int3[2][0][1]
      );
  printf("test OK.\n");
  return 0;
}