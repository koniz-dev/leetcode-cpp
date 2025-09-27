#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
    /*
     * 128. Longest Consecutive Sequence - Optimized Solution using Hash Set
     * 
     * Approach:
     * - Use unordered_set to store all numbers for O(1) lookup
     * - For each number, check if it's the start of a sequence (no num-1 exists)
     * - If it's a start, count consecutive numbers by incrementing and checking existence
     * - Track the maximum sequence length found
     * 
     * Key Insight: Only start counting from the beginning of each sequence
     * to avoid redundant work and achieve O(n) time complexity
     * 
     * Time Complexity: O(n) - Each number is visited at most twice
     * Space Complexity: O(n) - Hash set stores all unique numbers
     */
    int longestConsecutive(vector<int>& nums) {
        // Handle edge case
        if (nums.empty()) return 0;
        
        // Create hash set for O(1) lookup
        unordered_set<int> numSet(nums.begin(), nums.end());
        
        int maxLength = 0;
        
        // Iterate through each unique number
        for (int num : numSet) {
            // Only start counting if this is the beginning of a sequence
            // (i.e., num-1 doesn't exist in the set)
            if (numSet.find(num - 1) == numSet.end()) {
                int currentNum = num;
                int currentLength = 1;
                
                // Count consecutive numbers starting from current number
                while (numSet.find(currentNum + 1) != numSet.end()) {
                    currentNum++;
                    currentLength++;
                }
                
                // Update maximum length found
                maxLength = max(maxLength, currentLength);
            }
        }
        
        return maxLength;
    }
};
