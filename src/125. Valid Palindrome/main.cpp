class Solution {
    public:
        bool isPalindrome(string s) {
            string cleaned;
            for (unsigned char c: s) {
                if (isalnum(c)) {
                    c = tolower(c);
                    cleaned+= c;
                }
            }
    
            int left = 0;
            int right = cleaned.size() - 1;
            while (left <= right) {
                if (cleaned[left] != cleaned[right]) return false;
    
                left++;
                right--;
            }
    
            return true;
        }
    };