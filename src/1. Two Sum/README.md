# [1. Two Sum](https://leetcode.com/problems/two-sum/)

## Problem Statement
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

### 2. Brute Force Solution
**Time Complexity:** O(n²)  
**Space Complexity:** O(1)

Two nested loops to check all possible pairs.

```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    for (int i = 0; i < nums.size(); i++) {
        for (int j = i + 1; j < nums.size(); j++) {
            if (nums[i] + nums[j] == target) {
                return {i, j};
            }
        }
    }
    return {}; // No solution found
}
```

### 3. Two Pointers Solution (For sorted arrays)
**Time Complexity:** O(n log n) - due to sorting  
**Space Complexity:** O(n)

Only applicable when array can be sorted (loses original indices).

```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    // Create vector of pairs (value, original_index)
    vector<pair<int, int>> numsWithIndex;
    for (int i = 0; i < nums.size(); i++) {
        numsWithIndex.push_back({nums[i], i});
    }
    
    // Sort by value
    sort(numsWithIndex.begin(), numsWithIndex.end());
    
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        int sum = numsWithIndex[left].first + numsWithIndex[right].first;
        if (sum == target) {
            return {numsWithIndex[left].second, numsWithIndex[right].second};
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    
    return {}; // No solution found
}
```

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
- [15. 3Sum](https://leetcode.com/problems/3sum/)
- [18. 4Sum](https://leetcode.com/problems/4sum/)
- [167. Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/)
- [560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/)

## Practice Tips
1. Always consider hash map for lookup optimization
2. Use references for large containers to avoid copying
3. Consider edge cases (empty array, no solution)
4. Think about time/space complexity trade-offs
