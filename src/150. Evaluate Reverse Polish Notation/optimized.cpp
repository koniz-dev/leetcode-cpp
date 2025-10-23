#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include <functional>
using namespace std;

class Solution {
public:
    /*
     * Evaluate Reverse Polish Notation - Optimized Solution using Stack
     * 
     * Approach:
     * - Use a stack to store operands
     * - When encountering an operator, pop two operands and apply the operation
     * - Push the result back onto the stack
     * - Use a hash map for operator-to-function mapping for cleaner code
     * - Handle integer division with proper truncation toward zero
     * 
     * Time Complexity: O(n) - Process each token exactly once
     * Space Complexity: O(n) - Stack can hold at most n/2 + 1 elements in worst case
     */
    int evalRPN(vector<string>& tokens) {
        stack<int> operandStack; // Stack to store operands for RPN evaluation
        
        // Map operators to their corresponding functions for cleaner code
        unordered_map<string, function<int(int, int)>> operations = {
            {"+", [](int a, int b) { return a + b; }},
            {"-", [](int a, int b) { return a - b; }},
            {"*", [](int a, int b) { return a * b; }},
            {"/", [](int a, int b) { return a / b; }}
        };
        
        for (const string& token : tokens) {
            // Check if token is an operator
            if (operations.find(token) != operations.end()) {
                // Pop two operands (order matters: second operand is popped first)
                int secondOperand = operandStack.top();
                operandStack.pop();
                int firstOperand = operandStack.top();
                operandStack.pop();
                
                // Apply the operation and push result back
                int result = operations[token](firstOperand, secondOperand);
                operandStack.push(result);
            } else {
                // Token is a number, convert and push to stack
                operandStack.push(stoi(token));
            }
        }
        
        // The final result is the only element left in the stack
        return operandStack.top();
    }
};
