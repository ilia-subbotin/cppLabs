#include <iostream>
#include <exception>
#include <string>

class MathException : public std::exception {
public:
    MathException() : message_("Math error occurred") {}

    explicit MathException(const std::string& msg) : message_(msg) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }

protected:
    std::string message_;
};

class OverflowException : public MathException {
public:
    OverflowException() : MathException("Overflow error: division by zero") {}
    explicit OverflowException(const std::string& msg) : MathException(msg) {}
};

class UnderflowException : public MathException {
public:
    UnderflowException() : MathException("Underflow error") {}
    explicit UnderflowException(const std::string& msg) : MathException(msg) {}
};

int divide(int x, int y) {
    if (y == 0) {
        throw OverflowException();
    }
    return x / y;
}

int main() {
    try {
        int result = divide(10, 2);
        std::cout << "Result: " << result << std::endl;

        divide(10, 0);
    }
    catch (const MathException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}