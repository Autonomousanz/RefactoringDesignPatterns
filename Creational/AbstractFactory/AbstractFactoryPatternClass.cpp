#include "ProductFamilies.h"
#include "AbstractFactoryPatternClass.h"
#include <memory>
#include<iostream>
using namespace std;
// For each variant of a product family of chair sofa and coffeetable, we create a separate factory class based on the AbstractFactory interface

// The client code has to work with both factories and products via their respective abstract interfaces. 
//The client doesn’t have to be aware of the factory’s class, nor does it matter what kind of chair it gets.
//concrete factories instantiate concrete products, signatures of their creation methods must return corresponding abstract products. This way the client code that uses a factory
//doesn’t get coupled to the specific variant of the product it gets from a factory
// Client code
// Victorian Factory Implementation
std::unique_ptr<Chair> VictorianFurnitureFactory::createChair() const {
    return std::make_unique<VictorianChair>();
}

std::unique_ptr<Sofa> VictorianFurnitureFactory::createSofa() const {
    return std::make_unique<VictorianSofa>();
}

std::unique_ptr<CoffeeTable> VictorianFurnitureFactory::createCoffeetable() const {
    return std::make_unique<VictorianCoffeetable>();
}

// Modern Factory Implementation
std::unique_ptr<Chair> ModernFurnitureFactory::createChair() const {
    return std::make_unique<ModernChair>();
}

std::unique_ptr<Sofa> ModernFurnitureFactory::createSofa() const {
    return std::make_unique<ModernSofa>();
}

std::unique_ptr<CoffeeTable> ModernFurnitureFactory::createCoffeetable() const {
    return std::make_unique<ModernCoffeetable>();
}

class Client {
public:
    void createFurniture(const FurnitureFactory& factory) {

        auto chair = factory.createChair(); // std::unique_ptr<TYPECHAIR>()
        auto sofa = factory.createSofa();
        auto coffeeTable = factory.createCoffeetable();
        if (chair == nullptr) { // Can check for null
            return;
        }
        if (sofa == nullptr) { // Can check for null
            return;
        }
        if (coffeeTable == nullptr) { // Can check for null
            return;
        }
        chair->haslegs();
        sofa->haslegs();
        coffeeTable->haslegs();
        
        std::cout << "Chair sit: " << chair->sitOn() << std::endl;
        std::cout << "Sofa sit: " << sofa->sitOn() << std::endl;
        std::cout << "Coffee Table sit: " << coffeeTable->sitOn() << std::endl;
    }
};

int main() {
    std::cout << "Modern Furniture:" << std::endl;
    ModernFurnitureFactory modernFurnitureFactory;
    Client client;
    client.createFurniture(modernFurnitureFactory);

    std::cout << "\nVictorian Furniture:" << std::endl;
    VictorianFurnitureFactory victorianFurnitureFactory;
    client.createFurniture(victorianFurnitureFactory);

    return 0;
}