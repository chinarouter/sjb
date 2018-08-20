STRUCT(cream)
{
  STRING(name, 8);
  FIELD(int , sweetness);
  FIELD(uint64 , sweetness64);
  ARRAY(uint64 , array64, 3);
  BINARY(picture, 32);
  ARRAY2(string, creamstrarray, 4, 32);
  ARRAY2(int, int2, 4, 3);
  ARRAY3(int, int3, 4, 2, 8);
  ARRAY3(string, string3, 4, 2, 64);
  
  UNION_B(sweetType);
  UNION_C(0, uint64, u64_sweet);
  UNION_S(1, str_sweet, 32);
  UNION_E();
  
};

STRUCT(fruit)
{
	STRING(name, 8);
  FIELD(int , color);
  ARRAY(double, local, 2);
  ARRAY(cream, creams, 4);
  ARRAY2(string, fruitstrarray, 4, 32);
  FIELD(cream, cream);
};


STRUCT(cake)
{
	STRING(name, 8);
	ARRAY(fruit, fruits, 4);
	FIELD(cream, c);
};

