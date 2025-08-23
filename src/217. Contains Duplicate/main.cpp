class Solution {
    public:
        bool containsDuplicate(vector<int>& nums) {
            unordered_map<int, bool> seen;

            for (int i = 0; i < nums.size(); i++) {
                if (seen.find(nums[i]) != seen.end()) {
                    return true;
                }
                seen[nums[i]] = true;
            }

            return false;
        }
    };