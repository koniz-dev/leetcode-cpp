# 217. Contains Duplicate

## Problem Description

Given an integer array `nums`, return `true` if any value appears at least twice in the array, and return `false` if every element is distinct.

### Examples

**Example 1:**
```
Input: nums = [1,2,3,1]
Output: true
```

**Example 2:**
```
Input: nums = [1,2,3,4]
Output: false
```

**Example 3:**
```
Input: nums = [1,1,1,3,3,4,3,2,4,2]
Output: true
```

### Constraints

- `1 <= nums.length <= 10^5`
- `-10^9 <= nums[i] <= 10^9`

## Solution Approaches

### Approach 1: Hash Set (Recommended)

**Algorithm:**
1. Create an unordered_set to track seen numbers
2. Iterate through the array
3. For each number, check if it's already in the set
4. If found, return true (duplicate exists)
5. If not found, add to set and continue
6. If loop completes, return false (no duplicates)

**Time Complexity:** O(n)  
**Space Complexity:** O(n)

**Code:**
```cpp
bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> seen;
    
    for (int num : nums) {
        if (seen.find(num) != seen.end()) {
            return true;
        }
        seen.insert(num);
    }
    
    return false;
}
```

### Approach 2: Sorting

**Algorithm:**
1. Sort the array in ascending order
2. Compare adjacent elements
3. If any adjacent elements are equal, return true
4. Otherwise, return false

**Time Complexity:** O(n log n)  
**Space Complexity:** O(1) (if we can modify input array)

**Code:**
```cpp
bool containsDuplicateSorting(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] == nums[i-1]) {
            return true;
        }
    }
    
    return false;
}
```

### Approach 3: Brute Force

**Algorithm:**
1. Use nested loops to compare each element with every other element
2. If any two elements are equal, return true
3. Otherwise, return false

**Time Complexity:** O(n²)  
**Space Complexity:** O(1)

**Code:**
```cpp
bool containsDuplicateBruteForce(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
        for (int j = i + 1; j < nums.size(); j++) {
            if (nums[i] == nums[j]) {
                return true;
            }
        }
    }
    return false;
}
```

## Key C++ Concepts Used

### 1. **Containers**
- **`vector<int>`**: Dynamic array for storing integers
- **`unordered_set<int>`**: Hash set for O(1) lookup and insertion

### 2. **Iterators and Range-based For Loops**
- **Range-based for loop**: `for (int num : nums)` for clean iteration
- **Iterator operations**: `seen.find(num) != seen.end()` for membership check

### 3. **STL Algorithms**
- **`sort()`**: For sorting approach
- **`find()`**: For set membership checking

### 4. **References**
- **`vector<int>& nums`**: Reference parameter to avoid copying

## Performance Comparison

| Approach | Time Complexity | Space Complexity | Best For |
|----------|----------------|------------------|----------|
| Hash Set | O(n) | O(n) | General case |
| Sorting | O(n log n) | O(1) | Memory-constrained |
| Brute Force | O(n²) | O(1) | Educational only |

## Edge Cases

1. **Empty array**: Should return false
2. **Single element**: Should return false
3. **All duplicates**: Should return true
4. **Large numbers**: Handle overflow considerations
5. **Negative numbers**: Works the same as positive numbers

## Related Problems

- [219. Contains Duplicate II](https://leetcode.com/problems/contains-duplicate-ii/)
- [220. Contains Duplicate III](https://leetcode.com/problems/contains-duplicate-iii/)
- [26. Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/)
- [80. Remove Duplicates from Sorted Array II](https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/)

## Practice Tips

1. **Start with brute force** to understand the problem
2. **Think about trade-offs** between time and space complexity
3. **Consider edge cases** like empty arrays and single elements
4. **Practice with different data structures** (sets, maps, arrays)
5. **Understand when to use each approach** based on constraints

## NeetCode Roadmap Position

This problem is part of the **Arrays & Hashing** section in the NeetCode roadmap, focusing on:
- Basic array manipulation
- Hash set usage
- Time/space complexity analysis
- Multiple solution approaches
