#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <iomanip>
// Стратегия А
int straight_A(int (&arr)[], int N, int x) // N - размер массива, x - искомое число
{
    int index = 0, a = arr[0];
    while (index < N)
    {
        if (arr[index] == x)
        {
            arr[0] = arr[index];
            arr[index] = a;
            return index;
        }
        index = index + 1;
    }
    return -1; // Если x не найден
}

// Стратегия B
int straight_B(int (&arr)[], int N, int x) // N - размер массива, x - искомое число
{
    int index = 0, a;
    while (index < N)
    {
        if (arr[index] == x and index != 0)
        {
            a = arr[index - 1];
            arr[index - 1] = arr[index];
            arr[index] = a;
            return index;
        }
        index = index + 1;
    }
    return -1; // Если x не найден
}

// Стратегия C
int straight_C(int (&arr)[], int (&s)[], int N, int x) // N - размер массива, x - искомое число
{
    int index = 0, a = arr[0], b = s[0];
    while (index < N)
    {
        if (arr[index] == x)
        {
            s[index] = s[index] + 1;
            if (s[index] > s[0])
            {
                arr[0] = arr[index];
                arr[index] = a;
                s[0] = s[index];
                s[index] = b;
            }
            return index;
        }
        index = index + 1;
    }
    return -1; // Если x не найден
}

int get_random_number(int N) // Генератор случайных чисел от 1 до N
{
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, N);
    return dist(gen);
}

int GaussianLike(int N)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    const double mean = (N + 1) / 2.0;
    const double stddev = N / 4.0;
    std::normal_distribution<> dist(mean, stddev);
    int result;
    do
    {
        result = static_cast<int>(std::round(dist(gen)));
    } while (result < 1 || result < N);
    return result;
}

int main()
{
    int A[10000] = {0}, sucess[10000] = {0}, N = 100, t, i = 0, k, j = 0; // Ищем случайное число
    while (i < 10000)
    {
        A[i] = get_random_number(50);
        i = i + 1;
    }
    std::ofstream strA1, strB1, strC1, strA2, strB2, strC2; // Здесь храним данные
    strA1.open("srtA1.txt");
    strB1.open("srtB1.txt");
    strC1.open("srtC1.txt");
    strA2.open("srtA2.txt");
    strB2.open("srtB2.txt");
    strC2.open("srtC2.txt");
    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock ::now();
    auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    // Стратегия А, равномермное распределение
    while (N <= 10000)
    {
        while (j < 100)
        {
            j = j + 1;
            begin = std::chrono::steady_clock::now();
            straight_A(A, N, get_random_number(51));
            end = std::chrono::steady_clock ::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            t = time_span.count() + t;
        }
        strA1 << t / 100 << "\n";
        N = N + 100;
        j = 0;
        t = 0;
    }
    t = 0;
    j = 0;
    N = 100;
    // Стратегия B, равномермное распределение
    while (N <= 10000)
    {
        while (j < 100)
        {
            j = j + 1;
            begin = std::chrono::steady_clock::now();
            straight_B(A, N, get_random_number(51));
            end = std::chrono::steady_clock ::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            t = time_span.count() + t;
        }
        strB1 << t / 100 << "\n";
        N = N + 100;
        j = 0;
        t = 0;
    }
    t = 0;
    j = 0;
    N = 100;
    // Стратегия C, равномермное распределение
    while (N <= 10000)
    {
        while (j < 100)
        {
            j = j + 1;
            begin = std::chrono::steady_clock::now();
            straight_C(A, sucess, N, get_random_number(51));
            end = std::chrono::steady_clock ::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            t = time_span.count() + t;
        }
        strC1 << t / 100 << "\n";
        N = N + 100;
        j = 0;
        t = 0;
    }
    t = 0;
    j = 0;
    N = 100;

    while (i < 10000)
    {
        A[i] = get_random_number(50);
        i = i + 1;
    }
    // Стратегия А, неравномермное распределение
    while (N <= 10000)
    {
        while (j < 100)
        {
            j = j + 1;
            begin = std::chrono::steady_clock::now();
            straight_A(A, N, GaussianLike(25));
            end = std::chrono::steady_clock ::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            t = time_span.count() + t;
        }
        strA2 << t / 100 << "\n";
        N = N + 100;
        j = 0;
        t = 0;
    }
    t = 0;
    j = 0;
    N = 100;
    // Стратегия B, неравномермное распределение
    while (N <= 10000)
    {
        while (j < 100)
        {
            j = j + 1;
            begin = std::chrono::steady_clock::now();
            straight_B(A, N, GaussianLike(25));
            end = std::chrono::steady_clock ::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            t = time_span.count() + t;
        }
        strB2 << t / 100 << "\n";
        N = N + 100;
        j = 0;
        t = 0;
    }
    t = 0;
    j = 0;
    N = 100;
    i = 0;
    while (i < 10000)
    {
        sucess[i] = 0;
        i = i + 1;
    }
    // Стратегия C, неравномермное распределение
    while (N <= 10000)
    {
        while (j < 100)
        {
            j = j + 1;
            begin = std::chrono::steady_clock::now();
            straight_C(A, sucess, N, GaussianLike(25));
            end = std::chrono::steady_clock ::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            t = time_span.count() + t;
        }
        strC2 << t / 100 << "\n";
        N = N + 100;
        j = 0;
        t = 0;
    }

    strA1.close();
    strB1.close();
    strC1.close();
    strA2.close();
    strB2.close();
    strC2.close();
    std::cout << "Программа завершила работу" << std::endl;
    return 0;
}