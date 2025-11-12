# [84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)

## Problem Statement

Given an array of integers `heights` representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.

## Examples

**Example 1:**
```
Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.
```

**Example 2:**
```
Input: heights = [2,4]
Output: 4
```

**Constraints:**
- `1 <= heights.length <= 10^5`
- `0 <= heights[i] <= 10^4`

## Solutions

### 1. Optimized Solution (Monotonic Stack) - `optimized.cpp`
**Time Complexity:** O(n)  
**Space Complexity:** O(n)

Uses a monotonic stack to track bars in increasing height order. For each bar, we calculate the largest rectangle that can be formed ending at that position. When we encounter a shorter bar, we know rectangles extending from taller bars can no longer continue, so we calculate their areas.

**Key C++ Concepts Used:**
- `stack<pair<int, int>>` - Stack storing (start_index, height) pairs
- Structured bindings `auto [index, height]` - Modern C++ feature for pair unpacking
- Monotonic stack pattern - Maintains elements in sorted order
- Greedy approach - Calculate maximum area as soon as we know a rectangle can't extend further

**Algorithm Steps:**
1. Iterate through each bar in the histogram
2. While current bar is shorter than stack top, pop and calculate area
3. Track the start index where each height can form a rectangle
4. After processing all bars, calculate areas for remaining bars that extend to the end

### 2. Alternative Solution (Brute Force)
**Time Complexity:** O(n²)  
**Space Complexity:** O(1)

For each bar, expand left and right to find the maximum width rectangle with that bar's height.

```cpp
int largestRectangleArea(vector<int>& heights) {
    int maxArea = 0;
    int n = heights.size();
    
    for (int i = 0; i < n; i++) {
        int left = i;
        int right = i;
        
        // Expand left while bars are >= current height
        while (left >= 0 && heights[left] >= heights[i]) {
            left--;
        }
        
        // Expand right while bars are >= current height
        while (right < n && heights[right] >= heights[i]) {
            right++;
        }
        
        // Calculate area: height * width
        int width = right - left - 1;
        maxArea = max(maxArea, heights[i] * width);
    }
    
    return maxArea;
}
```

### 3. Alternative Solution (Divide and Conquer)
**Time Complexity:** O(n log n) average, O(n²) worst case  
**Space Complexity:** O(log n) for recursion stack

Divide the histogram at the minimum height bar and recursively solve left and right subproblems.

```cpp
int largestRectangleArea(vector<int>& heights) {
    return divideAndConquer(heights, 0, heights.size() - 1);
}

int divideAndConquer(vector<int>& heights, int left, int right) {
    if (left > right) return 0;
    if (left == right) return heights[left];
    
    // Find minimum height index
    int minIdx = left;
    for (int i = left + 1; i <= right; i++) {
        if (heights[i] < heights[minIdx]) {
            minIdx = i;
        }
    }
    
    // Calculate area with minimum height bar
    int area = heights[minIdx] * (right - left + 1);
    
    // Recursively solve left and right subproblems
    int leftArea = divideAndConquer(heights, left, minIdx - 1);
    int rightArea = divideAndConquer(heights, minIdx + 1, right);
    
    return max({area, leftArea, rightArea});
}
```

## Key DSA Concepts

### Monotonic Stack
- **Definition**: A stack that maintains elements in monotonic (increasing or decreasing) order
- **Use Case**: Efficiently find next/previous smaller or larger elements
- **Pattern**: When an element violates monotonicity, pop elements until order is restored
- **Time Complexity**: O(n) - Each element pushed and popped at most once

### Greedy Algorithm
- **Principle**: Make locally optimal choices (calculate area when rectangle can't extend further)
- **Optimal Substructure**: Maximum area is the maximum of all possible rectangles
- **Greedy Choice**: Calculate area as soon as we know a rectangle's boundaries

### Rectangle Area Calculation
- **Formula**: `area = height × width`
- **Width Calculation**: Distance between left and right boundaries
- **Boundary Finding**: Use stack to efficiently find left and right boundaries

### Stack-Based Boundary Tracking
- **Left Boundary**: Tracked by storing start indices in the stack
- **Right Boundary**: Current position when we encounter a shorter bar
- **Extension Logic**: A rectangle can extend until it hits a shorter bar

## Common Pitfalls

1. **Forgetting to process remaining stack elements** - Bars that extend to the end need special handling
2. **Incorrect start index tracking** - Must update start index when popping taller bars
3. **Off-by-one errors in width calculation** - Width is `right - left`, not `right - left + 1` when using indices
4. **Not handling equal heights correctly** - Equal heights can extend rectangles, so use `>` not `>=` when popping
5. **Stack underflow** - Always check `!st.empty()` before accessing top element
6. **Integer overflow** - Area calculation can be large, ensure using appropriate data types

## Related Problems

- [85. Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/) - Extension to 2D matrices
- [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/) - Similar stack-based approach
- [739. Daily Temperatures](https://leetcode.com/problems/daily-temperatures/) - Next greater element using monotonic stack
- [503. Next Greater Element II](https://leetcode.com/problems/next-greater-element-ii/) - Circular array variant
- [907. Sum of Subarray Minimums](https://leetcode.com/problems/sum-of-subarray-minimums/) - Similar monotonic stack pattern
- [155. Min Stack](https://leetcode.com/problems/min-stack/) - Stack data structure fundamentals

## Learning Notes

### Why Monotonic Stack Works
- **Efficiency**: Each bar is processed at most twice (push and pop), giving O(n) time
- **Correctness**: When we pop a bar, we've found its right boundary
- **Space Optimization**: Only store necessary information (start index and height)

### Key Insight: When to Calculate Area
- **Trigger**: When we encounter a bar shorter than the stack top
- **Reason**: Taller bars can no longer extend their rectangles
- **Action**: Calculate area for all taller bars that can't extend further

### Start Index Tracking
- **Purpose**: Track where a rectangle of a given height can begin
- **Update**: When popping taller bars, update start to the leftmost popped index
- **Benefit**: Allows rectangles to extend backward to form larger areas

### Edge Cases
- **Single bar**: Returns the bar's height
- **All bars same height**: Returns `height × n`
- **Increasing heights**: All bars remain in stack, processed at the end
- **Decreasing heights**: Each bar immediately triggers area calculations

### Optimization Techniques
- **Early termination**: Not applicable (must process all bars)
- **Space optimization**: Could use array instead of stack, but stack is clearer
- **Modern C++**: Structured bindings make pair unpacking cleaner

### Pattern Recognition
This problem demonstrates the **monotonic stack pattern** which is useful for:
- Finding next/previous smaller/larger elements
- Calculating areas/volumes with boundaries
- Solving problems with "extend until condition" logic

