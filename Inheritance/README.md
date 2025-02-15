## Favor composition over Inheritance

1. ***A subclass can’t reduce the interface of the superclass***. You have to implement all abstract methods of the parent class even if you won’t be using them.
2. ***When overriding methods you need to make sure that the new behavior is compatible with the base one.*** It’s important because objects of the subclass may be passed to any code that expects objects of the superclass and you don’t want that code to break.
3. ***Inheritance breaks encapsulation of the superclass because the internal details of the parent class become available to the subclass.*** OR a superclass is aware of some details of subclasses for the sake of making further extension easier.
4. ***Subclasses are tightly coupled to superclasses.*** Any change in a superclass may break the functionality of subclasses.
5. ***Trying to reuse code through inheritance can lead to creating parallel inheritance hierarchies.***you have to create lots of class combinations, bloating the class hierarchy to a ridiculous size.

Whereas inheritance represents the “is a” relationship between classes (a car is a transport), composition represents the “has a” relationship (a car has an engine).
Aggregation is mild composition - a car has a driver, but he or she may use another car or just walk without the car.

![alt text](image.png)
There’s a lot of duplicate code between subclasses because a subclass can’t extend two classes at the same time.You can solve this problem with composition. One can replace an engine object linked to a car object just by assigning a different engine object to the car.

![alt text](image-1.png)