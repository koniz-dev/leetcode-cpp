#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    /*
     * Trapping Rain Water - Optimized Solution using Two Pointers Technique
     * 
     * Approach:
     * - Use two pointers (left and right) starting from both ends
     * - Track maximum heights seen from left and right sides
     * - Move the pointer with smaller height towards center
     * - Calculate trapped water based on the smaller of the two max heights
     * - This ensures we always know the water level at current position
     * 
     * Time Complexity: O(n) - Single pass through the array
     * Space Complexity: O(1) - Only using constant extra space
     */
    int trap(vector<int>& height) {
        if (height.empty()) return 0;  // Edge case: empty array
        
        int left = 0;                    // Left pointer starting from beginning
        int right = height.size() - 1;   // Right pointer starting from end
        int maxLeft = 0;                 // Maximum height seen from left side
        int maxRight = 0;                // Maximum height seen from right side
        int trappedWater = 0;            // Total trapped water
        
        // Two pointers approach: move towards center
        while (left < right) {
            // Move the pointer with smaller height
            if (height[left] < height[right]) {
                // Process left side
                if (height[left] >= maxLeft) {
                    maxLeft = height[left];  // Update max height from left
                } else {
                    // Water can be trapped here
                    trappedWater += maxLeft - height[left];
                }
                left++;  // Move left pointer right
            } else {
                // Process right side
                if (height[right] >= maxRight) {
                    maxRight = height[right];  // Update max height from right
                } else {
                    // Water can be trapped here
                    trappedWater += maxRight - height[right];
                }
                right--;  // Move right pointer left
            }
        }
        
        return trappedWater;  // Return total trapped water
    }
};
