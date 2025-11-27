#include<vector>
#include <iostream>
#include <string>

using namespace std;
// The Diamond Problem
class Animal {
protected:
    string name;
    int age;
    
public:
    Animal(const string& n = "Unknown", int a = 0) : name(n), age(a) {
        cout << "Animal constructor: " << name << endl;
    }
    
    virtual void speak() {
        cout << "Animal speaks\n";
    }
    
    void eat() {
        cout << name << " is eating\n";
    }
};

// Without virtual inheritance - PROBLEM!
class Mammal : public Animal {
public:
    Mammal(const string& n) : Animal(n) {
        cout << "Mammal constructor\n";
    }
    
    void giveBirth() {
        cout << "Mammal gives birth\n";
    }
};
// SOLUTION: Virtual Inheritance
class VirtualMammal : virtual public Animal {
public:
    VirtualMammal(const string& n = "") : Animal(n) {
        cout << "VirtualMammal constructor\n";
    }
    
    void giveBirth() {
        cout << "VirtualMammal gives birth\n";
    }
};
class Bird : public Animal {
public:
    Bird(const string& n) : Animal(n) {
        cout << "Bird constructor\n";
    }
    
    void layEggs() {
        cout << "Bird lays eggs\n";
    }
};

// Diamond Problem: Bat has two copies of Animal!
class Bat : public Mammal, public Bird {
public:
    Bat() : Mammal("Bat"), Bird("Bat") {
        cout << "Bat constructor\n";
        // Problem: Two Animal base classes!
        // Mammal::name and Bird::name are different!
    }
    
    void fly() {
        cout << "Bat flies\n";
    }
    
    // Ambiguity - which eat() to call?
    void feedBat() {
        // eat();  // ERROR: Ambiguous!
        Mammal::eat();  // Must specify which path
        Bird::eat();    // Or this path
    }
};



class VirtualBird : virtual public Animal {
public:
    VirtualBird(const string& n = "") : Animal(n) {
        cout << "VirtualBird constructor\n";
    }
    
    void layEggs() {
        cout << "VirtualBird lays eggs\n";
    }
};

// Correct implementation with virtual inheritance
class VirtualBat : public VirtualMammal, public VirtualBird {
public:
    // Most derived class must call virtual base constructor
    VirtualBat() : Animal("VirtualBat"), VirtualMammal(), VirtualBird() {
        cout << "VirtualBat constructor\n";
        // Now only ONE Animal base class!
    }
    
    void fly() {
        cout << "VirtualBat flies\n";
    }
    
    void feedBat() {
        eat();  // No ambiguity! Only one Animal::eat()
    }
};

void diamondProblemExample() {
    cout << "=== Without Virtual Inheritance ===" << endl;
    Bat bat;
    // bat.eat();  // ERROR: Ambiguous
    bat.Mammal::eat();
    bat.Bird::eat();
    cout << "Size of Bat: " << sizeof(Bat) << " bytes\n";  // Larger due to duplication
    
    cout << "\n=== With Virtual Inheritance ===" << endl;
    VirtualBat vbat;
    vbat.eat();  // Works! No ambiguity
    cout << "Size of VirtualBat: " << sizeof(VirtualBat) << " bytes\n";
}

// Alternative Design Pattern to Avoid Diamond Problem
class IFlyable {
public:
    virtual void fly() = 0;
    virtual ~IFlyable() = default;
};

class IMammal {
public:
    virtual void giveBirth() = 0;
    virtual ~IMammal() = default;
};

// Using composition and interfaces instead of multiple inheritance
class ModernBat : public Animal, public IFlyable, public IMammal {
public:
    ModernBat() : Animal("ModernBat") {}
    
    void fly() override {
        cout << "ModernBat flies\n";
    }
    
    void giveBirth() override {
        cout << "ModernBat gives birth\n";
    }
};