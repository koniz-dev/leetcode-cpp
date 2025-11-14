# [74. Search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/)

## Problem Statement

You are given an `m x n` integer matrix `matrix` with the following two properties:

- Each row is sorted in non-decreasing order.
- The first integer of each row is greater than the last integer of the previous row.

Given an integer `target`, return `true` if `target` is in `matrix` or `false` otherwise.

You must write a solution in `O(log(m * n))` time complexity.

**Example 1:**
```
Input: matrix = [[1,4,7,11],[2,5,8,12],[3,6,9,16],[10,13,14,17]], target = 5
Output: true
```

**Example 2:**
```
Input: matrix = [[1,4,7,11],[2,5,8,12],[3,6,9,16],[10,13,14,17]], target = 3
Output: false
```

**Constraints:**
- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= m, n <= 100`
- `-10^4 <= matrix[i][j], target <= 10^4`

## Approach Analysis

### Approach 1: Binary Search on Flattened Array (Optimized Solution)
**Time Complexity:** O(log(m\*n)) - Binary search on m*n elements  
**Space Complexity:** O(1) - Only using constant extra space

The key insight is that the matrix can be treated as a single sorted 1D array due to its properties:
1. Each row is sorted
2. First element of each row > last element of previous row

This means the entire matrix is effectively a sorted array when flattened.

**Algorithm:**
1. **Flatten the Matrix Conceptually** - Treat the 2D matrix as a 1D array with `m * n` elements
2. **Binary Search** - Use standard binary search on the virtual flattened array
3. **Index Conversion** - Convert 1D index to 2D coordinates:
   - `row = index / n` (integer division)
   - `col = index % n` (modulo operation)
4. **Compare and Narrow** - Compare middle element with target and narrow search range

**Key DSA Concepts:**
- **Binary Search**: Efficient search algorithm for sorted data
- **Index Mapping**: Converting between 1D and 2D indices
- **Divide and Conquer**: Eliminating half of search space each iteration

### Approach 2: Two-Step Binary Search
**Time Complexity:** O(log m + log n) - Binary search on rows, then columns  
**Space Complexity:** O(1) - Constant extra space

First find the correct row, then search within that row:

```cpp
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size();
    int n = matrix[0].size();
    
    // Step 1: Binary search to find the correct row
    int top = 0, bottom = m - 1;
    while (top <= bottom) {
        int midRow = top + (bottom - top) / 2;
        
        if (target < matrix[midRow][0]) {
            bottom = midRow - 1;
        } else if (target > matrix[midRow][n - 1]) {
            top = midRow + 1;
        } else {
            // Target is in this row, search within it
            int left = 0, right = n - 1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (matrix[midRow][mid] == target) {
                    return true;
                } else if (matrix[midRow][mid] < target) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            return false;
        }
    }
    
    return false;
}
```

**Trade-offs:**
- Same time complexity: O(log m + log n) = O(log(m*n))
- More code complexity with two separate binary searches
- Flattened approach is simpler and cleaner

### Approach 3: Linear Search
**Time Complexity:** O(m*n) - Check every element  
**Space Complexity:** O(1) - Constant extra space

Simple nested loops to check every element:

```cpp
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] == target) {
                return true;
            }
        }
    }
    return false;
}
```

**When to Use:**
- Matrix is not sorted
- Matrix is very small
- Need to find all occurrences

## Solution Implementations

### Binary Search on Flattened Array (optimized.cpp)
See `optimized.cpp` for the complete binary search implementation treating the matrix as a flattened sorted array with comprehensive comments and index conversion logic.

### Binary Search on Flattened Array (main.cpp)
See `main.cpp` for the user's personal implementation using the same binary search approach.

## Complexity Analysis

### Time Complexity: O(log(m*n))
- **Logarithmic Growth**: Each iteration reduces the search space by half
- **Total Elements**: Searching through m*n elements
- **Mathematical Proof**: After k iterations, search space is (m*n)/(2^k)
- **Termination**: When (m\*n)/(2^k) = 1, we have k = log₂(m*n)
- **Example**: For 10x10 matrix (100 elements), at most 7 iterations needed

### Space Complexity: O(1)
- **Constant Space**: Only using a few variables (left, right, mid, m, n)
- **No Extra Data Structures**: No arrays, maps, or stacks needed
- **In-place Operations**: All operations work on the original matrix

## Key Learning Points

### 1. Matrix Properties Enable Binary Search
- **Row-wise Sorted**: Each row is sorted in non-decreasing order
- **Column-wise Sorted**: First element of row > last element of previous row
- **Combined Effect**: Entire matrix is effectively a sorted 1D array

### 2. Index Conversion (1D ↔ 2D)
- **1D to 2D**: Given index `i` in flattened array:
  - `row = i / n` (integer division)
  - `col = i % n` (modulo operation)
- **2D to 1D**: Given `(row, col)`:
  - `index = row * n + col`
- **Example**: In 3x4 matrix, index 7 → row 1, col 3 (7/4=1, 7%4=3)

### 3. Overflow Prevention
- **Safe Middle Calculation**: Use `left + (right - left) / 2` instead of `(left + right) / 2`
- **Why Important**: When `left` and `right` are large, `left + right` can overflow
- **Example**: If `left = 2,000,000,000` and `right = 2,000,000,000`, sum overflows

### 4. Binary Search Template for 2D Matrix
```cpp
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size();
    int n = matrix[0].size();
    int left = 0, right = m * n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cell = matrix[mid / n][mid % n];
        
        if (cell == target) return true;
        else if (cell < target) left = mid + 1;
        else right = mid - 1;
    }
    
    return false;
}
```

## Common Pitfalls

### 1. Incorrect Index Conversion
- **Wrong**: `row = mid % m, col = mid / m` (incorrect for row-major order)
- **Correct**: `row = mid / n, col = mid % n` (row-major order)
- **Remember**: Integer division gives row, modulo gives column

### 2. Off-by-One Errors
- **Wrong**: `right = m * n` (should be `m * n - 1`)
- **Wrong**: `while (left < right)` (misses single element case)
- **Wrong**: `left = mid` (should be `mid + 1` to avoid infinite loop)

### 3. Integer Overflow
- **Wrong**: `int mid = (left + right) / 2;`
- **Correct**: `int mid = left + (right - left) / 2;`

### 4. Assuming Matrix is Square
- **Wrong**: Using `m` for both row and column calculations
- **Correct**: Use `n` (number of columns) for index conversion

## Related Problems
- [240. Search a 2D Matrix II](https://leetcode.com/problems/search-a-2d-matrix-ii/) - Different matrix properties (sorted rows and columns)
- [35. Search Insert Position](https://leetcode.com/problems/search-insert-position/) - Binary search with insertion point
- [704. Binary Search](https://leetcode.com/problems/binary-search/) - Basic binary search on 1D array
- [33. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/) - Binary search on rotated array
- [162. Find Peak Element](https://leetcode.com/problems/find-peak-element/) - Binary search variant

## C++ Features Demonstrated

### Modern C++ Features
- **References**: `vector<vector<int>>&` for efficient parameter passing
- **RAII**: Automatic memory management with `vector`
- **STL Containers**: Using `vector<vector<int>>` for 2D dynamic arrays

### Best Practices
- **Overflow Safety**: Safe middle calculation prevents integer overflow
- **Clear Variable Names**: `m`, `n`, `left`, `right`, `mid` are self-documenting
- **Early Return**: Return immediately when target is found
- **Const Correctness**: Consider using `const vector<vector<int>>&` if not modifying

## Practice Tips
1. **Master Index Conversion**: Practice converting between 1D and 2D indices
2. **Visualize the Flattening**: Draw the matrix and trace the flattened indices
3. **Handle Edge Cases**: Empty matrix, single element, target at boundaries
4. **Understand Matrix Properties**: Recognize when a 2D structure can be treated as 1D
5. **Practice Variants**: Try problems with different matrix properties (like problem 240)

This problem demonstrates how understanding data structure properties can lead to elegant solutions. The key insight is recognizing that the matrix properties make it equivalent to a sorted 1D array, enabling direct binary search.

