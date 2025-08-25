#include <iostream>
#include <memory>
/*Abstract Products: Button and Checkbox interfaces*/
// Abstract Products
class Button {
public:
    virtual ~Button() = default;
    virtual void render() = 0;
};

class Checkbox {
public:
    virtual ~Checkbox() = default;
    virtual void render() = 0;
};
//Concrete Products: Windows and Mac implementations of each UI component
// Concrete Products - Windows Style
class WindowsButton : public Button {
public:
    void render() override {
        std::cout << "Rendering Windows-style button\n";
    }
};

class WindowsCheckbox : public Checkbox {
public:
    void render() override {
        std::cout << "Rendering Windows-style checkbox\n";
    }
};

// Concrete Products - Mac Style
class MacButton : public Button {
public:
    void render() override {
        std::cout << "Rendering Mac-style button\n";
    }
};

class MacCheckbox : public Checkbox {
public:
    void render() override {
        std::cout << "Rendering Mac-style checkbox\n";
    }
};
//Abstract Factory: GUIFactory interface that creates related products
// Abstract Factory
class GUIFactory {
public:
    virtual ~GUIFactory() = default;
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() = 0;
};
//Concrete Factories: WindowsFactory and MacFactory that create platform-specific components
// Concrete Factories
class WindowsFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<WindowsButton>();
    }
    
    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<WindowsCheckbox>();
    }
};

class MacFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<MacButton>();
    }
    
    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<MacCheckbox>();
    }
};
//Client: Application class that uses the factory without knowing concrete types
// Client code
class Application {
private:
    std::unique_ptr<GUIFactory> factory;
    
public:
    Application(std::unique_ptr<GUIFactory> f) : factory(std::move(f)) {}
    
    void createUI() {
        auto button = factory->createButton();
        auto checkbox = factory->createCheckbox();
        
        button->render();
        checkbox->render();
    }
};

// Usage
int main() {
    std::cout << "=== Windows UI ===\n";
    auto windowsApp = Application(std::make_unique<WindowsFactory>());
    windowsApp.createUI();
    
    std::cout << "\n=== Mac UI ===\n";
    auto macApp = Application(std::make_unique<MacFactory>());
    macApp.createUI();
    
    return 0;
}
/*Creates families of related objects (Windows or Mac UI components)
Ensures compatibility between products from the same factory
Easy to add new product families (e.g., Linux UI components)
Client code is decoupled from concrete classes*/