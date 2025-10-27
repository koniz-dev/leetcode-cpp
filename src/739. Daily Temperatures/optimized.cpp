#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    /*
     * Daily Temperatures - Optimized Solution using Monotonic Stack
     * 
     * Approach:
     * - Use a monotonic stack to maintain indices of temperatures in decreasing order
     * - For each temperature, pop all temperatures from stack that are smaller
     * - Calculate the difference in indices to get days until warmer temperature
     * - Push current index onto stack for future comparisons
     * 
     * Time Complexity: O(n) - Each element is pushed and popped at most once
     * Space Complexity: O(n) - Stack can contain up to n elements in worst case
     */
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> result(n, 0);  // Initialize with 0s (no warmer day found)
        stack<int> st;  // Stack to store indices of temperatures
        
        for (int i = 0; i < n; i++) {
            // Process all temperatures in stack that are smaller than current temperature
            while (!st.empty() && temperatures[st.top()] < temperatures[i]) {
                int prevIndex = st.top();  // Get the index of the smaller temperature
                st.pop();  // Remove it from stack as we found a warmer day
                result[prevIndex] = i - prevIndex;  // Calculate days until warmer temperature
            }
            
            // Push current index onto stack for future comparisons
            st.push(i);
        }
        
        return result;  // Return the result array with days until warmer temperature
    }
};
