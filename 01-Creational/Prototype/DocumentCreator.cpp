#include<iostream>
#include<memory>
#include<string>
#include<unordered_map>
#include<functional>
#include<vector>
using namespace std;

// Abstract Prototype
class Document{
    protected:
        string title, author, templateName, content;
        int date;
    public:
        virtual ~Document() = default;
        virtual std::unique_ptr<Document> clone() const = 0;
        virtual void generate() = 0;
        virtual string getDocumentType() const =0;
        
        // getter setters
        string getTitle() const {return this->title;}
        string getAuthor() const {return this->author;}
        string getContent() const {return this->content;}
        string getTemplateName() const {return this->templateName;}
        void setTitle(const string& t) { title = t; }
        void setAuthor(const string& a) { author = a; }
        void setContent(const string& c){ content = c;}
        void setTempName(const string& tname){ templateName = tname;}
        
        void displayInfo() const {
            cout << "Document: " << title << " (Type: " << getDocumentType() 
                 << ", Template: " << templateName << ")" << endl;
        }
};

//Concrete Prototypes
class Resume : public Document{
    private:
        vector<string> experience, education;
        string name;
    public:
        Resume(const string title = "Resume Template"){
            this->title = title;
            this->templateName = "Resume";
            this->author = "Default Author";
        }
        
        std::unique_ptr<Document> clone() const override{
            return std::make_unique<Resume>(*this);
        }
        
        void generate() override {
            cout << "Generating resume: " << title << endl;
            cout << "Author: " << author << endl;
            cout << "Experience entries: " << experience.size() << endl;
            cout << "Education entries: " << education.size() << endl;
        }
        
        string getDocumentType() const override{
            return "Resume";
        }
        
        void addWorkExperience(const string& exp) {
             experience.push_back(exp);
        }
        
        void setName(const string& n){
            this->name = n;
        }
        
        size_t getExperienceCount() const { return experience.size(); }
};

class Report : public Document{
    private:
        string department;
        int reportNo;
        vector<string> summaryReport;
    public:
        Report(const string title = "Report Template"){
            this->title = title;
            this->templateName = "Report";
            this->author = "Default Reporter";
            this->reportNo = 1001;
        }
        
        std::unique_ptr<Document> clone() const override{
            return std::make_unique<Report>(*this);
        }
        
        void generate() override {
            cout << "Generating Report: " << title << endl;
            cout << "Department: " << department << endl;
            cout << "Report No: " << reportNo << endl;
            cout << "Summary entries: " << summaryReport.size() << endl;
        }
        
        string getDocumentType() const override{
            return "Report";
        }
        
        void addSummary(const string& summary) {
             summaryReport.push_back(summary);
        }
        
        void setDepartment(const string& dept){
            this->department = dept;
        }
        
        void setReportNo(int num) { reportNo = num; }
        size_t getSummaryCount() const { return summaryReport.size(); }
};

// Prototype Registry
class TemplateManager {
    private:
        std::unordered_map<std::string, std::unique_ptr<Document>> documentTemplate;

    public:
        void registerTemplate(std::string name, std::unique_ptr<Document> DocumentType){
           documentTemplate[name] = std::move(DocumentType);
        }
        
        std::unique_ptr<Document> createDocument(std::string templateName){
            auto iter = documentTemplate.find(templateName);
            if (iter == documentTemplate.end()){
                return nullptr; 
            }
            cout << "Creating document from prototype: " << templateName << endl;
              // <-- USING CLONE() METHOD!
            return documentTemplate[templateName]->clone();
        }
        
        void listAvailableTemplates() const{
            std::cout << "All registered templates:" << std::endl;
            for (const auto &[name, document] : documentTemplate){
                 std::cout << "- " << name << " (" << document->getDocumentType() << ")" << std::endl;
            }
        }   
};

// Client code
int main() {
    cout << "=== Document Template System Demo ===" << endl << endl;
    
    // Create a registry and register some prototypes
    TemplateManager manager;
    
    // Create and configure resume template
    std::unique_ptr<Document> resumeTemplate = std::make_unique<Resume>("Software Engineer Resume"); // resumeTemplate is of type Document
   //  resumeTemplate->addWorkExperience("Some experience");  // ERROR! Document doesn't have this method
    resumeTemplate->setAuthor("Template Author");
    // Pre-populate with some default experience
    if (auto* resume = dynamic_cast<Resume*>(resumeTemplate.get())) { // NEEDS dynamic_cast example usage
        resume->addWorkExperience("Previous Software Development Experience");
        resume->addWorkExperience("Internship Experience");
    }
    
    // Create and configure report template  
    std::unique_ptr<Report> reportTemplate = std::make_unique<Report>("Monthly Sales Report");
    reportTemplate->setAuthor("Sales Manager");
    reportTemplate->setDepartment("Sales");
    reportTemplate->addSummary("Default executive summary");
    
    
    // Register templates
    manager.registerTemplate("software_resume", std::move(resumeTemplate));
    manager.registerTemplate("sales_report", std::move(reportTemplate));
    
    // List available templates
    manager.listAvailableTemplates();
    cout << endl;
    
    // Clone documents from templates
    cout << "=== Creating Documents from Templates ===" << endl;
    
    auto johnResume = manager.createDocument("software_resume"); // Returns unique_ptr<Document>
    if (johnResume) {
        johnResume->setTitle("John's Resume");
        johnResume->setAuthor("John Doe");
        
        // Add specific experience to John's resume , needs dynamic ptr for line 175
        if (auto* resume = dynamic_cast<Resume*>(johnResume.get())) {
            resume->addWorkExperience("Senior Developer at Tech Corp");
        }
        
        cout << "Created John's resume:" << endl;
        johnResume->displayInfo();
        johnResume->generate();
        cout << endl;
    }
    
    auto januaryReport = manager.createDocument("sales_report");
    if (januaryReport) {
        januaryReport->setTitle("January Sales Report");
        januaryReport->setAuthor("Jane Smith");
        
        if (auto* report = dynamic_cast<Report*>(januaryReport.get())) {
            report->setReportNo(2024001);
            report->addSummary("January showed 15% growth");
            report->addSummary("New customer acquisition exceeded targets");
        }
        
        cout << "Created January report:" << endl;
        januaryReport->displayInfo();
        januaryReport->generate();
        cout << endl;
    }
    
    // Demonstrate independence: create another resume and modify it differently
    cout << "=== Demonstrating Template Independence ===" << endl;
    
    auto sarahResume = manager.createDocument("software_resume");
    if (sarahResume) {
        sarahResume->setTitle("Sarah's Resume");
        sarahResume->setAuthor("Sarah Johnson");
        
        cout << "Created Sarah's resume (from same template):" << endl;
        sarahResume->displayInfo();
        sarahResume->generate();
        cout << endl;
    }
    
    // Show that original template is unchanged
    cout << "=== Verifying Original Template Unchanged ===" << endl;
    auto anotherResume = manager.createDocument("software_resume");
    if (anotherResume) {
        cout << "Fresh copy from original template:" << endl;
        anotherResume->displayInfo();
        anotherResume->generate();
    }
    
    return 0;
}