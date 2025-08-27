/*Value Semantics DefinitionValue semantics means that when you work with objects,
 you're working with independent copies of the actual data. 
Each object "owns" its data and operations on one object don't affect other objects.*/

#include <iostream>
#include <vector>
#include <memory>
#include <string>

class Person {
private:
    std::string name;
    int age;
    
public:
    Person(const std::string& name, int age) : name(name), age(age) {
        std::cout << "Creating Person: " << name << std::endl;
    }
    
    // Copy constructor (part of value semantics)
    Person(const Person& other) : name(other.name), age(other.age) {
        std::cout << "Copying Person: " << name << std::endl;
    }
    
    // Assignment operator (part of value semantics)
    Person& operator=(const Person& other) {
        std::cout << "Assigning Person: " << other.name << " to " << name << std::endl;
        if (this != &other) {
            name = other.name;
            age = other.age;
        }
        return *this;
    }
    
    ~Person() {
        std::cout << "Destroying Person: " << name << std::endl;
    }
    
    void display() const {
        std::cout << "Person: " << name << ", age " << age << std::endl;
    }
    
    void setAge(int newAge) { age = newAge; }
    std::string getName() const { return name; }
};

void demonstrateValueSemantics() {
    std::cout << "=== VALUE SEMANTICS DEMONSTRATION ===" << std::endl;
    
    // 1. Creating objects by value
    std::cout << "\n1. Creating objects:" << std::endl;
    Person alice("Alice", 25);
    Person bob("Bob", 30);
    
    // 2. Copying objects (value semantics)
    std::cout << "\n2. Copying objects:" << std::endl;
    Person alice_copy = alice;  // Copy constructor called
    Person charlie("Charlie", 35);
    charlie = bob;              // Assignment operator called
    
    // 3. Each object is independent
    std::cout << "\n3. Modifying copies doesn't affect originals:" << std::endl;
    alice_copy.setAge(99);
    alice.display();      // Still age 25
    alice_copy.display(); // Now age 99
    
    // 4. Storing by value in containers
    std::cout << "\n4. Storing in vector (value semantics):" << std::endl;
    std::vector<Person> people;
    people.push_back(alice);    // Copy of alice is stored
    people.push_back(bob);      // Copy of bob is stored
    
    // Modifying original doesn't affect the copies in vector
    alice.setAge(26);
    std::cout << "Original alice age changed to 26:" << std::endl;
    alice.display();
    std::cout << "But vector copy remains unchanged:" << std::endl;
    people[0].display();
    
    std::cout << "\n5. When objects go out of scope:" << std::endl;
    // All objects will be destroyed when function ends
}

void demonstrateReferenceSemantics() {
    std::cout << "\n=== REFERENCE SEMANTICS DEMONSTRATION ===" << std::endl;
    
    // 1. Creating objects and using pointers/references
    std::cout << "\n1. Using pointers and references:" << std::endl;
    Person original("Diana", 28);
    Person* ptr = &original;        // Pointer to original
    Person& ref = original;         // Reference to original
    
    // 2. No copying occurs
    std::cout << "\n2. No copying with pointers/references:" << std::endl;
    std::cout << "All refer to the same object:" << std::endl;
    original.display();
    ptr->display();
    ref.display();
    
    // 3. Modifications affect the same object
    std::cout << "\n3. Modifying through any reference affects all:" << std::endl;
    ptr->setAge(29);
    std::cout << "After modifying through pointer:" << std::endl;
    original.display();  // Shows age 29
    ref.display();       // Shows age 29
    
    // 4. Storing pointers (reference semantics)
    std::cout << "\n4. Storing pointers in vector:" << std::endl;
    std::vector<Person*> people_ptrs;
    people_ptrs.push_back(&original);
    
    // Modifying original affects what's "in" the vector
    original.setAge(30);
    std::cout << "After modifying original:" << std::endl;
    people_ptrs[0]->display();  // Shows age 30
}

void demonstrateSmartPointers() {
    std::cout << "\n=== SMART POINTERS (REFERENCE SEMANTICS WITH RAII) ===" << std::endl;
    
    std::cout << "\n1. Using shared_ptr:" << std::endl;
    auto person1 = std::make_shared<Person>("Eve", 32);
    auto person2 = person1;  // Sharing ownership, no copying of Person object
    
    std::cout << "Reference count: " << person1.use_count() << std::endl;
    
    std::cout << "\n2. Modifying through one affects the other:" << std::endl;
    person1->setAge(33);
    person2->display();  // Shows age 33
    
    std::vector<std::shared_ptr<Person>> smart_people;
    smart_people.push_back(person1);
    
    person1->setAge(34);
    std::cout << "After modifying original:" << std::endl;
    smart_people[0]->display();  // Shows age 34
}

// Demonstrating issues with mixing semantics
void demonstratePolymorphismIssues() {
    std::cout << "\n=== WHY VALUE SEMANTICS DON'T WORK WITH POLYMORPHISM ===" << std::endl;
    
    // Base class
    class Shape {
    public:
        virtual ~Shape() = default;
        virtual void draw() const { std::cout << "Drawing generic shape" << std::endl; }
        virtual double area() const { return 0.0; }
    };
    
    // Derived class
    class Circle : public Shape {
    private:
        double radius;
    public:
        Circle(double r) : radius(r) {}
        void draw() const override { 
            std::cout << "Drawing circle with radius " << radius << std::endl; 
        }
        double area() const override { return 3.14159 * radius * radius; }
    };
    
    std::cout << "\n1. Object slicing with value semantics:" << std::endl;
    Circle circle(5.0);
    Shape shape = circle;  // SLICING! Only Shape part is copied
    
    circle.draw();  // "Drawing circle with radius 5"
    shape.draw();   // "Drawing generic shape" - Circle behavior lost!
    
    std::cout << "\n2. Polymorphism works with reference semantics:" << std::endl;
    Shape* shape_ptr = &circle;
    Shape& shape_ref = circle;
    
    shape_ptr->draw();  // "Drawing circle with radius 5" - polymorphism works!
    shape_ref.draw();   // "Drawing circle with radius 5" - polymorphism works!
    
    std::cout << "\n3. This is why we use pointers for polymorphic containers:" << std::endl;
    // std::vector<Shape> shapes;  // Would cause slicing
    std::vector<std::shared_ptr<Shape>> shapes;  // Preserves polymorphism
    shapes.push_back(std::make_shared<Circle>(3.0));
    shapes[0]->draw();  // Correctly calls Circle::draw()
}

int main() {
    demonstrateValueSemantics();
    demonstrateReferenceSemantics();
    demonstrateSmartPointers();
    demonstratePolymorphismIssues();
    
    return 0;
}

/*
Key Takeaways:

VALUE SEMANTICS:
- Objects are copied when assigned or passed
- Each copy is independent 
- Modifications to copies don't affect originals
- Objects manage their own memory
- Automatic cleanup when objects go out of scope
- Examples: int, std::string, std::vector<T>, custom classes

REFERENCE SEMANTICS:  
- Objects are accessed through pointers/references
- Multiple references can point to the same object
- Modifications through any reference affect the same object
- Manual memory management (or smart pointers for RAII)
- Examples: int*, std::shared_ptr<T>, raw pointers

WHY POINTERS FOR POLYMORPHISM:
- Value semantics cause object slicing
- Polymorphism requires indirection (pointers/references)
- Virtual function dispatch only works through pointers/references
*/