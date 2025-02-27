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

int main()
{
    int A[100000] = {0}, sucess[100000] = {0}, N = 100, t, i = 0, k; // Ищем случайное число
    while (i < 100000)
    {
        A[i] = get_random_number(50);
        i = i + 1;
    }
    std::ofstream strA22, strB22, strC22; // Здесь храним данные
    strA22.open("srtA22.txt");
    strB22.open("srtB22.txt");
    strC22.open("srtC22.txt");
    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock ::now();
    auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    // Счётчик для стратегии А, неравномерно
    while (N <= 100000)
    {
        begin = std::chrono::steady_clock::now();
        k = get_random_number(60); // Неравномерное распределение, чем меньше число, тем оно чаще встречается
        k = get_random_number(k);
        k = get_random_number(k);
        k = get_random_number(k);
        k = get_random_number(k);
        straight_A(A, N, get_random_number(k));
        end = std::chrono::steady_clock ::now();
        time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        t = time_span.count();
        strA22 << t << "\n";
        std::cout << t << "\r";
        N = N + 1;
    }
    N = 100;

    // Счётчик для стратегии B, неравномерно
    while (N <= 100000)
    {
        begin = std::chrono::steady_clock::now();
        k = get_random_number(60);
        k = get_random_number(k);
        k = get_random_number(k);
        k = get_random_number(k);
        k = get_random_number(k);
        straight_B(A, N, get_random_number(k));
        end = std::chrono::steady_clock ::now();
        time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        t = time_span.count();
        strB22 << t << "\n";
        std::cout << t << "\r";
        N = N + 1;
    }
    N = 100;

    // Счётчик для стратегии C, неравномерно
    while (N <= 100000)
    {
        begin = std::chrono::steady_clock::now();
        k = get_random_number(60);
        k = get_random_number(k);
        k = get_random_number(k);
        k = get_random_number(k);
        k = get_random_number(k);
        straight_C(A, sucess, N, get_random_number(k));
        end = std::chrono::steady_clock ::now();
        time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        t = time_span.count();
        strC22 << t << "\n";
        std::cout << t << "\r";
        N = N + 1;
    }

    strA22.close();
    strB22.close();
    strC22.close();
    std::cout << "Программа завершила работу" << std::endl;
    return 0;
}