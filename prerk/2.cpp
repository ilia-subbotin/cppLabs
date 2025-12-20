#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

template<typename ForwardIterator, typename Function>
void transform_inplace(ForwardIterator first, ForwardIterator last, Function f) {
    for (; first != last; ++first) {
        f(*first);
    }
}

void to_uppercase_inplace(char& c) {
    c = std::toupper(static_cast<unsigned char>(c));
}

void transform_example(std::string world) {
    std::cout << "Before: " << std::quoted(world) << std::endl;

    transform_inplace(world.begin(), world.end(), to_uppercase_inplace);

    std::cout << "After:  " << std::quoted(world) << std::endl;
}

int main() {
    transform_example("hello world");

    std::vector<int> nums = { 1, 2, 3, 4, 5 };
    transform_inplace(nums.begin(), nums.end(), [](int& n) { n *= 2; });

    std::cout << "Numbers doubled: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << std::endl;

    return 0;
}