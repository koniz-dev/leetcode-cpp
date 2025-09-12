#include <vector>
#include <string>
#include <unordered_map>
#include <array>
using namespace std;

class Solution {
public:
    /*
     * 49. Group Anagrams - OPTIMAL Solution using Character Frequency Counting
     * 
     * Approach:
     * - Use character frequency array as key instead of sorting
     * - Count frequency of each character (a-z) for each string
     * - Use frequency pattern as unique key for anagrams
     * - Group strings with identical frequency patterns together
     * - Use modern C++ features for optimal performance
     * 
     * Time Complexity: O(N * M) - N strings, each of length M, only count frequencies
     * Space Complexity: O(N * M) - Store all strings in the map
     */
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> anagramGroups; // Maps frequency pattern to anagram groups
        
        // Group strings by their character frequency pattern
        for (const string& str : strs) {
            // Count character frequencies using fixed-size array (more efficient than map)
            array<int, 26> freq = {}; // Initialize all to 0
            for (char c : str) {
                freq[c - 'a']++; // Count frequency of each character
            }
            
            // Create frequency pattern string as key
            string key;
            key.reserve(52); // Pre-allocate: 26 chars * 2 digits max
            for (int count : freq) {
                key += to_string(count) + '#'; // Use # as separator
            }
            
            anagramGroups[key].push_back(str); // Add to group
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
