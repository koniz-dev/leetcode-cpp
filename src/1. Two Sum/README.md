# Two Sum

## Problem Description
Given an array of integers `nums` and an integer `target`, return indices of the two numbers such that they add up to `target`.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

## Examples
```
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

Input: nums = [3,2,4], target = 6
Output: [1,2]

Input: nums = [3,3], target = 6
Output: [0,1]
```

## Solutions

### 1. Optimized Solution (Hash Map) - `optimized.cpp`
**Time Complexity:** O(n)  
**Space Complexity:** O(n)

Uses `unordered_map` to store each number and its index. For each number, check if the complement (target - current_number) exists in the map.

**Key C++ Concepts Used:**
- `vector<int>` - Dynamic array container
- `unordered_map<int, int>` - Hash map for O(1) lookups
- References (`vector<int>&`) - Pass by reference to avoid copying
- `find()` method - Check if key exists in map
- Return brace initialization `{index1, index2}`

### 2. Brute Force Solution (Not implemented)
**Time Complexity:** O(n²)  
**Space Complexity:** O(1)

Two nested loops to check all possible pairs.

### 3. Two Pointers Solution (For sorted arrays)
**Time Complexity:** O(n log n) - due to sorting  
**Space Complexity:** O(n)

Only applicable when array can be sorted (loses original indices).

## C++ Knowledge Points

### Containers
- **vector**: Dynamic array, used for input/output
- **unordered_map**: Hash map for efficient lookups

### C++ Features
- **References**: `vector<int>&` for efficient parameter passing
- **Brace initialization**: `{index1, index2}` for return values
- **STL methods**: `find()`, `size()`, `end()`

### Algorithms
- **Hash Map Technique**: Using map for O(1) complement lookup
- **Single Pass**: Process array only once

## Related Problems
- 3Sum
- 4Sum
- Two Sum II (sorted array)
- Subarray Sum Equals K

## Practice Tips
1. Always consider hash map for lookup optimization
2. Use references for large containers to avoid copying
3. Consider edge cases (empty array, no solution)
4. Think about time/space complexity trade-offs
