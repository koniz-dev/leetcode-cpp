#include <stack>
using namespace std;

class MinStack {
private:
    stack<int> dataStack;    // Main stack to store all values
    stack<int> minStack;     // Auxiliary stack to track minimum values
    
public:
    /*
     * Min Stack - Optimized Solution using Two Stacks
     * 
     * Approach:
     * - Use two stacks: one for data, one for minimum tracking
     * - Data stack stores all pushed values in LIFO order
     * - Min stack stores minimum values, with current minimum always at top
     * - When pushing: add to data stack, add to min stack only if new minimum
     * - When popping: remove from data stack, remove from min stack if it was minimum
     * - All operations maintain O(1) time complexity
     * 
     * Time Complexity: O(1) for all operations - constant time stack operations
     * Space Complexity: O(n) - worst case when all elements are in decreasing order
     */
    
    MinStack() {
        // Constructor - stacks are automatically initialized as empty
    }
    
    void push(int val) {
        dataStack.push(val);  // Push value to main data stack
        
        // Push to min stack only if it's empty or val is <= current minimum
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
        }
    }
    
    void pop() {
        int topValue = dataStack.top();  // Get the value being removed
        dataStack.pop();  // Remove from data stack
        
        // If the removed element was the current minimum, remove it from min stack
        if (topValue == minStack.top()) {
            minStack.pop();
        }
    }
    
    int top() {
        return dataStack.top();  // Return most recently pushed element
    }
    
    int getMin() {
        return minStack.top();  // Return current minimum value
    }
};
