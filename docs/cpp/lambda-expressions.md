# Lambda Expressions in C++

## Overview

Lambda expressions (introduced in C++11) are a way to create anonymous function objects inline. They provide a concise syntax for defining small functions at the point where they are needed, making code more readable and maintainable.

## Basic Syntax

### Lambda Expression Structure

```cpp
[capture clause](parameters) -> return_type { body }
```

**Components:**
- **Capture clause**: Specifies which variables from the enclosing scope to capture
- **Parameters**: Function parameters (optional)
- **Return type**: Explicit return type (optional, auto-deduced if omitted)
- **Body**: Function implementation

### Simple Examples

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

// Basic lambda with no capture
auto print = [](const std::string& msg) {
    std::cout << msg << std::endl;
};

// Lambda with parameters and return value
auto add = [](int a, int b) -> int {
    return a + b;
};

// Lambda with auto return type deduction
auto multiply = [](int a, int b) {
    return a * b;
};

// Usage
print("Hello, Lambda!");
int result = add(5, 3);        // 8
int product = multiply(4, 6);  // 24
```

## Capture Clauses

### Value Capture

```cpp
int multiplier = 10;
auto lambda = [multiplier](int x) {
    return x * multiplier;  // Captures multiplier by value
};

// multiplier can be modified in outer scope without affecting lambda
multiplier = 20;
int result = lambda(5);  // Still uses 10, result = 50
```

### Reference Capture

```cpp
int sum = 0;
auto lambda = [&sum](int x) {
    sum += x;  // Captures sum by reference
};

// Modifies the original sum variable
lambda(5);   // sum = 5
lambda(10);  // sum = 15
lambda(3);   // sum = 18
```

### Mixed Capture

```cpp
int x = 10;
int y = 20;
int z = 30;

auto lambda = [x, &y, &z](int value) {
    // x captured by value (copy)
    // y and z captured by reference
    y += value;      // Modifies original y
    z += value;      // Modifies original z
    return x + y + z; // Uses copy of x
};

lambda(5);
// x remains 10 (copy)
// y becomes 25
// z becomes 35
```

### Capture All

```cpp
int a = 1, b = 2, c = 3;

// Capture all by value
auto lambda1 = [=]() {
    return a + b + c;  // Uses copies
};

// Capture all by reference
auto lambda2 = [&]() {
    a++; b++; c++;  // Modifies originals
};

// Capture all by value, but specific ones by reference
auto lambda3 = [=, &a]() {
    // a by reference, b and c by value
    a++;  // Modifies original a
    // b and c are copies
};
```

### Capture by Move

```cpp
#include <memory>
#include <string>

auto unique_ptr = std::make_unique<int>(42);
auto lambda = [ptr = std::move(unique_ptr)]() {
    return *ptr;  // ptr is moved into lambda
};
// unique_ptr is now nullptr in outer scope
```

## Lambda in Algorithms

### STL Algorithm Usage

```cpp
#include <vector>
#include <algorithm>
#include <iostream>

std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Count even numbers
auto evenCount = std::count_if(numbers.begin(), numbers.end(),
    [](int n) { return n % 2 == 0; });

// Transform numbers (double each)
std::transform(numbers.begin(), numbers.end(), numbers.begin(),
    [](int n) { return n * 2; });

// Find first number greater than threshold
int threshold = 15;
auto it = std::find_if(numbers.begin(), numbers.end(),
    [threshold](int n) { return n > threshold; });

// Sort with custom comparator
std::sort(numbers.begin(), numbers.end(),
    [](int a, int b) { return a > b; });  // Descending order
```

### Custom Predicates

```cpp
struct Person {
    std::string name;
    int age;
    double salary;
};

std::vector<Person> people = {
    {"Alice", 25, 50000},
    {"Bob", 30, 60000},
    {"Charlie", 35, 70000}
};

// Find people above certain age and salary
auto findQualified = [](int minAge, double minSalary) {
    return [minAge, minSalary](const Person& p) {
        return p.age >= minAge && p.salary >= minSalary;
    };
};

auto qualified = std::find_if(people.begin(), people.end(),
    findQualified(30, 60000));
```

## Advanced Lambda Features

### Generic Lambdas (C++14)

```cpp
// Lambda with auto parameters
auto print = [](const auto& item) {
    std::cout << item << std::endl;
};

// Works with any type
print(42);           // int
print(3.14);         // double
print("hello");      // const char*
print(std::vector<int>{1, 2, 3});  // vector

// Generic lambda with multiple auto parameters
auto add = [](const auto& a, const auto& b) {
    return a + b;
};

// Type deduction happens at call site
auto result1 = add(5, 3);        // int + int
auto result2 = add(3.14, 2.86);  // double + double
auto result3 = add(std::string("hello"), std::string(" world"));
```

### Mutable Lambdas

```cpp
int counter = 0;
auto lambda = [counter]() mutable {
    counter++;  // Can modify captured by value
    return counter;
};

// Each call gets a fresh copy of counter
std::cout << lambda() << std::endl;  // 1
std::cout << lambda() << std::endl;  // 2
std::cout << lambda() << std::endl;  // 3

// Original counter remains unchanged
std::cout << "Original counter: " << counter << std::endl;  // 0
```

### Lambda as Function Parameters

```cpp
#include <functional>

// Function taking a lambda as parameter
void processNumbers(const std::vector<int>& numbers,
                   std::function<void(int)> processor) {
    for (int num : numbers) {
        processor(num);
    }
}

// Usage with lambda
std::vector<int> nums = {1, 2, 3, 4, 5};
processNumbers(nums, [](int n) {
    std::cout << n * 2 << " ";
});

// Template version (more efficient)
template<typename Func>
void processNumbersTemplate(const std::vector<int>& numbers, Func processor) {
    for (int num : numbers) {
        processor(num);
    }
}
```

### Lambda with Complex Captures

```cpp
class Widget {
private:
    std::string name;
    int value;
    
public:
    Widget(const std::string& n, int v) : name(n), value(v) {}
    
    void process(std::function<void(const std::string&, int)> callback) {
        // Capture this pointer
        auto lambda = [this, callback]() {
            callback(name, value);
        };
        lambda();
    }
    
    // Lambda as member function
    auto getProcessor() {
        return [this](int multiplier) {
            return value * multiplier;
        };
    }
};

// Usage
Widget widget("Test", 10);
auto processor = widget.getProcessor();
int result = processor(5);  // 50
```

## Lambda with Standard Library

### Function Objects

```cpp
#include <functional>

// Store lambda in function object
std::function<int(int, int)> operation;

// Assign different lambdas
operation = [](int a, int b) { return a + b; };
int sum = operation(5, 3);  // 8

operation = [](int a, int b) { return a * b; };
int product = operation(5, 3);  // 15

// Lambda in map
std::map<std::string, std::function<int(int, int)>> operations = {
    {"add", [](int a, int b) { return a + b; }},
    {"subtract", [](int a, int b) { return a - b; }},
    {"multiply", [](int a, int b) { return a * b; }},
    {"divide", [](int a, int b) { return b != 0 ? a / b : 0; }}
};

int result = operations["add"](10, 5);      // 15
int result2 = operations["multiply"](4, 6); // 24
```

### Bind and Placeholders

```cpp
#include <functional>

auto add = [](int a, int b, int c) {
    return a + b + c;
};

// Bind first parameter
auto add5 = std::bind(add, 5, std::placeholders::_1, std::placeholders::_2);
int result = add5(3, 4);  // 5 + 3 + 4 = 12

// Bind multiple parameters
auto add5And3 = std::bind(add, 5, 3, std::placeholders::_1);
int result2 = add5And3(2);  // 5 + 3 + 2 = 10
```

## Performance Considerations

### Inlining and Optimization

```cpp
// Simple lambda - likely to be inlined
auto simple = [](int x) { return x * 2; };

// Complex lambda - may not be inlined
auto complex = [](int x) {
    // Complex computation
    int result = 0;
    for (int i = 0; i < x; ++i) {
        result += i * i;
    }
    return result;
};

// Lambda with capture - may affect inlining
int multiplier = 10;
auto captured = [multiplier](int x) { return x * multiplier; };
```

### Avoiding Unnecessary Copies

```cpp
std::vector<std::string> strings = {"hello", "world", "test"};

// Good: capture by reference
std::for_each(strings.begin(), strings.end(),
    [&strings](const std::string& s) {
        // Process string
    });

// Bad: capture by value (unnecessary copies)
std::for_each(strings.begin(), strings.end(),
    [strings](const std::string& s) {
        // strings vector copied unnecessarily
    });
```

## Common Patterns

### Factory Pattern

```cpp
auto createMultiplier = [](int factor) {
    return [factor](int value) {
        return value * factor;
    };
};

auto doubleIt = createMultiplier(2);
auto tripleIt = createMultiplier(3);

int result1 = doubleIt(5);   // 10
int result2 = tripleIt(5);   // 15
```

### Callback Registration

```cpp
class EventHandler {
private:
    std::vector<std::function<void(int)>> callbacks;
    
public:
    void registerCallback(std::function<void(int)> callback) {
        callbacks.push_back(callback);
    }
    
    void triggerEvent(int value) {
        for (const auto& callback : callbacks) {
            callback(value);
        }
    }
};

// Usage
EventHandler handler;
handler.registerCallback([](int value) {
    std::cout << "Event: " << value << std::endl;
});

handler.registerCallback([](int value) {
    std::cout << "Another handler: " << value * 2 << std::endl;
});

handler.triggerEvent(42);
```

### Conditional Execution

```cpp
auto conditionalProcess = [](bool condition) {
    return [condition](int value) {
        if (condition) {
            return value * 2;
        } else {
            return value / 2;
        }
    };
};

auto processor = conditionalProcess(true);
int result = processor(10);  // 20

auto processor2 = conditionalProcess(false);
int result2 = processor2(10); // 5
```

## Best Practices

### Do's and Don'ts

```cpp
// DO: Use descriptive names for complex lambdas
auto isValidEmail = [](const std::string& email) {
    return email.find('@') != std::string::npos && 
           email.find('.') != std::string::npos;
};

// DON'T: Create overly complex lambdas
// Consider extracting to a named function instead

// DO: Use appropriate capture modes
int threshold = 10;
auto aboveThreshold = [threshold](int value) { return value > threshold; };

// DON'T: Capture everything by reference unless necessary
// auto bad = [&]() { /* captures everything by reference */ };

// DO: Use const when appropriate
auto process = [](const auto& item) { /* process item */ };

// DON'T: Modify captured variables unless intended
// Use mutable keyword if you need to modify captured by value
```

### When to Use Lambdas

```cpp
// Good: Simple, one-off operations
std::sort(container.begin(), container.end(),
    [](const auto& a, const auto& b) { return a < b; });

// Good: Capturing local variables
int threshold = getThreshold();
auto filtered = std::find_if(data.begin(), data.end(),
    [threshold](const auto& item) { return item.value > threshold; });

// Good: Custom predicates
auto isPrime = [](int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
};

// Consider named function: Complex logic or reuse
// Consider named function: Long lambda bodies
// Consider named function: Multiple similar lambdas
```

## Summary

Lambda expressions provide:
- **Convenience**: Define functions inline where they're needed
- **Readability**: Clear intent and reduced boilerplate
- **Flexibility**: Capture local variables and context
- **Performance**: Potential for inlining and optimization

Key benefits:
- **Local scope**: Functions defined where they're used
- **Variable capture**: Access to enclosing scope variables
- **STL integration**: Seamless use with algorithms
- **Type deduction**: Automatic type inference
- **Performance**: Compiler optimization opportunities

Use lambdas for:
- Simple, one-off operations
- STL algorithm predicates
- Capturing local context
- Callback functions
- Custom comparators

Consider alternatives when:
- Logic is complex or long
- Function needs to be reused
- Multiple similar lambdas exist
- Lambda body exceeds a few lines

Lambda expressions are a powerful tool that makes C++ code more expressive and maintainable when used appropriately.
