#include <stack>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    /*
     * Valid Parentheses - Optimized Solution using Stack with Hash Map
     * 
     * Approach:
     * - Use a stack to track opening brackets
     * - Use a hash map for O(1) bracket matching lookup
     * - For opening brackets: push to stack
     * - For closing brackets: check if stack is empty or top doesn't match
     * - Return true only if stack is empty after processing all characters
     * 
     * Time Complexity: O(n) - Single pass through the string
     * Space Complexity: O(n) - Stack can hold up to n/2 opening brackets in worst case
     */
    bool isValid(string s) {
        stack<char> st; // Stack to store opening brackets
        
        // Hash map for O(1) bracket matching lookup
        unordered_map<char, char> bracketMap = {
            {')', '('},
            {']', '['},
            {'}', '{'}
        };
        
        for (char c : s) {
            // If it's an opening bracket, push to stack
            if (c == '(' || c == '[' || c == '{') {
                st.push(c);
            } else {
                // If it's a closing bracket
                if (st.empty() || st.top() != bracketMap[c]) {
                    return false; // No matching opening bracket or mismatch
                }
                st.pop(); // Remove the matched opening bracket
            }
        }
        
        return st.empty(); // Valid if all brackets are matched
    }
};
