#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    /*
     * Generate Parentheses - Optimized Solution using Backtracking
     * 
     * Approach:
     * - Use recursive backtracking to generate all valid combinations
     * - Track open and close parentheses counts to ensure validity
     * - Only add ')' when we have more '(' than ')' to maintain balance
     * - Base case: when we've used all n pairs, add to results
     * 
     * Time Complexity: O(4^n / sqrt(n)) - Catalan number, each valid sequence has 2n characters
     * Space Complexity: O(n) - Recursion depth and string building
     */
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        string current;
        backtrack(result, current, 0, 0, n);
        return result;
    }
    
private:
    /*
     * Backtracking helper function
     * 
     * @param result: Reference to store valid combinations
     * @param current: Current string being built
     * @param open: Count of opening parentheses used
     * @param close: Count of closing parentheses used  
     * @param n: Total number of pairs needed
     */
    void backtrack(vector<string>& result, string& current, int open, int close, int n) {
        // Base case: we've used all n pairs, add to results
        if (current.length() == 2 * n) {
            result.push_back(current);
            return;
        }
        
        // Add opening parenthesis if we haven't used all n
        if (open < n) {
            current.push_back('(');
            backtrack(result, current, open + 1, close, n);
            current.pop_back();  // Backtrack: remove the '(' we just added
        }
        
        // Add closing parenthesis if we have more '(' than ')'
        // This ensures we only generate valid combinations
        if (close < open) {
            current.push_back(')');
            backtrack(result, current, open, close + 1, n);
            current.pop_back();  // Backtrack: remove the ')' we just added
        }
    }
};
