#include<iostream>
using namespace std;
//Polymorphism that is resolved during compile-time is known as static polymorphism.
//COMPILE time polymorphism, Private and sealed methods vcan be overLoaded
// Method overLOADING / operator OverLoading
// Type 1 METHOD OVERLOADING Methods are overloaded when the class has same name method / same operator with different number of arguments/tyoes
class Sum{
    public:
        int addition(int a, int b){
            return a + b;
        }
        //Arguments must be different in the case of overloading.
        int addition(int a, int b, int c){
            return a + b + c;
        }
};
class Area {
  public:
    double calculateArea(double length, double breadth) {
      return length * breadth;
    }
    //Arguments must be different in the case of overloading.
    double calculateArea(double side) {
      return side * side;
    }
};
//TYPE 2 Operator Overloading
class ComplexNumber{
    private:
        int real, imaginary;
    public:
        ComplexNumber(int r = 0, int i = 0) : real(r), imaginary(i){}
        //overloading operator function
        ComplexNumber operator + (ComplexNumber const &complexObj){
            ComplexNumber result;
            result.real = complexObj.real + real;
            result.imaginary = complexObj.imaginary + imaginary;
            return result;
        }
        void display(){
            cout << "(" << real << "+" << imaginary << "i )" << '\n';
        }

};
int main(void) {
  Sum sum;
  cout << sum.addition(14, 35) << endl;
  cout << sum.addition(31, 34, 43) << endl;
  Area area;
  cout << "Area of rectangle = " << area.calculateArea(3, 4) << endl;
  cout << "Area of square = " << area.calculateArea(6) << endl;
  ComplexNumber c1(11,5), c2(2, 6);
  ComplexNumber c3 = c1 + c2;
  c3.display();
  return 0;
}