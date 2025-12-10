#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    /*
     * Koko Eating Bananas - Optimized Solution using Binary Search
     * 
     * Approach:
     * - Use binary search on the answer space (eating speed from 1 to max(piles))
     * - For each candidate speed, calculate total hours needed to eat all piles
     * - If hours needed <= h, this speed is valid (try slower speed)
     * - If hours needed > h, this speed is too slow (try faster speed)
     * - Find the minimum valid speed using binary search
     * 
     * Key Insight:
     * - This is a "binary search on answer" problem
     * - We're searching for the minimum speed that satisfies the constraint
     * - The answer space is monotonic: if speed k works, all speeds > k also work
     * 
     * Time Complexity: O(n * log(max(piles))) 
     *   - Binary search: O(log(max(piles)))
     *   - For each candidate: O(n) to calculate hours needed
     * 
     * Space Complexity: O(1) - Only using constant extra space
     */
    int minEatingSpeed(vector<int>& piles, int h) {
        // Find the maximum pile size to set upper bound for binary search
        // This is the worst-case speed needed (eating one pile per hour)
        int maxPile = *max_element(piles.begin(), piles.end());
        
        // Binary search on the answer space [1, maxPile]
        int left = 1;           // Minimum possible speed
        int right = maxPile;    // Maximum possible speed (one pile per hour)
        
        while (left <= right) {
            // Candidate eating speed to test
            int mid = left + (right - left) / 2;
            
            // Calculate total hours needed with this speed
            long long hoursNeeded = 0;
            for (int pile : piles) {
                // Ceiling division: (pile + mid - 1) / mid
                // Equivalent to: ceil(pile / mid)
                // Example: pile=10, mid=3 -> (10+3-1)/3 = 12/3 = 4 hours
                hoursNeeded += (pile + mid - 1) / mid;
            }
            
            // If this speed allows finishing within h hours
            if (hoursNeeded <= h) {
                // This speed is valid, try slower speed (search left)
                // We want the minimum valid speed
                right = mid - 1;
            } else {
                // This speed is too slow, need faster speed (search right)
                left = mid + 1;
            }
        }
        
        // After binary search, left points to the minimum valid speed
        // When loop ends: right < left, and left is the first valid speed
        return left;
    }
};

