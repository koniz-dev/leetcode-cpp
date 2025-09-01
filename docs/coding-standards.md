# C++23 Coding Standards

This document outlines the coding standards and best practices for LeetCode solutions using **C++23** (ISO/IEC 14882:2023) in a learning-focused repository.

## 🎯 Purpose

This repository is designed for **learning and knowledge storage**. The focus is on:
- Understanding modern C++23 features
- Learning algorithmic approaches
- Building reference material
- Improving coding skills

## 📝 Code Style Guidelines

### Naming Conventions
```cpp
// Classes: PascalCase
class Solution { };

// Functions: camelCase
int twoSum(vector<int>& nums, int target) { }

// Variables: camelCase
auto result = std::ranges::find(nums, target);

// Constants: UPPER_SNAKE_CASE
constexpr int MAX_SIZE = 10000;
```

### Modern C++23 Patterns

#### 1. Range-based Algorithms
```cpp
// Prefer std::ranges over traditional algorithms
auto it = std::ranges::find(nums, target);
// Instead of: auto it = std::find(nums.begin(), nums.end(), target);

// Use std::ranges::sort for cleaner syntax
std::ranges::sort(nums);
// Instead of: std::sort(nums.begin(), nums.end());
```

#### 2. Views for Lazy Evaluation
```cpp
// Use views for efficient data transformation
auto even_numbers = nums | std::views::filter([](int x) { return x % 2 == 0; });
auto doubled = nums | std::views::transform([](int x) { return x * 2; });
```

#### 3. Structured Bindings
```cpp
// Use structured bindings for cleaner code
auto [min_val, max_val] = std::ranges::minmax(nums);
auto [first, second] = std::pair{1, 2};
```

#### 4. constexpr and constinit
```cpp
// Use constexpr for compile-time computation
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

// Use constinit for static initialization
constinit int global_value = factorial(10);
```

## 🏗️ Solution Structure

### Class Template
```cpp
class Solution {
public:
    /*
     * Problem: [PROBLEM_NAME]
     * Difficulty: [EASY/MEDIUM/HARD]
     * 
     * Approach: [BRIEF_DESCRIPTION]
     * Time Complexity: O([COMPLEXITY])
     * Space Complexity: O([COMPLEXITY])
     * 
     * C++23 Features Used:
     * - std::ranges for [PURPOSE]
     * - std::views for [PURPOSE]
     * - [OTHER_FEATURES]
     */
    [RETURN_TYPE] [FUNCTION_NAME]([PARAMETERS]) {
        // Implementation using modern C++23 features
    }
};
```

### Function Documentation
```cpp
/*
 * Finds two numbers in nums that add up to target.
 * 
 * @param nums: Input array of integers
 * @param target: Target sum to find
 * @return: Vector containing indices of the two numbers
 * 
 * Algorithm: Uses hash map for O(n) time complexity
 * C++23: Leverages std::ranges::find and structured bindings
 */
```

## 🔧 Modern C++23 Best Practices

### 1. RAII and Smart Pointers
```cpp
// Prefer unique_ptr over raw pointers
auto data = std::make_unique<std::vector<int>>();

// Use shared_ptr only when shared ownership is needed
auto shared_data = std::make_shared<std::vector<int>>();
```

### 2. Concepts and Constraints
```cpp
// Use concepts for compile-time requirements
template<std::ranges::input_range R>
requires std::integral<std::ranges::range_value_t<R>>
auto sum_range(R&& range) {
    return std::ranges::fold_left(range, 0, std::plus{});
}
```

### 3. std::expected for Error Handling
```cpp
// Use std::expected instead of exceptions when possible
std::expected<int, std::string> safe_divide(int a, int b) {
    if (b == 0) return std::unexpected("Division by zero");
    return a / b;
}
```

### 4. std::format for String Formatting
```cpp
// Use std::format for type-safe string formatting
auto message = std::format("Found solution at indices: {} and {}", i, j);
```

## 📊 Performance Guidelines

### Time Complexity Analysis
- Always document time complexity in Big O notation
- Consider both average and worst-case scenarios
- Explain the reasoning behind complexity

### Space Complexity Analysis
- Document auxiliary space usage
- Distinguish between input space and extra space
- Consider stack space for recursive solutions

### Optimization Techniques
```cpp
// Use std::ranges::views for memory efficiency
auto result = nums | std::views::filter(predicate) | std::views::take(10);

// Leverage constexpr for compile-time optimization
constexpr auto compile_time_value = expensive_calculation();

// Use std::ranges::algorithms for better performance
std::ranges::sort(nums); // Often faster than std::sort
```

## 🧪 Testing and Validation

### Test Cases
```cpp
// Include multiple test cases
void test_solution() {
    Solution sol;
    
    // Test case 1: Basic functionality
    vector<int> nums1 = {2, 7, 11, 15};
    assert(sol.twoSum(nums1, 9) == vector<int>{0, 1});
    
    // Test case 2: Edge cases
    vector<int> nums2 = {3, 2, 4};
    assert(sol.twoSum(nums2, 6) == vector<int>{1, 2});
}
```

### Input Validation
```cpp
// Validate inputs when appropriate
if (nums.empty() || nums.size() < 2) {
    return {}; // Return empty result for invalid input
}
```

## 📚 Learning Resources

### Official Documentation
- [C++23 Reference](https://en.cppreference.com/w/cpp/23)
- [std::ranges Tutorial](https://en.cppreference.com/w/cpp/ranges)
- [Modern C++ Best Practices](https://isocpp.github.io/CppCoreGuidelines/)

### Online Resources
- [CppCon Talks](https://www.youtube.com/user/CppCon)
- [C++ Weekly](https://www.youtube.com/c/CWeekly)
- [Modern C++ Tutorial](https://github.com/AnthonyCalandra/modern-cpp-features)

## 🎯 Key Learning Points

### Focus on Understanding
1. **Why use C++23 features?** - Understand the benefits
2. **When to use each feature?** - Learn appropriate use cases
3. **How features work together?** - See the bigger picture
4. **Performance implications** - Understand trade-offs

### Practice Examples
- Study the optimized solutions in each problem
- Compare traditional vs. modern approaches
- Experiment with different C++23 features
- Build your own examples

---

**Remember: This repository is for learning and knowledge storage. Focus on understanding modern C++23 concepts and building your programming skills! 🚀📚**
