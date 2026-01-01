#include <vector>
using namespace std;

class Solution {
public:
    /*
     * Search in Rotated Sorted Array - Optimized Solution using Binary Search
     * 
     * Approach:
     * - The array is rotated, meaning it has two sorted halves.
     * - Use Binary Search to find the target.
     * - In each step, determine which half is sorted:
     *   - If nums[left] <= nums[mid], the left half is sorted.
     *   - Otherwise, the right half is sorted.
     * - Once the sorted half is identified, check if the target lies within that range.
     * - Eliminate the half where the target definitely does not exist.
     * 
     * Time Complexity: O(log n) - Binary search cuts search space in half each time
     * Space Complexity: O(1) - Constant extra space
     */
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                return mid;
            }

            // Check if the left half is sorted
            if (nums[left] <= nums[mid]) {
                // Target is in the sorted left half
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    // Target is in the right half
                    left = mid + 1;
                }
            } 
            // Otherwise, the right half is sorted
            else {
                // Target is in the sorted right half
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    // Target is in the left half
                    right = mid - 1;
                }
            }
        }

        return -1;
    }
};
