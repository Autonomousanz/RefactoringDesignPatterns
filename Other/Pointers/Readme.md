## Pointer Semantics for Composite Pattern

Raw Pointers (FileSystemComponent*):
```
cpp// Problematic - who owns and deletes these?
std::vector<FileSystemComponent*> children;  // Memory leak prone
```
Unique Pointers (std::unique_ptr):
```
cpp// Restrictive - exclusive ownership only
std::vector<std::unique_ptr<FileSystemComponent>> children;
// Can't easily share components between multiple parents
```

Value Semantics (storing objects directly):
cpp// Impossible due to polymorphism and abstract base class
```
std::vector<FileSystemComponent> children;  // Won't compile
```
When You Might Choose Differently:
std::unique_ptr: If you guarantee each component has exactly one parent and never need shared references
Raw pointers with manual management: In performance-critical code where you carefully manage lifetimes
Custom smart pointers: In embedded systems or when you need specific memory management behavior

1. Reference Counting
shared_ptr uses reference counting. Each time you copy it, the count increases:
```
auto file = std::make_shared<File>("test.txt");     // ref_count = 1
dir1->add(file);                                    // ref_count = 2
dir2->add(file);                                    // ref_count = 3
```

## Value Semantics

1. Independent Copies
int a = 5;
int b = a;    // b gets its own copy of the value 5
b = 10;       // Changing b doesn't affect a
// a is still 5, b is now 10

2. Copy Construction and Assignment
cppstd::string str1 = "hello";
std::string str2 = str1;     // Copy constructor - str2 gets its own copy
str2 = "world";              // Changing str2 doesn't affect str1

3. Automatic Memory Management
cpp{
    std::vector<int> vec = {1, 2, 3};
    // vec automatically manages its own memory
}  // vec is automatically destroyed here, memory cleaned up

![alt text](image.png)

## Value Semantics Don't Work with Polymorphism

1. Object Slicing
```
class Base { 
    virtual void func() { cout << "Base"; }
};

class Derived : public Base {
    int extra_data = 42;
    void func() override { cout << "Derived"; }
};

Derived d;
Base b = d;        // SLICING! extra_data is lost
b.func();          // Calls Base::func(), not Derived::func()
```

2. Abstract Classes Can't Be Instantiated
```
class Abstract {
    virtual void pure() = 0;  // Pure virtual
};

// These don't work:
Abstract obj;                    // ERROR: Can't instantiate abstract class
// WILL work
Derived someFile("example.txt")
Abstract* ptr = new Derived("test.txt");
Abstract& ref = someFile;

std::vector<Abstract> vec;       // ERROR: Can't create vector of abstract objects
// WILL work
std::vector<std::unique_ptr<Abstract>> vec; 

```

3. Polymorphism Requires Indirection
```
// This works (reference semantics):
Abstract* ptr = new Concrete();
ptr->pure();  // Calls Concrete::pure() via virtual dispatch

// This doesn't work (value semantics):
Abstract obj = concrete_instance;  // Can't compile
```