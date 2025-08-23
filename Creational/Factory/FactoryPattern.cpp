/* . The structure is as follows : -

1. Product - declares the interface , common to all objects that can be produced by creater class or its subclasses (Transport interface )
2. Creater class - declares factory method that returns new product objects, return type must match PRODUCT interface.  (logistics app)
3. Concrete product - different implementations of  product interface (new Ship(), new Truck())
4. Concrete creators - Override base factory method to replace the type of object formed (Road Logistics and ship logistics )

The factory method helps to decouple this logic from the concrete product classes. It can be abstract or return default base product. It can also return existing objects from
a cache, an object pool, or another source without creating new objects. */

#include<string>
#include<iostream>
using namespace std;

// Step 1 define product interfaces
//The Transport class serves as the abstract product interface, declaring the deliver() method that all concrete products must implement
class Transport {
    public:
     virtual void deliver() = 0; // pure virtual function
     //Using = default instead of an empty body ({}) can be more efficient, as it allows the compiler to generate the most appropriate implementation
     virtual ~Transport() = default; //virtual keyword makes the destructor virtual, allowing proper cleanup of derived classes when deleting through a base class pointer 
};
// step 2 create concrete product classes 
//Truck and Ship classes are concrete implementations of the Transport interface.
class Truck : public Transport{
    public:
        void deliver() override{
            std::cout << "Deliver by land in a box" << std::endl;
        }
};

class Ship : public Transport{
    public:
        void deliver() override{
            std::cout << "Deliver by sea in a box" << std::endl;
        }

};

// Step 3 Create Abstract Creator class
//The Logistics class is the abstract creator class, declaring the factory method createTransport() and
// providing a planDelivery() method that uses the factory method
class Logistics{
    public:
        virtual Transport* createTransport() = 0;
        void planDelivery(){
            Transport* t = createTransport(); // create instance of specific product interface.
            t->deliver();
            delete t;
        }

        virtual ~Logistics() = default;

};
// Step 4- implement 2 concrete creator classes
// RoadLogistics and ShipLogistics are concrete creator classes that override the createTransport() method to return specific product instances.
class RoadLogistics : public Logistics{
    Transport* createTransport() override{
        return new Truck(); // return specific product instances
    }
};

class ShipLogistics : public Logistics{
    Transport* createTransport()override{
        return new Ship(); // return specific product instances
    }
};


int main(){
    Logistics* roadLogisticsObj = new RoadLogistics();
    Logistics* shipLogisticsObj = new ShipLogistics();

    std::cout << "Choosing delivery method Land:" << std::endl;

    roadLogisticsObj->planDelivery();    
    
    std::cout << "Choosing delivery method Sea:" << std::endl;

    shipLogisticsObj->planDelivery();
    
    delete roadLogisticsObj;
    delete shipLogisticsObj; 
    return 0;
}

