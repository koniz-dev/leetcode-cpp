# [981. Time Based Key-Value Store](https://leetcode.com/problems/time-based-key-value-store/)

## Problem Statement

Design a time-based key-value data structure that can store multiple values for the same key at different time stamps and retrieve the key's value at a certain timestamp.

Implement the `TimeMap` class:

- `TimeMap()` Initializes the object of the data structure.
- `void set(String key, String value, int timestamp)` Stores the key `key` with the value `value` at the given time `timestamp`.
- `String get(String key, int timestamp)` Returns a value such that `set` was called previously, with `timestamp_prev <= timestamp`. If there are multiple such values, it returns the value associated with the largest `timestamp_prev`. If there are no values, it returns `""`.

**Example 1:**
```
Input
["TimeMap", "set", "get", "get", "set", "get", "get"]
[[], ["foo", "bar", 1], ["foo", 1], ["foo", 3], ["foo", "bar2", 4], ["foo", 4], ["foo", 5]]
Output
[null, null, "bar", "bar", null, "bar2", "bar2"]

Explanation
TimeMap timeMap = new TimeMap();
timeMap.set("foo", "bar", 1);  // store the key "foo" and value "bar" along with timestamp = 1.
timeMap.get("foo", 1);         // return "bar"
timeMap.get("foo", 3);         // return "bar", since there is no value at timestamp 3 and timestamp 2, then the only value is at timestamp 1 is "bar".
timeMap.set("foo", "bar2", 4); // store the key "foo" and value "bar2" along with timestamp = 4.
timeMap.get("foo", 4);         // return "bar2"
timeMap.get("foo", 5);         // return "bar2"
```

**Constraints:**
- `1 <= key.length, value.length <= 100`
- `key` and `value` consist of lowercase English letters and digits.
- `1 <= timestamp <= 10^7`
- All the timestamps `timestamp` of `set` are strictly increasing.
- At most `2 * 10^5` calls will be made to `set` and `get`.

## Approach Analysis

### Approach 1: Hash Map + Binary Search (Optimized Solution)
**Time Complexity:** 
- `set`: O(1)
- `get`: O(log n) where n is the number of entries for the key
**Space Complexity:** O(n) total space

We use a Hash Map (`unordered_map`) to store the mapping from `key` to a list of values. Since we need to retrieve values based on timestamps, we store a list of pairs `(timestamp, value)` for each key.

**Key Insight**: The problem statement guarantees that "All the timestamps `timestamp` of `set` are strictly increasing."
- This means the list of pairs for any key is **naturally sorted** by timestamp.
- We don't need to sort it manually.
- We can use **Binary Search** to efficiently find the target timestamp.

**Algorithm for `get(key, timestamp)`**:
1. Look up the list for `key`. If not found, return `""`.
2. Perform Binary Search on the list to find the element with the largest `timestamp_prev <= timestamp`.
   - We can use `std::upper_bound` to find the first element *greater than* `timestamp`.
   - The element we want is the one immediately preceding that position.
   - If `upper_bound` returns the beginning of the list, it means all timestamps are greater than `timestamp`, so we return `""`.

## Solution Implementations

### STL Upper Bound Solution (optimized.cpp)
See `optimized.cpp` for an implementation leveraging `std::upper_bound` for clean and efficient binary search.

### Manual Binary Search (main.cpp)
See `main.cpp` for an implementation using manual binary search logic, which is good for understanding the underlying mechanics.

## Key Learning Points
- **Hash Map + Vector**: Common pattern for grouping data by key.
- **Sorted Data Property**: Leveraging the fact that input is already sorted saves O(n log n) sorting time.
- **Binary Search Variations**: Using `upper_bound` vs manual implementation.

## Related Problems
- [33. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)
- [98. Validate Binary Search Tree](https://leetcode.com/problems/validate-binary-search-tree/)
- [224. Basic Calculator](https://leetcode.com/problems/basic-calculator/)
