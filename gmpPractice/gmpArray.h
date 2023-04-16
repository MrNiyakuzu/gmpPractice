//#pragma once
//#include <gmp_util.h>
#include "D:/DevFiles/gmp-v19/mpir/x64/Release/gmp_util.h"
#include "D:/DevFiles/gmp-v19/mpir/x64/Release/mpirxx.h"
#include <omp.h>
#include <string>
#include <chrono>
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
	void sumOMP(gmpArray& gmpAr1, gmpArray& gmpAr2, int numThreads);//summarize with OMP
	void mulOMP(gmpArray& gmpAr1, gmpArray& gmpAr2, int numThreads);//multiply with OMP
	void setRandom(int k);//set elements to a random number in range from 2^(k-1) to 2^k-1
	int get_len();//get number of elements
};

//Wrapper C methods for C++ class
#ifdef _cplusplus
extern "C" {
#endif

	gmpArray* gmpArray_new(int count);
	void gmpArray_del(gmpArray* gmpArray);

	void gmpArray_resize(gmpArray* gmpArray, int number);
	void gmpArray_sumOMP(gmpArray& gmpArray1, gmpArray& gmpArray2, int numThreads);
	void gmpArray_mulOMP(gmpArray& gmpArray1, gmpArray& gmpArray2, int numThreads);

	int gmpArray_get_len(gmpArray* gmpArray);
#ifdef _cpluplus
}
#endif