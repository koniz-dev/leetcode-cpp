#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    /*
     * Top K Frequent Elements - Optimized Solution using Heap (Priority Queue)
     * 
     * Approach:
     * - Count frequency of each element using unordered_map
     * - Use min-heap to maintain top K frequent elements efficiently
     * - For each element, add to heap and remove smallest if heap size > k
     * - Extract elements from heap to get final result
     * 
     * Time Complexity: O(n log k) - n elements processed, heap operations are O(log k)
     * Space Complexity: O(n + k) - frequency map O(n) + heap O(k)
     */
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // Step 1: Count frequency of each element
        unordered_map<int, int> freq;
        for (const int& num : nums) {
            freq[num]++;
        }
        
        // Step 2: Use min-heap to maintain top K frequent elements
        // Custom comparator: compare by frequency (second element of pair)
        auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second > b.second;  // Min-heap: smaller frequency on top
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> minHeap(cmp);
        
        // Step 3: Process each unique element
        for (const auto& [num, count] : freq) {
            minHeap.push({num, count});
            
            // Keep only top K elements in heap
            if (minHeap.size() > k) {
                minHeap.pop();  // Remove element with smallest frequency
            }
        }
        
        // Step 4: Extract elements from heap (in reverse order)
        vector<int> result;
        result.reserve(k);
        
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().first);
            minHeap.pop();
        }
        
        // Step 5: Reverse to get elements in descending order of frequency
        reverse(result.begin(), result.end());
        
        return result;
    }
};
