#include <iostream>
#include <vector>

template<typename T>
class Array {
    std::vector<T> data;
public:
    Array(size_t n, const T& val) : data(n, val) {}
    T& operator[](size_t i) { return data[i]; }
    auto begin() const { return data.begin(); }
    auto end() const { return data.end(); }
};

template<typename T>
void flatten(const T& val, std::ostream& out) {
    out << val << " ";
}

template<typename T>
void flatten(const Array<T>& array, std::ostream& out) {
    for (auto&& elem : array) {
        flatten(elem, out);
    }
}

int main() {
    Array<int> ints(2, 0);
    ints[0] = 10;
    ints[1] = 20;
    flatten(ints, std::cout);
    std::cout << std::endl;

    Array<Array<int>> array_of_ints(2, ints);
    flatten(array_of_ints, std::cout);
    std::cout << std::endl;

    Array<double> doubles(3, 1.1);
    flatten(doubles, std::cout);
    std::cout << std::endl;

    return 0;
}