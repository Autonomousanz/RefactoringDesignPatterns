## Proxy Pattern

There are three common types of Proxy patterns:
1. Virtual Proxy (Lazy Loading)

Purpose: Delays expensive object creation until actually needed
Example: ImageProxy only creates the RealImage when display() is called
Benefit: Saves memory and startup time when dealing with large resources

2. Protection Proxy (Access Control)

Purpose: Controls access to the real object based on permissions
Example: DocumentProxy checks user roles before allowing read/write/delete operations
Benefit: Implements security without modifying the original class

3. Caching Proxy (Performance)

Purpose: Stores results to avoid repeated expensive operations
Example: CachingWebServiceProxy caches API responses
Benefit: Dramatically improves performance for repeated requests

## Real-world expensive operations:

Loading large images from disk
Network requests to APIs
Database queries
File compression/decompression
Complex calculations