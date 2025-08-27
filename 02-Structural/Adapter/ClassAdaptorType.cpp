// =============================================================================
// EXAMPLE : Temperature Sensor Adapter (Class Adapter using multiple inheritance)
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
// class Adapter - interherits from both target and adaptee
class TempAdaptor : public Thermometer, public TempFahrenheit{
    public:
        double getTempCelsius() const override{
            //(F - 32) * 5/9
            double tempF = getTempFarenheit();
            return (tempF - 32) * 5.0/9.0;
        }
        void displayTemp()const override{
            std::cout<< "Temperature :" << getTempCelsius() <<  "°C" << std::endl;
        }
};

int main() {
    std::cout << "=== Adapter Pattern Examples - CLASS Adaptor Multiple Inheritance ===\n" << std::endl;
    TempAdaptor classAdaptor;
    classAdaptor.displayTemp();
    classAdaptor.displayTempFarenheit(); // Can also access original interface

    return 0;
};
