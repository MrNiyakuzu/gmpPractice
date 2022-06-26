#include <iostream>
#include "gmpArray.h"
#include <chrono>
#include <vector>
#include <iterator>
#include <string>

void timeTest(int ar_size, int pow, int num_mes, std::string task);
int main()
{
    int n = 100000, k = 1000, m = 100;
    timeTest(n, k, m, "sum");
    timeTest(n, k, m, "sumOMP");
    timeTest(n, k, m, "mul");
    timeTest(n, k, m, "mulOMP");
    return 0;
}

//ar_size - size of arrays
//pow - power for randomization(2^(pow-1), 2^pow-1)
//num_mes - number of measurement the time of working
//task - sum, sumOMP and other
void timeTest(int ar_size, int pow, int num_mes, std::string task)
{
    double average_time = 0;
    gmpArray op1(ar_size), op2(ar_size), res(ar_size);
    //res.setRandom(pow);
    op1.setRandom(pow);
    op2.setRandom(pow);
    std::vector<int> time;
    bool b = false;
    for (int i = 0; i < num_mes; i++)
    {
        auto begin = std::chrono::steady_clock::now();

        if (task == "sum")
        {
            res.sum(op1, op2);
            b = true;
        }
        if (task == "sumOMP")
        {
            res.sumOMP(op1, op2);
            b = true;
        }
        if (task == "mul")
        {
            res.mul(op1, op2);
            b = true;
        }
        if (task == "mulOMP")
        {
            res.mulOMP(op1, op2);
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
            time.push_back(elapsed_ms.count());
        }
        op1.setRandom(pow);
        op2.setRandom(pow);
    }
    std::cout << "Time was measured " << num_mes << " times, " << "average time of " << task << "= " << average_time / (num_mes) << " ms" << std::endl;
    copy(time.begin(), time.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}