#include <iostream>

template<typename T, typename U>
struct is_same {
    static constexpr bool value = false;
};

template<typename T>
struct is_same<T, T> {
    static constexpr bool value = true;
};

template<typename T, typename... Args>
struct are_same;

template<typename T>
struct are_same<T> {
    static constexpr bool value = true;
};

template<typename T, typename U, typename... Args>
struct are_same<T, U, Args...> {
    static constexpr bool value = is_same<T, U>::value && are_same<T, Args...>::value;
};

int main() {
    std::cout << std::boolalpha;
    bool same1 = are_same<int, int, int>::value;
    bool same2 = are_same<int, float, int>::value;
    std::cout << same1 << " " << same2 << std::endl;
    return 0;
}