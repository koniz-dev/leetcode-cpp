# [167. Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/)

## Problem Statement

Given a **1-indexed** array of integers `numbers` that is already **sorted in non-decreasing order**, find two numbers such that they add up to a specific `target` number. Let these two numbers be `numbers[index1]` and `numbers[index2]` where `1 <= index1 < index2 <= numbers.length`.

Return the indices of the two numbers, `index1` and `index2`, added by one as an integer array `[index1, index2]` of length 2.

The tests are generated such that there is exactly one solution. You may not use the same element twice.

Your solution must use only constant extra space.

### Example 1:
```
Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We return [1, 2].
```

### Example 2:
```
Input: numbers = [2,3,4], target = 6
Output: [1,3]
Explanation: The sum of 2 and 4 is 6. Therefore index1 = 1, index3 = 3. We return [1, 3].
```

### Example 3:
```
Input: numbers = [-1,0], target = -1
Output: [1,2]
Explanation: The sum of -1 and 0 is -1. Therefore index1 = 1, index2 = 2. We return [1, 2].
```

### Constraints:
- `2 <= numbers.length <= 3 * 10^4`
- `-1000 <= numbers[i] <= 1000`
- `numbers` is sorted in non-decreasing order
- `-1000 <= target <= 1000`
- The tests are generated such that there is exactly one solution

## Solution Approaches

### Approach 1: Two Pointers (Optimal)
**Time Complexity:** O(n)  
**Space Complexity:** O(1)

This is the most efficient approach that takes advantage of the sorted array property.

#### Algorithm:
1. Initialize two pointers: `left` at the beginning (index 0) and `right` at the end (index n-1)
2. Calculate the sum of elements at both pointers
3. Compare the sum with the target:
   - If `sum == target`: Return the 1-indexed positions
   - If `sum < target`: Move `left` pointer right to increase the sum
   - If `sum > target`: Move `right` pointer left to decrease the sum
4. Continue until the pointers meet or solution is found

#### Why This Works:
- Since the array is sorted, we can use the two-pointer technique
- Moving the left pointer right increases the sum (larger numbers)
- Moving the right pointer left decreases the sum (smaller numbers)
- This guarantees we'll find the solution if it exists

#### Implementation:
See `optimized.cpp` for the complete implementation.

### Approach 2: Binary Search (Alternative)
**Time Complexity:** O(n log n)  
**Space Complexity:** O(1)

For each element, use binary search to find its complement.

#### Algorithm:
1. For each element at index `i`, calculate the complement: `target - numbers[i]`
2. Use binary search to find the complement in the remaining array
3. Return the 1-indexed positions if found

#### Why This Works:
- Binary search is efficient for finding elements in sorted arrays
- We search for the complement of each element

#### Implementation:
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        for (int i = 0; i < numbers.size(); i++) {
            int complement = target - numbers[i];
            int left = i + 1, right = numbers.size() - 1;
            
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (numbers[mid] == complement) {
                    return {i + 1, mid + 1};
                } else if (numbers[mid] < complement) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return {};
    }
};
```

### Approach 3: Hash Map (Not Optimal for This Problem)
**Time Complexity:** O(n)  
**Space Complexity:** O(n)

While this works, it doesn't take advantage of the sorted property and uses extra space.

#### Algorithm:
1. Use a hash map to store numbers and their indices
2. For each number, check if its complement exists in the map
3. Return the indices if found

## Key DSA Concepts

### 1. Two Pointers Technique
- **Definition:** Using two pointers that move towards each other or in the same direction
- **When to use:** Sorted arrays, palindromes, finding pairs
- **Benefits:** O(1) space complexity, often O(n) time complexity

### 2. Sorted Array Properties
- **Monotonic property:** Elements are in non-decreasing order
- **Binary search applicability:** Can use binary search for O(log n) lookups
- **Two pointer optimization:** Can eliminate certain search directions

### 3. Space-Time Tradeoffs
- **Two pointers:** O(n) time, O(1) space (optimal for this problem)
- **Binary search:** O(n log n) time, O(1) space
- **Hash map:** O(n) time, O(n) space

## Related Problems

- [1. Two Sum](https://leetcode.com/problems/two-sum/) - Unsorted array version
- [15. 3Sum](https://leetcode.com/problems/3sum/) - Three elements that sum to zero
- [16. 3Sum Closest](https://leetcode.com/problems/3sum-closest/) - Three elements with sum closest to target
- [18. 4Sum](https://leetcode.com/problems/4sum/) - Four elements that sum to target
- [259. 3Sum Smaller](https://leetcode.com/problems/3sum-smaller/) - Count triplets with sum less than target

## Learning Takeaways

1. **Leverage sorted array properties** - Use two pointers or binary search
2. **Two pointers technique** - Efficient for finding pairs in sorted arrays
3. **Space optimization** - Two pointers achieve O(1) space complexity
4. **Problem constraints matter** - The sorted property enables more efficient solutions
5. **Index manipulation** - Remember to convert 0-indexed to 1-indexed for return values

## Practice Recommendations

1. Implement all three approaches to understand the tradeoffs
2. Practice similar two-pointer problems
3. Understand when to use two pointers vs. binary search vs. hash maps
4. Focus on the space-time complexity analysis
5. Practice with edge cases (negative numbers, duplicates, etc.)
