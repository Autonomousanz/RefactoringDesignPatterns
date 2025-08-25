#include <iostream>
#include <memory>

class Circle {
public:
    double radius;
    Circle(double r) : radius(r) {}
    void show() const { 
        std::cout << "Circle with radius: " << radius << std::endl; 
    }
};

// This is a FUNCTOR (Function Object)
struct CircleCreator {
    double defaultRadius;  // Data stored in the object
    
    // Constructor - sets up the "configuration"
    CircleCreator(double r) : defaultRadius(r) {
        std::cout << "📋 CircleCreator configured with radius: " << r << std::endl;
    }
    
    // The MAGIC: operator() makes this object "callable"
    // This is what makes it a "function object"
    std::unique_ptr<Circle> operator()() {
        std::cout << "🏭 CircleCreator is being called! Creating circle..." << std::endl;
        return std::make_unique<Circle>(defaultRadius);
    }
};
//ADVANTAGE 1: State Storage
// ADVANTAGE 2: Customizable behavior
// ADVANTAGE 3: Multiple operator() overloads
int main() {
    std::cout << "=== Understanding Function Objects (Functors) ===\n\n";
    
    std::cout << "Step 1: Creating a CircleCreator object\n";
    CircleCreator creator(5.0);  // Create the functor with radius 5.0
    
    std::cout << "\nStep 2: Using the functor like a function\n";
    // This looks like a function call, but it's actually calling operator()!
    auto circle1 = creator();  // Same as creator.operator()()
    circle1->show();
    
    std::cout << "\nStep 3: Creating another functor with different config\n";
    CircleCreator bigCreator(10.0);
    auto circle2 = bigCreator();
    circle2->show();
    
    std::cout << "\nStep 4: The functor remembers its configuration\n";
    auto circle3 = creator();  // Still uses radius 5.0
    auto circle4 = creator();  // Still uses radius 5.0
    circle3->show();
    circle4->show();
    
    std::cout << "\n=== Key Points ===\n";
    std::cout << "1. CircleCreator is a CLASS that acts like a FUNCTION\n";
    std::cout << "2. operator() is what makes it 'callable'\n";
    std::cout << "3. It can store data (defaultRadius)\n";
    std::cout << "4. Each object remembers its own configuration\n";
    
    return 0;
}