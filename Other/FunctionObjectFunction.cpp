#include <iostream>
#include <memory>
#include <vector>
#include <functional>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};

class Circle : public Shape {
private:
    double radius;
    std::string color;
public:
    Circle(double r, const std::string& c) : radius(r), color(c) {}
    void draw() const override {
        std::cout << color << " Circle (r=" << radius << ")" << std::endl;
    }
};

// ADVANTAGE 1: State Storage
struct ConfigurableCircleCreator {
    double defaultRadius;
    std::string defaultColor;
    int circlesCreated;  // Keep track of how many we've made!
    
    ConfigurableCircleCreator(double r, const std::string& c) 
        : defaultRadius(r), defaultColor(c), circlesCreated(0) {}
    
    std::unique_ptr<Circle> operator()() {
        circlesCreated++;  // Update state each time we're called
        std::cout << "Creating circle #" << circlesCreated << std::endl;
        return std::make_unique<Circle>(defaultRadius, defaultColor);
    }
    
    int getCount() const { return circlesCreated; }
};

// ADVANTAGE 2: Customizable behavior
struct SmartCircleCreator {
    double baseRadius;
    std::string color;
    bool shouldGrow;
    
    SmartCircleCreator(double r, const std::string& c, bool grow) 
        : baseRadius(r), color(c), shouldGrow(grow) {}
    
    std::unique_ptr<Circle> operator()() {
        double currentRadius = baseRadius;
        if (shouldGrow) {
            currentRadius *= 1.1;  // Grow by 10% each time
            baseRadius = currentRadius;  // Update for next time
        }
        return std::make_unique<Circle>(currentRadius, color);
    }
};

// ADVANTAGE 3: Multiple operator() overloads
struct MultiCreator {
    std::string defaultColor;
    
    MultiCreator(const std::string& c) : defaultColor(c) {}
    
    // Different ways to call this functor:
    
    // No parameters - use defaults
    std::unique_ptr<Circle> operator()() {
        return std::make_unique<Circle>(1.0, defaultColor);
    }
    
    // One parameter - custom radius
    std::unique_ptr<Circle> operator()(double radius) {
        return std::make_unique<Circle>(radius, defaultColor);
    }
    
    // Two parameters - custom everything
    std::unique_ptr<Circle> operator()(double radius, const std::string& color) {
        return std::make_unique<Circle>(radius, color);
    }
};

int main() {
    std::cout << "=== Advantages of Function Objects ===\n\n";
    
    // ADVANTAGE 1: State storage and tracking
    std::cout << "1. STATE STORAGE - Track how many circles created:\n";
    ConfigurableCircleCreator tracker(3.0, "Blue");
    
    for (int i = 0; i < 3; i++) {
        auto circle = tracker();
        circle->draw();
    }
    std::cout << "Total circles created: " << tracker.getCount() << "\n\n";
    
    // ADVANTAGE 2: Customizable behavior
    std::cout << "2. CUSTOMIZABLE BEHAVIOR - Growing circles:\n";
    SmartCircleCreator grower(2.0, "Green", true);
    
    for (int i = 0; i < 3; i++) {
        std::cout << "Creation #" << (i+1) << ": ";
        auto circle = grower();
        circle->draw();
    }
    std::cout << "\n";
    
    // ADVANTAGE 3: Multiple ways to call
    std::cout << "3. MULTIPLE OVERLOADS - Flexible creation:\n";
    MultiCreator flexible("Red");
    
    auto circle1 = flexible();              // Default size
    auto circle2 = flexible(5.0);           // Custom size
    auto circle3 = flexible(7.0, "Purple"); // Custom everything
    
    circle1->draw();
    circle2->draw(); 
    circle3->draw();
    std::cout << "\n";
    
    // ADVANTAGE 4: Works with std::function
    std::cout << "4. WORKS WITH STD::FUNCTION:\n";
    ConfigurableCircleCreator blueCreator(4.0, "Blue");
    
    // Can store functor in std::function
    std::function<std::unique_ptr<Circle>()> creator = blueCreator;
    auto circle4 = creator();
    circle4->draw();
    
    std::cout << "\n=== Summary of Advantages ===\n";
    std::cout << "✅ Store state/configuration\n";
    std::cout << "✅ Modify behavior over time\n";
    std::cout << "✅ Multiple operator() overloads\n";
    std::cout << "✅ Compatible with std::function\n";
    std::cout << "✅ More flexible than regular functions\n";
    std::cout << "✅ Can have constructors/destructors\n";
    
    return 0;
}