# [150. Evaluate Reverse Polish Notation](https://leetcode.com/problems/evaluate-reverse-polish-notation/)

## Problem Statement

You are given an array of strings `tokens` that represents an arithmetic expression in a **Reverse Polish Notation**.

Evaluate the expression. Return an integer that represents the value of the expression.

**Note that:**
- The valid operators are `+`, `-`, `*`, and `/`.
- Each operand may be an integer or another expression.
- Division between two integers should **truncate toward zero**.
- There will not be any division by zero operation.
- The input represents a valid arithmetic expression in a reverse polish notation.
- The answer and all the intermediate calculations can be represented in a **32-bit integer**.

## Examples

**Example 1:**
```
Input: tokens = ["2","1","+","3","*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9
```

**Example 2:**
```
Input: tokens = ["4","13","5","/","+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6
```

**Example 3:**
```
Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
Output: 22
Explanation: ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 22
```

## Approach 1: Stack-Based Evaluation (Implemented in main.cpp and optimized.cpp)

### Algorithm
1. **Initialize a stack** to store operands
2. **Iterate through each token**:
   - If token is an **operator** (`+`, `-`, `*`, `/`):
     - Pop two operands from stack (order matters: second operand first)
     - Apply the operation
     - Push result back to stack
   - If token is a **number**: convert to integer and push to stack
3. **Return the final result** (only element left in stack)

### Key Insights
- **Stack is perfect** for RPN evaluation because it naturally handles the "last in, first out" nature of operations
- **Order of operands matters**: second popped operand is the right operand in the operation
- **Division truncates toward zero** as required by the problem

### Time Complexity: O(n)
- Process each token exactly once
- Stack operations are O(1)

### Space Complexity: O(n)
- Stack can hold at most n/2 + 1 elements in worst case
- In worst case: all numbers followed by all operators

## Approach 2: Recursive Evaluation (Alternative)

### Algorithm
```cpp
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        int index = tokens.size() - 1;
        return evaluate(tokens, index);
    }
    
private:
    int evaluate(vector<string>& tokens, int& index) {
        string token = tokens[index--];
        
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            int right = evaluate(tokens, index);
            int left = evaluate(tokens, index);
            
            if (token == "+") return left + right;
            if (token == "-") return left - right;
            if (token == "*") return left * right;
            if (token == "/") return left / right;
        }
        
        return stoi(token);
    }
};
```

### Time Complexity: O(n)
### Space Complexity: O(n) - recursion stack

## Approach 3: Functional Programming Style (Alternative)

### Algorithm
```cpp
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        
        unordered_map<string, function<int(int, int)>> ops = {
            {"+", plus<int>()},
            {"-", minus<int>()},
            {"*", multiplies<int>()},
            {"/", divides<int>()}
        };
        
        for (const string& token : tokens) {
            if (ops.count(token)) {
                int b = st.top(); st.pop();
                int a = st.top(); st.pop();
                st.push(ops[token](a, b));
            } else {
                st.push(stoi(token));
            }
        }
        
        return st.top();
    }
};
```

## Data Structures and Algorithms Used

### Stack
- **Purpose**: Store operands for RPN evaluation
- **Operations**: Push (add operand), Pop (retrieve operands for operation)
- **Why Stack**: Natural LIFO behavior matches RPN evaluation order

### Hash Map (in optimized solution)
- **Purpose**: Map operators to functions for cleaner code
- **Benefits**: Eliminates repetitive if-else chains, more maintainable

## Key C++ Concepts Demonstrated

### Modern C++ Features
- **Lambda functions**: For operator-to-function mapping
- **Range-based for loops**: Clean iteration over tokens
- **STL containers**: `stack`, `unordered_map`, `vector`
- **Function objects**: `function<int(int, int)>` for type-safe function storage

### String Processing
- **`stoi()`**: String to integer conversion
- **String comparison**: Direct comparison with operator strings

## Common Pitfalls and Edge Cases

1. **Operand Order**: Second popped operand is the right operand
2. **Division Truncation**: C++ integer division already truncates toward zero
3. **Stack Underflow**: Problem guarantees valid RPN, so this won't occur
4. **Integer Overflow**: Problem guarantees 32-bit integer results

## Related Problems

- [224. Basic Calculator](https://leetcode.com/problems/basic-calculator/) - More complex expression evaluation
- [227. Basic Calculator II](https://leetcode.com/problems/basic-calculator-ii/) - Infix expression evaluation
- [71. Simplify Path](https://leetcode.com/problems/simplify-path/) - Another stack-based problem
- [155. Min Stack](https://leetcode.com/problems/min-stack/) - Stack with additional functionality

## Learning Outcomes

- **Stack Applications**: Understanding when and how to use stacks
- **RPN Evaluation**: Classic computer science algorithm
- **Expression Parsing**: Foundation for more complex parsing problems
- **Modern C++**: Using lambdas and function objects for cleaner code
