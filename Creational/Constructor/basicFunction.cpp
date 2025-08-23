#include <iostream>
#include <functional>

// Think of std::function like a "function variable"
// Just like you can have: int x = 5;
// You can have: std::function<int()> myFunc = someFunction;

// Regular function
int addTwoNumbers() {
    return 2 + 3;
}

int main() {
    std::cout << "=== Understanding std::function ===\n\n";
    
    // 1. std::function can hold a regular function
    std::function<int()> func1 = addTwoNumbers;
    std::cout << "Function 1 result: " << func1() << std::endl;
    
    // 2. std::function can hold a lambda (anonymous function)
    std::function<int()> func2 = []() { 
        return 10 * 2; 
    };
    std::cout << "Function 2 result: " << func2() << std::endl;
    
    // 3. You can change what function it holds!
    func1 = []() { return 100; };
    std::cout << "Function 1 (changed) result: " << func1() << std::endl;
    
    // 4. Different signatures //return type(arg1type, arg2type)
    std::function<int(int, int)> addFunc = [](int a, int b) { 
        return a + b; 
    };
    std::cout << "Add function result: " << addFunc(5, 7) << std::endl;
    
    // 5. Functions that return objects
    std::string temp = "Hello";
    // Option 1: Function takes no parameters
    std::function<std::string()> makeGreeting = [temp]() { 
        return temp; 
    };
    std::cout << "Greeting: " << makeGreeting() << std::endl;
    // Option 3: Function takes a parameter and uses it
    std::function<std::string(std::string)> makeGreeting3 = [temp](std::string name) { 
        return temp + " " + name; 
    };
    std::cout << "Greeting: " << makeGreeting3("Sanskruti") << std::endl;
    return 0;
}