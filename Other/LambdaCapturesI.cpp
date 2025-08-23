#include <iostream>
#include <functional>
#include <string>

int main() {
    std::cout << "=== Lambda Captures Explained ===\n\n";
    
    std::string greeting = "Hello";
    std::string name = "World";
    int count = 42;
    
    std::cout << "Original values:\n";
    std::cout << "  greeting = '" << greeting << "'\n";
    std::cout << "  name = '" << name << "'\n";
    std::cout << "  count = " << count << "\n\n";
    
    // 1. Capture by COPY [variable] - lambda gets its own copy
    std::cout << "1. Capture by COPY [greeting]:\n";
    auto lambda1 = [greeting]() {
        std::cout << "  Inside lambda - greeting = '" << greeting << "'\n";
        // greeting = "Modified";  // ❌ Can't modify - it's const by default
        return greeting;
    };
    
    greeting = "Changed Outside";  // Change original
    std::cout << "  After changing original to 'Changed Outside'\n";
    std::cout << "  Lambda still returns: '" << lambda1() << "'\n";
    std::cout << "  (Lambda has its own copy)\n\n";
    
    // 2. Capture by REFERENCE [&variable] - lambda uses the original
    std::cout << "2. Capture by REFERENCE [&name]:\n";
    auto lambda2 = [&name]() {
        std::cout << "  Inside lambda - name = '" << name << "'\n";
        name = "name modified by Lambda";  // ✅ Can modify the original!
        return name;
    };
    
    std::cout << "  Before calling lambda - name = '" << name << "'\n";
    std::cout << "  Lambda returns: '" << lambda2() << "'\n";
    std::cout << "  After calling lambda - name = '" << name << "'\n";
    std::cout << "  (Lambda modified the original)\n\n";
    
    // 3. Capture by MUTABLE COPY [variable] + mutable
    std::cout << "3. Mutable capture [count] with mutable keyword:\n";
    auto lambda3 = [count]() mutable {
        std::cout << "  Inside lambda - count = " << count << "\n";
        count = 999;  // ✅ Can modify the copy
        std::cout << "  Modified copy to: " << count << "\n";
        return count;
    };
    
    std::cout << "  Original count = " << count << "\n";
    std::cout << "  Lambda returns: " << lambda3() << "\n";
    std::cout << "  Original count still = " << count << "\n";
    std::cout << "  (Only the copy was modified)\n\n";
    
    // 4. Capture multiple variables
    std::cout << "4. Multiple captures [greeting, &name, count]:\n";
    greeting = "Hi";  // Reset for demo
    name = "Alice";
    
    auto lambda4 = [greeting, &name, count](std::string suffix) {
        return greeting + " " + name + " (" + std::to_string(count) + ")" + suffix;
    };
    
    std::cout << "  Result: '" << lambda4("!") << "'\n\n";
    
    // 5. Capture everything by copy [=]
    std::cout << "5. Capture all by copy [=]:\n";
    auto lambda5 = [=]() {
        return greeting + " " + name + " - " + std::to_string(count);
    };
    std::cout << "  Result: '" << lambda5() << "'\n\n";
    
    // 6. Capture everything by reference [&]
    std::cout << "6. Capture all by reference [&]:\n";
    auto lambda6 = [&]() {
        greeting = "Modified";
        name = "Bob";
        count = 100;
        return std::string("All modified!");
    };
    std::cout << "  Before: greeting='" << greeting << "', name='" << name << "', count=" << count << "\n";
    std::cout << "  Lambda returns: '" << lambda6() << "'\n";
    std::cout << "  After: greeting='" << greeting << "', name='" << name << "', count=" << count << "\n";
    
    return 0;
}