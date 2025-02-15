
#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>

using namespace std;

// To reuse existing objects in the factory method pattern, we can implement an object pool or caching mechanism within the factory
// Step 1 define product interfaces
//The Transport class serves as the abstract product interface, declaring the deliver() method that all concrete products must implement
class Transport {
    public:
     virtual void deliver() = 0;
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
class Train : public Transport{
    public:
        void deliver() override{
            std::cout << "Deliver by train in a box" << std::endl;
        }
};
class Ship : public Transport{
    public:
        void deliver() override{
            std::cout << "Deliver by sea in a box" << std::endl;
        }

};

// Step 3 Create Creator class
//The Logistics class is the abstract creator class, declaring the factory method createTransport() and providing a planDelivery() method that uses the factory method
class Logistics{
    public:
        virtual Transport* createTransport() = 0;
        virtual ~Logistics() = default;
        void planDelivery(const std::string& key){
            Transport* t = getOrCreateTransport(key);
            t->deliver();
            delete t;
        }
    private:
        std::unordered_map<std::string, Transport*> TransportPool;

    protected:
    Transport* getOrCreateTransport(const std::string& key) {
        auto it = TransportPool.find(key);
        if (it != TransportPool.end()) {
            return it->second;
        }
        Transport* newTransport = createTransport();
        TransportPool[key] = newTransport;
        return newTransport;
    }

};
// Step 4- implement 2 concrete creator classes
// RoadLogistics and ShipLogistics are concrete creator classes that override the createTransport() method to return specific product instances.
class RoadLogistics : public Logistics{
    Transport* createTransport() override{
        return new Truck();
    }
};

class ShipLogistics : public Logistics{
    Transport* createTransport()override{
        return new Ship();
    }
};


int main(){
    Logistics* roadLogisticsObj = new RoadLogistics();
    Logistics* shipLogisticsObj = new ShipLogistics();

    std::cout << "Choosing delivery method Land:" << std::endl;

    roadLogisticsObj->planDelivery("land");    
    
    std::cout << "Choosing delivery method Sea:" << std::endl;

    shipLogisticsObj->planDelivery("sea");
    
    delete roadLogisticsObj;
    delete shipLogisticsObj; 
    return 0;
}