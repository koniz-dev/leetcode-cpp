# Basic Algorithms in C++

## Overview
The C++ Standard Template Library (STL) provides many optimized algorithms in the `<algorithm>` library.

## Sorting Algorithms

### std::sort
Quick sort algorithm with O(n log n) complexity.

```cpp
#include <algorithm>
#include <vector>

std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6};

// Sort in ascending order
std::sort(nums.begin(), nums.end());

// Sort in descending order
std::sort(nums.begin(), nums.end(), std::greater<int>());

// Sort with custom comparator
std::sort(nums.begin(), nums.end(), [](int a, int b) {
    return a < b;
});
```

### std::stable_sort
Stable sort that preserves the relative order of equal elements.

```cpp
#include <algorithm>
#include <vector>
#include <string>

std::vector<std::pair<int, std::string>> data = {
    {3, "Alice"},
    {1, "Bob"},
    {3, "Charlie"},
    {1, "David"}
};

// Sort by number, preserve name order
std::stable_sort(data.begin(), data.end());
```

### std::partial_sort
Sort a portion of the container.

```cpp
#include <algorithm>
#include <vector>

std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6};

// Sort the 3 smallest elements
std::partial_sort(nums.begin(), nums.begin() + 3, nums.end());
```

## Searching Algorithms

### std::find
Linear search with O(n) complexity.

```cpp
#include <algorithm>
#include <vector>

std::vector<int> nums = {1, 2, 3, 4, 5};

// Search for value
auto it = std::find(nums.begin(), nums.end(), 3);
if (it != nums.end()) {
    std::cout << "Found at index: " << (it - nums.begin()) << std::endl;
}
```

### std::binary_search
Binary search with O(log n) complexity on sorted arrays.

```cpp
#include <algorithm>
#include <vector>

std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Binary search
bool found = std::binary_search(nums.begin(), nums.end(), 5);
if (found) {
    std::cout << "Found!" << std::endl;
}
```

### std::lower_bound and std::upper_bound
Find insertion position in sorted arrays.

```cpp
#include <algorithm>
#include <vector>

std::vector<int> nums = {1, 2, 2, 2, 3, 4, 5};

// Find first position where 2 could be inserted
auto lower = std::lower_bound(nums.begin(), nums.end(), 2);

// Find last position where 2 could be inserted
auto upper = std::upper_bound(nums.begin(), nums.end(), 2);

// Count occurrences of 2
int count = upper - lower;  // 3
```

## Two Pointers Technique

### Introduction
Two pointers technique uses two pointers to solve problems efficiently, often reducing time complexity from O(n²) to O(n).

### Basic Pattern
```cpp
int left = 0, right = array.size() - 1;

while (left < right) {
    // Process elements at left and right pointers
    if (condition) {
        left++;
    } else {
        right--;
    }
}
```

### Example: Two Sum on Sorted Array
```cpp
#include <vector>

std::vector<int> twoSumSorted(std::vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    while (left < right) {
        int sum = nums[left] + nums[right];
        
        if (sum == target) {
            return {left, right};
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    
    return {};
}
```

### Example: Remove Duplicates from Sorted Array
```cpp
#include <vector>

int removeDuplicates(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int writeIndex = 1;
    
    for (int readIndex = 1; readIndex < nums.size(); readIndex++) {
        if (nums[readIndex] != nums[readIndex - 1]) {
            nums[writeIndex] = nums[readIndex];
            writeIndex++;
        }
    }
    
    return writeIndex;
}
```

## Sliding Window Technique

### Introduction
Sliding window technique uses a window that slides through the array to solve problems efficiently.

### Fixed Size Window
```cpp
#include <vector>

int maxSumFixedWindow(const std::vector<int>& nums, int k) {
    if (nums.size() < k) return 0;
    
    // Calculate sum of first window
    int windowSum = 0;
    for (int i = 0; i < k; i++) {
        windowSum += nums[i];
    }
    
    int maxSum = windowSum;
    
    // Slide window
    for (int i = k; i < nums.size(); i++) {
        windowSum = windowSum - nums[i - k] + nums[i];
        maxSum = std::max(maxSum, windowSum);
    }
    
    return maxSum;
}
```

### Variable Size Window
```cpp
#include <vector>

int minSubArrayLen(const std::vector<int>& nums, int target) {
    int left = 0, sum = 0, minLen = INT_MAX;
    
    for (int right = 0; right < nums.size(); right++) {
        sum += nums[right];
        
        while (sum >= target) {
            minLen = std::min(minLen, right - left + 1);
            sum -= nums[left];
            left++;
        }
    }
    
    return minLen == INT_MAX ? 0 : minLen;
}
```

## Hash Map Techniques

### Introduction
Using hash maps to optimize search and counting problems.

### Example: Two Sum (Hash Map)

```cpp
#include <vector>
#include <unordered_map>

std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    std::unordered_map<int, int> seen;
    
    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        
        if (seen.find(complement) != seen.end()) {
            return {seen[complement], i};
        }
        
        seen[nums[i]] = i;
    }
    
    return {};
}
```

### Example: Group Anagrams

```cpp
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

std::vector<std::vector<std::string>> groupAnagrams(
    const std::vector<std::string>& strs) {
    
    std::unordered_map<std::string, std::vector<std::string>> groups;
    
    for (const std::string& str : strs) {
        std::string sorted = str;
        std::sort(sorted.begin(), sorted.end());
        groups[sorted].push_back(str);
    }
    
    std::vector<std::vector<std::string>> result;
    for (const auto& pair : groups) {
        result.push_back(pair.second);
    }
    
    return result;
}
```

## Dynamic Programming Patterns

### Fibonacci Sequence

```cpp
#include <vector>

int fibonacci(int n) {
    if (n <= 1) return n;
    
    std::vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    return dp[n];
}
```

### Longest Increasing Subsequence

```cpp
#include <vector>
#include <algorithm>

int lengthOfLIS(const std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    std::vector<int> dp(nums.size(), 1);
    
    for (int i = 1; i < nums.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[i] > nums[j]) {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
        }
    }
    
    return *std::max_element(dp.begin(), dp.end());
}
```

### Climbing Stairs

```cpp
#include <vector>

int climbStairs(int n) {
    if (n <= 2) return n;
    
    std::vector<int> dp(n + 1);
    dp[1] = 1;
    dp[2] = 2;
    
    for (int i = 3; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    return dp[n];
}
```

## Graph Algorithms

### Depth-First Search (DFS)

```cpp
#include <vector>
#include <unordered_set>

void dfs(const std::vector<std::vector<int>>& graph, 
         int node, std::unordered_set<int>& visited) {
    visited.insert(node);
    
    for (int neighbor : graph[node]) {
        if (visited.find(neighbor) == visited.end()) {
            dfs(graph, neighbor, visited);
        }
    }
}
```

### Breadth-First Search (BFS)

```cpp
#include <vector>
#include <queue>
#include <unordered_set>

void bfs(const std::vector<std::vector<int>>& graph, int start) {
    std::queue<int> q;
    std::unordered_set<int> visited;
    
    q.push(start);
    visited.insert(start);
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        // Process node
        
        for (int neighbor : graph[node]) {
            if (visited.find(neighbor) == visited.end()) {
                q.push(neighbor);
                visited.insert(neighbor);
            }
        }
    }
}
```

## String Algorithms

### String Matching

```cpp
#include <string>

bool isSubstring(const std::string& s, const std::string& t) {
    return s.find(t) != std::string::npos;
}
```

### Palindrome Check

```cpp
#include <string>

bool isPalindrome(const std::string& s) {
    int left = 0, right = s.length() - 1;
    
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    
    return true;
}
```

## Performance Considerations

### Time Complexity Summary

| Algorithm | Best Case | Average Case | Worst Case |
|-----------|-----------|--------------|------------|
| std::sort | O(n log n) | O(n log n) | O(n log n) |
| std::find | O(1) | O(n) | O(n) |
| std::binary_search | O(1) | O(log n) | O(log n) |
| Two Pointers | O(n) | O(n) | O(n) |
| Sliding Window | O(n) | O(n) | O(n) |
| Hash Map Search | O(1) | O(1) | O(n) |

### Space Complexity Summary

| Algorithm | Space Complexity |
|-----------|------------------|
| std::sort | O(log n) |
| std::find | O(1) |
| std::binary_search | O(1) |
| Two Pointers | O(1) |
| Sliding Window | O(1) |
| Hash Map | O(n) |

### Best Practices

1. **Choose the right algorithm**: Consider time and space complexity
2. **Use STL algorithms**: Leverage optimized implementations
3. **Avoid premature optimization**: Profile before optimizing
4. **Consider edge cases**: Handle empty containers and boundary conditions
5. **Use appropriate data structures**: Choose containers based on access patterns
