Document Template System
Scenario: You're building a document management system where users can create different types of documents (Resume, Report, Invoice, Letter) from pre-configured templates. Each document type has specific formatting, default content, and metadata that should be preserved when creating new documents from templates.
Requirements to implement:

Abstract Prototype: Document base class with:

Properties: title, author, creation date, template name, content
Pure virtual clone() method
Virtual methods: generate(), getDocumentType()
Common functionality for setting/getting properties


Concrete Prototypes:

Resume: Has sections (personal info, experience, education), default formatting
Report: Has report number, department, executive summary, findings
Invoice: Has invoice number, billing info, line items, total amount
Letter: Has recipient, sender, formal greeting/closing, body content


Template Manager: Registry that stores and manages document templates:

registerTemplate(name, document) - store a prototype
createDocument(templateName) - clone from prototype
listAvailableTemplates() - show all registered templates
deleteTemplate(name) - remove a template


Additional Features:

Each document type should have specific methods (e.g., Resume has addWorkExperience(), Invoice has addLineItem())
Support for document versioning (version number that increments on clone)
Ability to customize templates with different themes/styles



Test Scenarios:

Create templates for "Software Engineer Resume", "Monthly Sales Report", "Service Invoice"
Clone documents from templates and modify them independently
Verify that changes to cloned documents don't affect the original templates
Show that you can create multiple documents from the same template

auto* resume = dynamic_cast<Resume*>(resumeTemplate.get())
What's happening step by step:
1. resumeTemplate.get()

resumeTemplate is a std::unique_ptr<Document>
The .get() method returns the raw pointer that the unique_ptr is managing
So this returns a Document* (pointer to the base class)

2. dynamic_cast<Resume*>(...)

This is a runtime type conversion that safely converts from base class pointer to derived class pointer
It's checking: "Is this Document* actually pointing to a Resume object?"
If YES: returns a valid Resume* pointer
If NO: returns nullptr

3. auto* resume = ...

The auto* deduces the type as Resume*
Could also be written as: Resume* resume = dynamic_cast<Resume*>(...)

Copy constructor is called: make_unique<Resume>(*this) uses the copy constructor
New object created: A completely new Resume object with the same data
Independent object: Changes to the clone don't affect the original prototype