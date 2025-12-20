#include <iostream>

template<typename T, unsigned N>
class Array {};

template<typename T, unsigned N>
unsigned size(const Array<T, N>&) {
    return N;
}

int main() {
    unsigned s1 = size(Array<int, 10>{});
    Array<float, 100> array;
    unsigned s2 = size(array);
    std::cout << s1 << " " << s2 << std::endl;
    return 0;
}