## Static Member Variables definition 
* Non-const static data members cannot be initialized inside the class. This was a language rule designed around the compilation model.
```
class Example {
    // ✅ These work inside the class:
    static const int MAX_SIZE = 100;           // const integral types
    static constexpr double PI = 3.14159;     // constexpr types
    
    // ❌ These DON'T work in older C++:
    static std::vector<int> data = {};         // Non-const complex types
    static std::string name = "default";      // Non-const non-integral types
};
```
The reason was about when and where memory gets allocated:
```
// If this were allowed everywhere:
class MyClass {
    static std::vector<int> data = {1, 2, 3}; // Where does this memory live?
};
```
Problems:

* Multiple definitions: If this header is included in multiple source files, you'd get multiple definitions
* Linker confusion: The linker wouldn't know which definition to use
* Memory allocation timing: When should the constructor for the vector be called?

### Modern C++ Solutions
C++17 introduced inline static:
```
class TreeTypeFactory {
private:
    // ✅ This works in C++17+
    inline static std::unordered_map<std::string, std::shared_ptr<TreeType>> treeTypes_;
    
    // Or with initialization:
    inline static std::unordered_map<std::string, std::shared_ptr<TreeType>> treeTypes_{};
};
```

The inline Keyword Magic
inline static tells the compiler:

"This variable can be defined in the header"
"If you see multiple definitions, they're all the same - just use one"
"Initialize it exactly once across the whole program"