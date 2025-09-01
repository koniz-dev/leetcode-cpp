# 🟢 C++ Basic Syntax & Structure

## 📚 Overview
C++ is a powerful, general-purpose programming language that supports multiple programming paradigms. This guide covers the fundamental syntax and structure you need to get started.

---

## 🏗️ Basic Program Structure

### Hello World Example
```cpp
#include <iostream>  // Include input/output stream library
using namespace std; // Use standard namespace

int main() {         // Main function - entry point
    cout << "Hello, World!" << endl;  // Output statement
    return 0;        // Return success status
}
```

### Key Components Explained
- **`#include`** - Preprocessor directive to include libraries
- **`using namespace std`** - Makes standard library accessible
- **`int main()`** - Main function, program entry point
- **`cout`** - Standard output stream
- **`<<`** - Stream insertion operator
- **`endl`** - End line and flush buffer
- **`return 0`** - Exit program successfully

---

## 📝 Basic Syntax Rules

### 1. Semicolons
Every statement must end with a semicolon `;`
```cpp
int x = 5;        // Correct
cout << "Hello";  // Correct
int y = 10        // ERROR: Missing semicolon
```

### 2. Braces `{}`
Used to define code blocks and scope
```cpp
if (condition) {
    // Code block
    statement1;
    statement2;
}
```

### 3. Comments
```cpp
// Single line comment

/*
Multi-line comment
Can span multiple lines
*/

/// Documentation comment (for tools like Doxygen)
```

---

## 🔤 Naming Conventions

### Variables & Functions
- Use descriptive names
- Start with letter or underscore
- Case sensitive
- Cannot use reserved keywords

```cpp
// Good naming
int userAge = 25;
string firstName = "John";
bool isActive = true;

// Avoid
int a = 25;           // Too short
string fn = "John";   // Abbreviation
bool flag = true;     // Unclear
```

### Constants
```cpp
const int MAX_SIZE = 100;        // Runtime constant
constexpr int ARRAY_SIZE = 50;   // Compile-time constant
#define PI 3.14159              // Preprocessor macro (avoid in modern C++)
```

---

## 📦 Basic Data Types

### Integer Types
```cpp
int number = 42;           // Usually 4 bytes
short small = 32767;       // 2 bytes
long big = 2147483647L;    // 4+ bytes
long long huge = 9223372036854775807LL; // 8 bytes
```

### Floating Point Types
```cpp
float pi = 3.14f;         // 4 bytes, 6-7 digits precision
double pi_double = 3.14159265359; // 8 bytes, 15-17 digits precision
long double pi_long = 3.14159265359L; // 10+ bytes
```

### Character Types
```cpp
char letter = 'A';         // 1 byte
wchar_t wide = L'Ω';      // Wide character
char16_t utf16 = u'字';    // UTF-16 character
char32_t utf32 = U'🌍';    // UTF-32 character
```

### Boolean Type
```cpp
bool isTrue = true;        // true (1) or false (0)
bool isFalse = false;
```

---

## 🔄 Variables & Assignment

### Declaration & Initialization
```cpp
// Declaration
int x;
int y, z;

// Initialization
int a = 10;           // Copy initialization
int b(20);            // Direct initialization
int c{30};            // Brace initialization (C++11)
int d = {40};         // Copy brace initialization

// Multiple declaration
int e = 50, f = 60, g = 70;
```

### Type Deduction (C++11+)
```cpp
auto number = 42;           // int
auto text = "Hello";        // const char*
auto flag = true;           // bool
auto pi = 3.14159;         // double

// With explicit type
auto value = int{100};      // int
```

---

## 📥📤 Input & Output

### Basic Output
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Text output" << endl;
    cout << "Number: " << 42 << endl;
    cout << "Multiple " << "values " << "in " << "one " << "line" << endl;
    
    return 0;
}
```

### Basic Input
```cpp
#include <iostream>
using namespace std;

int main() {
    int age;
    string name;
    
    cout << "Enter your name: ";
    cin >> name;
    
    cout << "Enter your age: ";
    cin >> age;
    
    cout << "Hello " << name << ", you are " << age << " years old!" << endl;
    
    return 0;
}
```

---

## 🎯 Common Pitfalls & Best Practices

### 1. Always Initialize Variables
```cpp
// Bad
int x;
cout << x << endl;  // Undefined behavior!

// Good
int x = 0;
cout << x << endl;  // Predictable output
```

### 2. Use Meaningful Names
```cpp
// Bad
int a, b, c;

// Good
int width, height, depth;
```

### 3. Avoid Magic Numbers
```cpp
// Bad
if (score >= 70) { ... }

// Good
const int PASSING_SCORE = 70;
if (score >= PASSING_SCORE) { ... }
```

### 4. Use Braces for All Control Structures
```cpp
// Bad
if (condition)
    statement;

// Good
if (condition) {
    statement;
}
```

---

## 🧪 Practice Examples

### Example 1: Simple Calculator
```cpp
#include <iostream>
using namespace std;

int main() {
    int num1, num2;
    
    cout << "Enter first number: ";
    cin >> num1;
    
    cout << "Enter second number: ";
    cin >> num2;
    
    cout << "Sum: " << num1 + num2 << endl;
    cout << "Difference: " << num1 - num2 << endl;
    cout << "Product: " << num1 * num2 << endl;
    
    if (num2 != 0) {
        cout << "Quotient: " << num1 / num2 << endl;
    } else {
        cout << "Cannot divide by zero!" << endl;
    }
    
    return 0;
}
```

### Example 2: Temperature Converter
```cpp
#include <iostream>
using namespace std;

int main() {
    double celsius, fahrenheit;
    
    cout << "Enter temperature in Celsius: ";
    cin >> celsius;
    
    fahrenheit = (celsius * 9.0 / 5.0) + 32.0;
    
    cout << celsius << "°C = " << fahrenheit << "°F" << endl;
    
    return 0;
}
```

---

## 📚 What's Next?

After mastering basic syntax, move on to:
1. **Control Flow** - if/else, loops, switch statements
2. **Functions** - Function definition, parameters, return values
3. **Arrays & Vectors** - Collections of data
4. **Strings** - Text manipulation

---

## 🔗 Related Topics
- [Variables & Data Types](data-types.md)
- [Control Flow](control-flow.md)
- [Functions](functions.md)
- [Arrays & Vectors](arrays-vectors.md)

---

*Remember: Practice is key! Write small programs to reinforce these concepts.*
