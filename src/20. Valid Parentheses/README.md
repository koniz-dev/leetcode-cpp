# [20. Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)

## Problem Statement

Given a string `s` containing just the characters `'('`, `')'`, `'{'`, `'}'`, `'['` and `']'`, determine if the input string is valid.

An input string is valid if:
1. Open brackets must be closed by the same type of brackets.
2. Open brackets must be closed in the correct order.
3. Every close bracket has a corresponding open bracket of the same type.

**Example 1:**
```
Input: s = "()"
Output: true
```

**Example 2:**
```
Input: s = "()[]{}"
Output: true
```

**Example 3:**
```
Input: s = "(]"
Output: false
```

**Constraints:**
- `1 <= s.length <= 10^4`
- `s` consists of parentheses only `'()[]{}'`.

## Approach 1: Stack with Hash Map (Optimized)

**Algorithm:**
1. Use a stack to track opening brackets
2. Use a hash map for O(1) bracket matching lookup
3. For each character:
   - If it's an opening bracket `(`, `[`, `{`: push to stack
   - If it's a closing bracket `)`, `]`, `}`: 
     - Check if stack is empty (no matching opening bracket)
     - Check if top of stack matches the expected opening bracket
     - Pop the matched opening bracket
4. Return `true` only if stack is empty after processing all characters

**Time Complexity:** O(n) - Single pass through the string  
**Space Complexity:** O(n) - Stack can hold up to n/2 opening brackets in worst case

**Implementation:** See `optimized.cpp`

## Approach 2: Stack with Direct Comparison

**Algorithm:**
1. Use a stack to track opening brackets
2. For each character:
   - If it's an opening bracket: push to stack
   - If it's a closing bracket:
     - Check if stack is empty
     - Check if top of stack matches the closing bracket using direct comparison
     - Pop the matched opening bracket
3. Return `true` only if stack is empty

**Time Complexity:** O(n) - Single pass through the string  
**Space Complexity:** O(n) - Stack can hold up to n/2 opening brackets in worst case

**Implementation:** See `main.cpp`

## Key DSA Concepts

### Stack Data Structure
- **LIFO (Last In, First Out)** principle
- Perfect for tracking nested structures like parentheses
- Operations: `push()`, `pop()`, `top()`, `empty()`

### Hash Map for Lookup
- **O(1) average case** lookup time
- Maps closing brackets to their corresponding opening brackets
- Reduces code complexity and improves readability

### String Processing
- **Single pass algorithm** - process each character exactly once
- **Early termination** - return false as soon as invalid condition is detected

## Common Pitfalls

1. **Forgetting to check if stack is empty** before accessing top element
2. **Not handling the case** where closing brackets appear before opening brackets
3. **Incorrect bracket matching logic** - ensure proper pairing
4. **Not checking if stack is empty** at the end - unmatched opening brackets

## Related Problems

- [22. Generate Parentheses](https://leetcode.com/problems/generate-parentheses/)
- [32. Longest Valid Parentheses](https://leetcode.com/problems/longest-valid-parentheses/)
- [301. Remove Invalid Parentheses](https://leetcode.com/problems/remove-invalid-parentheses/)
- [678. Valid Parenthesis String](https://leetcode.com/problems/valid-parenthesis-string/)

## Learning Notes

### Why Stack is Perfect for This Problem
- **Nested structure**: Parentheses can be nested within each other
- **LIFO matching**: The most recently opened bracket must be closed first
- **State tracking**: Stack maintains the current "depth" of nesting

### Optimization Techniques
- **Hash map lookup**: O(1) bracket matching vs O(1) but cleaner code
- **Early termination**: Return false immediately when invalid condition detected
- **Single pass**: Process each character exactly once

### Edge Cases to Consider
- Empty string (handled by constraint)
- Single character strings
- All opening brackets
- All closing brackets
- Mixed valid and invalid patterns
