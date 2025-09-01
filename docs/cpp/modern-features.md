# Modern C++ Features

## Overview

Modern C++ (C++11 and beyond) introduces many powerful features that make the language more expressive, safer, and easier to use. These features improve performance, reduce boilerplate code, and enable new programming paradigms.

## C++11 Features

### Auto Keyword

```cpp
// Type deduction for variables
auto i = 42;                    // int
auto d = 3.14;                  // double
auto s = "hello";               // const char*
auto vec = std::vector<int>();  // std::vector<int>

// Type deduction in loops
std::vector<int> numbers = {1, 2, 3, 4, 5};
for (auto& num : numbers) {
    num *= 2;  // Modify in place
}

// Type deduction for function return types
auto multiply(int a, int b) -> int {
    return a * b;
}

// Lambda expressions
auto add = [](int a, int b) { return a + b; };
auto result = add(3, 4);  // 7
```

### Range-Based For Loop

```cpp
#include <vector>
#include <map>
#include <string>

// Simple iteration
std::vector<int> numbers = {1, 2, 3, 4, 5};
for (const auto& num : numbers) {
    std::cout << num << " ";
}

// Iterating over maps
std::map<std::string, int> scores = {{"Alice", 95}, {"Bob", 87}};
for (const auto& [name, score] : scores) {
    std::cout << name << ": " << score << std::endl;
}

// Modifying elements
for (auto& num : numbers) {
    num *= 2;
}

// Custom range-based for support
class NumberRange {
private:
    int start, end;
public:
    NumberRange(int s, int e) : start(s), end(e) {}
    
    class Iterator {
    private:
        int value;
    public:
        Iterator(int v) : value(v) {}
        int operator*() const { return value; }
        Iterator& operator++() { ++value; return *this; }
        bool operator!=(const Iterator& other) const { return value != other.value; }
    };
    
    Iterator begin() const { return Iterator(start); }
    Iterator end() const { return Iterator(end); }
};

// Usage
for (int num : NumberRange(1, 6)) {
    std::cout << num << " ";  // Prints: 1 2 3 4 5
}
```

### Lambda Expressions

```cpp
#include <algorithm>
#include <vector>
#include <functional>

std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Basic lambda
auto isEven = [](int n) { return n % 2 == 0; };
auto evenCount = std::count_if(numbers.begin(), numbers.end(), isEven);

// Lambda with capture
int threshold = 5;
auto aboveThreshold = [threshold](int n) { return n > threshold; };
auto aboveCount = std::count_if(numbers.begin(), numbers.end(), aboveThreshold);

// Lambda with reference capture
auto sum = 0;
std::for_each(numbers.begin(), numbers.end(), [&sum](int n) {
    sum += n;
});

// Lambda with mixed capture
auto multiplier = 2;
auto process = [multiplier, &sum](int n) mutable {
    sum += n * multiplier;
    multiplier++;  // Can modify captured by value
};

// Lambda with generic capture (C++14)
auto genericLambda = [](auto x, auto y) { return x + y; };
auto result1 = genericLambda(5, 3);      // int
auto result2 = genericLambda(3.14, 2.86); // double

// Lambda as function parameter
template<typename Func>
void applyToRange(const std::vector<int>& vec, Func func) {
    for (const auto& item : vec) {
        func(item);
    }
}

// Usage
applyToRange(numbers, [](int n) { std::cout << n << " "; });
```

### Smart Pointers

```cpp
#include <memory>
#include <iostream>

// unique_ptr - exclusive ownership
std::unique_ptr<int> ptr1 = std::make_unique<int>(42);
std::unique_ptr<int> ptr2 = std::move(ptr1);  // Transfer ownership

// unique_ptr with custom deleter
auto fileDeleter = [](FILE* f) { if (f) fclose(f); };
std::unique_ptr<FILE, decltype(fileDeleter)> file(nullptr, fileDeleter);

// shared_ptr - shared ownership
std::shared_ptr<int> shared1 = std::make_shared<int>(100);
std::shared_ptr<int> shared2 = shared1;  // Reference count increases
std::cout << "Use count: " << shared1.use_count() << std::endl;  // 2

// weak_ptr - non-owning reference
std::weak_ptr<int> weak = shared1;
if (auto locked = weak.lock()) {
    std::cout << "Value: " << *locked << std::endl;
}

// Smart pointer arrays
auto array_ptr = std::make_unique<int[]>(10);
array_ptr[0] = 42;

// Custom deleter for arrays
auto arrayDeleter = [](int* p) { delete[] p; };
std::unique_ptr<int, decltype(arrayDeleter)> custom_array(new int[5], arrayDeleter);
```

### Initializer Lists

```cpp
#include <vector>
#include <map>
#include <set>
#include <string>

// Container initialization
std::vector<int> vec = {1, 2, 3, 4, 5};
std::map<std::string, int> scores = {{"Alice", 95}, {"Bob", 87}};
std::set<int> unique_numbers = {1, 2, 2, 3, 3, 4};  // Duplicates removed

// Function parameters
void processNumbers(std::initializer_list<int> numbers) {
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
}

// Usage
processNumbers({10, 20, 30, 40});

// Custom initializer_list support
class NumberContainer {
private:
    std::vector<int> data;
public:
    NumberContainer(std::initializer_list<int> init) : data(init) {}
    
    void add(std::initializer_list<int> values) {
        data.insert(data.end(), values.begin(), values.end());
    }
    
    void print() const {
        for (const auto& num : data) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
};

// Usage
NumberContainer container = {1, 2, 3};
container.add({4, 5, 6});
container.print();  // 1 2 3 4 5 6
```

## C++14 Features

### Generic Lambdas

```cpp
#include <iostream>
#include <string>
#include <vector>

// Generic lambda with auto parameters
auto print = [](const auto& item) {
    std::cout << item << std::endl;
};

// Usage with different types
print(42);           // int
print(3.14);         // double
print("hello");      // const char*

// Generic lambda with multiple auto parameters
auto add = [](const auto& a, const auto& b) {
    return a + b;
};

// Usage
auto result1 = add(5, 3);        // int + int
auto result2 = add(3.14, 2.86);  // double + double
auto result3 = add(std::string("hello"), std::string(" world")); // string + string

// Generic lambda in algorithms
std::vector<int> numbers = {1, 2, 3, 4, 5};
std::vector<double> doubles = {1.1, 2.2, 3.3, 4.4, 5.5};

auto process = [](const auto& container) {
    for (const auto& item : container) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
};

process(numbers);   // Works with vector<int>
process(doubles);   // Works with vector<double>
```

### Return Type Deduction

```cpp
// Simple return type deduction
auto factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// Return type deduction with multiple return statements
auto getValue(bool flag) {
    if (flag) {
        return 42;      // int
    } else {
        return 3.14;    // double - ERROR: inconsistent types
    }
}

// Return type deduction with decltype
auto multiply(int a, int b) -> decltype(a * b) {
    return a * b;
}

// Return type deduction with trailing return type
auto complexCalculation(int x, double y) -> decltype(x * y + 1) {
    return x * y + 1;
}
```

### Binary Literals and Digit Separators

```cpp
// Binary literals
int binary = 0b1010;        // 10 in decimal
int binary_long = 0b1111'0000'1010'0101;  // With digit separators

// Digit separators for readability
int million = 1'000'000;
double pi = 3.141'592'653'59;
long long big_number = 123'456'789'012'345'678LL;

// Binary operations
int flags = 0b0001 | 0b0010 | 0b0100;  // 0b0111 = 7
```

## C++17 Features

### Structured Bindings

```cpp
#include <map>
#include <tuple>
#include <array>
#include <string>

// Pair binding
std::pair<int, std::string> getPerson() {
    return {42, "Alice"};
}

auto [age, name] = getPerson();
std::cout << name << " is " << age << " years old" << std::endl;

// Tuple binding
std::tuple<int, double, std::string> getData() {
    return {100, 3.14, "test"};
}

auto [value, pi, text] = getData();

// Array binding
std::array<int, 3> coords = {10, 20, 30};
auto [x, y, z] = coords;

// Map iteration with structured bindings
std::map<std::string, int> scores = {{"Alice", 95}, {"Bob", 87}};
for (const auto& [name, score] : scores) {
    std::cout << name << ": " << score << std::endl;
}

// Custom struct binding
struct Point {
    int x, y;
};

Point getPoint() { return {5, 10}; }
auto [px, py] = getPoint();
```

### if constexpr

```cpp
#include <type_traits>
#include <iostream>

template<typename T>
void processValue(const T& value) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "Integer: " << value << std::endl;
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "Float: " << value << std::endl;
    } else if constexpr (std::is_same_v<T, std::string>) {
        std::cout << "String: " << value << std::endl;
    } else {
        std::cout << "Unknown type" << std::endl;
    }
}

// Usage
processValue(42);           // Integer: 42
processValue(3.14);         // Float: 3.14
processValue(std::string("hello")); // String: hello

// Compile-time conditional compilation
template<typename T>
auto getSize(const T& container) {
    if constexpr (std::is_same_v<T, std::array<typename T::value_type, T::size()>>) {
        return T::size();  // Compile-time size for std::array
    } else {
        return container.size();  // Runtime size for other containers
    }
}
```

### std::optional

```cpp
#include <optional>
#include <string>
#include <iostream>

std::optional<int> divide(int a, int b) {
    if (b == 0) {
        return std::nullopt;  // No value
    }
    return a / b;  // Has value
}

// Usage
auto result = divide(10, 2);
if (result.has_value()) {
    std::cout << "Result: " << result.value() << std::endl;
} else {
    std::cout << "Division by zero" << std::endl;
}

// Using value_or for default
auto result2 = divide(10, 0);
std::cout << "Result: " << result2.value_or(-1) << std::endl;  // -1

// Optional with custom types
std::optional<std::string> findUser(int id) {
    if (id == 1) return "Alice";
    if (id == 2) return "Bob";
    return std::nullopt;
}

// Structured binding with optional
if (auto user = findUser(1); user.has_value()) {
    std::cout << "Found user: " << *user << std::endl;
}
```

## C++20 Features

### Concepts

```cpp
#include <concepts>
#include <vector>
#include <algorithm>

// Basic concept
template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

// Concept with requirements
template<typename T>
concept Sortable = requires(T& t) {
    { t.begin() } -> std::input_iterator;
    { t.end() } -> std::input_iterator;
    requires std::totally_ordered<typename T::value_type>;
};

// Function using concepts
template<Numeric T>
T add(T a, T b) {
    return a + b;
}

template<Sortable T>
void sortContainer(T& container) {
    std::sort(container.begin(), container.end());
}

// Usage
int result = add(5, 3);           // OK
double result2 = add(3.14, 2.86); // OK
// add("hello", "world");         // Error: string doesn't satisfy Numeric

std::vector<int> numbers = {3, 1, 4, 1, 5};
sortContainer(numbers);            // OK
```

### Ranges

```cpp
#include <ranges>
#include <vector>
#include <iostream>

std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Basic range operations
auto even_numbers = numbers | std::views::filter([](int n) { return n % 2 == 0; });
auto doubled = even_numbers | std::views::transform([](int n) { return n * 2; });

// Print results
for (int num : doubled) {
    std::cout << num << " ";  // 4 8 12 16 20
}

// Chaining range operations
auto result = numbers 
    | std::views::filter([](int n) { return n > 5; })
    | std::views::transform([](int n) { return n * n; })
    | std::views::take(3);

for (int num : result) {
    std::cout << num << " ";  // 36 49 64
}

// Range algorithms
auto sum = std::ranges::accumulate(numbers, 0);
auto max_val = std::ranges::max(numbers);
auto min_val = std::ranges::min(numbers);
```

### Three-Way Comparison (Spaceship Operator)

```cpp
#include <compare>
#include <iostream>

struct Point {
    int x, y;
    
    auto operator<=>(const Point& other) const = default;
    
    // Custom three-way comparison
    /*
    auto operator<=>(const Point& other) const {
        if (auto cmp = x <=> other.x; cmp != 0) return cmp;
        return y <=> other.y;
    }
    */
};

// Usage
Point p1{1, 2}, p2{1, 3}, p3{2, 1};

if (p1 < p2) std::cout << "p1 < p2" << std::endl;   // true
if (p1 < p3) std::cout << "p1 < p3" << std::endl;   // true
if (p2 < p3) std::cout << "p2 < p3" << std::endl;   // true

// All comparison operators are automatically generated
bool eq = p1 == p2;  // false
bool ne = p1 != p2;  // true
bool le = p1 <= p2;  // true
bool ge = p1 >= p2;  // false
```

## Best Practices

### When to Use Modern Features

```cpp
// Use auto when type is obvious
auto container = std::vector<int>{1, 2, 3};  // Good
auto result = complexCalculation();           // Good
auto x = 42;                                 // Good

// Avoid auto when type is unclear
auto value = getValue();  // Bad: unclear what type this is

// Use range-based for when possible
for (const auto& item : container) {  // Good
    process(item);
}

// Use smart pointers for dynamic memory
auto ptr = std::make_unique<MyClass>();  // Good
// MyClass* ptr = new MyClass();         // Bad

// Use lambda expressions for simple operations
auto isPositive = [](int n) { return n > 0; };  // Good
```

### Performance Considerations

```cpp
// Move semantics for expensive operations
std::vector<std::string> processStrings(std::vector<std::string> input) {
    // Process strings...
    return input;  // Move constructor used automatically
}

// Perfect forwarding
template<typename T>
void wrapper(T&& arg) {
    process(std::forward<T>(arg));
}

// Constexpr for compile-time evaluation
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

// Use concepts for better error messages
template<std::integral T>
T square(T value) {
    return value * value;
}
```

## Summary

Modern C++ features provide:
- **Type safety**: Auto deduction, concepts, and compile-time checks
- **Performance**: Move semantics, perfect forwarding, and constexpr
- **Expressiveness**: Lambda expressions, range-based for, and structured bindings
- **Safety**: Smart pointers and RAII
- **Readability**: Initializer lists, digit separators, and three-way comparison

Key benefits:
- **Reduced boilerplate**: Less code to write and maintain
- **Better performance**: Move semantics and compile-time evaluation
- **Improved safety**: Smart pointers and RAII
- **Enhanced expressiveness**: Lambda expressions and ranges
- **Modern syntax**: Cleaner, more intuitive code

These features make C++ more productive and enjoyable to use while maintaining its performance characteristics.
