# 🚀 Basic DSA Algorithms: Complete Guide

## 📚 Overview

Basic algorithms form the foundation of computer science and problem-solving. These fundamental techniques are essential building blocks for more complex algorithms and are frequently used in coding interviews and real-world applications.

## 🎯 Key Concepts

### What are Basic Algorithms?
- **Sorting**: Arranging elements in a specific order
- **Searching**: Finding elements in data structures
- **Iteration**: Processing elements sequentially
- **Recursion**: Solving problems by breaking them into smaller subproblems

### Algorithm Analysis
- **Time Complexity**: How runtime grows with input size
- **Space Complexity**: How memory usage grows with input size
- **Stability**: Whether equal elements maintain relative order
- **In-place**: Whether algorithm uses constant extra space

## 🔄 Sorting Algorithms

### Bubble Sort
```cpp
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // If no swapping occurred, array is sorted
        if (!swapped) break;
    }
}

// Time Complexity: O(n²) worst/average, O(n) best
// Space Complexity: O(1)
// Stable: Yes
// In-place: Yes
```

### Selection Sort
```cpp
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        
        // Find minimum element in unsorted portion
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        
        // Swap with first element of unsorted portion
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

// Time Complexity: O(n²) always
// Space Complexity: O(1)
// Stable: No
// In-place: Yes
```

### Insertion Sort
```cpp
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Move elements greater than key one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        arr[j + 1] = key;
    }
}

// Time Complexity: O(n²) worst/average, O(n) best
// Space Complexity: O(1)
// Stable: Yes
// In-place: Yes
```

### Merge Sort
```cpp
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    
    // Merge two sorted subarrays
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    
    // Copy remaining elements
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    
    // Copy back to original array
    for (int p = 0; p < k; p++) {
        arr[left + p] = temp[p];
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSort(vector<int>& arr) {
    mergeSort(arr, 0, arr.size() - 1);
}

// Time Complexity: O(n log n) always
// Space Complexity: O(n)
// Stable: Yes
// In-place: No
```

### Quick Sort
```cpp
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quickSort(vector<int>& arr) {
    quickSort(arr, 0, arr.size() - 1);
}

// Time Complexity: O(n²) worst, O(n log n) average
// Space Complexity: O(log n) average, O(n) worst
// Stable: No
// In-place: Yes
```

## 🔍 Searching Algorithms

### Linear Search
```cpp
int linearSearch(const vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            return i;  // Found at index i
        }
    }
    return -1;  // Not found
}

// Time Complexity: O(n)
// Space Complexity: O(1)
```

### Binary Search
```cpp
int binarySearch(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;  // Found at index mid
        } else if (arr[mid] < target) {
            left = mid + 1;  // Search right half
        } else {
            right = mid - 1;  // Search left half
        }
    }
    
    return -1;  // Not found
}

// Recursive version
int binarySearchRecursive(const vector<int>& arr, int target, int left, int right) {
    if (left > right) return -1;
    
    int mid = left + (right - left) / 2;
    
    if (arr[mid] == target) return mid;
    if (arr[mid] < target) return binarySearchRecursive(arr, target, mid + 1, right);
    return binarySearchRecursive(arr, target, left, mid - 1);
}

// Time Complexity: O(log n)
// Space Complexity: O(1) iterative, O(log n) recursive
```

### Binary Search Variations
```cpp
// Find first occurrence
int findFirst(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1;  // Continue searching left
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// Find last occurrence
int findLast(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            left = mid + 1;  // Continue searching right
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// Find insertion point
int findInsertPosition(const vector<int>& arr, int target) {
    int left = 0, right = arr.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}
```

## 🔄 Iteration Techniques

### Array Traversal
```cpp
void traverseArray(const vector<int>& arr) {
    // Forward traversal
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // Reverse traversal
    for (int i = arr.size() - 1; i >= 0; i--) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // Two-pointer traversal
    int left = 0, right = arr.size() - 1;
    while (left < right) {
        cout << arr[left] << " " << arr[right] << " ";
        left++;
        right--;
    }
    if (left == right) {
        cout << arr[left];
    }
    cout << endl;
}
```

### Matrix Traversal
```cpp
void traverseMatrix(const vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    // Row-wise traversal
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    // Column-wise traversal
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    // Spiral traversal
    int top = 0, bottom = rows - 1;
    int left = 0, right = cols - 1;
    
    while (top <= bottom && left <= right) {
        // Top row
        for (int j = left; j <= right; j++) {
            cout << matrix[top][j] << " ";
        }
        top++;
        
        // Right column
        for (int i = top; i <= bottom; i++) {
            cout << matrix[i][right] << " ";
        }
        right--;
        
        // Bottom row
        if (top <= bottom) {
            for (int j = right; j >= left; j--) {
                cout << matrix[bottom][j] << " ";
            }
            bottom--;
        }
        
        // Left column
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                cout << matrix[i][left] << " ";
            }
            left++;
        }
    }
    cout << endl;
}
```

## 🔁 Recursion Basics

### Factorial
```cpp
int factorial(int n) {
    // Base case
    if (n <= 1) return 1;
    
    // Recursive case
    return n * factorial(n - 1);
}

// Tail recursive version
int factorialTail(int n, int acc = 1) {
    if (n <= 1) return acc;
    return factorialTail(n - 1, n * acc);
}
```

### Fibonacci
```cpp
int fibonacci(int n) {
    // Base cases
    if (n <= 1) return n;
    
    // Recursive case
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Memoized version
int fibonacciMemo(int n, vector<int>& memo) {
    if (n <= 1) return n;
    
    if (memo[n] != -1) return memo[n];
    
    memo[n] = fibonacciMemo(n - 1, memo) + fibonacciMemo(n - 2, memo);
    return memo[n];
}

int fibonacciMemo(int n) {
    vector<int> memo(n + 1, -1);
    return fibonacciMemo(n, memo);
}
```

### GCD (Greatest Common Divisor)
```cpp
int gcd(int a, int b) {
    // Base case
    if (b == 0) return a;
    
    // Recursive case
    return gcd(b, a % b);
}

// Iterative version
int gcdIterative(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
```

## 🎯 Common Problem Patterns

### Two Sum
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
    
    return {};  // No solution found
}
```

### Maximum Subarray Sum (Kadane's Algorithm)
```cpp
int maxSubArraySum(const vector<int>& nums) {
    int maxSoFar = nums[0];
    int maxEndingHere = nums[0];
    
    for (int i = 1; i < nums.size(); i++) {
        maxEndingHere = max(nums[i], maxEndingHere + nums[i]);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }
    
    return maxSoFar;
}
```

### Find Missing Number
```cpp
int findMissingNumber(const vector<int>& nums) {
    int n = nums.size();
    int expectedSum = n * (n + 1) / 2;
    int actualSum = 0;
    
    for (int num : nums) {
        actualSum += num;
    }
    
    return expectedSum - actualSum;
}

// XOR version (handles duplicates and multiple missing numbers)
int findMissingNumberXOR(const vector<int>& nums) {
    int result = 0;
    
    // XOR all numbers from 0 to n
    for (int i = 0; i <= nums.size(); i++) {
        result ^= i;
    }
    
    // XOR with all numbers in array
    for (int num : nums) {
        result ^= num;
    }
    
    return result;
}
```

### Reverse Array
```cpp
void reverseArray(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    
    while (left < right) {
        swap(arr[left], arr[right]);
        left++;
        right--;
    }
}

// Recursive version
void reverseArrayRecursive(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    
    swap(arr[left], arr[right]);
    reverseArrayRecursive(arr, left + 1, right - 1);
}
```

## 📝 Best Practices

### 1. Choose the Right Algorithm
```cpp
// Use Bubble/Selection/Insertion Sort when:
// - Array is small (n < 50)
// - Memory is very limited
// - Stability is required (Insertion Sort)

// Use Merge Sort when:
// - Stability is required
// - Guaranteed O(n log n) performance needed
// - Extra memory is available

// Use Quick Sort when:
// - Average case performance is priority
// - In-place sorting is required
// - Array is large
```

### 2. Handle Edge Cases
```cpp
void safeSort(vector<int>& arr) {
    // Check for empty array
    if (arr.empty()) return;
    
    // Check for single element
    if (arr.size() == 1) return;
    
    // Check for already sorted
    bool sorted = true;
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i-1]) {
            sorted = false;
            break;
        }
    }
    if (sorted) return;
    
    // Perform sorting
    sort(arr.begin(), arr.end());
}
```

### 3. Optimize for Specific Cases
```cpp
void optimizedSort(vector<int>& arr) {
    int n = arr.size();
    
    // Use insertion sort for small arrays
    if (n <= 10) {
        insertionSort(arr);
        return;
    }
    
    // Use quicksort for larger arrays
    quickSort(arr);
}
```

## 🚀 Performance Considerations

### Time Complexity Comparison
```
Algorithm          | Best  | Average | Worst  | Space | Stable
------------------|-------|---------|--------|-------|--------
Bubble Sort       | O(n)  | O(n²)   | O(n²)  | O(1)  | Yes
Selection Sort    | O(n²) | O(n²)   | O(n²)  | O(1)  | No
Insertion Sort    | O(n)  | O(n²)   | O(n²)  | O(1)  | Yes
Merge Sort        | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes
Quick Sort        | O(n log n) | O(n log n) | O(n²) | O(log n) | No
```

### When to Use Each Algorithm
```cpp
// Small arrays (n < 50): Insertion Sort
// Medium arrays (50 ≤ n < 1000): Quick Sort
// Large arrays (n ≥ 1000): Merge Sort or Quick Sort
// Nearly sorted arrays: Insertion Sort
// Memory constrained: Quick Sort or Insertion Sort
// Stability required: Merge Sort or Insertion Sort
```

## 🎯 Practice Problems

### Problem 1: Sort Colors (Dutch National Flag)
```cpp
void sortColors(vector<int>& nums) {
    int low = 0, mid = 0, high = nums.size() - 1;
    
    while (mid <= high) {
        if (nums[mid] == 0) {
            swap(nums[low], nums[mid]);
            low++;
            mid++;
        } else if (nums[mid] == 1) {
            mid++;
        } else {
            swap(nums[mid], nums[high]);
            high--;
        }
    }
}
```

### Problem 2: Find Peak Element
```cpp
int findPeakElement(const vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] < nums[mid + 1]) {
            left = mid + 1;  // Peak is on the right
        } else {
            right = mid;      // Peak is on the left
        }
    }
    
    return left;
}
```

### Problem 3: Rotate Array
```cpp
void rotateArray(vector<int>& nums, int k) {
    k %= nums.size();
    
    // Reverse entire array
    reverse(nums.begin(), nums.end());
    
    // Reverse first k elements
    reverse(nums.begin(), nums.begin() + k);
    
    // Reverse remaining elements
    reverse(nums.begin() + k, nums.end());
}
```

## 📚 Summary

Key takeaways:
- **Master fundamental algorithms** before moving to advanced ones
- **Understand time/space complexity** for algorithm selection
- **Consider stability and in-place requirements**
- **Use appropriate algorithms** for different input sizes
- **Practice edge cases** and optimization techniques
- **Combine algorithms** for complex problems

These basic algorithms are the foundation for solving more complex problems. Master them thoroughly!

---

## 🔗 Related Topics
- [Complexity Analysis](complexity-analysis.md)
- [Basic Data Structures](basic-data-structures.md)
- [Two Pointers](patterns/two-pointers.md)
- [Binary Search](patterns/binary-search.md)
