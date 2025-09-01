# STL Algorithms in C++

## Overview

The Standard Template Library (STL) provides a rich collection of algorithms that work with containers. These algorithms are designed to be efficient, generic, and easy to use.

## Key Concepts

### Algorithm Categories
- **Non-modifying algorithms**: Don't change the container contents
- **Modifying algorithms**: Change the container contents
- **Sorting algorithms**: Arrange elements in order
- **Searching algorithms**: Find elements or patterns
- **Numeric algorithms**: Mathematical operations

### Iterator Requirements
- **Input iterators**: Read-only, forward-only
- **Output iterators**: Write-only, forward-only
- **Forward iterators**: Read/write, forward-only
- **Bidirectional iterators**: Read/write, forward/backward
- **Random access iterators**: Read/write, random access

## Non-Modifying Algorithms

### Finding Elements

```cpp
#include <algorithm>
#include <vector>

// find - returns iterator to first occurrence
auto it = std::find(vec.begin(), vec.end(), 42);
if (it != vec.end()) {
    // Found 42 at position it - vec.begin()
}

// find_if - find with predicate
auto it = std::find_if(vec.begin(), vec.end(), 
    [](int x) { return x > 10; });

// count - count occurrences
int count = std::count(vec.begin(), vec.end(), 42);

// count_if - count with predicate
int count = std::count_if(vec.begin(), vec.end(),
    [](int x) { return x % 2 == 0; });
```

### Searching

```cpp
// search - find subsequence
std::vector<int> haystack = {1, 2, 3, 4, 5, 6};
std::vector<int> needle = {3, 4, 5};
auto it = std::search(haystack.begin(), haystack.end(),
                      needle.begin(), needle.end());

// binary_search - requires sorted range
bool found = std::binary_search(vec.begin(), vec.end(), 42);

// lower_bound - first element >= value
auto it = std::lower_bound(vec.begin(), vec.end(), 42);

// upper_bound - first element > value
auto it = std::upper_bound(vec.begin(), vec.end(), 42);
```

### Testing Conditions

```cpp
// all_of - all elements satisfy condition
bool all_even = std::all_of(vec.begin(), vec.end(),
    [](int x) { return x % 2 == 0; });

// any_of - any element satisfies condition
bool any_odd = std::any_of(vec.begin(), vec.end(),
    [](int x) { return x % 2 == 1; });

// none_of - no element satisfies condition
bool none_negative = std::none_of(vec.begin(), vec.end(),
    [](int x) { return x < 0; });
```

## Modifying Algorithms

### Copying and Moving

```cpp
// copy - copy elements
std::vector<int> dest(10);
std::copy(src.begin(), src.begin() + 5, dest.begin());

// copy_if - copy with condition
std::copy_if(src.begin(), src.end(), dest.begin(),
    [](int x) { return x > 0; });

// move - move elements (C++11)
std::move(src.begin(), src.end(), dest.begin());

// reverse_copy - copy in reverse order
std::reverse_copy(src.begin(), src.end(), dest.begin());
```

### Transforming

```cpp
// transform - apply function to each element
std::transform(vec.begin(), vec.end(), result.begin(),
    [](int x) { return x * 2; });

// transform with two ranges
std::transform(a.begin(), a.end(), b.begin(), result.begin(),
    [](int x, int y) { return x + y; });

// replace - replace specific values
std::replace(vec.begin(), vec.end(), 0, -1);

// replace_if - replace with condition
std::replace_if(vec.begin(), vec.end(),
    [](int x) { return x < 0; }, 0);
```

### Removing

```cpp
// remove - move elements to end (doesn't resize)
auto new_end = std::remove(vec.begin(), vec.end(), 0);
vec.erase(new_end, vec.end());

// remove_if - remove with condition
auto new_end = std::remove_if(vec.begin(), vec.end(),
    [](int x) { return x % 2 == 0; });
vec.erase(new_end, vec.end());

// unique - remove consecutive duplicates
auto new_end = std::unique(vec.begin(), vec.end());
vec.erase(new_end, vec.end());
```

## Sorting Algorithms

### Basic Sorting

```cpp
// sort - default comparison
std::sort(vec.begin(), vec.end());

// sort with custom comparator
std::sort(vec.begin(), vec.end(), std::greater<int>());

// sort with lambda
std::sort(vec.begin(), vec.end(),
    [](int a, int b) { return a > b; });

// stable_sort - maintains relative order of equal elements
std::stable_sort(vec.begin(), vec.end());

// partial_sort - sort first n elements
std::partial_sort(vec.begin(), vec.begin() + 5, vec.end());
```

### Partitioning

```cpp
// partition - divide based on predicate
auto mid = std::partition(vec.begin(), vec.end(),
    [](int x) { return x % 2 == 0; });

// stable_partition - maintain relative order
auto mid = std::stable_partition(vec.begin(), vec.end(),
    [](int x) { return x % 2 == 0; });

// partition_copy - copy to two destinations
std::vector<int> even, odd;
std::partition_copy(vec.begin(), vec.end(),
    std::back_inserter(even), std::back_inserter(odd),
    [](int x) { return x % 2 == 0; });
```

## Numeric Algorithms

```cpp
#include <numeric>

// accumulate - sum with optional operation
int sum = std::accumulate(vec.begin(), vec.end(), 0);
int product = std::accumulate(vec.begin(), vec.end(), 1, 
    std::multiplies<int>());

// inner_product - dot product
int dot_product = std::inner_product(a.begin(), a.end(), b.begin(), 0);

// partial_sum - cumulative sum
std::partial_sum(vec.begin(), vec.end(), result.begin());

// adjacent_difference - differences between adjacent elements
std::adjacent_difference(vec.begin(), vec.end(), result.begin());
```

## Heap Operations

```cpp
// make_heap - create max heap
std::make_heap(vec.begin(), vec.end());

// push_heap - add element to heap
vec.push_back(42);
std::push_heap(vec.begin(), vec.end());

// pop_heap - remove largest element
std::pop_heap(vec.begin(), vec.end());
vec.pop_back();

// sort_heap - sort heap in ascending order
std::sort_heap(vec.begin(), vec.end());
```

## Best Practices

### Performance Considerations

```cpp
// Use appropriate iterators
// Random access for sort, bidirectional for reverse
std::sort(vec.begin(), vec.end());           // O(n log n)
std::reverse(vec.begin(), vec.end());        // O(n)

// Avoid unnecessary copies
// Use references and move semantics
std::for_each(vec.begin(), vec.end(),
    [](const auto& x) { /* process x */ });

// Use algorithms instead of loops when possible
// More readable and often more efficient
std::transform(vec.begin(), vec.end(), result.begin(),
    [](int x) { return x * 2; });
```

### Common Patterns

```cpp
// Find and erase pattern
auto it = std::find(vec.begin(), vec.end(), value);
if (it != vec.end()) {
    vec.erase(it);
}

// Remove-erase idiom
vec.erase(std::remove(vec.begin(), vec.end(), value), vec.end());

// Sort and unique pattern
std::sort(vec.begin(), vec.end());
vec.erase(std::unique(vec.begin(), vec.end()), vec.end());

// Transform and filter
std::vector<int> result;
std::copy_if(vec.begin(), vec.end(), std::back_inserter(result),
    [](int x) { return x > 0; });
std::transform(result.begin(), result.end(), result.begin(),
    [](int x) { return x * 2; });
```

## Advanced Usage

### Custom Comparators

```cpp
struct Person {
    std::string name;
    int age;
};

// Sort by age, then by name
std::sort(people.begin(), people.end(),
    [](const Person& a, const Person& b) {
        if (a.age != b.age) return a.age < b.age;
        return a.name < b.name;
    });
```

### Algorithm Composition

```cpp
// Chain multiple algorithms
std::vector<int> result;
auto it = std::copy_if(vec.begin(), vec.end(), 
    std::back_inserter(result),
    [](int x) { return x > 0; });
std::transform(result.begin(), it, result.begin(),
    [](int x) { return x * 2; });
```

## Summary

STL algorithms provide powerful, efficient tools for common operations:
- **Non-modifying**: find, count, search, test conditions
- **Modifying**: copy, transform, replace, remove
- **Sorting**: sort, stable_sort, partial_sort
- **Numeric**: accumulate, inner_product, partial_sum
- **Heap**: make_heap, push_heap, pop_heap

Key benefits:
- **Generic**: Work with any container type
- **Efficient**: Optimized implementations
- **Safe**: Bounds checking and error handling
- **Readable**: Clear intent and purpose

Use STL algorithms whenever possible to write cleaner, more maintainable code.
