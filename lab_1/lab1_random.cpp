#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <iomanip>
// Прямой поиск
int straight(int arr[], int N, int x) // N - размер массива, x - искомое число
{
    int index = 0;
    while (index < N)
    {
        if (arr[index] == x)
        {
            return index;
        }
        index = index + 1;
    }
    return -1; // Если x не найден
}

// Бинарный поиск
int binary(int arr[], int N, int x) // N - размер массива, x - искомое число
{
    int l = 0, r = N, mid;
    while (l < r)
    {
        mid = (l + r) / 2;
        if (arr[mid] > x)
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    r = r - 1;
    if (arr[r] == x)
    {
        return r;
    }
    return -1; // Элемент не найден
}

int get_random_number(int N) // Генератор случайных чисел от 1 до N
{
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, N);
    return dist(gen);
}

int main()
{
    int A[1000000] = {0}, N = 10000, t=0, i=0, j=0; // Ищем случайное число
    while (i<1000000)
    {
        A[i]=i+1;
        i=i+1;
    }
    std::ofstream sfr, bfr;                 // Здесь храним данные
    sfr.open("sfr.txt");
    bfr.open("bfr.txt");
    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock ::now();
    auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    
    // Счётчик для прямого поиска
    while (N <= 1000000)
    {   while (j<100)
        {
            j=j+1;
            begin = std::chrono::steady_clock::now();
            straight(A, N, get_random_number(1000000));
            end = std::chrono::steady_clock ::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            t=time_span.count()+t;
        }
        sfr << t/100 << "\n";
        std::cout << t/100 << "\r";
        j=0;
        N = N + 10000;
        t=0;
    }

    N=100;
    // Для бинарного поиска
    while (N <= 1000000)
    {   while (j<100)
        {
            j=j+1;
            begin = std::chrono::steady_clock::now();
            binary(A, N, get_random_number(1000000));
            end = std::chrono::steady_clock ::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            t=time_span.count()+t;
        }
        bfr << t/100 << "\n";
        std::cout << t/100 << "\r";
        j=0;
        N = N + 10000;
        t=0;
    }
    sfr.close();
    bfr.close();
    std::cout << "Программа завершила работу" << std::endl;
    return 0;
}