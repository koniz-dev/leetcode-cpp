# 🟢 Time & Space Complexity Analysis

## 📚 Overview
Complexity analysis is the study of how algorithms perform as input size grows. It helps us compare different solutions and choose the most efficient approach for a given problem.

---

## 🎯 Why Complexity Analysis Matters?

### Real-World Impact
- **Performance**: Faster algorithms save time and resources
- **Scalability**: Good algorithms work efficiently with large datasets
- **Resource Management**: Efficient algorithms use less memory and CPU
- **User Experience**: Faster response times improve user satisfaction

### Example: Search Algorithm Comparison
```cpp
// Linear Search: O(n)
int linearSearch(vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

// Binary Search: O(log n) - requires sorted array
int binarySearch(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
```

**Performance Comparison:**
- Array size: 1,000,000 elements
- Linear Search: ~500,000 comparisons (average)
- Binary Search: ~20 comparisons (worst case)
- **Binary Search is ~25,000x faster!**

---

## ⏱️ Time Complexity

### Definition
**Time Complexity** measures how the execution time of an algorithm grows as the input size increases.

### Big O Notation
We use **Big O notation** to describe the upper bound of an algorithm's growth rate.

```cpp
// O(1) - Constant Time
int getFirstElement(vector<int>& arr) {
    return arr[0];  // Always takes same time regardless of array size
}

// O(n) - Linear Time
int findMax(vector<int>& arr) {
    int max = arr[0];
    for (int i = 1; i < arr.size(); i++) {  // Loop runs n times
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

// O(n²) - Quadratic Time
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {           // Outer loop: n times
        for (int j = 0; j < n - i - 1; j++) {   // Inner loop: n times
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
```

### Common Time Complexities

| Complexity | Name | Example | Description |
|------------|------|---------|-------------|
| O(1) | Constant | Array access | Time doesn't change with input size |
| O(log n) | Logarithmic | Binary search | Time grows slowly with input size |
| O(n) | Linear | Linear search | Time grows proportionally with input size |
| O(n log n) | Linearithmic | Merge sort | Common for efficient sorting algorithms |
| O(n²) | Quadratic | Bubble sort | Time grows quadratically with input size |
| O(n³) | Cubic | 3 nested loops | Time grows cubically with input size |
| O(2ⁿ) | Exponential | Recursive Fibonacci | Time grows exponentially (very slow) |
| O(n!) | Factorial | Traveling salesman | Time grows factorially (extremely slow) |

---

## 💾 Space Complexity

### Definition
**Space Complexity** measures how much additional memory an algorithm uses beyond the input data.

### Types of Space Usage
```cpp
// O(1) - Constant Space
int findMax(vector<int>& arr) {
    int max = arr[0];                    // 1 variable
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > max) max = arr[i];  // Same variable reused
    }
    return max;
}

// O(n) - Linear Space
vector<int> reverseArray(vector<int>& arr) {
    vector<int> result(arr.size());      // New array of size n
    for (int i = 0; i < arr.size(); i++) {
        result[i] = arr[arr.size() - 1 - i];
    }
    return result;
}

// O(n²) - Quadratic Space
vector<vector<int>> createMatrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n));  // n × n matrix
    return matrix;
}
```

### Space Complexity Categories

| Complexity | Name | Example | Description |
|------------|------|---------|-------------|
| O(1) | Constant | In-place algorithms | Uses fixed amount of extra memory |
| O(log n) | Logarithmic | Recursive algorithms | Memory grows with recursion depth |
| O(n) | Linear | Creating new arrays | Memory proportional to input size |
| O(n²) | Quadratic | 2D arrays | Memory grows quadratically |

---

## 🔍 Analyzing Algorithm Complexity

### Step-by-Step Analysis

#### Example 1: Simple Loop
```cpp
void printNumbers(int n) {
    for (int i = 0; i < n; i++) {
        cout << i << " ";
    }
}
```

**Analysis:**
- Loop runs `n` times
- Each iteration: 1 operation (print)
- **Time Complexity: O(n)**
- **Space Complexity: O(1)** (only 1 variable `i`)

#### Example 2: Nested Loops
```cpp
void printMatrix(int n) {
    for (int i = 0; i < n; i++) {           // Outer loop: n times
        for (int j = 0; j < n; j++) {       // Inner loop: n times
            cout << "(" << i << "," << j << ") ";
        }
        cout << endl;
    }
}
```

**Analysis:**
- Outer loop: `n` iterations
- Inner loop: `n` iterations per outer iteration
- Total operations: `n × n = n²`
- **Time Complexity: O(n²)**
- **Space Complexity: O(1)** (only variables `i` and `j`)

#### Example 3: Recursive Function
```cpp
int factorial(int n) {
    if (n <= 1) return 1;           // Base case
    return n * factorial(n - 1);     // Recursive case
}
```

**Analysis:**
- Function calls itself `n` times
- Each call: 1 multiplication operation
- **Time Complexity: O(n)**
- **Space Complexity: O(n)** (call stack depth)

#### Example 4: Array Operations
```cpp
int findDuplicate(vector<int>& arr) {
    unordered_set<int> seen;        // Hash set
    for (int num : arr) {           // Loop: n times
        if (seen.count(num)) {      // Hash lookup: O(1) average
            return num;
        }
        seen.insert(num);            // Hash insert: O(1) average
    }
    return -1;
}
```

**Analysis:**
- Loop runs `n` times
- Each iteration: O(1) hash operations
- **Time Complexity: O(n)**
- **Space Complexity: O(n)** (hash set can store up to n elements)

---

## 📊 Complexity Comparison Examples

### Example 1: Finding Maximum Element

```cpp
// Approach 1: Linear Search - O(n) time, O(1) space
int findMaxLinear(vector<int>& arr) {
    int max = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

// Approach 2: Sorting + Get Last - O(n log n) time, O(1) space
int findMaxSort(vector<int>& arr) {
    sort(arr.begin(), arr.end());    // O(n log n)
    return arr.back();               // O(1)
}

// Approach 3: Using STL - O(n) time, O(1) space
int findMaxSTL(vector<int>& arr) {
    return *max_element(arr.begin(), arr.end());  // O(n)
}
```

**Best Choice:** Approach 1 or 3 (both O(n) time, O(1) space)

### Example 2: Checking for Duplicates

```cpp
// Approach 1: Brute Force - O(n²) time, O(1) space
bool hasDuplicateBrute(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[i] == arr[j]) return true;
        }
    }
    return false;
}

// Approach 2: Sorting + Linear Scan - O(n log n) time, O(1) space
bool hasDuplicateSort(vector<int>& arr) {
    sort(arr.begin(), arr.end());
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] == arr[i - 1]) return true;
    }
    return false;
}

// Approach 3: Hash Set - O(n) time, O(n) space
bool hasDuplicateHash(vector<int>& arr) {
    unordered_set<int> seen;
    for (int num : arr) {
        if (seen.count(num)) return true;
        seen.insert(num);
    }
    return false;
}
```

**Best Choice:** 
- **Space priority:** Approach 2 (O(n log n) time, O(1) space)
- **Time priority:** Approach 3 (O(n) time, O(n) space)

---

## 🎯 Best, Worst, and Average Case Analysis

### Example: Linear Search
```cpp
int linearSearch(vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}
```

**Cases:**
- **Best Case:** Target is first element → O(1)
- **Worst Case:** Target not found or last element → O(n)
- **Average Case:** Target is in middle → O(n/2) = O(n)

### Example: Quick Sort
```cpp
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
```

**Cases:**
- **Best Case:** Pivot always divides array in half → O(n log n)
- **Worst Case:** Pivot always smallest/largest → O(n²)
- **Average Case:** Random pivot → O(n log n)

---

## 🚨 Common Complexity Mistakes

### Mistake 1: Ignoring Hidden Operations
```cpp
// Wrong analysis: O(n)
void wrongAnalysis(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        arr.insert(arr.begin(), i);  // O(n) operation!
    }
}
// Correct: O(n²) - insert at beginning is O(n)
```

### Mistake 2: Confusing Time vs Space
```cpp
// Time: O(n), Space: O(n)
vector<int> createArray(int n) {
    vector<int> result;
    for (int i = 0; i < n; i++) {
        result.push_back(i);  // O(1) amortized
    }
    return result;
}
```

### Mistake 3: Ignoring Constants
```cpp
// Both are O(n), but first is faster
void fastVersion(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i];  // 1 operation
    }
}

void slowVersion(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";  // 2 operations
    }
}
```

---

## 🧪 Practice Problems

### Problem 1: Analyze Time Complexity
```cpp
void mysteryFunction(int n) {
    for (int i = 1; i <= n; i *= 2) {
        for (int j = 1; j <= i; j++) {
            cout << "Hello" << endl;
        }
    }
}
```

**Solution:**
- Outer loop: `i` doubles each time (1, 2, 4, 8, ..., n)
- Runs log₂(n) times
- Inner loop: runs `i` times
- Total operations: 1 + 2 + 4 + 8 + ... + n = 2n - 1
- **Time Complexity: O(n)**

### Problem 2: Analyze Space Complexity
```cpp
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
```

**Solution:**
- Function calls itself recursively
- Maximum call stack depth: n
- **Space Complexity: O(n)**

---

## 📚 What's Next?

After understanding complexity analysis, explore:
1. **Algorithm Design Techniques** - Divide and conquer, dynamic programming
2. **Data Structure Selection** - Choosing the right tool for the job
3. **Optimization Strategies** - Improving existing algorithms
4. **Advanced Analysis** - Amortized analysis, probabilistic analysis

---

## 🔗 Related Topics
- [Introduction to DSA](introduction.md)
- [Basic Data Structures](basic-data-structures.md)
- [Simple Algorithms](basic-algorithms.md)
- [Algorithm Design Techniques](algorithm-design.md)

---

## 💡 Key Takeaways

1. **Big O notation** describes growth rate, not exact time
2. **Time complexity** is usually more important than space complexity
3. **Always consider** best, worst, and average cases
4. **Practice analyzing** algorithms step by step
5. **Choose algorithms** based on problem constraints and requirements

---

*"The first rule of optimization: Don't do it. The second rule: Don't do it yet." - Michael A. Jackson*
