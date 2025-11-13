# [704. Binary Search](https://leetcode.com/problems/binary-search/)

## Problem Statement

Given an array of integers `nums` which is sorted in ascending order, and an integer `target`, write a function to search `target` in `nums`. If `target` exists, then return its index. Otherwise, return `-1`.

You must write an algorithm with `O(log n)` runtime complexity.

**Example 1:**
```
Input: nums = [-1,0,3,5,9,12], target = 9
Output: 4
Explanation: 9 exists in nums and its index is 4
```

**Example 2:**
```
Input: nums = [-1,0,3,5,9,12], target = 2
Output: -1
Explanation: 2 does not exist in nums so return -1
```

**Constraints:**
- `1 <= nums.length <= 10^4`
- `-10^4 < nums[i], target < 10^4`
- All the integers in `nums` are unique
- `nums` is sorted in ascending order

## Approach Analysis

### Approach 1: Binary Search (Optimized Solution)
**Time Complexity:** O(log n) - Each iteration eliminates half of the search space  
**Space Complexity:** O(1) - Only using constant extra space

The binary search algorithm is the optimal solution for searching in a sorted array. It works by:

1. **Two Pointers Technique** - Use `left` and `right` pointers to define the search range
2. **Middle Element Comparison** - Calculate middle index and compare with target
3. **Divide and Conquer** - Eliminate half of the search space in each iteration
4. **Termination Condition** - Continue until `left > right` (target not found) or target is found

**Key DSA Concepts:**
- **Binary Search**: Efficient search algorithm for sorted arrays
- **Divide and Conquer**: Breaking problem into smaller subproblems
- **Two Pointers**: Using two indices to track search boundaries

### Approach 2: Linear Search
**Time Complexity:** O(n) - Need to check every element in worst case  
**Space Complexity:** O(1) - Constant extra space

Simple linear search through the array:

```cpp
int search(vector<int>& nums, int target) {
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == target) {
            return i;
        }
    }
    return -1;
}
```

**When to Use:**
- Array is not sorted
- Array is very small
- Need to find all occurrences

### Approach 3: Recursive Binary Search
**Time Complexity:** O(log n) - Same as iterative  
**Space Complexity:** O(log n) - Recursion stack depth

Recursive implementation of binary search:

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        return binarySearch(nums, target, 0, nums.size() - 1);
    }
    
private:
    int binarySearch(vector<int>& nums, int target, int left, int right) {
        if (left > right) {
            return -1;  // Base case: target not found
        }
        
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            return binarySearch(nums, target, mid + 1, right);
        } else {
            return binarySearch(nums, target, left, mid - 1);
        }
    }
};
```

**Trade-offs:**
- More elegant code structure
- Higher space complexity due to recursion stack
- Iterative version is generally preferred for performance

## Solution Implementations

### Binary Search Solution (optimized.cpp)
See `optimized.cpp` for the complete iterative binary search implementation with comprehensive comments and overflow-safe middle calculation.

### Binary Search Solution (main.cpp)
See `main.cpp` for the user's personal implementation using the same binary search approach.

## Complexity Analysis

### Time Complexity: O(log n)
- **Logarithmic Growth**: Each iteration reduces the search space by half
- **Mathematical Proof**: After k iterations, search space is n/(2^k)
- **Termination**: When n/(2^k) = 1, we have k = log₂(n)
- **Example**: For array of size 1024, at most 10 iterations needed

### Space Complexity: O(1)
- **Constant Space**: Only using a few variables (left, right, mid)
- **No Extra Data Structures**: No arrays, maps, or stacks needed
- **Iterative Approach**: No recursion stack overhead

## Key Learning Points

### 1. Binary Search Prerequisites
- **Sorted Array**: Binary search only works on sorted arrays
- **Unique Elements**: Problem guarantees unique integers (simplifies logic)
- **Comparable Elements**: Elements must support comparison operations

### 2. Overflow Prevention
- **Safe Middle Calculation**: Use `left + (right - left) / 2` instead of `(left + right) / 2`
- **Why Important**: When `left` and `right` are large, `left + right` can overflow
- **Example**: If `left = 2,000,000,000` and `right = 2,000,000,000`, sum overflows

### 3. Boundary Conditions
- **Inclusive Range**: `left <= right` ensures we check all valid positions
- **Exclusive Updates**: `left = mid + 1` and `right = mid - 1` exclude already-checked mid
- **Termination**: When `left > right`, we've exhausted all possibilities

### 4. Binary Search Template
```cpp
int binarySearch(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) return mid;
        else if (nums[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    
    return -1;  // Not found
}
```

## Common Pitfalls

### 1. Off-by-One Errors
- **Wrong**: `right = nums.size()` (should be `nums.size() - 1`)
- **Wrong**: `while (left < right)` (misses single element case)
- **Wrong**: `left = mid` (should be `mid + 1` to avoid infinite loop)

### 2. Integer Overflow
- **Wrong**: `int mid = (left + right) / 2;`
- **Correct**: `int mid = left + (right - left) / 2;`

### 3. Unsorted Array
- Binary search **requires** sorted array
- If array is not sorted, use linear search or sort first

## Related Problems
- [35. Search Insert Position](https://leetcode.com/problems/search-insert-position/) - Binary search with insertion point
- [34. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/) - Binary search variants
- [33. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/) - Binary search on rotated array
- [69. Sqrt(x)](https://leetcode.com/problems/sqrtx/) - Binary search for square root
- [278. First Bad Version](https://leetcode.com/problems/first-bad-version/) - Binary search with boolean condition
- [162. Find Peak Element](https://leetcode.com/problems/find-peak-element/) - Binary search on unsorted array

## C++ Features Demonstrated

### Modern C++ Features
- **References**: `vector<int>&` for efficient parameter passing
- **RAII**: Automatic memory management with `vector`
- **STL Containers**: Using `vector` for dynamic arrays

### Best Practices
- **Overflow Safety**: Safe middle calculation prevents integer overflow
- **Clear Variable Names**: `left`, `right`, `mid` are self-documenting
- **Early Return**: Return immediately when target is found
- **Const Correctness**: Consider using `const vector<int>&` if not modifying

## Practice Tips
1. **Master the Template**: Memorize the binary search template for interviews
2. **Handle Edge Cases**: Empty array, single element, target at boundaries
3. **Understand Invariants**: What does `left` and `right` represent at each step?
4. **Practice Variants**: Search for insertion point, first/last occurrence, etc.
5. **Visualize**: Draw the array and trace through the algorithm

Binary search is one of the most fundamental algorithms in computer science and appears frequently in coding interviews. Mastering it is essential for efficient problem-solving.
