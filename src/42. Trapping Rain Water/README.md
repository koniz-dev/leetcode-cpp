# [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)

## Problem Statement

Given `n` non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

**Example 1:**
```
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
```

**Example 2:**
```
Input: height = [4,2,0,3,2,5]
Output: 9
```

**Constraints:**
- `n == height.length`
- `1 <= n <= 2 * 10^4`
- `0 <= height[i] <= 10^5`

## Approaches

### 1. Two Pointers (Optimized) - O(n) Time, O(1) Space

**Algorithm:**
- Use two pointers starting from both ends of the array
- Track the maximum heights seen from left and right sides
- Move the pointer with smaller height towards the center
- Calculate trapped water based on the smaller of the two max heights

**Key Insight:** At any position, the water level is determined by the minimum of the maximum heights on both sides.

**Implementation:** See `optimized.cpp`

**Time Complexity:** O(n) - Single pass through the array
**Space Complexity:** O(1) - Only using constant extra space

### 2. Dynamic Programming - O(n) Time, O(n) Space

**Algorithm:**
- Precompute maximum heights from left and right for each position
- For each position, water trapped = min(maxLeft[i], maxRight[i]) - height[i]

```cpp
int trap(vector<int>& height) {
    int n = height.size();
    if (n == 0) return 0;
    
    vector<int> maxLeft(n), maxRight(n);
    
    // Compute max heights from left
    maxLeft[0] = height[0];
    for (int i = 1; i < n; i++) {
        maxLeft[i] = max(maxLeft[i-1], height[i]);
    }
    
    // Compute max heights from right
    maxRight[n-1] = height[n-1];
    for (int i = n-2; i >= 0; i--) {
        maxRight[i] = max(maxRight[i+1], height[i]);
    }
    
    // Calculate trapped water
    int trappedWater = 0;
    for (int i = 0; i < n; i++) {
        trappedWater += min(maxLeft[i], maxRight[i]) - height[i];
    }
    
    return trappedWater;
}
```

**Time Complexity:** O(n) - Three passes through the array
**Space Complexity:** O(n) - Two additional arrays of size n

### 3. Stack-based Approach - O(n) Time, O(n) Space

**Algorithm:**
- Use a stack to keep track of indices of bars
- When current bar is higher than the bar at stack top, pop and calculate water

```cpp
int trap(vector<int>& height) {
    stack<int> st;
    int trappedWater = 0;
    
    for (int i = 0; i < height.size(); i++) {
        while (!st.empty() && height[i] > height[st.top()]) {
            int top = st.top();
            st.pop();
            
            if (st.empty()) break;
            
            int distance = i - st.top() - 1;
            int boundedHeight = min(height[i], height[st.top()]) - height[top];
            trappedWater += distance * boundedHeight;
        }
        st.push(i);
    }
    
    return trappedWater;
}
```

**Time Complexity:** O(n) - Each element is pushed and popped once
**Space Complexity:** O(n) - Stack can contain up to n elements

## DSA Concepts Used

### 1. Two Pointers Technique
- **Concept:** Use two pointers moving towards each other to solve problems efficiently
- **When to use:** When you can eliminate possibilities by moving pointers based on some condition
- **Key insight:** At least one of the pointers will find the optimal solution

### 2. Dynamic Programming
- **Concept:** Break down complex problems into simpler subproblems
- **Pattern:** Precompute values that will be used multiple times
- **Trade-off:** Space for time optimization

### 3. Stack Data Structure
- **Concept:** LIFO (Last In, First Out) data structure
- **When to use:** When you need to process elements in reverse order or maintain a sequence
- **Pattern:** Monotonic stack for finding next/previous greater/smaller elements

## Complexity Analysis

| Approach | Time Complexity | Space Complexity | Notes |
|----------|----------------|------------------|-------|
| Two Pointers | O(n) | O(1) | Most efficient, single pass |
| Dynamic Programming | O(n) | O(n) | Three passes, uses extra space |
| Stack | O(n) | O(n) | Each element pushed/popped once |

## Key Insights

1. **Water Level Determination:** At any position, water level = min(maxLeft, maxRight)
2. **Two Pointers Optimization:** We only need to know the smaller of the two max heights
3. **Greedy Approach:** Moving the pointer with smaller height is always safe
4. **Edge Cases:** Empty array, single element, all elements same height

## Related Problems

- [11. Container With Most Water](https://leetcode.com/problems/container-with-most-water/) - Similar two pointers technique
- [84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/) - Stack-based approach
- [407. Trapping Rain Water II](https://leetcode.com/problems/trapping-rain-water-ii/) - 2D version using priority queue

## Learning Notes

- **Two Pointers:** Master this technique for array problems where you can eliminate possibilities
- **Space-Time Trade-off:** Sometimes using extra space can simplify the algorithm
- **Stack Applications:** Learn when to use stack for maintaining sequences and processing in reverse order
- **Problem Decomposition:** Break complex problems into simpler, solvable subproblems
