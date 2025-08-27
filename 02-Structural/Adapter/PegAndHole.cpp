#include <iostream>
#include <cmath>
using namespace std;


class RoundPeg{
    private:
       int radius;
    public:
        RoundPeg(int rad): radius(rad) {} // Fixed: initialize radius with rad
        
        virtual int getRadius(){
            return radius; // Make this virtual for proper polymorphism
        }
        virtual ~RoundPeg(){} // Virtual destructor for proper cleanup

};
//Target Interface: The interface that the client expects
class RoundHole {
    private:
        int r;
    public:
        RoundHole(int radius): r(radius){
            std::cout<< "Round hole" << std::endl;
        }
        int getRadius(){
            return r;
        }
        bool fits(RoundPeg* peg){
            return this->getRadius() >= peg->getRadius();
        }
};
//an incompatible class: SquarePeg 
//Adaptee: The existing class with an incompatible interface
class SquarePeg{
    private:
        int width;
    public:
        SquarePeg(int w) : width(w){}
        int getWidth(){
            return width; // Return the square peg width.
        }

};
// An adapter class lets you fit square pegs into round holes. It extends the RoundPeg class to let the adapter objects act as round pegs.
//Object Adapter: Uses composition (has-a relationship)
class SquarePegAdapter : public RoundPeg{
    private:
    // contains the instance of incompatible class
    SquarePeg* pegMember;

    public:
        SquarePegAdapter(SquarePeg* pegArg): RoundPeg(0), pegMember(pegArg){} // Initialize base class
        int getRadius() override {
            return pegMember->getWidth()* std::sqrt(2)/2; // Make this override for proper inheritance 
        }

};

// client code 
int main(){

    RoundHole* hole = new RoundHole(5);
    RoundPeg* rpeg = new RoundPeg(5);
    std::cout << "Round peg fits in the hole ? :" << hole->fits(rpeg) << std:: endl;

    SquarePeg* speg =  new SquarePeg(5);
    SquarePeg* largespeg = new SquarePeg(10);

    //std::cout << "peg fits in the hole " << hole->fits(speg) << std:: endl;//hole.fits(speg) // this won't compile (incompatible types)
    SquarePegAdapter* small_speg = new SquarePegAdapter(speg);
   // SquarePegAdapter* large_speg = new SquarePegAdapter(largespeg);
    
    std::cout << "small square peg fits in the hole?: " << hole->fits(small_speg) << std:: endl;
    //std::cout << "large square peg fits in the hole?: " << hole->fits(large_speg) << std:: endl;

    delete hole;
    delete rpeg;
    delete speg;
    //delete large_speg;
    delete small_speg;
    delete largespeg;

    return 0;
}