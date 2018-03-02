# sjb - simple JSON binding and serialization scheme for C

### how to do it in sjb?

```C

sjb_struct_def.h - custom defined struct


STRUCT(cream)               /* defined struct and sjb_bind_cream function */
{
  STRING(name, 8);          /* - char name[8] */
  FIELD(int , sweetness);   /* - int sweetness */
  BINARY(picture, 1024);    /* - char picture[1024]  and int __picture */
};


STRUCT(fruit)                 /* defined struct and sjb_bind_fruit function */
{
	STRING(name, 8);            /*  - char name[8]  */
  FIELD(int , color);         /*  - int color     */
  ARRAY(int, local, 2);       /*  - int local[2]  and int __local */
  ARRAY(cream, creams, 4);    /*  - cream creams[4]  and int __creams */
  FIELD(cream, cream);        /*  - cream cream */
};


sjb_struct_api.h - auto extern api;


extern void sjb_bind_cream(cJSON* json  /* json tree */
                          , int m       /* 0: to json, 1: from json*/
                          , cream *str  /* C struct ptr */
                          , int i       /* 0 */
                          , int size    /* 0 */
                          );

extern void sjb_bind_fruit(cJSON* json  /* json tree */
                          , int m       /* 0: to json, 1: from json*/
                          , fruit *str  /* C struct ptr */
                          , int i       /* 0 */
                          , int size    /* 0 */
                          );
              
test.c - sample code use sjb_struct_api.h;

sjb_bind_cream(json, 1, &c, 0, 0);

```

```json
{
	"name":	"fruit",
	"color":	1111,
	"local":	[1, 2],
	"creams":	[{
			"name":	"cream1",
			"sweetness":	0,
			"picture":	"5152535455"
		}, {
			"name":	"cream2",
			"sweetness":	0,
			"picture":	""
		}],
	"cream":	{
		"name":	"cream11",
		"sweetness":	0,
		"picture":	"1112131415"
	}
}
```