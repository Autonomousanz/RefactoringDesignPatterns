#include<iostream>
#include<memory>
#include<string>
#include<vector>

// Implementor interface for shapes (Bridge Interface)
// This defines the interface for the implementation heirarcy
class DrawingAPI {
    public:
        virtual ~DrawingAPI() = default;
        virtual void drawCircle(double x, double y, double radius) = 0;
        virtual void drawRectangle(double x, double y, double width, double height) = 0;
        virtual void drawLine(double x1, double y1, double x2, double y2) = 0;
        virtual std::string getAPIName()const = 0;
};     
// concrete implementations
class OpenGLAPI : public DrawingAPI{
    public:
        void drawLine(double x1, double y1, double x2, double y2) override{
             std::cout << "OpenGL: Drawing line from (" << x1 << "," << y1 
                  << ") to (" << x2 << "," << y2 << ")" << std::endl;
        }
        void drawCircle(double x, double y, double radius) override {
        std::cout << "OpenGL: Drawing circle at (" << x << "," << y 
                  << ") with radius " << radius << std::endl;
        }
    
        void drawRectangle(double x, double y, double width, double height) override {
            std::cout << "OpenGL: Drawing rectangle at (" << x << "," << y 
                    << ") size " << width << "x" << height << std::endl;
        }
    
        std::string getAPIName() const override {
            return "OpenGL";
        }
};
class SVGDrawingAPI : public DrawingAPI {
public:
    void drawLine(double x1, double y1, double x2, double y2) override {
        std::cout << "SVG: <line x1=\"" << x1 << "\" y1=\"" << y1 
                  << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\"/>" << std::endl;
    }
    
    void drawCircle(double x, double y, double radius) override {
        std::cout << "SVG: <circle cx=\"" << x << "\" cy=\"" << y 
                  << "\" r=\"" << radius << "\"/>" << std::endl;
    }
    
    void drawRectangle(double x, double y, double width, double height) override {
        std::cout << "SVG: <rect x=\"" << x << "\" y=\"" << y 
                  << "\" width=\"" << width << "\" height=\"" << height << "\"/>" << std::endl;
    }
    
    std::string getAPIName() const override {
        return "SVG";
    }
};
// Abstraction base class
// This defines the interface that clients use
class Shape{
    protected:
        std::shared_ptr<DrawingAPI> drawApi;
        double x, y;
    public:
        Shape(std::shared_ptr<DrawingAPI> api, double x = 0, double y = 0) :
            drawApi(api), x(x), y(y){}
        virtual ~Shape() = default;
        virtual void draw() = 0;
        virtual void resize(double factor) = 0;
        // Can change implementation at runtime
        void setDrawAPI(std::shared_ptr<DrawingAPI> api){
            drawApi = api;
        }
        std::string getDrawAPIName() const{
            return drawApi->getAPIName();
        }
};
// Refined Abstractions - Specific shapes
class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(std::shared_ptr<DrawingAPI> api, double x, double y, double radius)
        : Shape(api, x, y), radius(radius) {}
    
    void draw() override {
        std::cout << "Circle: ";
        drawApi->drawCircle(x, y, radius);
    }
    
    void resize(double factor) override {
        radius *= factor;
        std::cout << "Circle resized by factor " << factor 
                  << ", new radius: " << radius << std::endl;
    }
    
    double getRadius() const { return radius; }
};

class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(std::shared_ptr<DrawingAPI> api, double x, double y, double width, double height)
        : Shape(api, x, y), width(width), height(height) {}
    
    void draw() override {
        std::cout << "Rectangle: ";
        drawApi->drawRectangle(x, y, width, height);
    }
    
    void resize(double factor) override {
        width *= factor;
        height *= factor;
        std::cout << "Rectangle resized by factor " << factor 
                  << ", new size: " << width << "x" << height << std::endl;
    }
};

class Line : public Shape {
private:
    double x2, y2;
    
public:
    Line(std::shared_ptr<DrawingAPI> api, double x1, double y1, double x2, double y2)
        : Shape(api, x1, y1), x2(x2), y2(y2) {}
    
    void draw() override {
        std::cout << "Line: ";
        drawApi->drawLine(x, y, x2, y2);
    }
    
    void resize(double factor) override {
        // Scale the line by moving the end point
        x2 = x + (x2 - x) * factor;
        y2 = y + (y2 - y) * factor;
        std::cout << "Line resized by factor " << factor << std::endl;
    }
};
int main(){
     std::cout << "=== Shape Drawing Bridge Pattern Demo ===\n" << std::endl;
    
    // Create different drawing APIs
    auto openGL = std::make_shared<OpenGLAPI>();
    auto svg = std::make_shared<SVGDrawingAPI>();
    
    // Create shapes with different implementations
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(openGL, 10, 10, 5));
    shapes.push_back(std::make_unique<Line>(svg, 0, 0, 10, 10));
    
    // Draw all shapes
    std::cout << "Drawing shapes with their original APIs:" << std::endl;
    for (auto& shape : shapes) {
        shape->draw();
    }
    
    std::cout << "\nChanging all shapes to use SVG API:" << std::endl;
    for (auto& shape : shapes) {
        shape->setDrawAPI(svg);// runtime change
        shape->draw();
    }
    
    std::cout << "\nResizing shapes:" << std::endl;
    for (auto& shape : shapes) {
        shape->resize(1.5);
    }
    
    std::cout << "\nDrawing resized shapes:" << std::endl;
    for (auto& shape : shapes) {
        shape->draw();
    }
    return 0;
}