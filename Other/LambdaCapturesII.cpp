#include <iostream>
#include <functional>
#include <memory>
#include <map>
#include <string>

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
        std::cout << color << " Circle (radius: " << radius << ")" << std::endl;
    }
};

class Rectangle : public Shape {
private:
    double width, height;
    std::string material;
public:
    Rectangle(double w, double h, const std::string& m) : width(w), height(h), material(m) {}
    void draw() const override {
        std::cout << material << " Rectangle (" << width << "x" << height << ")" << std::endl;
    }
};

int main() {
    std::cout << "=== Lambda Captures in Factory Pattern ===\n\n";
    
    // Factory using std::function that takes NO parameters
    std::map<std::string, std::function<std::unique_ptr<Shape>()>> factory;
    
    // Configuration values we want to capture
    double defaultRadius = 5.0;
    std::string favoriteColor = "Blue";
    double roomWidth = 10.0;
    double roomHeight = 8.0;
    std::string buildingMaterial = "Wood";
    
    std::cout << "Configuration:\n";
    std::cout << "  Default radius: " << defaultRadius << "\n";
    std::cout << "  Favorite color: " << favoriteColor << "\n";
    std::cout << "  Room size: " << roomWidth << "x" << roomHeight << "\n";
    std::cout << "  Material: " << buildingMaterial << "\n\n";
    
    // Register shapes with captured values
    std::cout << "Registering shapes with captured values...\n";
    
    // Capture by copy - lambda gets its own copy of the values
    factory["small_circle"] = [defaultRadius, favoriteColor]() {
        double smallRadius = defaultRadius / 2;  // Use captured value
        return std::make_unique<Circle>(smallRadius, favoriteColor);
    };
    
    factory["big_circle"] = [defaultRadius, favoriteColor]() {
        double bigRadius = defaultRadius * 2;   // Use captured value
        return std::make_unique<Circle>(bigRadius, favoriteColor);
    };
    
    factory["room_rectangle"] = [roomWidth, roomHeight, buildingMaterial]() {
        return std::make_unique<Rectangle>(roomWidth, roomHeight, buildingMaterial);
    };
    
    // Capture with modifications
    factory["golden_circle"] = [defaultRadius]() {
        std::string specialColor = "Gold";  // New value inside lambda
        return std::make_unique<Circle>(defaultRadius, specialColor);
    };
    
    // Now change the original values
    std::cout << "\nChanging original configuration values...\n";
    defaultRadius = 100.0;
    favoriteColor = "Red";
    roomWidth = 50.0;
    
    std::cout << "New values:\n";
    std::cout << "  Default radius: " << defaultRadius << "\n";
    std::cout << "  Favorite color: " << favoriteColor << "\n";
    std::cout << "  Room width: " << roomWidth << "\n\n";
    
    // Test the factory - lambdas still use the OLD captured values
    std::cout << "Creating shapes (using OLD captured values):\n";
    
    std::vector<std::string> shapeTypes = {
        "small_circle", "big_circle", "room_rectangle", "golden_circle"
    };
    
    for (const auto& type : shapeTypes) {
        std::cout << "Creating " << type << ": ";
        auto shape = factory[type]();  // Call the lambda!
        shape->draw();
    }
    
    std::cout << "\n=== Key Points ===\n";
    std::cout << "1. Lambdas captured values by COPY\n";
    std::cout << "2. Even though we changed the original variables,\n";
    std::cout << "3. The lambdas still use their captured copies\n";
    std::cout << "4. This is why small_circle still uses radius 2.5 (5.0/2)\n";
    std::cout << "5. Instead of 50.0 (100.0/2) from the new defaultRadius\n";
    
    return 0;
}