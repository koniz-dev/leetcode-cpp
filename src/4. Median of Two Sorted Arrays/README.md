# [4. Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/)

## Problem Statement

Given two sorted arrays `nums1` and `nums2` of size `m` and `n` respectively, return the median of the two sorted arrays.

The overall run time complexity should be **O(log (m + n))**.

**Constraints:**
- `nums1.length == m`
- `nums2.length == n`
- `0 <= m <= 1000`
- `0 <= n <= 1000`
- `1 <= m + n <= 2000`
- `-10^6 <= nums1[i], nums2[i] <= 10^6`
- Both `nums1` and `nums2` are sorted in non-decreasing order

## Examples

```text
Input: nums1 = [1,3], nums2 = [2]
Output: 2.0
Explanation: merged array = [1,2,3] and median is 2.
```

```text
Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.5
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
```

```text
Input: nums1 = [0,0], nums2 = [0,0]
Output: 0.0
```

```text
Input: nums1 = [], nums2 = [1]
Output: 1.0
```

```text
Input: nums1 = [2], nums2 = []
Output: 2.0
```

## Approaches

### 1. Binary Search Partition (Optimized) – `optimized.cpp`

**Idea:**
- Always binary-search on the **smaller** array.
- Conceptually partition the two arrays into **left** and **right** parts.
- Choose a cut position `i` in `nums1`, and derive `j` in `nums2` so that the total left part has `(m + n + 1) / 2` elements.
- Let:
  - `L1 = nums1[i - 1]` or `-∞` if `i == 0`
  - `R1 = nums1[i]` or `+∞` if `i == m`
  - `L2 = nums2[j - 1]` or `-∞` if `j == 0`
  - `R2 = nums2[j]` or `+∞` if `j == n`
- A correct partition satisfies `L1 <= R2` and `L2 <= R1`.
- Once correct partition is found:
  - If total length is odd → median is `max(L1, L2)`.
  - If even → median is `(max(L1, L2) + min(R1, R2)) / 2.0`.

**Why it works:**
- Binary search invariant maintains that we are searching for a partition where:
  - All elements in the left part are ≤ all elements in the right part.
  - Left part size is fixed to half of the total length.
- Using sentinel values (`INT_MIN`, `INT_MAX`) avoids special-case handling at array boundaries.

**Complexity:**
- Time: `O(log(min(m, n)))` – binary search on the smaller array.
- Space: `O(1)` – constant extra variables.

### 2. Merge and Then Find Median – `O(m + n)` Time

**Idea:**
- Use two pointers to merge the two sorted arrays into a single sorted array (or just iterate until reaching the median index).
- After merge:
  - If total length is odd → take middle element.
  - If even → average the two middle elements.

**Complexity:**
- Time: `O(m + n)` – full linear merge.
- Space: `O(m + n)` if building a merged array, or `O(1)` extra if only tracking current/previous element until the median index.

This approach is simpler conceptually but does **not** meet the required `O(log (m + n))` time complexity, so it is mainly useful as a baseline or for understanding.

### 3. Two Pointers Without Extra Array – `O(m + n)` Time, `O(1)` Space

**Idea:**
- Similar to the merge step in merge sort, but instead of building a new array:
  - Maintain two indices `i` and `j` for `nums1` and `nums2`.
  - Walk forward until you pass the median position(s), keeping track of the last one or two values seen.

**Complexity:**
- Time: `O(m + n)` – still linear in the combined length.
- Space: `O(1)` – only a few variables.

Again, this does not satisfy the logarithmic time requirement but is a good stepping stone toward understanding the optimized solution.

## DSA & C++ Concepts

- **Binary Search on Answer/Partition**:
  - Searching on a **position/partition** instead of the actual values.
  - Maintain invariants on left/right parts.
- **Two Pointers**:
  - Used in linear merge or streaming median calculation.
- **Edge Cases Handling**:
  - One array empty.
  - Highly unbalanced sizes (e.g., `m << n`).
  - Duplicate values and negative numbers.
- **C++ Concepts**:
  - `vector<int>` for dynamic arrays.
  - `INT_MIN`, `INT_MAX` from `<climits>` as sentinels.
  - `std::max` / `std::min` for comparing partition boundaries.

## Complexity Summary

| Approach                         | Time Complexity           | Space Complexity | Notes                                |
|----------------------------------|---------------------------|------------------|--------------------------------------|
| Binary Search Partition          | `O(log(min(m, n)))`      | `O(1)`           | Optimal, used in `optimized.cpp`     |
| Merge with Extra Array           | `O(m + n)`               | `O(m + n)`       | Simple but not optimal               |
| Two Pointers, No Extra Array     | `O(m + n)`               | `O(1)`           | Space-efficient, still linear time   |

## Key Insights

1. Median is about **partitioning** the combined sorted sequence into two halves.
2. You do **not** need to fully merge the arrays – only identify a correct partition.
3. Always binary search on the **shorter array** to keep the search space minimal.
4. Using sentinel values for boundaries greatly simplifies edge-case handling.

## Related Problems

- [1. Two Sum](https://leetcode.com/problems/two-sum/)
- [11. Container With Most Water](https://leetcode.com/problems/container-with-most-water/)
- [33. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)
- [704. Binary Search](https://leetcode.com/problems/binary-search/)

