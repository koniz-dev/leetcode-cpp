class Solution {
    public:
        string encode(vector<string>& strs) {
            string result;
            for (auto &str : strs) {
                result += to_string(str.size()) + "#" + str;
            }
            return result;
        }
    
        vector<string> decode(string s) {
            vector<string> strs;
            int i = 0;
    
            while (i < (int)s.size()) {
                int j = i;
                while (s[j] != '#') j++;
    
                int length = stoi(s.substr(i, j - i));
                string word = s.substr(j + 1, length);
    
                strs.push_back(word);
                i = j + 1 + length;
            }
    
            return strs;
        }
    };
    