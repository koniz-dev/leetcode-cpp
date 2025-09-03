# 🧩 C++ Template Metaprogramming

## 📚 Overview

Template Metaprogramming (TMP) is a powerful C++ technique that allows you to perform computations at compile-time using templates. It's a form of "programming the compiler" that can generate highly optimized code and provide compile-time type safety.

## 🎯 Key Concepts

### What is Template Metaprogramming?
- **Compile-time computation** using templates
- **Type-level programming** with type safety
- **Code generation** at compile time
- **Zero-cost abstractions** with no runtime overhead

### Why Use TMP?
- **Performance**: Compile-time optimizations
- **Type Safety**: Catch errors at compile time
- **Code Generation**: Reduce boilerplate code
- **Generic Programming**: Write type-independent algorithms

## 🔧 Basic Template Metaprogramming

### Type Traits
```cpp
// Basic type trait
template<typename T>
struct is_pointer {
    static constexpr bool value = false;
};

template<typename T>
struct is_pointer<T*> {
    static constexpr bool value = true;
};

// Usage
static_assert(is_pointer<int*>::value == true);
static_assert(is_pointer<int>::value == false);
```

### Compile-time Constants
```cpp
// Compile-time factorial
template<unsigned n>
struct factorial {
    static constexpr unsigned value = n * factorial<n-1>::value;
};

template<>
struct factorial<0> {
    static constexpr unsigned value = 1;
};

// Usage
constexpr unsigned result = factorial<5>::value; // 120
```

### Conditional Types
```cpp
// Type selection based on condition
template<bool condition, typename T1, typename T2>
struct conditional {
    using type = T1;
};

template<typename T1, typename T2>
struct conditional<false, T1, T2> {
    using type = T2;
};

// Usage
using result_type = conditional<true, int, double>::type; // int
```

## 🚀 Advanced TMP Techniques

### SFINAE (Substitution Failure Is Not An Error)
```cpp
// Enable if pattern
template<typename T, typename = void>
struct has_size_method : std::false_type {};

template<typename T>
struct has_size_method<T, 
    std::void_t<decltype(std::declval<T>().size())>> 
    : std::true_type {};

// Usage
static_assert(has_size_method<std::vector<int>>::value);
static_assert(!has_size_method<int>::value);
```

### Variadic Templates
```cpp
// Compile-time sum
template<typename... Args>
struct sum;

template<typename T>
struct sum<T> {
    static constexpr T value = T{};
};

template<typename T, typename... Args>
struct sum<T, Args...> {
    static constexpr T value = T{} + sum<Args...>::value;
};

// Usage
constexpr int result = sum<int, 1, 2, 3, 4, 5>::value; // 15
```

### Template Specialization
```cpp
// Primary template
template<typename T>
struct type_info {
    static constexpr const char* name = "unknown";
    static constexpr size_t size = sizeof(T);
};

// Specializations
template<>
struct type_info<int> {
    static constexpr const char* name = "int";
    static constexpr size_t size = 4;
};

template<>
struct type_info<double> {
    static constexpr const char* name = "double";
    static constexpr size_t size = 8;
};
```

## 🎨 Modern C++ TMP Features

### `constexpr` Functions
```cpp
// Modern compile-time factorial
constexpr unsigned factorial(unsigned n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

// Usage
constexpr unsigned result = factorial(5); // 120
static_assert(factorial(5) == 120);
```

### `if constexpr`
```cpp
template<typename T>
auto process(T value) {
    if constexpr (std::is_integral_v<T>) {
        return value * 2;
    } else if constexpr (std::is_floating_point_v<T>) {
        return value + 1.0;
    } else {
        return value;
    }
}
```

### Concepts (C++20)
```cpp
template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<Numeric T>
T add(T a, T b) {
    return a + b;
}

// Usage
auto result1 = add(5, 3);      // OK
auto result2 = add(3.14, 2.0); // OK
// auto result3 = add("hello", "world"); // Compile error
```

## 🔍 Practical Applications

### Compile-time Data Structures
```cpp
// Compile-time linked list
template<typename T, typename Next = void>
struct compile_time_list {
    using value_type = T;
    using next = Next;
};

// Usage
using list = compile_time_list<int, 
    compile_time_list<double, 
    compile_time_list<char>>>;
```

### Type Lists
```cpp
// Type list operations
template<typename... Types>
struct type_list {};

// Get first type
template<typename List>
struct front;

template<typename T, typename... Rest>
struct front<type_list<T, Rest...>> {
    using type = T;
};

// Get size
template<typename List>
struct size;

template<typename... Types>
struct size<type_list<Types...>> {
    static constexpr size_t value = sizeof...(Types);
};
```

### Compile-time Algorithms
```cpp
// Compile-time sorting (bubble sort)
template<typename List>
struct sort;

template<typename T>
struct sort<type_list<T>> {
    using type = type_list<T>;
};

template<typename T1, typename T2, typename... Rest>
struct sort<type_list<T1, T2, Rest...>> {
    using type = std::conditional_t<
        sizeof(T1) <= sizeof(T2),
        typename sort<type_list<T2, Rest...>>::type,
        typename sort<type_list<T2, T1, Rest...>>::type
    >;
};
```

## ⚡ Performance Benefits

### Zero Runtime Overhead
- **Compile-time computation** eliminates runtime calculations
- **Type information** available at compile time
- **Optimization opportunities** for the compiler

### Memory Efficiency
- **No dynamic allocation** for compile-time structures
- **Stack-based storage** for all computations
- **Predictable memory layout**

## 🚨 Common Pitfalls

### Template Bloat
```cpp
// Avoid excessive template instantiation
template<typename T>
struct expensive_computation {
    // This can cause code bloat
    static constexpr auto value = /* complex computation */;
};
```

### Compilation Time
- **Large templates** increase compilation time
- **Complex metaprogramming** can slow builds
- **Debugging difficulty** with template errors

### Readability
- **Complex syntax** can be hard to understand
- **Error messages** are often cryptic
- **Maintenance challenges** for complex TMP code

## 🛠️ Best Practices

### 1. Keep It Simple
```cpp
// Prefer simple, readable TMP over complex solutions
template<typename T>
using remove_pointer_t = typename std::remove_pointer<T>::type;
```

### 2. Use Modern C++ Features
```cpp
// Use constexpr instead of template metaprogramming when possible
constexpr bool is_power_of_two(unsigned n) {
    return n > 0 && (n & (n - 1)) == 0;
}
```

### 3. Document Your Intent
```cpp
// Clear documentation for complex TMP
/**
 * @brief Compile-time type list with push_back operation
 * @tparam T Element type to add
 * @tparam List Current type list
 */
template<typename T, typename List>
struct push_back;
```

### 4. Test Thoroughly
```cpp
// Unit tests for TMP code
static_assert(std::is_same_v<
    push_back<int, type_list<double>>::type,
    type_list<double, int>
>);
```

## 📚 Advanced Topics

### Expression Templates
```cpp
// Lazy evaluation for mathematical expressions
template<typename Lhs, typename Rhs>
struct add_expression {
    Lhs lhs;
    Rhs rhs;
    
    auto operator[](size_t i) const {
        return lhs[i] + rhs[i];
    }
};
```

### Type Erasure
```cpp
// Hide complex types behind interfaces
class drawable {
    struct concept {
        virtual ~concept() = default;
        virtual void draw() const = 0;
    };
    
    template<typename T>
    struct model : concept {
        T data;
        void draw() const override { data.draw(); }
    };
    
    std::unique_ptr<concept> pimpl;
public:
    template<typename T>
    drawable(T&& obj) : pimpl(std::make_unique<model<T>>(std::forward<T>(obj))) {}
    
    void draw() const { pimpl->draw(); }
};
```

### Compile-time Reflection
```cpp
// Basic compile-time reflection
template<typename T>
struct reflect {
    static constexpr size_t size = sizeof(T);
    static constexpr bool is_trivially_copyable = std::is_trivially_copyable_v<T>;
    static constexpr bool is_pod = std::is_pod_v<T>;
};
```

## 🎯 Learning Path

### Beginner Level
1. **Basic templates** and type traits
2. **Simple compile-time constants**
3. **Template specialization**

### Intermediate Level
1. **SFINAE techniques**
2. **Variadic templates**
3. **Type lists and algorithms**

### Advanced Level
1. **Expression templates**
2. **Type erasure patterns**
3. **Compile-time reflection**

### Expert Level
1. **Custom type systems**
2. **Domain-specific languages**
3. **Advanced optimization techniques**

## 📖 Resources

### Books
- "Modern C++ Design" by Andrei Alexandrescu
- "C++ Templates: The Complete Guide" by David Vandevoorde
- "Effective Modern C++" by Scott Meyers

### Online Resources
- [cppreference.com](https://en.cppreference.com/w/cpp/language/templates)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)
- [Template Metaprogramming Tutorials](https://en.cppreference.com/w/cpp/language/templates)

## 🚀 Practice Problems

### Basic Exercises
1. **Type Trait Creation**: Implement `is_same`, `is_base_of`
2. **Compile-time Math**: Implement GCD, LCM, prime checking
3. **Type Lists**: Implement `front`, `back`, `at` operations

### Intermediate Exercises
1. **SFINAE Patterns**: Create enable_if alternatives
2. **Variadic Templates**: Implement tuple-like structures
3. **Type Algorithms**: Sort types by size, find common base

### Advanced Exercises
1. **Expression Templates**: Build mathematical expression system
2. **Type Erasure**: Implement polymorphic containers
3. **Compile-time Reflection**: Analyze class members

---

*Template metaprogramming is a powerful tool that can generate highly optimized code and provide compile-time guarantees. Master it to write more efficient, safer, and more expressive C++ code.*
