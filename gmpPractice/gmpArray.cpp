#include "gmpArray.h"

gmpArray::gmpArray(int count)
{
	n = count;
	values = new mpz_t[n];
	for (int i = 0; i < n; i++)
	{
		mpz_init(values[i]);
	}
}
gmpArray::~gmpArray()
{
	for (int i = 0; i < n; i++)
	{
		mpz_clear(values[i]);
	}
	delete[] values;
}

mpz_t& gmpArray::operator[](int number)
{
	return values[number];
}

void gmpArray::print()
{
	for (int i = 0; i < n; i++)
	{
		std::cout << values[i] << std::endl;
	}
}

void gmpArray::clearValues()
{
	for (int i = 0; i < n; i++)
	{
		mpz_clear(values[i]);
	}
}
void gmpArray::resize(int number)
{
	mpz_t* temp = new mpz_t[number];
	for (int i = 0; i < number; i++)
	{
		mpz_init(temp[i]);
		if (i < n)
		{
			mpz_set(temp[i], values[i]);
		}
	}
	clearValues();
	delete[] values;
	values = temp;
	n = number;
}

void gmpArray::sum(gmpArray& gmpAr1, gmpArray& gmpAr2)
{
	if (gmpAr1.n != gmpAr2.n)
	{
		std::cout << "Can't summurize, array's lenghts are not equal" << std::endl;
	}
	else
	{
		if (n != gmpAr1.n)
		{
			this->resize(gmpAr1.n);
		}
		for (int i = 0; i < n; i++)
		{
			mpz_add(values[i], gmpAr1.values[i], gmpAr2.values[i]);
		}
	}
}

void gmpArray::mul(gmpArray& gmpAr1, gmpArray& gmpAr2)
{
	if (gmpAr1.n != gmpAr2.n)
	{
		std::cout << "Can't multiply, array's lenghts are not equal" << std::endl;
	}
	else
	{
		if (n != gmpAr1.n)
		{
			this->resize(gmpAr1.n);
		}
		for (int i = 0; i < n; i++)
		{
			mpz_mul(values[i], gmpAr1.values[i], gmpAr2.values[i]);
		}
	}
}

void gmpArray::sumOMP(gmpArray& gmpAr1, gmpArray& gmpAr2, int numThreads)
{
	if (gmpAr1.n != gmpAr2.n)
	{
		std::cout << "Can't summurize, array's lenghts are not equal" << std::endl;
	}
	else
	{
		if (n != gmpAr1.n)
		{
			this->resize(gmpAr1.n);
		}

		int i = 0;
		mpz_t* v1 = gmpAr1.values;
		mpz_t* v2 = gmpAr2.values;
		mpz_t* r = values;
#pragma omp parallel for shared(v1, v2, r) private(i) num_threads(numThreads)
		for (i = 0; i < n; i++)
		{
			mpz_add(values[i], gmpAr1.values[i], gmpAr2.values[i]);
		}
	}
}

void gmpArray::mulOMP(gmpArray& gmpAr1, gmpArray& gmpAr2, int numThreads)
{
	if (gmpAr1.n != gmpAr2.n)
	{
		std::cout << "Can't multiply, array's lenghts are not equal" << std::endl;
	}
	else
	{
		if (n != gmpAr1.n)
		{
			this->resize(gmpAr1.n);
		}

		int i = 0;
		mpz_t* v1 = gmpAr1.values;
		mpz_t* v2 = gmpAr2.values;
		mpz_t* r = values;
#pragma omp parallel for shared(v1, v2, r) private(i) num_threads(numThreads)
		for (i = 0; i < n; i++)
		{
			mpz_mul(values[i], gmpAr1.values[i], gmpAr2.values[i]);
		}
	}
}

void gmpArray::setRandom(int k)
{
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	for (int i = 0; i < n; i++)
	{
		mpz_rrandomb(values[i], state, k);
	}
}

int gmpArray::get_len()
{
	return this->n;
}

//Wrapper C methods for C++ class

//Constructor wrapper
gmpArray* gmpArray_new(int count)
{
	return new gmpArray(count);
}

//Destructor wrapper
void gmpArray_del(gmpArray* gmpArray)
{
	delete gmpArray;
}

void gmpArray_resize(gmpArray* gmpArray, int number)
{
	gmpArray->resize(number);
}

void gmpArray_sumOMP(gmpArray& gmpArray1, gmpArray& gmpArray2, int numThreads)
{
	gmpArray1.sumOMP(gmpArray1, gmpArray2, numThreads);
}

void gmpArray_mulOMP(gmpArray& gmpArray1, gmpArray& gmpArray2, int numThreads)
{
	gmpArray1.mulOMP(gmpArray1, gmpArray2, numThreads);
}

int gmpArray_get_len(gmpArray* gmpArray)
{
	return gmpArray->get_len();
}