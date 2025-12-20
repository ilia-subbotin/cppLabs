#include <iostream>

template<typename T, typename U>
struct is_same {
    static constexpr bool value = false;
};

template<typename T>
struct is_same<T, T> {
    static constexpr bool value = true;
};

int main() {
    std::cout << std::boolalpha;
    bool same1 = is_same<int, int>::value;
    bool same2 = is_same<int, float>::value;
    std::cout << same1 << " " << same2 << std::endl;
    return 0;
}