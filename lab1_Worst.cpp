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
int main()
{
    int A[1000000] = {0}, N = 100, x = 1, t; // Нам нужно сравнить асимптотики, поэтому рассмотрим худший случай: массив из N нулей и ищем единицу
    std::ofstream sf, bf;                 // Здесь храним данные
    sf.open("sf.txt");
    bf.open("bf.txt");
    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock ::now();
    auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    
    // Счётчик для прямого поиска
    while (N <= 1000000)
    {
        begin = std::chrono::steady_clock::now();
        straight(A, N, x);
        end = std::chrono::steady_clock ::now();
        time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        t=time_span.count();
        sf << t << "\n";
        std::cout << t << "\r";
        N = N + 1;
    }


    // Для бинарного поиска
    N = 100;
    while (N <= 1000000)
    {
        begin = std::chrono::steady_clock::now();
        binary(A, N, x);
        end = std::chrono::steady_clock ::now();
        time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        t=time_span.count();
        bf<<t <<"\n";
        std::cout << t << "\r";
        N = N + 1;
    }
    sf.close();
    bf.close();
    std::cout << "Программа завершила работу" << std::endl;
    return 0;
}