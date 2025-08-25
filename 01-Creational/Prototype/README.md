## Main Prototype Pattern requirements
Abstract Prototype (Shape): Defines the clone() interface that all concrete prototypes must implement
Concrete Prototypes (Circle, Rectangle, Triangle): Each implements the clone() method to create copies of themselves.The pattern is particularly useful when you have objects with many possible configurations and want to avoid the combinatorial explosion of subclasses or complex factory methods.
Copy constructor is called: make_unique<Resume>(*this) uses the copy constructor
New object created: A completely new Resume object with the same data
Independent object: Changes to the clone don't affect the original prototype

1. Copy constructor -  A constructor that initializes an object using another object of the same class
```
class MyClass : Parent{
public:
    int value;
    MyClass(int v) : value(v) {}
    MyClass(const MyClass& other) : Parent(other), value(other.value) {}
};

int main() {
    MyClass obj1(5);
    MyClass obj2 = obj1; // Calls copy constructor
    return 0;
}
```
2. Pure virtual clone method that must be implemented by derived classes
```
    virtual Shape* clone() const = 0;
```

3. To use static cast for type conversion at compile time for above clone method return type object


```
// Create a clone of the original rectangle
    Rectangle* clone = static_cast<Rectangle*>(original->clone()); // single clone returns type Shape* 

//example 2

class Base {};
class Derived : public Base {};

Derived* derived = new Derived();
Base* base = static_cast<Base*>(derived);

// example 3
int i = 10;
float f = static_cast<float>(i);

// example 4 
//Downcasting (base class pointer to derived class pointer, when you're sure it's safe)
Base* base = new Derived();
Derived* derived = static_cast<Derived*>(base);


//example 5
//Converting void* to a typed pointer:

void* voidPtr = &base;
Derived* typedPtr = static_cast<Derived*>(voidPtr);

```

Pros of Prototype 

You can clone objects without coupling to their concrete classes.
You can get rid of repeated initialization code in favor of cloning pre-built prototypes.

Cons 

Cloning complex objects that have circular references might be very tricky.
