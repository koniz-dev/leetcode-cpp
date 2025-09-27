# 128. Longest Consecutive Sequence

## Problem Statement
Given an unsorted array of integers `nums`, return the length of the longest consecutive elements sequence.

You must write an algorithm that runs in `O(n)` time.

**Example 1:**
```
Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
```

**Example 2:**
```
Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9
```

## DSA Concepts Used

### 1. Hash Set (unordered_set)
- **Purpose**: Provides O(1) average-case lookup time
- **Why Important**: Enables efficient existence checking without sorting
- **Key Insight**: Allows us to check if consecutive numbers exist without scanning the entire array

### 2. Greedy Algorithm Pattern
- **Strategy**: Only start counting from the beginning of each sequence
- **Optimization**: Avoid redundant work by identifying sequence starts
- **Efficiency**: Each number is visited at most twice

## Solution Approaches

### Approach 1: Hash Set with Sequence Start Detection (Optimal)
**Time Complexity**: O(n)  
**Space Complexity**: O(n)

**Algorithm:**
1. Store all numbers in a hash set for O(1) lookup
2. For each number, check if it's the start of a sequence (num-1 doesn't exist)
3. If it's a start, count consecutive numbers by incrementing and checking existence
4. Track the maximum sequence length

**Key Insight**: By only starting from sequence beginnings, we ensure each number is processed at most twice, achieving O(n) time complexity.

```cpp
int longestConsecutive(vector<int>& nums) {
    if (nums.empty()) return 0;
    
    unordered_set<int> numSet(nums.begin(), nums.end());
    int maxLength = 0;
    
    for (int num : numSet) {
        // Only start if this is the beginning of a sequence
        if (numSet.find(num - 1) == numSet.end()) {
            int currentNum = num;
            int currentLength = 1;
            
            // Count consecutive numbers
            while (numSet.find(currentNum + 1) != numSet.end()) {
                currentNum++;
                currentLength++;
            }
            
            maxLength = max(maxLength, currentLength);
        }
    }
    
    return maxLength;
}
```

### Approach 2: Sorting (Suboptimal)
**Time Complexity**: O(n log n)  
**Space Complexity**: O(1) or O(n) depending on sorting algorithm

**Algorithm:**
1. Sort the array
2. Iterate through sorted array counting consecutive sequences
3. Track the maximum length

**Why Suboptimal**: Sorting takes O(n log n) time, which doesn't meet the O(n) requirement.

```cpp
int longestConsecutive(vector<int>& nums) {
    if (nums.empty()) return 0;
    
    // Sort the array - O(n log n)
    sort(nums.begin(), nums.end());
    
    int maxLength = 1;
    int currentLength = 1;
    
    // Count consecutive sequences - O(n)
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] == nums[i-1] + 1) {
            // Consecutive number found
            currentLength++;
        } else if (nums[i] == nums[i-1]) {
            // Duplicate number, skip
            continue;
        } else {
            // Sequence broken, update max and reset
            maxLength = max(maxLength, currentLength);
            currentLength = 1;
        }
    }
    
    // Don't forget the last sequence
    maxLength = max(maxLength, currentLength);
    
    return maxLength;
}
```

### Approach 3: Union-Find (Advanced)
**Time Complexity**: O(n α(n)) where α is the inverse Ackermann function  
**Space Complexity**: O(n)

**Algorithm:**
1. Create a union-find data structure
2. For each number, union it with its consecutive neighbors
3. Find the size of the largest connected component

**When to Use**: More complex but useful for understanding advanced data structures.

```cpp
class UnionFind {
private:
    vector<int> parent;
    vector<int> size;
    
public:
    UnionFind(int n) : parent(n), size(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px != py) {
            if (size[px] < size[py]) swap(px, py);
            parent[py] = px;
            size[px] += size[py];
        }
    }
    
    int getSize(int x) {
        return size[find(x)];
    }
};

int longestConsecutive(vector<int>& nums) {
    if (nums.empty()) return 0;
    
    // Create mapping from value to index
    unordered_map<int, int> valueToIndex;
    for (int i = 0; i < nums.size(); i++) {
        valueToIndex[nums[i]] = i;
    }
    
    UnionFind uf(nums.size());
    
    // Union consecutive numbers
    for (int i = 0; i < nums.size(); i++) {
        int num = nums[i];
        
        // Check if num+1 exists and union them
        if (valueToIndex.count(num + 1)) {
            uf.unite(i, valueToIndex[num + 1]);
        }
    }
    
    // Find the largest component size
    int maxSize = 1;
    for (int i = 0; i < nums.size(); i++) {
        maxSize = max(maxSize, uf.getSize(i));
    }
    
    return maxSize;
}
```

## Learning Points

### 1. Hash Set Optimization
- **Lookup Efficiency**: Hash sets provide O(1) average-case lookup
- **Memory Trade-off**: Use extra space to achieve better time complexity
- **Modern C++**: `unordered_set` is the standard hash set implementation

### 2. Sequence Detection Pattern
- **Start Identification**: Look for sequence beginnings to avoid redundant work
- **Greedy Strategy**: Process each sequence only once from its start
- **Efficiency**: This pattern is common in sequence-related problems

### 3. Time Complexity Analysis
- **Naive Approach**: O(n²) - checking every pair
- **Sorting Approach**: O(n log n) - sorting dominates
- **Hash Set Approach**: O(n) - each element visited at most twice

### 4. Edge Cases
- **Empty Array**: Return 0
- **Single Element**: Return 1
- **All Same Elements**: Return 1
- **No Consecutive Elements**: Return 1

## Common Mistakes

1. **Not Checking Sequence Start**: Starting from every number leads to O(n²) complexity
2. **Using Vector Instead of Set**: Vector lookup is O(n), defeating the optimization
3. **Forgetting Edge Cases**: Empty arrays or single elements
4. **Incorrect Loop Condition**: Not properly checking for sequence boundaries

## Related Problems

- **Longest Increasing Subsequence**: Similar sequence finding with different constraints
- **Missing Number**: Uses similar hash set techniques
- **First Missing Positive**: Advanced version with space constraints
- **Array Nesting**: Another sequence detection problem

## Practice Recommendations

1. **Implement All Approaches**: Understand trade-offs between different solutions
2. **Test Edge Cases**: Empty arrays, single elements, duplicates
3. **Analyze Complexity**: Practice time/space complexity analysis
4. **Hash Set Mastery**: Practice more problems using hash sets for optimization

## Key Takeaways

- **Hash sets enable O(1) lookup** for existence checking
- **Sequence start detection** is a powerful optimization pattern
- **Greedy algorithms** can achieve optimal time complexity
- **Space-time trade-offs** are common in algorithm optimization
- **Modern C++ features** like `unordered_set` provide efficient implementations
