# [22. Generate Parentheses](https://leetcode.com/problems/generate-parentheses/)

## Problem Statement

Given `n` pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

**Example 1:**
```
Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
```

**Example 2:**
```
Input: n = 1
Output: ["()"]
```

**Constraints:**
- `1 <= n <= 8`

## Approach Analysis

### Approach 1: Backtracking (Optimized Solution)
**Time Complexity:** O(4^n / √n) - Catalan number  
**Space Complexity:** O(n) - Recursion depth

The backtracking approach is the most intuitive and commonly taught solution for this problem. It uses recursion to explore all possible valid combinations by:

1. **Building strings character by character** - Add '(' or ')' one at a time
2. **Maintaining validity constraints** - Only add ')' when we have more '(' than ')'
3. **Backtracking** - Remove the last character when returning from recursion
4. **Base case** - When string length equals 2n, we have a valid combination

**Key DSA Concepts:**
- **Backtracking**: Systematic exploration of all possible solutions
- **Recursion**: Breaking down the problem into smaller subproblems
- **Constraint satisfaction**: Ensuring parentheses are always balanced

### Approach 2: Iterative with Stack (Current Implementation)
**Time Complexity:** O(4^n / √n) - Same as backtracking  
**Space Complexity:** O(4^n / √n) - Stack stores all intermediate states

The iterative approach uses a stack to simulate the recursive process:

1. **Stack-based state management** - Store (current_string, open_count, close_count)
2. **Systematic exploration** - Process all states in the stack
3. **Constraint checking** - Only generate valid combinations

**Key DSA Concepts:**
- **Stack data structure**: LIFO behavior for state management
- **Iterative algorithms**: Converting recursive logic to iterative
- **State space exploration**: Systematic traversal of all possibilities

## Solution Implementations

### Backtracking Solution (optimized.cpp)
See `optimized.cpp` for the complete backtracking implementation with comprehensive comments and modern C++ features.

### Iterative Stack Solution (main.cpp)  
See `main.cpp` for the complete iterative stack-based implementation using structured bindings and tuple state management.

### Dynamic Programming Approach
This approach uses memoization to avoid recalculating the same subproblems:

```cpp
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        unordered_map<int, vector<string>> memo;
        return generateParenthesisDP(n, memo);
    }
    
private:
    vector<string> generateParenthesisDP(int n, unordered_map<int, vector<string>>& memo) {
        if (n == 0) return {""};
        if (memo.count(n)) return memo[n];
        
        vector<string> result;
        for (int i = 0; i < n; i++) {
            for (string left : generateParenthesisDP(i, memo)) {
                for (string right : generateParenthesisDP(n - 1 - i, memo)) {
                    result.push_back("(" + left + ")" + right);
                }
            }
        }
        
        memo[n] = result;
        return result;
    }
};
```

**Time Complexity:** O(4^n / √n) - Same as backtracking but with memoization  
**Space Complexity:** O(4^n / √n) - Memoization storage

## Complexity Analysis

### Time Complexity: O(4^n / √n)
- **Catalan Number**: The number of valid parentheses combinations follows the Catalan sequence
- **Exponential Growth**: Each valid sequence has exactly 2n characters
- **Pruning**: The constraint `close < open` significantly reduces the search space

### Space Complexity
- **Backtracking**: O(n) - Recursion depth and string building
- **Iterative**: O(4^n / √n) - Stack stores all intermediate states

## Key Learning Points

### 1. Backtracking Pattern
- **Choose**: Add '(' or ')' to current string
- **Explore**: Recursively generate remaining characters
- **Unchoose**: Remove the character when backtracking

### 2. Constraint Satisfaction
- **Validity Rules**: 
  - Can add '(' if `open < n`
  - Can add ')' if `close < open`
- **Base Case**: String length equals 2n

### 3. Catalan Numbers
- **Mathematical Insight**: The number of valid parentheses combinations is the nth Catalan number
- **Formula**: C(n) = (2n)! / ((n+1)! * n!)
- **Growth Rate**: Approximately 4^n / √n

## Related Problems
- [20. Valid Parentheses](https://leetcode.com/problems/valid-parentheses/) - Check if parentheses are valid
- [32. Longest Valid Parentheses](https://leetcode.com/problems/longest-valid-parentheses/) - Find longest valid substring
- [301. Remove Invalid Parentheses](https://leetcode.com/problems/remove-invalid-parentheses/) - Remove minimum invalid parentheses

## C++ Features Demonstrated

### Modern C++ Features
- **Structured Bindings**: `auto [current, open, close] = st.top()`
- **RAII**: Automatic memory management with `vector` and `string`
- **Const Correctness**: Proper use of const references

### Best Practices
- **Clear Function Signatures**: Descriptive parameter names
- **Separation of Concerns**: Helper function for backtracking logic
- **Efficient String Operations**: Using `push_back()` and `pop_back()`

This problem is an excellent introduction to backtracking algorithms and demonstrates how constraint satisfaction can be used to generate valid combinations efficiently.
