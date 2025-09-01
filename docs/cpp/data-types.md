# 🟢 C++ Data Types & Variables

## 📚 Overview
Data types define the kind of data a variable can hold and how much memory it occupies. Understanding data types is crucial for efficient programming and avoiding common pitfalls.

---

## 🔢 Integer Types

### Signed Integer Types
```cpp
char c = 127;              // 1 byte: -128 to 127
short s = 32767;           // 2 bytes: -32,768 to 32,767
int i = 2147483647;        // 4 bytes: -2,147,483,648 to 2,147,483,647
long l = 2147483647L;      // 4+ bytes: platform dependent
long long ll = 9223372036854775807LL; // 8 bytes: -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
```

### Unsigned Integer Types
```cpp
unsigned char uc = 255;           // 1 byte: 0 to 255
unsigned short us = 65535;        // 2 bytes: 0 to 65,535
unsigned int ui = 4294967295U;    // 4 bytes: 0 to 4,294,967,295
unsigned long ul = 4294967295UL;  // 4+ bytes: platform dependent
unsigned long long ull = 18446744073709551615ULL; // 8 bytes: 0 to 18,446,744,073,709,551,615
```

### Integer Literals
```cpp
int decimal = 42;         // Decimal
int octal = 052;          // Octal (starts with 0)
int hexadecimal = 0x2A;   // Hexadecimal (starts with 0x)
int binary = 0b101010;    // Binary (C++14, starts with 0b)

// Suffixes for type specification
long long big = 123456789LL;      // Long long
unsigned int positive = 42U;      // Unsigned
```

---

## 🔢 Floating Point Types

### Precision & Range
```cpp
float f = 3.14f;          // 4 bytes, ~6-7 decimal digits precision
double d = 3.14159265359; // 8 bytes, ~15-17 decimal digits precision
long double ld = 3.14159265359L; // 10+ bytes, platform dependent

// Scientific notation
float small = 1.23e-4f;   // 0.000123
double large = 1.23e+8;   // 123,000,000
```

### Floating Point Literals
```cpp
double pi = 3.14159;      // Default is double
float pi_f = 3.14159f;    // f suffix for float
long double pi_ld = 3.14159L; // L suffix for long double
```

---

## 🔤 Character Types

### Basic Characters
```cpp
char c = 'A';             // 1 byte, ASCII character
char newline = '\n';      // Escape sequence
char tab = '\t';          // Tab character
char quote = '\'';        // Single quote
char backslash = '\\';    // Backslash
```

### Wide Characters
```cpp
wchar_t wc = L'Ω';       // Wide character (2-4 bytes)
char16_t c16 = u'字';     // UTF-16 character (2 bytes)
char32_t c32 = U'🌍';     // UTF-32 character (4 bytes)
```

### Escape Sequences
```cpp
char newline = '\n';      // New line
char tab = '\t';          // Horizontal tab
char backspace = '\b';    // Backspace
char carriage = '\r';     // Carriage return
char formfeed = '\f';     // Form feed
char alert = '\a';        // Alert (bell)
char vertical = '\v';     // Vertical tab
char null = '\0';         // Null character
```

---

## ✅ Boolean Type

### Boolean Values
```cpp
bool isTrue = true;       // true (1)
bool isFalse = false;     // false (0)

// Boolean expressions
bool result = (5 > 3);    // true
bool check = (10 == 5);   // false
```

### Boolean Conversion
```cpp
// Non-zero values convert to true
bool b1 = 42;             // true
bool b2 = -1;             // true
bool b3 = 0;              // false

// Boolean to integer
int true_val = true;      // 1
int false_val = false;    // 0
```

---

## 🔄 Type Modifiers

### Size Modifiers
```cpp
short int small = 32767;      // Same as 'short'
long int big = 2147483647L;   // Same as 'long'
long long int huge = 9223372036854775807LL; // Same as 'long long'
```

### Sign Modifiers
```cpp
signed int si = -42;          // Same as 'int' (signed by default)
unsigned int ui = 42;         // Only positive values
```

---

## 🔀 Type Conversion

### Implicit Conversion (Coercion)
```cpp
int i = 42;
double d = i;             // int → double: 42.0
char c = 65;              // int → char: 'A'

double pi = 3.14159;
int rounded = pi;         // double → int: 3 (truncation)
```

### Explicit Conversion (Casting)
```cpp
// C-style cast (avoid in modern C++)
int x = (int)3.14;        // 3

// C++ style casts (preferred)
int y = static_cast<int>(3.14);      // 3
double z = static_cast<double>(42);  // 42.0

// Const cast
const int* ptr = &x;
int* non_const = const_cast<int*>(ptr);

// Reinterpret cast (dangerous!)
int* int_ptr = reinterpret_cast<int*>(0x1234);

// Dynamic cast (for polymorphic classes)
// BaseClass* base = dynamic_cast<BaseClass*>(derived_ptr);
```

---

## 📏 Size & Limits

### Sizeof Operator
```cpp
cout << "Size of char: " << sizeof(char) << " bytes" << endl;           // 1
cout << "Size of int: " << sizeof(int) << " bytes" << endl;             // 4
cout << "Size of double: " << sizeof(double) << " bytes" << endl;       // 8
cout << "Size of bool: " << sizeof(bool) << " bytes" << endl;           // 1

// Size of variables
int x = 42;
cout << "Size of x: " << sizeof x << " bytes" << endl;                  // 4
cout << "Size of x: " << sizeof(x) << " bytes" << endl;                 // 4
```

### Numeric Limits
```cpp
#include <limits>
#include <iostream>

cout << "INT_MAX: " << numeric_limits<int>::max() << endl;              // 2147483647
cout << "INT_MIN: " << numeric_limits<int>::min() << endl;              // -2147483648
cout << "UINT_MAX: " << numeric_limits<unsigned int>::max() << endl;    // 4294967295
cout << "DOUBLE_MAX: " << numeric_limits<double>::max() << endl;        // 1.79769e+308
cout << "DOUBLE_MIN: " << numeric_limits<double>::min() << endl;        // 2.22507e-308
```

---

## 🎯 Variable Declaration & Initialization

### Declaration Styles
```cpp
// C-style initialization
int x = 10;

// Constructor initialization
int y(20);

// Brace initialization (C++11) - preferred
int z{30};
int w = {40};

// Multiple declaration
int a = 1, b = 2, c = 3;

// Type deduction with auto (C++11)
auto number = 42;         // int
auto text = "Hello";      // const char*
auto flag = true;         // bool
```

### Initialization Best Practices
```cpp
// Always initialize variables
int uninitialized;        // BAD: contains garbage value
int initialized = 0;      // GOOD: predictable value

// Use brace initialization to catch narrowing conversions
int narrow{3.14};        // ERROR: narrowing conversion
int narrow_c = 3.14;     // OK: truncates to 3

// Initialize arrays
int arr[5] = {1, 2, 3, 4, 5};
int arr2[5] = {1, 2};    // Rest initialized to 0
```

---

## 🚨 Common Pitfalls

### 1. Integer Overflow
```cpp
int max_int = 2147483647;
max_int = max_int + 1;   // Overflow! Undefined behavior
cout << max_int << endl;  // Unpredictable result
```

### 2. Floating Point Precision
```cpp
double a = 0.1;
double b = 0.2;
double c = a + b;
cout << c << endl;        // Might not be exactly 0.3

// Better approach for money calculations
int cents = 10 + 20;      // 30 cents
double dollars = cents / 100.0; // 0.30 dollars
```

### 3. Char vs String
```cpp
char c = 'A';             // Single character
string s = "A";           // String (requires #include <string>)
```

### 4. Type Mismatch
```cpp
int x = 5;
double y = x / 2;         // Result: 2.0 (integer division)
double z = x / 2.0;       // Result: 2.5 (floating point division)
```

---

## 🧪 Practice Examples

### Example 1: Type Conversion Calculator
```cpp
#include <iostream>
#include <limits>
using namespace std;

int main() {
    cout << "=== Type Conversion Calculator ===" << endl;
    
    // Integer to different types
    int int_val = 42;
    cout << "Integer: " << int_val << endl;
    cout << "As double: " << static_cast<double>(int_val) << endl;
    cout << "As char: " << static_cast<char>(int_val) << endl;
    
    // Floating point to integer
    double double_val = 3.14159;
    cout << "\nDouble: " << double_val << endl;
    cout << "As int: " << static_cast<int>(double_val) << endl;
    
    // Size information
    cout << "\n=== Size Information ===" << endl;
    cout << "Size of int: " << sizeof(int) << " bytes" << endl;
    cout << "Size of double: " << sizeof(double) << " bytes" << endl;
    cout << "Size of char: " << sizeof(char) << " bytes" << endl;
    
    return 0;
}
```

### Example 2: Numeric Limits Checker
```cpp
#include <iostream>
#include <limits>
using namespace std;

int main() {
    cout << "=== Numeric Limits ===" << endl;
    
    cout << "Integer Limits:" << endl;
    cout << "  INT_MIN: " << numeric_limits<int>::min() << endl;
    cout << "  INT_MAX: " << numeric_limits<int>::max() << endl;
    
    cout << "\nUnsigned Integer Limits:" << endl;
    cout << "  UINT_MAX: " << numeric_limits<unsigned int>::max() << endl;
    
    cout << "\nFloating Point Limits:" << endl;
    cout << "  DOUBLE_MIN: " << numeric_limits<double>::min() << endl;
    cout << "  DOUBLE_MAX: " << numeric_limits<double>::max() << endl;
    
    return 0;
}
```

---

## 📚 What's Next?

After understanding data types, explore:
1. **Control Flow** - Making decisions and loops
2. **Functions** - Organizing code into reusable blocks
3. **Arrays & Vectors** - Working with collections
4. **Pointers & References** - Memory management

---

## 🔗 Related Topics
- [Basic Syntax & Structure](basic-syntax.md)
- [Control Flow](control-flow.md)
- [Functions](functions.md)
- [Arrays & Vectors](arrays-vectors.md)

---

*Remember: Choose the right data type for your needs. When in doubt, prefer clarity over optimization.*
