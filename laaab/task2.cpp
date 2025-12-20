#include <iostream>
#include <algorithm>
#include <utility>
#include <cassert>

template <typename T>
class Grid final
{
public:
    using value_type = T;
    using size_type = unsigned;

private:
    T *data;
    size_type y_size, x_size;

    struct Proxy
    {
        T *row_ptr;
        T &operator[](size_type x_idx) { return row_ptr[x_idx]; }
        T const &operator[](size_type x_idx) const { return row_ptr[x_idx]; }
    };

    struct ConstProxy
    {
        T const *row_ptr;
        T const &operator[](size_type x_idx) const { return row_ptr[x_idx]; }
    };

public:
    // Конструкторы из Задания 1
    Grid(T const &t) : y_size(1), x_size(1)
    {
        data = new T[1]{t};
    }

    Grid(size_type y_size, size_type x_size)
        : y_size(y_size), x_size(x_size)
    {
        data = new T[y_size * x_size]();
    }

    Grid(size_type y_size, size_type x_size, T const &t)
        : y_size(y_size), x_size(x_size)
    {
        size_type count = y_size * x_size;
        data = (T *)operator new(count * sizeof(T));
        for (size_type i = 0; i < count; ++i)
        {
            new (data + i) T(t);
        }
    }

    ~Grid()
    {
        if (data)
        {
            size_type count = y_size * x_size;
            for (size_type i = 0; i < count; ++i)
                data[i].~T();
            operator delete(data);
        }
    }

    Grid(Grid<T> const &other) : y_size(other.y_size), x_size(other.x_size)
    {
        size_type count = y_size * x_size;
        data = (T *)operator new(count * sizeof(T));
        for (size_type i = 0; i < count; ++i)
        {
            new (data + i) T(other.data[i]);
        }
    }

    Grid<T> &operator=(Grid<T> const &other)
    {
        if (this != &other)
        {
            Grid<T> temp(other);
            std::swap(data, temp.data);
            std::swap(y_size, temp.y_size);
            std::swap(x_size, temp.x_size);
        }
        return *this;
    }

    Grid(Grid<T> &&other) noexcept
        : data(other.data), y_size(other.y_size), x_size(other.x_size)
    {
        other.data = nullptr;
        other.y_size = 0;
        other.x_size = 0;
    }

    Grid<T> &operator=(Grid<T> &&other) noexcept
    {
        if (this != &other)
        {
            this->~Grid();
            data = other.data;
            y_size = other.y_size;
            x_size = other.x_size;
            other.data = nullptr;
            other.y_size = 0;
            other.x_size = 0;
        }
        return *this;
    }

    // Оператор индексирования
    // Возвращает объект, указывающий на начало нужной строки
    Proxy operator[](size_type y_idx)
    {
        return Proxy{data + (y_idx * x_size)};
    }

    ConstProxy operator[](size_type y_idx) const
    {
        return ConstProxy{data + (y_idx * x_size)};
    }

    // --- Методы доступа ---
    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }

    T operator()(size_type y_idx, size_type x_idx) const
    {
        return data[y_idx * x_size + x_idx];
    }

    T &operator()(size_type y_idx, size_type x_idx)
    {
        return data[y_idx * x_size + x_idx];
    }

    Grid<T> &operator=(T const &t)
    {
        size_type count = y_size * x_size;
        for (size_type i = 0; i < count; ++i)
            data[i] = t;
        return *this;
    }
};

int main()
{
    Grid<float> g(3, 2, 0.0f);
    assert(3 == g.get_y_size());
    assert(2 == g.get_x_size());

    using gsize_t = Grid<float>::size_type;

    // Проверка чтения через g[y][x]
    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(0.0f == g[y_idx][x_idx]);

    // Проверка записи через g[y][x]
    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            g[y_idx][x_idx] = 1.0f;

    // Проверка результата через оператор ()
    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(1.0f == g(y_idx, x_idx));

    std::cout << "Успех" << std::endl;
    return 0;
}