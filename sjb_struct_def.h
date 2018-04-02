STRUCT(cream)
{
  STRING(name, 8);
  FIELD(int , sweetness);
  BINARY(picture, 1024);
  ARRAYSTR(creamstrarray, 4, 32);
};

STRUCT(fruit)
{
	STRING(name, 8);
  FIELD(int , color);
  ARRAY(double, local, 2);
  ARRAY(cream, creams, 4);
  ARRAYSTR(fruitstrarray, 4, 32);
  FIELD(cream, cream);
};


STRUCT(cake)
{
	STRING(name, 8);
	ARRAY(fruit, fruits, 4);
	FIELD(cream, c);
};

