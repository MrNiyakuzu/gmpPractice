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

void gmpArray::resize(int number)
{
	mpz_t* temp = new mpz_t[number];
	for (int i = 0; i < number; i++)
	{
		mpz_init(temp[i]);
		if (i < n)
		{
			mpz_set(temp[i], values[i]);
			mpz_clear(values[i]);
		}
	}
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

void gmpArray::sumOMP(gmpArray& gmpAr1, gmpArray& gmpAr2)
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

		int threadsNum = 2;
		omp_set_num_threads(threadsNum);
		int i = 0;
#pragma omp parallel for shared(gmpAr1.values, gmpAr2.values, values) private(i)
		for (i = 0; i < n; i++)
		{
			mpz_add(values[i], gmpAr1.values[i], gmpAr2.values[i]);
		}
	}
}

void gmpArray::mulOMP(gmpArray& gmpAr1, gmpArray& gmpAr2)
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

		int threadsNum = 2;
		omp_set_num_threads(threadsNum);
		int i = 0;
#pragma omp parallel for shared(gmpAr1.values, gmpAr2.values, values) private(i)
		for (i = 0; i < n; i++)
		{
			mpz_mul(values[i], gmpAr1.values[i], gmpAr2.values[i]);
		}
	}
}