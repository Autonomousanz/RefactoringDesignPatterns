#include <iostream>
#include<string>
using namespace std;
// Parent class
class Vehicle{
    private:
        string name;
        string model;
    public:
        Vehicle(string name, string model) : name(name), model(model) {}
        void getName(){
            cout << "Name of car is " << this->name << " model of the car is " << this->model;
        }
        virtual int getYear() const {
            return 2025; // jsut default vlaue;
        }
         // Virtual destructor for proper cleanup
        virtual ~Vehicle() = default;
};
// single Inheritance
// Derived child class
class FuelCar : public virtual Vehicle{
    private:
        string combustType;
    public:
        FuelCar(string name, string model, string comtype): Vehicle(name, model){
            this->combustType = comtype;
        }
        int getYear() const override{
            return 2001; // method overriding same return type and name (Dynamic Polymorphism)
        }
        void getFuelCar(){
            Vehicle::getName();
            cout << " Fuel car combust type is " << this->combustType << endl;
            cout << ", Year of this fuelcar is " << this->getYear() << endl;
        }
        string getcombustType(){
            return this->combustType; // getters
        }
        void setcombustType(string combustType){
            this->combustType = combustType; //setter for private variables
        }
};
// Heirarchical inheritance
// Alongside the FuelCar class, the ElectricCar class is also extending from Vehicle class
// Another Derived class (Child) 2 child single parent
class ElectricCar : public virtual Vehicle{
    private:
        string batteryPower;
    public:
        ElectricCar(string name, string model, string batteryPow):Vehicle(name, model){
            this->batteryPower = batteryPow;
        }
        int getYear() const override{
            return 2026; // method overriding same return type and name (Dynamic Polymorphism)
        }
        void getElectricCar(){
            Vehicle::getName();
            cout << "Battery power of Electric vehicle is " << this->batteryPower << endl;
            cout << " ,year of the car" << this->getYear() << endl;
        }
        string getBatteryPow(){
            return this->batteryPower; // getters
        }
        void setBatteryPow(string batteryPow){
            this->batteryPower = batteryPow; //setters
        }
};
// Multi level inheritance
// inheriting from a class that inherits from another class
// Derived class (GRANDCHILD)
class GasolineCar : public FuelCar{
    private:
        string gasCapacity;
    public:
        GasolineCar(string name, string model, string gasCap, string combustType) : Vehicle(name, model), FuelCar(name, model,combustType){
            this->gasCapacity = gasCap;
        }
        void getGasolineCar(){
            FuelCar::getFuelCar();
            cout << "Gas capacity of the car is " << this->gasCapacity << endl;
        }
        // IT IS NOT MANDATORY TO implement virtual method getYear from base class, only PURE virtuals are mandatory
};
// Multiple class Inheritance
// Derived class
/*Diamond Problem: Your HybridCar class inherits from both GasolineCar and ElectricCar, which both inherit from Vehicle. 
This creates the diamond problem - HybridCar has two copies of Vehicle. Consider using virtual inheritance:
This ensures only one copy of Vehicle exists in HybridCar*/
class HybridCar : public GasolineCar, public ElectricCar{
    private:
        string batteryPower;
        string gasCap;
    public:
        HybridCar(string name, string model, string batteryPow, string gasCapacity, string combustType): Vehicle(name, model),
         GasolineCar(name, model,gasCapacity,combustType), ElectricCar(name, model, batteryPow){
            this->batteryPower = batteryPow;
            this->gasCap = gasCapacity;
        }
        // Override getYear to resolve ambiguity
        int getYear() const override {
            return 2024; // Hybrid cars are modern
        }
        void getHybrid(){
            FuelCar::getFuelCar();
            cout << "Hybrid car battery pow is " << this->batteryPower << std::endl;
        }

};
int main(){
    cout << "Single Inheritance " << endl;
    FuelCar fuelcar("Honda", "Accord", "Petrol");
    fuelcar.getFuelCar();
    cout << endl << " " << endl;

    cout << "Hierarchical Inheritance" <<endl;
    ElectricCar electric("Tesla", "ModelX", "200 kWh");
    electric.getElectricCar();
    cout << endl << " " << endl;

    cout << "Multi-Level Inheritance" <<endl;
    GasolineCar gasCar("Honda", "Civic", "Petrol", "30 litres");
    gasCar.getGasolineCar();
    cout << endl << " " << endl;

    cout << "Multiple Inheritance " << endl;
    HybridCar myhybrid("Toyota", "Venza", "900 Wh", "14.5 gallons", "hybrid");
    myhybrid.getHybrid();
    cout << endl << " " << endl;
    
    cout << "=== Polymorphism Demonstration ===" << endl;
    Vehicle* vehicles[] = {
        new FuelCar("BMW", "X5", "Diesel"),
        new ElectricCar("Nissan", "Leaf", "40 kWh"),
        new GasolineCar("Ford", "Mustang", "60 litres", "Gasoline")
    };
    
    for (int i = 0; i < 3; i++) {
        vehicles[i]->getName();
        cout << ", Year: " << vehicles[i]->getYear() << endl;
        delete vehicles[i]; // Clean up memory
    }
}
