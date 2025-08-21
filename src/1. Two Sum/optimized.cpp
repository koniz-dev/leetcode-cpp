#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    /*
     * Two Sum - Optimized Solution using Hash Map
     * 
     * Approach:
     * - Use an unordered_map to store each number and its index
     * - For each number, check if (target - current_number) exists in the map
     * - If found, return the current index and the stored index
     * - If not found, add current number and its index to the map
     * 
     * Time Complexity: O(n) - single pass through the array
     * Space Complexity: O(n) - hash map can store up to n elements
     */
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> numMap; // value -> index mapping
        
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            
            // Check if complement exists in the map
            if (numMap.find(complement) != numMap.end()) {
                return {numMap[complement], i};
            }
            
            // Add current number and its index to the map
            numMap[nums[i]] = i;
        }
        
        // No solution found (though problem guarantees a solution exists)
        return {};
    }
};
