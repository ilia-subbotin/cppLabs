#include <iostream>
#include <utility>

template<typename F, typename... Args>
auto invoke(F func, Args&&... args) -> decltype(func(std::forward<Args>(args)...)) {
    return func(std::forward<Args>(args)...);
}

int foo(int a, int b, int c) {
    return a * a * a + b * b + c;
}

float bar(float r) {
    return 3.14f * r * r;
}

int main() {
    int result1 = invoke(foo, 1, 2, 3);
    float result2 = invoke(bar, 1.0f);
    std::cout << result1 << " " << result2 << std::endl;
    return 0;
}