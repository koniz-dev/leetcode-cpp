# Memory Management in C++

## Overview

Memory management in C++ involves controlling how memory is allocated, used, and deallocated. Modern C++ provides several mechanisms for memory management, from manual control to automatic resource management through RAII and smart pointers.

## Memory Model

### Memory Layout

```cpp
#include <iostream>

int globalVar = 42;           // Global/Static memory
static int staticVar = 100;    // Global/Static memory

void function() {
    int localVar = 10;        // Stack memory
    static int localStatic = 20; // Global/Static memory
    
    int* heapVar = new int(30); // Heap memory
    delete heapVar;            // Manual deallocation
}

class MyClass {
    int memberVar;            // Part of object memory
    static int staticMember;  // Global/Static memory
};
```

### Memory Segments

```cpp
// Text segment (code)
void function() { /* function code */ }

// Data segment (global/static variables)
int globalVar = 42;
static int staticVar = 100;

// BSS segment (uninitialized global/static variables)
int uninitializedGlobal;
static int uninitializedStatic;

// Stack segment (local variables, function calls)
void stackExample() {
    int localVar = 10;
    double localDouble = 3.14;
    // Stack grows downward
}

// Heap segment (dynamic memory)
void heapExample() {
    int* heapInt = new int(42);
    double* heapDouble = new double(3.14);
    delete heapInt;
    delete heapDouble;
}
```

## Manual Memory Management

### new and delete

```cpp
#include <iostream>

// Single object allocation
int* singleInt = new int(42);
delete singleInt;

// Array allocation
int* intArray = new int[10];
delete[] intArray;

// Object allocation
class MyClass {
public:
    MyClass(int val) : value(val) {
        std::cout << "Constructor called" << std::endl;
    }
    ~MyClass() {
        std::cout << "Destructor called" << std::endl;
    }
private:
    int value;
};

MyClass* obj = new MyClass(100);
delete obj;

// Placement new
char buffer[sizeof(MyClass)];
MyClass* placedObj = new(buffer) MyClass(200);
placedObj->~MyClass(); // Explicit destructor call
```

### Common Pitfalls

```cpp
// Memory leak
void memoryLeak() {
    int* ptr = new int(42);
    // Forgot to delete - memory leak!
    return; // ptr goes out of scope, memory lost
}

// Double deletion
void doubleDelete() {
    int* ptr = new int(42);
    delete ptr;
    delete ptr; // Undefined behavior!
}

// Dangling pointer
void danglingPointer() {
    int* ptr = new int(42);
    delete ptr;
    *ptr = 100; // Undefined behavior - accessing freed memory
}

// Array/object mismatch
void mismatch() {
    int* array = new int[10];
    delete array; // Should be delete[] array
    
    int* single = new int(42);
    delete[] single; // Should be delete single
}
```

## RAII (Resource Acquisition Is Initialization)

### Basic RAII Principle

```cpp
#include <iostream>

class ResourceManager {
private:
    int* resource;
    
public:
    ResourceManager(int value) : resource(new int(value)) {
        std::cout << "Resource acquired" << std::endl;
    }
    
    ~ResourceManager() {
        delete resource;
        std::cout << "Resource released" << std::endl;
    }
    
    int getValue() const { return *resource; }
    void setValue(int value) { *resource = value; }
};

void raiiExample() {
    ResourceManager rm(42);
    std::cout << "Value: " << rm.getValue() << std::endl;
    // Resource automatically released when rm goes out of scope
}
```

### RAII with File Handling

```cpp
#include <fstream>
#include <string>

class FileHandler {
private:
    std::fstream file;
    
public:
    FileHandler(const std::string& filename, std::ios::openmode mode) {
        file.open(filename, mode);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
    }
    
    ~FileHandler() {
        if (file.is_open()) {
            file.close();
        }
    }
    
    std::fstream& getFile() { return file; }
    
    // Prevent copying
    FileHandler(const FileHandler&) = delete;
    FileHandler& operator=(const FileHandler&) = delete;
    
    // Allow moving
    FileHandler(FileHandler&& other) noexcept : file(std::move(other.file)) {}
    FileHandler& operator=(FileHandler&& other) noexcept {
        if (this != &other) {
            file = std::move(other.file);
        }
        return *this;
    }
};

void fileExample() {
    try {
        FileHandler handler("test.txt", std::ios::out);
        handler.getFile() << "Hello, RAII!" << std::endl;
        // File automatically closed when handler goes out of scope
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
```

## Smart Pointers

### unique_ptr

```cpp
#include <memory>
#include <iostream>

class Resource {
public:
    Resource(int id) : id_(id) {
        std::cout << "Resource " << id_ << " created" << std::endl;
    }
    
    ~Resource() {
        std::cout << "Resource " << id_ << " destroyed" << std::endl;
    }
    
    void use() {
        std::cout << "Using resource " << id_ << std::endl;
    }
    
    int getId() const { return id_; }
    
private:
    int id_;
};

void uniquePtrExample() {
    // Create unique_ptr
    auto resource1 = std::make_unique<Resource>(1);
    resource1->use();
    
    // Transfer ownership
    auto resource2 = std::move(resource1);
    if (resource1 == nullptr) {
        std::cout << "resource1 is now nullptr" << std::endl;
    }
    
    // Custom deleter
    auto customResource = std::unique_ptr<Resource, void(*)(Resource*)>(
        new Resource(2),
        [](Resource* r) {
            std::cout << "Custom deletion for resource " << r->getId() << std::endl;
            delete r;
        }
    );
    
    // Array unique_ptr
    auto arrayPtr = std::make_unique<Resource[]>(3);
    arrayPtr[0].use();
    arrayPtr[1].use();
    arrayPtr[2].use();
}
```

### shared_ptr

```cpp
#include <memory>
#include <iostream>

class SharedResource {
public:
    SharedResource(int id) : id_(id) {
        std::cout << "SharedResource " << id_ << " created" << std::endl;
    }
    
    ~SharedResource() {
        std::cout << "SharedResource " << id_ << " destroyed" << std::endl;
    }
    
    void use() {
        std::cout << "Using shared resource " << id_ << std::endl;
    }
    
private:
    int id_;
};

void sharedPtrExample() {
    // Create shared_ptr
    auto resource1 = std::make_shared<SharedResource>(1);
    
    {
        auto resource2 = resource1; // Reference count increases
        std::cout << "Reference count: " << resource1.use_count() << std::endl;
        resource2->use();
    } // resource2 goes out of scope, reference count decreases
    
    std::cout << "Reference count: " << resource1.use_count() << std::endl;
    resource1->use();
    
    // Weak pointer to avoid circular references
    std::weak_ptr<SharedResource> weakRef = resource1;
    if (auto locked = weakRef.lock()) {
        locked->use();
    }
    
    // Custom deleter
    auto customShared = std::shared_ptr<SharedResource>(
        new SharedResource(2),
        [](SharedResource* r) {
            std::cout << "Custom deletion for shared resource" << std::endl;
            delete r;
        }
    );
}
```

### weak_ptr

```cpp
#include <memory>
#include <iostream>

class Node {
public:
    std::string name;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev; // Weak reference to avoid circular dependency
    
    Node(const std::string& n) : name(n) {
        std::cout << "Node " << name << " created" << std::endl;
    }
    
    ~Node() {
        std::cout << "Node " << name << " destroyed" << std::endl;
    }
};

void weakPtrExample() {
    auto node1 = std::make_shared<Node>("First");
    auto node2 = std::make_shared<Node>("Second");
    
    // Create circular reference with weak_ptr
    node1->next = node2;
    node2->prev = node1;
    
    // Check if weak_ptr is still valid
    if (auto prev = node2->prev.lock()) {
        std::cout << "Previous node: " << prev->name << std::endl;
    }
    
    // Reset node1
    node1.reset();
    
    // Check weak_ptr after original is destroyed
    if (auto prev = node2->prev.lock()) {
        std::cout << "Previous node still exists: " << prev->name << std::endl;
    } else {
        std::cout << "Previous node no longer exists" << std::endl;
    }
}
```

## Custom Allocators

### Basic Allocator

```cpp
#include <memory>
#include <iostream>

template<typename T>
class SimpleAllocator {
private:
    static constexpr size_t POOL_SIZE = 1024;
    static char pool[POOL_SIZE];
    static size_t poolIndex;
    
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    
    SimpleAllocator() noexcept = default;
    template<typename U>
    SimpleAllocator(const SimpleAllocator<U>&) noexcept {}
    
    T* allocate(size_type n) {
        if (n == 1 && poolIndex + sizeof(T) <= POOL_SIZE) {
            T* ptr = reinterpret_cast<T*>(&pool[poolIndex]);
            poolIndex += sizeof(T);
            return ptr;
        }
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }
    
    void deallocate(T* ptr, size_type n) noexcept {
        if (ptr >= reinterpret_cast<T*>(pool) && 
            ptr < reinterpret_cast<T*>(pool + POOL_SIZE)) {
            // Memory from pool, do nothing
        } else {
            ::operator delete(ptr);
        }
    }
    
    template<typename U, typename... Args>
    void construct(U* ptr, Args&&... args) {
        ::new(ptr) U(std::forward<Args>(args)...);
    }
    
    template<typename U>
    void destroy(U* ptr) {
        ptr->~U();
    }
};

template<typename T>
char SimpleAllocator<T>::pool[POOL_SIZE];

template<typename T>
size_t SimpleAllocator<T>::poolIndex = 0;

// Usage
void allocatorExample() {
    std::vector<int, SimpleAllocator<int>> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    
    for (int val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}
```

### Pool Allocator

```cpp
#include <memory>
#include <vector>
#include <iostream>

template<typename T>
class PoolAllocator {
private:
    struct Block {
        Block* next;
    };
    
    static constexpr size_t BLOCK_SIZE = sizeof(T);
    static constexpr size_t POOL_SIZE = 1024;
    
    Block* freeList = nullptr;
    char* pool = nullptr;
    size_t poolIndex = 0;
    
public:
    using value_type = T;
    
    PoolAllocator() {
        pool = new char[POOL_SIZE];
        poolIndex = 0;
    }
    
    ~PoolAllocator() {
        delete[] pool;
    }
    
    T* allocate(size_type n) {
        if (n != 1) {
            return static_cast<T*>(::operator new(n * sizeof(T)));
        }
        
        if (freeList) {
            T* result = reinterpret_cast<T*>(freeList);
            freeList = freeList->next;
            return result;
        }
        
        if (poolIndex + BLOCK_SIZE <= POOL_SIZE) {
            T* result = reinterpret_cast<T*>(&pool[poolIndex]);
            poolIndex += BLOCK_SIZE;
            return result;
        }
        
        return static_cast<T*>(::operator new(sizeof(T)));
    }
    
    void deallocate(T* ptr, size_type n) noexcept {
        if (n != 1) {
            ::operator delete(ptr);
            return;
        }
        
        if (ptr >= reinterpret_cast<T*>(pool) && 
            ptr < reinterpret_cast<T*>(pool + POOL_SIZE)) {
            Block* block = reinterpret_cast<Block*>(ptr);
            block->next = freeList;
            freeList = block;
        } else {
            ::operator delete(ptr);
        }
    }
};
```

## Memory Alignment

### Alignment Requirements

```cpp
#include <iostream>
#include <cstddef>

struct AlignedStruct {
    alignas(16) double data[4];  // 16-byte aligned
    int id;
};

struct PackedStruct {
    char a;
    int b;      // May have padding
    char c;
} __attribute__((packed));  // Remove padding

void alignmentExample() {
    std::cout << "Size of AlignedStruct: " << sizeof(AlignedStruct) << std::endl;
    std::cout << "Alignment of AlignedStruct: " << alignof(AlignedStruct) << std::endl;
    
    std::cout << "Size of PackedStruct: " << sizeof(PackedStruct) << std::endl;
    std::cout << "Alignment of PackedStruct: " << alignof(PackedStruct) << std::endl;
    
    // Dynamic alignment
    std::aligned_storage_t<sizeof(int), alignof(int)> storage;
    int* ptr = reinterpret_cast<int*>(&storage);
    *ptr = 42;
}
```

### Custom Alignment

```cpp
#include <memory>
#include <iostream>

template<typename T>
T* alignedAllocate(size_t count, size_t alignment) {
    size_t size = count * sizeof(T);
    size_t alignedSize = (size + alignment - 1) & ~(alignment - 1);
    
    void* ptr = std::aligned_alloc(alignment, alignedSize);
    return static_cast<T*>(ptr);
}

template<typename T>
void alignedDeallocate(T* ptr) {
    std::free(ptr);
}

void customAlignmentExample() {
    // Allocate 16-byte aligned memory
    double* alignedPtr = alignedAllocate<double>(10, 16);
    
    std::cout << "Address: " << alignedPtr << std::endl;
    std::cout << "Alignment: " << (reinterpret_cast<uintptr_t>(alignedPtr) % 16) << std::endl;
    
    // Use memory
    for (int i = 0; i < 10; ++i) {
        alignedPtr[i] = i * 1.5;
    }
    
    alignedDeallocate(alignedPtr);
}
```

## Memory Pools and Object Factories

### Object Pool

```cpp
#include <memory>
#include <vector>
#include <iostream>

template<typename T>
class ObjectPool {
private:
    struct PoolObject {
        T data;
        bool inUse;
        PoolObject() : inUse(false) {}
    };
    
    std::vector<std::unique_ptr<PoolObject>> pool;
    size_t poolSize;
    
public:
    ObjectPool(size_t size) : poolSize(size) {
        for (size_t i = 0; i < size; ++i) {
            pool.push_back(std::make_unique<PoolObject>());
        }
    }
    
    T* acquire() {
        for (auto& obj : pool) {
            if (!obj->inUse) {
                obj->inUse = true;
                return &obj->data;
            }
        }
        return nullptr; // Pool exhausted
    }
    
    void release(T* obj) {
        for (auto& poolObj : pool) {
            if (&poolObj->data == obj) {
                poolObj->inUse = false;
                break;
            }
        }
    }
    
    size_t getAvailableCount() const {
        size_t count = 0;
        for (const auto& obj : pool) {
            if (!obj->inUse) ++count;
        }
        return count;
    }
};

// Usage
class ExpensiveObject {
public:
    ExpensiveObject() {
        std::cout << "ExpensiveObject created" << std::endl;
    }
    
    ~ExpensiveObject() {
        std::cout << "ExpensiveObject destroyed" << std::endl;
    }
    
    void use() {
        std::cout << "Using ExpensiveObject" << std::endl;
    }
};

void objectPoolExample() {
    ObjectPool<ExpensiveObject> pool(3);
    
    auto obj1 = pool.acquire();
    auto obj2 = pool.acquire();
    
    if (obj1 && obj2) {
        obj1->use();
        obj2->use();
        
        pool.release(obj1);
        pool.release(obj2);
    }
    
    std::cout << "Available objects: " << pool.getAvailableCount() << std::endl;
}
```

## Best Practices

### Memory Management Guidelines

```cpp
// DO: Use smart pointers by default
class GoodClass {
private:
    std::unique_ptr<Resource> resource;
    
public:
    GoodClass() : resource(std::make_unique<Resource>()) {}
    // No destructor needed - unique_ptr handles cleanup
};

// DON'T: Use raw pointers for ownership
class BadClass {
private:
    Resource* resource; // BAD: Raw pointer ownership
    
public:
    BadClass() : resource(new Resource()) {}
    ~BadClass() { delete resource; } // Manual cleanup needed
    
    // Need copy constructor, assignment operator, move operations
    BadClass(const BadClass& other) : resource(new Resource(*other.resource)) {}
    BadClass& operator=(const BadClass& other) {
        if (this != &other) {
            delete resource;
            resource = new Resource(*other.resource);
        }
        return *this;
    }
};

// DO: Use RAII for all resources
class RAIIExample {
private:
    std::unique_ptr<File> file;
    std::unique_ptr<Network> network;
    
public:
    RAIIExample() {
        file = std::make_unique<File>("data.txt");
        network = std::make_unique<Network>("localhost", 8080);
    }
    // All resources automatically cleaned up
};

// DO: Consider move semantics
class MoveableClass {
private:
    std::unique_ptr<Resource> resource;
    
public:
    MoveableClass() = default;
    
    MoveableClass(MoveableClass&& other) noexcept = default;
    MoveableClass& operator=(MoveableClass&& other) noexcept = default;
    
    // Delete copy operations
    MoveableClass(const MoveableClass&) = delete;
    MoveableClass& operator=(const MoveableClass&) = delete;
};
```

### Performance Considerations

```cpp
// Use appropriate allocation strategies
class OptimizedClass {
private:
    // Small objects: stack allocation
    int smallData[16];
    
    // Large objects: heap allocation
    std::unique_ptr<std::vector<int>> largeData;
    
    // Frequently allocated: object pool
    static ObjectPool<ExpensiveObject> pool;
    
public:
    OptimizedClass() {
        // Use pool for expensive objects
        auto obj = pool.acquire();
        if (obj) {
            // Use object
            pool.release(obj);
        }
    }
};

// Avoid unnecessary allocations
class EfficientString {
private:
    std::string data;
    
public:
    void append(const std::string& str) {
        // Reserve space to avoid reallocation
        if (data.size() + str.size() > data.capacity()) {
            data.reserve(data.size() + str.size());
        }
        data += str;
    }
};
```

## Summary

Memory management in C++ provides:
- **Control**: Fine-grained control over memory allocation
- **Performance**: Optimized memory usage and access patterns
- **Safety**: Prevention of memory leaks and undefined behavior
- **Flexibility**: Multiple approaches for different use cases

Key principles:
- **Use RAII**: Automatic resource management
- **Prefer smart pointers**: Automatic cleanup and exception safety
- **Avoid raw pointers**: Use smart pointers for ownership
- **Consider performance**: Choose appropriate allocation strategies
- **Plan for exceptions**: Ensure cleanup even when exceptions occur

Modern C++ memory management:
- **Smart pointers**: `unique_ptr`, `shared_ptr`, `weak_ptr`
- **RAII**: Automatic resource cleanup
- **Move semantics**: Efficient resource transfer
- **Custom allocators**: Specialized memory management
- **Memory pools**: Optimized allocation for specific use cases

The key is to use the right tool for the job: smart pointers for most cases, custom solutions when performance is critical, and always ensure exception safety through RAII.
