# [15. 3Sum](https://leetcode.com/problems/3sum/)

## Problem Statement

Given an integer array `nums`, return all the triplets `[nums[i], nums[j], nums[k]]` such that `i != j`, `i != k`, and `j != k`, and `nums[i] + nums[j] + nums[k] == 0`.

Notice that the solution set must not contain duplicate triplets.

**Example 1:**
```
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.
```

**Example 2:**
```
Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.
```

**Example 3:**
```
Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.
```

**Constraints:**
- `3 <= nums.length <= 3000`
- `-10^5 <= nums[i] <= 10^5`

## Approach 1: Two Pointers (Optimized)

**Algorithm:**
1. Sort the array to enable two-pointer technique and duplicate detection
2. Fix the first element and use two pointers for the remaining elements
3. Use left pointer from `i+1` and right pointer from the end
4. Skip duplicates at all three positions to avoid duplicate triplets
5. Early termination when `nums[i] > 0` since array is sorted

**Time Complexity:** O(n²) - Outer loop O(n), inner two-pointer scan O(n)
**Space Complexity:** O(1) - Only using constant extra space (excluding output)

**Key Insights:**
- Sorting enables the two-pointer technique and duplicate skipping
- Early termination when first element > 0 (since array is sorted)
- Careful duplicate handling at all three positions
- Two-pointer technique reduces time complexity from O(n³) to O(n²)

## Approach 2: Hash Set (Alternative)

**Algorithm:**
1. Sort the array
2. For each element, use hash set to find pairs that sum to negative of current element
3. Skip duplicates to avoid duplicate triplets

**Time Complexity:** O(n²) - Outer loop O(n), inner hash set operations O(n)
**Space Complexity:** O(n) - Hash set storage

```cpp
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    
    for (int i = 0; i < nums.size() - 2; ++i) {
        if (nums[i] > 0) break;
        if (i > 0 && nums[i] == nums[i-1]) continue;
        
        unordered_set<int> seen;
        for (int j = i + 1; j < nums.size(); ++j) {
            int complement = -(nums[i] + nums[j]);
            if (seen.count(complement)) {
                result.push_back({nums[i], complement, nums[j]});
                while (j + 1 < nums.size() && nums[j] == nums[j+1]) ++j;
            }
            seen.insert(nums[j]);
        }
    }
    
    return result;
}
```

## Approach 3: Brute Force (Not Recommended)

**Algorithm:**
1. Use three nested loops to check all possible triplets
2. Check if sum equals zero and triplet is not duplicate

**Time Complexity:** O(n³) - Three nested loops
**Space Complexity:** O(1) - Constant extra space

```cpp
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    set<vector<int>> uniqueTriplets;
    
    for (int i = 0; i < nums.size() - 2; ++i) {
        for (int j = i + 1; j < nums.size() - 1; ++j) {
            for (int k = j + 1; k < nums.size(); ++k) {
                if (nums[i] + nums[j] + nums[k] == 0) {
                    vector<int> triplet = {nums[i], nums[j], nums[k]};
                    sort(triplet.begin(), triplet.end());
                    uniqueTriplets.insert(triplet);
                }
            }
        }
    }
    
    for (const auto& triplet : uniqueTriplets) {
        result.push_back(triplet);
    }
    
    return result;
}
```

## Data Structures and Algorithms Used

### Two Pointers Technique
- **Concept:** Use two pointers moving towards each other to find pairs
- **When to use:** Sorted arrays, finding pairs/triplets with specific properties
- **Benefits:** Reduces time complexity, eliminates need for extra space

### Sorting
- **Purpose:** Enables two-pointer technique and duplicate detection
- **Time Complexity:** O(n log n)
- **Space Complexity:** O(1) for in-place sorting

### Duplicate Handling
- **Strategy:** Skip duplicates at all three positions
- **Implementation:** Check if current element equals previous element
- **Importance:** Prevents duplicate triplets in result

## Key Learning Points

1. **Two Pointers Technique:** Essential for reducing time complexity in array problems
2. **Sorting Benefits:** Enables efficient algorithms and duplicate detection
3. **Early Termination:** Optimize by stopping when no valid solution possible
4. **Duplicate Management:** Critical for problems requiring unique solutions
5. **Space-Time Tradeoff:** Two pointers vs hash set approaches

## Related Problems

- [Two Sum](https://leetcode.com/problems/two-sum/) - Foundation for two-pointer technique
- [3Sum Closest](https://leetcode.com/problems/3sum-closest/) - Variation with closest sum
- [4Sum](https://leetcode.com/problems/4sum/) - Extension to four elements
- [Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) - Two pointers on sorted array

## Implementation Notes

- **Modern C++ Features:** Use `emplace_back()` for efficiency
- **Const Correctness:** Use `const` for variables that don't change
- **Early Returns:** Implement early termination for optimization
- **Clear Variable Names:** Use descriptive names for better readability
