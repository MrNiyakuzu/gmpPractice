#include <iostream>
#include "gmpArray.h"
#include <chrono>
#include <vector>
#include <iterator>
#include <string>
#include <fstream>

std::string timeTest(int ar_size, int pow, int num_mes, std::string task, int numThreads);
int main()
{
    int n, k = 2000, m = 75;
    std::ofstream fout("time.csv");
    for (int j = 1; j < 5; j++)
    {
        if (j == 1)
        {
            n = 10000;
        }

        if (j == 2)
        {
            n = 25000;
        }

        if (j == 3)
        {
            n = 50000;
        }
        if (j == 4)
        {
            n = 100000;
        }

        for (int i = 1; i < 5; i++)
        {
            fout << timeTest(n, k, m, "sumOMP", i);
        }
        fout << '\n';
        for (int i = 1; i < 5; i++)
        {
            fout << timeTest(n, k, m, "mulOMP", i);
        }
        fout << '\n';
    }

    fout.close();
    return 0;
}

//ar_size - size of arrays
//pow - power for randomization(2^(pow-1), 2^pow-1)
//num_mes - number of measurement the time of working
//task - sum, sumOMP and other
std::string timeTest(int ar_size, int pow, int num_mes, std::string task, int numThreads)
{
    double average_time = 0;
    gmpArray op1(ar_size), op2(ar_size), res(ar_size);
    bool b = false;
    for (int i = 0; i < num_mes + 1; i++)
    {
        op1.setRandom(pow);
        op2.setRandom(pow);
        auto begin = std::chrono::steady_clock::now();

        if (task == "sumOMP")
        {
            res.sumOMP(op1, op2, numThreads);
            b = true;
        }
        if (task == "mulOMP")
        {
            res.mulOMP(op1, op2, numThreads);
            b = true;
        }
        if (!b)
        {
            std::cout << "Wrong task" << std::endl;
            break;
        }

        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (i != 0)
        {
            average_time += elapsed_ms.count();
        }

    }

    std::string str;
    str = "Number of threads= " + std::to_string(numThreads);
    //str += ", numbers in range 2^(" + std::to_string(pow) + "-1), 2^" + std::to_string(pow) + "-1";
    str += ", arrays' size= " + std::to_string(ar_size);
    str += ", average time of " + task + "= " + std::to_string(average_time / (num_mes)) + "ms\n";

    return str;
}