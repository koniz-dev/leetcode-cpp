class Solution {
    public:
        vector<int> topKFrequent(vector<int>& nums, int k) {
            unordered_map<int, int> freq;
    
            for (const int &num : nums) {
                freq[num]++; 
            }
    
            vector<pair<int,int>> arr(freq.begin(), freq.end());
            sort(arr.begin(), arr.end(), [](const pair<int,int> &a, const pair<int,int> &b) {
                return a.second > b.second;
            });
    
            vector<int> res;
            res.reserve(k);
            for (int i = 0; i < k && i < (int)arr.size(); i++) {
                res.push_back(arr[i].first);
            }
    
            return res;
        }
    };