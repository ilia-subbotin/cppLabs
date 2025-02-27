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
        mid = l + (r - l) / 2;
        if (arr[mid] == x)
        {
            return 1;
        }
        if (arr[mid] > x)
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return -1; // Элемент не найден
}
int main()
{
    int A[1000000] = {0}, N = 10000, i = 0, t = 0, j = 0; // Нам нужно сравнить асимптотики, поэтому рассмотрим худший случай: массив из N нулей и ищем единицу
    while (i < 10000)                                                   // В задании не указан размер массива, поэтому уменьшим максимальный размер, чтобы программа завершилась быстрее
    {
        A[i] = i + 1;
        i = i + 1;
    }
    std::ofstream sf, bf; // Здесь храним данные
    sf.open("sf.txt");
    bf.open("bf.txt");
    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock ::now();
    auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    // Счётчик для прямого поиска
    while (N <= 1000000)
    {
        while (j < 100)
        {
            j = j + 1;
            begin = std::chrono::steady_clock::now();
            straight(A, N, -1);
            end = std::chrono::steady_clock ::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            t = time_span.count() + t;
        }
        sf << t / 100 << "\n";
        std::cout << t / 100 << "\r";
        j = 0;
        N = N + 10000;
        t = 0;
    }

    // Для бинарного поиска
    N = 10000;
    while (N <= 1000000)
    {
        while (j < 100)
        {
            j = j + 1;
            begin = std::chrono::steady_clock::now();
            binary(A, N, -1);
            end = std::chrono::steady_clock ::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            t = time_span.count() + t;
        }
        bf << t / 100 << "\n";
        std::cout << t / 100 << "\r";
        j = 0;
        N = N + 10000;
        t = 0;
    }
    sf.close();
    bf.close();
    std::cout << "Программа завершила работу" << std::endl;
    return 0;
}