#include<iostream>
using namespace std;
#include "ProductFamilies.h"


// 2. Concrete Products are various implementations of abstract products, grouped by variants. Each abstract product (chair/sofa) must be implemented in all given variants (Victorian/Modern).
// Concrete product implementations
void VictorianChair::haslegs() { 
    std::cout << "Victorian Chair" << std::endl; 
}

void ModernChair::haslegs() { 
    std::cout << "Modern Chair" << std::endl; 
}

void VictorianSofa::haslegs() { 
    std::cout << "Victorian Sofa" << std::endl; 
}

void ModernSofa::haslegs() { 
    std::cout << "Modern Sofa" << std::endl; 
}

void VictorianCoffeetable::haslegs() { 
    std::cout << "Victorian Coffeetable" << std::endl; 
}

void ModernCoffeetable::haslegs() { 
    std::cout << "Modern Coffeetable" << std::endl; 
}
