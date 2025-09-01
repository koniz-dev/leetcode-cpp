# 🚀 C++ Move Semantics: Complete Guide

## 📚 Overview

Move semantics is one of the most important features introduced in C++11. It allows you to transfer resources from one object to another instead of copying them, significantly improving performance and enabling efficient resource management.

## 🎯 Key Concepts

### What are Move Semantics?
- **Resource transfer**: Move resources instead of copying them
- **Performance improvement**: Avoid expensive copy operations
- **Rvalue references**: New reference type for temporary objects
- **Move constructors/assignment**: Special member functions for moving

### Why Move Semantics?
- **Eliminate unnecessary copying** of large objects
- **Return objects efficiently** from functions
- **Optimize container operations** (insert, push_back, etc.)
- **Enable perfect forwarding** in templates

## 🔄 Rvalue References

### Basic Rvalue References
```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 42;
    
    // Lvalue reference (traditional)
    int& lref = x;           // OK: x is an lvalue
    
    // Rvalue reference (C++11)
    int&& rref = 42;         // OK: 42 is an rvalue
    int&& rref2 = x + 1;     // OK: x + 1 is an rvalue
    
    // Cannot bind rvalue reference to lvalue
    // int&& rref3 = x;      // Error: x is an lvalue
    
    // Can bind rvalue reference to lvalue using std::move
    int&& rref4 = move(x);   // OK: explicitly move from x
    
    cout << "x: " << x << endl;           // x is still 42 (but moved from)
    cout << "rref: " << rref << endl;     // 42
    cout << "rref2: " << rref2 << endl;   // 43
    cout << "rref4: " << rref4 << endl;   // 42
    
    return 0;
}
```

### Function Overloading with Rvalue References
```cpp
#include <iostream>
#include <string>
using namespace std;

// Function overloaded for lvalue and rvalue references
void process(const string& str) {
    cout << "Lvalue reference: " << str << endl;
}

void process(string&& str) {
    cout << "Rvalue reference: " << str << endl;
    // str is moved from, so it's in a valid but unspecified state
}

int main() {
    string name = "Alice";
    
    process(name);           // Calls lvalue version
    process("Bob");          // Calls rvalue version
    process(move(name));     // Calls rvalue version
    
    // After move, name is in valid but unspecified state
    cout << "Name after move: '" << name << "'" << endl;
    
    return 0;
}
```

### Perfect Forwarding
```cpp
#include <iostream>
#include <string>
using namespace std;

// Template function that preserves value category
template<typename T>
void wrapper(T&& arg) {
    // Forward preserves the value category (lvalue/rvalue)
    process(forward<T>(arg));
}

int main() {
    string name = "Alice";
    
    wrapper(name);           // T is string&, calls lvalue version
    wrapper("Bob");          // T is string, calls rvalue version
    wrapper(move(name));     // T is string, calls rvalue version
    
    return 0;
}
```

## 🏗️ Move Constructor

### Basic Move Constructor
```cpp
#include <iostream>
#include <cstring>
using namespace std;

class String {
private:
    char* data;
    size_t length;
    
public:
    // Default constructor
    String() : data(nullptr), length(0) {}
    
    // Constructor from C-string
    String(const char* str) {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }
    
    // Copy constructor
    String(const String& other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
        cout << "Copy constructor called" << endl;
    }
    
    // Move constructor
    String(String&& other) noexcept {
        // Transfer ownership of resources
        data = other.data;
        length = other.length;
        
        // Leave other in valid but unspecified state
        other.data = nullptr;
        other.length = 0;
        
        cout << "Move constructor called" << endl;
    }
    
    // Destructor
    ~String() {
        delete[] data;
    }
    
    // Assignment operator
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
            cout << "Copy assignment called" << endl;
        }
        return *this;
    }
    
    // Move assignment operator
    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] data;
            
            // Transfer ownership
            data = other.data;
            length = other.length;
            
            // Leave other in valid but unspecified state
            other.data = nullptr;
            other.length = 0;
            
            cout << "Move assignment called" << endl;
        }
        return *this;
    }
    
    // Getter
    const char* c_str() const { return data; }
};

// Function that returns a String
String createString() {
    return String("Hello from function");
}

int main() {
    String s1("Hello");
    String s2 = s1;                    // Copy constructor
    String s3 = move(s1);              // Move constructor
    String s4 = createString();        // Move constructor (RVO)
    
    s2 = s3;                           // Copy assignment
    s3 = move(s4);                     // Move assignment
    
    return 0;
}
```

### Move Constructor with Member Initialization
```cpp
class Resource {
private:
    int* data;
    size_t size;
    
public:
    // Constructor
    Resource(size_t s) : size(s) {
        data = new int[size];
        for (size_t i = 0; i < size; i++) {
            data[i] = i;
        }
    }
    
    // Move constructor with member initializer list
    Resource(Resource&& other) noexcept
        : data(other.data), size(other.size) {
        // Reset other object
        other.data = nullptr;
        other.size = 0;
    }
    
    // Destructor
    ~Resource() {
        delete[] data;
    }
    
    // Move assignment
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
};
```

## 🔄 Move Assignment Operator

### Complete Move Assignment Example
```cpp
#include <iostream>
#include <vector>
using namespace std;

class DynamicArray {
private:
    int* data;
    size_t size;
    size_t capacity;
    
public:
    // Constructor
    DynamicArray(size_t initialCapacity = 10) 
        : size(0), capacity(initialCapacity) {
        data = new int[capacity];
    }
    
    // Copy constructor
    DynamicArray(const DynamicArray& other) 
        : size(other.size), capacity(other.capacity) {
        data = new int[capacity];
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    
    // Move constructor
    DynamicArray(DynamicArray&& other) noexcept
        : data(other.data), size(other.size), capacity(other.capacity) {
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    
    // Copy assignment
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new int[capacity];
            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    // Move assignment
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            delete[] data;
            
            // Transfer ownership
            data = other.data;
            size = other.size;
            capacity = other.capacity;
            
            // Reset other object
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }
    
    // Destructor
    ~DynamicArray() {
        delete[] data;
    }
    
    // Add element
    void push_back(int value) {
        if (size >= capacity) {
            capacity *= 2;
            int* newData = new int[capacity];
            for (size_t i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size++] = value;
    }
    
    // Get size
    size_t getSize() const { return size; }
    
    // Get element
    int& operator[](size_t index) { return data[index]; }
    const int& operator[](size_t index) const { return data[index]; }
};

int main() {
    DynamicArray arr1;
    for (int i = 0; i < 5; i++) {
        arr1.push_back(i);
    }
    
    DynamicArray arr2;
    arr2 = move(arr1);  // Move assignment
    
    cout << "arr2 size: " << arr2.getSize() << endl;
    for (size_t i = 0; i < arr2.getSize(); i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

## 🚀 Advanced Move Semantics

### Move with Inheritance
```cpp
class Base {
protected:
    int* data;
    
public:
    Base() : data(new int(0)) {}
    
    // Virtual destructor for proper cleanup
    virtual ~Base() { delete data; }
    
    // Move constructor
    Base(Base&& other) noexcept : data(other.data) {
        other.data = nullptr;
    }
    
    // Move assignment
    Base& operator=(Base&& other) noexcept {
        if (this != &other) {
            delete data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }
};

class Derived : public Base {
private:
    string* name;
    
public:
    Derived() : name(new string("default")) {}
    
    // Move constructor
    Derived(Derived&& other) noexcept
        : Base(move(other)), name(other.name) {
        other.name = nullptr;
    }
    
    // Move assignment
    Derived& operator=(Derived&& other) noexcept {
        if (this != &other) {
            Base::operator=(move(other));
            delete name;
            name = other.name;
            other.name = nullptr;
        }
        return *this;
    }
    
    ~Derived() { delete name; }
};
```

### Move with Templates
```cpp
template<typename T>
class Container {
private:
    T* data;
    size_t size;
    
public:
    Container(size_t s) : size(s) {
        data = new T[size];
    }
    
    // Move constructor
    Container(Container&& other) noexcept
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }
    
    // Move assignment
    Container& operator=(Container&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
    
    ~Container() { delete[] data; }
};

// Specialization for types that can't be moved
template<>
class Container<const int> {
    // No move operations for const int
    // Copy operations only
};
```

### Move with Smart Pointers
```cpp
#include <memory>
#include <iostream>
using namespace std;

class Widget {
private:
    unique_ptr<int> data;
    string name;
    
public:
    Widget(const string& n, int value) 
        : data(make_unique<int>(value)), name(n) {}
    
    // Move constructor
    Widget(Widget&& other) noexcept = default;
    
    // Move assignment
    Widget& operator=(Widget&& other) noexcept = default;
    
    // Copy operations are deleted (unique_ptr is move-only)
    Widget(const Widget&) = delete;
    Widget& operator=(const Widget&) = delete;
    
    void display() const {
        cout << name << ": " << *data << endl;
    }
};

int main() {
    Widget w1("Widget1", 42);
    Widget w2 = move(w1);  // Move constructor
    
    // w1 is now in moved-from state
    // w2 owns the resources
    
    return 0;
}
```

## 📝 Best Practices

### 1. Use noexcept for Move Operations
```cpp
class Resource {
public:
    // Good: Mark move operations as noexcept
    Resource(Resource&& other) noexcept;
    Resource& operator=(Resource&& other) noexcept;
    
    // This allows containers to use move operations
    // even when they need strong exception guarantees
};
```

### 2. Implement Move Operations Consistently
```cpp
class MyClass {
public:
    // If you define one move operation, define both
    MyClass(MyClass&& other) noexcept;
    MyClass& operator=(MyClass&& other) noexcept;
    
    // Also consider copy operations
    MyClass(const MyClass& other);
    MyClass& operator=(const MyClass& other);
};
```

### 3. Use std::move Appropriately
```cpp
void process(String&& str) {
    // Good: Move from rvalue reference
    String local = move(str);
}

void process(String& str) {
    // Good: Move from lvalue reference when done with it
    String local = move(str);
    // str is now in moved-from state
}

void process(const String& str) {
    // Bad: Can't move from const reference
    // String local = move(str);  // Error
}
```

### 4. Avoid Moving from Objects You Still Need
```cpp
int main() {
    String s1("Hello");
    String s2 = move(s1);  // s1 is moved from
    
    // Bad: Using s1 after move
    cout << s1.c_str() << endl;  // Undefined behavior
    
    // Good: Reassign s1 if you need it
    s1 = "New string";
    cout << s1.c_str() << endl;  // OK
    
    return 0;
}
```

### 5. Use Move Semantics in Return Statements
```cpp
// Good: Return by value (compiler may optimize)
String createString() {
    String result("Hello");
    return result;  // May use move constructor
}

// Good: Explicit move for complex objects
vector<int> createVector() {
    vector<int> result = {1, 2, 3, 4, 5};
    return move(result);  // Explicit move
}
```

## 🎯 Performance Benefits

### Vector Operations
```cpp
#include <vector>
#include <chrono>

void benchmark() {
    vector<string> strings;
    
    // Without move semantics (C++98 style)
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) {
        string temp = "String " + to_string(i);
        strings.push_back(temp);  // Copy
    }
    auto end = chrono::high_resolution_clock::now();
    auto copy_time = chrono::duration_cast<chrono::microseconds>(end - start);
    
    // With move semantics (C++11+)
    vector<string> strings2;
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) {
        string temp = "String " + to_string(i);
        strings2.push_back(move(temp));  // Move
    }
    end = chrono::high_resolution_clock::now();
    auto move_time = chrono::duration_cast<chrono::microseconds>(end - start);
    
    cout << "Copy time: " << copy_time.count() << " μs" << endl;
    cout << "Move time: " << move_time.count() << " μs" << endl;
}
```

### Function Return Optimization
```cpp
// Without move semantics
vector<int> createLargeVector() {
    vector<int> result(1000000);
    // Fill result...
    return result;  // Copy (expensive)
}

// With move semantics
vector<int> createLargeVector() {
    vector<int> result(1000000);
    // Fill result...
    return result;  // Move (cheap)
}

int main() {
    // This is now efficient
    vector<int> data = createLargeVector();
    return 0;
}
```

## 🎯 Practice Problems

### Problem 1: Move-Only Resource Class
```cpp
class FileHandle {
private:
    FILE* file;
    
public:
    FileHandle(const char* filename, const char* mode) {
        file = fopen(filename, mode);
        if (!file) {
            throw runtime_error("Failed to open file");
        }
    }
    
    // Move constructor
    FileHandle(FileHandle&& other) noexcept : file(other.file) {
        other.file = nullptr;
    }
    
    // Move assignment
    FileHandle& operator=(FileHandle&& other) noexcept {
        if (this != &other) {
            close();
            file = other.file;
            other.file = nullptr;
        }
        return *this;
    }
    
    // Destructor
    ~FileHandle() {
        close();
    }
    
    // Copy operations deleted
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;
    
    void close() {
        if (file) {
            fclose(file);
            file = nullptr;
        }
    }
    
    FILE* get() const { return file; }
};
```

### Problem 2: Move-Enabled Container
```cpp
template<typename T>
class SimpleVector {
private:
    T* data;
    size_t size;
    size_t capacity;
    
public:
    SimpleVector() : data(nullptr), size(0), capacity(0) {}
    
    // Move constructor
    SimpleVector(SimpleVector&& other) noexcept
        : data(other.data), size(other.size), capacity(other.capacity) {
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    
    // Move assignment
    SimpleVector& operator=(SimpleVector&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            capacity = other.capacity;
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }
    
    // Destructor
    ~SimpleVector() {
        delete[] data;
    }
    
    // Copy operations
    SimpleVector(const SimpleVector& other) : size(other.size), capacity(other.size) {
        data = new T[capacity];
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    
    SimpleVector& operator=(const SimpleVector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.size;
            data = new T[capacity];
            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    void push_back(const T& value) {
        if (size >= capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            T* newData = new T[capacity];
            for (size_t i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size++] = value;
    }
    
    void push_back(T&& value) {
        if (size >= capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            T* newData = new T[capacity];
            for (size_t i = 0; i < size; i++) {
                newData[i] = move(data[i]);
            }
            delete[] data;
            data = newData;
        }
        data[size++] = move(value);
    }
    
    size_t getSize() const { return size; }
    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }
};
```

### Problem 3: Perfect Forwarding Template
```cpp
template<typename T>
class Wrapper {
private:
    T data;
    
public:
    // Perfect forwarding constructor
    template<typename U>
    Wrapper(U&& value) : data(forward<U>(value)) {}
    
    // Move constructor
    Wrapper(Wrapper&& other) noexcept = default;
    
    // Move assignment
    Wrapper& operator=(Wrapper&& other) noexcept = default;
    
    // Copy operations
    Wrapper(const Wrapper& other) = default;
    Wrapper& operator=(const Wrapper& other) = default;
    
    T& get() { return data; }
    const T& get() const { return data; }
};

int main() {
    string str = "Hello";
    
    Wrapper<string> w1(str);           // Copy constructor
    Wrapper<string> w2("World");        // Move constructor
    Wrapper<string> w3(move(str));      // Move constructor
    
    return 0;
}
```

## 📚 Summary

Key takeaways:
- **Move semantics eliminate unnecessary copying** and improve performance
- **Rvalue references** enable move operations and perfect forwarding
- **Move constructors and assignment operators** transfer resource ownership
- **Use noexcept** for move operations to enable optimizations
- **std::move** converts lvalues to rvalues for moving
- **Perfect forwarding** preserves value categories in templates
- **Follow the rule of five** when implementing move operations

Master move semantics to write high-performance, modern C++ code!

---

## 🔗 Related Topics
- [Object-Oriented Programming](oop-concepts.md)
- [Templates](templates.md)
- [Smart Pointers](smart-pointers.md)
- [Exception Handling](exception-handling.md)
