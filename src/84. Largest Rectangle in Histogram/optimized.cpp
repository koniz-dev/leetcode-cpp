#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:
    /*
     * Largest Rectangle in Histogram - Optimized Solution using Monotonic Stack
     * 
     * Approach:
     * - Use a monotonic stack to track indices of bars in increasing height order
     * - For each bar, calculate the largest rectangle that can be formed ending at that bar
     * - When we encounter a bar shorter than the top of the stack, we know rectangles
     *   extending from previous bars can no longer continue, so we calculate their areas
     * - Store pairs of (start_index, height) in the stack to track where each rectangle starts
     * - After processing all bars, calculate areas for remaining bars in the stack
     * 
     * Key Insight:
     * - A rectangle can only extend as far as the next shorter bar
     * - We can calculate the maximum area for each bar when we find a shorter bar
     * - The start index tracks where the rectangle of a given height can begin
     * 
     * Time Complexity: O(n) - Each bar is pushed and popped at most once
     * Space Complexity: O(n) - Stack can contain at most n elements
     */
    int largestRectangleArea(vector<int>& heights) {
        stack<pair<int, int>> st;  // Stack of (start_index, height) pairs
        int largestArea = 0;        // Track the maximum rectangle area found
        
        // Process each bar in the histogram
        for (int i = 0; i < heights.size(); i++) {
            int start = i;  // Default start index for current bar's rectangle
            
            // While current bar is shorter than the top of the stack,
            // we can no longer extend rectangles from taller bars
            while (!st.empty() && st.top().second > heights[i]) {
                auto [index, height] = st.top();  // Get the top bar's info
                st.pop();  // Remove it from stack as it can't extend further
                
                // Calculate area: height * width (from start_index to current position)
                largestArea = max(largestArea, height * (i - index));
                
                // Update start index: rectangles can extend backward to this index
                start = index;
            }
            
            // Push current bar with its start index
            // If we popped any bars, start will be the leftmost index where
            // this height can form a rectangle
            st.push({start, heights[i]});
        }
        
        // Process remaining bars in the stack
        // These bars can extend all the way to the end of the histogram
        int n = heights.size();
        while (!st.empty()) {
            auto [index, height] = st.top();
            st.pop();
            
            // Calculate area: height * width (from start_index to end of histogram)
            largestArea = max(largestArea, height * (n - index));
        }
        
        return largestArea;  // Return the maximum rectangle area found
    }
};

