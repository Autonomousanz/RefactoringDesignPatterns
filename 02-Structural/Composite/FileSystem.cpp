#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include<algorithm>
// Component - Abstract base class
class FileSystemComponent {
public:
    virtual ~FileSystemComponent() = default;
    virtual void display(int depth = 0) const = 0;
    virtual int getSize() const = 0;
    virtual std::string getName() const = 0;
    
    // Optional: Add/Remove operations (only meaningful for composites)
    virtual void add(std::shared_ptr<FileSystemComponent> component) {
        throw std::runtime_error("Operation not supported");
    }
    
    virtual void remove(std::shared_ptr<FileSystemComponent> component) {
        throw std::runtime_error("Operation not supported");
    }
};

// Leaf - File
class File : public FileSystemComponent {
private:
    std::string name;
    int size;
    
public:
    File(const std::string& name, int size) : name(name), size(size) {}
    
    void display(int depth = 0) const override {
        std::string indent(depth * 2, ' ');
        std::cout << indent << "File: " << name << " (" << size << " bytes)" << std::endl;
    }
    
    int getSize() const override {
        return size;
    }
    
    std::string getName() const override {
        return name;
    }
};

// Composite - Directory
class Directory : public FileSystemComponent {
private:
    std::string name;
    //std::vector<std::shared_ptr<FileSystemComponent>> instead of std::vector<FileSystemComponent> -
    // we need reference semantics to support polymorphism and avoid object slicing!
    std::vector<std::shared_ptr<FileSystemComponent>> children;
    
public:
    Directory(const std::string& name) : name(name) {}
    
    void display(int depth = 0) const override {
        std::string indent(depth * 2, ' ');
        std::cout << indent << "Directory: " << name << " (" << getSize() << " bytes total)" << std::endl;
        
        // Display all children
        for (const auto& child : children) {
            child->display(depth + 1);
        }
    }
    
    int getSize() const override {
        int totalSize = 0;
        for (const auto& child : children) {
            totalSize += child->getSize();
        }
        return totalSize;
    }
    
    std::string getName() const override {
        return name;
    }
    
    void add(std::shared_ptr<FileSystemComponent> component) override {
        children.push_back(component);
    }
    
    void remove(std::shared_ptr<FileSystemComponent> component) override {
        auto it = std::find(children.begin(), children.end(), component);
        if (it != children.end()) {
            children.erase(it);
        }
    }
    
    // Additional utility method
    std::vector<std::shared_ptr<FileSystemComponent>> getChildren() const {
        return children;
    }
};

// Client code demonstrating usage
int main() {
    // Create files (leaves)
    auto file1 = std::make_shared<File>("document.txt", 1024);
    auto file2 = std::make_shared<File>("photo.jpg", 2048);
    auto file3 = std::make_shared<File>("config.xml", 512);
    auto file4 = std::make_shared<File>("readme.md", 256);
    
    // Create directories (composites)
    auto rootDir = std::make_shared<Directory>("root");
    auto documentsDir = std::make_shared<Directory>("documents");
    auto imagesDir = std::make_shared<Directory>("images");
    
    // Build the tree structure add Directory Obj to Directory
    rootDir->add(documentsDir);
    rootDir->add(imagesDir);
    rootDir->add(file4);  // readme in root
    // Add File type object to Directory
    documentsDir->add(file1);
    documentsDir->add(file3);
    // Add File type object to Directory
    imagesDir->add(file2);
    
    // Display the entire tree
    std::cout << "File System Structure:" << std::endl;
    std::cout << "======================" << std::endl;
    rootDir->display();
    
    std::cout << std::endl;
    
    // Demonstrate uniform treatment
    std::cout << "Individual Component Sizes:" << std::endl;
    std::cout << "===========================" << std::endl;
    std::cout << "Root directory total: " << rootDir->getSize() << " bytes" << std::endl;
    std::cout << "Documents directory: " << documentsDir->getSize() << " bytes" << std::endl;
    std::cout << "Single file (photo.jpg): " << file2->getSize() << " bytes" << std::endl;
    
    std::cout << std::endl;
    
    // Demonstrate adding/removing
    std::cout << "Adding a new file to images directory..." << std::endl;
    auto newFile = std::make_shared<File>("thumbnail.png", 128);
    imagesDir->add(newFile);
    
    std::cout << "Updated structure:" << std::endl;
    rootDir->display();
    
    std::cout << "Removing an existing file.. " << std::endl;
    imagesDir->remove(newFile);
    std::cout << "Updated structure: " << std::endl;
    imagesDir->display();
    return 0;
}

