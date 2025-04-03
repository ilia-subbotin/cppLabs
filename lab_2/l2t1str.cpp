#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <iomanip>

struct array_info
{
    int *data;
    size_t size;
};

array_info strategy_1(array_info array, int new_element)
{
    array_info res;
    int *new_array = new int[array.size + 1];
    for (size_t i = 0; i < array.size; ++i)
    {
        new_array[i] = array.data[i];
    }
    new_array[array.size] = new_element;
    res.size=array.size+1;
    res.data=new_array;
    delete[] new_array;
    return res;
}

array_info strategy_2(array_info array, size_t num, int new_element)
{
    if (num > array.size - 1)
    {
        array_info res;
        int *new_array = new int[array.size + 100];
        for (size_t i = 0; i < array.size; ++i)
        {
            new_array[i] = array.data[i];
        }
        new_array[num] = new_element;
        res.size=array.size+100;
        res.data=new_array;
        delete[] new_array;
        return res;
    }
    array.data[num] = new_element;
    return array;
}

array_info strategy_3(array_info array, size_t num, int new_element)
{
    if (num > array.size - 1)
    {
        array_info res;
        int *new_array = new int[2 * array.size];
        for (size_t i = 0; i < array.size; ++i)
        {
            new_array[i] = array.data[i];
        }
        new_array[num] = new_element;
        res.data=new_array;
        res.size=array.size*2;
        delete[] new_array;
        return res;
    }
    array.data[num] = new_element;
    return array;
}

int main()
{
    array_info A, B, C;
    int *a = new int[1];
    a[0] = 0;
    A.data=a;
    B.data=a;
    C.data=a;
    A.size=1;
    B.size=1;
    C.size=1;
    size_t n = 1;
    int N = 1;
    long long int t = 0;

    std::ofstream l1t1s1, l1t1s2, l1t1s3; // Здесь храним данные
    l1t1s1.open("l1t1s1.txt");
    l1t1s2.open("l1t1s2.txt");
    l1t1s3.open("l1t1s3.txt");
    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock ::now();
    auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    while (N < 1000)
    {
        begin = std::chrono::steady_clock::now();
        A = strategy_1(A, N);
        end = std::chrono::steady_clock ::now();
        time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        t = time_span.count() + t;
        l1t1s1 << t << "\n";
        N = N + 1;
    }

    t = 0;
    N = 1;
    n = 1;

    while (N < 1000)
    {
        begin = std::chrono::steady_clock::now();
        B = strategy_2(B, n, N);
        end = std::chrono::steady_clock ::now();
        time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        t = time_span.count() + t;
        l1t1s2 << t << "\n";
        n = n + 1;
        N = N + 1;
    }


    t = 0;
    N = 1;
    n = 1;

    while (N < 1000)
    {
        begin = std::chrono::steady_clock::now();
        C = strategy_3(C, n, N);
        end = std::chrono::steady_clock ::now();
        time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        t = time_span.count() + t;
        l1t1s3 << t << "\n";
        n = n + 1;
        N = N + 1;
    }

    l1t1s1.close();
    l1t1s2.close();
    l1t1s3.close();
    std::cout << "Программа завершила работу";
}