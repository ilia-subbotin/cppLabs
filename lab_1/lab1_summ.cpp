#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <iomanip>
#include <algorithm>
// Прямой поиск суммы двух
int straight_sum(int arr[], int N, int sum) // N - размер массива, sum - искомая сумма, нам не важен результат поска, поэтому вернём 1, если такая пара есть, и 0 в ином случае
{
    int i = 0, j = 0;
    while (i < N)
    {
        j = 0;
        while (j < N)
        {
            if (arr[i] + arr[j] == sum)
            {
                return 1; // Если пара найдена
            }
            j = j + 1;
        }
        i = i + 1;
    }
    return -1; // Если пара не найдена
}

// Эффективный поиск
int eff_pair(int arr[], int N, int sum) // N - размер массива, sum - искомая сумма
{
    int l = 0, r = N - 1;
    while (l < r)
    {
        if (arr[l] + arr[r] == sum)
        {
            return 1; // Сейчас номера элементов не важны
        }
        if (arr[l] + arr[r] < sum)
        {
            l = l + 1;
        }
        if (arr[l] + arr[r] > sum)
        {
            r = r - 1;
        }
    }
    return -1; // Пары нет
}

int get_random_number(int N) // Генератор случайных чисел от 1 до N
{
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, N);
    return dist(gen);
}

int main()
{
    int A[10000] = {0}, N = 100, i = 0, j = 0;
    long long int t = 0;
    while (i < 10000) // В задании не указан размер массива, поэтому уменьшим максимальный размер, чтобы программа завершилась быстрее
    {
        A[i] = i+1;
        i = i + 1;
    }
    std::ofstream ssfr, epfr; // Здесь храним данные
    ssfr.open("ssfr.txt");
    epfr.open("epfr.txt");
    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock ::now();
    auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    // Счётчик для прямого поиска
    while (N <= 10000)
    {
        while (j < 100)
        {
            j = j + 1;
            begin = std::chrono::steady_clock::now();
            straight_sum(A, N, get_random_number(101));
            end = std::chrono::steady_clock ::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            t = time_span.count() + t;
        }
        ssfr << t / 100 << "\n";
        N = N + 100;
        j = 0;
        t = 0;
    }
    t = 0;
    j = 0;
    //std::sort(A, A + N); // Сортируем массив
    // Для бинарного поиска
    N = 100;
    while (N <= 10000)
    {
        while (j < 100)
        {
            j = j + 1;
            begin = std::chrono::steady_clock::now();
            eff_pair(A, N, get_random_number(101));
            end = std::chrono::steady_clock ::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            t = time_span.count() + t;
        }
        epfr << t / 100 << "\n";
        N = N + 100;
        j = 0;
        t = 0;
    }
    ssfr.close();
    epfr.close();
    std::cout << "Программа завершила работу" << std::endl;
    return 0;
}