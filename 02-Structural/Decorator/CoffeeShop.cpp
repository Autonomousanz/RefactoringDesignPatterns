#include <iostream>
#include <memory>
#include <string>
// COFFEE SHOP example
// Abstract base component
class Coffee{
    public:
        virtual ~Coffee() = default;
        virtual std::string getDescription() const = 0;
        virtual double getCost()const = 0;
};
// Concrete component - basic coffee 
class ColdBrew : public Coffee{
    public:
        std::string getDescription() const override{
            return "Cold Brew ";
        }
        double getCost() const override{
            return 2.0;
        }
};
// Abstract decorator base class
class CoffeeDecorator : public Coffee{
    protected:
        std::unique_ptr<Coffee> coffee;
    public:
    //prevent unintended implicit type conversions and ensure intentional object creation.
    explicit CoffeeDecorator(std::unique_ptr<Coffee> coffeeObj){
        this->coffee = std::move(coffeeObj);
    }
    std::string getDescription() const override{
        return coffee->getDescription();
    }
    double getCost() const override{
        return coffee->getCost();
    }
};
// concrete decorators
class MilkDecorator : public CoffeeDecorator{
    public:
        explicit MilkDecorator(std::unique_ptr<Coffee> coffeeObj) : CoffeeDecorator(std::move(coffeeObj)){}
        std::string getDescription() const override{
            return coffee->getDescription() + ", Milk";
        }
        double getCost() const override{
            return coffee->getCost() + 0.5;
        }
};
// concrete decorators
class SyrupDecorator : public CoffeeDecorator{
    public:
        explicit SyrupDecorator(std::unique_ptr<Coffee> coffeeObj): CoffeeDecorator(std::move(coffeeObj)){}
        std::string getDescription() const override{
            return coffee->getDescription() + ", Syrup";
        }
        double getCost()const override{
            return coffee->getCost() + 0.65;
        }
};
// concrete Decorators
class WhipCreamDecorator : public CoffeeDecorator{
    public:
        explicit WhipCreamDecorator(std::unique_ptr<Coffee> c):CoffeeDecorator(std::move(c)){}
        std::string getDescription() const override{
            return coffee->getDescription() + ", Whip Cream";
        }
        double getCost()const override{
            return coffee->getCost() + 0.6;
        }
};
// Helper function to print details of coffe
void printCoffeeInfo(const Coffee &coffe){
    std::cout  << "Description : " << coffe.getDescription() << " | Cost: $" << coffe.getCost() << std::endl;
}


int main() {
    std::cout << "=== Coffee Shop Decorator Pattern Demo ===\n" << std::endl;
    
    // Simple coffee
    auto coffee1 = std::make_unique<ColdBrew>();
    printCoffeeInfo(*coffee1);
    std::cout << std::endl;
    
    // Coffee with milk
    auto coffee2 = std::make_unique<MilkDecorator>(
        std::make_unique<ColdBrew>()
    );
    printCoffeeInfo(*coffee2);
    std::cout << std::endl;
    
    // Coffee with milk and syrup
    auto coffee3 = std::make_unique<SyrupDecorator>(
        std::make_unique<MilkDecorator>(
            std::make_unique<ColdBrew>()
        )
    );
    printCoffeeInfo(*coffee3);
    std::cout << std::endl;
    
    // Fancy coffee with all decorations
    auto fancyCoffee = std::make_unique<WhipCreamDecorator>(
        std::make_unique<SyrupDecorator>(
                std::make_unique<MilkDecorator>(
                    std::make_unique<ColdBrew>()
                )
            )
        );
    printCoffeeInfo(*fancyCoffee);
    std::cout << std::endl;
    
    // Demonstrate runtime decoration
    std::cout << "=== Runtime Decoration Example ===" << std::endl;
    
    auto baseCoffee = std::make_unique<ColdBrew>();
    std::cout << "Starting with: ";
    printCoffeeInfo(*baseCoffee);
    
    // Add decorations step by step (simulating user choices)
    auto step1 = std::make_unique<MilkDecorator>(std::move(baseCoffee));
    std::cout << "Added milk: ";
    printCoffeeInfo(*step1);
    
    auto step2 = std::make_unique<WhipCreamDecorator>(std::move(step1));
    std::cout << "Added WhipCream: ";
    printCoffeeInfo(*step2);
    
    auto finalCoffee = std::make_unique<SyrupDecorator>(std::move(step2));
    std::cout << "Added whip: ";
    printCoffeeInfo(*finalCoffee);
    
    return 0;
}