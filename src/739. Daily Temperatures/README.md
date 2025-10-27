# [739. Daily Temperatures](https://leetcode.com/problems/daily-temperatures/)

## Problem Statement

Given an array of integers `temperatures` representing the daily temperatures, return an array `answer` such that `answer[i]` is the number of days you have to wait after the `ith` day to get a warmer temperature. If there is no future day for which this is possible, keep `answer[i] == 0` instead.

**Example 1:**
```
Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]
```

**Example 2:**
```
Input: temperatures = [30,40,50,60]
Output: [1,1,1,0]
```

**Example 3:**
```
Input: temperatures = [30,60,90]
Output: [1,1,0]
```

**Constraints:**
- `1 <= temperatures.length <= 10^5`
- `30 <= temperatures[i] <= 100`

## Approaches

### 1. Monotonic Stack (Optimized)

**Algorithm:**
- Use a stack to maintain indices of temperatures in decreasing order
- For each temperature, pop all temperatures from stack that are smaller
- Calculate the difference in indices to get days until warmer temperature
- Push current index onto stack for future comparisons

**Key Insight:** We only need to keep track of temperatures that haven't found their warmer day yet.

**Implementation:** See `optimized.cpp`

**Time Complexity:** O(n) - Each element is pushed and popped at most once
**Space Complexity:** O(n) - Stack can contain up to n elements in worst case

### 2. Brute Force

**Algorithm:**
- For each day, scan all future days to find the first warmer temperature
- Count the number of days until warmer temperature is found

```cpp
vector<int> dailyTemperatures(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (temperatures[j] > temperatures[i]) {
                result[i] = j - i;
                break;
            }
        }
    }
    
    return result;
}
```

**Time Complexity:** O(n²) - For each element, potentially scan all remaining elements
**Space Complexity:** O(1) - Only using the result array (not counting input)

### 3. Array-based Approach

**Algorithm:**
- Process temperatures from right to left
- Use the result array to store the next warmer day for each temperature
- For each temperature, check if next day is warmer, otherwise jump to its next warmer day

```cpp
vector<int> dailyTemperatures(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);
    
    for (int i = n - 2; i >= 0; i--) {
        int j = i + 1;
        while (j < n && temperatures[j] <= temperatures[i]) {
            if (result[j] == 0) {
                j = n;  // No warmer day found
                break;
            }
            j += result[j];  // Jump to next warmer day
        }
        if (j < n) {
            result[i] = j - i;
        }
    }
    
    return result;
}
```

**Time Complexity:** O(n) - Each element is visited at most twice
**Space Complexity:** O(1) - Only using the result array (not counting input)

## DSA Concepts Used

### 1. Monotonic Stack
- **Concept:** A stack that maintains elements in a specific order (increasing or decreasing)
- **When to use:** When you need to find the next/previous greater/smaller element
- **Key insight:** Elements that are popped will never be needed again for future comparisons
- **Pattern:** Process elements and maintain stack property by removing elements that violate the order

### 2. Stack Data Structure
- **Concept:** LIFO (Last In, First Out) data structure
- **When to use:** When you need to process elements in reverse order or maintain a sequence
- **Applications:** Expression evaluation, function calls, backtracking, and monotonic problems

### 3. Array Processing
- **Concept:** Efficiently processing arrays by maintaining additional information
- **Pattern:** Using the result array itself to store intermediate results
- **Optimization:** Jumping to known positions instead of scanning linearly

## Complexity Analysis

| Approach | Time Complexity | Space Complexity | Notes |
|----------|----------------|------------------|-------|
| Monotonic Stack | O(n) | O(n) | Most intuitive, each element pushed/popped once |
| Brute Force | O(n²) | O(1) | Simple but inefficient for large inputs |
| Array-based | O(n) | O(1) | Space-optimized, uses result array for jumps |

## Key Insights

1. **Monotonic Stack Pattern:** When finding next greater element, maintain decreasing order
2. **Element Elimination:** Once an element finds its next greater element, it's no longer needed
3. **Index Tracking:** Store indices in stack to calculate distances between elements
4. **Edge Cases:** Handle cases where no warmer day exists (result remains 0)

## Related Problems

- [496. Next Greater Element I](https://leetcode.com/problems/next-greater-element-i/) - Similar monotonic stack pattern
- [503. Next Greater Element II](https://leetcode.com/problems/next-greater-element-ii/) - Circular array version
- [84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/) - Monotonic stack for area calculation
- [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/) - Stack-based water trapping

## Learning Notes

- **Monotonic Stack:** Master this pattern for "next greater/smaller element" problems
- **Stack Applications:** Learn when to use stack for maintaining sequences and processing in reverse order
- **Index Management:** Practice tracking indices in stack-based solutions
- **Problem Patterns:** Recognize when a problem can be solved with monotonic data structures
- **Space-Time Trade-offs:** Understand when to use extra space for better time complexity
