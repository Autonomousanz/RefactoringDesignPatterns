## Abstract Factory Pattern

Abstract Products: Button and Checkbox interfaces
Concrete Products: Windows and Mac implementations of each UI component
Abstract Factory: GUIFactory interface that creates related products
Concrete Factories: WindowsFactory and MacFactory that create platform-specific components
Client: Application class that uses the factory without knowing concrete types

A pure virtual function (or abstract function) in C++ is a virtual function for which we can have an implementation, But we must override that function in the derived class, otherwise, the derived class will also become an abstract class. A pure virtual function is declared by assigning 0 in the declaration. 
```
// An abstract class
class Test {
    // Data members of class
public:
    // Pure Virtual Function
    virtual void show() = 0;

    /* Other members */
};
```
1. A class is abstract if it has at least one pure virtual function.
2. If we do not override the pure virtual function in the derived class, then the derived class also becomes an abstract class.
3. We can create pointers and references of abstract class type for new derived object.

```
 //creating an object of Derived class using
    // a pointer of the Base class
    Base* ptr = new Derived(6, 7);
     ptr->show(); // Derived class properties
     
```
In C++, the override keyword is used in derived classes to explicitly indicate that a virtual function is intended to override a base class method.
Example scenarios for using override:

1. Derived class implements virtual method from base class
2. Ensures compiler checks method signature matches base class
3. Prevents accidental creation of new methods instead of overriding

```
class Base {
public:
    virtual void someMethod() = 0;
};

class Derived : public Base {
public:
    // Correct override
    void someMethod() override { 
        // Implementation 
    }
};
```
An interface in C++ defines a contract that specifies a set of methods a class must implement. It serves as a blueprint for classes, ensuring they adhere to a particular behavior. C++ achieves interfaces through abstract classes, which contain at least one pure virtual function (a virtual function declared with = 0).

## Instructions to RUN THE CODE

```
g++ -c ProductFamilies.cpp AbstractFactoryPatternClass.cpp
g++ AbstractFactoryPattern.o ProductFamilies.o -o YourProgram
.\YourProgram.exe
```