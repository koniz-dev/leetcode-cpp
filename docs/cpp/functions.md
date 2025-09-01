# 🚀 C++ Functions: Complete Guide

## 📚 Overview

Functions are the building blocks of C++ programs, allowing you to organize code into reusable, logical units. Understanding functions is crucial for writing clean, maintainable, and efficient code.

## 🎯 Key Concepts

### What are Functions?
- **Reusable code blocks** that perform specific tasks
- **Input parameters** for flexibility
- **Return values** for output
- **Function calls** to execute the code

### Function Components
```cpp
return_type function_name(parameter_list) {
    // Function body
    return value;
}
```

## 🔧 Basic Function Syntax

### Simple Function
```cpp
#include <iostream>
using namespace std;

// Function declaration (prototype)
int add(int a, int b);

// Function definition
int add(int a, int b) {
    return a + b;
}

int main() {
    int result = add(5, 3);  // Function call
    cout << "Result: " << result << endl;
    return 0;
}
```

### Function Without Parameters
```cpp
void greet() {
    cout << "Hello, World!" << endl;
}

int main() {
    greet();  // Call function
    return 0;
}
```

### Function Without Return Value
```cpp
void printSum(int a, int b) {
    cout << "Sum: " << (a + b) << endl;
}

int main() {
    printSum(10, 20);
    return 0;
}
```

## 📥 Function Parameters

### Pass by Value
```cpp
void increment(int x) {
    x++;  // Local copy, original unchanged
    cout << "Inside function: " << x << endl;
}

int main() {
    int num = 5;
    increment(num);
    cout << "Original: " << num << endl;  // Still 5
    return 0;
}
```

### Pass by Reference
```cpp
void increment(int& x) {
    x++;  // Modifies original variable
    cout << "Inside function: " << x << endl;
}

int main() {
    int num = 5;
    increment(num);
    cout << "Original: " << num << endl;  // Now 6
    return 0;
}
```

### Pass by Const Reference
```cpp
void printValue(const int& x) {
    cout << "Value: " << x << endl;
    // x++;  // Error: can't modify const reference
}

int main() {
    int num = 42;
    printValue(num);
    return 0;
}
```

### Default Parameters
```cpp
void greet(string name = "User", string greeting = "Hello") {
    cout << greeting << ", " << name << "!" << endl;
}

int main() {
    greet();                    // "Hello, User!"
    greet("Alice");             // "Hello, Alice!"
    greet("Bob", "Hi");         // "Hi, Bob!"
    return 0;
}
```

## 🔄 Function Overloading

### Same Name, Different Parameters
```cpp
int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

string add(string a, string b) {
    return a + b;
}

int main() {
    cout << add(5, 3) << endl;           // 8
    cout << add(5.5, 3.2) << endl;      // 8.7
    cout << add("Hello", "World") << endl; // "HelloWorld"
    return 0;
}
```

### Overloading with Different Parameter Counts
```cpp
int sum(int a, int b) {
    return a + b;
}

int sum(int a, int b, int c) {
    return a + b + c;
}

int sum(int a, int b, int c, int d) {
    return a + b + c + d;
}
```

## 📤 Return Values

### Multiple Return Values (using references)
```cpp
void getMinMax(int arr[], int size, int& min, int& max) {
    min = max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
}

int main() {
    int numbers[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int min, max;
    getMinMax(numbers, 8, min, max);
    cout << "Min: " << min << ", Max: " << max << endl;
    return 0;
}
```

### Return by Reference
```cpp
int& getElement(int arr[], int index) {
    return arr[index];  // Return reference to array element
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int& element = getElement(numbers, 2);
    element = 100;  // Modifies the original array
    cout << "Modified: " << numbers[2] << endl;  // 100
    return 0;
}
```

## 🎭 Inline Functions

### Performance Optimization
```cpp
inline int square(int x) {
    return x * x;
}

int main() {
    int result = square(5);  // May be expanded inline
    cout << result << endl;
    return 0;
}
```

## 🔧 Function Best Practices

### 1. Clear Naming
```cpp
// Good
int calculateArea(int width, int height);
void validateUserInput(const string& input);

// Bad
int calc(int w, int h);
void val(const string& s);
```

### 2. Single Responsibility
```cpp
// Good: Each function has one clear purpose
int calculateArea(int width, int height) {
    return width * height;
}

void displayArea(int area) {
    cout << "Area: " << area << endl;
}

// Bad: Function does multiple things
void calculateAndDisplayArea(int width, int height) {
    int area = width * height;
    cout << "Area: " << area << endl;
    // More logic...
}
```

### 3. Const Correctness
```cpp
// Use const for parameters that shouldn't be modified
void printArray(const int arr[], int size);
void processString(const string& text);

// Use const for member functions that don't modify state
class Calculator {
public:
    int add(int a, int b) const;  // Won't modify object state
};
```

### 4. Error Handling
```cpp
bool divide(int a, int b, double& result) {
    if (b == 0) {
        return false;  // Error condition
    }
    result = static_cast<double>(a) / b;
    return true;  // Success
}

int main() {
    double result;
    if (divide(10, 2, result)) {
        cout << "Result: " << result << endl;
    } else {
        cout << "Error: Division by zero" << endl;
    }
    return 0;
}
```

## 🚀 Advanced Function Concepts

### Function Pointers
```cpp
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }

int main() {
    int (*operation)(int, int);  // Function pointer declaration
    
    operation = add;
    cout << "Add: " << operation(5, 3) << endl;  // 8
    
    operation = subtract;
    cout << "Subtract: " << operation(5, 3) << endl;  // 2
    
    operation = multiply;
    cout << "Multiply: " << operation(5, 3) << endl;  // 15
    
    return 0;
}
```

### Lambda Functions (C++11+)
```cpp
#include <vector>
#include <algorithm>

int main() {
    vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Lambda function to find even numbers
    auto isEven = [](int n) { return n % 2 == 0; };
    
    // Count even numbers
    int evenCount = count_if(numbers.begin(), numbers.end(), isEven);
    cout << "Even numbers: " << evenCount << endl;
    
    return 0;
}
```

## 📝 Common Pitfalls

### 1. Missing Return Statement
```cpp
int getValue(int x) {
    if (x > 0) {
        return x;  // Missing return for x <= 0 case
    }
    // Undefined behavior!
}

// Fix: Always provide return for all code paths
int getValue(int x) {
    if (x > 0) {
        return x;
    }
    return 0;  // Default return value
}
```

### 2. Reference to Local Variable
```cpp
int& getLocalReference() {
    int localVar = 42;
    return localVar;  // DANGER: Returning reference to local variable
}

// Fix: Return by value or ensure variable lives longer
int getLocalValue() {
    int localVar = 42;
    return localVar;  // Safe: Returns copy
}
```

### 3. Infinite Recursion
```cpp
int factorial(int n) {
    return n * factorial(n - 1);  // Missing base case!
}

// Fix: Always have base case
int factorial(int n) {
    if (n <= 1) return 1;  // Base case
    return n * factorial(n - 1);
}
```

## 🎯 Practice Problems

### Problem 1: Function to Check Prime
```cpp
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}
```

### Problem 2: Function to Reverse Array
```cpp
void reverseArray(int arr[], int size) {
    for (int i = 0; i < size / 2; i++) {
        swap(arr[i], arr[size - 1 - i]);
    }
}
```

### Problem 3: Function to Find GCD
```cpp
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
```

## 📚 Summary

Functions are essential for:
- **Code organization** and readability
- **Code reuse** and maintainability
- **Modular programming** design
- **Testing** individual components
- **Performance optimization** through inline functions

Master these concepts to write professional, efficient C++ code!

---

## 🔗 Related Topics
- [Control Flow](control-flow.md)
- [Arrays & Vectors](arrays-vectors.md)
- [Object-Oriented Programming](oop-concepts.md)
- [Templates](templates.md)
