#pragma once
#include <gmp_util.h>
class gmpArray
{
private:
	int n;
	mpz_t* values;
public:
	gmpArray(int count = 0);
	~gmpArray();
};

