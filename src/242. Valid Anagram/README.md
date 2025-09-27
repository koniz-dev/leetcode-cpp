# Valid Anagram

## Problem Description
Given two strings `s` and `t`, return `true` if `t` is an anagram of `s`, and `false` otherwise.

An **Anagram** is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

## Examples
```
Input: s = "anagram", t = "nagaram"
Output: true
Explanation: Both strings contain the same characters with the same frequencies.

Input: s = "rat", t = "car"
Output: false
Explanation: Different characters and frequencies.

Input: s = "listen", t = "silent"
Output: true
Explanation: Same characters rearranged.
```

## Solutions

### 1. Optimized Solution (Character Frequency Counting) - `optimized.cpp`
**Time Complexity:** O(n)  
**Space Complexity:** O(1)

Uses a fixed-size array to count character frequencies. Counts characters in string `s` and decrements for string `t`. If any frequency becomes negative, the strings are not anagrams.

**Key DSA Concepts:**
- **Character Frequency Counting**: Using array as a frequency counter
- **Early Exit Optimization**: Check length first before processing
- **Single Pass Algorithm**: Process each string only once
- **Constant Space**: Fixed-size array regardless of input size

**Key C++ Concepts Used:**
- `vector<int>` - Fixed-size array for character counting
- `string` - String container with `length()` method
- Range-based for loops (`for (char c : s)`)
- Character arithmetic (`c - 'a'`) for array indexing

### 2. Sorting Solution (Current Implementation) - `main.cpp`
**Time Complexity:** O(n log n) - due to sorting  
**Space Complexity:** O(1) - in-place sorting

Sorts both strings and compares them. Simple but less efficient than frequency counting.

**Key DSA Concepts:**
- **Sorting**: Using comparison-based sorting
- **String Comparison**: Direct string equality check

**Key C++ Concepts Used:**
- `sort()` - STL sorting algorithm
- `begin()`, `end()` - Iterator access
- String comparison operator (`==`)

### 3. Hash Map Solution (Alternative)
**Time Complexity:** O(n)  
**Space Complexity:** O(k) where k is unique characters

Uses `unordered_map<char, int>` to count frequencies. More flexible for Unicode characters but uses more space.

```cpp
bool isAnagram(string s, string t) {
    if (s.length() != t.length()) return false;
    
    unordered_map<char, int> charCount;
    
    // Count characters in string s
    for (char c : s) {
        charCount[c]++;
    }
    
    // Decrement count for characters in string t
    for (char c : t) {
        charCount[c]--;
        if (charCount[c] < 0) {
            return false; // More occurrences in t than in s
        }
    }
    
    return true;
}
```

## DSA Knowledge Points

### String Algorithms
- **Anagram Detection**: Understanding what makes strings anagrams
- **Character Frequency Analysis**: Counting occurrences of characters
- **String Comparison**: Different methods to compare strings

### Optimization Techniques
- **Early Exit**: Check length before processing
- **Single Pass**: Process data only once when possible
- **Constant Space**: Use fixed-size data structures when applicable

### Algorithm Analysis
- **Time Complexity**: Understanding sorting vs. counting trade-offs
- **Space Complexity**: Fixed vs. variable space requirements
- **Input Constraints**: Leveraging problem constraints (lowercase letters)

## C++ Knowledge Points

### Containers
- **vector**: Fixed-size array for character counting
- **string**: String container with useful methods

### C++ Features
- **Range-based for loops**: `for (char c : s)` for clean iteration
- **Character arithmetic**: `c - 'a'` for array indexing
- **STL algorithms**: `sort()` for string sorting
- **Const correctness**: Understanding when to use references

### Memory Management
- **Stack allocation**: Fixed-size arrays for small, known ranges
- **Efficient iteration**: Avoiding unnecessary copying

## Related Problems
- [49. Group Anagrams](https://leetcode.com/problems/group-anagrams/)
- [438. Find All Anagrams in a String](https://leetcode.com/problems/find-all-anagrams-in-a-string/)
- [20. Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)
- [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)
- [76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)

## Practice Tips
1. **Always consider input constraints** - lowercase letters allow fixed-size array
2. **Think about early exits** - check length before processing
3. **Consider space vs. time trade-offs** - sorting vs. counting
4. **Use appropriate data structures** - array for small ranges, hash map for larger
5. **Understand anagram properties** - same characters, same frequencies

## Learning Objectives
- Master character frequency counting techniques
- Understand string algorithm optimization
- Learn when to use fixed-size vs. dynamic data structures
- Practice early exit optimization strategies
- Develop intuition for string comparison algorithms
