#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    /*
     * 49. Group Anagrams - OPTIMAL Solution using Character Frequency Counting
     * 
     * Approach:
     * - Use character frequency counting as key instead of sorting
     * - Count frequency of each character (a-z) for each string
     * - Use frequency pattern as unique key for anagrams
     * - Group strings with identical frequency patterns together
     * 
     * Time Complexity: O(N * M) - N strings, each of length M, only count frequencies
     * Space Complexity: O(N * M) - Store all strings in the map
     */
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        
        for (const string& str : strs) {
            // Count character frequencies
            vector<int> count(26, 0);
            for (char c : str) {
                count[c - 'a']++;
            }
            
            // Create frequency pattern string as key
            string key;
            for (int i = 0; i < 26; i++) {
                key += to_string(count[i]) + '#';
            }
            
            groups[key].push_back(str);
        }
        
        // Convert map values to result vector
        vector<vector<string>> result;
        for (auto& [key, group] : groups) {
            result.push_back(move(group));
        }
        
        return result;
    }
};
