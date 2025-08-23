#include <iostream>
using namespace std;

class Singleton {
    private:
        static Singleton* commonInstance;// declaration
        static string f;
        Singleton(string f){
            std::cout << "Constructor call" << std::endl;
        }
        // delete copy constructor and assignment operator
        Singleton(const Singleton& obj2)= delete;
        Singleton& operator=(const Singleton &obj2)=delete;
    public:
        static Singleton* getSingletonInstance(){
            if (commonInstance == nullptr){
                commonInstance = new Singleton("default");
                std::cout << "Creating instance" << std::endl;
            }
            return commonInstance;
        }
        void someMethod(const std::string& f) {
            // Execute SQL query
            std::cout << "Output :" << f << std::endl;
        }
        ~Singleton(){
            delete commonInstance;
        }
};
Singleton* Singleton::commonInstance = nullptr;//definition
int main(){
    Singleton* object = Singleton::getSingletonInstance();
    string temp = "sanskruti";
    object->someMethod(temp);
    Singleton* object2 = Singleton::getSingletonInstance();
    temp = "type2";
    object2->someMethod(temp);
    Singleton* object3 = Singleton::getSingletonInstance();
    object3->someMethod(temp);
    return 0;
}