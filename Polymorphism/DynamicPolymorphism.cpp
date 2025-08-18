#include<iostream>
using namespace std;

//RUNTIME POLYMORPHISM - method overRiding parent class's implem, Private and sealed methods cannot be overridden.
//Gives worse performance because the binding is being done at runtime.
class Animal{
    public:
    //Arguments must be the same in the case of overriding. Return type of the method must be the same.
        virtual void printAnimal(){
            cout << "I am from the Animal class" << endl;
        }
        void printAnimal2(){
            cout << "I am non virtual method from Animal class"<< endl;
        }
};
class Lion : public Animal{
    public:
        void printAnimal(){
            // METHOD overriding;
            cout << "I am from the Lion class" << endl;
        }
};
int main(){
    Animal* animal;
    Lion lion;
    animal = &lion;
    animal->printAnimal2();
    animal->printAnimal();// method overriden
    return 0;
}