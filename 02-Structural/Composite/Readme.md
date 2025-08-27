## Composite Pattern

Component (FileSystemComponent): Abstract base class defining the interface that both leaves and composites must implement.
Leaf (File): Represents individual objects that don't have children. Files implement the basic operations like display() and getSize().
Composite (Directory): Can contain other components (both files and directories). It implements the same interface as leaves but delegates operations to its children.


## Benefits
Uniform Treatment: Client code can treat individual files and directories the same way
Recursive Structure: Operations like getSize() automatically recurse through the tree
Easy Extension: You can add new types of components without changing existing code
Flexible Hierarchy: You can build complex tree structures easily

## Usage of Shared pointer

1. Shared Ownership
In a composite structure, a single component can potentially be referenced from multiple places:

A child component is owned by its parent directory
The same component might be referenced in multiple containers or collections
Client code might hold references to components for later use
```
// Without shared_ptr, this would be problematic:
auto file = std::make_shared<File>("shared.txt", 100);
dir1->add(file);  // dir1 owns it
dir2->add(file);  // dir2 also needs to reference it
// Both directories can safely reference the same file
```

2. Safe Polymorphic Storage
The vector stores shared_ptr<FileSystemComponent>, allowing it to hold both files and directories polymorphically:
```
std::vector<std::shared_ptr<FileSystemComponent>> children;
// Can safely store both File and Directory objects
```
3. Polymorphic using Reference Semantics

```
std::cout << "\n2. Polymorphism works with reference semantics:" << std::endl;
File file("example");
Directory* dir_ptr = &file;
Directory& dir_ref = file;
```
