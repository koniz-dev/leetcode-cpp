#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    /*
     * Container With Most Water - Optimized Solution using Two Pointers Technique
     * 
     * Approach:
     * - Use two pointers starting from both ends of the array
     * - Calculate area using the shorter height and current width
     * - Move the pointer with the shorter height inward
     * - Keep track of maximum area found so far
     * - Continue until pointers meet
     * 
     * Time Complexity: O(n) - Single pass through the array
     * Space Complexity: O(1) - Only using constant extra space
     */
    int maxArea(vector<int>& height) {
        int maxArea = 0;                    // Track maximum area found
        int left = 0;                       // Left pointer starting from beginning
        int right = height.size() - 1;      // Right pointer starting from end
        
        // Two pointers approach - move inward until they meet
        while (left < right) {
            int width = right - left;                           // Current width between pointers
            int minHeight = min(height[left], height[right]);   // Container height limited by shorter side
            int currentArea = width * minHeight;                // Calculate current area
            
            maxArea = max(maxArea, currentArea);                // Update maximum area
            
            // Move the pointer with shorter height inward
            // This is optimal because moving the taller pointer can only decrease area
            if (height[left] < height[right]) {
                left++;     // Move left pointer right
            } else {
                right--;    // Move right pointer left
            }
        }
        
        return maxArea;     // Return maximum area found
    }
};
