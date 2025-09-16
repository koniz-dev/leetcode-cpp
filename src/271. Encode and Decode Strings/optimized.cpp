#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Solution {
public:
    /*
     * 271. Encode and Decode Strings - Optimized Solution using String Manipulation
     * 
     * Approach:
     * - Use length-prefix encoding: "length#string" format
     * - Encode: For each string, prepend its length followed by '#' delimiter
     * - Decode: Parse length, then extract exactly that many characters
     * - Handle edge cases: empty strings, special characters, numbers in strings
     * 
     * Time Complexity: O(n) - Single pass through all characters in all strings
     * Space Complexity: O(1) - Only using input/output space, no extra data structures
     */
    
    // Encode a list of strings to a single string
    string encode(vector<string>& strs) {
        string result;
        
        for (const auto& str : strs) {
            // Format: "length#string" - length tells us exactly how many chars to read
            result += to_string(str.length()) + "#" + str;
        }
        
        return result;
    }
    
    // Decode a single string to a list of strings
    vector<string> decode(string s) {
        vector<string> result;
        size_t i = 0;
        
        while (i < s.length()) {
            // Find the delimiter '#' to separate length from content
            size_t delimiterPos = s.find('#', i);
            
            // Extract length: substring from i to delimiter
            int length = stoi(s.substr(i, delimiterPos - i));
            
            // Extract string: substring after '#' with exact length
            string word = s.substr(delimiterPos + 1, length);
            result.push_back(move(word)); // Use move semantics for efficiency
            
            // Move to next encoded string
            i = delimiterPos + 1 + length;
        }
        
        return result;
    }

};
