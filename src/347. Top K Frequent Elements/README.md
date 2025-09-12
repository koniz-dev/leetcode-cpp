# 347. Top K Frequent Elements

## Problem Statement
Given an integer array `nums` and an integer `k`, return the `k` most frequent elements. You may return the answer in any order.

**Example 1:**
```
Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
```

**Example 2:**
```
Input: nums = [1], k = 1
Output: [1]
```

## DSA Concepts Used
- **Hash Map (unordered_map)**: For frequency counting
- **Heap (Priority Queue)**: For maintaining top K elements efficiently
- **Sorting**: Alternative approach for comparison
- **Bucket Sort**: Most optimal approach for this problem

## Solution Approaches

### Approach 1: Sorting (Your Solution)
**Time Complexity:** O(n log n)  
**Space Complexity:** O(n)

```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    
    // Count frequencies
    for (const int &num : nums) {
        freq[num]++; 
    }
    
    // Convert to vector and sort by frequency
    vector<pair<int,int>> arr(freq.begin(), freq.end());
    sort(arr.begin(), arr.end(), [](const pair<int,int> &a, const pair<int,int> &b) {
        return a.second > b.second;
    });
    
    // Extract top k elements
    vector<int> res;
    res.reserve(k);
    for (int i = 0; i < k && i < (int)arr.size(); i++) {
        res.push_back(arr[i].first);
    }
    
    return res;
}
```

**Analysis:**
- ✅ Simple and intuitive approach
- ✅ Easy to understand and implement
- ❌ Not optimal for large datasets
- ❌ O(n log n) time complexity due to sorting

### Approach 2: Max-Heap (Intuitive Solution)
**Time Complexity:** O(n log n)  
**Space Complexity:** O(n)

```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
    // Count frequencies
    unordered_map<int, int> freq;
    for (const int& num : nums) {
        freq[num]++;
    }
    
    // Max-heap: highest frequency at root
    auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;  // Max-heap
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> maxHeap(cmp);
    
    // Add all elements to max-heap
    for (const auto& [num, count] : freq) {
        maxHeap.push({num, count});
    }
    
    // Extract top k elements
    vector<int> result;
    result.reserve(k);
    for (int i = 0; i < k && !maxHeap.empty(); i++) {
        result.push_back(maxHeap.top().first);
        maxHeap.pop();
    }
    
    return result;
}
```

**Analysis:**
- ✅ Very intuitive and easy to understand
- ✅ Straightforward implementation
- ✅ Natural approach: build heap → pop k times
- ❌ O(n log n) time complexity (same as sorting)
- ❌ Less efficient than min-heap when k << n

### Approach 3: Min-Heap (Space-Optimized Solution)
**Time Complexity:** O(n log k)  
**Space Complexity:** O(n + k)

```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
    // Count frequencies
    unordered_map<int, int> freq;
    for (const int& num : nums) {
        freq[num]++;
    }
    
    // Min-heap to maintain top K elements
    auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;  // Min-heap
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> minHeap(cmp);
    
    // Process each unique element
    for (const auto& [num, count] : freq) {
        minHeap.push({num, count});
        if (minHeap.size() > k) {
            minHeap.pop();  // Remove smallest frequency
        }
    }
    
    // Extract results
    vector<int> result;
    result.reserve(k);
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().first);
        minHeap.pop();
    }
    reverse(result.begin(), result.end());
    
    return result;
}
```

**Analysis:**
- ✅ Better time complexity O(n log k) vs O(n log n)
- ✅ Efficient for large datasets when k << n
- ✅ Uses heap data structure effectively
- ✅ Modern C++ features (structured bindings, auto)

### Approach 4: Bucket Sort (Most Optimal)
**Time Complexity:** O(n)  
**Space Complexity:** O(n)

```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
    // Count frequencies
    unordered_map<int, int> freq;
    for (const int& num : nums) {
        freq[num]++;
    }
    
    // Create buckets: index = frequency, value = list of numbers
    vector<vector<int>> buckets(nums.size() + 1);
    for (const auto& [num, count] : freq) {
        buckets[count].push_back(num);
    }
    
    // Extract top k elements from buckets
    vector<int> result;
    result.reserve(k);
    for (int i = buckets.size() - 1; i >= 0 && result.size() < k; i--) {
        for (const int& num : buckets[i]) {
            if (result.size() < k) {
                result.push_back(num);
            }
        }
    }
    
    return result;
}
```

**Analysis:**
- ✅ Optimal O(n) time complexity
- ✅ Linear time solution
- ✅ Best for very large datasets
- ✅ Uses bucket sort concept effectively

## Key Learning Points

### 1. Heap Data Structure
- **Max-heap**: Root has maximum value, intuitive for "top K" problems
- **Min-heap**: Root has minimum value, space-efficient for maintaining top K elements
- **Heap operations**: Insert O(log n), Extract O(log n), Peek O(1)
- **Key insight**: Max-heap is more intuitive, min-heap is more space-efficient

### 2. Frequency Counting Pattern
- Use `unordered_map` for O(1) average case insertion and lookup
- Common pattern in many array problems
- Essential for problems involving counting occurrences

### 3. Top K Elements Pattern
- **Max-heap approach**: O(n log n) - intuitive, build heap → pop k times
- **Min-heap approach**: O(n log k) - space-efficient, maintain size k
- **Sorting approach**: O(n log n) - simple but not optimal
- **Bucket sort**: O(n) - optimal when frequency range is limited

### 4. Modern C++ Features Used
- **Structured bindings**: `for (const auto& [num, count] : freq)`
- **Auto keyword**: `auto cmp = [...]`
- **Lambda expressions**: Custom comparators
- **Reserve**: `result.reserve(k)` for performance optimization

## Complexity Comparison

| Approach | Time | Space | Best Use Case |
|----------|------|-------|---------------|
| Sorting | O(n log n) | O(n) | Small datasets, simple implementation |
| Max-Heap | O(n log n) | O(n) | Intuitive approach, easy to understand |
| Min-Heap | O(n log k) | O(n + k) | Large datasets, k << n, space-efficient |
| Bucket Sort | O(n) | O(n) | Very large datasets, limited frequency range |

## Related Problems
- [215. Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/)
- [451. Sort Characters By Frequency](https://leetcode.com/problems/sort-characters-by-frequency/)
- [692. Top K Frequent Words](https://leetcode.com/problems/top-k-frequent-words/)
- [973. K Closest Points to Origin](https://leetcode.com/problems/k-closest-points-to-origin/)

## Practice Recommendations
1. Implement all three approaches to understand trade-offs
2. Practice heap operations and custom comparators
3. Understand when to use each approach based on constraints
4. Master frequency counting patterns for array problems
