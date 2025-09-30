# [238. Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/)

## Problem Statement
Given an integer array `nums`, return an array `answer` such that `answer[i]` is equal to the product of all the elements of `nums` except `nums[i]`.

The product of any prefix or suffix of `nums` is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in `O(n)` time and without using the division operator.

## Examples

### Example 1:
```
Input: nums = [1,2,3,4]
Output: [24,12,8,6]
Explanation: 
- answer[0] = 2*3*4 = 24
- answer[1] = 1*3*4 = 12
- answer[2] = 1*2*4 = 8
- answer[3] = 1*2*3 = 6
```

### Example 2:
```
Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
```

## DSA Concepts Used

### 1. Array Manipulation
- **Concept**: Efficiently computing products using array traversal
- **Key Insight**: Breaking down the problem into left and right products
- **Learning**: How to optimize space by reusing existing arrays

### 2. Prefix/Suffix Products
- **Concept**: Computing cumulative products from left and right
- **Pattern**: Common technique for array problems involving products/sums
- **Application**: Used in many array-based problems for efficient computation

### 3. Space Optimization
- **Concept**: Reducing auxiliary space from O(n) to O(1)
- **Technique**: Using the result array itself for intermediate calculations
- **Trade-off**: Slightly more complex logic for significant space savings

## Solution Approaches

### Approach 1: Prefix and Suffix Arrays (Original)
```cpp
vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> prefix(n), suffix(n), answer(n);
    
    // Calculate prefix products
    prefix[0] = 1;
    for (int i = 1; i < n; i++) {
        prefix[i] = prefix[i - 1] * nums[i - 1];
    }
    
    // Calculate suffix products
    suffix[n - 1] = 1;
    for (int i = n - 2; i >= 0; i--) {
        suffix[i] = suffix[i + 1] * nums[i + 1];
    }
    
    // Calculate final answer
    for (int i = 0; i < n; i++) {
        answer[i] = prefix[i] * suffix[i];
    }
    
    return answer;
}
```

**Time Complexity**: O(n) - Three passes through the array
**Space Complexity**: O(n) - Two additional arrays (prefix and suffix)

### Approach 2: Optimized Space (Recommended)
```cpp
vector<int> productExceptSelf(vector<int>& nums) {
    const int n = nums.size();
    vector<int> result(n);
    
    // First pass: Calculate left products
    result[0] = 1;
    for (int i = 1; i < n; ++i) {
        result[i] = result[i - 1] * nums[i - 1];
    }
    
    // Second pass: Calculate right products and multiply
    int rightProduct = 1;
    for (int i = n - 1; i >= 0; --i) {
        result[i] *= rightProduct;
        rightProduct *= nums[i];
    }
    
    return result;
}
```

**Time Complexity**: O(n) - Two passes through the array
**Space Complexity**: O(1) - Only using the result array (excluding input/output)

## Algorithm Analysis

### Why This Approach Works
1. **Left Products**: First pass calculates the product of all elements to the left of each position
2. **Right Products**: Second pass calculates right products on-the-fly and multiplies with stored left products
3. **Space Optimization**: By reusing the result array and using a single variable for right products

### Key Insights
- **No Division**: Avoids division operator as required by the problem
- **Handles Zeros**: Naturally handles arrays with zeros
- **No Overflow**: Works within 32-bit integer constraints
- **Optimal Complexity**: Achieves the best possible time and space complexity

## Edge Cases

### 1. Single Element
```
Input: [5]
Output: [1]
```

### 2. Two Elements
```
Input: [2, 3]
Output: [3, 2]
```

### 3. Array with Zeros
```
Input: [1, 0, 3, 4]
Output: [0, 12, 0, 0]
```

### 4. All Same Elements
```
Input: [2, 2, 2, 2]
Output: [8, 8, 8, 8]
```

## Learning Takeaways

### 1. Array Traversal Patterns
- **Forward Pass**: Calculate cumulative values from left to right
- **Backward Pass**: Calculate cumulative values from right to left
- **Combined Approach**: Use both passes for complete solution

### 2. Space Optimization Techniques
- **Reuse Arrays**: Use result array for intermediate calculations
- **Single Variables**: Use variables instead of arrays when possible
- **In-place Operations**: Modify existing data structures when safe

### 3. Problem Decomposition
- **Break Down**: Split complex operations into simpler steps
- **Independent Calculations**: Calculate left and right products separately
- **Combine Results**: Merge independent calculations for final answer

### 4. Modern C++ Features
- **const int**: Use const for values that don't change
- **++i vs i++**: Prefer pre-increment for better performance
- **Clear Variable Names**: Use descriptive names for better readability

## Related Problems
- [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)
- [135. Candy](https://leetcode.com/problems/candy/)
- [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)
- [11. Container With Most Water](https://leetcode.com/problems/container-with-most-water/)

## Practice Recommendations
1. **Implement Both Approaches**: Understand the trade-offs between clarity and optimization
2. **Trace Through Examples**: Manually trace through the algorithm with different inputs
3. **Handle Edge Cases**: Test with arrays containing zeros, negative numbers, and single elements
4. **Space Analysis**: Practice analyzing space complexity and optimization opportunities
5. **Pattern Recognition**: Look for similar prefix/suffix patterns in other array problems
