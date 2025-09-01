# 🚀 C++ Templates: Complete Guide

## 📚 Overview

Templates are one of C++'s most powerful features, enabling generic programming. They allow you to write code that works with different data types without duplicating code, making your programs more flexible and maintainable.

## 🎯 Key Concepts

### What are Templates?
- **Generic programming**: Write code once, use with multiple types
- **Compile-time polymorphism**: Type resolution happens during compilation
- **Code reuse**: Avoid duplicating similar functions/classes for different types
- **Type safety**: Compiler ensures type consistency

### Template Types
- **Function templates**: Generic functions that work with any type
- **Class templates**: Generic classes that can hold any type
- **Variable templates**: Generic variables (C++14+)
- **Alias templates**: Type aliases for templates (C++11+)

## 🔧 Function Templates

### Basic Function Template
```cpp
#include <iostream>
using namespace std;

// Function template for finding maximum of two values
template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// Function template for swapping two values
template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// Function template for printing any type
template<typename T>
void print(const T& value) {
    cout << "Value: " << value << endl;
}

int main() {
    // Use with different types
    cout << "Max of 5 and 10: " << maximum(5, 10) << endl;
    cout << "Max of 3.14 and 2.71: " << maximum(3.14, 2.71) << endl;
    cout << "Max of 'a' and 'z': " << maximum('a', 'z') << endl;
    
    // Swapping
    int x = 5, y = 10;
    swap(x, y);
    cout << "After swap: x=" << x << ", y=" << y << endl;
    
    // Printing
    print(42);
    print("Hello");
    print(3.14159);
    
    return 0;
}
```

### Multiple Type Parameters
```cpp
// Template with multiple type parameters
template<typename T1, typename T2>
void printPair(const T1& first, const T2& second) {
    cout << "First: " << first << ", Second: " << second << endl;
}

// Template with mixed types
template<typename T1, typename T2>
T1 convert(const T2& value) {
    return static_cast<T1>(value);
}

int main() {
    printPair(42, "Hello");
    printPair(3.14, true);
    
    double d = convert<double>(42);      // int to double
    int i = convert<int>(3.14159);       // double to int
    
    return 0;
}
```

### Template Specialization
```cpp
// Primary template
template<typename T>
T absolute(T value) {
    return (value < 0) ? -value : value;
}

// Specialization for int
template<>
int absolute<int>(int value) {
    return abs(value);  // Use std::abs for int
}

// Specialization for double
template<>
double absolute<double>(double value) {
    return fabs(value);  // Use std::fabs for double
}

int main() {
    cout << "Absolute of -5: " << absolute(-5) << endl;
    cout << "Absolute of -3.14: " << absolute(-3.14) << endl;
    cout << "Absolute of -10: " << absolute(-10) << endl;
    
    return 0;
}
```

### Template Overloading
```cpp
// Primary template
template<typename T>
void process(T value) {
    cout << "Generic process: " << value << endl;
}

// Overloaded template for pointers
template<typename T>
void process(T* value) {
    cout << "Pointer process: " << *value << endl;
}

// Overloaded template for arrays
template<typename T, size_t N>
void process(T (&array)[N]) {
    cout << "Array process with " << N << " elements" << endl;
}

// Non-template function (exact match preferred)
void process(int value) {
    cout << "Int process: " << value << endl;
}

int main() {
    int x = 42;
    int arr[] = {1, 2, 3, 4, 5};
    
    process(x);        // Calls non-template function
    process(&x);       // Calls pointer template
    process(arr);      // Calls array template
    process(3.14);     // Calls generic template
    
    return 0;
}
```

## 🏗️ Class Templates

### Basic Class Template
```cpp
#include <iostream>
#include <vector>
using namespace std;

// Template class for a generic container
template<typename T>
class Container {
private:
    vector<T> data;
    
public:
    // Constructor
    Container() = default;
    
    // Add element
    void add(const T& item) {
        data.push_back(item);
    }
    
    // Remove element
    void remove(const T& item) {
        auto it = find(data.begin(), data.end(), item);
        if (it != data.end()) {
            data.erase(it);
        }
    }
    
    // Get element at index
    T& at(size_t index) {
        if (index < data.size()) {
            return data[index];
        }
        throw out_of_range("Index out of range");
    }
    
    // Get size
    size_t size() const {
        return data.size();
    }
    
    // Check if empty
    bool empty() const {
        return data.empty();
    }
    
    // Display all elements
    void display() const {
        cout << "Container contents: ";
        for (const auto& item : data) {
            cout << item << " ";
        }
        cout << endl;
    }
};

int main() {
    // Container of integers
    Container<int> intContainer;
    intContainer.add(10);
    intContainer.add(20);
    intContainer.add(30);
    intContainer.display();
    
    // Container of strings
    Container<string> stringContainer;
    stringContainer.add("Hello");
    stringContainer.add("World");
    stringContainer.display();
    
    // Container of doubles
    Container<double> doubleContainer;
    doubleContainer.add(3.14);
    doubleContainer.add(2.71);
    doubleContainer.display();
    
    return 0;
}
```

### Template Class with Multiple Parameters
```cpp
// Template class with multiple type parameters
template<typename T, typename U>
class Pair {
private:
    T first;
    U second;
    
public:
    // Constructor
    Pair(const T& f, const U& s) : first(f), second(s) {}
    
    // Getters
    T getFirst() const { return first; }
    U getSecond() const { return second; }
    
    // Setters
    void setFirst(const T& f) { first = f; }
    void setSecond(const U& s) { second = s; }
    
    // Display
    void display() const {
        cout << "(" << first << ", " << second << ")" << endl;
    }
};

// Template class with non-type parameters
template<typename T, size_t N>
class Array {
private:
    T data[N];
    
public:
    // Constructor
    Array() {
        for (size_t i = 0; i < N; i++) {
            data[i] = T{};  // Default initialization
        }
    }
    
    // Access element
    T& operator[](size_t index) {
        if (index >= N) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    // Const access
    const T& operator[](size_t index) const {
        if (index >= N) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    // Get size
    size_t size() const { return N; }
    
    // Fill with value
    void fill(const T& value) {
        for (size_t i = 0; i < N; i++) {
            data[i] = value;
        }
    }
};

int main() {
    // Pair with different types
    Pair<int, string> pair1(42, "Hello");
    Pair<double, char> pair2(3.14, 'A');
    
    pair1.display();
    pair2.display();
    
    // Fixed-size arrays
    Array<int, 5> intArray;
    Array<string, 3> stringArray;
    
    intArray[0] = 10;
    intArray[1] = 20;
    stringArray[0] = "First";
    
    cout << "Int array size: " << intArray.size() << endl;
    cout << "String array size: " << stringArray.size() << endl;
    
    return 0;
}
```

### Template Class Specialization
```cpp
// Primary template
template<typename T>
class Storage {
private:
    T value;
    
public:
    Storage(const T& v) : value(v) {}
    
    void display() const {
        cout << "Generic storage: " << value << endl;
    }
    
    T getValue() const { return value; }
};

// Specialization for bool
template<>
class Storage<bool> {
private:
    bool value;
    
public:
    Storage(bool v) : value(v) {}
    
    void display() const {
        cout << "Boolean storage: " << (value ? "true" : "false") << endl;
    }
    
    bool getValue() const { return value; }
    
    // Special method for bool
    void toggle() {
        value = !value;
    }
};

// Partial specialization for pointers
template<typename T>
class Storage<T*> {
private:
    T* value;
    
public:
    Storage(T* v) : value(v) {}
    
    void display() const {
        if (value) {
            cout << "Pointer storage: " << *value << endl;
        } else {
            cout << "Pointer storage: null" << endl;
        }
    }
    
    T* getValue() const { return value; }
    
    // Special method for pointers
    void setValue(T* v) { value = v; }
};

int main() {
    Storage<int> intStorage(42);
    Storage<bool> boolStorage(true);
    Storage<string> stringStorage("Hello");
    
    int x = 100;
    Storage<int*> ptrStorage(&x);
    
    intStorage.display();
    boolStorage.display();
    stringStorage.display();
    ptrStorage.display();
    
    boolStorage.toggle();
    boolStorage.display();
    
    return 0;
}
```

## 🚀 Advanced Template Features

### Template Metaprogramming
```cpp
// Compile-time factorial calculation
template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};

// Base case
template<>
struct Factorial<0> {
    static constexpr int value = 1;
};

// Compile-time Fibonacci
template<int N>
struct Fibonacci {
    static constexpr int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

// Base cases
template<>
struct Fibonacci<0> {
    static constexpr int value = 0;
};

template<>
struct Fibonacci<1> {
    static constexpr int value = 1;
};

// Type traits
template<typename T>
struct IsPointer {
    static constexpr bool value = false;
};

template<typename T>
struct IsPointer<T*> {
    static constexpr bool value = true;
};

int main() {
    cout << "Factorial of 5: " << Factorial<5>::value << endl;
    cout << "Fibonacci of 10: " << Fibonacci<10>::value << endl;
    
    cout << "Is int a pointer? " << (IsPointer<int>::value ? "Yes" : "No") << endl;
    cout << "Is int* a pointer? " << (IsPointer<int*>::value ? "Yes" : "No") << endl;
    
    return 0;
}
```

### Variable Templates (C++14+)
```cpp
// Variable template for mathematical constants
template<typename T>
constexpr T PI = T(3.14159265358979323846);

template<typename T>
constexpr T E = T(2.71828182845904523536);

// Variable template for type sizes
template<typename T>
constexpr size_t type_size = sizeof(T);

int main() {
    cout << "PI (double): " << PI<double> << endl;
    cout << "PI (float): " << PI<float> << endl;
    cout << "E (double): " << E<double> << endl;
    
    cout << "Size of int: " << type_size<int> << " bytes" << endl;
    cout << "Size of double: " << type_size<double> << " bytes" << endl;
    cout << "Size of string: " << type_size<string> << " bytes" << endl;
    
    return 0;
}
```

### Alias Templates (C++11+)
```cpp
// Alias for vector of specific type
template<typename T>
using Vector = std::vector<T>;

// Alias for map with specific key type
template<typename T>
using StringMap = std::map<std::string, T>;

// Alias for function pointer
template<typename T>
using FunctionPtr = T(*)(T, T);

// Alias for smart pointer
template<typename T>
using UniquePtr = std::unique_ptr<T>;

int main() {
    Vector<int> numbers = {1, 2, 3, 4, 5};
    StringMap<int> scores;
    scores["Alice"] = 95;
    scores["Bob"] = 87;
    
    FunctionPtr<int> add = [](int a, int b) { return a + b; };
    cout << "5 + 3 = " << add(5, 3) << endl;
    
    UniquePtr<int> ptr = std::make_unique<int>(42);
    cout << "Value: " << *ptr << endl;
    
    return 0;
}
```

### Concepts (C++20)
```cpp
// Concept definition (C++20)
template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<typename T>
concept Printable = requires(T t) {
    { std::cout << t } -> std::convertible_to<std::ostream&>;
};

// Function using concepts
template<Numeric T>
T add(T a, T b) {
    return a + b;
}

template<Printable T>
void print(const T& value) {
    std::cout << value << std::endl;
}

// Class using concepts
template<Numeric T>
class Calculator {
private:
    T value;
    
public:
    Calculator(T v) : value(v) {}
    
    T getValue() const { return value; }
    
    void add(T other) { value += other; }
    void subtract(T other) { value -= other; }
    void multiply(T other) { value *= other; }
    void divide(T other) { 
        if (other != T{}) value /= other; 
    }
};

int main() {
    // These work with concepts
    cout << add(5, 3) << endl;
    cout << add(3.14, 2.71) << endl;
    
    print("Hello");
    print(42);
    
    Calculator<int> calc(10);
    calc.add(5);
    cout << "Result: " << calc.getValue() << endl;
    
    return 0;
}
```

## 📝 Best Practices

### 1. Use Meaningful Template Names
```cpp
// Good: Clear, descriptive names
template<typename ElementType>
class Container { /* ... */ };

template<typename KeyType, typename ValueType>
class Dictionary { /* ... */ };

// Bad: Unclear names
template<typename T>
class Container { /* ... */ };

template<typename K, typename V>
class Dict { /* ... */ };
```

### 2. Provide Default Template Arguments
```cpp
// Good: Provide sensible defaults
template<typename T = int, size_t N = 10>
class Array { /* ... */ };

template<typename T = string>
class Logger { /* ... */ };

// Usage
Array<> defaultArray;        // Array<int, 10>
Array<double> doubleArray;   // Array<double, 10>
Array<string, 5> strArray;  // Array<string, 5>
```

### 3. Use Type Constraints
```cpp
// Good: Constrain template types
template<typename T>
requires std::is_arithmetic_v<T>
T absolute(T value) {
    return (value < 0) ? -value : value;
}

// Or use concepts (C++20)
template<std::integral T>
T factorial(T n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
```

### 4. Avoid Template Code Bloat
```cpp
// Good: Separate implementation
template<typename T>
class Container {
    // ... interface ...
private:
    void internalMethod();  // Declaration only
};

// Implementation in separate file
template<typename T>
void Container<T>::internalMethod() {
    // Implementation
}

// Bad: All code in header (can cause bloat)
template<typename T>
class Container {
    // ... all implementation here ...
};
```

## 🎯 Practice Problems

### Problem 1: Generic Stack
```cpp
template<typename T>
class Stack {
private:
    vector<T> data;
    
public:
    void push(const T& item) {
        data.push_back(item);
    }
    
    T pop() {
        if (data.empty()) {
            throw runtime_error("Stack is empty");
        }
        T item = data.back();
        data.pop_back();
        return item;
    }
    
    T peek() const {
        if (data.empty()) {
            throw runtime_error("Stack is empty");
        }
        return data.back();
    }
    
    bool empty() const { return data.empty(); }
    size_t size() const { return data.size(); }
};
```

### Problem 2: Generic Binary Search Tree
```cpp
template<typename T>
class TreeNode {
public:
    T data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

template<typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root;
    
    TreeNode<T>* insert(TreeNode<T>* node, const T& value) {
        if (!node) {
            return new TreeNode<T>(value);
        }
        
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        
        return node;
    }
    
    void inorder(TreeNode<T>* node) const {
        if (node) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }
    
public:
    BinarySearchTree() : root(nullptr) {}
    
    void insert(const T& value) {
        root = insert(root, value);
    }
    
    void display() const {
        inorder(root);
        cout << endl;
    }
};
```

### Problem 3: Generic Sort Function
```cpp
template<typename T, typename Compare = std::less<T>>
void bubbleSort(vector<T>& arr, Compare comp = Compare{}) {
    int n = arr.size();
    bool swapped;
    
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (comp(arr[j + 1], arr[j])) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Usage with custom comparator
struct Person {
    string name;
    int age;
    
    bool operator<(const Person& other) const {
        return age < other.age;
    }
};

int main() {
    vector<int> numbers = {64, 34, 25, 12, 22, 11, 90};
    bubbleSort(numbers);
    
    vector<Person> people = {{"Alice", 25}, {"Bob", 30}, {"Charlie", 20}};
    bubbleSort(people);
    
    return 0;
}
```

## 📚 Summary

Key takeaways:
- **Templates enable generic programming** and code reuse
- **Function templates** work with any compatible type
- **Class templates** create generic data structures
- **Template specialization** allows custom behavior for specific types
- **Use concepts and constraints** to ensure type safety
- **Follow best practices** to avoid code bloat and maintain readability

Master templates to write flexible, reusable, and efficient C++ code!

---

## 🔗 Related Topics
- [Functions](functions.md)
- [Object-Oriented Programming](oop-concepts.md)
- [STL Containers](stl-containers.md)
- [STL Algorithms](stl-algorithms.md)
