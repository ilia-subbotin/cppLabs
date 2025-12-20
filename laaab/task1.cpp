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

public:
    // Неявное преобразование из Т в Grid (размер 1x1)
    Grid(T const &t) : y_size(1), x_size(1)
    {
        data = new T[1]{t};
    }

    // Сетка y_size x x_size, заполненная по умолчанию
    Grid(size_type y_size, size_type x_size)
        : y_size(y_size), x_size(x_size)
    {
        data = new T[y_size * x_size]();
    }

    // Сетка y_size x x_size, заполненная копиями объекта t
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

    // Правило Пяти (RAII)

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

    // Конструктор копирования
    Grid(Grid<T> const &other)
        : y_size(other.y_size), x_size(other.x_size)
    {
        size_type count = y_size * x_size;
        data = (T *)operator new(count * sizeof(T));
        for (size_type i = 0; i < count; ++i)
        {
            new (data + i) T(other.data[i]);
        }
    }

    // Оператор присваивания копированием
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

    // Конструктор перемещения
    Grid(Grid<T> &&other) noexcept
        : data(other.data), y_size(other.y_size), x_size(other.x_size)
    {
        other.data = nullptr;
        other.y_size = 0;
        other.x_size = 0;
    }

    // Оператор присваивания перемещением
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
        {
            data[i] = t;
        }
        return *this;
    }
};

int main()
{
    // Проверка неявного преобразования (1x1)
    Grid<int> g1 = 5;
    assert(g1.get_y_size() == 1 && g1.get_x_size() == 1);
    assert(g1(0, 0) == 5);

    // Проверка конструктора с дефолтными значениями
    Grid<float> g2(2, 3);
    assert(g2.get_y_size() == 2 && g2.get_x_size() == 3);
    assert(g2(1, 1) == 0.0f);

    // Проверка конструктора с заполнением объектом t
    Grid<std::string> g3(2, 2, "Hello");
    assert(g3(0, 0) == "Hello" && g3(1, 1) == "Hello");

    // Проверка оператора присваивания всей сетке
    g3 = "World";
    assert(g3(0, 1) == "World");
    std::cout << "Успех" << std::endl;
    return 0;
}