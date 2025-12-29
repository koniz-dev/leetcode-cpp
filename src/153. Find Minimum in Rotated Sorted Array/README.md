# [153. Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)

## Problem Statement

Suppose an array of length `n` sorted in ascending order is rotated between `1` and `n` times. Given the rotated sorted array `nums` of **unique** elements, return the minimum element of this array.

You must write an algorithm that runs in `O(log n)` time.

**Example 1:**
```
Input: nums = [3,4,5,1,2]
Output: 1
Explanation: The original array was [1,2,3,4,5] rotated 3 times.
```

**Example 2:**
```
Input: nums = [4,5,6,7,0,1,2]
Output: 0
Explanation: The original array was [0,1,2,4,5,6,7] rotated 4 times.
```

**Example 3:**
```
Input: nums = [11,13,15,17]
Output: 11
Explanation: The array is already sorted (no rotation).
```

**Constraints:**
- `1 <= nums.length <= 5000`
- `-5000 <= nums[i] <= 5000`
- All the integers of `nums` are unique
- `nums` is sorted and rotated between `1` and `n` times

## Approach Analysis

### Approach 1: Binary Search by Comparing with Right (Optimized Solution)
**Time Complexity:** O(log n)  
**Space Complexity:** O(1)

Key observation: if `nums[mid] > nums[right]`, then the minimum is in the right half (because `mid` is in the “left” sorted block). Otherwise, the minimum is at `mid` or in the left half.

Steps:
1. If `nums[0] <= nums[n-1]`, the array is already sorted, return `nums[0]`.
2. Use `left` and `right` pointers.
3. While `left < right`, compute `mid`.
4. Narrow the search range using the comparison with `nums[right]`.

**Key DSA Concepts:**
- **Binary Search on Answer/Invariant**: Maintain that the minimum lies within `[left, right]`
- **Rotated Sorted Array**: Two sorted blocks, split at the rotation pivot

### Approach 2: Linear Scan
**Time Complexity:** O(n)  
**Space Complexity:** O(1)

Scan all elements and track the minimum. This is simple but does not meet the required `O(log n)` runtime.

```cpp
int findMin(vector<int>& nums) {
    int ans = nums[0];
    for (int x : nums) ans = min(ans, x);
    return ans;
}
```

## Solution Implementations

### Binary Search Solution (optimized.cpp)
See `optimized.cpp` for the iterative binary search solution with an early return when the array is already sorted.

### Binary Search Solution (main.cpp)
See `main.cpp` for the concise binary search implementation using the same right-comparison idea.

## Complexity Analysis

### Time Complexity: O(log n)
- Each iteration discards half of the remaining range by choosing the sorted side that cannot contain the minimum.

### Space Complexity: O(1)
- Uses a constant number of pointers and indices.

## Common Pitfalls

### 1. Wrong loop condition
- Using `while (left <= right)` with `right = mid` can cause infinite loops. The common safe pattern here is `while (left < right)`.

### 2. Confusing comparisons
- Comparing `nums[mid]` with `nums[left]` can work, but you need careful handling when the range crosses the pivot. Comparing with `nums[right]` is often simpler for this problem.

### 3. Not handling already sorted case
- If the array is not rotated, returning early with `nums[0]` is correct and avoids extra iterations.

## Related Problems
- [33. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)
- [154. Find Minimum in Rotated Sorted Array II](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/)
