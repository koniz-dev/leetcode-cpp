# 🚀 C++ Smart Pointers: Complete Guide

## 📚 Overview

Smart pointers are C++ objects that manage the lifetime of dynamically allocated memory automatically. They provide automatic memory management, preventing memory leaks and dangling pointers, while maintaining RAII (Resource Acquisition Is Initialization) principles.

## 🎯 Key Concepts

### What are Smart Pointers?
- **Automatic memory management**: Memory is automatically freed when no longer needed
- **RAII compliance**: Resources are managed through object lifetime
- **Exception safety**: Memory is freed even when exceptions occur
- **No manual delete**: Eliminates the need for manual memory deallocation

### Types of Smart Pointers
- **unique_ptr**: Exclusive ownership, move-only
- **shared_ptr**: Shared ownership with reference counting
- **weak_ptr**: Non-owning reference to shared_ptr
- **auto_ptr**: Deprecated (C++17), replaced by unique_ptr

## 🔒 Unique Pointer (unique_ptr)

### Basic Usage
```cpp
#include <memory>
#include <iostream>
using namespace std;

int main() {
    // Create unique_ptr
    unique_ptr<int> ptr1(new int(42));
    unique_ptr<int> ptr2 = make_unique<int>(100);  // Preferred way
    
    // Access the value
    cout << "Value: " << *ptr1 << endl;
    cout << "Value: " << *ptr2 << endl;
    
    // Check if pointer is valid
    if (ptr1) {
        cout << "ptr1 is valid" << endl;
    }
    
    // Reset pointer
    ptr1.reset();  // ptr1 now points to nullptr
    if (!ptr1) {
        cout << "ptr1 is now null" << endl;
    }
    
    // Release ownership
    int* rawPtr = ptr2.release();  // ptr2 now owns nothing
    cout << "Raw pointer value: " << *rawPtr << endl;
    delete rawPtr;  // Manual cleanup required
    
    return 0;
}
```

### Unique Pointer with Custom Deleter
```cpp
#include <memory>
#include <iostream>
#include <cstdio>
using namespace std;

// Custom deleter for FILE*
struct FileDeleter {
    void operator()(FILE* file) {
        if (file) {
            fclose(file);
            cout << "File closed" << endl;
        }
    }
};

// Custom deleter for arrays
struct ArrayDeleter {
    void operator()(int* ptr) {
        delete[] ptr;
        cout << "Array deleted" << endl;
    }
};

int main() {
    // unique_ptr with custom deleter
    unique_ptr<FILE, FileDeleter> filePtr(fopen("test.txt", "w"));
    if (filePtr) {
        fprintf(filePtr.get(), "Hello, World!");
    }
    
    // unique_ptr for arrays
    unique_ptr<int, ArrayDeleter> arrayPtr(new int[5]{1, 2, 3, 4, 5});
    
    // Lambda deleter
    auto lambdaDeleter = [](int* ptr) {
        delete ptr;
        cout << "Lambda deleter called" << endl;
    };
    
    unique_ptr<int, decltype(lambdaDeleter)> lambdaPtr(new int(42), lambdaDeleter);
    
    return 0;
}
```

### Unique Pointer in Functions
```cpp
#include <memory>
#include <iostream>
using namespace std;

// Function that takes ownership
void takeOwnership(unique_ptr<int> ptr) {
    cout << "Ownership transferred, value: " << *ptr << endl;
    // ptr is automatically deleted when function ends
}

// Function that returns unique_ptr
unique_ptr<int> createValue(int value) {
    return make_unique<int>(value);
}

// Function that conditionally returns unique_ptr
unique_ptr<int> maybeCreateValue(bool shouldCreate) {
    if (shouldCreate) {
        return make_unique<int>(42);
    }
    return nullptr;
}

int main() {
    auto ptr1 = make_unique<int>(100);
    
    // Transfer ownership to function
    takeOwnership(move(ptr1));  // ptr1 is now nullptr
    
    // Get unique_ptr from function
    auto ptr2 = createValue(200);
    cout << "Received value: " << *ptr2 << endl;
    
    // Conditional creation
    auto ptr3 = maybeCreateValue(true);
    if (ptr3) {
        cout << "Created value: " << *ptr3 << endl;
    }
    
    return 0;
}
```

### Unique Pointer in Containers
```cpp
#include <memory>
#include <vector>
#include <iostream>
using namespace std;

int main() {
    // Vector of unique_ptr
    vector<unique_ptr<int>> numbers;
    
    // Add elements
    numbers.push_back(make_unique<int>(1));
    numbers.push_back(make_unique<int>(2));
    numbers.push_back(make_unique<int>(3));
    
    // Access elements
    for (const auto& ptr : numbers) {
        cout << *ptr << " ";
    }
    cout << endl;
    
    // Cannot copy unique_ptr, but can move
    vector<unique_ptr<int>> numbers2;
    for (auto& ptr : numbers) {
        numbers2.push_back(move(ptr));
    }
    
    // numbers now contains nullptr pointers
    // numbers2 owns the actual integers
    
    return 0;
}
```

## 🔗 Shared Pointer (shared_ptr)

### Basic Usage
```cpp
#include <memory>
#include <iostream>
using namespace std;

class Resource {
public:
    Resource(int value) : data(value) {
        cout << "Resource " << data << " created" << endl;
    }
    
    ~Resource() {
        cout << "Resource " << data << " destroyed" << endl;
    }
    
    int getValue() const { return data; }
    
private:
    int data;
};

int main() {
    // Create shared_ptr
    shared_ptr<Resource> ptr1 = make_shared<Resource>(42);
    shared_ptr<Resource> ptr2 = ptr1;  // Reference count: 2
    
    cout << "Reference count: " << ptr1.use_count() << endl;
    
    // Access the resource
    cout << "Value: " << ptr1->getValue() << endl;
    cout << "Value: " << ptr2->getValue() << endl;
    
    // Reset one pointer
    ptr1.reset();  // Reference count: 1
    cout << "After reset, reference count: " << ptr2.use_count() << endl;
    
    // Reset the other pointer
    ptr2.reset();  // Reference count: 0, Resource destroyed
    
    return 0;
}
```

### Shared Pointer with Custom Deleter
```cpp
#include <memory>
#include <iostream>
using namespace std;

// Custom deleter function
void customDelete(int* ptr) {
    cout << "Custom delete called for value: " << *ptr << endl;
    delete ptr;
}

// Custom deleter class
struct CustomDeleter {
    void operator()(int* ptr) {
        cout << "Custom deleter operator called for value: " << *ptr << endl;
        delete ptr;
    }
};

int main() {
    // Function pointer deleter
    shared_ptr<int> ptr1(new int(42), customDelete);
    
    // Function object deleter
    shared_ptr<int> ptr2(new int(100), CustomDeleter{});
    
    // Lambda deleter
    auto lambdaDeleter = [](int* ptr) {
        cout << "Lambda deleter called for value: " << *ptr << endl;
        delete ptr;
    };
    
    shared_ptr<int> ptr3(new int(200), lambdaDeleter);
    
    return 0;
}
```

### Shared Pointer and Inheritance
```cpp
#include <memory>
#include <iostream>
using namespace std;

class Base {
public:
    virtual ~Base() {
        cout << "Base destructor" << endl;
    }
    
    virtual void display() const {
        cout << "Base class" << endl;
    }
};

class Derived : public Base {
public:
    ~Derived() override {
        cout << "Derived destructor" << endl;
    }
    
    void display() const override {
        cout << "Derived class" << endl;
    }
};

int main() {
    // Create shared_ptr to derived class
    shared_ptr<Derived> derivedPtr = make_shared<Derived>();
    
    // Assign to base class pointer (polymorphism)
    shared_ptr<Base> basePtr = derivedPtr;
    
    // Both pointers share ownership
    cout << "Reference count: " << derivedPtr.use_count() << endl;
    cout << "Reference count: " << basePtr.use_count() << endl;
    
    // Polymorphic behavior
    basePtr->display();
    derivedPtr->display();
    
    return 0;
}
```

### Shared Pointer in Data Structures
```cpp
#include <memory>
#include <iostream>
using namespace std;

struct Node {
    int data;
    shared_ptr<Node> next;
    
    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    shared_ptr<Node> head;
    
public:
    void insert(int value) {
        auto newNode = make_shared<Node>(value);
        newNode->next = head;
        head = newNode;
    }
    
    void display() const {
        auto current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    
    // Note: This can cause stack overflow for long lists
    // due to recursive destruction of shared_ptr
};

int main() {
    LinkedList list;
    list.insert(3);
    list.insert(2);
    list.insert(1);
    
    list.display();
    
    return 0;
}
```

## 🔗 Weak Pointer (weak_ptr)

### Basic Usage
```cpp
#include <memory>
#include <iostream>
using namespace std;

int main() {
    shared_ptr<int> sharedPtr = make_shared<int>(42);
    
    // Create weak_ptr from shared_ptr
    weak_ptr<int> weakPtr = sharedPtr;
    
    // Check if weak_ptr is valid
    if (auto lockedPtr = weakPtr.lock()) {
        cout << "Weak pointer is valid, value: " << *lockedPtr << endl;
    } else {
        cout << "Weak pointer is expired" << endl;
    }
    
    // Check use count
    cout << "Shared pointer use count: " << sharedPtr.use_count() << endl;
    
    // Reset shared_ptr
    sharedPtr.reset();
    
    // Check weak_ptr again
    if (auto lockedPtr = weakPtr.lock()) {
        cout << "Weak pointer is still valid" << endl;
    } else {
        cout << "Weak pointer is now expired" << endl;
    }
    
    return 0;
}
```

### Weak Pointer to Break Circular References
```cpp
#include <memory>
#include <iostream>
using namespace std;

struct Node {
    int data;
    shared_ptr<Node> next;
    weak_ptr<Node> prev;  // Use weak_ptr to break circular reference
    
    Node(int value) : data(value), next(nullptr) {}
};

class CircularList {
private:
    shared_ptr<Node> head;
    
public:
    void insert(int value) {
        auto newNode = make_shared<Node>(value);
        
        if (!head) {
            head = newNode;
            newNode->next = head;
            newNode->prev = head;
        } else {
            newNode->next = head;
            newNode->prev = head->prev;
            
            if (auto prevNode = head->prev.lock()) {
                prevNode->next = newNode;
            }
            head->prev = newNode;
        }
    }
    
    void display() const {
        if (!head) return;
        
        auto current = head;
        do {
            cout << current->data << " ";
            current = current->next;
        } while (current != head);
        cout << endl;
    }
};

int main() {
    CircularList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    
    list.display();
    
    return 0;
}
```

## 🚀 Advanced Smart Pointer Features

### Enable Shared From This
```cpp
#include <memory>
#include <iostream>
using namespace std;

class Widget : public enable_shared_from_this<Widget> {
public:
    Widget() {
        cout << "Widget created" << endl;
    }
    
    ~Widget() {
        cout << "Widget destroyed" << endl;
    }
    
    shared_ptr<Widget> getShared() {
        return shared_from_this();
    }
    
    void process() {
        cout << "Processing widget" << endl;
    }
};

int main() {
    auto widget = make_shared<Widget>();
    
    // Get shared_ptr from this
    auto sharedWidget = widget->getShared();
    
    cout << "Reference count: " << widget.use_count() << endl;
    
    return 0;
}
```

### Smart Pointer Arrays
```cpp
#include <memory>
#include <iostream>
using namespace std;

int main() {
    // C++11: unique_ptr for arrays
    unique_ptr<int[]> array1(new int[5]{1, 2, 3, 4, 5});
    
    // Access elements
    for (int i = 0; i < 5; i++) {
        cout << array1[i] << " ";
    }
    cout << endl;
    
    // C++17: shared_ptr for arrays
    shared_ptr<int[]> array2 = make_shared<int[]>(5);
    for (int i = 0; i < 5; i++) {
        array2[i] = i + 1;
    }
    
    // C++20: make_unique for arrays
    auto array3 = make_unique<int[]>(5);
    for (int i = 0; i < 5; i++) {
        array3[i] = i + 1;
    }
    
    return 0;
}
```

### Smart Pointer with Polymorphic Deleter
```cpp
#include <memory>
#include <iostream>
using namespace std;

// Base class for different resource types
class Resource {
public:
    virtual ~Resource() = default;
    virtual void cleanup() = 0;
};

class FileResource : public Resource {
public:
    void cleanup() override {
        cout << "File resource cleaned up" << endl;
    }
};

class NetworkResource : public Resource {
public:
    void cleanup() override {
        cout << "Network resource cleaned up" << endl;
    }
};

// Polymorphic deleter
struct PolymorphicDeleter {
    void operator()(Resource* ptr) {
        if (ptr) {
            ptr->cleanup();
            delete ptr;
        }
    }
};

int main() {
    // Create unique_ptr with polymorphic deleter
    unique_ptr<Resource, PolymorphicDeleter> filePtr(new FileResource());
    unique_ptr<Resource, PolymorphicDeleter> networkPtr(new NetworkResource());
    
    return 0;
}
```

## 📝 Best Practices

### 1. Prefer make_unique and make_shared
```cpp
// Good: Use make functions
auto ptr1 = make_unique<int>(42);
auto ptr2 = make_shared<string>("Hello");

// Bad: Direct construction
unique_ptr<int> ptr3(new int(42));
shared_ptr<string> ptr4(new string("Hello"));
```

### 2. Use unique_ptr by Default
```cpp
// Good: Use unique_ptr when you need exclusive ownership
unique_ptr<Resource> resource = make_unique<Resource>();

// Only use shared_ptr when you need shared ownership
shared_ptr<Resource> sharedResource = make_shared<Resource>();
```

### 3. Avoid Circular References
```cpp
// Bad: Circular reference with shared_ptr
struct BadNode {
    shared_ptr<BadNode> next;
    shared_ptr<BadNode> prev;  // Circular reference!
};

// Good: Use weak_ptr to break circular references
struct GoodNode {
    shared_ptr<GoodNode> next;
    weak_ptr<GoodNode> prev;   // No circular reference
};
```

### 4. Don't Use get() Unless Necessary
```cpp
// Bad: Using get() unnecessarily
auto ptr = make_unique<int>(42);
int* rawPtr = ptr.get();
delete rawPtr;  // Double deletion!

// Good: Let smart pointer manage memory
auto ptr = make_unique<int>(42);
// No manual deletion needed
```

### 5. Use weak_ptr for Observers
```cpp
class Subject {
private:
    vector<weak_ptr<Observer>> observers;
    
public:
    void addObserver(weak_ptr<Observer> observer) {
        observers.push_back(observer);
    }
    
    void notify() {
        // Remove expired observers
        observers.erase(
            remove_if(observers.begin(), observers.end(),
                     [](const weak_ptr<Observer>& wp) { return wp.expired(); }),
            observers.end()
        );
        
        // Notify valid observers
        for (auto& observer : observers) {
            if (auto obs = observer.lock()) {
                obs->update();
            }
        }
    }
};
```

## 🎯 Performance Considerations

### Shared Pointer Overhead
```cpp
#include <memory>
#include <chrono>
#include <vector>

void benchmark() {
    const int iterations = 1000000;
    
    // unique_ptr performance
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        auto ptr = make_unique<int>(i);
    }
    auto end = chrono::high_resolution_clock::now();
    auto unique_time = chrono::duration_cast<chrono::microseconds>(end - start);
    
    // shared_ptr performance
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        auto ptr = make_shared<int>(i);
    }
    end = chrono::high_resolution_clock::now();
    auto shared_time = chrono::duration_cast<chrono::microseconds>(end - start);
    
    cout << "unique_ptr time: " << unique_time.count() << " μs" << endl;
    cout << "shared_ptr time: " << shared_time.count() << " μs" << endl;
}
```

### Memory Layout
```cpp
// unique_ptr: Single pointer, no overhead
unique_ptr<int> ptr;  // Size: sizeof(int*)

// shared_ptr: Two pointers (object + control block)
shared_ptr<int> ptr;  // Size: 2 * sizeof(int*)

// weak_ptr: Two pointers (same as shared_ptr)
weak_ptr<int> ptr;    // Size: 2 * sizeof(int*)
```

## 🎯 Practice Problems

### Problem 1: Resource Manager
```cpp
class ResourceManager {
private:
    unique_ptr<Resource> resource;
    
public:
    ResourceManager() = default;
    
    void setResource(unique_ptr<Resource> newResource) {
        resource = move(newResource);
    }
    
    Resource* getResource() const {
        return resource.get();
    }
    
    bool hasResource() const {
        return resource != nullptr;
    }
    
    void clearResource() {
        resource.reset();
    }
};
```

### Problem 2: Observer Pattern
```cpp
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const string& message) = 0;
};

class Subject {
private:
    vector<weak_ptr<Observer>> observers;
    
public:
    void addObserver(weak_ptr<Observer> observer) {
        observers.push_back(observer);
    }
    
    void notify(const string& message) {
        // Remove expired observers
        observers.erase(
            remove_if(observers.begin(), observers.end(),
                     [](const weak_ptr<Observer>& wp) { return wp.expired(); }),
            observers.end()
        );
        
        // Notify valid observers
        for (auto& observer : observers) {
            if (auto obs = observer.lock()) {
                obs->update(message);
            }
        }
    }
};
```

### Problem 3: Factory Pattern
```cpp
class Product {
public:
    virtual ~Product() = default;
    virtual void operation() = 0;
};

class ConcreteProductA : public Product {
public:
    void operation() override {
        cout << "ConcreteProductA operation" << endl;
    }
};

class ConcreteProductB : public Product {
public:
    void operation() override {
        cout << "ConcreteProductB operation" << endl;
    }
};

class Factory {
public:
    static unique_ptr<Product> createProduct(const string& type) {
        if (type == "A") {
            return make_unique<ConcreteProductA>();
        } else if (type == "B") {
            return make_unique<ConcreteProductB>();
        }
        return nullptr;
    }
};
```

## 📚 Summary

Key takeaways:
- **Use smart pointers instead of raw pointers** for automatic memory management
- **Prefer unique_ptr for exclusive ownership** and shared_ptr for shared ownership
- **Use weak_ptr to break circular references** and implement observer patterns
- **Use make_unique and make_shared** for exception-safe creation
- **Understand the performance implications** of different smart pointer types
- **Follow RAII principles** for resource management
- **Avoid common pitfalls** like circular references and unnecessary get() usage

Master smart pointers to write safe, modern C++ code with automatic memory management!

---

## 🔗 Related Topics
- [Object-Oriented Programming](oop-concepts.md)
- [Move Semantics](move-semantics.md)
- [Exception Handling](exception-handling.md)
- [RAII and Resource Management](memory-management.md)
