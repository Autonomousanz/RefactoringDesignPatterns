#include<memory>
#include<iostream>
#include<string>
// The Database class defines the `getInstance` method that lets clients access the same instance of a database connection throughout the program.
class Database{
    // The field for storing the singleton instance should be declared static
    private:
           static Database* instance ;
           //The singleton's constructor should always be private to prevent direct construction calls with the `new` operator.
           // Private constructor
           Database(){
            std::cout << "instance of the constructor, Create database connection here " << std::endl;
           } 
           //The copy constructor and assignment operator are deleted to prevent duplication
           Database(const Database&)=delete;
           Database& operator= (const Database&)=delete;

    public:
    //The static method that controls access to the singleton instance.
        static Database* getInstance(){
            if (instance == nullptr){
                instance = new Database();
            }
            return instance;
        }
        void query(const std::string& sql) {
            // Execute SQL query
            std::cout << "Query SQL :" << sql << std::endl;
        }
        ~Database(){
            std::cout << "close database connection" << std::endl;
        }

};
// Initialize the static member
Database* Database::instance = nullptr;

int main() {
    Database* db = Database::getInstance();
    db->query("SELECT * FROM users");
    Database* bar = Database::getInstance();
    bar->query("SELECT ...");
    std::cout <<  "The constructor was called once hence same object is used twice."<< std::endl;
    return 0;
}
