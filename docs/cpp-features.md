# Modern C++ Features

## Overview
Modern C++ (C++11 and later) provides many new features that make code more concise, safe, and efficient.

## Auto Keyword (C++11)

### Introduction
`auto` allows the compiler to automatically deduce the data type from the initializer.

### Basic Usage

```cpp
// Instead of writing verbose types
std::vector<int>::iterator it = vec.begin();

// Can write concisely
auto it = vec.begin();

// With complex types
auto result = std::make_pair(42, "hello");
auto lambda = [](int x) { return x * 2; };
```

### Best Practices

```cpp
// ✅ Good - clear types
auto i = 0;           // int
auto str = "hello";   // const char*
auto vec = std::vector<int>{1, 2, 3};

// ❌ Avoid - unclear types
auto result = someComplexFunction();  // Hard to understand return type
```

## Range-based For Loop (C++11)

### Introduction
Simple syntax for iterating through containers.

### Basic Usage

```cpp
#include <vector>
#include <string>

std::vector<int> nums = {1, 2, 3, 4, 5};

// Iterate by value (copy)
for (int num : nums) {
    std::cout << num << " ";
}

// Iterate by reference (avoid copy)
for (const int& num : nums) {
    std::cout << num << " ";
}

// Iterate by mutable reference
for (int& num : nums) {
    num *= 2;
}
```

### With Other Containers

```cpp
// With string
std::string str = "hello";
for (char c : str) {
    std::cout << c << " ";
}

// With array
int arr[] = {1, 2, 3, 4, 5};
for (int num : arr) {
    std::cout << num << " ";
}

// With unordered_map
std::unordered_map<std::string, int> scores = {
    {"Alice", 95},
    {"Bob", 87}
};

for (const auto& pair : scores) {
    std::cout << pair.first << ": " << pair.second << std::endl;
}
```

## Lambda Expressions (C++11)

### Introduction
Anonymous functions that can be defined inline.

### Basic Syntax

```cpp
// Syntax: [capture](parameters) -> return_type { body }

// Simple lambda
auto add = [](int a, int b) { return a + b; };
int result = add(3, 4);  // 7

// Lambda with capture
int multiplier = 10;
auto multiply = [multiplier](int x) { return x * multiplier; };
int result = multiply(5);  // 50
```

### Capture Clauses

```cpp
int x = 10, y = 20;

// Capture by value
auto lambda1 = [x, y]() { return x + y; };

// Capture by reference
auto lambda2 = [&x, &y]() { return x + y; };

// Capture all by value
auto lambda3 = [=]() { return x + y; };

// Capture all by reference
auto lambda4 = [&]() { return x + y; };

// Mixed capture
auto lambda5 = [x, &y]() { return x + y; };
```

### Common Use Cases

```cpp
#include <vector>
#include <algorithm>

std::vector<int> nums = {1, 2, 3, 4, 5};

// Sort with lambda
std::sort(nums.begin(), nums.end(), [](int a, int b) {
    return a > b;  // Sort in descending order
});

// Find with lambda
auto it = std::find_if(nums.begin(), nums.end(), [](int x) {
    return x % 2 == 0;  // Find first even number
});

// Transform with lambda
std::transform(nums.begin(), nums.end(), nums.begin(), [](int x) {
    return x * x;  // Square each element
});
```

## Smart Pointers (C++11)

### Introduction
Smart pointers automatically manage memory, preventing memory leaks.

### unique_ptr

```cpp
#include <memory>

// Create unique_ptr
std::unique_ptr<int> ptr1(new int(42));
auto ptr2 = std::make_unique<int>(42);  // Preferred

// Transfer ownership
std::unique_ptr<int> ptr3 = std::move(ptr1);

// Access value
int value = *ptr2;
int* rawPtr = ptr2.get();

// Check if valid
if (ptr2) {
    std::cout << "Pointer is valid" << std::endl;
}
```

### shared_ptr

```cpp
#include <memory>

// Create shared_ptr
auto ptr1 = std::make_shared<int>(42);
auto ptr2 = ptr1;  // Share ownership

// Check reference count
std::cout << "Reference count: " << ptr1.use_count() << std::endl;

// Access value
int value = *ptr1;
```

### weak_ptr

```cpp
#include <memory>

auto shared = std::make_shared<int>(42);
std::weak_ptr<int> weak = shared;

// Check if still valid
if (auto locked = weak.lock()) {
    std::cout << "Value: " << *locked << std::endl;
}
```

## Move Semantics (C++11)

### Introduction
Move semantics allow efficient transfer of resources instead of copying.

### Move Constructor and Assignment

```cpp
#include <vector>

class MyClass {
private:
    std::vector<int> data;
    
public:
    // Move constructor
    MyClass(MyClass&& other) noexcept 
        : data(std::move(other.data)) {}
    
    // Move assignment operator
    MyClass& operator=(MyClass&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
        }
        return *this;
    }
};
```

### std::move

```cpp
#include <vector>
#include <utility>

std::vector<int> createVector() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    return vec;  // RVO (Return Value Optimization)
}

std::vector<int> vec1 = {1, 2, 3};
std::vector<int> vec2 = std::move(vec1);  // Move vec1 to vec2

// After move, vec1 is in valid but unspecified state
```

## References

### Introduction
References provide an alias for existing variables, avoiding copying.

### Lvalue References

```cpp
int x = 42;
int& ref = x;  // Reference to x

ref = 100;  // Modifies x
std::cout << x << std::endl;  // 100

// Function parameters
void modifyValue(int& value) {
    value *= 2;
}

int num = 10;
modifyValue(num);  // num becomes 20
```

### Const References

```cpp
int x = 42;
const int& ref = x;  // Const reference

// ref = 100;  // Error: cannot modify through const reference

// Function parameters (avoid copying)
void printValue(const std::vector<int>& vec) {
    for (int num : vec) {
        std::cout << num << " ";
    }
}
```

### Rvalue References (C++11)

```cpp
int x = 42;
int&& rref = 42;  // Rvalue reference to temporary

// Function overloading
void process(int& value) {
    std::cout << "Lvalue reference" << std::endl;
}

void process(int&& value) {
    std::cout << "Rvalue reference" << std::endl;
}

int num = 10;
process(num);      // Calls lvalue version
process(42);       // Calls rvalue version
```

## Const Correctness

### Introduction
Const correctness ensures that objects are not modified when they shouldn't be.

### Const Variables

```cpp
const int MAX_SIZE = 100;
const double PI = 3.14159;

// const int x;  // Error: must be initialized
```

### Const Member Functions

```cpp
class MyClass {
private:
    int data;
    
public:
    // Const member function - cannot modify member variables
    int getData() const {
        return data;
    }
    
    // Non-const member function - can modify member variables
    void setData(int value) {
        data = value;
    }
};
```

### Const Pointers

```cpp
int x = 42;

const int* ptr1 = &x;        // Pointer to const int
int* const ptr2 = &x;        // Const pointer to int
const int* const ptr3 = &x;  // Const pointer to const int

// *ptr1 = 100;  // Error: cannot modify through ptr1
// ptr2 = nullptr;  // Error: cannot modify ptr2
// *ptr3 = 100;  // Error: cannot modify through ptr3
// ptr3 = nullptr;  // Error: cannot modify ptr3
```

## Templates

### Introduction
Templates allow writing generic code that works with different types.

### Function Templates

```cpp
template<typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

// Usage
int result1 = max(10, 20);
double result2 = max(3.14, 2.71);
```

### Class Templates

```cpp
template<typename T>
class Stack {
private:
    std::vector<T> data;
    
public:
    void push(const T& value) {
        data.push_back(value);
    }
    
    T pop() {
        if (data.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        T value = data.back();
        data.pop_back();
        return value;
    }
    
    bool empty() const {
        return data.empty();
    }
};

// Usage
Stack<int> intStack;
Stack<std::string> stringStack;
```

### Template Specialization

```cpp
// Primary template
template<typename T>
class Container {
public:
    void process() {
        std::cout << "Generic processing" << std::endl;
    }
};

// Specialization for int
template<>
class Container<int> {
public:
    void process() {
        std::cout << "Int-specific processing" << std::endl;
    }
};
```

## Exception Handling

### Introduction
Exception handling provides a way to handle errors gracefully.

### Basic Exception Handling

```cpp
#include <stdexcept>

int divide(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}

int main() {
    try {
        int result = divide(10, 0);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Unknown error: " << e.what() << std::endl;
    }
    
    return 0;
}
```

### Custom Exceptions

```cpp
class MyException : public std::exception {
private:
    std::string message;
    
public:
    MyException(const std::string& msg) : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};

void riskyFunction() {
    throw MyException("Something went wrong");
}
```

## Best Practices

### 1. Use Modern C++ Features
```cpp
// ✅ Modern approach
auto vec = std::vector<int>{1, 2, 3, 4, 5};
for (const auto& num : vec) {
    std::cout << num << " ";
}

// ❌ Old approach
std::vector<int> vec;
vec.push_back(1);
vec.push_back(2);
// ...
for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
    std::cout << *it << " ";
}
```

### 2. Prefer Smart Pointers
```cpp
// ✅ Smart pointers
auto ptr = std::make_unique<MyClass>();

// ❌ Raw pointers
MyClass* ptr = new MyClass();
// Don't forget to delete!
```

### 3. Use Const Correctness
```cpp
// ✅ Const correct
void processData(const std::vector<int>& data) {
    for (int num : data) {
        std::cout << num << " ";
    }
}

// ❌ Not const correct
void processData(std::vector<int> data) {  // Unnecessary copy
    for (int num : data) {
        std::cout << num << " ";
    }
}
```

### 4. Leverage Move Semantics
```cpp
// ✅ Move semantics
std::vector<int> createVector() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    return vec;  // RVO/move
}

// ❌ Copy semantics
std::vector<int> createVector() {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    // ...
    return vec;  // Copy
}
```

### 5. Use RAII
```cpp
// ✅ RAII - Resource Acquisition Is Initialization
class ResourceManager {
private:
    std::unique_ptr<Resource> resource;
    
public:
    ResourceManager() : resource(std::make_unique<Resource>()) {}
    // Destructor automatically cleans up
};

// ❌ Manual resource management
class ResourceManager {
private:
    Resource* resource;
    
public:
    ResourceManager() {
        resource = new Resource();
    }
    
    ~ResourceManager() {
        delete resource;  // Don't forget!
    }
};
```
