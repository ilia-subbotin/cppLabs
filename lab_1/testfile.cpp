// Файл, чтобы тестировать работу подпрограмм
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <algorithm>
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

int main()
{
    int A[10] = {0}, N = 10, t, i = 0, B[] = {1, 2, 3, 4, 5};
    while (i < N)
    {
        A[i] = get_random_number(100);
        i = i + 1;
    }
    std::cout << get_random_number(10) << std::endl;
    std::cout << get_random_number(100) << std::endl;
    std::cout << get_random_number(1000) << std::endl;
    std::cout << straight_sum(A, N, 3) << std::endl;
    std::cout << straight_sum(A, N, 0) << std::endl;
    i = 0;
    while (i < N)
    {
        std::cout << A[i] << " ";
        i = i + 1;
    }
    std::cout << std::endl;
    std::sort(A, A + N); // Сортируем массив
    i = 0;
    while (i < N)
    {
        std::cout << A[i] << " ";
        i = i + 1;
    }
    std::cout << std::endl;
    std::cout << eff_pair(A, N, 0) << std::endl;
    std::cout << eff_pair(A, N, 10) << std::endl;
    std::cout << eff_pair(A, N, 48) << std::endl;
    std::cout << binary(A, N, 11) << std::endl;
    std::cout << binary(A, N, 18) << std::endl;
    std::cout << binary(A, N, 68) << std::endl;
    std::cout << std::endl;
    i = 0;
    while (i < 5)
    {
        std::cout << B[i] << " ";
        i = i + 1;
    }
    straight_A(B, 5, 4);
    std::cout << std::endl;
    i = 0;
    while (i < 5)
    {
        std::cout << B[i] << " ";
        i = i + 1;
    }

    straight_B(B, 5, 1);
    std::cout << std::endl;
    i = 0;
    while (i < 5)
    {
        std::cout << B[i] << " ";
        i = i + 1;
    }
    std::cout << std::endl;
    int s[5] = {0};
    straight_C(B, s, 5, 1);
    std::cout << std::endl;
    i = 0;
    while (i < 5)
    {
        std::cout << B[i] << " ";
        i = i + 1;
    }
    std::cout << " ";
    i = 0;
    while (i < 5)
    {
        std::cout << s[i] << " ";
        i = i + 1;
    }
    straight_C(B, s, 5, 3);
    std::cout << std::endl;
    i = 0;
    while (i < 5)
    {
        std::cout << B[i] << " ";
        i = i + 1;
    }
    std::cout << " ";
    i = 0;
    while (i < 5)
    {
        std::cout << s[i] << " ";
        i = i + 1;
    }
    straight_C(B, s, 5, 4);
    std::cout << std::endl;
    i = 0;
    while (i < 5)
    {
        std::cout << B[i] << " ";
        i = i + 1;
    }
    std::cout << " ";
    i = 0;
    while (i < 5)
    {
        std::cout << s[i] << " ";
        i = i + 1;
    }
    straight_C(B, s, 5, 4);
    std::cout << std::endl;
    i = 0;
    while (i < 5)
    {
        std::cout << B[i] << " ";
        i = i + 1;
    }
    std::cout << " ";
    i = 0;
    while (i < 5)
    {
        std::cout << s[i] << " ";
        i = i + 1;
    }
    return 0;
}