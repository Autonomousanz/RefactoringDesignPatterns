#ifndef INTERFACE_BUILDER_H
#define INTERFACE_BUILDER_H
#include<iostream>
using namespace std;
// related products 
class Car{
    public:
        Car(){
            std::cout << "build a car" << std::endl;
        }
};
class Manual{
    public:
        Manual(){
            std::cout << "build a manual" << std::endl;
        }

};
//The builder interface specifies methods for creating the different parts of the product objects.
//Interface is abstract class with atleast 1 pure virtual function

class Builder{
    public:
    virtual ~Builder() = default;  // Virtual destructor for proper cleanup when using polymorphism. This is a good practice to ensure derived class destructors are called correctly.
    virtual void reset() = 0;
    virtual void setSeats(const int& num) = 0;
    virtual void setEngine(const string& type) = 0;
    virtual void setComputer(bool& setspec)=0;
    virtual void setGPS(bool& setspec)=0;
    virtual void* getResult() = 0;  // Returns void* which concrete builders will override

};
//The concrete builder classes follow the builder interface and provide specific implementations of the building steps program may have several variations of builders, each implemented differently.
// Concrete builders are supposed to provide their own methods for retrieving results. 
//after returning the end result to the client, builder instance is expected to be ready to start producing another product.
class CarBuilder: public Builder{
    private:
       Car* car;
    public:
        void reset() override{
            this->car = new Car();
        }
        CarBuilder(){
            this->reset();
        }
        void setSeats(const int& num) override{
            std::cout << "set seats to " << num << std::endl;

        }
        void setEngine(const string& type) override{
            std::cout << "set engine to " <<type << std::endl;
        }
        void setComputer(bool& setspec) override{
             std::cout << "set Computer "<<setspec << std::endl;
        }
        void setGPS(bool& setspec) override{
             std::cout << "set gps " << setspec << std::endl;
        }
        void* getResult() override{
            Car* product = this->car;
            //this->reset();
            return product;
        }
            // Add type-safe getter
        Car* getCarResult() {
            return static_cast<Car*>(getResult());
        }
        ~CarBuilder(){
            delete this->car;
        }
};
class ManualBuilder: public Builder{
    private:
       Manual* manual;

    public:
        void reset() override{
            this->manual = new Manual();
        }
        ManualBuilder(){
            this->reset();
        }
        void setSeats(const int& num) override{
            std::cout << "write seats in manual to " <<num << std::endl;

        }
        void setEngine(const string& type) override{
            std::cout << "write engine type in manual to " <<type << std::endl;
        }
        void setComputer(bool& setspec) override{
             std::cout << "write Computer in manual " << setspec << std::endl;
        }
        void setGPS(bool& setspec) override{
             std::cout << "write gps available " << setspec  << std::endl;
        }
        void* getResult() override{
            Manual* product = this->manual;
            // this->reset();
            return product;
        }
          
        // Add type-safe getter
        Manual* getManualResult() {
            return static_cast<Manual*>(getResult());
        }
        ~ManualBuilder(){
            delete this->manual;
        }

};
//The director is only responsible for executing the building steps in a particular sequence. It's helpful when producing  products according to a specific order or configuration.
// The director class is optional, since the  client can control builders directly
class Director{
    private:
        Builder* builder;
    public:
        Director() : builder(nullptr) {}  // Initialize builder
        const int num = 2;
        const int seats = 4;
        bool setSpec = true;
        bool setSpecF = false;
        // director can construct various products several variations
        void setBuilder(Builder* builderType){
            this->builder = builderType;
        }
        void constructSportsCar(Builder* build);
        void constructSUVCar( Builder* builder);

};

# endif