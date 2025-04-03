#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <iomanip>
int *strategy_1(int *array, size_t size, int new_element)
{
    int *new_array = new int[size + 1];
    for (size_t i = 0; i < size; ++i)
    {
        new_array[i] = array[i];
    }
    new_array[size] = new_element;
    delete[] array;
    return new_array;
}

int *strategy_2(int *array, size_t size, size_t num, int new_element)
{
    if (num > size - 1)
    {
        int *new_array = new int[size + 100];
        for (size_t i = 0; i < size; ++i)
        {
            new_array[i] = array[i];
        }
        new_array[num] = new_element;
        delete[] array;
        return new_array;
    }
    array[num] = new_element;
    return array;
}

int *strategy_3(int *array, size_t size, size_t num, int new_element)
{
    if (num > size - 1)
    {
        int *new_array = new int[2 * size];
        for (size_t i = 0; i < size; ++i)
        {
            new_array[i] = array[i];
        }
        new_array[num] = new_element;
        delete[] array;
        return new_array;
    }
    array[num] = new_element;
    return array;
}

int main()
{
    int *A = new int[1];
    A[0] = 0;
    size_t s, n = 1;
    int N = 1;
    long long int t = 0;

    std::ofstream l1t1s1, l1t1s2, l1t1s3; // Здесь храним данные
    l1t1s1.open("l1t1s1.txt");
    l1t1s2.open("l1t1s2.txt");
    l1t1s3.open("l1t1s3.txt");
    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock ::now();
    auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    while (N < 100000)
    {
        begin = std::chrono::steady_clock::now();
        A = strategy_1(A, s, N);
        end = std::chrono::steady_clock ::now();
        time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        t = time_span.count() + t;
        l1t1s1 << t << "\n";
        s = s + 1;
        N = N + 1;
    }

    delete[] A;

    t = 0;
    N = 1;
    n = 1;
    s = 1;
    int *B = new int[1];
    B[0] = 0;

    while (N < 100000)
    {
        begin = std::chrono::steady_clock::now();
        B = strategy_2(B, s, n, N);
        end = std::chrono::steady_clock ::now();
        time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        t = time_span.count() + t;
        l1t1s2 << t << "\n";
        if (n > s - 1)
        {
            s = s + 100;
        }
        n = n + 1;
        N = N + 1;
    }

    delete[] B;

    t = 0;
    N = 1;
    n = 1;
    s = 1;
    int *C = new int[1];
    C[0] = 0;

    while (N < 100000)
    {
        begin = std::chrono::steady_clock::now();
        C = strategy_3(C, s, n, N);
        end = std::chrono::steady_clock ::now();
        time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        t = time_span.count() + t;
        l1t1s3 << t << "\n";
        if (n > s - 1)
        {
            s = 2 * s;
        }
        n = n + 1;
        N = N + 1;
    }

    delete[] C;

    l1t1s1.close();
    l1t1s2.close();
    l1t1s3.close();
    std::cout << "Программа завершила работу";
}