# [155. Min Stack](https://leetcode.com/problems/min-stack/)

## Problem Statement

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

Implement the `MinStack` class:

- `MinStack()` initializes the stack object.
- `void push(int val)` pushes the element `val` onto the stack.
- `void pop()` removes the element on the top of the stack.
- `int top()` gets the top element of the stack.
- `int getMin()` retrieves the minimum element in the stack.

You must implement a solution with `O(1)` time complexity for each function.

## Examples

**Example 1:**
```
Input
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

Output
[null,null,null,null,-3,null,0,-2]

Explanation
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2
```

**Constraints:**
- `-2^31 <= val <= 2^31 - 1`
- Methods `pop`, `top` and `getMin` operations will always be called on **non-empty** stacks.
- At most `3 * 10^4` calls will be made to `push`, `pop`, `top`, and `getMin`.

## Solutions

### 1. Optimized Solution (Two Stacks) - `optimized.cpp`
**Time Complexity:** O(1) for all operations  
**Space Complexity:** O(n)

Uses two stacks: one for data storage and another for minimum tracking. The min stack only stores values that have been the minimum at some point.

**Key C++ Concepts Used:**
- `stack<int>` - LIFO data structure for efficient push/pop operations
- Two-stack approach - auxiliary data structure for O(1) minimum retrieval
- Invariant maintenance - min stack top is always current minimum

### 2. Alternative Solution (Single Stack with Pairs)
**Time Complexity:** O(1) for all operations  
**Space Complexity:** O(n)

Uses a single stack storing pairs of (value, current_minimum).

```cpp
class MinStack {
private:
    stack<pair<int, int>> st;  // Stack of (value, min_so_far) pairs

public:
    void push(int val) {
        if (st.empty()) {
            st.push({val, val});
        } else {
            st.push({val, min(val, st.top().second)});
        }
    }
    
    void pop() {
        st.pop();
    }
    
    int top() {
        return st.top().first;
    }
    
    int getMin() {
        return st.top().second;
    }
};
```

## Key DSA Concepts

### Stack Data Structure
- **LIFO (Last In, First Out)** principle
- Perfect for tracking minimum values efficiently
- Operations: `push()`, `pop()`, `top()`, `empty()`

### Auxiliary Data Structure Pattern
- **Problem**: Need to maintain additional information (minimum) alongside main data
- **Solution**: Use auxiliary data structure (min stack) to track the additional information
- **Benefit**: Achieves O(1) time complexity for the additional operation

### Invariant Maintenance
- **Invariant**: Min stack top is always the current minimum
- **Maintenance**: Carefully update min stack only when necessary
- **Benefit**: Ensures correctness while maintaining efficiency

## Common Pitfalls

1. **Forgetting to check if min stack is empty** before accessing top element
2. **Incorrect minimum tracking logic** - ensure proper comparison with `<=`
3. **Not handling duplicate minimums** - multiple elements can have the same minimum value
4. **Memory management issues** - ensure proper stack operations

## Related Problems

- [716. Max Stack](https://leetcode.com/problems/max-stack/)
- [232. Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/)
- [225. Implement Stack using Queues](https://leetcode.com/problems/implement-stack-using-queues/)
- [20. Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)
- [84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)

## Learning Notes

### Why Two Stacks Work
- **Data stack**: Maintains the normal stack behavior
- **Min stack**: Tracks minimum values efficiently
- **Space optimization**: Min stack only stores values that have been minimum

### Optimization Techniques
- **Auxiliary data structure**: Use additional structure for O(1) operations
- **Invariant maintenance**: Keep data structures in consistent states
- **Single pass operations**: Each operation processes data exactly once

### Edge Cases to Consider
- Empty stack (handled by constraints)
- Duplicate minimum values
- Integer overflow (values can be as large as 2^31 - 1)
- Memory management with STL containers
