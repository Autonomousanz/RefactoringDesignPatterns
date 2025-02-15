#include "InterfaceBuilder.h"
#include <memory>


    void Director::constructSportsCar(Builder* builder){
        if (builder == nullptr) { // Can check for null
            return;
        }
        builder->reset(); // can't call non-const member functions on const reference
        builder->setSeats(num);
        builder->setComputer(setSpec); 
        builder->setGPS(setSpecF);
        builder->setEngine("Sports car");

    }

    void Director::constructSUVCar(Builder* builder){
        if (builder == nullptr) { // Can check for null
            return;
        }
        builder->reset();
        builder->setSeats(seats);
        builder->setComputer(setSpec); 
        builder->setGPS(setSpecF);
        builder->setEngine("SUV car");
    }

int main(){

        // Option 1 is not better due to formation of new objects 
        // auto director = new Director();   // Manually allocated
        // Builder* builder = new CarBuilder();

        // director->constructSportsCar(builder); // If an exception occurs here, we leak memory
        // Car mycar = builder->getResult();
        // // deletion of allocated memory
        // delete director; // Must remember to free
        // delete builder;


        std::unique_ptr<Director> director = std::make_unique<Director>();
        std::unique_ptr<Builder> builder = std::make_unique<CarBuilder>();
        std::unique_ptr<Builder> manualbuilder = std::make_unique<ManualBuilder>();
            // Even if exception occurs, memory is automatically freed
            // builder.get() returns the raw Builder* pointer from unique_ptr
        director->constructSportsCar(builder.get());
        // builder.get() returns the raw Builder* pointer from unique_ptr
        director->constructSportsCar(manualbuilder.get());
        // No manual deletion needed - automatically cleaned up
        // Option 1: Using base class getResult with casting
        Car* car = static_cast<Car*>(builder->getResult());
        Manual* manual = static_cast<Manual*>(manualbuilder->getResult());
}
    