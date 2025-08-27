#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>

// Protection Proxy example - controls access based on permissions
enum class UserRole { GUEST, USER, ADMIN };
//subject interface defines common operations,
// Defines the common interface that both Real Subject and Proxy implement
class SecureDocument {
public:
    virtual ~SecureDocument() = default;
    virtual void read() = 0;
    virtual void write(const std::string& content) = 0;
    virtual void deleteDoc() = 0;
};
// real subject; the actual heavy object
class RealDocument : public SecureDocument {
private:
    std::string filename_;
    std::string content_;

public:
    explicit RealDocument(const std::string& filename) 
        : filename_(filename), content_("Original content of " + filename) {
        std::cout << "RealDocument created: " << filename_ << std::endl;
    }

    void read() override {
        std::cout << "Reading document: " << filename_ << std::endl;
        std::cout << "Content: " << content_ << std::endl;
    }

    void write(const std::string& content) override {
        std::cout << "Writing to document: " << filename_ << std::endl;
        content_ = content;
        std::cout << "Content updated successfully" << std::endl;
    }

    void deleteDoc() override {
        std::cout << "Deleting document: " << filename_ << std::endl;
        content_.clear();
    }
};
// Virtual Proxy - controls access and permissions
//Controls access to the Real Subject and can add additional behavior
class DocumentProxy : public SecureDocument {
private:
    std::unique_ptr<RealDocument> realDocument_;
    std::string filename_;
    UserRole userRole_;
    RealDocument* getRealDocument() {
        if (!realDocument_) {
            realDocument_ = std::make_unique<RealDocument>(filename_);
        }
        return realDocument_.get();
    }

    std::string roleToString(UserRole role) const {
        switch (role) {
            case UserRole::GUEST: return "GUEST";
            case UserRole::USER: return "USER";
            case UserRole::ADMIN: return "ADMIN";
            default: return "UNKNOWN";
        }
    }

public:
    DocumentProxy(const std::string& filename, UserRole role) 
        : filename_(filename), userRole_(role) {
        std::cout << "DocumentProxy created with role: " << roleToString(role) << std::endl;
    }

    void read() override {
        std::cout << "Proxy: Checking read permissions..." << std::endl;
        if (userRole_ == UserRole::GUEST && filename_.find("confidential") != std::string::npos) {
            std::cout << "Access denied: Guests cannot read confidential documents" << std::endl;
            return;
        }
        getRealDocument()->read();
    }

    void write(const std::string& content) override {
        std::cout << "Proxy: Checking write permissions..." << std::endl;
        if (userRole_ == UserRole::GUEST) {
            std::cout << "Access denied: Guests cannot write documents" << std::endl;
            return;
        }
        getRealDocument()->write(content);
    }

    void deleteDoc() override {
        std::cout << "Proxy: Checking delete permissions..." << std::endl;
        if (userRole_ != UserRole::ADMIN) {
            std::cout << "Access denied: Only admins can delete documents" << std::endl;
            return;
        }
        getRealDocument()->deleteDoc();
    }
    
};
int main(){
      // 2. Protection Proxy - Access Control
    std::cout << "\n\n2. Protection Proxy (Access Control) Example:" << std::endl;
    
    auto guestDoc = std::make_unique<DocumentProxy>("report.txt", UserRole::GUEST);
    auto userDoc = std::make_unique<DocumentProxy>("confidential_report.txt", UserRole::USER);
    auto adminDoc = std::make_unique<DocumentProxy>("system_config.txt", UserRole::ADMIN);
    
    std::cout << "\nGuest trying to read normal document:" << std::endl;
    guestDoc->read();
    
    std::cout << "\nGuest trying to write document:" << std::endl;
    guestDoc->write("Guest content");
    
    std::cout << "\nUser trying to read confidential document:" << std::endl;
    userDoc->read();
    
    std::cout << "\nUser trying to delete document:" << std::endl;
    userDoc->deleteDoc();
    
    std::cout << "\nAdmin performing all operations:" << std::endl;
    adminDoc->read();
    adminDoc->write("New admin content");
    adminDoc->deleteDoc();
    adminDoc->read();  // Should show empty content after deletion
    return 0;
}