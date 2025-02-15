1. Why maintain single instance of the class?
The reason for this is to control access to some shared resource—for example, a database or a file.
2. How to implement
Make the default constructor private, to prevent other objects from using the new operator with the Singleton class. The Singleton class declares the static method getInstance that returns the same instance of its own class.

Violates the Single Responsibility Principle. The pattern solves two problems at the time
The Singleton pattern can mask bad design, for instance, when the components of the program know too much about each other.
The pattern requires special treatment in a multithreaded  environment so that multiple threads won’t create a singleton object several times