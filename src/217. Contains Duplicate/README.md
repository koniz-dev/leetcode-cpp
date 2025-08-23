# 217. Contains Duplicate

## Problem Description

Given an integer array `nums`, return `true` if any value appears at least twice in the array, and return `false` if every element is distinct.

### Examples

**Example 1:**
```
Input: nums = [1,2,3,1]
Output: true
```

**Example 2:**
```
Input: nums = [1,2,3,4]
Output: false
```

**Example 3:**
```
Input: nums = [1,1,1,3,3,4,3,2,4,2]
Output: true
```

### Constraints
- `1 <= nums.length <= 10^5`
- `-10^9 <= nums[i] <= 10^9`

## Solution Approaches

### Approach 1: Hash Set (Recommended)
**Time Complexity:** O(n)  
**Space Complexity:** O(n)

Use an `unordered_set` to track seen elements. If we encounter an element that's already in the set, we've found a duplicate.

```cpp
bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> seen;
    
    for (int num : nums) {
        if (seen.find(num) != seen.end()) {
            return true;  // Duplicate found
        }
        seen.insert(num);
    }
    
    return false;  // No duplicates
}
```

**Key Points:**
- Most efficient approach for this problem
- Uses hash set for O(1) average lookup time
- Single pass through the array

### Approach 2: Hash Map (Alternative)
**Time Complexity:** O(n)  
**Space Complexity:** O(n)

Use an `unordered_map` to count occurrences. Return true if any element appears more than once.

```cpp
bool containsDuplicateMap(vector<int>& nums) {
    unordered_map<int, int> count;
    
    for (int num : nums) {
        count[num]++;
        if (count[num] > 1) {
            return true;  // Duplicate found
        }
    }
    
    return false;  // No duplicates
}
```

**Key Points:**
- Similar time/space complexity to hash set approach
- Useful when you need to track frequency of elements
- Slightly more memory usage than hash set

### Approach 3: Sorting
**Time Complexity:** O(n log n)  
**Space Complexity:** O(1) (if input can be modified)

Sort the array and check adjacent elements for duplicates.

```cpp
bool containsDuplicateSort(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] == nums[i-1]) {
            return true;  // Duplicate found
        }
    }
    
    return false;  // No duplicates
}
```

**Key Points:**
- Constant space complexity (if input modification is allowed)
- Slower time complexity due to sorting
- Useful when memory is extremely limited

## C++ Concepts Used

### Containers
- **`vector<int>`**: Dynamic array to store input numbers
- **`unordered_set<int>`**: Hash set for O(1) average lookup time
- **`unordered_map<int, int>`**: Hash map for counting occurrences

### Algorithms
- **Hash-based lookup**: Using `find()` method for O(1) average time complexity
- **Sorting**: Using `sort()` algorithm for O(n log n) time complexity

### C++ Features
- **Range-based for loop**: `for (int num : nums)` for cleaner iteration
- **References**: `vector<int>& nums` to avoid copying large arrays
- **STL containers**: Using standard library containers for efficient operations

## Related Problems
- [219. Contains Duplicate II](https://leetcode.com/problems/contains-duplicate-ii/) - Find duplicates within k distance
- [220. Contains Duplicate III](https://leetcode.com/problems/contains-duplicate-iii/) - Find duplicates within k distance and t value difference
- [136. Single Number](https://leetcode.com/problems/single-number/) - Find the single element in array of duplicates
- [268. Missing Number](https://leetcode.com/problems/missing-number/) - Find missing number in array

## Practice Tips
1. **Hash-based solutions** are usually the most efficient for duplicate detection
2. **Consider space constraints** - sorting approach uses O(1) space but O(n log n) time
3. **Think about early termination** - return as soon as first duplicate is found
4. **Consider edge cases** - empty arrays, single element arrays
5. **Choose appropriate container** - `unordered_set` for existence check, `unordered_map` for counting

## Test Cases
```cpp
// Test Case 1: Contains duplicates
vector<int> nums1 = {1, 2, 3, 1};
// Expected: true

// Test Case 2: No duplicates
vector<int> nums2 = {1, 2, 3, 4};
// Expected: false

// Test Case 3: Multiple duplicates
vector<int> nums3 = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};
// Expected: true

// Test Case 4: Empty array
vector<int> nums4 = {};
// Expected: false

// Test Case 5: Single element
vector<int> nums5 = {1};
// Expected: false
```
