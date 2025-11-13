#include <vector>
using namespace std;

class Solution {
public:
    /*
     * Binary Search - Optimized Solution using Two Pointers
     * 
     * Approach:
     * - Use two pointers (left and right) to define the search range
     * - Calculate middle index using safe formula: left + (right - left) / 2
     * - Compare middle element with target to determine which half to search
     * - If middle element equals target, return its index
     * - If middle element is less than target, search right half (left = mid + 1)
     * - If middle element is greater than target, search left half (right = mid - 1)
     * - Continue until left > right, indicating target not found
     * 
     * Time Complexity: O(log n) - Each iteration eliminates half of the search space
     * Space Complexity: O(1) - Only using constant extra space for pointers
     */
    int search(vector<int>& nums, int target) {
        int left = 0;                    // Left boundary of search range
        int right = nums.size() - 1;     // Right boundary of search range
        
        // Continue searching while there's a valid range
        while (left <= right) {
            // Calculate middle index using safe formula to prevent overflow
            // Using (left + right) / 2 could overflow for large values
            int mid = left + (right - left) / 2;
            
            // Found the target at middle index
            if (nums[mid] == target) {
                return mid;
            }
            // Target is in the right half (target > nums[mid])
            else if (nums[mid] < target) {
                left = mid + 1;  // Narrow search to right half, exclude mid
            }
            // Target is in the left half (target < nums[mid])
            else {
                right = mid - 1; // Narrow search to left half, exclude mid
            }
        }
        
        // Target not found in the array
        return -1;
    }
};

