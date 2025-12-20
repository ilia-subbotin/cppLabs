#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

template <typename T, unsigned N>
class Grid;

template <typename T>
class Grid<T, 1>
{
public:
    using value_type = T;
    using size_type = unsigned;

private:
    std::vector<T> data;

public:
    Grid(size_type size, T const &t = T()) : data(size, t) {}

    T &operator[](size_type idx) { return data[idx]; }
    T const &operator[](size_type idx) const { return data[idx]; }

    T &operator()(size_type idx) { return data[idx]; }
    T const &operator()(size_type idx) const { return data[idx]; }

    size_type get_size() const { return data.size(); }
};

template <typename T, unsigned N>
class Grid
{
public:
    using value_type = T;
    using size_type = unsigned;

private:
    std::vector<Grid<T, N - 1>> data;
    size_type current_size;

public:
    template <typename... Args>
    Grid(size_type size, Args... args)
        : data(size, Grid<T, N - 1>(args...)), current_size(size)
    {
    }

    Grid<T, N - 1> &operator[](size_type idx)
    {
        return data[idx];
    }

    Grid<T, N - 1> const &operator[](size_type idx) const
    {
        return data[idx];
    }

    template <typename... Args>
    T &operator()(size_type idx, Args... args)
    {
        return data[idx](args...);
    }

    template <typename... Args>
    T const &operator()(size_type idx, Args... args) const
    {
        return data[idx](args...);
    }

    size_type get_size() const { return current_size; }
};

int main()
{
    // Создание трехмерной сетки
    Grid<float, 3> const g3(2, 3, 4, 1.0f);

    // Проверка доступа через круглые скобки
    assert(1.0f == g3(1, 1, 1));

    // Создание двумерной сетки
    Grid<float, 2> g2(2, 5, 2.0f);

    // Проверка доступа
    assert(2.0f == g2(1, 1));

    // Оператор индексирования возвращает сетку меньшей размерности
    g2 = g3[1];

    // Проверка результата после присваивания
    assert(1.0f == g2(1, 1));
    std::cout << "Успех" << std::endl;
    return 0;
}