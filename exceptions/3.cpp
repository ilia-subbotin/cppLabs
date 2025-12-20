#include <iostream>
#include <string>
#include <sstream>
#include <exception>

class bad_from_string : public std::exception {
public:
    explicit bad_from_string(const std::string& msg) : message_(msg) {}
    explicit bad_from_string(const char* msg) : message_(msg) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

template<class T>
T from_string(std::string const& s) {
    std::istringstream is(s);
    T tmp;

    if (!(is >> std::noskipws >> tmp)) {
        throw bad_from_string("Invalid conversion: format error");
    }

    char leftover;
    if (is >> leftover) {
        throw bad_from_string("Invalid conversion: extra characters detected");
    }

    return tmp;
}

int main() {
    try {
        std::string s1("123");
        int a1 = from_string<int>(s1);
        double b1 = from_string<double>(s1);
        std::string c1 = from_string<std::string>(s1);
        std::cout << "Test 1 (123) - int: " << a1 << ", double: " << b1 << ", string: " << c1 << std::endl;

        try {
            std::string s2("12.3");
            std::cout << "Test 2 (12.3) - double: " << from_string<double>(s2) << std::endl;
            from_string<int>(s2);
        }
        catch (const bad_from_string& e) {
            std::cout << "Test 2 expected error (int): " << e.what() << std::endl;
        }

        try {
            std::string s3("abc");
            from_string<int>(s3);
        }
        catch (const bad_from_string& e) {
            std::cout << "Test 3 expected error (abc to int): " << e.what() << std::endl;
        }

        try {
            std::string s4(" 123");
            from_string<int>(s4);
        }
        catch (const bad_from_string& e) {
            std::cout << "Test 4 expected error (leading space): " << e.what() << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }

    return 0;
}