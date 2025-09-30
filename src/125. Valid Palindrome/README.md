# [125. Valid Palindrome](https://leetcode.com/problems/valid-palindrome/)

## Problem Statement

A phrase is a **palindrome** if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward.

Given a string `s`, return `true` if it is a palindrome, or `false` otherwise.

### Examples

```
Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.

Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.

Input: s = " "
Output: true
Explanation: s is an empty string "" after removing non-alphanumeric characters.
Since an empty string reads the same forward and backward, it is a palindrome.
```

## DSA Concepts Used

- **Two Pointers Technique**: Efficiently traverse from both ends
- **String Processing**: Character validation and case conversion
- **In-place Algorithm**: No additional space for string manipulation

## Solution Approaches

### Approach 1: Two Pointers (Optimized)

**Key Insight:** Use two pointers to compare characters from both ends, skipping non-alphanumeric characters in-place.

**Implementation:** See `optimized.cpp` for the complete implementation.

**Time Complexity:** O(n) - Single pass through the string  
**Space Complexity:** O(1) - Only using constant extra space

### Approach 2: String Cleaning + Two Pointers

**Key Insight:** First clean the string by removing non-alphanumeric characters and converting to lowercase, then use two pointers.

**Implementation:** See `main.cpp` for the complete implementation.

**Time Complexity:** O(n) - Two passes through the string  
**Space Complexity:** O(n) - Additional string for cleaned version

### Approach 3: Reverse and Compare

**Key Insight:** Clean the string and compare it with its reverse.

```cpp
bool isPalindrome(string s) {
    string cleaned;
    for (char c : s) {
        if (isalnum(c)) {
            cleaned += tolower(c);
        }
    }
    
    string reversed = cleaned;
    reverse(reversed.begin(), reversed.end());
    
    return cleaned == reversed;
}
```

**Time Complexity:** O(n) - Multiple passes for cleaning and reversing  
**Space Complexity:** O(n) - Two additional strings

## Algorithm Analysis

### Why Two Pointers is Optimal

1. **Space Efficiency**: No additional string allocation needed
2. **Time Efficiency**: Single pass through the input
3. **Early Termination**: Can return false as soon as mismatch is found
4. **Memory Locality**: Better cache performance with in-place processing

### Edge Cases to Consider

1. **Empty string**: Should return true
2. **Single character**: Should return true
3. **Only non-alphanumeric characters**: Should return true
4. **Mixed case**: Should be case-insensitive
5. **Special characters**: Should be ignored

## C++ Features Demonstrated

- **`isalnum()`**: Character classification function
- **`tolower()`**: Case conversion function
- **Two-pointer technique**: Efficient string traversal
- **In-place processing**: Memory-efficient algorithm design

## Related Problems

- [680. Valid Palindrome II](https://leetcode.com/problems/valid-palindrome-ii/) - Can remove at most one character
- [9. Palindrome Number](https://leetcode.com/problems/palindrome-number/) - Check if integer is palindrome
- [234. Palindrome Linked List](https://leetcode.com/problems/palindrome-linked-list/) - Check if linked list is palindrome

## Learning Takeaways

1. **Two Pointers Technique**: Extremely useful for palindrome and string problems
2. **In-place Processing**: Always consider if you can avoid extra space
3. **Character Classification**: Use built-in functions like `isalnum()` for efficiency
4. **Early Termination**: Return as soon as you know the answer
5. **Edge Case Handling**: Always consider empty strings and special characters

## Implementation Notes

- The optimized solution uses the two-pointer approach for maximum efficiency
- Character validation and case conversion are done on-the-fly
- The algorithm handles all edge cases naturally
- Modern C++ features like range-based loops could be used but two pointers are more efficient here
