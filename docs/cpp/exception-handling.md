# Exception Handling in C++

## Overview

Exception handling is a mechanism that allows programs to deal with exceptional circumstances (runtime errors) in a controlled manner. It provides a way to transfer control from one part of a program to another when an error occurs.

## Key Concepts

### Exception Handling Components
- **try block**: Code that might throw exceptions
- **catch block**: Code that handles specific exceptions
- **throw statement**: Raises an exception
- **Exception object**: Contains information about the error

### Exception Safety Levels
- **Basic guarantee**: No resource leaks, objects remain in valid state
- **Strong guarantee**: Operation either succeeds or has no effect
- **No-throw guarantee**: Operation never throws exceptions

## Basic Exception Handling

### Try-Catch Blocks

```cpp
#include <iostream>
#include <stdexcept>

int main() {
    try {
        // Code that might throw an exception
        int x = 10;
        int y = 0;
        
        if (y == 0) {
            throw std::runtime_error("Division by zero");
        }
        
        int result = x / y;
        std::cout << "Result: " << result << std::endl;
        
    } catch (const std::runtime_error& e) {
        // Handle runtime errors
        std::cerr << "Runtime error: " << e.what() << std::endl;
        
    } catch (const std::exception& e) {
        // Handle any standard exception
        std::cerr << "Standard exception: " << e.what() << std::endl;
        
    } catch (...) {
        // Handle any other exception
        std::cerr << "Unknown exception occurred" << std::endl;
    }
    
    return 0;
}
```

### Throwing Exceptions

```cpp
// Throw with a string literal
throw "Something went wrong";

// Throw with an exception object
throw std::runtime_error("Invalid input");

// Throw with a custom exception class
class CustomException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Custom error message";
    }
};

throw CustomException();
```

## Exception Classes

### Standard Exception Hierarchy

```cpp
#include <exception>
#include <stdexcept>
#include <new>
#include <typeinfo>

// Base exception class
std::exception

// Logic errors (preventable)
std::logic_error
├── std::invalid_argument
├── std::domain_error
├── std::length_error
└── std::out_of_range

// Runtime errors (unpredictable)
std::runtime_error
├── std::range_error
├── std::overflow_error
├── std::underflow_error
└── std::system_error

// Other exceptions
std::bad_alloc        // Memory allocation failure
std::bad_cast         // Dynamic cast failure
std::bad_typeid       // Type info failure
std::bad_function_call // Function call failure
```

### Using Standard Exceptions

```cpp
#include <stdexcept>
#include <string>

class Calculator {
public:
    double divide(double a, double b) {
        if (b == 0.0) {
            throw std::invalid_argument("Division by zero");
        }
        return a / b;
    }
    
    int factorial(int n) {
        if (n < 0) {
            throw std::domain_error("Factorial not defined for negative numbers");
        }
        if (n > 20) {
            throw std::overflow_error("Result too large");
        }
        
        int result = 1;
        for (int i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    }
};
```

## Custom Exception Classes

### Creating Custom Exceptions

```cpp
#include <exception>
#include <string>

class FileException : public std::runtime_error {
private:
    std::string filename;
    int error_code;
    
public:
    FileException(const std::string& msg, const std::string& fname, int code)
        : std::runtime_error(msg), filename(fname), error_code(code) {}
    
    const std::string& getFilename() const { return filename; }
    int getErrorCode() const { return error_code; }
    
    const char* what() const noexcept override {
        static std::string full_msg;
        full_msg = std::runtime_error::what();
        full_msg += " (File: " + filename + ", Code: " + std::to_string(error_code) + ")";
        return full_msg.c_str();
    }
};

// Usage
void openFile(const std::string& filename) {
    // Simulate file operation
    if (filename.empty()) {
        throw FileException("Empty filename", filename, -1);
    }
    
    // File not found simulation
    if (filename == "nonexistent.txt") {
        throw FileException("File not found", filename, 2);
    }
}
```

### Exception with Additional Data

```cpp
class ValidationException : public std::exception {
private:
    std::string field_name;
    std::string value;
    std::string reason;
    
public:
    ValidationException(const std::string& field, const std::string& val, const std::string& r)
        : field_name(field), value(val), reason(r) {}
    
    const char* what() const noexcept override {
        static std::string msg;
        msg = "Validation failed for field '" + field_name + 
              "' with value '" + value + "': " + reason;
        return msg.c_str();
    }
    
    const std::string& getFieldName() const { return field_name; }
    const std::string& getValue() const { return value; }
    const std::string& getReason() const { return reason; }
};
```

## Exception Safety

### RAII and Exception Safety

```cpp
class ResourceManager {
private:
    int* resource;
    
public:
    ResourceManager() : resource(new int(42)) {
        std::cout << "Resource acquired" << std::endl;
    }
    
    ~ResourceManager() {
        delete resource;
        std::cout << "Resource released" << std::endl;
    }
    
    // Copy constructor
    ResourceManager(const ResourceManager& other) : resource(new int(*other.resource)) {
        std::cout << "Resource copied" << std::endl;
    }
    
    // Copy assignment
    ResourceManager& operator=(const ResourceManager& other) {
        if (this != &other) {
            int* new_resource = new int(*other.resource);
            delete resource;
            resource = new_resource;
        }
        return *this;
    }
    
    // Move constructor
    ResourceManager(ResourceManager&& other) noexcept : resource(other.resource) {
        other.resource = nullptr;
        std::cout << "Resource moved" << std::endl;
    }
    
    // Move assignment
    ResourceManager& operator=(ResourceManager&& other) noexcept {
        if (this != &other) {
            delete resource;
            resource = other.resource;
            other.resource = nullptr;
        }
        return *this;
    }
};
```

### Exception-Safe Functions

```cpp
class Vector {
private:
    int* data;
    size_t size;
    size_t capacity;
    
public:
    // Strong exception guarantee
    void push_back(int value) {
        if (size >= capacity) {
            // Create new array with double capacity
            size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
            int* new_data = new int[new_capacity];
            
            try {
                // Copy existing elements
                for (size_t i = 0; i < size; ++i) {
                    new_data[i] = data[i];
                }
                
                // Add new element
                new_data[size] = value;
                
                // Update state (no-throw operations)
                delete[] data;
                data = new_data;
                capacity = new_capacity;
                ++size;
                
            } catch (...) {
                // Clean up on exception
                delete[] new_data;
                throw; // Re-throw the exception
            }
        } else {
            // Simple case - no allocation needed
            data[size] = value;
            ++size;
        }
    }
};
```

## Advanced Exception Handling

### Function Try Blocks

```cpp
class Widget {
private:
    std::string name;
    
public:
    Widget(const std::string& n) try : name(n) {
        if (n.empty()) {
            throw std::invalid_argument("Name cannot be empty");
        }
        // Constructor body
    } catch (...) {
        // Handle exceptions from member initialization
        std::cerr << "Failed to construct Widget" << std::endl;
        throw; // Re-throw to caller
    }
    
    void process() try {
        if (name.empty()) {
            throw std::runtime_error("Cannot process empty name");
        }
        // Process the widget
    } catch (const std::exception& e) {
        std::cerr << "Processing failed: " << e.what() << std::endl;
        throw; // Re-throw
    }
};
```

### Nested Exception Handling

```cpp
void outerFunction() {
    try {
        middleFunction();
    } catch (const std::exception& e) {
        std::cerr << "Outer caught: " << e.what() << std::endl;
        throw; // Re-throw to caller
    }
}

void middleFunction() {
    try {
        innerFunction();
    } catch (const std::runtime_error& e) {
        std::cerr << "Middle caught runtime_error: " << e.what() << std::endl;
        throw std::logic_error("Wrapped error: " + std::string(e.what()));
    }
}

void innerFunction() {
    throw std::runtime_error("Something went wrong");
}
```

### Exception Specifications (C++11+)

```cpp
// noexcept specification
void safeFunction() noexcept {
    // This function promises not to throw
}

// Conditional noexcept
template<typename T>
void swap(T& a, T& b) noexcept(noexcept(T(std::move(a)))) {
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}

// noexcept operator
template<typename T>
void process(T& obj) {
    if constexpr (noexcept(obj.process())) {
        obj.process(); // Safe to call
    } else {
        try {
            obj.process();
        } catch (...) {
            // Handle exception
        }
    }
}
```

## Best Practices

### Do's and Don'ts

```cpp
// DO: Use RAII for resource management
class FileHandler {
    std::ifstream file;
public:
    FileHandler(const std::string& filename) : file(filename) {
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
    }
    // File automatically closed in destructor
};

// DON'T: Throw from destructors
class BadClass {
public:
    ~BadClass() {
        // BAD: Destructors should not throw
        // throw std::runtime_error("Destructor error");
    }
};

// DO: Use specific exception types
void validateAge(int age) {
    if (age < 0) {
        throw std::invalid_argument("Age cannot be negative");
    }
    if (age > 150) {
        throw std::out_of_range("Age seems unrealistic");
    }
}

// DON'T: Catch and ignore exceptions
void badFunction() {
    try {
        riskyOperation();
    } catch (...) {
        // BAD: Silent failure
        // Log the error or handle it appropriately
    }
}
```

### Exception-Safe Design

```cpp
class Transaction {
private:
    std::vector<std::string> operations;
    bool committed = false;
    
public:
    void addOperation(const std::string& op) {
        operations.push_back(op);
    }
    
    void commit() {
        try {
            // Execute all operations
            for (const auto& op : operations) {
                executeOperation(op);
            }
            committed = true;
        } catch (...) {
            // Rollback on failure
            rollback();
            throw;
        }
    }
    
    void rollback() {
        // Undo all operations
        operations.clear();
        committed = false;
    }
    
private:
    void executeOperation(const std::string& op) {
        // Simulate operation execution
        if (op == "fail") {
            throw std::runtime_error("Operation failed");
        }
    }
};
```

## Summary

Exception handling provides:
- **Error isolation**: Errors don't crash the entire program
- **Resource safety**: RAII ensures proper cleanup
- **Error propagation**: Exceptions bubble up to appropriate handlers
- **Type safety**: Different exception types for different errors

Key principles:
- **Use RAII** for automatic resource management
- **Throw by value, catch by reference**
- **Provide meaningful error messages**
- **Design for exception safety**
- **Don't throw from destructors**
- **Use appropriate exception types**

Exception handling is essential for writing robust, maintainable C++ code that can gracefully handle errors and maintain program integrity.
