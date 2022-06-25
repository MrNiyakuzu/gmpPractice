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

	mpz_t& operator[] (int number);
	void print();
	void resize(int number);
};

