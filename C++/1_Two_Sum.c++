class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> index, value, result;
        std::vector<int>::iterator it;
        for(int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            it = std::find(value.begin(), value.end(), complement);
            if (it != value.end()) {
                result.push_back(index[it - value.begin()]);
                result.push_back(i);
                break;
            }
            else {
                value.push_back(nums[i]);
                index.push_back(i);
            }
        }
        return result;
    }
};
