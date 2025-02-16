Creational patterns provide various object creation mechanisms,
which increase flexibility and reuse of existing code.

1. Factory Method - Factory Method is a creational design pattern that provides an interface for creating objects in a superclass, but allows subclasses to alter the type of objects that will be created.The Factory Method pattern suggests that you replace direct object construction calls (using the new operator) with calls to a special factory method.There’s a slight limitation though: subclasses may return different types of products only if these products have a common base class or interface.The client treats all the products as abstract Transport.You can declare the factory method as abstract to force all subclasses to implement their own versions of the method.

<img src="Creational/media/image.png" alt="Alt Text" width="300" height="200">

<img src="Creational/media/image-6.png" alt="Alt Text" width="300" height="200">

<img src="Creational/media/image-11.png" alt="Alt Text" width="300" height="200">


The factory method in the RoadLogistics class returns truck objects, whereas the factory method in the SeaLogistics class returns ships.

2. Abstract Factory Pattern - Abstract Factory—an interface with a list of creation methods for all products that are part of the product family. (for example, createChair , createSofa and createCoffeeTable ). These methods must return abstract product types represented by the interfaces we extracted previously: Chair , Sofa , CoffeeTable. The client code has to work with both factories and products via their respective abstract interfaces. The Client can work with any concrete factory/product variant, as long as it communicates with their objects via abstract interfaces (VictorianFurnitureFactory and ModernFurnitureFactory)

Use the Abstract Factory when your code needs to work with various families of related products, but you don’t want it to depend on the concrete classes of those products—they might be unknown beforehand or you simply want to allow for future extensibility.Consider implementing the Abstract Factory when you have a class with a set of Factory Methods that blur its primary responsibility.In a well-designed program each class is responsible only for one thing. When a class deals with multiple product types, it may be worth extracting its factory methods into a standalone factory class or a full-blown Abstract Factory implementation.

<img src="Creational/media/image-1.png" alt="Alt Text" width="300" height="200">
<img src="Creational/media/image-10.png" alt="Alt Text" width="300" height="200">
<img src="Creational/media/image-12.png" alt="Alt Text" width="300" height="200">

a. Map out a matrix of distinct product types versus variants of these products.
b. Declare **abstract product interfaces** for all product types. Then make all concrete product classes implement these interfaces.
c. Declare the **abstract factory interface** with a set of creation methods for all abstract products.
d. Implement a set of concrete factory classes, one for each product variant.
e. Create factory initialization code somewhere in the app. It should instantiate one of the concrete factory classes, depending on the application configuration or the current environment.Pass this factory object o all classes that construct products.Scan through the code and find all direct calls to product constructors. Replace them with calls to the appropriate creation method on the factory object.

3. Builder Pattern - Builder is a creational design pattern that lets you construct complex objects step by step. The Builder pattern suggests that you extract the object construction code out of its own class and move it to separate objects called builders.The client code that Patterns / Builder calls the building steps is able to interact with builders using a common interface a separate class called director. The director class defines the order in which to execute the building steps, while the builder provides the implementation for those steps.You can always call the building steps in a specific order  directly from the client code without director as well. The director class completely hides the details of product construction from the client code. The Client must associate one of the builder objects with the director. Usually, it’s done just once, via parameters of the director’s constructor. Then the director uses that builder object for all further construction. However, there’s an alternative approach for when the client passes the builder object to the production method of the director. In this case, you can use a different builder each time you produce something with the director.
 
![alt text](Creational/media/image-2.png)
![alt text](Creational/media/imageb13.png)
![alt text](Creational/media/imageb14.png)

4. Prototype Pattern

The pattern declares a common interface for all objects that support cloning. This interface lets you clone an object without coupling your code to the class of that object.The Prototype Registry provides an easy way to access frequently-used prototypes. It stores a set of re-built objects that are ready to be copied. The simplest prototype registry is a name → prototype hash map.The Prototype interface declares the cloning methods. In most cases, it’s a single clone method. The Concrete Prototype class implements the cloning method. In addition to copying the original object’s data to the clone, this method may also handle some edge cases of the cloning process related to cloning linked objects, untangling recursive dependencies. The Client can produce a copy of any object that follows the prototype interface.

![alt text](Creational/media/image15.png)

![alt text](Creational/media/image-3.png)
![alt text](Creational/media/image16.png)
5. Singleton Pattern

![alt text](Creational/media/image-4.png)
