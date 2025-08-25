## Constructor Pattern 

```
// BAD APPROACH: Using if-else chains
std::unique_ptr<Shape> createShapeBadWay(const std::string& type) {
    if (type == "circle") {
        return std::make_unique<Circle>();
    }
    else if (type == "rectangle") {
        return std::make_unique<Rectangle>();
    }
    // What if we add 50 more shape types? This gets messy!
    return nullptr;
}
```
 std::function as a "smart container" that can hold any function-like thing:
 
```
// NEW WAY: Map + std::function (GOOD!)
class GoodFactory {
private:
    std::map<std::string, std::function<std::unique_ptr<Shape>()>> creators;
    
public:
    // Register new types WITHOUT modifying existing code
    void addType(const std::string& name, std::function<std::unique_ptr<Shape>()> creator) {
        creators[name] = creator;
    }
    
    std::unique_ptr<Shape> create(const std::string& type) {
        auto it = creators.find(type);
        return (it != creators.end()) ? it->second() : nullptr;
    }
};
```
## Functor (function object)

```
 std::unique_ptr<Circle> operator()() {
        return std::make_unique<Circle>(defaultRadius);
    }
```
Stateful: Can remember values between calls
Configurable: Each object can have different settings
Flexible: Can have multiple operator() overloads
Compatible: Works with std::function, algorithms, etc.