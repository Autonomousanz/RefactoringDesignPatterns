#include<iostream>
#include<string>
using namespace std;
// Product Interface
class Button{
    public:
      virtual void render() = 0;
      virtual void OnClick(std::string f){
        std::cout << "Bind on click event" << std::endl;
      }
    virtual ~Button() = default;
};

//Concrete products
class WindowsButton : public Button{
    public:
        void render() override{
            std::cout << "render a windows style button" << std::endl;
        }
        void OnClick(string f) override{
            std::cout << "input event is:" << f << std::endl;
        }
        virtual ~WindowsButton() = default;
};
class RoundButtons : public Button{
    public:
        void render() override{
            std::cout << "render a Round style button" << std::endl;
        }
        void OnClick(string f) override{
            std::cout << "input event is:" << f << std::endl;
        }
        virtual ~RoundButtons() = default;
};

class HTMLButton : public Button{
    public:
        void render() override{
            std::cout << "render a Ubuntu style button" << std::endl;
        }
        void OnClick(string f) override{
            std::cout << "input event is:" << f << std::endl;
        }
        virtual ~HTMLButton() = default;
};
// Creator class
class Dialog{
    public:
    // abstract factory method
    virtual Button* createButton() = 0;
    std::string CloseDialog = "Windows";
    virtual ~Dialog() = default;
    // provide common functionality
    void renderButton(){
        Button* okButton = createButton();
        okButton->OnClick(CloseDialog);
        okButton->render();
        delete okButton;
    }
};
// Concrete creator classes
class WindowDialog : public Dialog{
    public:
        Button* createButton() override{
            return new WindowsButton();
        }
};

class HTMLDialog : public Dialog{
    public:
        Button* createButton() override{
            return new HTMLButton();
        }
};
class RoundUIDialog : public Dialog{
    public:
        Button* createButton() override{
            return new RoundButtons();
        }
};

//To add a new product type to the app, you’ll only need to create a new creator subclass and override the factory method in it.
//The client code works with an instance of a concrete creator class
int main(){
    Dialog* dialogObj1 = new WindowDialog();
    Dialog* dialogObject = new HTMLDialog();
    Dialog* roundButtonObj = new RoundUIDialog();
    dialogObject->CloseDialog = "HTML";
    dialogObj1->renderButton();
    dialogObject->renderButton();

    roundButtonObj->renderButton();

    delete dialogObj1;
    delete dialogObject;
    delete roundButtonObj;
    return 0;
}