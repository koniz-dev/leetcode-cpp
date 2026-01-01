# 🪟 Sliding Window Technique

## 📚 Overview
The **Sliding Window** technique uses a window that can expand or contract to efficiently solve substring and subarray problems.

## 🎯 **When to Use**
- **Substring problems** - Find longest/shortest substring satisfying conditions
- **Subarray problems** - Find subarray with sum/product equal to target
- **Fixed size problems** - Find subarray with fixed size
- **Variable size problems** - Find subarray with variable size

## 📊 **Visual Guide**

### **Variable Window Logic**
Used for finding the smallest/largest window satisfying a condition.

```mermaid
graph TD
    A[Start: left=0, right=0] --> B{right < size?}
    B -- No --> C[End]
    B -- Yes --> D[Add nums[right] to Window]
    D --> E{Condition Violated?}
    E -- Yes --> F[Remove nums[left]]
    F --> G[left++]
    G --> E
    E -- No --> H[Update Result]
    H --> I[right++]
    I --> B
```

## ⚖️ **Window Types Comparison**

| Window Type | Constraint | Logic | Example |
|---|---|---|---|
| **Fixed Size** | `window.size == k` | `add(right), remove(right-k)` | Max Sum Subarray of size K |
| **Variable (Min)** | `sum >= target` | `expand until valid, then shrink` | Min Subarray Len |
| **Variable (Max)** | `distinct <= k` | `expand, if invalid shrink` | Longest Substring |

## 🚀 **Common Patterns**

### 1. **Fixed Size Window**
```cpp
// Find subarray of size k with maximum sum
int maxSumFixedWindow(vector<int>& nums, int k) {
    if (nums.size() < k) return 0;
    
    // Calculate sum of first window
    int windowSum = 0;
    for (int i = 0; i < k; i++) {
        windowSum += nums[i];
    }
    
    int maxSum = windowSum;
    
    // Slide the window
    for (int i = k; i < nums.size(); i++) {
        windowSum = windowSum - nums[i - k] + nums[i];
        maxSum = max(maxSum, windowSum);
    }
    
    return maxSum;
}
```

**Time Complexity**: O(n)  
**Space Complexity**: O(1)

### 2. **Variable Size Window**
```cpp
// Find shortest subarray with sum >= target
int minSubArrayLen(int target, vector<int>& nums) {
    int left = 0, right = 0;
    int windowSum = 0;
    int minLen = INT_MAX;
    
    while (right < nums.size()) {
        windowSum += nums[right];
        
        // Contract window when condition is met
        while (windowSum >= target) {
            minLen = min(minLen, right - left + 1);
            windowSum -= nums[left];
            left++;
        }
        
        right++;
    }
    
    return minLen == INT_MAX ? 0 : minLen;
}
```

**Time Complexity**: O(n)  
**Space Complexity**: O(1)

### 3. **Longest Substring Without Repeating Characters**
```cpp
// Find longest substring without repeating characters
int lengthOfLongestSubstring(string s) {
    vector<int> charIndex(128, -1);
    int left = 0, maxLen = 0;
    
    for (int right = 0; right < s.length(); right++) {
        char currentChar = s[right];
        
        // If character already appeared, update left
        if (charIndex[currentChar] >= left) {
            left = charIndex[currentChar] + 1;
        }
        
        charIndex[currentChar] = right;
        maxLen = max(maxLen, right - left + 1);
    }
    
    return maxLen;
}
```

**Time Complexity**: O(n)  
**Space Complexity**: O(1) - Fixed size array

## 🔍 **Problem Examples**

### **Easy Level**
- [643. Maximum Average Subarray I](https://leetcode.com/problems/maximum-average-subarray-i/)
- [1052. Grumpy Bookstore Owner](https://leetcode.com/problems/grumpy-bookstore-owner/)

### **Medium Level**
- [209. Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/)
- [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)
- [424. Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/)

### **Hard Level**
- [76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)
- [239. Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)
- [992. Subarrays with K Different Integers](https://leetcode.com/problems/subarrays-with-k-different-integers/)

## 💡 **Key Insights**

### **1. Window Expansion vs Contraction**
```cpp
// Expand window when need to add elements
while (right < nums.size() && !condition_met) {
    windowSum += nums[right];
    right++;
}

// Contract window when condition is met
while (left < right && condition_met) {
    windowSum -= nums[left];
    left++;
}
```

### **2. Hash Map for Character Count**
```cpp
// Use hash map to count characters in window
unordered_map<char, int> charCount;
int uniqueChars = 0;

// Add new character
if (++charCount[s[right]] == 1) uniqueChars++;

// Remove old character
if (--charCount[s[left]] == 0) uniqueChars--;
```

### **3. Monotonic Queue for Max/Min**
```cpp
// Use deque to find max/min in window
deque<int> dq;  // Monotonic decreasing

// Add new element
while (!dq.empty() && nums[dq.back()] < nums[right]) {
    dq.pop_back();
}
dq.push_back(right);

// Remove old element
if (dq.front() <= right - k) {
    dq.pop_front();
}
```

## 🎯 **C++23 Modern Implementation**

### **Using std::ranges and std::views**
```cpp
// Modern C++23 approach with ranges and views
auto slidingWindow = [&](int k) -> std::vector<int> {
    std::vector<int> result;
    
    // Create view for first window
    auto firstWindow = nums | std::views::take(k);
    int windowSum = std::ranges::fold_left(firstWindow, 0, std::plus{});
    result.push_back(windowSum);
    
    // Slide the window
    for (int i = k; i < std::ranges::ssize(nums); ++i) {
        windowSum = windowSum - nums[i - k] + nums[i];
        result.push_back(windowSum);
    }
    
    return result;
};
```

### **Using std::accumulate with std::views**
```cpp
// Calculate sum of windows with std::views
auto windowSums = std::views::iota(0, static_cast<int>(nums.size()) - k + 1)
    | std::views::transform([&](int start) {
        auto window = nums | std::views::drop(start) | std::views::take(k);
        return std::ranges::fold_left(window, 0, std::plus{});
    });
```

## 📊 **Complexity Analysis**

| Pattern | Time | Space | Best For |
|---------|------|-------|----------|
| Fixed Size | O(n) | O(1) | Subarray with fixed size |
| Variable Size | O(n) | O(1) | Subarray with specific conditions |
| Character Count | O(n) | O(k) | String problems with characters |

## 🎓 **Practice Problems**

### **Beginner**
1. [Maximum Average Subarray I](https://leetcode.com/problems/maximum-average-subarray-i/)
2. [Grumpy Bookstore Owner](https://leetcode.com/problems/grumpy-bookstore-owner/)
3. [Maximum Sum of 3 Non-Overlapping Subarrays](https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/)

### **Intermediate**
1. [Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/)
2. [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)
3. [Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/)

### **Advanced**
1. [Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)
2. [Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)
3. [Subarrays with K Different Integers](https://leetcode.com/problems/subarrays-with-k-different-integers/)

## 🔗 **Related Patterns**
- **Two Pointers** - Foundation of Sliding Window
- **Hash Map** - Count and track elements
- **Monotonic Queue/Stack** - Optimize max/min
- **Binary Search** - Find optimal window size

## 🚀 **Optimization Tips**

### **1. Early Termination**
```cpp
// Stop early when result is found
if (maxLen == targetLength) break;
```

### **2. Memory Optimization**
```cpp
// Use vector instead of unordered_map for ASCII
vector<int> charCount(128, 0);
```

### **3. Boundary Conditions**
```cpp
// Handle edge cases
if (nums.empty() || k <= 0) return 0;
if (k > nums.size()) return -1;  // or handle appropriately
```

---

**Remember**: Sliding Window is a powerful pattern for substring/subarray problems. Practice to master it! 🚀
