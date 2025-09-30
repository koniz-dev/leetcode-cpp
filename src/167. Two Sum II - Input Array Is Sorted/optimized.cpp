#include <vector>
using namespace std;

class Solution {
public:
    /*
     * Two Sum II - Input Array Is Sorted - Optimized Solution using Two Pointers
     * 
     * Approach:
     * - Use two pointers starting from the beginning and end of the sorted array
     * - Calculate the sum of elements at both pointers
     * - If sum equals target, return the 1-indexed positions
     * - If sum is less than target, move left pointer right to increase sum
     * - If sum is greater than target, move right pointer left to decrease sum
     * - Continue until pointers meet or solution is found
     * 
     * Time Complexity: O(n) - Each element is visited at most once
     * Space Complexity: O(1) - Only using constant extra space for pointers
     */
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0;                    // Left pointer starting from beginning
        int right = numbers.size() - 1;  // Right pointer starting from end
        
        // Two pointer technique: move pointers based on sum comparison
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            
            if (sum == target) {
                // Found the solution, return 1-indexed positions
                return {left + 1, right + 1};
            } else if (sum < target) {
                // Sum is too small, move left pointer right to increase sum
                left++;
            } else {
                // Sum is too large, move right pointer left to decrease sum
                right--;
            }
        }
        
        // No solution found (shouldn't happen according to problem constraints)
        return {};
    }
};
