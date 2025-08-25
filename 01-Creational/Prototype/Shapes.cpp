#include <iostream>
#include <memory>
#include <string>

//All shape classes follow the same interface, which provides a cloning method. 
//A subclass may call the parent’s cloning method before copying its own field values to the resulting object.
// Abstract base class implementing the Prototype pattern
class Shape{
    protected:
        int X;
        int Y;
        std::string color;
    public:
        //Regular constructor
        Shape() : X(0), Y(0), color("") {} //default initialization
        
   // Prototype constructor (copy constructor). A fresh object is initialized with values from the existing object.
        Shape(const Shape& source): X(source.X), Y(source.Y) , color(source.color){}
    
    virtual ~Shape()=default;
    // Pure virtual clone method that must be implemented by derived classes
    virtual Shape* clone() const = 0;

    // Pass by value for small types integers are small (typically 4 bytes)
    void setX(int x){ X = x;} 
    void setY(int y){ Y = y; }
    // Pass by reference for larger types std::string is a relatively large object that contains a pointer and size information
    void setColor(const std::string& c){ color = c; }

    int getX(){ return X;}
    int getY(){ return Y;}
    const std::string& getColor(){ return color;}
};
//All shape classes follow the same interface, which provides a cloning method.
class Rectangle : public Shape{
    private:
        int width;
        int height;
        std::string pattern;
    public:
        Rectangle() : Shape(), width(0), height(0), pattern("solid") {std::cout << "create a rectangle" << std::endl; }
        // copy constructor -  A constructor that initializes an object using another object of the same class
        Rectangle(const Rectangle& source) : Shape(source), width(source.width), height(source.height), pattern(source.pattern)
        {
            std::cout << "create a rectangle copy" << std::endl;
        }
        //A parent constructor call is needed to copy private fields defined in the parent class
        // Clone method
        Shape* clone() const override{
            return new Rectangle(*this); // this is calling second copy constructor with pointer of existing this object.
        }
        // Getters and setters
        void setWidth(int w){ width= w; }
        void setHeight(int h){height = h;}
        void setPattern(const std::string& s) { pattern = s;}

        int getWidth(){return width;}
        int getHeight(){ return height;}
        const std::string& getPattern(){ return pattern;}
};

class Circle: public Shape{
    private:
        int radius;

    public:
        Circle() : Shape(), radius(0) {std::cout << "create a circle" << std::endl; }
        // copy constructor
        Circle(const Circle& source) : Shape(source), radius(source.radius){
            std::cout << "create a Circle copy" << std::endl;}
        //A parent constructor call is needed to copy private fields defined in the parent class
        // Clone method
        Shape* clone() const override{
            return new Circle(*this); // this is calling second copy constructor with pointer of existing this object.
        }
        // Getters and setters
        void setRadius(int r){ radius= r; }
        int getRadius(){return radius;}
};

// Example usage
int main() {
    Rectangle* original = new Rectangle();
    original->setX(10);
    original->setY(20);
    original->setColor("red");
    original->setWidth(50);
    original->setHeight(100);

    // Create a clone of the original rectangle
    Rectangle* clone = static_cast<Rectangle*>(original->clone());//static cast because it returns shape* type 
    // Clean up
    delete original;
    std::cout << "Get clone Properties " << clone->getColor()<< std::endl;
    std::cout << "Get clone Properties " << clone->getWidth()<< std::endl;
    std::cout << "Get clone Properties " << clone->getHeight()<< std::endl;
    std::cout << "Get clone Properties " << clone->getX()<< std::endl;

    Circle* originalCircle = new Circle();
    originalCircle->setRadius(5);
    originalCircle->setColor("azul");

    Circle* clone2 = static_cast<Circle*>(originalCircle->clone());
    std::cout << "Get clone Properties of clone circle " << clone2->getColor()<< std::endl;
    std::cout << "Get clone Properties of clone circle " << clone2->getRadius()<< std::endl;
    delete clone;

    return 0;
}