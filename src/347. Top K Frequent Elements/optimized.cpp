#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    /*
     * Top K Frequent Elements - Most Optimized Solution using Bucket Sort
     * 
     * Approach:
     * - Count frequency of each element using unordered_map
     * - Create buckets where bucket[i] contains all elements with frequency i
     * - Traverse buckets from highest frequency to lowest
     * - Collect elements until we have k elements
     * 
     * Time Complexity: O(n) - Single pass through array + single pass through buckets
     * Space Complexity: O(n) - frequency map + buckets array
     */
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // Step 1: Count frequency of each element
        unordered_map<int, int> freq;
        for (const int& num : nums) {
            freq[num]++;
        }
        
        // Step 2: Create buckets - bucket[i] contains elements with frequency i
        // Maximum possible frequency is nums.size()
        vector<vector<int>> buckets(nums.size() + 1);
        
        // Step 3: Group elements by their frequency
        for (const auto& [num, count] : freq) {
            buckets[count].push_back(num);
        }
        
        // Step 4: Collect top K frequent elements from buckets
        vector<int> result;
        result.reserve(k);
        
        // Traverse buckets from highest frequency to lowest
        for (int freq = buckets.size() - 1; freq >= 1 && result.size() < k; --freq) {
            // Add all elements in current frequency bucket
            for (const int& num : buckets[freq]) {
                if (result.size() < k) {
                    result.push_back(num);
                } else {
                    break;  // We have enough elements
                }
            }
        }
        
        return result;
    }
};
