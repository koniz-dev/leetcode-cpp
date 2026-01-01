# 🔍 Binary Search

## 📚 Overview
**Binary Search** is an efficient search algorithm with O(log n) complexity, using the sorted property of data.

## 🎯 **When to Use**
- **Sorted arrays** - Search in sorted arrays
- **Rotated sorted arrays** - Search in arrays that have been rotated
- **Monotonic functions** - Monotonic functions (increasing/decreasing)
- **Optimization problems** - Find optimal values (Binary Search on Answer)
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

### **1. Rotated Sorted Array**
When an array is rotated, one half is always sorted. We can use this property to decide which half to search.

```mermaid
graph TD
    A[Start: left, right] --> B{left <= right?}
    B -- No --> C[Return -1]
    B -- Yes --> D[mid = left + (right-left)/2]
    D --> E{nums[mid] == target?}
    E -- Yes --> F[Return mid]
    E -- No --> G{nums[left] <= nums[mid]?}
    G -- Yes: Left Sorted --> H{nums[left] <= target < nums[mid]?}
    H -- Yes --> I[right = mid - 1]
    H -- No --> J[left = mid + 1]
    G -- No: Right Sorted --> K{nums[mid] < target <= nums[right]?}
    K -- Yes --> L[left = mid + 1]
    K -- No --> M[right = mid - 1]
    I --> B
    J --> B
    L --> B
    M --> B
```

```cpp
int searchRotated(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) return mid;
        
        // Check if left half is sorted
        if (nums[left] <= nums[mid]) {
            if (nums[left] <= target && target < nums[mid])
                right = mid - 1;
            else
                left = mid + 1;
        } 
        // Right half is sorted
        else {
            if (nums[mid] < target && target <= nums[right])
                left = mid + 1;
            else
                right = mid - 1;
        }
    }
    return -1;
}
```

### **2. Binary Search on Answer**
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

### **3. Binary Search on 2D Array**
```cpp
// Search in sorted 2D array
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    int left = 0, right = m * n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int row = mid / n, col = mid % n;
        
        if (matrix[row][col] == target) return true;
        else if (matrix[row][col] < target) left = mid + 1;
        else right = mid - 1;
    }
    return false;
}
```

## 📊 **Comparison of Variations**

| Variation | Condition | Key Logic | Use Case |
|---|---|---|---|
| **Standard** | `nums[mid] == target` | `mid < target ? left=mid+1 : right=mid-1` | Exact match in sorted array |
| **Lower Bound** | `nums[mid] >= target` | Find first `x >= target` | Insertion point, duplicate handling |
| **Upper Bound** | `nums[mid] > target` | Find first `x > target` | Range counting, last occurrence |
| **Rotated** | `nums[left] <= nums[mid]` | Identify sorted half first | Rotated sorted arrays (e.g. `[4,5,1,2,3]`) |
| **On Answer** | `isValid(mid)` | `isValid ? right=mid : left=mid+1` | Optimization problems (Min-Max) |

## 🎓 **Practice Problems by Category**

### **Basic Binary Search**
1. [704. Binary Search](https://leetcode.com/problems/binary-search/)
2. [35. Search Insert Position](https://leetcode.com/problems/search-insert-position/)
3. [278. First Bad Version](https://leetcode.com/problems/first-bad-version/)

### **Rotated Arrays**
1. [33. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)
2. [153. Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)
3. [81. Search in Rotated Sorted Array II](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/)

### **Range & Optimization**
1. [34. Find First and Last Position](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)
2. [981. Time Based Key-Value Store](https://leetcode.com/problems/time-based-key-value-store/)
3. [875. Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/)
4. [410. Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/)

### **Matrix Problems**
1. [74. Search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/)
2. [240. Search a 2D Matrix II](https://leetcode.com/problems/search-a-2d-matrix-ii/)

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

---

**Remember**: Binary Search requires sorted data or monotonic functions. Practice to identify patterns! 🚀
