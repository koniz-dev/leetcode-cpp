// Solution 1: faster
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> index, value, result;
        std::vector<int>::iterator it;

        for(int i = 0; i < nums.size(); i++) {
            int j = target - nums[i];

            it = std::find(value.begin(), value.end(), j);
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

// Solution 2: slower
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        
        for(int i = 0; i < nums.size() - 1; i++) {
            for(int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    result.push_back(i);
                    result.push_back(j);
                    break;
                }
            }
        }
        
        return result;
    }
};