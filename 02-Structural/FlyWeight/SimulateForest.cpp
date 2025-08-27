#include <iostream>
#include <unordered_map>           
#include <string>
#include <memory>
#include <vector>
//The Flyweight pattern is a structural design pattern that minimizes memory usage by efficiently sharing data among multiple similar objects.
//when you need to create a large number of objects that have some common characteristics.
/*TreeType (Flyweight): Stores shared data (tree name and color) that multiple trees can use
TreeTypeFactory: Ensures flyweights are shared - creates new ones only when needed
Tree (Context): Stores unique data for each tree (x, y position) and holds a reference to the shared flyweight
Forest(Client): Manages many tree objects*/

//FlyWeight class stores intrinsic state(shared data)
class TreeType{
    private:
        std::string name_;
        std::string color_;
    public:
        TreeType(const std::string& name, const std::string& color) : name_(name), color_(color){
            std::cout << "Creating Flyweight: "<< name_<< "(" << color_ << ")" << std::endl;
        }
        // Method that uses both intrinsic and extrinsic state
        void render(int x, int y) const{
            std::cout << name_ << "tree (" << color_ << ") at position (" 
                  << x << ", " << y << ")\n";
        }
};
// Flyweight factory manages and shares flyweight class instances
class TreeTypeFactory{
    private:
        static std::unordered_map<std::string, std::shared_ptr<TreeType>> treeTypes_; // name_color -> TreeType(shared_ptr , same object can be shared)
    public:
        static std::shared_ptr<TreeType> getTreeType(const std::string &name, const std::string &color){
            std::string key = name + " _ " + color;
        
        // return exsiting flyweight object if found
        if (treeTypes_.find(key) != treeTypes_.end()){
            std::cout << "Reusing existing flyweight for " << key << std::endl;
            std::cout << "Address of Tree from MAP BEFORE rendering:\n";
            std::cout << treeTypes_[key] << std::endl;
            return treeTypes_[key];
        }
        // Create new flyweight if not found
        std::cout << "Creating new flyweight for " << key << std::endl;
        treeTypes_[key] = std::make_shared<TreeType>(name, color);
        std::cout << "Address of Tree from MAP BEFORE rendering:\n";
        std::cout << treeTypes_[key] << std::endl;
        return treeTypes_[key];
    }
    static int getFlyweightCount(){
        return treeTypes_.size();
    }
};
// Intialize treeType_
std::unordered_map<std::string, std::shared_ptr<TreeType>> TreeTypeFactory::treeTypes_;
// Context class - stores the extrinsic state (unique data per new object)
class Tree{
    private:
        int x_ , y_;// Extrinsic state - position of this specific tree
        std::shared_ptr<TreeType> treeType_;// Reference to shared flyweight

    public:
        Tree(int x, int y, const std::string &name, const std::string &color){
            x_ = x, y_ = y;
            treeType_  = TreeTypeFactory::getTreeType(name, color);
        }
        // pass extrinsic state to flyweight
        void render() const{
            treeType_->render(x_, y_);
        }
};
// Client Class that uses many objects
class Forest{
    private:
        std::vector<Tree> trees_;
    public:
        void plantTree(int x, int y, const std::string & name, const std::string &color){
            trees_.emplace_back(x,y,name, color);// THIS will create a new Tree object
        }
        void render() const{
            std::cout << "\nRendering forest:\n";
            for (const auto &tree : trees_){
                std::cout << "\nAddress of Tree AFTER rendering:\n";
                std::cout << &tree << std::endl;
                tree.render();
            }
        }
        void showStats() const {
            std::cout << "\nForest Statistics:\n";
            std::cout << "Total trees: " << trees_.size() << "\n";
            std::cout << "Flyweight objects created: " << TreeTypeFactory::getFlyweightCount() << "\n";
        }
};

int main() {
    Forest forest;
    
    // Plant many trees - notice how flyweights are reused
    forest.plantTree(10, 20, "Oak", "Green");
    forest.plantTree(30, 40, "Pine", "Green");
    forest.plantTree(50, 60, "Oak", "Green");    // Reuses Oak-Green flyweight factory
    forest.plantTree(70, 80, "Pine", "Green");   // Reuses Pine-Green flyweight factory
    forest.plantTree(90, 100, "Oak", "Brown");   // Creates new Oak-Brown flyweight 
    forest.plantTree(110, 120, "Oak", "Green");  // Reuses Oak-Green flyweight again
    
    forest.render();
    forest.showStats();
    
    return 0;
}
