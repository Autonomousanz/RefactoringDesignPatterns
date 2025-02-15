#ifndef ABSTRACTFACTORYPATTERN_H
#define ABSTRACTFACTORYPATTERN_H
#include "ProductFamilies.h"
#include <memory>
#include<iostream>
using namespace std;
//3. The Abstract Factory interface declares a set of methods for creating each of the abstract products.an interface with a list of creation methods for all products that are part of the product family
class FurnitureFactory{ // Abstract class
    public:
    virtual std::unique_ptr<Chair> createChair() const = 0; // pure virtual functions
    virtual std::unique_ptr<Sofa> createSofa() const = 0;
    virtual std::unique_ptr<CoffeeTable> createCoffeetable() const = 0;

};
//4. Concrete Factories implement creation methods of the abstract factory. Each concrete factory corresponds to a specific variant of products and creates only those product variants
class VictorianFurnitureFactory : public FurnitureFactory{
    public:
   // VictorianFurnitureFactory(){};// explicit default constructor
    std::unique_ptr<Chair> createChair() const override;
    std::unique_ptr<Sofa> createSofa() const override;
    std::unique_ptr<CoffeeTable> createCoffeetable() const override;
   // ~VictorianFurnitureFactory(){};
};

class ModernFurnitureFactory : public FurnitureFactory{
    public:
   // ModernFurnitureFactory(){};
    std::unique_ptr<Chair> createChair() const override;
    std::unique_ptr<Sofa> createSofa() const override;
    std::unique_ptr<CoffeeTable> createCoffeetable() const override;
    //~ModernFurnitureFactory(){};
};
// The client code has to work with both factories and products via their respective abstract interfaces. 
//The client doesn’t have to be aware of the factory’s class, nor does it matter what kind of chair it gets.
//concrete factories instantiate concrete products, signatures of their creation methods must return corresponding abstract products. This way the client code that uses a factory
//doesn’t get coupled to the specific variant of the product it gets from a factory
// Client code

#endif