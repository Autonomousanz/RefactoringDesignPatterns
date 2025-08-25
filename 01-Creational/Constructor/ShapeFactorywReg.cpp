#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <functional>
//Registry-based: Register constructor functions and create objects by type name
//Runtime Creation: Create objects based on runtime information (like user input)
// Base class that defines the interface for objects
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual std::string getType() const = 0;
};

// Concrete implementations
class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r = 1.0) : radius(r) {}
    
    void draw() const override {
        std::cout << "Drawing Circle with radius: " << radius << std::endl;
    }
    
    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this);
    }
    
    std::string getType() const override {
        return "Circle";
    }
    
    void setRadius(double r) { radius = r; }
    double getRadius() const { return radius; }
};

class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double w = 1.0, double h = 1.0) : width(w), height(h) {}
    
    void draw() const override {
        std::cout << "Drawing Rectangle " << width << "x" << height << std::endl;
    }
    
    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Rectangle>(*this);
    }
    
    std::string getType() const override {
        return "Rectangle";
    }
    
    void setDimensions(double w, double h) { width = w; height = h; }
    double getWidth() const { return width; }
    double getHeight() const { return height; }
};

class Triangle : public Shape {
private:
    double base, height;
    
public:
    Triangle(double b = 1.0, double h = 1.0) : base(b), height(h) {}
    
    void draw() const override {
        std::cout << "Drawing Triangle base: " << base << ", height: " << height << std::endl;
    }
    
    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Triangle>(*this);
    }
    
    std::string getType() const override {
        return "Triangle";
    }
    
    void setDimensions(double b, double h) { base = b; height = h; }
    double getBase() const { return base; }
    double getHeight() const { return height; }
};

// Constructor Pattern Implementation
class ShapeFactory {
private:
    // Registry of constructor functions
    std::map<std::string, std::function<std::unique_ptr<Shape>()>> constructors; // "circle" : object of circle Runtime Type Resolution:
    // The client code doesn't need to know about specific classes - it just needs to know the string identifier
    // Purpose: Encapsulates object creation logic and provides a way to create objects without specifying their exact classes
public:
    // Register a constructor function for a shape type
    void registerConstructor(const std::string& type, std::function<std::unique_ptr<Shape>()> constructor) {
        constructors[type] = constructor;
    }
    
    // Create an object using the registered constructor
    std::unique_ptr<Shape> create(const std::string& type) {
        auto it = constructors.find(type);
        if (it != constructors.end()) {
            return it->second();
        }
        std::cout << "Unknown shape type: " << type << std::endl;
        return nullptr;
    }
    
    // List available types
    void listAvailableTypes() const {
        std::cout << "Available shape types: ";
        for (const auto& pair : constructors) {
            std::cout << pair.first << " ";
        }
        std::cout << std::endl;
    }
};

// Alternative Constructor Pattern using function pointers
class SimpleShapeFactory {
public:
    enum ShapeType { CIRCLE, RECTANGLE, TRIANGLE };
    
    static std::unique_ptr<Shape> createShape(ShapeType type) {
        switch (type) {
            case CIRCLE:
                return std::make_unique<Circle>();
            case RECTANGLE:
                return std::make_unique<Rectangle>();
            case TRIANGLE:
                return std::make_unique<Triangle>();
            default:
                return nullptr;
        }
    }
    
    // Constructor pattern with parameters
    static std::unique_ptr<Shape> createCircle(double radius) {
        return std::make_unique<Circle>(radius);
    }
    
    static std::unique_ptr<Shape> createRectangle(double width, double height) {
        return std::make_unique<Rectangle>(width, height);
    }
    
    static std::unique_ptr<Shape> createTriangle(double base, double height) {
        return std::make_unique<Triangle>(base, height);
    }
};

// Constructor Pattern with template metaprogramming
template<typename T>
class GenericFactory {
public:
    template<typename... Args>
    static std::unique_ptr<T> create(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
};

// Usage examples
int main() {
    std::cout << "=== Constructor Pattern Examples ===\n\n";
    
    // Example 1: Registry-based Constructor Pattern
    std::cout << "1. Registry-based Constructor Pattern:\n";
    ShapeFactory factory;
    
    // Register constructors
    factory.registerConstructor("circle", []() { return std::make_unique<Circle>(5.0); });
    factory.registerConstructor("rectangle", []() { return std::make_unique<Rectangle>(4.0, 3.0); });
    factory.registerConstructor("triangle", []() { return std::make_unique<Triangle>(6.0, 4.0); });
    
    factory.listAvailableTypes();
    
    auto shape1 = factory.create("circle");
    auto shape2 = factory.create("rectangle");
    auto shape3 = factory.create("triangle");
    
    if (shape1) shape1->draw();
    if (shape2) shape2->draw();
    if (shape3) shape3->draw();
    
    std::cout << "\n";
    
    // Example 2: Simple Constructor Pattern
    std::cout << "2. Simple Constructor Pattern:\n";
    auto circle = SimpleShapeFactory::createShape(SimpleShapeFactory::CIRCLE);
    auto rectangle = SimpleShapeFactory::createRectangle(10.0, 8.0);
    auto triangle = SimpleShapeFactory::createTriangle(7.0, 5.0);
    
    circle->draw();
    rectangle->draw();
    triangle->draw();
    
    std::cout << "\n";
    
    // Example 3: Template-based Constructor Pattern
    std::cout << "3. Template-based Constructor Pattern:\n";
    auto genericCircle = GenericFactory<Circle>::create(3.14);
    auto genericRectangle = GenericFactory<Rectangle>::create(2.0, 4.0);
    auto genericTriangle = GenericFactory<Triangle>::create(1.5, 2.5);
    
    genericCircle->draw();
    genericRectangle->draw();
    genericTriangle->draw();
    
    std::cout << "\n";
    
    // Example 4: Runtime type creation
    std::cout << "4. Runtime Constructor Pattern:\n";
    std::string userInput = "rectangle";  // Simulating user input
    auto userShape = factory.create(userInput);
    if (userShape) {
        std::cout << "User requested: ";
        userShape->draw();
    }
    
    return 0;
}