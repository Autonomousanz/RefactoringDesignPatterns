// =============================================================================
// EXAMPLE : Temperature Sensor Adapter (Object Adaptor using Target Interface)
// =============================================================================
#include<iostream>
#include<memory>
// Target Interface - expects celsius
class Thermometer{
    public:
        virtual ~Thermometer() = default;
        virtual double getTempCelsius() const = 0;
        virtual void displayTemp() const = 0;
};
// Adapteee - legacy sensor reports in Fahrenheit
class TempFahrenheit{
    public:
        double getTempFarenheit() const{
            return 98.6;
        }
        void displayTempFarenheit() const{
            std::cout<< "Fahrenheit reading : " << getTempFarenheit() << "°F" << std::endl;
        }
};
// Object Adapter - interherits only target and has object of incompatible adaptee (composition)
class TempAdaptor : public Thermometer{
    private:
        std::unique_ptr<TempFahrenheit> sensor;
    public:
        TempAdaptor(){
            sensor = std::make_unique<TempFahrenheit>(); // initialize
        }
        double getTempCelsius() const override{
            //(F - 32) * 5/9
            double tempF = sensor->getTempFarenheit();
            return (tempF - 32) * 5.0/9.0;
        }
        void displayTemp()const override{
            std::cout<< "Temperature :" << getTempCelsius() <<  "°C" << std::endl;
        }
};

int main() {
    std::cout << "=== Adapter Pattern Examples - OBJECT Adaptor TARGET Inheritance ===\n" << std::endl;
    TempAdaptor classAdaptor;
    classAdaptor.displayTemp();
    //classAdaptor.displayTempFarenheit(); // CanNOT also access original interface

    return 0;
};
