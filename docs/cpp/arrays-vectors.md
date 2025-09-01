# 🚀 C++ Arrays & Vectors: Complete Guide

## 📚 Overview

Arrays and vectors are fundamental data structures in C++ for storing collections of elements. Understanding their differences, usage patterns, and best practices is crucial for efficient programming.

## 🎯 Key Concepts

### Arrays vs Vectors
- **Arrays**: Fixed-size, stack-allocated, C-style
- **Vectors**: Dynamic-size, heap-allocated, C++ STL container
- **Performance**: Arrays are faster, vectors are more flexible

## 🔧 C-Style Arrays

### Basic Array Declaration
```cpp
#include <iostream>
using namespace std;

int main() {
    // Fixed-size array declaration
    int numbers[5] = {1, 2, 3, 4, 5};
    
    // Array without initializer (contains garbage values)
    int scores[10];
    
    // Array with partial initialization
    int partial[5] = {1, 2};  // {1, 2, 0, 0, 0}
    
    // Array size inference
    int autoSize[] = {1, 2, 3, 4, 5};  // Size = 5
    
    return 0;
}
```

### Array Access and Iteration
```cpp
int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    
    // Accessing elements
    cout << "First element: " << arr[0] << endl;    // 10
    cout << "Last element: " << arr[4] << endl;     // 50
    
    // Iterating with for loop
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // Range-based for loop (C++11)
    for (int element : arr) {
        cout << element << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Multi-dimensional Arrays
```cpp
int main() {
    // 2D array
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    // Accessing 2D array
    cout << "Center element: " << matrix[1][1] << endl;  // 5
    
    // Iterating 2D array
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    // 3D array
    int cube[2][2][2] = {
        {{1, 2}, {3, 4}},
        {{5, 6}, {7, 8}}
    };
    
    return 0;
}
```

### Array as Function Parameters
```cpp
// Pass by value (creates copy)
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Pass by reference (modifies original)
void modifyArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;  // Double each element
    }
}

// Pass by const reference (read-only)
void printArrayConst(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
        // arr[i] = 0;  // Error: can't modify const array
    }
    cout << endl;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = 5;
    
    printArray(numbers, size);
    modifyArray(numbers, size);
    printArray(numbers, size);
    
    return 0;
}
```

## 🚀 STL Vectors

### Basic Vector Operations
```cpp
#include <vector>
#include <iostream>
using namespace std;

int main() {
    // Vector declaration
    vector<int> numbers;
    
    // Adding elements
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    
    // Vector with initial size
    vector<int> scores(5);  // 5 elements with default value 0
    
    // Vector with initial size and value
    vector<int> filled(3, 42);  // 3 elements with value 42
    
    // Vector with initializer list
    vector<int> initial = {1, 2, 3, 4, 5};
    
    return 0;
}
```

### Vector Access and Iteration
```cpp
int main() {
    vector<int> vec = {10, 20, 30, 40, 50};
    
    // Accessing elements
    cout << "First: " << vec.front() << endl;    // 10
    cout << "Last: " << vec.back() << endl;     // 50
    cout << "Index 2: " << vec[2] << endl;      // 30
    cout << "Index 2 (safe): " << vec.at(2) << endl;  // 30
    
    // Size and capacity
    cout << "Size: " << vec.size() << endl;           // 5
    cout << "Capacity: " << vec.capacity() << endl;   // 5
    cout << "Empty: " << vec.empty() << endl;         // false
    
    // Iterating with index
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
    
    // Range-based for loop
    for (int element : vec) {
        cout << element << " ";
    }
    cout << endl;
    
    // Iterator-based loop
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Vector Modifications
```cpp
int main() {
    vector<int> vec = {1, 2, 3};
    
    // Adding elements
    vec.push_back(4);        // Add to end
    vec.insert(vec.begin(), 0);  // Insert at beginning
    vec.insert(vec.begin() + 2, 25);  // Insert at position 2
    
    // Removing elements
    vec.pop_back();          // Remove from end
    vec.erase(vec.begin());  // Remove first element
    vec.erase(vec.begin() + 1, vec.begin() + 3);  // Remove range
    
    // Resizing
    vec.resize(5);           // Resize to 5 elements
    vec.resize(8, 100);      // Resize to 8, fill new with 100
    
    // Clearing
    vec.clear();              // Remove all elements
    
    return 0;
}
```

### Vector Memory Management
```cpp
int main() {
    vector<int> vec;
    
    // Reserve capacity to avoid reallocation
    vec.reserve(1000);  // Pre-allocate space for 1000 elements
    
    cout << "Capacity: " << vec.capacity() << endl;  // 1000
    
    // Add elements (no reallocation until capacity is exceeded)
    for (int i = 0; i < 1000; i++) {
        vec.push_back(i);
    }
    
    // Shrink to fit (reduce capacity to match size)
    vec.shrink_to_fit();
    
    // Swap to clear memory
    vector<int>().swap(vec);  // Clear and free memory
    
    return 0;
}
```

### Multi-dimensional Vectors
```cpp
int main() {
    // 2D vector
    vector<vector<int>> matrix(3, vector<int>(3, 0));
    
    // Initialize 2D vector
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = i * 3 + j + 1;
        }
    }
    
    // Accessing elements
    cout << "Center: " << matrix[1][1] << endl;  // 5
    
    // 3D vector
    vector<vector<vector<int>>> cube(2, 
        vector<vector<int>>(2, vector<int>(2, 0)));
    
    return 0;
}
```

## 🔄 Common Array/Vector Operations

### Searching
```cpp
#include <algorithm>

int main() {
    vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6};
    
    // Find element
    auto it = find(vec.begin(), vec.end(), 5);
    if (it != vec.end()) {
        cout << "Found 5 at position: " << (it - vec.begin()) << endl;
    }
    
    // Find minimum and maximum
    auto minIt = min_element(vec.begin(), vec.end());
    auto maxIt = max_element(vec.begin(), vec.end());
    cout << "Min: " << *minIt << ", Max: " << *maxIt << endl;
    
    // Binary search (requires sorted vector)
    sort(vec.begin(), vec.end());
    bool found = binary_search(vec.begin(), vec.end(), 5);
    cout << "5 found: " << found << endl;
    
    return 0;
}
```

### Sorting and Manipulation
```cpp
int main() {
    vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6};
    
    // Sort in ascending order
    sort(vec.begin(), vec.end());
    
    // Sort in descending order
    sort(vec.begin(), vec.end(), greater<int>());
    
    // Reverse
    reverse(vec.begin(), vec.end());
    
    // Remove duplicates (requires sorted vector)
    sort(vec.begin(), vec.end());
    auto last = unique(vec.begin(), vec.end());
    vec.erase(last, vec.end());
    
    // Rotate
    rotate(vec.begin(), vec.begin() + 2, vec.end());
    
    return 0;
}
```

### Mathematical Operations
```cpp
#include <numeric>

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};
    
    // Sum of all elements
    int sum = accumulate(vec.begin(), vec.end(), 0);
    cout << "Sum: " << sum << endl;  // 15
    
    // Product of all elements
    int product = accumulate(vec.begin(), vec.end(), 1, multiplies<int>());
    cout << "Product: " << product << endl;  // 120
    
    // Count elements
    int count = count(vec.begin(), vec.end(), 3);
    cout << "Count of 3: " << count << endl;  // 1
    
    return 0;
}
```

## 🎯 Performance Considerations

### Array vs Vector Performance
```cpp
#include <chrono>

void benchmark() {
    const int size = 1000000;
    
    // C-style array
    int* arr = new int[size];
    auto start = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto arr_time = chrono::duration_cast<chrono::microseconds>(end - start);
    
    delete[] arr;
    
    // Vector
    vector<int> vec(size);
    start = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < size; i++) {
        vec[i] = i;
    }
    
    end = chrono::high_resolution_clock::now();
    auto vec_time = chrono::duration_cast<chrono::microseconds>(end - start);
    
    cout << "Array time: " << arr_time.count() << " μs" << endl;
    cout << "Vector time: " << vec_time.count() << " μs" << endl;
}
```

### Memory Layout
```cpp
int main() {
    // Arrays: contiguous memory, cache-friendly
    int arr[5] = {1, 2, 3, 4, 5};
    
    // Vectors: also contiguous memory
    vector<int> vec = {1, 2, 3, 4, 5};
    
    // Pointer arithmetic works with both
    int* arrPtr = arr;
    int* vecPtr = &vec[0];
    
    cout << "Array pointer: " << arrPtr << endl;
    cout << "Vector pointer: " << vecPtr << endl;
    
    return 0;
}
```

## 📝 Best Practices

### 1. Choose the Right Container
```cpp
// Use arrays when:
// - Size is known at compile time
// - Maximum performance is needed
// - Memory is limited

// Use vectors when:
// - Size is dynamic
// - Need STL algorithms
// - Want automatic memory management
```

### 2. Memory Management
```cpp
// Good: Reserve capacity when you know size
vector<int> vec;
vec.reserve(1000);
for (int i = 0; i < 1000; i++) {
    vec.push_back(i);
}

// Bad: Frequent reallocation
vector<int> vec;
for (int i = 0; i < 1000; i++) {
    vec.push_back(i);  // May cause multiple reallocations
}
```

### 3. Bounds Checking
```cpp
// Good: Use .at() for bounds checking in debug builds
try {
    int value = vec.at(index);
} catch (const out_of_range& e) {
    cout << "Index out of range: " << e.what() << endl;
}

// Good: Check bounds manually
if (index >= 0 && index < vec.size()) {
    int value = vec[index];
}
```

### 4. Iterator Safety
```cpp
// Good: Check if iterator is valid
auto it = find(vec.begin(), vec.end(), value);
if (it != vec.end()) {
    // Use iterator safely
    cout << "Found at: " << (it - vec.begin()) << endl;
}

// Bad: Assume iterator is valid
auto it = find(vec.begin(), vec.end(), value);
cout << "Found at: " << (it - vec.begin()) << endl;  // May crash
```

## 🚀 Advanced Techniques

### Custom Comparators
```cpp
struct Person {
    string name;
    int age;
};

int main() {
    vector<Person> people = {
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 20}
    };
    
    // Sort by age
    sort(people.begin(), people.end(), 
         [](const Person& a, const Person& b) {
             return a.age < b.age;
         });
    
    // Sort by name
    sort(people.begin(), people.end(),
         [](const Person& a, const Person& b) {
             return a.name < b.name;
         });
    
    return 0;
}
```

### Move Semantics
```cpp
vector<int> createLargeVector() {
    vector<int> vec(1000000, 42);
    return vec;  // RVO/move semantics avoid copying
}

int main() {
    // Efficient: no copying
    vector<int> result = createLargeVector();
    
    // Also efficient: move constructor
    vector<int> moved = move(result);
    
    return 0;
}
```

## 🎯 Practice Problems

### Problem 1: Find Missing Number
```cpp
int findMissingNumber(const vector<int>& nums) {
    int n = nums.size();
    int expectedSum = n * (n + 1) / 2;
    int actualSum = accumulate(nums.begin(), nums.end(), 0);
    return expectedSum - actualSum;
}
```

### Problem 2: Rotate Array
```cpp
void rotateArray(vector<int>& nums, int k) {
    k %= nums.size();
    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin() + k);
    reverse(nums.begin() + k, nums.end());
}
```

### Problem 3: Two Sum
```cpp
vector<int> twoSum(const vector<int>& nums, int target) {
    unordered_map<int, int> seen;
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        if (seen.count(complement)) {
            return {seen[complement], i};
        }
        seen[nums[i]] = i;
    }
    return {};
}
```

## 📚 Summary

Key takeaways:
- **Arrays**: Fixed-size, fast, stack-allocated
- **Vectors**: Dynamic-size, flexible, heap-allocated
- **Choose wisely** based on requirements
- **Use STL algorithms** for common operations
- **Manage memory** efficiently with reserve/resize
- **Bounds checking** is important for safety

Master these concepts to write efficient, safe C++ code!

---

## 🔗 Related Topics
- [Data Types](data-types.md)
- [Functions](functions.md)
- [STL Containers](stl-containers.md)
- [STL Algorithms](stl-algorithms.md)
