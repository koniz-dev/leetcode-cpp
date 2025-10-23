# Stack Pattern

## Overview
The stack pattern is one of the most fundamental and widely used patterns in computer science. It follows the Last In, First Out (LIFO) principle, making it perfect for problems involving nested structures, expression evaluation, and backtracking.

## When to Use Stack Pattern

### 1. Expression Evaluation
- **Reverse Polish Notation (RPN)** evaluation
- **Infix to Postfix** conversion
- **Parentheses matching** and validation
- **Calculator** implementations

### 2. Nested Structure Processing
- **Parentheses matching** (valid parentheses, nested brackets)
- **HTML/XML tag matching**
- **Function call tracking**
- **Nested object processing**

### 3. Backtracking and Undo Operations
- **Browser history** (back button functionality)
- **Text editor undo/redo**
- **Game state management**
- **Recursive algorithm simulation**

### 4. Monotonic Stack Problems
- **Next greater element** problems
- **Largest rectangle in histogram**
- **Stock span** problems
- **Temperature** problems

## Core Stack Operations

```cpp
#include <stack>
#include <iostream>
using namespace std;

void demonstrateStackOperations() {
    stack<int> st;
    
    // Push elements
    st.push(1);
    st.push(2);
    st.push(3);
    
    // Check if empty
    cout << "Is empty: " << st.empty() << endl;  // 0 (false)
    
    // Get size
    cout << "Size: " << st.size() << endl;       // 3
    
    // Access top element
    cout << "Top element: " << st.top() << endl; // 3
    
    // Pop element
    st.pop();
    cout << "After pop, top: " << st.top() << endl; // 2
    
    // Pop all elements
    while (!st.empty()) {
        cout << "Popping: " << st.top() << endl;
        st.pop();
    }
}
```

## Pattern 1: Expression Evaluation

### Reverse Polish Notation (RPN)
```cpp
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        
        for (const string& token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                int b = st.top(); st.pop();
                int a = st.top(); st.pop();
                
                if (token == "+") st.push(a + b);
                else if (token == "-") st.push(a - b);
                else if (token == "*") st.push(a * b);
                else if (token == "/") st.push(a / b);
            } else {
                st.push(stoi(token));
            }
        }
        
        return st.top();
    }
};
```

### Key Insights for RPN
- **Operand order matters**: Second popped operand is the right operand
- **Stack naturally handles** the LIFO nature of operations
- **Division truncates** toward zero as required

## Pattern 2: Parentheses Matching

### Valid Parentheses
```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') {
                st.push(c);
            } else {
                if (st.empty()) return false;
                
                char top = st.top();
                st.pop();
                
                if ((c == ')' && top != '(') ||
                    (c == ']' && top != '[') ||
                    (c == '}' && top != '{')) {
                    return false;
                }
            }
        }
        
        return st.empty();
    }
};
```

### Key Insights for Parentheses
- **Opening brackets** go on stack
- **Closing brackets** must match the most recent opening bracket
- **Stack empty check** is crucial for valid sequences

## Pattern 3: Monotonic Stack

### Next Greater Element
```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, -1);
        stack<int> st; // Store indices
        
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[st.top()] < nums[i]) {
                result[st.top()] = nums[i];
                st.pop();
            }
            st.push(i);
        }
        
        return result;
    }
};
```

### Key Insights for Monotonic Stack
- **Maintain decreasing order** in stack
- **Process elements** that are smaller than current
- **Store indices** for result mapping

## Pattern 4: Nested Structure Processing

### Simplify Path
```cpp
class Solution {
public:
    string simplifyPath(string path) {
        stack<string> st;
        stringstream ss(path);
        string token;
        
        while (getline(ss, token, '/')) {
            if (token == "" || token == ".") continue;
            if (token == "..") {
                if (!st.empty()) st.pop();
            } else {
                st.push(token);
            }
        }
        
        if (st.empty()) return "/";
        
        string result = "";
        while (!st.empty()) {
            result = "/" + st.top() + result;
            st.pop();
        }
        
        return result;
    }
};
```

## Common Stack Patterns

### 1. Two-Stack Approach
```cpp
// Min Stack implementation
class MinStack {
private:
    stack<int> data;
    stack<int> minStack;
    
public:
    void push(int val) {
        data.push(val);
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
        }
    }
    
    void pop() {
        if (data.top() == minStack.top()) {
            minStack.pop();
        }
        data.pop();
    }
    
    int top() { return data.top(); }
    int getMin() { return minStack.top(); }
};
```

### 2. Stack with Additional Data
```cpp
// Stack with getMax() in O(1)
class MaxStack {
private:
    stack<int> data;
    stack<int> maxStack;
    
public:
    void push(int val) {
        data.push(val);
        if (maxStack.empty() || val >= maxStack.top()) {
            maxStack.push(val);
        }
    }
    
    void pop() {
        if (data.top() == maxStack.top()) {
            maxStack.pop();
        }
        data.pop();
    }
    
    int top() { return data.top(); }
    int getMax() { return maxStack.top(); }
};
```

## Advanced Stack Applications

### 1. Largest Rectangle in Histogram
```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        int maxArea = 0;
        int n = heights.size();
        
        for (int i = 0; i <= n; i++) {
            int h = (i == n) ? 0 : heights[i];
            
            while (!st.empty() && heights[st.top()] > h) {
                int height = heights[st.top()];
                st.pop();
                int width = st.empty() ? i : i - st.top() - 1;
                maxArea = max(maxArea, height * width);
            }
            st.push(i);
        }
        
        return maxArea;
    }
};
```

### 2. Trapping Rain Water
```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        stack<int> st;
        int water = 0;
        
        for (int i = 0; i < height.size(); i++) {
            while (!st.empty() && height[st.top()] < height[i]) {
                int top = st.top();
                st.pop();
                
                if (st.empty()) break;
                
                int distance = i - st.top() - 1;
                int boundedHeight = min(height[i], height[st.top()]) - height[top];
                water += distance * boundedHeight;
            }
            st.push(i);
        }
        
        return water;
    }
};
```

## Stack vs Other Data Structures

| Problem Type | Best Data Structure | Reason |
|--------------|-------------------|---------|
| Expression Evaluation | Stack | Natural LIFO for operations |
| Parentheses Matching | Stack | Nested structure processing |
| Next Greater Element | Monotonic Stack | Maintain order efficiently |
| BFS Traversal | Queue | FIFO for level-order |
| DFS Traversal | Stack/Recursion | LIFO for depth-first |

## Common Pitfalls

### 1. Stack Underflow
```cpp
// Always check if stack is empty before popping
if (!st.empty()) {
    int top = st.top();
    st.pop();
}
```

### 2. Wrong Operand Order
```cpp
// In RPN: second popped is right operand
int b = st.top(); st.pop();  // Right operand
int a = st.top(); st.pop();  // Left operand
int result = a + b;          // Correct order
```

### 3. Forgetting to Handle Edge Cases
```cpp
// Check for empty stack in final result
return st.empty() ? 0 : st.top();
```

## Practice Problems

### Easy
- [20. Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)
- [155. Min Stack](https://leetcode.com/problems/min-stack/)
- [225. Implement Stack using Queues](https://leetcode.com/problems/implement-stack-using-queues/)

### Medium
- [150. Evaluate Reverse Polish Notation](https://leetcode.com/problems/evaluate-reverse-polish-notation/)
- [71. Simplify Path](https://leetcode.com/problems/simplify-path/)
- [739. Daily Temperatures](https://leetcode.com/problems/daily-temperatures/)

### Hard
- [84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)
- [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)
- [85. Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/)

## Key Takeaways

1. **Stack is perfect for nested structures** and expression evaluation
2. **LIFO principle** naturally handles many algorithmic problems
3. **Monotonic stacks** are powerful for range queries
4. **Always check for empty stack** before operations
5. **Operand order matters** in expression evaluation
6. **Stack can simulate recursion** for iterative solutions

## Related Patterns
- [Queue Pattern](queue.md) - FIFO operations
- [Two Pointers](two-pointers.md) - Alternative to stack for some problems
- [Sliding Window](sliding-window.md) - Often combined with stack
- [Tree Traversal](tree-traversal.md) - Stack-based iterative DFS
