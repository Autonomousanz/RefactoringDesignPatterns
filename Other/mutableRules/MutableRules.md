## mutable: Allows lazy loading in const methods (logical constness)
## The Problem Without mutable
```class ImageProxy : public Image {
private:
    std::unique_ptr<RealImage> realImage_;  // No mutable
    
public:
    std::string getInfo() const {  // const function
        if (!realImage_) {
            // ERROR: Cannot modify realImage_ in const function!
            realImage_ = std::make_unique<RealImage>(filename_);
        }
        return realImage_->getInfo();
    }
};
// CAN modfy now

class ImageProxy : public Image {
private:
    mutable std::unique_ptr<RealImage> realImage_;  // Now mutable
    
public:
    std::string getInfo() const {  // const function
        if (!realImage_) {
            // OK: mutable allows modification even in const function
            realImage_ = std::make_unique<RealImage>(filename_);
        }
        return realImage_->getInfo();
    }
};
```
Why Use mutable Here?
The key concept is logical vs physical constness:
Physical constness: No bits in the object change
Logical constness: The object's observable state doesn't change from the client's perspective
const ImageProxy proxy("photo.jpg");

// From client perspective, these should work on const object:
std::string info = proxy.getInfo();  // Just getting info - should be const
proxy.display();                     // Just displaying - should be const

// But internally, we might need to lazy-load the real image
// This is an implementation detail that doesn't affect logical state

```
class LibraryCatalog {
private:
    mutable std::unordered_map<std::string, BookInfo> cache_;  // Cache is mutable
    
public:
    BookInfo getBookInfo(const std::string& isbn) const {  // const method
        // Check cache first (logical const operation)
        if (cache_.find(isbn) != cache_.end()) {
            return cache_[isbn];
        }
        
        // Cache miss - fetch from database (modifies cache, but logically const)
        BookInfo info = fetchFromDatabase(isbn);
        cache_[isbn] = info;  // OK because cache_ is mutable
        return info;
    }
};
```

From user perspective: Just getting book information (const operation)
Internally: Might need to update cache (physical modification, but logically const)