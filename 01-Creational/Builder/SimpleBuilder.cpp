#include<iostream>
#include<string>
#include<memory>

using namespace std;
//Product class
class Computer{
    private:    
        string cpu, gpu;
        int ram, storage;
    public:
        //setters
        void setCpu(const std::string &cpu) { this->cpu = cpu;};
        void setGpu(const std::string &gpu) { this->gpu = gpu;};
        void setRam(const int &RAM) { this->ram = RAM;};
        void setStorage(const int &storage) { this->storage = storage;};

    void display() const {
        std::cout << "Computer Specs:\n";
        std::cout << "CPU: " << cpu << "\n";
        std::cout << "GPU: " << gpu << "\n";
        std::cout << "RAM: " << ram << "GB\n";
        std::cout << "Storage: " << storage << "GB\n\n";
    }
};
// Builder class
class ComputerBuilder{
    private:
        std::unique_ptr<Computer> comp;
    public:
        ComputerBuilder(){
            comp = std::make_unique<Computer>();
        }
        ComputerBuilder& setCpu(const std::string &cpu){
            comp->setCpu(cpu);
            return *this;
        }
        ComputerBuilder& setGpu(const std::string &gpu){
            comp->setGpu(gpu);
            return *this;
        }
        ComputerBuilder& setRam(const int &Ram){
            comp->setRam(Ram);
            return *this;
        }
        ComputerBuilder& setStorage(const int &storage){
            comp->setStorage(storage);
            return *this;
        }
        std::unique_ptr<Computer> build(){
            return std::move(comp);
        }
};      
//Method chaining is a programming technique 
//where you call multiple methods on the same object in a single statement by linking them together with dots.
int main(){
    auto gamingComp = ComputerBuilder().setCpu("Intel-i9").setGpu("NVIDIA RTX 4090").setRam(300).setStorage(2).build();
    gamingComp->display();
    auto workComp = ComputerBuilder().setCpu("Intel-i5").setRam(200).setStorage(1).build();
    workComp->display();
    return 0;
}