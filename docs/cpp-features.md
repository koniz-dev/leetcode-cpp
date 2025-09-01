# Modern C++23 Features

This document covers modern C++23 features and best practices used in LeetCode solutions.

## 🚀 C++23 Standard Features

### std::ranges (C++20/23)
Modern range-based algorithms that work directly with containers.

```cpp
#include <ranges>
#include <vector>
#include <algorithm>

std::vector<int> nums = {1, 2, 3, 4, 5};

// Traditional C++11 approach
auto it = std::find(nums.begin(), nums.end(), 3);
if (it != nums.end()) {
    return std::distance(nums.begin(), it);
}

// Modern C++23 approach
auto it = std::ranges::find(nums, 3);
if (it != nums.end()) {
    return std::ranges::distance(nums.begin(), it);
}

// Sorting with ranges
std::ranges::sort(nums);
std::ranges::reverse(nums);

// Finding min/max
auto [min_val, max_val] = std::ranges::minmax(nums);
```

**Benefits of std::ranges:**
- Cleaner syntax without begin/end iterators
- Better performance through compiler optimizations
- Consistent API across all range algorithms
- More readable and maintainable code

### std::views (C++20/23)
Lazy evaluation views that transform data without creating intermediate containers.

```cpp
#include <ranges>
#include <vector>

std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Filter even numbers
auto even_nums = nums | std::views::filter([](int x) { return x % 2 == 0; });

// Transform numbers (double them)
auto doubled = nums | std::views::transform([](int x) { return x * 2; });

// Take first 5 elements
auto first_five = nums | std::views::take(5);

// Drop first 2 elements
auto without_first_two = nums | std::views::drop(2);

// Combine multiple views
auto result = nums 
    | std::views::filter([](int x) { return x % 2 == 0; })
    | std::views::transform([](int x) { return x * x; })
    | std::views::take(3);

// Convert view to vector if needed
std::vector<int> result_vec(result.begin(), result.end());
```

**Benefits of std::views:**
- Memory efficient (no intermediate containers)
- Lazy evaluation (computation only when needed)
- Composable (chain multiple operations)
- Better cache locality and performance

### std::format (C++20/23)
Type-safe string formatting with compile-time format string checking.

```cpp
#include <format>
#include <string>
#include <iostream>

int x = 42;
std::string name = "World";
double pi = 3.14159;

// Basic formatting
auto message1 = std::format("Hello, {}!", name);
auto message2 = std::format("x = {}, pi = {:.2f}", x, pi);

// Positional arguments
auto message3 = std::format("x = {1}, y = {0}", 10, 20);

// Format specifiers
auto message4 = std::format("Hex: {:#x}, Binary: {:#b}", x, x);
auto message5 = std::format("Width: {:>10}, Center: {:^10}", x, x);

// Custom formatting
auto message6 = std::format("Vector: [{:}]", std::format("{}", std::views::all(nums)));

std::cout << message1 << std::endl;  // Output: Hello, World!
std::cout << message2 << std::endl;  // Output: x = 42, pi = 3.14
```

**Benefits of std::format:**
- Type-safe (compile-time checking)
- Performance (often faster than string concatenation)
- Readable and maintainable
- Consistent with other modern languages

### std::expected (C++23)
Error handling without exceptions, providing a more predictable control flow.

```cpp
#include <expected>
#include <string>

std::expected<int, std::string> safe_divide(int a, int b) {
    if (b == 0) {
        return std::unexpected("Division by zero");
    }
    return a / b;
}

std::expected<int, std::string> safe_sqrt(int x) {
    if (x < 0) {
        return std::unexpected("Cannot take square root of negative number");
    }
    return static_cast<int>(std::sqrt(x));
}

// Usage
void process_calculation() {
    auto result = safe_divide(10, 2);
    if (result.has_value()) {
        std::cout << "Result: " << result.value() << std::endl;
    } else {
        std::cout << "Error: " << result.error() << std::endl;
    }
    
    // Using monadic operations
    auto final_result = safe_divide(10, 2)
        .and_then([](int x) { return safe_sqrt(x); });
}
```

**Benefits of std::expected:**
- No exception overhead
- Predictable error handling
- Compile-time error checking
- Functional programming style

### Concepts and Constraints (C++20/23)
Compile-time requirements checking for templates.

```cpp
#include <concepts>
#include <ranges>
#include <vector>

// Simple concept
template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

// Function using concept
template<Numeric T>
T add(T a, T b) {
    return a + b;
}

// Range concept
template<typename R>
concept InputRange = std::ranges::input_range<R>;

// Algorithm using range concept
template<InputRange R>
requires std::integral<std::ranges::range_value_t<R>>
auto sum_range(R&& range) {
    return std::ranges::fold_left(range, 0, std::plus{});
}

// Usage
std::vector<int> nums = {1, 2, 3, 4, 5};
auto sum = sum_range(nums);  // Works
// auto sum2 = sum_range("hello");  // Compile error - not integral range
```

**Benefits of concepts:**
- Better error messages
- Compile-time requirements checking
- More readable template code
- Better IDE support

## 🔧 Modern C++23 Patterns

### Structured Bindings (C++17/23)
Clean syntax for extracting multiple values from objects.

```cpp
#include <map>
#include <tuple>
#include <ranges>

// With std::pair
std::pair<int, std::string> get_pair() {
    return {42, "answer"};
}

auto [value, text] = get_pair();
// value = 42, text = "answer"

// With std::tuple
auto get_tuple() {
    return std::make_tuple(1, 2.5, "three");
}

auto [a, b, c] = get_tuple();
// a = 1, b = 2.5, c = "three"

// With std::map
std::map<std::string, int> scores = {{"Alice", 100}, {"Bob", 95}};
for (const auto& [name, score] : scores) {
    std::cout << name << ": " << score << std::endl;
}

// With std::ranges::minmax
auto [min_val, max_val] = std::ranges::minmax(nums);
```

### constexpr and constinit (C++11/20/23)
Compile-time computation and initialization.

```cpp
// constexpr function
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

// Compile-time constant
constexpr int MAX_SIZE = factorial(10);

// constexpr if (C++17)
template<typename T>
auto get_value(T& container) {
    if constexpr (std::ranges::sized_range<T>) {
        return container.size();
    } else {
        return -1;
    }
}

// constinit (C++20)
constinit int global_value = factorial(10);
```

### Smart Pointers and RAII
Modern memory management without raw pointers.

```cpp
#include <memory>
#include <vector>

// unique_ptr - exclusive ownership
auto data = std::make_unique<std::vector<int>>();
data->push_back(42);

// shared_ptr - shared ownership
auto shared_data = std::make_shared<std::vector<int>>();
auto data_copy = shared_data;  // Reference count increases

// weak_ptr - non-owning reference
auto weak_ref = std::weak_ptr(shared_data);
if (auto locked = weak_ref.lock()) {
    // Use locked data
}

// RAII with custom deleter
auto file_ptr = std::unique_ptr<FILE, decltype(&fclose)>(
    fopen("data.txt", "r"), fclose);
```

## 📊 Performance Optimization

### Move Semantics
Efficient transfer of resources instead of copying.

```cpp
#include <vector>
#include <string>

std::vector<std::string> create_strings() {
    std::vector<std::string> result;
    result.reserve(1000);
    
    for (int i = 0; i < 1000; ++i) {
        result.emplace_back("String " + std::to_string(i));
    }
    
    return result;  // Move constructor called, not copy
}

// Usage
auto strings = create_strings();  // Move assignment

// Explicit move
std::vector<std::string> source = {"a", "b", "c"};
std::vector<std::string> destination = std::move(source);
// source is now empty, destination has the data
```

### Perfect Forwarding
Preserve value categories in template functions.

```cpp
template<typename T>
void wrapper(T&& arg) {
    // Forward preserves lvalue/rvalue nature
    process(std::forward<T>(arg));
}

// Usage
std::string str = "hello";
wrapper(str);           // T = std::string&, arg = std::string&
wrapper(std::string{}); // T = std::string, arg = std::string&&
```

## 🧪 Testing Modern C++23 Code

### Compile-time Testing
```cpp
// Static assertions
static_assert(std::ranges::sized_range<std::vector<int>>);
static_assert(std::integral<int>);
static_assert(factorial(5) == 120);

// Concept checking
template<typename T>
concept Testable = requires(T t) {
    { t.test() } -> std::convertible_to<bool>;
};

static_assert(Testable<TestClass>);
```

### Runtime Testing
```cpp
#include <cassert>
#include <iostream>

void test_modern_features() {
    // Test std::ranges
    std::vector<int> nums = {3, 1, 4, 1, 5};
    std::ranges::sort(nums);
    assert(nums == std::vector<int>{1, 1, 3, 4, 5});
    
    // Test std::views
    auto even_squares = nums 
        | std::views::filter([](int x) { return x % 2 == 0; })
        | std::views::transform([](int x) { return x * x; });
    
    std::vector<int> result(even_squares.begin(), even_squares.end());
    assert(result == std::vector<int>{16});  // Only 4^2 = 16
    
    // Test std::format
    auto message = std::format("Sum: {}", std::ranges::fold_left(nums, 0, std::plus{}));
    assert(message == "Sum: 14");
    
    std::cout << "All tests passed!" << std::endl;
}
```

## 📚 Learning Resources

### Official Documentation
- [C++23 Reference](https://en.cppreference.com/w/cpp/23)
- [std::ranges Tutorial](https://en.cppreference.com/w/cpp/ranges)
- [std::views Documentation](https://en.cppreference.com/w/cpp/ranges#Range_adaptors)
- [std::format Reference](https://en.cppreference.com/w/cpp/utility/format/format)

### Best Practices
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)
- [Modern C++ Design](https://www.modernescpp.com/)
- [C++23 Compiler Support](https://en.cppreference.com/w/cpp/compiler_support)

### Online Resources
- [CppCon Talks](https://www.youtube.com/user/CppCon)
- [C++ Weekly](https://www.youtube.com/c/CWeekly)
- [Modern C++ Tutorial](https://github.com/AnthonyCalandra/modern-cpp-features)

---

**Remember: Modern C++23 features make code more readable, efficient, and maintainable. Use them wisely to write better LeetCode solutions! 🚀✨**
