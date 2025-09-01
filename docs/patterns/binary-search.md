# 🔍 Binary Search

## 📚 Overview
**Binary Search** is an efficient search algorithm with O(log n) complexity, using the sorted property of data.

## 🎯 **When to Use**
- **Sorted arrays** - Search in sorted arrays
- **Monotonic functions** - Monotonic functions (increasing/decreasing)
- **Optimization problems** - Find optimal values
- **Range problems** - Find ranges satisfying conditions
- **Answer validation** - Check feasibility of answers

## 🚀 **Core Implementation**

### **1. Standard Binary Search**
```cpp
// Search for target element in sorted array
int binarySearch(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;  // Avoid overflow
        
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;  // Not found
}
```

**Time Complexity**: O(log n)  
**Space Complexity**: O(1)

### **2. Lower Bound (First Occurrence)**
```cpp
// Find first occurrence of target
int lowerBound(vector<int>& nums, int target) {
    int left = 0, right = nums.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;  // First position >= target
}
```

### **3. Upper Bound (Last Occurrence)**
```cpp
// Find last occurrence of target
int upperBound(vector<int>& nums, int target) {
    int left = 0, right = nums.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] <= target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left - 1;  // Last position <= target
}
```

## 🔍 **Advanced Patterns**

### **1. Binary Search on Answer**
```cpp
// Find optimal value satisfying condition
int binarySearchOnAnswer(vector<int>& nums, int k) {
    int left = 1, right = 1e9;  // Range of answer
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (canAchieve(nums, mid, k)) {
            right = mid;  // Find smaller value
        } else {
            left = mid + 1;  // Increase value
        }
    }
    
    return left;
}
```

### **2. Binary Search with Custom Comparator**
```cpp
// Search with complex conditions
int binarySearchCustom(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Custom condition
        if (isValid(nums, mid, target)) {
            return mid;
        } else if (shouldGoRight(nums, mid, target)) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}
```

### **3. Binary Search on 2D Array**
```cpp
// Search in sorted 2D array
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) return false;
    
    int m = matrix.size(), n = matrix[0].size();
    int left = 0, right = m * n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int row = mid / n, col = mid % n;
        
        if (matrix[row][col] == target) {
            return true;
        } else if (matrix[row][col] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return false;
}
```

## 🔍 **Problem Examples**

### **Easy Level**
- [704. Binary Search](https://leetcode.com/problems/binary-search/)
- [35. Search Insert Position](https://leetcode.com/problems/search-insert-position/)
- [278. First Bad Version](https://leetcode.com/problems/first-bad-version/)

### **Medium Level**
- [34. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)
- [74. Search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/)
- [875. Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/)

### **Hard Level**
- [4. Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/)
- [410. Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/)
- [1231. Divide Chocolate](https://leetcode.com/problems/divide-chocolate/)

## 💡 **Key Insights**

### **1. Loop Termination**
```cpp
// Important: left <= right vs left < right
while (left <= right) {  // Standard search
    // ...
}

while (left < right) {   // Lower/Upper bound
    // ...
}
```

### **2. Mid Calculation**
```cpp
// Avoid overflow
int mid = left + (right - left) / 2;  // ✅ Good
int mid = (left + right) / 2;         // ❌ Potential overflow
```

### **3. Boundary Updates**
```cpp
// Update boundaries accurately
if (nums[mid] < target) {
    left = mid + 1;   // ✅ Correct
} else {
    right = mid - 1;  // ✅ Correct
}
```

## 🎯 **C++23 Modern Implementation**

### **Using std::ranges**
```cpp
// Modern C++23 approach with std::ranges
auto binarySearchModern = [&](const auto& nums, int target) -> int {
    auto it = std::ranges::lower_bound(nums, target);
    
    if (it != nums.end() && *it == target) {
        return std::ranges::distance(nums.begin(), it);
    }
    
    return -1;
};
```

### **Using std::views for Range Operations**
```cpp
// Search in range with std::views
auto searchInRange = [&](const auto& nums, int start, int end, int target) -> int {
    auto range = nums | std::views::drop(start) | std::views::take(end - start);
    auto it = std::ranges::find(range, target);
    
    if (it != range.end()) {
        return start + std::ranges::distance(range.begin(), it);
    }
    
    return -1;
};
```

### **Using std::binary_search**
```cpp
// Use std::binary_search
bool found = std::ranges::binary_search(nums, target);

// Or with custom comparator
bool found = std::ranges::binary_search(nums, target, std::greater{});
```

## 📊 **Complexity Analysis**

| Pattern | Time | Space | Best For |
|---------|------|-------|----------|
| Standard Search | O(log n) | O(1) | Simple search |
| Lower/Upper Bound | O(log n) | O(1) | Insert position |
| Answer Validation | O(log n) | O(1) | Optimization problems |
| 2D Search | O(log(m×n)) | O(1) | Matrix problems |

## 🎓 **Practice Problems by Category**

### **Basic Binary Search**
1. [Binary Search](https://leetcode.com/problems/binary-search/)
2. [Search Insert Position](https://leetcode.com/problems/search-insert-position/)
3. [First Bad Version](https://leetcode.com/problems/first-bad-version/)

### **Range Problems**
1. [Find First and Last Position](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)
2. [Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)
3. [Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)

### **Optimization Problems**
1. [Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/)
2. [Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/)
3. [Divide Chocolate](https://leetcode.com/problems/divide-chocolate/)

### **Matrix Problems**
1. [Search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/)
2. [Search a 2D Matrix II](https://leetcode.com/problems/search-a-2d-matrix-ii/)
3. [Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/)

## 🔗 **Related Patterns**
- **Two Pointers** - Combine with binary search
- **Sliding Window** - Optimize range
- **Dynamic Programming** - Optimization with binary search
- **Greedy** - Validation with binary search

## 🚀 **Optimization Tips**

### **1. Early Termination**
```cpp
// Terminate early if possible
if (nums[left] > target || nums[right] < target) return -1;
```

### **2. Custom Comparator**
```cpp
// Use lambda for complex conditions
auto isValid = [&](int mid) -> bool {
    return checkCondition(nums, mid, target);
};
```

### **3. Range Optimization**
```cpp
// Optimize initial range
int left = *std::ranges::min_element(nums);
int right = *std::ranges::max_element(nums);
```

---

**Remember**: Binary Search requires sorted data or monotonic functions. Practice to identify patterns! 🚀
