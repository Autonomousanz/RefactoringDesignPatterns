#include <iostream>
#include <string>

class IntegerWrapper {
private:
    int value;

public:
    IntegerWrapper(int val) : value(val) {}
    
    // Add extra functionality beyond what a plain int offers
    void increment() { value++; }
    void decrement() { value--; }
    bool isPositive() const { return value > 0; }
    bool isEven() const { return value % 2 == 0; }
    std::string toString() const { return std::to_string(value); }
    
    // Allow access to the underlying value
    int getValue() const { return value; }
    void setValue(int val) { value = val; }
    
    // Operator overloading for convenience
    operator int() const { return value; }
};

int main() {
    IntegerWrapper num(42);
    
    // Using added functionality
    std::cout << "Original value: " << num.getValue() << std::endl;
    num.increment();
    std::cout << "After increment: " << num.getValue() << std::endl;
    std::cout << "Is positive? " << (num.isPositive() ? "Yes" : "No") << std::endl;
    std::cout << "Is even? " << (num.isEven() ? "Yes" : "No") << std::endl;
    
    // Convert to string
    std::string str = num.toString();
    std::cout << "As string: " << str << std::endl;
    
    // Implicit conversion to int
    int plainInt = num;
    std::cout << "Implicit conversion: " << plainInt << std::endl;
    
    return 0;
}