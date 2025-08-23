#include <functional>
#include <memory>
#include <iostream>

// Example class for demonstration
class Circle {
public:
    Circle(double r = 1.0) : radius(r) {}
    double radius;
};

// Regular function
std::unique_ptr<Circle> createDefaultCircle() {
    return std::make_unique<Circle>(1.0); //default circle
}

// Function object (functor)
struct CircleCreator {
    double defaultRadius;
    CircleCreator(double r) : defaultRadius(r) {}
    
    std::unique_ptr<Circle> operator()() {
        return std::make_unique<Circle>(defaultRadius);
    }
};

int main() {
    // std::function can hold different types of callables
    std::function<std::unique_ptr<Circle>()> creator;
    
    // 1. Regular function
    creator = createDefaultCircle;
    auto circle1 = creator();
    std::cout << "Circle 1 radius: " << circle1->radius << std::endl;
    
    // 2. Lambda function (most common in factories)
    creator = []() { return std::make_unique<Circle>(5.0); };
    auto circle2 = creator();
    std::cout << "Circle 2 radius: " << circle2->radius << std::endl;
    
    // 3. Lambda with capture
    double capturedRadius = 10.0;
    creator = [capturedRadius]() { return std::make_unique<Circle>(capturedRadius); };
    auto circle3 = creator();
    std::cout << "Circle 3 radius: " << circle3->radius << std::endl;
    
    // 4. Function object
    creator = CircleCreator(7.0);
    auto circle4 = creator();
    std::cout << "Circle 4 radius: " << circle4->radius << std::endl;
    
    // 5. Member function (with std::bind - more complex)
    // This is less common in factory patterns
    
    return 0;
}