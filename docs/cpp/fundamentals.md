# C++ Fundamentals

## Overview

C++ fundamentals form the foundation of C++ programming. This section covers the essential concepts, syntax, and features that every C++ programmer must understand to write effective and efficient code.

## Basic Syntax and Structure

### Hello World Program

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```

### Program Structure

```cpp
// Preprocessor directives
#include <iostream>
#include <vector>
#include <string>

// Using declarations
using namespace std;

// Global constants
const int MAX_SIZE = 100;
const double PI = 3.14159;

// Function declarations
void printMessage(const string& message);
int calculateSum(int a, int b);

// Main function
int main() {
    // Program logic here
    printMessage("Welcome to C++!");
    int result = calculateSum(5, 3);
    cout << "Sum: " << result << endl;
    
    return 0;
}

// Function definitions
void printMessage(const string& message) {
    cout << message << endl;
}

int calculateSum(int a, int b) {
    return a + b;
}
```

## Variables and Data Types

### Basic Data Types

```cpp
#include <iostream>
#include <limits>

int main() {
    // Integer types
    char character = 'A';                    // 1 byte, -128 to 127
    short shortNum = 32767;                 // 2 bytes, -32,768 to 32,767
    int integer = 2147483647;               // 4 bytes, -2^31 to 2^31-1
    long longNum = 2147483647L;             // 4+ bytes, -2^31 to 2^31-1
    long long longLongNum = 9223372036854775807LL; // 8 bytes, -2^63 to 2^63-1
    
    // Floating-point types
    float floatNum = 3.14f;                 // 4 bytes, 6-7 decimal digits
    double doubleNum = 3.14159265359;       // 8 bytes, 15-17 decimal digits
    long double longDoubleNum = 3.14159265359L; // 10+ bytes, 19+ decimal digits
    
    // Boolean type
    bool boolean = true;                     // 1 byte, true or false
    
    // Void type (no value)
    void* pointer = nullptr;                // Pointer to void
    
    // Display size and limits
    cout << "Size of int: " << sizeof(int) << " bytes" << endl;
    cout << "Maximum int value: " << numeric_limits<int>::max() << endl;
    cout << "Minimum int value: " << numeric_limits<int>::min() << endl;
    
    return 0;
}
```

### Type Modifiers

```cpp
#include <iostream>

int main() {
    // Signed and unsigned
    signed int signedInt = -100;             // Can be negative
    unsigned int unsignedInt = 100;          // Only positive values
    
    // Size modifiers
    short int shortInt = 100;               // Short integer
    long int longInt = 1000000L;            // Long integer
    
    // Combined modifiers
    unsigned short int unsignedShort = 100;  // Unsigned short
    signed long int signedLong = -1000000L;  // Signed long
    
    // Type aliases using typedef
    typedef unsigned long long ULL;
    ULL bigNumber = 18446744073709551615ULL;
    
    // Type aliases using using (C++11)
    using BigInt = unsigned long long;
    BigInt anotherBigNumber = 18446744073709551615ULL;
    
    return 0;
}
```

### Variable Declaration and Initialization

```cpp
#include <iostream>
#include <string>

int main() {
    // Different ways to initialize variables
    
    // Copy initialization
    int a = 10;
    double b = 3.14;
    std::string str = "Hello";
    
    // Direct initialization
    int c(20);
    double d(2.718);
    
    // Brace initialization (C++11) - preferred
    int e{30};
    double f{1.414};
    std::string g{"World"};
    
    // Auto keyword (C++11) - type deduction
    auto autoInt = 42;                      // Deduced as int
    auto autoDouble = 3.14159;              // Deduced as double
    auto autoString = "Auto string";        // Deduced as const char*
    
    // Multiple variable declaration
    int x = 1, y = 2, z = 3;
    
    // Const variables
    const int MAX_VALUE = 100;
    const double GRAVITY = 9.81;
    
    // Constexpr (C++11) - compile-time constants
    constexpr int ARRAY_SIZE = 100;
    constexpr double PI = 3.14159;
    
    return 0;
}
```

## Control Flow

### Conditional Statements

```cpp
#include <iostream>

int main() {
    int age = 18;
    
    // If statement
    if (age >= 18) {
        std::cout << "You are an adult." << std::endl;
    }
    
    // If-else statement
    if (age >= 18) {
        std::cout << "You are an adult." << std::endl;
    } else {
        std::cout << "You are a minor." << std::endl;
    }
    
    // If-else if-else statement
    if (age < 13) {
        std::cout << "You are a child." << std::endl;
    } else if (age < 18) {
        std::cout << "You are a teenager." << std::endl;
    } else if (age < 65) {
        std::cout << "You are an adult." << std::endl;
    } else {
        std::cout << "You are a senior." << std::endl;
    }
    
    // Conditional operator (ternary operator)
    std::string status = (age >= 18) ? "adult" : "minor";
    std::cout << "Status: " << status << std::endl;
    
    // Switch statement
    int day = 3;
    switch (day) {
        case 1:
            std::cout << "Monday" << std::endl;
            break;
        case 2:
            std::cout << "Tuesday" << std::endl;
            break;
        case 3:
            std::cout << "Wednesday" << std::endl;
            break;
        default:
            std::cout << "Other day" << std::endl;
            break;
    }
    
    return 0;
}
```

### Loops

```cpp
#include <iostream>
#include <vector>

int main() {
    // For loop
    for (int i = 0; i < 5; ++i) {
        std::cout << "For loop iteration: " << i << std::endl;
    }
    
    // Range-based for loop (C++11)
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    for (const auto& num : numbers) {
        std::cout << "Number: " << num << std::endl;
    }
    
    // While loop
    int count = 0;
    while (count < 3) {
        std::cout << "While loop iteration: " << count << std::endl;
        ++count;
    }
    
    // Do-while loop
    int value = 0;
    do {
        std::cout << "Do-while iteration: " << value << std::endl;
        ++value;
    } while (value < 3);
    
    // Loop control statements
    for (int i = 0; i < 10; ++i) {
        if (i == 5) {
            continue;  // Skip this iteration
        }
        if (i == 8) {
            break;     // Exit the loop
        }
        std::cout << "i = " << i << std::endl;
    }
    
    // Nested loops
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            std::cout << "(" << i << "," << j << ") ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
```

## Functions

### Function Basics

```cpp
#include <iostream>
#include <string>

// Function declaration (prototype)
int add(int a, int b);
void printMessage(const std::string& message);
double calculateArea(double radius);
int factorial(int n);

int main() {
    // Function calls
    int sum = add(5, 3);
    std::cout << "Sum: " << sum << std::endl;
    
    printMessage("Hello from function!");
    
    double area = calculateArea(5.0);
    std::cout << "Area: " << area << std::endl;
    
    int fact = factorial(5);
    std::cout << "5! = " << fact << std::endl;
    
    return 0;
}

// Function definitions
int add(int a, int b) {
    return a + b;
}

void printMessage(const std::string& message) {
    std::cout << message << std::endl;
}

double calculateArea(double radius) {
    const double PI = 3.14159;
    return PI * radius * radius;
}

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}
```

### Function Overloading

```cpp
#include <iostream>
#include <string>

// Function overloading - same name, different parameters
int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

std::string add(const std::string& a, const std::string& b) {
    return a + b;
}

int add(int a, int b, int c) {
    return a + b + c;
}

int main() {
    std::cout << "add(5, 3) = " << add(5, 3) << std::endl;           // int version
    std::cout << "add(3.14, 2.86) = " << add(3.14, 2.86) << std::endl; // double version
    std::cout << "add(\"Hello\", \" World\") = " << add("Hello", " World") << std::endl; // string version
    std::cout << "add(1, 2, 3) = " << add(1, 2, 3) << std::endl;     // three ints version
    
    return 0;
}
```

### Default Parameters

```cpp
#include <iostream>
#include <string>

// Function with default parameters
void printInfo(const std::string& name, int age = 25, const std::string& city = "Unknown") {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "City: " << city << std::endl;
    std::cout << "---" << std::endl;
}

int main() {
    // Different ways to call the function
    printInfo("Alice");                    // Uses default age and city
    printInfo("Bob", 30);                  // Uses default city
    printInfo("Charlie", 35, "New York");  // All parameters specified
    
    return 0;
}
```

### Inline Functions

```cpp
#include <iostream>

// Inline function - compiler may inline the function call
inline int square(int x) {
    return x * x;
}

// Inline function with multiple statements
inline void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int num = 5;
    std::cout << "Square of " << num << " is " << square(num) << std::endl;
    
    int x = 10, y = 20;
    std::cout << "Before swap: x = " << x << ", y = " << y << std::endl;
    swap(x, y);
    std::cout << "After swap: x = " << x << ", y = " << y << std::endl;
    
    return 0;
}
```

## Arrays and Vectors

### Arrays

```cpp
#include <iostream>
#include <algorithm>

int main() {
    // Array declaration and initialization
    int numbers[5] = {1, 2, 3, 4, 5};
    
    // Array without size (deduced from initializer)
    int scores[] = {85, 92, 78, 96, 88};
    
    // Array with partial initialization
    int partial[5] = {1, 2};  // Rest are initialized to 0
    
    // Accessing array elements
    std::cout << "First element: " << numbers[0] << std::endl;
    std::cout << "Last element: " << numbers[4] << std::endl;
    
    // Modifying array elements
    numbers[2] = 10;
    std::cout << "Modified element: " << numbers[2] << std::endl;
    
    // Array traversal
    std::cout << "Array elements: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;
    
    // Range-based for loop with arrays
    std::cout << "Using range-based for: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Array size
    int size = sizeof(numbers) / sizeof(numbers[0]);
    std::cout << "Array size: " << size << std::endl;
    
    // Sorting array
    std::sort(numbers, numbers + 5);
    std::cout << "Sorted array: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

### Vectors

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // Vector declaration and initialization
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Empty vector
    std::vector<int> emptyVector;
    
    // Vector with size and default value
    std::vector<int> sizedVector(5, 0);  // 5 elements, all 0
    
    // Adding elements
    numbers.push_back(6);
    numbers.push_back(7);
    
    // Inserting elements
    numbers.insert(numbers.begin() + 2, 10);  // Insert 10 at index 2
    
    // Accessing elements
    std::cout << "First element: " << numbers[0] << std::endl;
    std::cout << "Last element: " << numbers.back() << std::endl;
    std::cout << "Element at index 2: " << numbers.at(2) << std::endl;
    
    // Vector size and capacity
    std::cout << "Size: " << numbers.size() << std::endl;
    std::cout << "Capacity: " << numbers.capacity() << std::endl;
    std::cout << "Empty: " << (numbers.empty() ? "Yes" : "No") << std::endl;
    
    // Iterating through vector
    std::cout << "Vector elements: ";
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;
    
    // Range-based for loop
    std::cout << "Using range-based for: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Using iterators
    std::cout << "Using iterators: ";
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Sorting vector
    std::sort(numbers.begin(), numbers.end());
    std::cout << "Sorted vector: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Removing elements
    numbers.pop_back();  // Remove last element
    numbers.erase(numbers.begin() + 1);  // Remove element at index 1
    
    // Clearing vector
    numbers.clear();
    std::cout << "After clear, size: " << numbers.size() << std::endl;
    
    return 0;
}
```

## Strings

### String Basics

```cpp
#include <iostream>
#include <string>

int main() {
    // String declaration and initialization
    std::string str1 = "Hello";
    std::string str2("World");
    std::string str3(5, 'A');  // 5 copies of 'A'
    
    // String concatenation
    std::string result = str1 + " " + str2;
    std::cout << "Concatenated: " << result << std::endl;
    
    // String length
    std::cout << "Length of str1: " << str1.length() << std::endl;
    std::cout << "Length of str1: " << str1.size() << std::endl;
    
    // Accessing characters
    std::cout << "First character: " << str1[0] << std::endl;
    std::cout << "Last character: " << str1.back() << std::endl;
    std::cout << "Character at index 2: " << str1.at(2) << std::endl;
    
    // String comparison
    if (str1 == str2) {
        std::cout << "Strings are equal" << std::endl;
    } else {
        std::cout << "Strings are not equal" << std::endl;
    }
    
    // String methods
    std::string text = "Hello World";
    
    // Substring
    std::string sub = text.substr(0, 5);  // "Hello"
    std::cout << "Substring: " << sub << std::endl;
    
    // Find
    size_t pos = text.find("World");
    if (pos != std::string::npos) {
        std::cout << "Found 'World' at position: " << pos << std::endl;
    }
    
    // Replace
    text.replace(6, 5, "C++");
    std::cout << "After replace: " << text << std::endl;
    
    // Insert
    text.insert(5, " Beautiful ");
    std::cout << "After insert: " << text << std::endl;
    
    // Erase
    text.erase(5, 10);
    std::cout << "After erase: " << text << std::endl;
    
    // String iteration
    std::cout << "Characters: ";
    for (char c : text) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
    
    // String conversion
    std::string numberStr = "42";
    int number = std::stoi(numberStr);
    std::cout << "Converted number: " << number << std::endl;
    
    // Number to string
    std::string numStr = std::to_string(123);
    std::cout << "Number as string: " << numStr << std::endl;
    
    return 0;
}
```

## Basic I/O

### Input/Output Operations

```cpp
#include <iostream>
#include <iomanip>
#include <string>

int main() {
    // Basic output
    std::cout << "Hello, World!" << std::endl;
    
    // Multiple outputs
    std::cout << "Name: " << "John" << ", Age: " << 25 << std::endl;
    
    // Input
    std::string name;
    int age;
    
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    
    std::cout << "Enter your age: ";
    std::cin >> age;
    
    std::cout << "Hello, " << name << "! You are " << age << " years old." << std::endl;
    
    // Formatting output
    double pi = 3.14159;
    
    // Set precision
    std::cout << "Pi with 2 decimal places: " << std::fixed << std::setprecision(2) << pi << std::endl;
    
    // Set width and fill
    std::cout << "Pi with width 10: " << std::setw(10) << std::setfill('*') << pi << std::endl;
    
    // Left and right alignment
    std::cout << std::left << std::setw(10) << "Left" << std::endl;
    std::cout << std::right << std::setw(10) << "Right" << std::endl;
    
    // Boolean output
    bool flag = true;
    std::cout << "Flag: " << std::boolalpha << flag << std::endl;
    
    // Hexadecimal and octal
    int num = 255;
    std::cout << "Decimal: " << num << std::endl;
    std::cout << "Hexadecimal: " << std::hex << num << std::endl;
    std::cout << "Octal: " << std::oct << num << std::endl;
    
    // Reset to decimal
    std::cout << std::dec;
    
    return 0;
}
```

## Summary

C++ fundamentals provide the essential building blocks for:

- **Basic syntax**: Program structure, variables, control flow
- **Data types**: Understanding memory representation and type safety
- **Functions**: Code organization and reuse
- **Arrays and vectors**: Data storage and manipulation
- **Strings**: Text processing and manipulation
- **I/O operations**: User interaction and data display

Key concepts:
- **Type safety**: C++ is strongly typed, preventing many runtime errors
- **Memory management**: Understanding how data is stored and accessed
- **Control flow**: Making decisions and repeating operations
- **Function design**: Creating reusable and maintainable code
- **Standard library**: Using built-in containers and algorithms

These fundamentals form the foundation for advanced C++ programming concepts and are essential for writing efficient, maintainable code.
