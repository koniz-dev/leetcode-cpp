# Containers in C++

## Overview
Containers are pre-designed data structures in the C++ Standard Template Library (STL) for storing and managing data.

## Vector

### Introduction
`vector` is a dynamic container that can automatically resize. Similar to dynamic arrays in other programming languages.

### Declaration and Initialization

```cpp
#include <vector>

// Basic declaration
std::vector<int> numbers;

// Initialize with size
std::vector<int> vec(5);  // 5 elements with value 0

// Initialize with value
std::vector<int> vec(5, 10);  // 5 elements with value 10

// Initialize from list
std::vector<int> vec = {1, 2, 3, 4, 5};

// Copy from another vector
std::vector<int> vec2 = vec;
```

### Basic Methods

#### Adding Elements
```cpp
std::vector<int> vec;

// Add to end
vec.push_back(10);
vec.push_back(20);

// Insert at specific position
vec.insert(vec.begin() + 1, 15);

// Insert multiple elements
vec.insert(vec.end(), {30, 40, 50});
```

#### Accessing Elements
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};

// Access by index
int first = vec[0];        // No bounds checking
int second = vec.at(1);    // With bounds checking

// Access first/last elements
int front = vec.front();
int back = vec.back();
```

#### Removing Elements
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};

// Remove last element
vec.pop_back();

// Remove element at position
vec.erase(vec.begin() + 2);

// Remove multiple elements
vec.erase(vec.begin() + 1, vec.begin() + 3);

// Remove all elements
vec.clear();
```

#### Vector Information
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};

// Current size
size_t size = vec.size();

// Check if vector is empty
bool isEmpty = vec.empty();

// Current capacity
size_t capacity = vec.capacity();

// Maximum size
size_t maxSize = vec.max_size();
```

### Memory Management

#### Resizing
```cpp
std::vector<int> vec = {1, 2, 3};

// Resize to larger size
vec.resize(5);  // New elements initialized to 0

// Resize with default value
vec.resize(7, 100);  // New elements initialized to 100

// Reserve capacity
vec.reserve(100);  // Pre-allocate space for 100 elements
```

#### Iterators
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};

// Range-based for loop (C++11)
for (int element : vec) {
    std::cout << element << " ";
}

// Iterator-based loop
for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
    std::cout << *it << " ";
}

// Const iterator
for (std::vector<int>::const_iterator it = vec.cbegin(); it != vec.cend(); ++it) {
    std::cout << *it << " ";
}
```

### Performance Considerations

#### Time Complexity
- Access by index: O(1)
- Insert/Delete at end: O(1) amortized
- Insert/Delete at beginning/middle: O(n)
- Search: O(n)

#### Space Complexity
- Space used: O(n) where n is the number of elements
- Additional overhead: Small constant factor

### Common Use Cases

#### Basic Usage
```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> numbers;
    
    // Add elements
    for (int i = 1; i <= 10; ++i) {
        numbers.push_back(i);
    }
    
    // Print elements
    for (int num : numbers) {
        std::cout << num << " ";
    }
    
    return 0;
}
```

#### Vector of Vectors (2D Vector)
```cpp
#include <vector>

// 2D vector (matrix)
std::vector<std::vector<int>> matrix(3, std::vector<int>(4, 0));

// Access element
int element = matrix[1][2];

// Add row
matrix.push_back(std::vector<int>(4, 1));
```

## Map

### Introduction
`map` is an associative container that stores key-value pairs in sorted order based on keys.

### Declaration and Initialization

```cpp
#include <map>

// Basic declaration
std::map<std::string, int> scores;

// Initialize with values
std::map<std::string, int> scores = {
    {"Alice", 95},
    {"Bob", 87},
    {"Charlie", 92}
};

// Copy from another map
std::map<std::string, int> scores2 = scores;
```

### Basic Operations

#### Inserting Elements
```cpp
std::map<std::string, int> scores;

// Insert single element
scores.insert({"Alice", 95});

// Insert with hint
scores.insert(scores.begin(), {"Bob", 87});

// Using operator[]
scores["Charlie"] = 92;
```

#### Accessing Elements
```cpp
std::map<std::string, int> scores = {
    {"Alice", 95},
    {"Bob", 87},
    {"Charlie", 92}
};

// Access by key
int aliceScore = scores["Alice"];

// Safe access (check if exists)
auto it = scores.find("David");
if (it != scores.end()) {
    int davidScore = it->second;
}

// Check if key exists
bool hasKey = scores.count("Alice") > 0;
```

#### Removing Elements
```cpp
std::map<std::string, int> scores = {
    {"Alice", 95},
    {"Bob", 87},
    {"Charlie", 92}
};

// Remove by key
scores.erase("Bob");

// Remove by iterator
auto it = scores.find("Charlie");
if (it != scores.end()) {
    scores.erase(it);
}

// Remove all elements
scores.clear();
```

### Iterating Through Map

```cpp
std::map<std::string, int> scores = {
    {"Alice", 95},
    {"Bob", 87},
    {"Charlie", 92}
};

// Range-based for loop
for (const auto& pair : scores) {
    std::cout << pair.first << ": " << pair.second << std::endl;
}

// Iterator-based loop
for (std::map<std::string, int>::iterator it = scores.begin();
     it != scores.end(); ++it) {
    std::cout << it->first << ": " << it->second << std::endl;
}
```

### Performance Considerations

#### Time Complexity
- Insert/Delete: O(log n)
- Search: O(log n)
- Access: O(log n)

#### Space Complexity
- Space used: O(n) where n is the number of key-value pairs

## Unordered Map

### Introduction
`unordered_map` is an associative container that uses hash tables to store key-value pairs. Operations like search, insert, and delete have O(1) average complexity.

### Declaration and Initialization

```cpp
#include <unordered_map>

// Basic declaration
std::unordered_map<std::string, int> scores;

// Initialize with values
std::unordered_map<std::string, int> scores = {
    {"Alice", 95},
    {"Bob", 87},
    {"Charlie", 92}
};

// Copy from another unordered_map
std::unordered_map<std::string, int> scores2 = scores;
```

### Basic Operations

#### Inserting Elements
```cpp
std::unordered_map<std::string, int> scores;

// Insert single element
scores.insert({"Alice", 95});

// Using operator[]
scores["Bob"] = 87;
scores["Charlie"] = 92;
```

#### Accessing Elements
```cpp
std::unordered_map<std::string, int> scores = {
    {"Alice", 95},
    {"Bob", 87},
    {"Charlie", 92}
};

// Access by key
int aliceScore = scores["Alice"];

// Safe access (check if exists)
auto it = scores.find("David");
if (it != scores.end()) {
    int davidScore = it->second;
}

// Check if key exists
bool hasKey = scores.count("Alice") > 0;
```

#### Removing Elements
```cpp
std::unordered_map<std::string, int> scores = {
    {"Alice", 95},
    {"Bob", 87},
    {"Charlie", 92}
};

// Remove by key
scores.erase("Bob");

// Remove by iterator
auto it = scores.find("Charlie");
if (it != scores.end()) {
    scores.erase(it);
}

// Remove all elements
scores.clear();
```

### Iterating Through Unordered Map

```cpp
std::unordered_map<std::string, int> scores = {
    {"Alice", 95},
    {"Bob", 87},
    {"Charlie", 92}
};

// Range-based for loop
for (const auto& pair : scores) {
    std::cout << pair.first << ": " << pair.second << std::endl;
}

// Iterator-based loop
for (std::unordered_map<std::string, int>::iterator it = scores.begin();
     it != scores.end(); ++it) {
    std::cout << it->first << ": " << it->second << std::endl;
}
```

### Advanced Usage

#### Nested Containers
```cpp
// Map of vectors
std::unordered_map<std::string, std::vector<int>> data;
data["scores"] = {85, 92, 78, 96};

// Access nested container
std::vector<int>& scores = data["scores"];
scores.push_back(88);
```

#### Function Parameters
```cpp
#include <unordered_map>

void processMap(const std::unordered_map<std::string, int>& scores) {
    for (const auto& pair : scores) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

// Example usage
std::unordered_map<int, int> seen;
// ... populate seen map
processMap(seen);
```

### Comparison: Map vs Unordered Map

| Feature | unordered_map | map |
|---------|---------------|-----|
| Implementation | Hash table | Red-black tree |
| Order | Unordered | Sorted by key |
| Time complexity | O(1) average | O(log n) |
| Space complexity | O(n) | O(n) |
| Key requirements | Hashable | Comparable |

### Common Use Cases

#### Two Sum Problem
```cpp
#include <vector>
#include <unordered_map>

std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::unordered_map<int, int> seen;
    
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        
        if (seen.find(complement) != seen.end()) {
            return {seen[complement], i};
        }
        
        seen[nums[i]] = i;
    }
    
    return {};
}
```

### Performance Considerations

#### Hash Function
- **Hash function**: unordered_map uses hash function for key type
- **Collision handling**: Uses chaining or open addressing
- **Load factor**: Affects performance, can be adjusted

#### Memory Management
```cpp
#include <unordered_map>

std::unordered_map<int, int> seen;

// Reserve space to avoid rehashing
seen.reserve(1000);

// Check load factor
float loadFactor = seen.load_factor();
float maxLoadFactor = seen.max_load_factor();
```

### Time Complexity Summary

| Operation | Average | Worst Case |
|-----------|---------|------------|
| Insert | O(1) | O(n) |
| Delete | O(1) | O(n) |
| Search | O(1) | O(n) |
| Access | O(1) | O(n) |

## Unordered Set

### Introduction
`unordered_set` is a container that stores unique elements in no particular order. It uses a hash table implementation for O(1) average time complexity operations.

### Declaration and Initialization

```cpp
#include <unordered_set>

// Basic declaration
std::unordered_set<int> numbers;

// Initialize from list
std::unordered_set<int> set = {1, 2, 3, 4, 5};

// Copy from another set
std::unordered_set<int> set2 = set;
```

### Basic Methods

#### Adding Elements
```cpp
std::unordered_set<int> set;

// Insert single element
set.insert(10);
set.insert(20);

// Insert multiple elements
set.insert({30, 40, 50});

// Insert with return value
auto result = set.insert(10);  // Returns pair<iterator, bool>
if (result.second) {
    std::cout << "Element inserted successfully" << std::endl;
} else {
    std::cout << "Element already exists" << std::endl;
}
```

#### Checking Membership
```cpp
std::unordered_set<int> set = {1, 2, 3, 4, 5};

// Check if element exists
if (set.find(3) != set.end()) {
    std::cout << "3 is in the set" << std::endl;
}

// Count occurrences (0 or 1 for sets)
size_t count = set.count(3);  // Returns 1 if exists, 0 otherwise

// Check if empty
bool isEmpty = set.empty();
```

#### Removing Elements
```cpp
std::unordered_set<int> set = {1, 2, 3, 4, 5};

// Remove by value
set.erase(3);

// Remove by iterator
auto it = set.find(2);
if (it != set.end()) {
    set.erase(it);
}

// Remove all elements
set.clear();
```

#### Set Information
```cpp
std::unordered_set<int> set = {1, 2, 3, 4, 5};

// Current size
size_t size = set.size();

// Check if set is empty
bool isEmpty = set.empty();

// Maximum size
size_t maxSize = set.max_size();
```

### Iteration

```cpp
std::unordered_set<int> set = {1, 2, 3, 4, 5};

// Range-based for loop
for (int num : set) {
    std::cout << num << " ";
}

// Iterator-based loop
for (std::unordered_set<int>::iterator it = set.begin(); 
     it != set.end(); ++it) {
    std::cout << *it << " ";
}
```

### Common Use Cases

#### Contains Duplicate Problem
```cpp
#include <vector>
#include <unordered_set>

bool containsDuplicate(std::vector<int>& nums) {
    std::unordered_set<int> seen;
    
    for (int num : nums) {
        if (seen.find(num) != seen.end()) {
            return true;  // Duplicate found
        }
        seen.insert(num);
    }
    
    return false;  // No duplicates
}
```

#### Finding Unique Elements
```cpp
#include <vector>
#include <unordered_set>

std::vector<int> getUniqueElements(const std::vector<int>& nums) {
    std::unordered_set<int> uniqueSet(nums.begin(), nums.end());
    return std::vector<int>(uniqueSet.begin(), uniqueSet.end());
}
```

### Performance Considerations

#### Hash Function
- **Hash function**: unordered_set uses hash function for element type
- **Collision handling**: Uses chaining or open addressing
- **Load factor**: Affects performance, can be adjusted

#### Memory Management
```cpp
#include <unordered_set>

std::unordered_set<int> set;

// Reserve space to avoid rehashing
set.reserve(1000);

// Check load factor
float loadFactor = set.load_factor();
float maxLoadFactor = set.max_load_factor();
```

### Comparison: Set vs Unordered Set

| Feature | unordered_set | set |
|---------|---------------|-----|
| Implementation | Hash table | Red-black tree |
| Order | Unordered | Sorted |
| Time complexity | O(1) average | O(log n) |
| Space complexity | O(n) | O(n) |
| Element requirements | Hashable | Comparable |

### Time Complexity Summary

| Operation | Average | Worst Case |
|-----------|---------|------------|
| Insert | O(1) | O(n) |
| Delete | O(1) | O(n) |
| Search | O(1) | O(n) |
| Access | O(1) | O(n) |
