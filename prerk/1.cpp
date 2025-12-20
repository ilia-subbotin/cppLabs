#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <cassert>

template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {
    ForwardIterator max_it = last;

    for (ForwardIterator it = first; it != last; ++it) {
        if (pred(*it)) {
            if (max_it == last || *max_it < *it) {
                max_it = it;
            }
        }
    }
    return max_it;
}

void TestUniqueMax() {
    auto IsEven = [](int x) { return x % 2 == 0; };

    const std::list<int> hill{ 2, 4, 8, 9, 6, 4, 2 };
    auto max_iterator = hill.begin();
    std::advance(max_iterator, 2);

    std::vector<int> numbers(10);
    std::iota(numbers.begin(), numbers.end(), 1);

    assert(max_element_if(numbers.begin(), numbers.end(), IsEven) == --numbers.end());
    assert(max_element_if(hill.begin(), hill.end(), IsEven) == max_iterator);
    std::cout << "TestUniqueMax passed!" << std::endl;
}

void TestSeveralMax() {
    struct IsCapitalized {
        bool operator()(const std::string& s) {
            return !s.empty() && std::isupper(s.front());
        }
    };
    const std::forward_list<std::string> text{
        "One", "two", "Three", "One", "Two", "Three", "one", "Two", "three"
    };

    auto max_iterator = text.begin();
    std::advance(max_iterator, 4);

    assert(max_element_if(text.begin(), text.end(), IsCapitalized()) == max_iterator);
    std::cout << "TestSeveralMax passed!" << std::endl;
}

int main() {
    TestUniqueMax();
    TestSeveralMax();
    return 0;
}