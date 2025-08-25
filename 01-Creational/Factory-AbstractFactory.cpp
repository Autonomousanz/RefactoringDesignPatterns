#include <iostream>
#include <memory>

// ============================================
// FACTORY METHOD PATTERN - Creates ONE type of object
// ============================================

// Product interface
class Vehicle {
public:
    virtual ~Vehicle() = default;
    virtual void start() = 0;
};

// Concrete products
class Car : public Vehicle {
public:
    void start() override {
        std::cout << "Car engine started\n";
    }
};

class Motorcycle : public Vehicle {
public:
    void start() override {
        std::cout << "Motorcycle engine started\n";
    }
};

// Factory Method - creates ONE type of object
class VehicleFactory {
public:
    virtual ~VehicleFactory() = default;
    virtual std::unique_ptr<Vehicle> createVehicle() = 0;
};

class CarFactory : public VehicleFactory {
public:
    std::unique_ptr<Vehicle> createVehicle() override {
        return std::make_unique<Car>();
    }
};

class MotorcycleFactory : public VehicleFactory {
public:
    std::unique_ptr<Vehicle> createVehicle() override {
        return std::make_unique<Motorcycle>();
    }
};

// ============================================
// ABSTRACT FACTORY PATTERN - Creates FAMILIES of related objects
// ============================================

// Multiple product interfaces (family of products)
class Button {
public:
    virtual ~Button() = default;
    virtual void render() = 0;
};

class Menu {
public:
    virtual ~Menu() = default;
    virtual void show() = 0;
};

// Windows family of products
class WindowsButton : public Button {
public:
    void render() override { std::cout << "Windows button rendered\n"; }
};

class WindowsMenu : public Menu {
public:
    void show() override { std::cout << "Windows menu shown\n"; }
};

// Mac family of products
class MacButton : public Button {
public:
    void render() override { std::cout << "Mac button rendered\n"; }
};

class MacMenu : public Menu {
public:
    void show() override { std::cout << "Mac menu shown\n"; }
};

// Abstract Factory - creates MULTIPLE related objects interfaces
class UIFactory {
public:
    virtual ~UIFactory() = default;
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<Menu> createMenu() = 0;
};

class WindowsUIFactory : public UIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<WindowsButton>();
    }
    std::unique_ptr<Menu> createMenu() override {
        return std::make_unique<WindowsMenu>();
    }
};

class MacUIFactory : public UIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<MacButton>();
    }
    std::unique_ptr<Menu> createMenu() override {
        return std::make_unique<MacMenu>();
    }
};

// ============================================
// DEMONSTRATION
// ============================================

int main() {
    std::cout << "=== FACTORY METHOD PATTERN ===\n";
    std::cout << "Creates ONE type of object\n\n";
    
    auto carFactory = std::make_unique<CarFactory>();
    auto car = carFactory->createVehicle();
    car->start();
    
    auto bikeFactory = std::make_unique<MotorcycleFactory>();
    auto bike = bikeFactory->createVehicle();
    bike->start();
    
    std::cout << "\n=== ABSTRACT FACTORY PATTERN ===\n";
    std::cout << "Creates FAMILIES of related objects\n\n";
    
    // Create Windows UI family
    std::cout << "Windows UI:\n";
    auto windowsFactory = std::make_unique<WindowsUIFactory>();
    auto winButton = windowsFactory->createButton();
    auto winMenu = windowsFactory->createMenu();
    
    winButton->render();
    winMenu->show();
    
    // Create Mac UI family
    std::cout << "\nMac UI:\n";
    auto macFactory = std::make_unique<MacUIFactory>();
    auto macButton = macFactory->createButton();
    auto macMenu = macFactory->createMenu();
    
    macButton->render();
    macMenu->show();
    
    return 0;
}