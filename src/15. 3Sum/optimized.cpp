#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    /*
     * 3Sum - Optimized Solution using Two Pointers Technique
     * 
     * Approach:
     * - Sort the array to enable two-pointer technique and duplicate skipping
     * - Fix one element (nums[i]) and use two pointers for remaining elements
     * - Use left pointer from i+1 and right pointer from end
     * - Skip duplicates at all three positions to avoid duplicate triplets
     * - Early termination when nums[i] > 0 since array is sorted
     * 
     * Time Complexity: O(n²) - Outer loop O(n), inner two-pointer scan O(n)
     * Space Complexity: O(1) - Only using constant extra space (excluding output)
     */
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        const int n = nums.size();
        
        // Sort array to enable two-pointer technique and duplicate detection
        sort(nums.begin(), nums.end());
        
        // Fix first element and find pairs that sum to -nums[i]
        for (int i = 0; i < n - 2; ++i) {
            // Early termination: if first element > 0, no valid triplet possible
            if (nums[i] > 0) break;
            
            // Skip duplicates for first element
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            
            // Two-pointer technique for remaining elements
            int left = i + 1;
            int right = n - 1;
            
            while (left < right) {
                const int sum = nums[i] + nums[left] + nums[right];
                
                if (sum == 0) {
                    // Found valid triplet
                    result.emplace_back(vector<int>{nums[i], nums[left], nums[right]});
                    
                    // Skip duplicates for second element
                    while (left < right && nums[left] == nums[left + 1]) {
                        ++left;
                    }
                    
                    // Skip duplicates for third element
                    while (left < right && nums[right] == nums[right - 1]) {
                        --right;
                    }
                    
                    // Move both pointers
                    ++left;
                    --right;
                } else if (sum < 0) {
                    // Sum too small, move left pointer to increase sum
                    ++left;
                } else {
                    // Sum too large, move right pointer to decrease sum
                    --right;
                }
            }
        }
        
        return result;
    }
};
