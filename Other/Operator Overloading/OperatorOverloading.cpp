#include <iostream>

class Number {
private:
    int value;

public:
    // Constructor
    Number(int val = 0) : value(val) {}

    // Conversion operator: allows implicit conversion to int
    operator int() const {
        return value;
    }

    // Explicit conversion operator (C++11 and later)
    explicit operator double() const {
        return static_cast<double>(value);
    }

    // Arithmetic operator overload
    Number operator+(const Number& other) const {
        return Number(value + other.value);
    }
    Number operator+(int other) const{
        return Number(value + other);
    }

    // Comparison operator overload
    bool operator>(const Number& other) const {
        return value > other.value;
    }

    // Getter method
    int getValue() const {
        return value;
    }

        // Setter method
    void setValue(int &value) const {
        value = value;
    }
};

int main() {
    Number num1(10);
    Number num2(20);

    // Implicit conversion to int using conversion operator
    int intValue = num1;  // Equivalent to: int intValue = num1.operator int();
    std::cout << "Implicit int conversion: " << intValue << std::endl;

    // Using conversion in different contexts
    int sum = num1 + 5;  // num1 is converted to int
    std::cout << "Sum with int: " << sum << std::endl;

    // Comparison using overloaded comparison operator
    if (num1 > num2) {
        std::cout << "num1 is greater than num2" << std::endl;
    } else {
        std::cout << "num1 is not greater than num2" << std::endl;
    }

    // Addition using overloaded + operator
    Number num3 = num1 + num2;
    std::cout << "Result of num1 + num2: " << num3.getValue() << std::endl;

    return 0;
}