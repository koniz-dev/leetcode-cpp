#include <string>
#include <cctype>
using namespace std;

class Solution {
public:
    /*
     * Valid Palindrome - Optimized Solution using Two Pointers
     * 
     * Approach:
     * - Use two pointers (left and right) to traverse from both ends
     * - Skip non-alphanumeric characters by advancing pointers
     * - Compare characters in-place without creating additional string
     * - Convert to lowercase for case-insensitive comparison
     * 
     * Time Complexity: O(n) - Single pass through the string
     * Space Complexity: O(1) - Only using constant extra space
     */
    bool isPalindrome(string s) {
        int left = 0;
        int right = s.size() - 1;
        
        while (left < right) {
            // Skip non-alphanumeric characters from left
            while (left < right && !isalnum(s[left])) {
                left++;
            }
            
            // Skip non-alphanumeric characters from right
            while (left < right && !isalnum(s[right])) {
                right--;
            }
            
            // Compare characters (case-insensitive)
            if (tolower(s[left]) != tolower(s[right])) {
                return false;  // Characters don't match, not a palindrome
            }
            
            // Move both pointers towards center
            left++;
            right--;
        }
        
        return true;  // All characters matched, it's a palindrome
    }
};
