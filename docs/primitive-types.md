# Primitive Data Types in C++

## Overview
Primitive data types are the basic types predefined in the C++ language.

## Integer Types

### int
- **Size**: Usually 4 bytes (32-bit)
- **Range**: -2,147,483,648 to 2,147,483,647
- **Usage**: Basic integers, array indices, counters

```cpp
int count = 0;
int index = 5;
int result = 42;
```

### long
- **Size**: Usually 8 bytes (64-bit)
- **Range**: -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
- **Usage**: Large integers, timestamps

```cpp
long timestamp = 1640995200L;
long largeNumber = 123456789012345L;
```

### long long
- **Size**: 8 bytes (64-bit)
- **Range**: -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
- **Usage**: Very large integers

```cpp
long long factorial = 1;
for (int i = 1; i <= 20; i++) {
    factorial *= i;
}
```

## Floating-Point Types

### float
- **Size**: 4 bytes
- **Precision**: ~7 decimal digits
- **Usage**: Low-precision floating-point numbers

```cpp
float pi = 3.14159f;
float temperature = 25.5f;
```

### double
- **Size**: 8 bytes
- **Precision**: ~15 decimal digits
- **Usage**: High-precision floating-point numbers

```cpp
double pi = 3.14159265359;
double distance = 123.456789;
```

## Character Type

### char
- **Size**: 1 byte
- **Range**: -128 to 127 or 0 to 255 (unsigned)
- **Usage**: Single characters, ASCII codes

```cpp
char grade = 'A';
char symbol = '+';
char digit = '5';
```

## Boolean Type

### bool
- **Size**: 1 byte
- **Values**: true or false
- **Usage**: Logical conditions, status flags

```cpp
bool isValid = true;
bool isFound = false;
bool hasPermission = (age >= 18);
```

## Unsigned Types

### unsigned int
- **Size**: 4 bytes
- **Range**: 0 to 4,294,967,295
- **Usage**: Non-negative integers

```cpp
unsigned int count = 0;
unsigned int size = 100;
```

### unsigned long
- **Size**: 8 bytes
- **Range**: 0 to 18,446,744,073,709,551,615
- **Usage**: Large non-negative integers

```cpp
unsigned long fileSize = 1234567890UL;
unsigned long memoryAddress = 0x7fff12345678UL;
```

## Type Modifiers

### const
- **Purpose**: Makes variables read-only
- **Usage**: Constants, function parameters

```cpp
const int MAX_SIZE = 100;
const double PI = 3.14159;

void processData(const std::vector<int>& data) {
    // Cannot modify data
}
```

### static
- **Purpose**: Variables with static storage duration
- **Usage**: Global variables, function-local static variables

```cpp
static int counter = 0;

void incrementCounter() {
    counter++;  // Persists between function calls
}
```

## Type Conversion

### Implicit Conversion
```cpp
int i = 42;
double d = i;  // int to double
char c = i;    // int to char (truncation)
```

### Explicit Conversion (Casting)
```cpp
double d = 3.14;
int i = static_cast<int>(d);  // 3

char c = 'A';
int ascii = static_cast<int>(c);  // 65
```

## Size and Limits

### sizeof Operator
```cpp
std::cout << "Size of int: " << sizeof(int) << " bytes" << std::endl;
std::cout << "Size of double: " << sizeof(double) << " bytes" << std::endl;
std::cout << "Size of char: " << sizeof(char) << " bytes" << std::endl;
```

### Numeric Limits
```cpp
#include <limits>

std::cout << "Max int: " << std::numeric_limits<int>::max() << std::endl;
std::cout << "Min int: " << std::numeric_limits<int>::min() << std::endl;
std::cout << "Max double: " << std::numeric_limits<double>::max() << std::endl;
```

## Best Practices

### 1. Choose Appropriate Types
```cpp
// ✅ Good - appropriate types
int age = 25;                    // int for age
double price = 19.99;           // double for price
bool isActive = true;           // bool for status
unsigned int count = 0;         // unsigned for non-negative

// ❌ Avoid - inappropriate types
double age = 25.0;              // double for age
int price = 1999;               // int for price (cents)
int isActive = 1;               // int for boolean
```

### 2. Use const for Constants
```cpp
// ✅ Good
const int MAX_RETRIES = 3;
const double TAX_RATE = 0.08;

// ❌ Avoid
int maxRetries = 3;  // Can be modified accidentally
```

### 3. Be Careful with Type Conversions
```cpp
// ✅ Good - explicit conversion
int result = static_cast<int>(3.14);

// ❌ Avoid - implicit conversion
int result = 3.14;  // Loss of precision
```

### 4. Use Appropriate Integer Types
```cpp
// ✅ Good - appropriate ranges
unsigned int arraySize = 1000;
long long factorial = 1;
int loopCounter = 0;

// ❌ Avoid - potential overflow
int factorial = 1;  // May overflow for large numbers
```

## Common Pitfalls

### 1. Integer Overflow
```cpp
int a = 2147483647;  // Max int
int b = a + 1;       // Undefined behavior
```

### 2. Floating-Point Precision
```cpp
double a = 0.1;
double b = 0.2;
double c = a + b;    // May not be exactly 0.3
```

### 3. Char vs Int
```cpp
char c = 'A';
int i = c;           // i = 65 (ASCII value)
char d = 65;         // d = 'A'
```

### 4. Boolean Conversion
```cpp
bool b1 = 1;         // true
bool b2 = 0;         // false
bool b3 = 42;        // true (non-zero)
bool b4 = -1;        // true (non-zero)
```
