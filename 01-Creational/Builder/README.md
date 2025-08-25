Important Notes - 

1. We cannot call const Builder& but try to call non-const member functions like reset 

```
void Director::constructSportsCar(const Builder& build){
        build->reset(); // Incorrect Arrow operators 
    }


class CarBuilder: public Builder{
    private:
       Car* car;
    public:
        void reset() override{
            this->car = new Car();
        }
};
// Either remove  in parameter or add const to the void reset function // Remove const
```

2. Arrow operators vs Dot operators

**Nullability** :
Pointers (Builder*) can be null
References (Builder&) cannot be null - must be initialized when created
**Syntax** :
With pointers (Builder*): use -> to access members
With references (Builder&): use . to access members
**Reassignment** : 
Pointers can be reassigned: builder = new Builder();
References cannot be reassigned after initialization

```
// Pointer version
void Director::constructSportsCar(Builder* builder) {
    builder->reset();  // Use -> with pointers
    if (builder == nullptr) { // Can check for null
        return;
    }
}

// Reference version
void Director::constructSportsCar(Builder& builder) {
    builder.reset();   // Use . with references
    // Can't be null
}

// With pointers (->)
Builder* ptr = new Builder();
ptr->reset();         // Use -> with pointers

// With references (.)
Builder& ref = *ptr;  
ref.reset();          // Use . with references

// With objects (.)
Builder obj;
obj.reset();          // Use . with objects
```
Rule of thumb 

```
class Builder {
public:
    void reset() { }
};

class Director {
private:
    // Three different ways to store a Builder
    Builder  obj;     // Object
    Builder* ptr;     // Pointer
    Builder& ref;     // Reference
    
public:
    void example() {
        obj.reset();  // Use . for object
        ptr->reset(); // Use -> for pointer
        ref.reset();  // Use . for reference
    }
};
```
When to Use Which:

Use references (Builder&) when:

You want to ensure the parameter can't be null
You don't need to reassign the reference
You want to provide a cleaner syntax (using .)

Use pointers (Builder*) when:

The parameter might be null
You need to reassign the pointer
You're working with dynamic allocation
You need to represent optional parameters

3. Reference Member Initialization in the Director class, the builder reference member is not initialized in the constructor

```
class Director{
private:
    Builder& builder; // incorrect usage
};

// Correct usage 

class Director {
private:
    Builder* builder;  // Changed to pointer
public:
    Director() : builder(nullptr) {}  // Initialize builder
};

````

4. Implements proper memory management using smart pointers std::unique_ptr is preferred over raw pointers:
Memory is automatically freed when the unique_ptr goes out of scope
Handles exception safety automatically
Prevents memory leaks by design
```
// Problematic raw pointer approach
void makeCar() {
    auto director = new Director();  // Manually allocated
    Builder* builder = new CarBuilder();
    
    // If an exception occurs here, we leak memory
    director->constructSportsCar(builder);
    
    delete builder;    // Must remember to free
    delete director;   // Must remember to free
}

// Safe unique_ptr approach
void makeCar() {
    std::unique_ptr<Director> director = std::make_unique<Director>();
    std::unique_ptr<Builder> builder = std::make_unique<CarBuilder>();
    
    // Even if exception occurs, memory is automatically freed
    director->constructSportsCar(builder.get());
    
    // No manual deletion needed - automatically cleaned up
}

// Raw pointers don't communicate ownership
void someFunction(Director* dir) {
    // Should I delete dir? Who owns it?
    // Very unclear ownership semantics
}

// unique_ptr makes ownership clear
void someFunction(std::unique_ptr<Director> dir) {
    // Clearly shows this function takes ownership
}

void anotherFunction(Director* dir) {
    // Clearly just borrowing the pointer
}
```

Prevention of copy 
``` 
std::unique_ptr<Director> director1 = std::make_unique<Director>();
std::unique_ptr<Director> director2 = std::make_unique<Director>();

// This won't compile - prevents accidental copy
director2 = director1;  // Compilation error

// Must explicitly transfer ownership
director2 = std::move(director1);  // Now director1 is null
```

Modern c++ work better with smart pointers containers

```
// Modern containers work well with unique_ptr
std::vector<std::unique_ptr<Director>> directors;
directors.push_back(std::make_unique<Director>());

```

5. Unique ptr object dynamics , how to push object formed using unique ptr to methods that need raw pointer input argument

.get() is a method of smart pointers (like unique_ptr and shared_ptr) that returns the raw pointer managed by the smart pointer.
When you need to pass the pointer to a function that expects a raw pointer
```
void makeCar() {
    std::unique_ptr<Director> director = std::make_unique<Director>(); 
    std::unique_ptr<Builder> builder = std::make_unique<CarBuilder>();
    
    // builder.get() returns the raw Builder* pointer from unique_ptr
    director->constructSportsCar(builder.get());  // Safe because ownership stays with unique_ptr
}

// The function expects a raw pointer
void Director::constructSportsCar(Builder* builder) {
    builder->reset();
    // ... other operations
}
```
6. Using virtual destructor 

    virtual ~Builder() = default;  // Virtual destructor for proper cleanup when using polymorphism. This is a good practice to ensure derived class destructors are called correctly.

7. Type-getters

base class

```
    virtual void* getResult() = 0;
```
Derived class 
```
        void* getResult() override{
            Car* product = this->car;
            this->reset();
            return product;
        }
            // Add type-safe getter
        Car* getCarResult() {
            return static_cast<Car*>(getResult());
        }
            // Add type-safe getter
        Car* getCarResult() {
            return static_cast<Car*>(getResult());
        }
```

When calling above methods 
``` // Option 1: Using base class getResult with casting
            Car* car = static_cast<Car*>(builder->getResult());

            // Option 2: Using type-safe getter
    Car* car2 = builder->getCarResult();
``` 

## Run Instructions
 g++ -m64 InterfaceBuilder.cpp -o builder_program.exe
 
 .\builder_program.exe