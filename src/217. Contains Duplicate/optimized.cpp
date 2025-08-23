#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    /*
     * Contains Duplicate - Optimized Solution using Hash Set
     * 
     * Approach:
     * - Use an unordered_set to track seen numbers
     * - For each number, check if it already exists in the set
     * - If found, return true (duplicate exists)
     * - If not found, add the number to the set and continue
     * - If loop completes without finding duplicates, return false
     * 
     * Time Complexity: O(n) - single pass through the array
     * Space Complexity: O(n) - hash set can store up to n elements
     */
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen; // Track seen numbers
        
        for (int num : nums) {
            // Check if current number already exists in the set
            if (seen.find(num) != seen.end()) {
                return true;  // Duplicate found
            }
            
            // Add current number to the set
            seen.insert(num);
        }
        
        return false;  // No duplicates found
    }
};
