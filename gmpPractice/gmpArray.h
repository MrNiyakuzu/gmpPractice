#pragma once
#include <gmp_util.h>
#include <omp.h>
class gmpArray
{
private:
	int n;//number of elements
	mpz_t* values;//values of elements
public:
	gmpArray(int count = 0);//constructor
	~gmpArray();//destructor

	mpz_t& operator[] (int number);
	void print();//print gmpArray to the console
	void clearValues();//clear all elements
	void resize(int number); //change size of values
	void sum(gmpArray& gmpAr1, gmpArray& gmpAr2);//summarize without OMP
	void mul(gmpArray& gmpAr1, gmpArray& gmpAr2);//multiply without OMP
	void sumOMP(gmpArray& gmpAr1, gmpArray& gmpAr2);//summarize with OMP
	void mulOMP(gmpArray& gmpAr1, gmpArray& gmpAr2);//multiply with OMP
	void setRandom(int k);//set elements to a random number in range from 2^(k-1) to 2^k-1
};