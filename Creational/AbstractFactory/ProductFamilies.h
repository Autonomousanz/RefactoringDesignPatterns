#ifndef PRODUCT_FAMILIES_H
#define PRODUCT_FAMILIES_H

// all chair variants can implement the Chair interface, Sofa Interface and coffeetable interface
//1. Chair, Sofa , Coffeetable are Abstract Products which declare interfaces for a set of distinct but related products which make up a product family.
   
    class Chair{
        public:
        virtual void haslegs() = 0;//pure virtual functions 
        virtual bool sitOn() = 0;
        virtual ~Chair()= default;
    };
    class Sofa{
        public:
        virtual void haslegs()= 0;
        virtual bool sitOn() = 0;
        virtual ~Sofa() = default;
    };
    class CoffeeTable{
        public:
        virtual void haslegs() = 0 ;
        virtual bool sitOn() = 0;
        virtual ~CoffeeTable()= default;
    };

    
// Concrete product classes
    class VictorianChair : public Chair{
        public:
        void haslegs() override;
        bool sitOn() override {return true;};
        ~VictorianChair()= default;
    };
    class ModernChair: public Chair{
        public:
        void haslegs() override;
        bool sitOn() override {return true;};
        ~ModernChair()= default;
    };
    class VictorianSofa : public Sofa{
        public:
        void haslegs() override;
        bool sitOn() override {return true;};
        ~VictorianSofa()= default;
    };
    class ModernSofa: public Sofa{
        public:
        void haslegs() override;
        bool sitOn() override {return true;};
        ~ModernSofa()= default;
    };

    class VictorianCoffeetable : public CoffeeTable{
        public:
        void haslegs() override;
        bool sitOn() override {return false;};
        ~VictorianCoffeetable()= default;
    };
    class ModernCoffeetable: public CoffeeTable{
        public:
        void haslegs() override;
        bool sitOn() override {return false;};
        ~ModernCoffeetable()= default;
    };


#endif