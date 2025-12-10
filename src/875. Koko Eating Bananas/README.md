# [875. Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/)

## Problem Statement

Koko loves to eat bananas. There are `n` piles of bananas, the `i`th pile has `piles[i]` bananas. The guards have gone and will come back in `h` hours.

Koko can decide her bananas-per-hour eating speed of `k`. Each hour, she chooses some pile of bananas and eats `k` bananas from that pile. If the pile has less than `k` bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return *the minimum integer `k` such that she can eat all the bananas within `h` hours*.

**Example 1:**
```
Input: piles = [3,6,7,11], h = 8
Output: 4
Explanation: 
- With speed 4: [3,6,7,11] takes [1,2,2,3] hours = 8 hours total ✓
- With speed 3: [3,6,7,11] takes [1,2,3,4] hours = 10 hours total ✗
```

**Example 2:**
```
Input: piles = [30,11,23,4,20], h = 5
Output: 30
Explanation: 
- With speed 30: [30,11,23,4,20] takes [1,1,1,1,1] hours = 5 hours total ✓
```

**Example 3:**
```
Input: piles = [30,11,23,4,20], h = 6
Output: 23
Explanation: 
- With speed 23: [30,11,23,4,20] takes [2,1,1,1,1] hours = 6 hours total ✓
```

**Constraints:**
- `1 <= piles.length <= 10^4`
- `piles.length <= h <= 10^9`
- `1 <= piles[i] <= 10^9`

## Approach Analysis

### Approach 1: Binary Search on Answer (Optimized Solution)
**Time Complexity:** O(n * log(max(piles))) - Binary search on answer space  
**Space Complexity:** O(1) - Only using constant extra space

This is a classic "binary search on answer" problem. Instead of searching in a sorted array, we search in the answer space [1, max(piles)].

**Key Insight:** The answer space has a monotonic property: if speed `k` works, all speeds `> k` also work.

**Algorithm:**
1. **Set Search Range** - `left = 1`, `right = max(piles)`
2. **Binary Search** - For each candidate speed `mid`:
   - Calculate total hours needed: sum of `ceil(pile[i] / mid)` for all piles
   - If `hoursNeeded <= h`: speed is valid, try slower speed (search left)
   - If `hoursNeeded > h`: speed too slow, try faster speed (search right)
3. **Return Minimum Valid Speed** - Return `left` after binary search completes

**Key DSA Concepts:**
- **Binary Search on Answer**: Searching in answer space instead of array
- **Monotonic Property**: If speed k works, all speeds > k also work
- **Ceiling Division**: Efficient calculation using `(pile + speed - 1) / speed`

### Approach 2: Linear Search (Brute Force)
**Time Complexity:** O(n * max(piles)) - Try every possible speed  
**Space Complexity:** O(1) - Constant extra space

Try every possible speed from 1 to max(piles):

```cpp
int minEatingSpeed(vector<int>& piles, int h) {
    int maxPile = *max_element(piles.begin(), piles.end());
    
    for (int speed = 1; speed <= maxPile; speed++) {
        long long hoursNeeded = 0;
        for (int pile : piles) {
            hoursNeeded += (pile + speed - 1) / speed;
        }
        if (hoursNeeded <= h) {
            return speed;
        }
    }
    return maxPile;
}
```

**When to Use:**
- Only when max(piles) is very small
- For educational purposes to understand the problem

## Solution Implementations

### Binary Search on Answer (optimized.cpp)
See `optimized.cpp` for the complete binary search implementation with comprehensive comments explaining the "binary search on answer" technique.

### Binary Search on Answer (main.cpp)
See `main.cpp` for the user's personal implementation using the same binary search approach.

## Complexity Analysis

### Time Complexity: O(n * log(max(piles)))
- **Binary Search Iterations**: O(log(max(piles))) - Each iteration halves the search space
- **Validation per Iteration**: O(n) - Calculate hours needed for all piles
- **Overall**: O(n * log(max(piles)))
- **Example**: For n = 10^4, max(piles) = 10^9 → ~30 iterations × 10^4 = 3×10^5 operations

### Space Complexity: O(1)
- **Constant Space**: Only using a few variables (left, right, mid, hoursNeeded, maxPile)
- **No Extra Data Structures**: No arrays, maps, or stacks needed
- **Iterative Approach**: No recursion stack overhead

## Key Learning Points

### 1. Binary Search on Answer Pattern
- **Concept**: Search in the answer space instead of a sorted array
- **When to Use**: Problem asks for minimum/maximum value that satisfies a condition
- **Key Requirement**: We can validate if a candidate answer works efficiently
- **Monotonic Property**: The answer space must have a monotonic property enabling binary search

### 2. Ceiling Division Trick
- **Problem**: Calculate `ceil(a / b)` efficiently in integer arithmetic
- **Solution**: `(a + b - 1) / b`
- **Why It Works**: 
  - If `a` is divisible by `b`: `(a + b - 1) / b = a / b` ✓
  - If `a` is not divisible: adds `b-1` to round up
- **Example**: `ceil(10/3) = 4` → `(10 + 3 - 1) / 3 = 12 / 3 = 4` ✓

### 3. Monotonic Property
- **Key Insight**: If speed `k` allows finishing in `h` hours, then any speed `> k` also works
- **Why**: Higher speed means eating faster, so if we can finish with speed `k`, we can definitely finish with speed `k+1`
- **Visualization**:
  ```
  Speed:  1  2  3  4  5  6  7  8  9  10
  Valid:  ✗  ✗  ✗  ✓  ✓  ✓  ✓  ✓  ✓  ✓
                  ↑
              Minimum valid speed
  ```

### 4. Overflow Prevention
- **Issue**: `hoursNeeded` can overflow `int` when piles are large
- **Solution**: Use `long long` for `hoursNeeded`
- **Example**: 10^4 piles, each requiring 10^9 hours (worst case) → Total: 10^13 (exceeds `int` range)

## Common Pitfalls

### 1. Wrong Binary Search Template
- **Wrong**: `while (left < right)` with `right = mid` (might miss the answer)
- **Correct**: `while (left <= right)` with `right = mid - 1` for minimum valid answer
- **Why**: Need to ensure we check all valid positions and correctly identify the minimum

### 2. Integer Overflow
- **Wrong**: `int hoursNeeded = 0;` (can overflow!)
- **Correct**: `long long hoursNeeded = 0;` (use long long)
- **Why**: When accumulating hours for large piles, total can exceed int range

### 3. Wrong Ceiling Calculation
- **Wrong**: `hoursNeeded += pile / speed;` (floor division, not ceiling!)
- **Correct**: `hoursNeeded += (pile + speed - 1) / speed;` (efficient ceiling)
- **Why**: Need to round up to account for partial hours

### 4. Incorrect Search Range
- **Wrong**: `int right = maxPile + 1;` (unnecessary, maxPile is already valid)
- **Correct**: `int right = maxPile;` (maximum needed speed)
- **Why**: maxPile is already a valid speed (one pile per hour)

## Related Problems

- [410. Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/) - Similar binary search on answer pattern
- [1011. Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/) - Very similar problem
- [1482. Minimum Number of Days to Make m Bouquets](https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/) - Same technique
- [704. Binary Search](https://leetcode.com/problems/binary-search/) - Basic binary search on 1D array
- [35. Search Insert Position](https://leetcode.com/problems/search-insert-position/) - Binary search with insertion point

## C++ Features Demonstrated

### Modern C++ Features
- **STL Algorithms**: `max_element()` for finding maximum
- **Range-based for loops**: `for (int pile : piles)` for cleaner iteration
- **References**: `vector<int>&` for efficient parameter passing
- **Type Safety**: Using `long long` to prevent overflow

### Best Practices
- **Overflow Safety**: Safe middle calculation `left + (right - left) / 2` prevents integer overflow
- **Clear Variable Names**: `hoursNeeded`, `maxPile` are self-documenting
- **Efficient Division**: Ceiling division trick `(pile + speed - 1) / speed`
- **Const Correctness**: Consider using `const vector<int>&` if not modifying

## Practice Tips

1. **Master the Pattern**: Binary search on answer is a powerful technique for optimization problems
2. **Recognize Monotonicity**: Identify when a problem has monotonic properties in the answer space
3. **Practice Validation**: Write efficient validation functions for candidate answers
4. **Handle Edge Cases**: Empty arrays, single element, maximum constraints
5. **Watch for Overflow**: Use `long long` when accumulating values that could exceed `int` range
6. **Visualize**: Draw the answer space and understand the search process

This problem demonstrates how binary search can be applied beyond simple array searching. The key insight is recognizing that the answer space has a monotonic property, enabling efficient binary search to find the minimum valid speed.
