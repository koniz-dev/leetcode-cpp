# [11. Container With Most Water](https://leetcode.com/problems/container-with-most-water/)

## Problem Statement

You are given an integer array `height` of length `n`. There are `n` vertical lines drawn such that the two endpoints of the `ith` line are `(i, 0)` and `(i, height[i])`.

Find two lines that together with the x-axis form a container, such that the container contains the most water.

Return the maximum amount of water a container can store.

**Notice** that you may not slant the container.

### Examples

**Example 1:**
```
Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
```

**Example 2:**
```
Input: height = [1,1]
Output: 1
```

### Constraints

- `n == height.length`
- `2 <= n <= 10^5`
- `0 <= height[i] <= 10^4`

## Solution Approaches

### Approach 1: Two Pointers (Optimal)

**Algorithm:**
1. Initialize two pointers at the start and end of the array
2. Calculate the area using the shorter height and current width
3. Move the pointer with the shorter height inward
4. Keep track of the maximum area found
5. Continue until pointers meet

**Key Insight:** Moving the pointer with the taller height inward can only decrease the area, so we always move the shorter pointer.

**Time Complexity:** O(n) - Single pass through the array
**Space Complexity:** O(1) - Constant extra space

**Implementation:** See `optimized.cpp`

### Approach 2: Brute Force (Not Implemented)

**Algorithm:**
1. Check all possible pairs of lines
2. Calculate area for each pair
3. Return the maximum area found

**Time Complexity:** O(n²) - Check all pairs
**Space Complexity:** O(1) - Constant extra space

```cpp
int maxArea(vector<int>& height) {
    int maxArea = 0;
    for (int i = 0; i < height.size(); i++) {
        for (int j = i + 1; j < height.size(); j++) {
            int width = j - i;
            int minHeight = min(height[i], height[j]);
            int area = width * minHeight;
            maxArea = max(maxArea, area);
        }
    }
    return maxArea;
}
```

## Data Structures and Algorithms Used

### Two Pointers Technique
- **Concept:** Use two pointers moving from opposite ends toward each other
- **When to use:** Array problems where we need to find optimal pairs
- **Key insight:** Greedy approach - always move the pointer that can potentially improve the result

### Greedy Algorithm
- **Concept:** Make locally optimal choice at each step
- **Application:** Moving the shorter pointer is always the optimal choice
- **Why it works:** Moving the taller pointer can only decrease the area

## Complexity Analysis

### Time Complexity: O(n)
- Single pass through the array
- Each element is visited at most once
- Two pointers approach ensures linear time

### Space Complexity: O(1)
- Only using constant extra variables
- No additional data structures required
- Space usage doesn't grow with input size

## Key Learning Points

1. **Two Pointers Technique:** Essential for array problems involving pairs
2. **Greedy Strategy:** Sometimes the locally optimal choice leads to global optimum
3. **Mathematical Insight:** Understanding why moving the shorter pointer is always better
4. **Problem Transformation:** Converting geometric problem to array manipulation

## Related Problems

- [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/) - Similar two pointers approach
- [15. 3Sum](https://leetcode.com/problems/3sum/) - Two pointers with sorting
- [167. Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) - Two pointers on sorted array

## Implementation Notes

- The solution in `main.cpp` implements the optimal two pointers approach
- The `optimized.cpp` provides the same algorithm with comprehensive comments
- Both implementations achieve O(n) time and O(1) space complexity
- The key insight is that we never need to move the taller pointer inward
