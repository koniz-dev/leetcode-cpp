# 49. Group Anagrams

## Problem Statement
Given an array of strings `strs`, group the anagrams together. You can return the answer in any order.

An **Anagram** is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

## Examples

### Example 1:
```
Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
```

### Example 2:
```
Input: strs = [""]
Output: [[""]]
```

### Example 3:
```
Input: strs = ["a"]
Output: [["a"]]
```

## Solution Approaches

### Approach 1: Hash Map with Sorted Keys (Optimized)
**Time Complexity:** O(N × M log M) where N is the number of strings and M is the average length of strings  
**Space Complexity:** O(N × M)

#### Algorithm:
1. **Create a hash map** to group anagrams by their sorted character representation
2. **For each string:**
   - Sort the characters to create a unique key
   - Add the original string to the group corresponding to that key
3. **Convert the map values** to the result vector

#### Key Insights:
- **Anagrams have identical sorted character sequences** - this is the core insight
- **Hash map provides O(1) average lookup** for grouping
- **Move semantics** optimize memory usage when building result

#### C++ Implementation:
```cpp
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> anagramGroups;
    
    for (const string& str : strs) {
        string key = str;
        sort(key.begin(), key.end());
        anagramGroups[key].push_back(str);
    }
    
    vector<vector<string>> result;
    result.reserve(anagramGroups.size());
    
    for (auto& [key, group] : anagramGroups) {
        result.push_back(move(group));
    }
    
    return result;
}
```

### Approach 2: Hash Map with Character Count (Alternative)
**Time Complexity:** O(N × M)  
**Space Complexity:** O(N × M)

#### Algorithm:
1. **For each string**, count the frequency of each character
2. **Use character count as key** instead of sorted string
3. **Group strings** with identical character counts

#### Implementation:
```cpp
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;
    
    for (const string& str : strs) {
        vector<int> count(26, 0);
        for (char c : str) {
            count[c - 'a']++;
        }
        
        string key;
        for (int i = 0; i < 26; i++) {
            key += to_string(count[i]) + '#';
        }
        
        groups[key].push_back(str);
    }
    
    vector<vector<string>> result;
    for (auto& [key, group] : groups) {
        result.push_back(move(group));
    }
    
    return result;
}
```

## Data Structures & Algorithms Used

### 1. Hash Map (unordered_map)
- **Purpose:** Group anagrams efficiently
- **Key Insight:** Use sorted string as key for O(1) grouping
- **C++ Benefits:** Average O(1) insertion and lookup

### 2. String Sorting
- **Purpose:** Create unique identifier for anagrams
- **Algorithm:** std::sort with O(M log M) complexity
- **Key Insight:** All anagrams sort to the same character sequence

### 3. Move Semantics
- **Purpose:** Optimize memory usage
- **Benefit:** Avoid unnecessary copying of vectors
- **C++ Feature:** std::move transfers ownership efficiently

## Key Learning Points

### 1. Anagram Recognition
- **Core Concept:** Anagrams have identical character frequencies
- **Implementation:** Sort characters or count frequencies
- **Trade-off:** Sorting is simpler, counting is more efficient for long strings

### 2. Hash Map Grouping Pattern
- **Common Pattern:** Use processed data as key for grouping
- **Applications:** Group by any transformation of input
- **Efficiency:** O(1) average grouping operations

### 3. Modern C++ Features
- **Structured Bindings:** `for (auto& [key, group] : map)`
- **Move Semantics:** `result.push_back(move(group))`
- **Reserve:** `result.reserve(size)` for performance

## Complexity Analysis

### Time Complexity: O(N × M log M)
- **N iterations** through input strings
- **M log M sorting** for each string of length M
- **O(1) hash map operations** (average case)

### Space Complexity: O(N × M)
- **Hash map storage** for all strings
- **Result vector** containing all grouped strings
- **Temporary sorted keys** during processing

## Edge Cases
1. **Empty strings:** Handled naturally by sorting
2. **Single character strings:** Work with any approach
3. **All identical strings:** Grouped together correctly
4. **No anagrams:** Each string forms its own group

## Related Problems
- [242. Valid Anagram](https://leetcode.com/problems/valid-anagram/)
- [438. Find All Anagrams in a String](https://leetcode.com/problems/find-all-anagrams-in-a-string/)
- [2273. Find Resultant Array After Removing Anagrams](https://leetcode.com/problems/find-resultant-array-after-removing-anagrams/)

## Practice Recommendations
1. **Understand the core insight** that anagrams have identical sorted sequences
2. **Practice hash map grouping patterns** - very common in interviews
3. **Learn when to use sorting vs counting** for anagram problems
4. **Master modern C++ features** like structured bindings and move semantics
