#include <iostream>
using namespace std;
/*, we only. After that, . This interface is part of encapsulation.

We use the functions to calculate the area and perimeter. 
Users do not need to know the implementation details of the functions. 
*/
class Circle {
  //define data attributes
  double radius;//declaration
  double pi;
  
  public:
  //define constructors
  Circle() {
    radius = 0;//definition
    pi = 3.142;//definition
  }
  Circle(double r) {
    radius = r;
    pi = 3.142;
  }
  
  //define methods
  double area() {
    return pi * radius * radius;
  }
  
  double perimeter() {
    return 2 * pi * radius;
  }
};

int main() {
  Circle circle(5);
  cout << "Area: " << circle.area() << endl;
  cout << "Perimeter: " << circle.perimeter() << endl;
}