class Solution {
    public:
        vector<vector<string>> groupAnagrams(vector<string>& strs) {
            unordered_map<string, vector<string>> mp;
            for (const string &s : strs) {
                string key = s;
                sort(key.begin(), key.end());
                mp[key].push_back(s);
            }
    
            vector<vector<string>> res;
            res.reserve(mp.size());
            for (auto &p : mp) res.push_back(move(p.second));
            return res;
        }
    };