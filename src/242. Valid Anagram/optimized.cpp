#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    /*
     * Valid Anagram - Optimized Solution using Character Frequency Counting
     * 
     * Approach:
     * - Use a fixed-size array (vector<int>) to count character frequencies
     * - First, check if strings have the same length (anagrams must have equal length)
     * - Count frequency of each character in string s
     * - Decrement frequency for each character in string t
     * - If any frequency becomes negative, strings are not anagrams
     * - If all frequencies are zero at the end, strings are anagrams
     * 
     * Time Complexity: O(n) - single pass through both strings
     * Space Complexity: O(1) - fixed size array (26 for lowercase letters)
     */
    bool isAnagram(string s, string t) {
        // Early exit: anagrams must have the same length
        if (s.length() != t.length()) {
            return false;
        }
        
        // Character frequency counter (assuming lowercase letters a-z)
        vector<int> charCount(26, 0);
        
        // Count characters in string s
        for (char c : s) {
            charCount[c - 'a']++;
        }
        
        // Decrement counts for characters in string t
        for (char c : t) {
            charCount[c - 'a']--;
            
            // If any character count becomes negative, t has more of that character
            if (charCount[c - 'a'] < 0) {
                return false;
            }
        }
        
        // All character frequencies should be zero for anagrams
        return true;
    }
};
