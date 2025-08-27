#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <thread>
// Caching Proxy example
class WebService {
public:
    virtual ~WebService() = default;
    virtual std::string getData(const std::string& url) = 0;
};

class RealWebService : public WebService {
public:
    std::string getData(const std::string& url) override {
        std::cout << "Fetching data from: " << url << std::endl;
        // Simulate network delay
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        return "Data from " + url;
    }
};

class CachingWebServiceProxy : public WebService {
private:
    std::unique_ptr<RealWebService> realService_;
    mutable std::unordered_map<std::string, std::string> cache_;

public:
    CachingWebServiceProxy() : realService_(std::make_unique<RealWebService>()) {}

    std::string getData(const std::string& url) override {
        // Check cache first
        auto it = cache_.find(url);
        if (it != cache_.end()) {
            std::cout << "Cache hit for: " << url << std::endl;
            return it->second;
        }

        // Cache miss - fetch from real service
        std::cout << "Cache miss for: " << url << std::endl;
        std::string data = realService_->getData(url);
        cache_[url] = data;  // Store in cache
        return data;
    }

    void clearCache() {
        cache_.clear();
        std::cout << "Cache cleared" << std::endl;
    }

    size_t getCacheSize() const {
        return cache_.size();
    }
};


int main(){
     // 3. Caching Proxy
    std::cout << "\n\n3. Caching Proxy Example:" << std::endl;
    
    CachingWebServiceProxy webProxy;
    
    std::cout << "\nFirst request to API:" << std::endl;
    std::string data1 = webProxy.getData("https://api.example.com/users");
    std::cout << "Received: " << data1 << std::endl;
    
    std::cout << "\nSecond request to same URL (should be cached):" << std::endl;
    std::string data2 = webProxy.getData("https://api.example.com/users");
    std::cout << "Received: " << data2 << std::endl;
    
    std::cout << "\nRequest to different URL:" << std::endl;
    std::string data3 = webProxy.getData("https://api.example.com/posts");
    std::cout << "Received: " << data3 << std::endl;
    
    std::cout << "\nCache size: " << webProxy.getCacheSize() << std::endl;

    std::cout << "\n=== Proxy Pattern Benefits ===" << std::endl;
    std::cout << "- Lazy Loading: Objects created only when needed" << std::endl;
    std::cout << "- Access Control: Fine-grained permissions" << std::endl;
    std::cout << "- Caching: Improved performance through data reuse" << std::endl;
    std::cout << "- Transparency: Client uses same interface" << std::endl;

    return 0;
}