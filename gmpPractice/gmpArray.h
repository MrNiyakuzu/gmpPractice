#pragma once
#include <gmp_util.h>
#include <omp.h>
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
	void sum(gmpArray& gmpAr1, gmpArray& gmpAr2);
	void mul(gmpArray& gmpAr1, gmpArray& gmpAr2);
	void sumOMP(gmpArray& gmpAr1, gmpArray& gmpAr2);
	void mulOMP(gmpArray& gmpAr1, gmpArray& gmpAr2);
};