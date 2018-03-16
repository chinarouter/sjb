STRUCT(cream)
{
  STRING(name, 8);
  FIELD(int , sweetness);
  BINARY(picture, 1024);
};

STRUCT(fruit)
{
	STRING(name, 8);
  FIELD(int , color);
  ARRAY(double, local, 2);
  ARRAY(cream, creams, 4);
  FIELD(cream, cream);
};


STRUCT(cake)
{
	STRING(name, 8);
	ARRAY(fruit, fruits, 4);
	FIELD(cream, c);
};

