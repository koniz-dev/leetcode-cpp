# [33. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)

## Problem Statement

There is an integer array `nums` sorted in ascending order (with **distinct** values).

Prior to being passed to your function, `nums` is **possibly rotated** at an unknown pivot index `k` (`1 <= k < nums.length`) such that the resulting array is `[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]` (0-indexed). For example, `[0,1,2,4,5,6,7]` might be rotated at pivot index `3` and become `[4,5,6,7,0,1,2]`.

Given the array `nums` after the possible rotation and an integer `target`, return *the index of* `target` *if it is in* `nums`, *or* `-1` *if it is not in* `nums`.

You must write an algorithm with `O(log n)` runtime complexity.

**Example 1:**
```
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
```

**Example 2:**
```
Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
```

**Example 3:**
```
Input: nums = [1], target = 0
Output: -1
```

**Constraints:**
- `1 <= nums.length <= 5000`
- `-10^4 <= nums[i] <= 10^4`
- All values of `nums` are **unique**.
- `nums` is an ascending array that is possibly rotated.
- `-10^4 <= target <= 10^4`

## Approach Analysis

### Approach 1: Binary Search (Optimized Solution)
**Time Complexity:** O(log n)  
**Space Complexity:** O(1)

Since the array is rotated sorted, at any pivot point, at least one half of the array (left or right) remains sorted. We can leverage this property in a binary search.

1. **Identify Sorted Half**:
   - Calculate `mid`.
   - If `nums[left] <= nums[mid]`, the left half `[left...mid]` is sorted.
   - Otherwise, the right half `[mid...right]` is sorted.

2. **Check Range**:
   - If the left half is sorted, check if `target` lies within `[nums[left], nums[mid])`. If yes, search left; else, search right.
   - If the right half is sorted, check if `target` lies within `(nums[mid], nums[right]]`. If yes, search right; else, search left.

3. **Eliminate and Repeat**:
   - Adjust `left` or `right` pointers accordingly until `target` is found or range is invalid.

### Approach 2: Linear Search
**Time Complexity:** O(n)  
**Space Complexity:** O(1)

Iterate through the array and check each element. This does not meet the `O(log n)` requirement but is a valid fallback.

## Solution Implementations

### Binary Search Solution (optimized.cpp)
See `optimized.cpp` for the implementation using the logic described above. It handles edge cases and ensures O(log n) complexity.

### User Solution (main.cpp)
See `main.cpp` for the user's implementation, which follows the same binary search logic.

## Key Learning Points
- **Rotated Sorted Arrays**: Key insight is that one half is always sorted.
- **Binary Search Conditions**: Adapting standard binary search conditions to handle the rotation.
- **Edge Cases**: Handling cases where the array is not rotated (fully sorted) or contains only 1 element.

## Related Problems
- [153. Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)
- [81. Search in Rotated Sorted Array II](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/) (with duplicates)
- [981. Time Based Key-Value Store](https://leetcode.com/problems/time-based-key-value-store/)
