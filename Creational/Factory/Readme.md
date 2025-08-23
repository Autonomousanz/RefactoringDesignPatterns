## Factory design pattern 

The Factory pattern is a creational pattern that provides a template that can be used to create objects. 
It is used in complex situations where the type of the object required varies and needs to be specified in each case.

It provides an INTERFACE for creating objects in a superclass but allows subclasses to alter the type of the objects that will be created switch objects behavior based on classes being called. 
* It does not use the new keyword directly to instantiate objects.
* It does not explicitly require the use of a constructor to create objects. Instead, it provides a generic interface that delegates the object creation responsibility to the corresponding subclass.