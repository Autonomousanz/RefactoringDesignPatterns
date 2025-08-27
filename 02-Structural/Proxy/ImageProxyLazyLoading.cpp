#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <thread>
//subject interface defines common operations
//Defines the common interface that both Real Subject and Proxy implement
class Image{
    public: 
        virtual ~Image() = default;
        virtual void display() = 0;
        virtual void load() = 0;
        virtual std::string getInfo() const = 0;
};
// real subject; the actual heavy object
class RealImage : public Image{
    private:
        std::string fileName_;
        std::string imageData_;
        bool isLoaded_;
    public:
        explicit RealImage(const std::string &filename): Image(), fileName_(filename), isLoaded_(false){
            std::cout << "Real image created for : " << fileName_ << std::endl;
        }
        void load() override{
            if (!isLoaded_){
                std::cout << "Loading image from Disk : " << fileName_ << std::endl;
                // Simulate Expensive loading operation
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                imageData_ = "Binary Data for : " + fileName_;
                isLoaded_ = true;
                std::cout << "Image loaded successfully: " << fileName_ << std::endl;
            }
        }
        void display() override{
            if (!isLoaded_){
                load();
            }
            std::cout << "Displaying image: " << fileName_ << " [" << imageData_ << "]" << std::endl;
        }
        std::string getInfo() const override{
            return "Realimage : " + fileName_ + "(Loaded Image : " + (isLoaded_? "Yes" : "No") + ")";
        }

};

// Virtual Proxy - controls access and lazy loading
class ImageProxy : public Image {
private:
    std::string filename_;
    //mutable: Allows lazy loading in const methods (logical constness)
    mutable std::unique_ptr<RealImage> realImage_;  // mutable for lazy loading in const methods
    RealImage* getRealImage() const {
        if (!realImage_) {
            std::cout << "Proxy: Creating real image on demand..." << std::endl;
            realImage_ = std::make_unique<RealImage>(filename_);
        }
        std::cout << "Proxy: Real image address, it will return the same heavy object and create only once " << &realImage_ << std::endl;
        return realImage_.get();
    }
public:
    explicit ImageProxy(const std::string& filename) : filename_(filename) {
        std::cout << "ImageProxy created for: " << filename_ << std::endl;
    }

    void load() override {
        getRealImage()->load();
    }

    void display() override {
        std::cout << "Proxy: Delegating display request..." << std::endl;
        getRealImage()->display();
    }

    std::string getInfo() const override {
        if (realImage_) {
            return "Proxy now loaded -> " + realImage_->getInfo();
        }
        return "Proxy: " + filename_ + " (Not loaded yet)";
    }
   
};

int main() {
    std::cout << "=== Proxy Pattern Examples ===" << std::endl;

    // 1. Virtual Proxy - Lazy Loading
    std::cout << "\n1. Virtual Proxy (Lazy Loading) Example:" << std::endl;
    
    std::vector<std::unique_ptr<Image>> images;
    images.push_back(std::make_unique<ImageProxy>("photo1.jpg"));
    images.push_back(std::make_unique<ImageProxy>("photo2.jpg"));
    images.push_back(std::make_unique<ImageProxy>("photo3.jpg"));
    
    std::cout << "\nImages created (but not loaded yet):" << std::endl;
    for (const auto& img : images) {
        std::cout << img->getInfo() << std::endl;
    }
    //ImageProxy only creates/loads the RealImage when display() is called
    std::cout << "\nDisplaying first image (will trigger loading):" << std::endl;  
    images[0]->display();
    //ImageProxy only creates/loads the RealImage when display() is called
    std::cout << "\nDisplaying first image again (already loaded):" << std::endl;
    images[0]->display();
    return 0;
}
