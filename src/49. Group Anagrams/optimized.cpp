#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    /*
     * 49. Group Anagrams - Optimized Solution using Hash Map with Sorted Keys
     * 
     * Approach:
     * - Use unordered_map to group anagrams by their sorted character representation
     * - Sort each string to create a unique key for anagrams
     * - Group all strings with the same sorted key together
     * - Use move semantics for efficient vector operations
     * 
     * Time Complexity: O(N * M log M) - N strings, each of length M needs sorting
     * Space Complexity: O(N * M) - Store all strings in the map
     */
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> anagramGroups; // Maps sorted string to list of anagrams
        
        // Group strings by their sorted character representation
        for (const string& str : strs) {
            string key = str;           // Create copy for sorting
            sort(key.begin(), key.end()); // Sort characters to create unique key
            anagramGroups[key].push_back(str); // Add original string to group
        }
        
        // Convert map values to result vector efficiently
        vector<vector<string>> result;
        result.reserve(anagramGroups.size()); // Pre-allocate for efficiency
        
        for (auto& [key, group] : anagramGroups) {
            result.push_back(move(group)); // Use move semantics for efficiency
        }
        
        return result;
    }
};
